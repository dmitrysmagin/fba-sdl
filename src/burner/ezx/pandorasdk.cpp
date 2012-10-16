

#include <getopt.h>
#include <sys/stat.h>
#include <SDL/SDL.h>

#include "pandorasdk.h"
#include "burner.h"
#include "config.h"
#include "snd.h"
#include "fba_player.h"

#define BLOCKSIZE 1024
#define SetTaken(Start, Size) TakenSize[(Start - 0x2000000) / BLOCKSIZE] = (Size - 1) / BLOCKSIZE + 1

extern char **environ;

extern CFG_OPTIONS config_options;
extern CFG_KEYMAP config_keymap;

unsigned short *VideoBuffer = NULL;
static int screen_mode = 0;

char LEFTDOWN,RIGHTDOWN,ADOWN,BDOWN,XDOWN,YDOWN,UPDOWN,DOWNDOWN,STARTDOWN,SELECTDOWN,LSDOWN,RSDOWN,QDOWN,VUDOWN,VDDOWN,PAUSEDOWN=0;
int kinput=0;

int WINDOW_WIDTH;
int WINDOW_HEIGHT;


//struct usbjoy *joys[4];
char joyCount = 0;

SDL_Joystick *joys[4];
const char* WINDOW_TITLE = "FBA";

SDL_Surface* myscreen;
//SDL_Surface* framebuffer[4];
//SDL_Surface* SDL_VideoBuffer;

int vb;

void gp2x_initialize()
{
	BurnDrvGetFullSize(&WINDOW_WIDTH, &WINDOW_HEIGHT);

	printf("Setting screen to %d x %d\n",WINDOW_WIDTH,WINDOW_HEIGHT);
	if ((SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_VIDEO | SDL_INIT_TIMER))<0)
	{
		printf("sdl failed to init\n");
	}

	// Initialize SDL
	myscreen = SDL_SetVideoMode(320, 240, 16, SDL_SWSURFACE);
	if(!myscreen)
	{
		printf("SDL_SetVideoMode screen not initialised.\n"); // debug output example for serial cable
	}
	else printf("SDL_SetVideoMode successful.\n");
	VideoBuffer=(unsigned short*)myscreen->pixels;

	SDL_ShowCursor(SDL_DISABLE);							// Disable mouse cursor on gp2x
	SDL_WM_SetCaption( WINDOW_TITLE, 0 );					// Sets the window title (not needed for gp2x)

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

	gp2x_video_flip();
}

void gp2x_terminate(char *frontend)
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

// don't forget to check orientation BurnDrvGetFlags() & BDF_ORIENTATION_VERTICAL)
// because we should change dpad directions
int get_pc_keyboard()
{
	int pckeydata=0;
	kinput=0;
	SDL_Event event;
	while( SDL_PollEvent( &event ) )
		{
//			printf("event\n");
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
				{
						// PC buttons
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
				//printf("event=%d\n",event.type);
				if (event.type== SDL_KEYDOWN)
				{
					// PC buttons
					kinput=event.key.keysym.scancode;
					//printf("key=%d\n",event.key.keysym.sym);

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
		if (BurnDrvGetFlags() & BDF_ORIENTATION_VERTICAL) {
			if (UPDOWN) pckeydata|=MY_LEFT;
			if (LEFTDOWN) pckeydata|=MY_DOWN;
			if (RIGHTDOWN) pckeydata|=MY_UP;
			if (DOWNDOWN) pckeydata|=MY_RIGHT;
		} else {
			if (UPDOWN) pckeydata|=MY_UP;
			if (LEFTDOWN) pckeydata|=MY_LEFT;
			if (RIGHTDOWN) pckeydata|=MY_RIGHT;
			if (DOWNDOWN) pckeydata|=MY_DOWN;
		}
		
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

unsigned long gp2x_joystick_read(void) // called from do_keypad() in fba_player.cpp
{
	int value=get_pc_keyboard();
	return value;
}

void gp2x_clear_framebuffers()
{
	memset(VideoBuffer,0,/*WINDOW_HEIGHT*WINDOW_WIDTH*2*/320*240*2);
}

void gp2x_video_flip()
{
	SDL_Flip(myscreen);
}
