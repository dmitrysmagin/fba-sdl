#ifndef _CONFIG_H_
#define _CONFIG_H_

#ifndef MAX_PATH
#define MAX_PATH 511
#endif

typedef struct
{
	int option_sound_enable;
	int option_rescale;
	int option_rotate;
	int option_samplerate;
	int option_showfps;
	int option_forcem68k;
    int option_forcec68k;
    int option_z80core;
    int option_sense;
	char option_frontend[MAX_PATH];
	int option_create_lists;
	char option_startspeed[6];
	char option_selectspeed[6];
} CFG_OPTIONS;

typedef struct
{
	int up;
	int down;
	int left;
	int right;
	int fire1;
	int fire2;
    int fire3;
    int fire4;
    int fire5;
	int fire6;
	int coin1;
	int coin2;
	int start1;
	int start2;
	int pause;
	int quit;
	int fps;

} CFG_KEYMAP;

#endif
