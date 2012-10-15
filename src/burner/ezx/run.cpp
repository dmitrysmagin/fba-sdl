
// Run module
#include <SDL/SDL.h>

#include "burner.h"
#include "gamewidget.h"
#include "snd.h"
#include "font.h"
#include "pandorasdk.h"
#include "config.h"


extern int fps;
extern unsigned int FBA_KEYPAD[4];
extern CFG_OPTIONS config_options;
extern void do_keypad();

static int VideoBufferWidth = 0;
static int VideoBufferHeight = 0;
static int PhysicalBufferWidth = 0;

/*#ifndef HighCol16(r,g,b,i)
#define HighCol16(r,g,b,i) ((r<<8)&0xf800)|((g<<3)&0x07e0)|(b>>3)
#endif
*/

static unsigned short * BurnVideoBuffer = NULL;	// think max enough
static bool BurnVideoBufferAlloced = false;

bool bShowFPS = false;
bool bPauseOn = false;

int InpMake(unsigned int[]);
void uploadfb(void);
void VideoBufferUpdate(void);
void VideoTrans();

int RunReset()
{
	nFramesEmulated = 0;
	nCurrentFrame = 0;
	nFramesRendered = 0;

	return 0;
}

int RunOneFrame(bool bDraw, int fps)
{
	do_keypad();
	InpMake(FBA_KEYPAD);
	if (bPauseOn==false)
	{

	nFramesEmulated++;
	nCurrentFrame++;

	pBurnDraw = NULL;
	if ( bDraw )
	{
		nFramesRendered++;
		VideoBufferUpdate();
		pBurnDraw = (unsigned char *)&BurnVideoBuffer[0];
	}
//	printf("vbupdate %2d  ",(SDL_GetTicks()-profile));
	BurnDrvFrame();
 //   printf("bdframe %2d  \n",(SDL_GetTicks()-profile));
	pBurnDraw = NULL;
	if ( bDraw )
	{
		VideoTrans();
		if (bShowFPS)
		{
			char buf[10];
			int x;
			sprintf(buf, "FPS: %2d/%2d", fps,(nBurnFPS/100));
			DrawRect((uint16 *) (unsigned short *) &VideoBuffer[0],0, 0, 60, 9, 0,PhysicalBufferWidth);
			DrawString (buf, (unsigned short *) &VideoBuffer[0], 0, 0,PhysicalBufferWidth);
		}

		gp2x_video_flip();
	}
	}
	if (bPauseOn)
	{
		DrawString ("PAUSED", (unsigned short *) &VideoBuffer[0], (PhysicalBufferWidth>>1)-24, 120,PhysicalBufferWidth);
		gp2x_video_flip();
	}
	return 0;
}

// --------------------------------

/*static unsigned int HighCol16(int r, int g, int b, int )
{
	unsigned int t;

	t  = (r << 8) & 0xF800;
	t |= (g << 3) & 0x07E0;
	t |= (b >> 3) & 0x001F;

	return t;
}*/

static unsigned int myHighCol16(int r, int g, int b, int /* i */)
{
	unsigned int t;
	t =(r<<8)&0xf800; // rrrr r000 0000 0000
	t|=(g<<3)&0x07e0; // 0000 0ggg ggg0 0000
	t|=(b>>3)&0x001f; // 0000 0000 000b bbbb
	return t;
}

static void BurnerVideoTransDemo(){}

static void (*BurnerVideoTrans) () = BurnerVideoTransDemo;

//typedef unsigned long long UINT64;

static void BurnerVideoTrans_rotate()
{
	int z=VideoBufferHeight*VideoBufferWidth+1;
	unsigned short * p = &VideoBuffer[0];
	unsigned short * q = &BurnVideoBuffer[VideoBufferWidth-1];
	for (int j=0; j<VideoBufferWidth; j++,q-=z)
	{
		for (int i=0; i<VideoBufferHeight; i++)
		{
			memcpy(p,q,2);
			p++;
			q+=VideoBufferWidth;
		}
	}
}

static void BurnerVideoTrans_flipped()
{
	int z=VideoBufferHeight*VideoBufferWidth+1;
	unsigned short * p = &VideoBuffer[0];
	unsigned short * q = &BurnVideoBuffer[VideoBufferWidth*(VideoBufferHeight-1)];
	for (int j=0; j<VideoBufferWidth; j++,q+=z)
	{
		for (int i=0; i<VideoBufferHeight; i++)
		{
			memcpy(p,q,2);
			p++;
			q-=VideoBufferWidth;
		}
	}
}

static void BurnerVideoTrans_flipped_horiz()
{
	unsigned short * p = &VideoBuffer[0];
	unsigned short * q = &BurnVideoBuffer[(VideoBufferHeight-1)*VideoBufferWidth];
	for (int j=0; j<VideoBufferHeight; j++,q-=VideoBufferWidth,p+=VideoBufferWidth)
	{
		memcpy(p,q,VideoBufferWidth<<1);
	}
}

static void BurnerVideoTrans_flipped_horiz2()
{
	unsigned short * p = &VideoBuffer[0];
	unsigned short * q = &BurnVideoBuffer[VideoBufferHeight*VideoBufferWidth-1];
	   for (int j=0; j<VideoBufferHeight; j++)
	{
		for (int i=0; i<VideoBufferWidth; i++)
		{
			memcpy(p,q,2);
			p++;
			q--;
		}
	}
}

int VideoInit()
{
	BurnDrvGetFullSize(&VideoBufferWidth, &VideoBufferHeight);
	printf("w=%d h=%d\n",VideoBufferWidth, VideoBufferHeight);
//	printf("Screen Size: %d x %d\n", VideoBufferWidth, VideoBufferHeight);

	nBurnBpp = 2;
	BurnHighCol = myHighCol16;

	BurnRecalcPal();

	if (((config_options.option_rotate==0) && (BurnDrvGetFlags() & BDF_ORIENTATION_VERTICAL)) || (config_options.option_rotate==2))
	{
		BurnVideoBuffer = (unsigned short *)malloc( VideoBufferWidth * VideoBufferHeight * 2 );
		BurnVideoBufferAlloced = true;
		nBurnPitch  = VideoBufferWidth * 2;
		if (BurnDrvGetFlags() & BDF_ORIENTATION_FLIPPED) BurnerVideoTrans = BurnerVideoTrans_flipped; else BurnerVideoTrans = BurnerVideoTrans_rotate;
		PhysicalBufferWidth = VideoBufferHeight;
	}
	else if (BurnDrvGetFlags() & BDF_ORIENTATION_FLIPPED)
	{
		BurnVideoBuffer = (unsigned short *)malloc( VideoBufferWidth * VideoBufferHeight * 2 );
		BurnVideoBufferAlloced = true;
		nBurnPitch  = VideoBufferWidth * 2;
		BurnerVideoTrans = BurnerVideoTrans_flipped_horiz2;
		PhysicalBufferWidth = VideoBufferWidth;
	}
	else
	{
		BurnVideoBuffer = &VideoBuffer[0];
		BurnVideoBufferAlloced = false;
		BurnerVideoTrans = BurnerVideoTransDemo;
		PhysicalBufferWidth	= VideoBufferWidth;
		nBurnPitch  = VideoBufferWidth * 2;

	}


	return 0;
}

// 'VideoBuffer' is updated each frame due to double buffering, so we sometimes need to ensure BurnVideoBuffer is updated too.
void VideoBufferUpdate (void)
{
	if (BurnVideoBufferAlloced == false) BurnVideoBuffer = &VideoBuffer[0];
	/*if (BurnVideoBufferAlloced == false)
	{
		if (VideoBufferWidth == 384 && VideoBufferHeight == 224)
		{
			BurnVideoBuffer = &VideoBuffer[3072];
		}
		else if (VideoBufferWidth == 384 && VideoBufferHeight == 240)
		{
			BurnVideoBuffer = &VideoBuffer[0];
		}
		else if (VideoBufferWidth == 320 && VideoBufferHeight == 240)
		{
			BurnVideoBuffer = &VideoBuffer[0];
		}
		else if (VideoBufferWidth == 320 && VideoBufferHeight == 224)
		{
			BurnVideoBuffer = &VideoBuffer[2560];
			//BurnVideoBuffer = &VideoBuffer[0];
		}
		else if (VideoBufferWidth == 448)
		{
			BurnVideoBuffer = &VideoBuffer[3584];
		}
		else
		{
			BurnVideoBuffer = NULL;
		}
	}*/
}

void VideoTrans()
{
	BurnerVideoTrans();
}

void VideoExit()
{
	if ( BurnVideoBufferAlloced )
		free(BurnVideoBuffer);
	BurnVideoBuffer = NULL;
	BurnVideoBufferAlloced = false;
	BurnerVideoTrans = BurnerVideoTransDemo;
}

void ChangeFrameskip()
{
	bShowFPS = !bShowFPS;
	gp2x_clear_framebuffers();
	nFramesRendered = 0;
}
