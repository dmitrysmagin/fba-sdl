

#include <getopt.h>
#include <sys/stat.h>
#include <SDL/SDL.h>

#include "pandorasdk.h"
#include "burner.h"
#include "config.h"
#include "snd.h"
#include "fba_player.h"
#include "sdlinput.h"

extern CFG_OPTIONS config_options;
extern CFG_KEYMAP config_keymap;

unsigned short *VideoBuffer = NULL;

int WINDOW_WIDTH;
int WINDOW_HEIGHT;

const char* WINDOW_TITLE = "FBA";

SDL_Surface* myscreen;

void gp2x_initialize()
{
	if ((SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE)) < 0) {
		printf("sdl failed to init\n");
	}

	// Initialize SDL
	myscreen = SDL_SetVideoMode(320, 240, 16, SDL_SWSURFACE);
	if(!myscreen)
	{
		printf("SDL_SetVideoMode screen not initialised.\n");
	}
	else printf("SDL_SetVideoMode successful.\n");
	VideoBuffer = (unsigned short*)myscreen->pixels;

	SDL_ShowCursor(SDL_DISABLE);
	SDL_WM_SetCaption( WINDOW_TITLE, 0 );

	sdl_input_init();
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

void gp2x_clear_framebuffers()
{
	memset(VideoBuffer,0,/*WINDOW_HEIGHT*WINDOW_WIDTH*2*/320*240*2);
}

void gp2x_video_flip()
{
	SDL_Flip(myscreen);
}
