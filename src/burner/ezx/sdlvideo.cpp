
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/stat.h>
#include <SDL/SDL.h>

#include "burner.h"
#include "fba_player.h"
#include "config.h"	
#include "sdlvideo.h"
#include "sdlinput.h"

int VideoBufferWidth = 0;
int VideoBufferHeight = 0;
int PhysicalBufferWidth = 0;

unsigned short *BurnVideoBuffer = NULL; // source FBA video buffer
unsigned short *VideoBuffer = NULL; // screen buffer

SDL_Surface *screen;

// --------------------------------

static unsigned int myHighCol16(int r, int g, int b, int /* i */)
{
	unsigned int t;
	t =(r<<8)&0xf800; // rrrr r000 0000 0000
	t|=(g<<3)&0x07e0; // 0000 0ggg ggg0 0000
	t|=(b>>3)&0x001f; // 0000 0000 000b bbbb
	return t;
}

static void Blit_null() {}

static void (*BurnerVideoTrans)() = Blit_null;

static void Blit_448x224_to_320x240() 
{
	// IGS 448x224
	unsigned short * p = &VideoBuffer[2560];
	unsigned short * q = BurnVideoBuffer;
	
	for (int i=0; i<224; i++)
		for (int j=0; j<64; j++) {
			p[0] = q[0];
			p[1] = q[1];
			p[2] = q[3];
			p[3] = q[4];
			p[4] = q[6];
			p += 5;
			q += 7;
		}
}

static void Blit_384x256_to_320x240()
{
#define COLORMIX(a, b) ( ((((a & 0xF81F) + (b & 0xF81F)) >> 1) & 0xF81F) | ((((a & 0x07E0) + (b & 0x07E0)) >> 1) & 0x07E0) )
	// Irem 384x256
	unsigned short * p = &VideoBuffer[0];
	unsigned short * q = BurnVideoBuffer + 384*8;
	
	for (int i=0; i<240; i++)
		for (int j=0; j<64; j++) {
			p[0] = q[0];
			p[1] = q[1];
			p[2] = COLORMIX(q[2],q[3]);
			p[3] = q[4];
			p[4] = q[5];
			p += 5;
			q += 6;
		}
#undef COLORMIX
}

static void Blit_384x240_to_320x240() 
{
#define COLORMIX(a, b) ( ((((a & 0xF81F) + (b & 0xF81F)) >> 1) & 0xF81F) | ((((a & 0x07E0) + (b & 0x07E0)) >> 1) & 0x07E0) )
	// 384x240
	unsigned short * p = &VideoBuffer[0];
	unsigned short * q = BurnVideoBuffer;
	
	for (int i=0; i<240; i++)
		for (int j=0; j<64; j++) {
			p[0] = q[0];
			p[1] = q[1];
			p[2] = COLORMIX(q[2],q[3]);
			p[3] = q[4];
			p[4] = q[5];
			p += 5;
			q += 6;
		}
#undef COLORMIX
}

static void Blit_384x224_to_320x240() 
{
#define COLORMIX(a, b) ( ((((a & 0xF81F) + (b & 0xF81F)) >> 1) & 0xF81F) | ((((a & 0x07E0) + (b & 0x07E0)) >> 1) & 0x07E0) )
	// CPS1 & CPS2 384x224
	unsigned short * p = &VideoBuffer[2560];
	unsigned short * q = BurnVideoBuffer;
	
	for (int i=0; i<224; i++)
		for (int j=0; j<64; j++) {
			p[0] = q[0];
			p[1] = q[1];
			p[2] = COLORMIX(q[2],q[3]);
			p[3] = q[4];
			p[4] = q[5];
			p += 5;
			q += 6;
		}
#undef COLORMIX
}

static void Blit_352x240_to_320x240() 
{
	// V-System 352x240
	unsigned short * p = &VideoBuffer[0];
	unsigned short * q = BurnVideoBuffer;
	
	for (int i=0; i<240; i++)
		for (int j=0; j<32; j++) {
			p[0] = q[0];
			p[1] = q[1];
			p[2] = q[2];
			p[3] = q[3];
			p[4] = q[4];
			p[5] = q[5];
			p[6] = q[6];
			p[7] = q[7];
			p[8] = q[8];
			p[9] = q[10];
			p += 10;
			q += 11;
		}
}

static void Blit_320x240_to_320x240() 
{
	// Cave & Toaplan 320x240
	unsigned short * p = &VideoBuffer[0];
	unsigned short * q = &BurnVideoBuffer[0];
	memcpy( p, q, 320 * 240 * 2 );
}

static void Blit_256x256_to_320x240() 
{
	// 256x256
	unsigned short * p = &VideoBuffer[(320-256)/2];
	unsigned short * q = &BurnVideoBuffer[0];
	for (int i = 0; i < 240; i++) {
		memcpy( p, q, 256 * 2 );
		p += 320;
		q += 256;
		if(i % 16 == 0) q += 256;
	}
}

static void Blit_256x256_to_400x240() 
{
	// 256x256
	unsigned short * p = &VideoBuffer[(400-256)/2];
	unsigned short * q = &BurnVideoBuffer[0];
	for (int i = 0; i < 240; i++) {
		memcpy( p, q, 256 * 2 );
		p += 400;
		q += 256;
		if(i % 16 == 0) q += 256; 
	}
}
static void Blit_448x224_to_400x240()
{
	// IGS 448x224
	unsigned short * p = &VideoBuffer[8*400+4];
	unsigned short * q = BurnVideoBuffer;
	
	for (int i=0; i<224; i++, p += 8)
		for (int j=0; j<56; j++) {
			p[0] = q[0];
			p[1] = q[1];
			p[2] = q[2];
			p[3] = q[3];
			p[4] = q[4];
			p[5] = q[5];
			p[6] = q[7];
			p += 7;
			q += 8;
		}
}

static unsigned int p_offset = 0, q_offset = 0;

static void Blit()
{
	register unsigned short *p = &VideoBuffer[p_offset];
	register unsigned short *q = &BurnVideoBuffer[0];
	for(int y = VideoBufferHeight; y--;) {
		for(int x = VideoBufferWidth; x--;)
			*p++ = *q++;
		p += screen->w - VideoBufferWidth;
	}
}

static void Blitf()
{
	register unsigned short *p = &VideoBuffer[p_offset];
	register unsigned short *q = &BurnVideoBuffer[q_offset];
	for(int y = VideoBufferHeight; y--;) {
		for(int x = VideoBufferWidth; x--;)
			*p++ = *q--;
		p += screen->w - VideoBufferWidth;
	}
}

typedef struct
{
	int dst_w;
	int dst_h;
	int src_w;
	int src_h;
	void (*blit)();
	void (*blitf)();
} BLIT_TABLE;

BLIT_TABLE blit_table[] = {
	{320, 240, 448, 224, Blit_448x224_to_320x240, Blit_448x224_to_320x240}, // IGS (PGM)
	{320, 240, 384, 256, Blit_384x256_to_320x240, Blit_384x256_to_320x240}, // Irem
	{320, 240, 384, 240, Blit_384x240_to_320x240, Blit_384x240_to_320x240}, // Cave
	{320, 240, 384, 224, Blit_384x224_to_320x240, Blit_384x224_to_320x240}, // CPS1 & CPS2
	{320, 240, 352, 240, Blit_352x240_to_320x240, Blit_352x240_to_320x240}, // V-System
	{320, 240, 320, 240, Blit_320x240_to_320x240, Blit_320x240_to_320x240}, // Cave & Toaplan
	{320, 240, 256, 256, Blit_256x256_to_320x240, Blit_256x256_to_320x240},
	{400, 240, 256, 256, Blit_256x256_to_400x240, Blit_256x256_to_400x240},
	{400, 240, 448, 224, Blit_448x224_to_400x240, Blit_448x224_to_400x240}, // IGS (PGM)
	{  0,   0,   0,   0, NULL, NULL}
};

int VideoInit()
{
	BurnDrvGetFullSize(&VideoBufferWidth, &VideoBufferHeight);
	printf("w=%d h=%d\n",VideoBufferWidth, VideoBufferHeight);

	nBurnBpp = 2;
	BurnHighCol = myHighCol16;

	BurnRecalcPal();
	nBurnPitch = VideoBufferWidth * 2;
	PhysicalBufferWidth = screen->w;
	BurnVideoBuffer = (unsigned short *)malloc(VideoBufferWidth * VideoBufferHeight * 2);
	BurnerVideoTrans = Blit_320x240_to_320x240; // default blit

	// if source buffer < screen buffer then set general blitting routine with centering if needed
	if(VideoBufferWidth <= screen->w && VideoBufferHeight <= screen->h) {
		p_offset = (screen->w - VideoBufferWidth)/2 + (screen->h - VideoBufferHeight)/2*screen->w;
		q_offset = VideoBufferWidth*VideoBufferHeight-1;
		if(BurnDrvGetFlags() & BDF_ORIENTATION_FLIPPED)
			BurnerVideoTrans = Blitf;
		else
			BurnerVideoTrans = Blit;
	} else {
		// if source buffer is bigger than screen buffer then find an appropriate downscaler
		for(int i = 0; blit_table[i].dst_w != 0; i++) {
			if(blit_table[i].dst_w == screen->w && blit_table[i].dst_h == screen->h &&
			   blit_table[i].src_w == VideoBufferWidth && blit_table[i].src_h == VideoBufferHeight) {
				if (BurnDrvGetFlags() & BDF_ORIENTATION_FLIPPED)
					BurnerVideoTrans = blit_table[i].blitf;
				else
					BurnerVideoTrans = blit_table[i].blit;
				break;
			}
		}
	}

	return 0;
}

void VideoTrans()
{
	BurnerVideoTrans();
}

void VideoExit()
{
	free(BurnVideoBuffer);
	BurnVideoBuffer = NULL;
	BurnerVideoTrans = Blit_null;
}

void SystemInit()
{
	static const char* WINDOW_TITLE = "FBA";

	if ((SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE)) < 0) {
		printf("sdl failed to init\n");
	}

	// Initialize SDL
	screen = SDL_SetVideoMode(320, 240, 16, SDL_SWSURFACE);
	/*{
		int i = 0; // 0 - 320x240, 1 - 400x240, 2 - 480x272
		int surfacewidth, surfaceheight;
		#define NUMOFVIDEOMODES 3
		struct {
			int x;
			int y;
		} vm[NUMOFVIDEOMODES] = {
			{320, 240},
			{400, 240},
			{480, 272}
		};

		// check 3 videomodes: 480x272, 400x240, 320x240
		for(i = NUMOFVIDEOMODES-1; i >= 0; i--) {
			if(SDL_VideoModeOK(vm[i].x, vm[i].y, 16, SDL_SWSURFACE) != 0) {
				surfacewidth = vm[i].x;
				surfaceheight = vm[i].y;
				break;
			}
		}
		screen = SDL_SetVideoMode(surfacewidth, surfaceheight, 16, SDL_SWSURFACE);
	}*/
	if(!screen)
	{
		printf("SDL_SetVideoMode screen not initialised.\n");
	}
	else printf("SDL_SetVideoMode successful.\n");
	VideoBuffer = (unsigned short*)screen->pixels;

	SDL_ShowCursor(SDL_DISABLE);
	SDL_WM_SetCaption( WINDOW_TITLE, 0 );

	sdl_input_init();
}

void SystemExit(char *frontend)
{
	struct stat info;
	SDL_Quit();
#ifndef WIN32
	if( (lstat(frontend, &info) == 0) && S_ISREG(info.st_mode) )
	{
	char path[256];
	char *p;
		strcpy(path, frontend);
		p = strrchr(path, '/');
		if(p == NULL) p = strrchr(path, '\\');
		if(p != NULL)
		{
			*p = '\0';
			chdir(path);
		}
		execl(frontend, frontend, NULL);
	}
#endif
}

void VideoClear()
{
	memset(VideoBuffer,0,320*240*2);
}

void VideoFlip()
{
	SDL_Flip(screen);
}