/*
 * FinalBurn Alpha for MOTO EZX Modile Phone
 * Copyright (C) 2006 OopsWare. CHINA.
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
 * $Id: fba_player.cpp,v 0.10 2006/12/03 $
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

#include "version.h"
#include "fba_player.h"
#include "font.h"
#include "snd.h"

#include "burnint.h"
#include "config.h"
#include "cache.h"
#include "pandorasdk.h"

#ifndef DRV_NAME
#define DRV_NAME (0)
#endif

#define _s(A) #A
#define _a(A) _s(A)
#define VERSION _a(VER_MAJOR.VER_MINOR.VER_BETA.VER_ALPHA)

//extern INT32 create_datfile(TCHAR* szFilename, INT32 bType);

extern char szAppRomPaths[20] [20];
char szAppBurnVer[16] = VERSION;

extern int nAnalogSpeed;

void uploadfb(void);

int fwidth = 320, fheight = 240; // text surface

extern unsigned int nFramesRendered;
static int frame_count = 0;
unsigned int FBA_KEYPAD[4];
signed int FBA_AXIS[4] [4];
unsigned char ServiceRequest = 0;
unsigned char P1P2Start = 0;
unsigned short *titlefb;
extern bool bShowFPS;
void ChangeFrameskip();
extern SDL_Joystick *joys[4];
extern char joyCount;

extern CFG_OPTIONS config_options;
extern CFG_KEYMAP config_keymap;
extern volatile short *pOutput[];
extern bool bPauseOn;
int pausecnt=0;

bool GameLooping;

int joyMap[8] = {0x0040,0x0080,0x0100,0x0200,0x0400,0x0800,0x10,0x20};
/*struct keymap_item FBA_KEYMAP[] = {
		{"-----",	0, false },
		{"START",	1, false },
		{"COIN",	2, false },
		{"A",		3, false },
		{"B", 		4, false },
		{"C",		5, false },
		{"D",		6, false },
		{"E",		7, false },
		{"F",		8, false },

		{"A+B",		9, false },
		{"C+D",	   10, false },
		{"A+B+C",  11, false },

		{"A-Turbo",	3, true  },
		{"B-Turbo",	4, true  },
		{"C-Turbo",	5, true  },
		{"D-Turbo",	6, true  },
		{"E-Turbo",	7, true  },
		{"F-Turbo",	8, true  } 	};
*/

void do_keypad()
{
	static unsigned int turbo = 0;
	unsigned long joy = gp2x_joystick_read();
	int bVert = ((BurnDrvGetFlags() & BDF_ORIENTATION_VERTICAL) && (config_options.option_rotate==1));
	//int bVert=config_options.option_rescale<=2;
	turbo ++;

	FBA_KEYPAD[0] = 0;
	FBA_KEYPAD[1] = 0;
	FBA_KEYPAD[2] = 0;
	FBA_KEYPAD[3] = 0;
	ServiceRequest =0;
	P1P2Start = 0;

	/*FBA_AXIS[0] [0]=SDL_JoystickGetAxis(0,0);
	FBA_AXIS[0] [1]=SDL_JoystickGetAxis(0,1);
	FBA_AXIS[0] [2]=SDL_JoystickGetAxis(0,2);
	FBA_AXIS[0] [3]=SDL_JoystickGetAxis(0,3);*/

	if ( joy & MY_UP  ) FBA_KEYPAD[0] |= bVert?0x0004:0x0001;
	if ( joy & MY_DOWN  ) FBA_KEYPAD[0] |= bVert?0x0008:0x0002;
	if ( joy & MY_LEFT  ) FBA_KEYPAD[0] |= bVert?0x0002:0x0004;
	if ( joy & MY_RIGHT ) FBA_KEYPAD[0] |= bVert?0x0001:0x0008;

	if ( joy & MY_SELECT )	FBA_KEYPAD[0] |= 0x0010;
	if ( joy & MY_START )		FBA_KEYPAD[0] |= 0x0020;

	if ( joy & MY_BUTT_A )	FBA_KEYPAD[0] |= 0x0040;	// A
	if ( joy & MY_BUTT_X )  FBA_KEYPAD[0] |= 0x0080;	// B
		//if (bVert)
			//ezx_change_volume(1);
		//else
			//FBA_KEYPAD[0] |= 0x0080;	// B
	if ( joy & MY_BUTT_B )	FBA_KEYPAD[0] |= 0x0100;	// C
	if ( joy & MY_BUTT_Y ) FBA_KEYPAD[0] |= 0x0200;	// D
		//if (bVert)
			//ezx_change_volume(-1);
		//else
//			FBA_KEYPAD[0] |= 0x0200;	// D
	if ( joy & MY_BUTT_SL )	FBA_KEYPAD[0] |= 0x0400;						// E
		//if (bVert)
			//FBA_KEYPAD[0] |= 0x0100;
		//else
		//	FBA_KEYPAD[0] |= 0x0400;
	if ( joy & MY_BUTT_SR )	FBA_KEYPAD[0] |= 0x0800;						// F
		//if (bVert)
			//FBA_KEYPAD[0] |= 0x0200;
		//else
			//FBA_KEYPAD[0] |= 0x0800;
	/*if ( joy & MY_VOL_UP )
		if (bVert)
			FBA_KEYPAD[0] |= 0x0040;
		else
			ezx_change_volume(1);
	if ( joy & MY_VOL_DOWN )
		if (bVert)
			FBA_KEYPAD[0] |= 0x0080;
		else
			ezx_change_volume(-1);*/
	if (joy & MY_QT) GameLooping=false;
	if (pausecnt>0) pausecnt--;
	if ((joy & MY_PAUSE) && (pausecnt==0))
	{
		bPauseOn=!bPauseOn;
		pausecnt=20;
		if (config_options.option_sound_enable == 2) SDL_PauseAudio(bPauseOn);
	}
	//if (joy & MY_KS) ServiceRequest=1:
	/*if ((joy & MY_BUTT_SL) && (joy & MY_BUTT_SR))
	{
		if (joy & MY_BUTT_Y) ChangeFrameskip();
		else
		if (joy & MY_START) GameLooping = false;
		else
		if ( joy & MY_SELECT) ServiceRequest = 1;
		else
		if ( joy & MY_BUTT_X)
		{
			FILE * filterfile;
			filterfile=fopen("/etc/pandora/conf/dss_fir/none_up","r");
			if (filterfile)
			{
				int i;
				char f [161];
				int tmp;
				fgets(f,160,filterfile);
				fgets(f,160,filterfile);
				fread(f,20,8,filterfile);
				f[160]=0;
				tmp = open("/sys/devices/platform/omapdss/overlay1/filter_coef_up_h", O_WRONLY);
				if (tmp) printf("success %d\n",strlen(f)); else printf("failed\n");
				printf("%d\n",write (tmp,f,strlen(f)+1));
				close(tmp);
				fgets(f,160,filterfile);
				fread(f,20,8,filterfile);
				f[160]=0;
				tmp = open("/sys/devices/platform/omapdss/overlay1/filter_coef_up_v3", O_WRONLY);
				write (tmp,f,strlen(f)+1);
				close(tmp);
				fgets(f,160,filterfile);
				fread(f,20,8,filterfile);
				f[160]=0;
				tmp = open("/sys/devices/platform/omapdss/overlay1/filter_coef_up_v5", O_WRONLY);
				write (tmp,f,strlen(f)+1);
				close(tmp);
				//printf(f);

				fclose(filterfile);


			}
		}
	}
	else
		if (joy & MY_START && joy & MY_SELECT) P1P2Start = 1;*/

/*	for (int i=0;i<joyCount;i++)
	{
	int numButtons = joy_buttons(joys[i]);
		if (numButtons > 8)
			numButtons = 8;
		joy_update(joys[i]);
		if(joy_getaxe(JOYUP, joys[i])) FBA_KEYPAD[i] |= bVert?0x0004:0x0001;
		if(joy_getaxe(JOYDOWN, joys[i])) FBA_KEYPAD[i] |= bVert?0x0008:0x0002;
		if(joy_getaxe(JOYLEFT, joys[i])) FBA_KEYPAD[i] |= bVert?0x0002:0x0004;
		if(joy_getaxe(JOYRIGHT, joys[i])) FBA_KEYPAD[i] |= bVert?0x0001:0x0008;

		for (int nButton = 0; nButton < numButtons; nButton++) {
			if(joy_getbutton(nButton, joys[i]))
				FBA_KEYPAD[i] |= joyMap[nButton];
		}
	}*/
}

int DrvInit(int nDrvNum, bool bRestore);
int DrvExit();

int RunReset();
int RunOneFrame(bool bDraw, int fps);

int VideoInit();
void VideoExit();

int InpInit();
int InpExit();
void InpDIP();

extern int nBurnFPS;
int fps=0;

void show_rom_loading_text(char * szText, int nSize, int nTotalSize)
{
	int doffset=20;
	/*if (config_options.option_rescale>=3)
	{
		pwidth=240;
		doffset=0;
	}*/
	static long long size = 0;
	//printf("!!! %s, %d / %d\n", szText, size + nSize, nTotalSize);

	DrawRect((uint16 *) titlefb, doffset, 120, 300, 20, 0, fwidth);

	if (szText)
		DrawString (szText, (uint16 *) titlefb, doffset, 120, fwidth);

	if (nTotalSize == 0) {
		size = 0;
		DrawRect((uint16 *) titlefb, doffset, 140, 280, 12, 0x00FFFFFF, fwidth);
		DrawRect((uint16 *) titlefb, doffset+1, 141, 278, 10, 0x00808080, fwidth);
	} else {
		size += nSize;
		if (size > nTotalSize) size = nTotalSize;
		DrawRect((uint16 *) titlefb, doffset+1, 141, size * 278 / nTotalSize, 10, 0x00FFFF00, fwidth);
	}

	//if (config_options.option_rescale<3) memcpy (VideoBuffer, titlefb, fwidth*fheight*2); else memcpy (VideoBuffer, titlefb, pwidth*fwidth*2);
	memcpy (VideoBuffer,titlefb, 320*240*2 /*fwidth*fheight*2*/);
	gp2x_video_flip();

}

void show_rom_error_text(char * szText)
{

	int doffset=20;

	static long long size = 0;
	//printf("!!! %s, %d / %d\n", szText, size + nSize, nTotalSize);

	DrawRect((uint16 *) titlefb, doffset, 120, 300, 20, 0, fwidth);

	DrawString ("Error loading rom:", (uint16 *) titlefb, doffset, 160, fwidth);
	if (szText)
		DrawString (szText, (uint16 *) titlefb, doffset, 180, fwidth);
	DrawString ("Exiting - press any key", (uint16 *) titlefb, doffset, 200, fwidth);


	memcpy (VideoBuffer, titlefb, 320*240*2/*fwidth*fheight*2*/);
	gp2x_video_flip();
	SDL_Event event;
	while (event.type!=SDL_KEYDOWN)
		SDL_WaitEvent(&event);

}

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
	/*char temp[24];
	strcpy(temp,"FBA ");
	strcat(temp,szAppBurnVer);
	strcat(temp,".dat");
	create_datfile(temp, 0);*/

}

void shutdown()
{
	printf("---- Shutdown Finalburn Alpha plus ----\n\n");
	DrvExit();

	BurnLibExit();

	if (config_options.option_sound_enable)
		SndExit();

	VideoExit();
	InpExit();

	BurnCacheExit();
	gp2x_terminate(config_options.option_frontend);
}


void load_keymap(char * nm)
{
	FILE * f;
	char arg1[128];
	signed long argd;
	char line[256];
	char fullpath[256];
	strcpy(fullpath,"./config/");
	strcat(fullpath,nm);
	strcat(fullpath,".kmp");
	if ((f = fopen(fullpath,"r")) == NULL) f = fopen("./config/default.kmp", "r");
	if (f==NULL) return;

			while(fgets(line,sizeof(line),f) != NULL){

			sscanf(line, "%s %d", &arg1,&argd);
			if (argd>0)
			{
				if (strcmp(arg1,"#")!=0) {
					if (strcmp(arg1,"KEY_UP")==0) config_keymap.up  = argd;
					if (strcmp(arg1,"KEY_DOWN")==0) config_keymap.down  = argd;
					if (strcmp(arg1,"KEY_LEFT")==0) config_keymap.left  = argd;
					if (strcmp(arg1,"KEY_RIGHT")==0) config_keymap.right  = argd;
					if (strcmp(arg1,"KEY_FIRE1")==0) config_keymap.fire1  = argd;
					if (strcmp(arg1,"KEY_FIRE2")==0) config_keymap.fire2  = argd;
					if (strcmp(arg1,"KEY_FIRE3")==0) config_keymap.fire3  = argd;
					if (strcmp(arg1,"KEY_FIRE4")==0) config_keymap.fire4  = argd;
					if (strcmp(arg1,"KEY_FIRE5")==0) config_keymap.fire5  = argd;
					if (strcmp(arg1,"KEY_FIRE6")==0) config_keymap.fire6  = argd;
					if (strcmp(arg1,"KEY_COIN1")==0) config_keymap.coin1  = argd;
					if (strcmp(arg1,"KEY_START1")==0) config_keymap.start1  = argd;
					if (strcmp(arg1,"KEY_PAUSE")==0) config_keymap.pause  = argd;
					if (strcmp(arg1,"KEY_QUIT")==0) config_keymap.quit  = argd;

				}
			}
		}
		fclose(f);


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

void run_fba_emulator(const char *fn)
{
	atexit(shutdown);
	int pwidth=fwidth;
	int doffset=20;
	if (config_options.option_rescale>=3)
	{
		pwidth=240;
		doffset=0;
	}

	printf("about to burnlibinit()\n");
	BurnLibInit();
	printf("completed burnlibinit()\n");

	ConfigAppLoad();

	// process rom path and name
	printf("about to load rom\n");
	char romname[MAX_PATH];
	char *p;
	if (BurnCacheInit(fn, romname))
		goto finish;

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

	load_keymap(BurnDrvGetTextA(DRV_NAME));
	gp2x_initialize();

	titlefb=(unsigned short*)malloc(fwidth * fheight*2);

	printf("Attempt to initialise '%s'\n", BurnDrvGetTextA(DRV_FULLNAME));

	memset (titlefb, 0, 320*240*2/*fwidth*fheight*2*/);
	DrawString ("Finalburn Alpha for OpenDingux (v " VERSION ")", titlefb, 10, 20, fwidth);
	DrawString ("Based on FinalBurnAlpha", titlefb, 10, 35, fwidth);
	DrawString ("Now loading ... ", titlefb, 10, 105, fwidth);
	show_rom_loading_text("Open Zip", 0, 0);
	memcpy (VideoBuffer, titlefb, 320*240*2 /*fwidth*fheight*2*/);
	gp2x_video_flip();

	InpInit();
	InpDIP();

	VideoInit();
	printf("completed videoinit()\n");

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

	gp2x_clear_framebuffers();

	if(SndOpen()) config_options.option_sound_enable = 0; // disable sound if error

	{
		int now, start, lim=0, wait=0, frame_count=0, skipped_frames=0, draw_this_frame=true, fps=0;
		int frame_limit = nBurnFPS/100, frametime = 100000000/nBurnFPS; // 16667 usec
		int skip_limit = 0;

		start = get_ticks_us();
		while (GameLooping)
		{
			RunOneFrame(draw_this_frame, fps);
			SndFrameRendered();

			now = get_ticks_us();
			draw_this_frame = true;
			frame_count++;
			if(now - start >= 1000000) {
				start = now;
				fps = frame_limit - skipped_frames;
				skipped_frames = 0;
				frame_count = 0;
				continue;
			}

			lim = (frame_count) * frametime;
			if(config_options.option_frameskip == -1) { // auto frameskip
				if(now-start > lim) if(++skipped_frames < frame_limit) draw_this_frame = false;
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

			//printf("diff: %i, lim: %i, wait: %i, skipped: %i\n", now-start, lim, wait, skipped_frames);
		}
	}

	printf ("Finished emulating\n");

finish:
	printf("---- Shutdown Finalburn Alpha plus ----\n\n");
	ConfigAppSave();
}

int BurnStateLoad(const char * szName, int bAll, int (*pLoadGame)());
int BurnStateSave(const char * szName, int bAll);



