#include "pandorasdk.h"
//#include "gp2xmemfuncs.h"
#include "burner.h"
#include "config.h"
#include "snd.h"
#include <getopt.h>
#include "fba_player.h"
#include "SDL/SDL.h"

#define BLOCKSIZE 1024
#define SetTaken(Start, Size) TakenSize[(Start - 0x2000000) / BLOCKSIZE] = (Size - 1) / BLOCKSIZE + 1

//extern CFG_OPTIONS config_options;

extern char **environ;

extern CFG_OPTIONS config_options;
extern CFG_KEYMAP config_keymap;


//static int mem_fd = -1;
//void *UpperMem;
//int TakenSize[0x2000000 / BLOCKSIZE];
unsigned short *VideoBuffer = NULL;
static int screen_mode = 0;
//volatile static unsigned short *gp2xregs = NULL;
//unsigned long gp2x_physvram[4]={0,0,0,0};
//unsigned short *framebuffer[4]={0,0,0,0};


char LEFTDOWN,RIGHTDOWN,ADOWN,BDOWN,XDOWN,YDOWN,UPDOWN,DOWNDOWN,STARTDOWN,SELECTDOWN,LSDOWN,RSDOWN,QDOWN,VUDOWN,VDDOWN,PAUSEDOWN=0;
int kinput=0;

int WINDOW_WIDTH;
int WINDOW_HEIGHT;


static int currentframebuffer = 0;
//struct usbjoy *joys[4];
char joyCount = 0;

SDL_Joystick *joys[4];
const char* WINDOW_TITLE = "FBA";

SDL_Surface* myscreen;
SDL_Surface* framebuffer[4];
SDL_Surface* SDL_VideoBuffer;

#define FBIO_WAITFORVSYNC _IOW('F', 0x20, __u32)
unsigned long fbdev;
int vb;

    int scaleheight=480;
    int scalewidth=800;

void gp2x_initialize()
{

    BurnDrvGetFullSize(&WINDOW_WIDTH, &WINDOW_HEIGHT);
    if (((config_options.option_rotate==0) && (BurnDrvGetFlags() & BDF_ORIENTATION_VERTICAL)) || (config_options.option_rotate==2))
    {
        int t;
        t=WINDOW_HEIGHT;
        WINDOW_HEIGHT=WINDOW_WIDTH;
        WINDOW_WIDTH=t;
    }
    printf("dw:%d dh:%d\n",WINDOW_WIDTH,WINDOW_HEIGHT);
    if (config_options.option_rescale==0)
    {
        scaleheight=WINDOW_HEIGHT;
        scalewidth=WINDOW_WIDTH;
        if (scaleheight>480) scaleheight=480;
        if (scalewidth>800) scalewidth=800;
    }
    if (config_options.option_rescale==1)
    {
        scaleheight=WINDOW_HEIGHT*2;
        scalewidth=WINDOW_WIDTH*2;
        if (scaleheight>480) scaleheight=480;
        if (scalewidth>800) scalewidth=800;
    }
    if (config_options.option_rescale==2)
    {
        float xw,xh;
        xh=(float)480/(float)WINDOW_HEIGHT;
        xw=(float)800/(float)WINDOW_WIDTH;
        if (xh>xw)
        {
            scalewidth=(int)((float)WINDOW_WIDTH*xw);
            scaleheight=(int)((float)WINDOW_HEIGHT*xw);
        }
        else
        {
            scalewidth=(int)((float)WINDOW_WIDTH*xh);
            scaleheight=(int)((float)WINDOW_HEIGHT*xh);

        }
        if (scaleheight>480) scaleheight=480;
        if (scalewidth>800) scalewidth=800;
    }
    if (config_options.option_rescale==3)
    {
        scaleheight=480;
        scalewidth=800;
    }

    char scaling[64];
    sprintf(scaling,"SDL_OMAP_LAYER_SIZE=%dx%d",scalewidth,scaleheight);
    printf("scaling x:%d y:%d   %s\n",scalewidth,scaleheight,scaling);

    for (int i=0;environ[i];i++)
    {
        if (strstr(environ[i],"SDL_OMAP_LAYER_SIZE="))
        {
            strcpy(environ[i],scaling);
        }

    }


    printf("Setting screen to %d x %d\n",WINDOW_WIDTH,WINDOW_HEIGHT);
    if ((SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_VIDEO | SDL_INIT_TIMER))<0)
    {
        printf("sdl failed to init\n");
    }			// Initialize SDL
//    myscreen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 16, SDL_HWSURFACE | SDL_HWPALETTE | SDL_DOUBLEBUF);
    myscreen = SDL_SetVideoMode(scalewidth, scaleheight, 16, SDL_FULLSCREEN | SDL_SWSURFACE  | SDL_DOUBLEBUF);
    if(!myscreen)
	{
		printf("SDL_SetVideoMode screen not initialised.\n");								// debug output example for serial cable
	}
	else printf("SDL_SetVideoMode successful.\n");
	SDL_ShowCursor(SDL_DISABLE);															// Disable mouse cursor on gp2x
	SDL_WM_SetCaption( WINDOW_TITLE, 0 );													// Sets the window title (not needed for gp2x)

    fbdev=open("/dev/fb0", O_RDONLY);

    joyCount=SDL_NumJoysticks();
	if (joyCount>5) joyCount=5;
	printf("%d Joystick(s) Found\n",joyCount);
	//if ((joyCount==1) && (strcmp(SDL_JoystickName(0),"gpio-keys")==0)) joyCount=0;
	if (joyCount>0)
	{

	    for (int i=0;i<joyCount;i++)
        {
            printf("%s\t",SDL_JoystickName(i));
            joys[i] = SDL_JoystickOpen(i);
            printf("Hats %d\t",SDL_JoystickNumHats(joys[i]));
            printf("Buttons %d\t",SDL_JoystickNumButtons(joys[i]));
            printf("Axis %d\n",SDL_JoystickNumAxes(joys[i]));
            if (strcmp(SDL_JoystickName(i),"nub0")==0) joys[0]=SDL_JoystickOpen(i);
            if (strcmp(SDL_JoystickName(i),"nub1")==0) joys[1]=SDL_JoystickOpen(i);
        }
        //if (joyCount>1) joys[0]=SDL_JoystickOpen(1);
        //if (joyCount>2) joys[1]=SDL_JoystickOpen(2);
	}
	VideoBuffer=(unsigned short*)malloc((WINDOW_WIDTH*2) * WINDOW_HEIGHT);
	SDL_VideoBuffer=SDL_CreateRGBSurfaceFrom(VideoBuffer,WINDOW_WIDTH*2,WINDOW_HEIGHT,16,WINDOW_WIDTH*2,0xF800,0x7E0,0x1F,0x0);
	SDL_LockSurface(SDL_VideoBuffer);
    gp2x_video_flip();
}

void gp2x_terminate(char *frontend)
{
    struct stat info;
    SDL_Quit();
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

}

int get_pc_keyboard()
{
    int pckeydata=0;
    kinput=0;
    SDL_Event event;
	while( SDL_PollEvent( &event ) )
		{
//		    printf("event\n");
                    /*if ((event.type==SDL_JOYBUTTONUP) && (p[pi].joy<5))
                    {
                        if (event.jbutton.button==p[pi].fire) p[pi].firedown=0;
                        if (event.jbutton.button==p[pi].thrust) p[pi].thrustdown=0;
                        if (event.jbutton.button==p[pi].left) p[pi].leftdown=0;
                        if (event.jbutton.button==p[pi].right) p[pi].rightdown=0;
                    }

                    if ((event.type==SDL_JOYBUTTONDOWN) && (p[pi].joy<5))
                    {
                        if (event.jbutton.button==p[pi].fire) p[pi].firedown=1;
                        if (event.jbutton.button==p[pi].thrust) p[pi].thrustdown=1;
                        if (event.jbutton.button==p[pi].left) p[pi].leftdown=1;
                        if (event.jbutton.button==p[pi].right) p[pi].rightdown=1;
                    }

                    if ((event.type==SDL_KEYUP) && (p[pi].joy==5))
                    {
                        if (event.key.keysym.sym==p[pi].fire) p[pi].firedown=0;
                        if (event.key.keysym.sym==p[pi].thrust) p[pi].thrustdown=0;
                        if (event.key.keysym.sym==p[pi].left) p[pi].leftdown=0;
                        if (event.key.keysym.sym==p[pi].right) p[pi].rightdown=0;
                    }

                    if ((event.type==SDL_KEYDOWN) && (p[pi].joy==5))
                    {
                        kinput=event.key.keysym.sym;
                        if (event.key.keysym.sym==p[pi].fire) p[pi].firedown=1;
                        if (event.key.keysym.sym==p[pi].thrust) p[pi].thrustdown=1;
                        if (event.key.keysym.sym==p[pi].left) p[pi].leftdown=1;
                        if (event.key.keysym.sym==p[pi].right) p[pi].rightdown=1;
                    }*/


                if (event.type== SDL_KEYUP)
                {																	// PC buttons

						if (event.key.keysym.sym==config_keymap.up)
							UPDOWN=0;

						if (event.key.keysym.sym==config_keymap.left)
							LEFTDOWN=0;

						if (event.key.keysym.sym==config_keymap.right)
							RIGHTDOWN=0;

                        if (event.key.keysym.sym==config_keymap.fire1)
                            ADOWN=0;

                        if (event.key.keysym.sym==config_keymap.fire4)
                            YDOWN=0;

                        if (event.key.keysym.sym==config_keymap.fire2)
                            XDOWN=0;

                        if (event.key.keysym.sym==config_keymap.fire3)
                            BDOWN=0;

                        if (event.key.keysym.sym==config_keymap.fire5)
                            LSDOWN=0;

                        if (event.key.keysym.sym==config_keymap.down)
							DOWNDOWN=0;

                        if (event.key.keysym.sym==config_keymap.fire6)
							RSDOWN=0;

                        if (event.key.keysym.sym==config_keymap.coin1)
							SELECTDOWN=0;

                        if (event.key.keysym.sym==config_keymap.start1)
                            STARTDOWN=0;

                        if (event.key.keysym.sym==config_keymap.quit)
                            QDOWN=0;

                        if (event.key.keysym.sym==config_keymap.pause)
                            PAUSEDOWN=0;


				}
    //            printf("event=%d\n",event.type);
				if (event.type== SDL_KEYDOWN)
				{																	// PC buttons
				    kinput=event.key.keysym.scancode;
  //                      printf("key=%d\n",event.key.keysym.sym);

						if (event.key.keysym.sym==config_keymap.up)
							UPDOWN=1;

						if (event.key.keysym.sym==config_keymap.left)
							LEFTDOWN=1;

						if (event.key.keysym.sym==config_keymap.right)
							RIGHTDOWN=1;

                        if (event.key.keysym.sym==config_keymap.fire1)
                            ADOWN=1;

                        if (event.key.keysym.sym==config_keymap.fire4)
                            YDOWN=1;

                        if (event.key.keysym.sym==config_keymap.fire2)
                            XDOWN=1;

                        if (event.key.keysym.sym==config_keymap.fire3)
                            BDOWN=1;

                        if (event.key.keysym.sym==config_keymap.fire5)
                            LSDOWN=1;

                        if (event.key.keysym.sym==config_keymap.down)
							DOWNDOWN=1;

                        if (event.key.keysym.sym==config_keymap.fire6)
							RSDOWN=1;


                        if (event.key.keysym.sym==config_keymap.coin1)
							SELECTDOWN=1;

                        if (event.key.keysym.sym==config_keymap.start1)
                            STARTDOWN=1;

                        if (event.key.keysym.sym==config_keymap.quit)
                            QDOWN=1;

                        if (event.key.keysym.sym==config_keymap.pause)
                            PAUSEDOWN=1;


				}

			}


		if (UPDOWN) pckeydata|=MY_UP;
		if (LEFTDOWN) pckeydata|=MY_LEFT;
		if (RIGHTDOWN) pckeydata|=MY_RIGHT;
		if (DOWNDOWN) pckeydata|=MY_DOWN;
		if (ADOWN) pckeydata|=MY_BUTT_A;
		if (YDOWN) pckeydata|=MY_BUTT_Y;
		if (XDOWN) pckeydata|=MY_BUTT_X;
		if (BDOWN) pckeydata|=MY_BUTT_B;
		if (LSDOWN) pckeydata|=MY_BUTT_SL;
		if (RSDOWN) pckeydata|=MY_BUTT_SR;
		if (STARTDOWN) pckeydata|=MY_START;
		if (SELECTDOWN) pckeydata|=MY_SELECT;
		if (PAUSEDOWN) pckeydata|=MY_PAUSE;
		if (QDOWN)
		{
		    pckeydata|=MY_QT;
		}

		if (kinput)
		{
		    int conv=0;
		    //printf("keycode: %d\n",kinput);
		    if (kinput==32) {kinput=1;conv=1;}
            if (kinput==46) {kinput=38;conv=1;}
		    if (kinput==33) {kinput=39;conv=1;}
		    if (kinput==13) {kinput=40;conv=1;}
		    if ((kinput>=97) && (kinput<=122)) {kinput-=95;conv=1;}
		    if ((kinput>=48) && (kinput<=57)) {kinput-=20;conv=1;}
		    if (conv==0) kinput=0;
		}

        return pckeydata;
}


unsigned long gp2x_joystick_read(void)
{
  int value=get_pc_keyboard();
  return value;
}

void drawSprite(SDL_Surface* imageSurface, SDL_Surface* screenSurface, int srcX, int srcY, int dstX, int dstY, int width, int height)
{
	SDL_Rect srcRect;
	srcRect.x = srcX;
	srcRect.y = srcY;
	srcRect.w = width;
	srcRect.h = height;

	SDL_Rect dstRect;
	dstRect.x = dstX;
	dstRect.y = dstY;
	dstRect.w = scalewidth;
	dstRect.h = scaleheight;
        SDL_SoftStretch(imageSurface, &srcRect, screenSurface, &dstRect);
//	SDL_BlitSurface(imageSurface, &srcRect, screenSurface, &dstRect);
}



void gp2x_clear_framebuffers()
{
    memset(VideoBuffer,0,WINDOW_HEIGHT*WINDOW_WIDTH*2);
}

void gp2x_video_flip()
{
    SDL_UnlockSurface(SDL_VideoBuffer);
    drawSprite(SDL_VideoBuffer,myscreen,0,0,0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
    if (nBurnFPS>5900) ioctl(fbdev,FBIO_WAITFORVSYNC,&vb); //use vblank if running at 60 hz
    SDL_Flip(myscreen);
    SDL_LockSurface(SDL_VideoBuffer);
}


//void * UpperMalloc(size_t size)
//{
    //printf("using upper malloc\n");
  /*int i = 0;
ReDo:
  for (; TakenSize[i]; i += TakenSize[i]);
  if (i >= 0x2000000 / BLOCKSIZE) {
    printf("UpperMalloc out of mem!");
    return NULL;
  }
  int BSize = (size - 1) / BLOCKSIZE + 1;
  for(int j = 1; j < BSize; j++) {
    if (TakenSize[i + j]) {
      i += j;
      goto ReDo; //OMG Goto, kill me.
    }
  }

  TakenSize[i] = BSize;
  void* mem = ((char*)UpperMem) + i * BLOCKSIZE;
//  gp2x_memset(mem, 0, size);
*/
/*void * mem=(char*)malloc(size);
  if (mem==NULL) printf("mem alloc of %d bytes failed\n",size);
  return mem;
}/*

//Releases UpperMalloced memory
//void UpperFree(void* mem)
{
 /* int i = (((int)mem) - ((int)UpperMem));
  if (i < 0 || i >= 0x2000000) {
    fprintf(stderr, "UpperFree of not UpperMalloced mem: %p\n", mem);
  } else {
    if (i % BLOCKSIZE)
      fprintf(stderr, "delete error: %p\n", mem);
    TakenSize[i / BLOCKSIZE] = 0;
  }*/
//  free(mem);
//}

//Returns the size of a UpperMalloced block.
/*int GetUpperSize(void* mem)
{
  int i = (((int)mem) - ((int)UpperMem));
  if (i < 0 || i >= 0x2000000) {
    fprintf(stderr, "GetUpperSize of not UpperMalloced mem: %p\n", mem);
    return -1;
  }
  return TakenSize[i / BLOCKSIZE] * BLOCKSIZE;
}

*/
