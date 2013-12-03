/*
 * FinalBurn Alpha for Dingux/OpenDingux
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <SDL/SDL.h>

#include "fba_player.h"
#include "font.h"
#include "snd.h"

#include "burner.h"
#include "sdlgui.h"
#include "sdlvideo.h"
#include "sdlinput.h"
#include "sdlromload.h"

#ifndef DRV_NAME
#define DRV_NAME (0)
#endif

static int frame_count = 0;
bool GameLooping;
int fps=0;

void CreateCapexLists()
{
	printf("Create rom lists (%d)\n",nBurnDrvCount);
	FILE * zipf;
	FILE * romf;
	zipf=fopen("zipname.fba","w");
	romf=fopen("rominfo.fba","w");
	char * fullname;
	int j;
	for (int i=0;i<nBurnDrvCount;i++)
	{
		nBurnDrvActive=i;
		fullname=(char*)malloc(strlen(BurnDrvGetTextA(DRV_FULLNAME))+1);
		strcpy(fullname,BurnDrvGetTextA(DRV_FULLNAME));
		for (j=0;j<strlen(fullname);j++)
		{
			if (fullname[j]==',') fullname[j]=' ';
		}
		if (BurnDrvGetTextA(DRV_PARENT)) fprintf(romf,"FILENAME( %s %s %s \"%s\" )\n",BurnDrvGetTextA(DRV_NAME),BurnDrvGetTextA(DRV_PARENT),BurnDrvGetTextA(DRV_DATE),BurnDrvGetTextA(DRV_MANUFACTURER)); else fprintf(romf,"FILENAME( %s fba %s \"%s\" )\n",BurnDrvGetTextA(DRV_NAME),BurnDrvGetTextA(DRV_DATE),BurnDrvGetTextA(DRV_MANUFACTURER));
		fprintf(zipf,"%s,%s,%s %s\n",BurnDrvGetTextA(DRV_NAME),fullname,BurnDrvGetTextA(DRV_DATE),BurnDrvGetTextA(DRV_MANUFACTURER));
		free(fullname);
	}
	fclose(zipf);
	fclose(romf);
	char temp[24];
	strcpy(temp,"FBA ");
	strcat(temp,szAppBurnVer);
	strcat(temp,".dat");
	create_datfile(temp, 0);
}

void shutdown()
{
	printf("---- Shutdown Finalburn Alpha plus ----\n\n");
	DrvExit();

	BurnLibExit();

	gui_Exit();

	RomLoadExit();
	VideoExit();
	InpExit();

	SystemExit(config_options.option_frontend);
}

long long get_ticks_us()
{
#ifndef WIN32
	long long ticks;
	struct timeval current_time;
	gettimeofday(&current_time, NULL);

	return (long long)current_time.tv_sec * 1000000 + (long long)current_time.tv_usec;
#else
	return SDL_GetTicks() * 1000;
#endif
}

void sleep_us(int value)
{
#ifndef WIN32
	usleep(value);
#else
	SDL_Delay(value / 1000);
#endif
}

struct timeval start;

unsigned int GetTicks (void)
{
	unsigned int ticks;
	struct timeval now;
	gettimeofday(&now, NULL);
	ticks=(now.tv_sec-start.tv_sec)*1000000 + now.tv_usec-start.tv_usec;
	return ticks;
}

void run_fba_emulator(const char *fn)
{
	atexit(shutdown);

	BurnPathsInit();
	gui_Init();

	BurnLibInit();

	ConfigAppLoad();

	// process rom path and name
	printf("about to load rom\n");
	char romname[MAX_PATH];
	char *p;

	strcpy(szAppRomPaths[0], fn);
	p = strrchr(szAppRomPaths[0], '/');
	if (p) {
		p++;
		strcpy(romname, p);

		*p = 0;
		p = strrchr(romname, '.');
		if (p) *p = 0;
		else {
			// error
			goto finish;
		}
	} else {
		// error
		goto finish;
	}

	// find rom by name
	for (nBurnDrvSelect[0]=0; nBurnDrvSelect[0]<nBurnDrvCount; nBurnDrvSelect[0]++)
	{
		nBurnDrvActive=nBurnDrvSelect[0];
		if ( strcasecmp(romname, BurnDrvGetTextA(DRV_NAME)) == 0 )
			break;
	}
	if (nBurnDrvSelect[0] >= nBurnDrvCount)
	{
		// unsupport rom ...
		nBurnDrvSelect[0] = ~0U;
		nBurnDrvActive=nBurnDrvSelect[0];
		printf ("rom not supported!\n");
		goto finish;
	}

	if (config_options.option_create_lists)
	{
		unsigned int tmp=nBurnDrvActive;
		CreateCapexLists();
		nBurnDrvActive=tmp;
	}

	SystemInit();
	VideoInit();
	printf("completed videoinit()\n");

	printf("Attempt to initialise '%s'\n", BurnDrvGetTextA(DRV_FULLNAME));

	RomLoadInit();

	InpInit();
	InpDIP();

	if (DrvInit(nBurnDrvSelect[0], false) != 0)
	{
		printf ("Driver initialisation failed! Likely causes are:\n- Corrupt/Missing ROM(s)\n- I/O Error\n- Memory error\n\n");
		goto finish;
	}

	if (config_options.option_sense<100)
	{
		nAnalogSpeed=0x100/100*config_options.option_sense;
	}

	RunReset();

	frame_count = 0;
	GameLooping = true;

	bShowFPS = config_options.option_showfps;

	if (BurnDrvGetFlags() & BDF_ORIENTATION_FLIPPED) printf("flipped!\n");

	printf ("Let's go!\n");

	VideoClear();

#ifdef FBA_DEBUG
	gui_RunDebug();
#endif

#if 0
	{
		int now, start, lim=0, wait=0, frame_count=0, skipped_frames=0, draw_this_frame=true, fps=0;
		int frame_limit = nBurnFPS/100, frametime = 100000000/nBurnFPS; // 16667 usec
		int skip_limit = 0;

		start = get_ticks_us();
		while (GameLooping)
		{
			RunOneFrame(draw_this_frame, fps);
			SndPlay();

			now = get_ticks_us();
			draw_this_frame = true;
			frame_count++;
			if(now - start >= 1000000) {
				start = now;
				fps = frame_limit - skipped_frames;
				skipped_frames = 0;
				frame_count = 0;
			}

			lim = (frame_count) * frametime;
			if(config_options.option_frameskip == -1) { // auto frameskip
				if(now-start > lim) if(++skipped_frames < frame_limit/2) draw_this_frame = false;
			} else { // manual frameskip 0..10
				if(config_options.option_frameskip > 0) {
					if(skipped_frames < config_options.option_frameskip) { 
						if(--skip_limit < 0) { 
							draw_this_frame = false;
							skip_limit = frame_limit / config_options.option_frameskip;
							skipped_frames++; 
						}
					}
				}
			}

			wait = lim - (now - start);
			if(config_options.option_sound_enable != 2 && wait > 0) sleep_us(wait);

			//printf("%i:, diff: %i, lim: %i, wait: %i\n", frame_count, now-start, lim, wait);
		}
	}
#else
	{
		int now, done=0, timer = 0, ticks=0, tick=0, i=0, fps = 0;
		unsigned int frame_limit = nBurnFPS/100, frametime = 100000000/nBurnFPS;

		gettimeofday(&start, NULL);
		while (GameLooping)
		{
			timer = GetTicks()/frametime;;
			if(timer-tick>frame_limit && bShowFPS)
			{
				fps = nFramesRendered;
				nFramesRendered = 0;
				tick = timer;
			}
			now = timer;
			ticks=now-done;
			if(ticks<1) continue;
			if(ticks>10) ticks=10;
			for (i=0; i<ticks-1; i++)
			{
				RunOneFrame(false,fps);
				SndPlay();
			}
			if(ticks>=1)
			{
				RunOneFrame(true,fps);
				SndPlay();
			}

			done = now;
		}
	}
#endif

	printf ("Finished emulating\n");

finish:
	printf("---- Shutdown Finalburn Alpha plus ----\n\n");
	ConfigAppSave();
}
