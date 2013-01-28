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
	int option_frameskip;
	int option_68kcore;
	int option_z80core;
	int option_sense;
	int option_useswap;
	char option_frontend[MAX_PATH];
	int option_create_lists;
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
	int qsave;
	int qload;
} CFG_KEYMAP;

int ConfigAppLoad();
int ConfigAppSave();

extern CFG_OPTIONS config_options;
extern CFG_KEYMAP config_keymap;

#endif
