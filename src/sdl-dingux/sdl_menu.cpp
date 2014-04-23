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
#include <string.h>
#include <sys/time.h>
#include <SDL/SDL.h>

#include "version.h"
#include "burner.h"
#include "snd.h"
#include "sdl_run.h"
#include "sdl_video.h"
#include "sdl_input.h"

#ifdef FBA_DEBUG
#include "m68000_intf.h"
#include "m68000_debug.h"
#include "m68k.h"
#endif

#define _s(A) #A
#define _a(A) _s(A)
#define VERSION _a(VER_MAJOR.VER_MINOR.VER_BETA.VER_ALPHA)

#define color16(red, green, blue) ((red << 11) | (green << 5) | blue)

#define COLOR_BG            color16(05, 03, 02)
#define COLOR_ROM_INFO      color16(22, 36, 26)
#define COLOR_ACTIVE_ITEM   color16(31, 63, 31)
#define COLOR_INACTIVE_ITEM color16(13, 40, 18)
#define COLOR_FRAMESKIP_BAR color16(15, 31, 31)
#define COLOR_HELP_TEXT     color16(16, 40, 24)

/* SDL declarations */
extern SDL_Surface *screen;
SDL_Surface *menuSurface = NULL; // menu rendering

/* type definitions */
typedef struct {
	char *itemName;       // item name
	int *itemPar;         // item parameter
	int itemParMaxValue;  // item max parameter value
	char **itemParName;   // item parameter name
	void (*itemOnA)();    // item action on A press
} MENUITEM;

typedef struct {
	int itemNum; // number of items
	int itemCur; // current item
	MENUITEM *m; // array of items
} MENU;

/* prototypes */
static void gui_Stub() { }
static void gui_LoadState() { extern int done; if(!StatedLoad(nSavestateSlot)) done = 1; }
static void gui_Savestate() { StatedSave(nSavestateSlot); }
static void call_exit() { extern int done; GameLooping = false; done = 1; }
static void call_continue() { extern int done; done = 1; }
static void gui_KeyMenuRun();
static void gui_AutofireMenuRun();
static void gui_help();
static void gui_reset();

/* data definitions */
#define GCW0_KEY_ORDER
#ifdef GCW0_KEY_ORDER
char *gui_KeyNames[] = {"A", "B", "Y", "X", "L", "R"};
#else
char *gui_KeyNames[] = {"A", "B", "X", "Y", "L", "R"};
#endif
int gui_KeyData[] = {0, 1, 2, 3, 4, 5};
int gui_KeyValue[] = {SDLK_LCTRL, SDLK_LALT, SDLK_SPACE, SDLK_LSHIFT, SDLK_TAB, SDLK_BACKSPACE};
char *gui_SoundDrvNames[] = {"No sound", "LIBAO", "SDL mutex", "SDL"};
char *gui_SoundSampleRates[] = {"11025", "16000", "22050", "32000", "44100"};
char *gui_AutofireFpsNames[] = {"off", "6 fps", "10 fps", "16 fps", "30 fps"};
int gui_AutofireFpsData[] = {0, 0, 0, 0, 0, 0};
int gui_AutofireFpsValue[] = {0, 6, 10, 16, 30};

MENUITEM gui_MainMenuItems[] = {
	{(char *)"Continue", NULL, 0, NULL, &call_continue},
	{(char *)"Key config", NULL, 0, NULL, &gui_KeyMenuRun},
	{(char *)"Autofire config", NULL, 0, NULL, &gui_AutofireMenuRun},
	{(char *)"Load state: ", &nSavestateSlot, 9, NULL, &gui_LoadState},
	{(char *)"Save state: ", &nSavestateSlot, 9, NULL, &gui_Savestate},
	{(char *)"Help", NULL, 0, NULL, &gui_help},
	{(char *)"Reset", NULL, 0, NULL, &gui_reset},
	{(char *)"Exit", NULL, 0, NULL, &call_exit},
	{NULL, NULL, 0, NULL, NULL}
};

MENU gui_MainMenu = { 8, 0, (MENUITEM *)&gui_MainMenuItems };

MENUITEM gui_KeyMenuItems[] = {
	{(char *)"Fire 1   - ", &gui_KeyData[0], 5, (char **)&gui_KeyNames, NULL},
	{(char *)"Fire 2   - ", &gui_KeyData[1], 5, (char **)&gui_KeyNames, NULL},
	{(char *)"Fire 3   - ", &gui_KeyData[2], 5, (char **)&gui_KeyNames, NULL},
	{(char *)"Fire 4   - ", &gui_KeyData[3], 5, (char **)&gui_KeyNames, NULL},
	{(char *)"Fire 5   - ", &gui_KeyData[4], 5, (char **)&gui_KeyNames, NULL},
	{(char *)"Fire 6   - ", &gui_KeyData[5], 5, (char **)&gui_KeyNames, NULL},
	{NULL, NULL, 0, NULL, NULL}
};

MENU gui_KeyMenu = { 6, 0, (MENUITEM *)&gui_KeyMenuItems };

MENUITEM gui_AutofireMenuItems[] = {
	{(char *)"Autofire 1 fps - ", &gui_AutofireFpsData[0], 4, (char **)&gui_AutofireFpsNames, NULL},
	{(char *)"Autofire 1 key - ", &gui_KeyData[0], 5, (char **)&gui_KeyNames, NULL},
	{(char *)"Autofire 2 fps - ", &gui_AutofireFpsData[1], 5, (char **)&gui_AutofireFpsNames, NULL},
	{(char *)"Autofire 2 key - ", &gui_KeyData[1], 5, (char **)&gui_KeyNames, NULL},
	{(char *)"Autofire 3 fps - ", &gui_AutofireFpsData[2], 4, (char **)&gui_AutofireFpsNames, NULL},
	{(char *)"Autofire 3 key - ", &gui_KeyData[2], 5, (char **)&gui_KeyNames, NULL},
	{(char *)"Autofire 4 fps - ", &gui_AutofireFpsData[3], 4, (char **)&gui_AutofireFpsNames, NULL},
	{(char *)"Autofire 4 key - ", &gui_KeyData[3], 5, (char **)&gui_KeyNames, NULL},
	{(char *)"Autofire 5 fps - ", &gui_AutofireFpsData[4], 4, (char **)&gui_AutofireFpsNames, NULL},
	{(char *)"Autofire 5 key - ", &gui_KeyData[4], 5, (char **)&gui_KeyNames, NULL},
	{(char *)"Autofire 6 fps - ", &gui_AutofireFpsData[5], 4, (char **)&gui_AutofireFpsNames, NULL},
	{(char *)"Autofire 6 key - ", &gui_KeyData[5], 5, (char **)&gui_KeyNames, NULL},
	{NULL, NULL, 0, NULL, NULL}
};

MENU gui_AutofireMenu = { 12, 0, (MENUITEM *)&gui_AutofireMenuItems };

int done = 0; // flag to indicate exit status
extern unsigned char gui_font[2048];


#ifdef FBA_DEBUG
int debug = 0;
#endif

/* local functions */

void gui_Flip()
{
	SDL_Rect dstrect;

	dstrect.x = (screen->w - 320) / 2;
	dstrect.y = (screen->h - 240) / 2;

	SDL_BlitSurface(menuSurface, 0, screen, &dstrect);
	SDL_Flip(screen);
}

/*
	Prints char on a menu surface
*/
void DrawChar(SDL_Surface *s, int x, int y, unsigned char a, int fg_color, int bg_color)
{
	Uint16 *dst;
	int w, h;

	if(SDL_MUSTLOCK(s)) SDL_LockSurface(s);
	for(h = 8; h; h--) {
		dst = (Uint16 *)s->pixels + (y+8-h)*s->w + x;
		for(w = 8; w; w--) {
			Uint16 color = bg_color; // background
			if((gui_font[a*8 + (8-h)] >> w) & 1) color = fg_color; // test bits 876543210
			*dst++ = color;
		}
	}
	if(SDL_MUSTLOCK(s)) SDL_UnlockSurface(s);
}

/*
	Draws a string on a menu surface
*/
void DrawString(const char *s, unsigned short fg_color, unsigned short bg_color, int x, int y)
{
	int i, j = strlen(s);
	for(i = 0; i < j; i++, x += 8) DrawChar(menuSurface, x, y, s[i], fg_color, bg_color);
}

void ShowMenuItem(int x, int y, MENUITEM *m, int fg_color)
{
	static char i_str[24];

	// if no parameters, show simple menu item
	if(m->itemPar == NULL) DrawString(m->itemName, fg_color, COLOR_BG, x, y);
	else {
		if(m->itemParName == NULL) {
			// if parameter is a digit
			sprintf(i_str, "%s%i", m->itemName, *m->itemPar);
		} else {
			// if parameter is a name in array
			sprintf(i_str, "%s%s", m->itemName, *(m->itemParName + *m->itemPar));
		}
		DrawString(i_str, fg_color, COLOR_BG, x, y);
	}
}

void ShowHeader()
{
	DrawString("Press B to return to game", COLOR_HELP_TEXT, COLOR_BG, 56, 220);
	DrawString("FinalBurn Alpha for OpenDingux", COLOR_HELP_TEXT, COLOR_BG, 44, 2);
	DrawString("Based on FBA " VERSION " (c) Team FB Alpha", COLOR_HELP_TEXT, COLOR_BG, 0, 12);
}

/*
	Shows menu items and pointing arrow
*/
void ShowMenu(MENU *menu)
{
	int i;
	MENUITEM *mi = menu->m;

	// clear buffer
	SDL_FillRect(menuSurface, NULL, COLOR_BG);

	// show menu lines
	int startline = menu == &gui_AutofireMenu ? 12 : 16;
	for(i = 0; i < menu->itemNum; i++, mi++) {
		int fg_color;

		if(menu->itemCur == i) fg_color = COLOR_ACTIVE_ITEM; else fg_color = COLOR_INACTIVE_ITEM;
		ShowMenuItem(80, (startline + i) * 8, mi, fg_color);
	}

	// show preview screen
	//ShowPreview(menu);

	// print info string
	ShowHeader();
}

/*
	Main function that runs all the stuff
*/
void gui_MenuRun(MENU *menu)
{
	SDL_Event gui_event;
	MENUITEM *mi;

	done = 0;

	while(!done) {
		mi = menu->m + menu->itemCur; // pointer to highlit menu option

		while(SDL_PollEvent(&gui_event)) {
			if(gui_event.type == SDL_KEYDOWN) {
				// DINGOO A - apply parameter or enter submenu
				if(gui_event.key.keysym.sym == SDLK_LCTRL) if(mi->itemOnA != NULL) (*mi->itemOnA)();
				// DINGOO B - exit or back to previous menu
				if(gui_event.key.keysym.sym == SDLK_LALT) return;
				// DINGOO UP - arrow down
				if(gui_event.key.keysym.sym == SDLK_UP) if(--menu->itemCur < 0) menu->itemCur = menu->itemNum - 1;
				// DINGOO DOWN - arrow up
				if(gui_event.key.keysym.sym == SDLK_DOWN) if(++menu->itemCur == menu->itemNum) menu->itemCur = 0;
				// DINGOO LEFT - decrease parameter value
				if(gui_event.key.keysym.sym == SDLK_LEFT) {
					if(mi->itemPar != NULL && *mi->itemPar > 0) *mi->itemPar -= 1;
				}
				// DINGOO RIGHT - increase parameter value
				if(gui_event.key.keysym.sym == SDLK_RIGHT) {
					if(mi->itemPar != NULL && *mi->itemPar < mi->itemParMaxValue) *mi->itemPar += 1;
				}
			}
		}
		if(!done) ShowMenu(menu); // show menu items
		SDL_Delay(16);
		gui_Flip();
	}
}

static void gui_KeyMenuRun()
{
	// key decode
	int *key = &keymap.fire1;
	for(int i = 0; i < 6; key++, i++)
		for(int j = 0; j < 6; j++) if(gui_KeyValue[j] == *key) gui_KeyData[i] = j;

	gui_MenuRun(&gui_KeyMenu);

	// key encode
	key = &keymap.fire1;
	for(int i = 0; i < 6; key++, i++)
		*key = gui_KeyValue[gui_KeyData[i]];
}

static void gui_AutofireMenuRun()
{
	// key decode
	CFG_AUTOFIRE_KEY *af = &autofire.fire1;
	for(int i = 0; i < 6; af++, i++) {
		for(int j = 0; j < 5; j++) if(gui_AutofireFpsValue[j] == af->fps) gui_AutofireFpsData[i] = j;
		for(int j = 0; j < 6; j++) if(gui_KeyValue[j] == af->key) gui_KeyData[i] = j;
	}

	gui_MenuRun(&gui_AutofireMenu);

	// key encode
	af = &autofire.fire1;
	for(int i = 0; i < 6; af++, i++) {
		af->fps = gui_AutofireFpsValue[gui_AutofireFpsData[i]];
		af->key = gui_KeyValue[gui_KeyData[i]];
	}
	sdl_autofire_init();
}

static void gui_help()
{
	int x = 60;
	int row = 12;
	int row_size = 8;
	SDL_FillRect(menuSurface, NULL, COLOR_BG);

	DrawString("D-PAD        Movement", COLOR_INACTIVE_ITEM, COLOR_BG, x, row++ * row_size);
	DrawString("SELECT       Coin", COLOR_INACTIVE_ITEM, COLOR_BG, x, row++ * row_size);
	DrawString("START        Start1", COLOR_INACTIVE_ITEM, COLOR_BG, x, row++ * row_size);
	DrawString("SELECT+START Start2", COLOR_INACTIVE_ITEM, COLOR_BG, x, row++ * row_size);
	DrawString("A,B,X,Y,L,R  Fire buttons", COLOR_INACTIVE_ITEM, COLOR_BG, x, row++ * row_size);
	DrawString("L+R+X        Show/hide fps", COLOR_INACTIVE_ITEM, COLOR_BG, x, (++row)++ * row_size);
	DrawString("L+R+A        Quick load", COLOR_INACTIVE_ITEM, COLOR_BG, x, row++ * row_size);
	DrawString("L+R+B        Quick save", COLOR_INACTIVE_ITEM, COLOR_BG, x, row++ * row_size);
	DrawString("L+R+SELECT   Service menu", COLOR_INACTIVE_ITEM, COLOR_BG, x, row++ * row_size);
	DrawString("L+R+START    FBA SDL menu", COLOR_INACTIVE_ITEM, COLOR_BG, x, row++ * row_size);

	ShowHeader();
	gui_Flip();

	SDL_Event gui_event;
	done = 0;

	while(!done) {
		while(SDL_PollEvent(&gui_event)) {
			if(gui_event.type == SDL_KEYDOWN) {
				// DINGOO B - exit or back to previous menu
				if(gui_event.key.keysym.sym == SDLK_LALT) return;
			}
		}
		SDL_Delay(16);
	}

}

static void gui_reset()
{
	DrvInitCallback();
	done = 1;
}

/* exported functions */ 

void gui_Init()
{
	menuSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, 320, 240, 16, 0, 0, 0, 0);
}

void gui_Run()
{
	struct timeval s, e;
	extern struct timeval start;

#ifdef FBA_DEBUG
	debug = 1;
#endif
	gettimeofday(&s, NULL);

	VideoClear();
	SDL_EnableKeyRepeat(/*SDL_DEFAULT_REPEAT_DELAY*/ 150, /*SDL_DEFAULT_REPEAT_INTERVAL*/30);
	gui_MainMenu.itemCur = 0;
	gui_MenuRun(&gui_MainMenu);
	SDL_EnableKeyRepeat(0, 0);
	ConfigGameSave();
	VideoClear();

	gettimeofday(&e, NULL);
	start.tv_sec += e.tv_sec - s.tv_sec;
	start.tv_usec += e.tv_usec - s.tv_usec;
}

void gui_Exit()
{
	if(menuSurface) SDL_FreeSurface(menuSurface);
}

#ifdef FBA_DEBUG

void show_disasm(int pc)
{
	int i, pcd;
	char opcode[512];
	char text[512];

	for(i = 0; i < 8; i++) {
		pcd = m68k_disassemble(opcode, pc, M68K_CPU_TYPE_68000);
		sprintf(text, "%08x: %s", pc, opcode);
		DrawString(text, COLOR_HELP_TEXT, COLOR_BG, 0, 14*8 + i*8);
		if(i == 0) {
			int j;
			strcpy(text, "opcode: ");
			for(j = 0; j < pcd; j++) {
				sprintf(opcode, " %02x", SekFetchByte(pc + j));
				strcat(text, opcode);
				//sprintf(text, "opcode: %02x %02x %02x %02x", SekFetchByte(pc), SekFetchByte(pc+1), SekFetchByte(pc+2), SekFetchByte(pc+3));
			}
			DrawString(text, COLOR_HELP_TEXT, COLOR_BG, 0, 24*8);
		}
		pc += pcd;
	}

	sprintf(text, "CPU: %i", nSekActive);
	DrawString(text, COLOR_HELP_TEXT, COLOR_BG, 0, 26*8);
}

void show_regs()
{
	char *regname[18] = {
		"D0", "D1", "D2", "D3", "D4", "D5", "D6", "D7", 
		"A0", "A1", "A2", "A3", "A4", "A5", "A6", "A7",
		"PC", "SR"
	};
	char text[512];
	int i;
	char flags[] = "- - - - -";
	int ccr;

	for(int i = 0; i < 8; i++) {
		sprintf(text, "%s=%08X", regname[i], SekDbgGetRegister((SekRegister)i));
		DrawString(text, COLOR_HELP_TEXT, COLOR_BG, 0, i*8);
	}

	for(int i = 8; i < 18; i++) {
		sprintf(text, "%s=%08X", regname[i], SekDbgGetRegister((SekRegister)i));
		DrawString(text, COLOR_HELP_TEXT, COLOR_BG, 16*8, (i-8)*8);
	}

	ccr = SekDbgGetRegister(SEK_REG_CCR);
	flags[4*2] = (ccr & (1 << 0) ? '*' : '-');
	flags[3*2] = (ccr & (1 << 1) ? '*' : '-');
	flags[2*2] = (ccr & (1 << 2) ? '*' : '-');
	flags[1*2] = (ccr & (1 << 3) ? '*' : '-');
	flags[0*2] = (ccr & (1 << 4) ? '*' : '-');

	DrawString("X N Z V C", COLOR_HELP_TEXT, COLOR_BG, 1*8, 10*8);
	DrawString(flags, COLOR_HELP_TEXT, COLOR_BG, 1*8, 11*8);

	sprintf(text, "FLAGS: %08x", ccr);
	DrawString(text, COLOR_HELP_TEXT, COLOR_BG, 0, 27*8);
}

FILE *f;

void dump(int pc)
{
	char *regname[18] = {
		"D0", "D1", "D2", "D3", "D4", "D5", "D6", "D7", 
		"A0", "A1", "A2", "A3", "A4", "A5", "A6", "A7",
		"PC", "SR"
	};
	char flagshi[] = "XNZVC";
	char flagslo[] = "xnzvc";
	char text[1024];
	char output[4096];
	int i;

	memset(text, 0, 1024);
	memset(output, 0, 4096);
	m68k_disassemble(text, pc, M68K_CPU_TYPE_68000);
	sprintf(output, "%08x: %02x %02x %s \t\t\t ", pc, SekFetchByte(pc), SekFetchByte(pc+1), text);


	for(int i = 0; i < 16; i++) {
		sprintf(text, "%s=%08X ", regname[i], SekDbgGetRegister((SekRegister)i));
		strcat(output, text);
	}

	/*strcat(output, "FLAGS: ");
	strcpy(text, "xnzvc");
	{
		int ccr = SekDbgGetRegister(SEK_REG_CCR);

		if(ccr & (1 << 4)) text[0] = 'X';
		if(ccr & (1 << 3)) text[1] = 'N';
		if(ccr & (1 << 2)) text[2] = 'Z';
		if(ccr & (1 << 1)) text[3] = 'V';
		if(ccr & (1 << 0)) text[4] = 'C';
	}
	strcat(output, text);*/

	fprintf(f, "%s\n", output);
}

void dbg_handler(unsigned int pc, int id)
{

	static int skip = 0;
	static int count = 2000000;
	char text[256];
	SDL_Event gui_event;


	if(skip > 0) {
		skip--;
		return;
	}

#if 0
	if(pc == 0x1a00 && SekFetchWord(pc) == 0x48e7)
		debug = 1;
	if(debug)
		if(--count > 0) dump(pc);

#else
	/*if(pc == 0x1a00 && SekFetchWord(pc) == 0x48e7)
		debug = 1;*/

	if(debug) {
		SDL_FillRect(menuSurface, NULL, 0);
		show_disasm(pc);
		show_regs();
		gui_Flip();

		while(1) {
			while(SDL_PollEvent(&gui_event)) {
				if(gui_event.type == SDL_KEYDOWN) {
					if(gui_event.key.keysym.sym == SDLK_ESCAPE) {
						fclose(f);
						call_exit();
						debug = 0;
						return;
					}

					if(gui_event.key.keysym.sym == SDLK_LCTRL)
						return;

					if(gui_event.key.keysym.sym == SDLK_LALT) {
						skip = 0x100;
						return;
					}

					if(gui_event.key.keysym.sym == SDLK_SPACE) {
						skip = 0x1000;
						return;
					}

					if(gui_event.key.keysym.sym == SDLK_LSHIFT) {
						debug = 0;
						//SekDbgBreakpointHandlerFetch = NULL;
						return;
					}
				}
			}

			SDL_Delay(16);
		}
	}
#endif
}

void gui_RunDebug()
{
	printf("Enter DEBUG\n");

	SekDbgEnableSingleStep();
	SekDbgBreakpointHandlerFetch = &dbg_handler;

	//f = fopen("./1.log", "w");
}
#endif

//
// Font: THIN8X8.pf
// Exported from PixelFontEdit 2.7.0

unsigned char gui_font[2048] =
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 000 (.)
	0x7E, 0x81, 0xA5, 0x81, 0xBD, 0x99, 0x81, 0x7E,	// Char 001 (.)
	0x7E, 0xFF, 0xDB, 0xFF, 0xC3, 0xE7, 0xFF, 0x7E,	// Char 002 (.)
	0x6C, 0xFE, 0xFE, 0xFE, 0x7C, 0x38, 0x10, 0x00,	// Char 003 (.)
	0x10, 0x38, 0x7C, 0xFE, 0x7C, 0x38, 0x10, 0x00,	// Char 004 (.)
	0x38, 0x7C, 0x38, 0xFE, 0xFE, 0x7C, 0x38, 0x7C,	// Char 005 (.)
	0x10, 0x10, 0x38, 0x7C, 0xFE, 0x7C, 0x38, 0x7C,	// Char 006 (.)
	0x00, 0x00, 0x18, 0x3C, 0x3C, 0x18, 0x00, 0x00,	// Char 007 (.)
	0xFF, 0xFF, 0xE7, 0xC3, 0xC3, 0xE7, 0xFF, 0xFF,	// Char 008 (.)
	0x00, 0x3C, 0x66, 0x42, 0x42, 0x66, 0x3C, 0x00,	// Char 009 (.)
	0xFF, 0xC3, 0x99, 0xBD, 0xBD, 0x99, 0xC3, 0xFF,	// Char 010 (.)
	0x0F, 0x07, 0x0F, 0x7D, 0xCC, 0xCC, 0xCC, 0x78,	// Char 011 (.)
	0x3C, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x7E, 0x18,	// Char 012 (.)
	0x3F, 0x33, 0x3F, 0x30, 0x30, 0x70, 0xF0, 0xE0,	// Char 013 (.)
	0x7F, 0x63, 0x7F, 0x63, 0x63, 0x67, 0xE6, 0xC0,	// Char 014 (.)
	0x99, 0x5A, 0x3C, 0xE7, 0xE7, 0x3C, 0x5A, 0x99,	// Char 015 (.)
	0x80, 0xE0, 0xF8, 0xFE, 0xF8, 0xE0, 0x80, 0x00,	// Char 016 (.)
	0x02, 0x0E, 0x3E, 0xFE, 0x3E, 0x0E, 0x02, 0x00,	// Char 017 (.)
	0x18, 0x3C, 0x7E, 0x18, 0x18, 0x7E, 0x3C, 0x18,	// Char 018 (.)
	0x66, 0x66, 0x66, 0x66, 0x66, 0x00, 0x66, 0x00,	// Char 019 (.)
	0x7F, 0xDB, 0xDB, 0x7B, 0x1B, 0x1B, 0x1B, 0x00,	// Char 020 (.)
	0x3E, 0x63, 0x38, 0x6C, 0x6C, 0x38, 0xCC, 0x78,	// Char 021 (.)
	0x00, 0x00, 0x00, 0x00, 0x7E, 0x7E, 0x7E, 0x00,	// Char 022 (.)
	0x18, 0x3C, 0x7E, 0x18, 0x7E, 0x3C, 0x18, 0xFF,	// Char 023 (.)
	0x18, 0x3C, 0x7E, 0x18, 0x18, 0x18, 0x18, 0x00,	// Char 024 (.)
	0x18, 0x18, 0x18, 0x18, 0x7E, 0x3C, 0x18, 0x00,	// Char 025 (.)
	0x00, 0x18, 0x0C, 0xFE, 0x0C, 0x18, 0x00, 0x00,	// Char 026 (.) right arrow
	0x00, 0x30, 0x60, 0xFE, 0x60, 0x30, 0x00, 0x00,	// Char 027 (.)
	0x00, 0x00, 0xC0, 0xC0, 0xC0, 0xFE, 0x00, 0x00,	// Char 028 (.)
	0x00, 0x24, 0x66, 0xFF, 0x66, 0x24, 0x00, 0x00,	// Char 029 (.)
	0x00, 0x18, 0x3C, 0x7E, 0xFF, 0xFF, 0x00, 0x00,	// Char 030 (.)
	0x00, 0xFF, 0xFF, 0x7E, 0x3C, 0x18, 0x00, 0x00,	// Char 031 (.)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 032 ( )
	0x40, 0x40, 0x40, 0x40, 0x40, 0x00, 0x40, 0x00,	// Char 033 (!)
	0x90, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 034 (")
	0x50, 0x50, 0xF8, 0x50, 0xF8, 0x50, 0x50, 0x00,	// Char 035 (#)
	0x20, 0x78, 0xA0, 0x70, 0x28, 0xF0, 0x20, 0x00,	// Char 036 ($)
	0xC8, 0xC8, 0x10, 0x20, 0x40, 0x98, 0x98, 0x00,	// Char 037 (%)
	0x70, 0x88, 0x50, 0x20, 0x54, 0x88, 0x74, 0x00,	// Char 038 (&)
	0x60, 0x20, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 039 (')
	0x20, 0x40, 0x80, 0x80, 0x80, 0x40, 0x20, 0x00,	// Char 040 (()
	0x20, 0x10, 0x08, 0x08, 0x08, 0x10, 0x20, 0x00,	// Char 041 ())
	0x00, 0x20, 0xA8, 0x70, 0x70, 0xA8, 0x20, 0x00,	// Char 042 (*)
	0x00, 0x00, 0x20, 0x20, 0xF8, 0x20, 0x20, 0x00,	// Char 043 (+)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x20, 0x40,	// Char 044 (,)
	0x00, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00,	// Char 045 (-)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x60, 0x00,	// Char 046 (.)
	0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00,	// Char 047 (/)
	0x70, 0x88, 0x98, 0xA8, 0xC8, 0x88, 0x70, 0x00,	// Char 048 (0)
	0x40, 0xC0, 0x40, 0x40, 0x40, 0x40, 0xE0, 0x00,	// Char 049 (1)
	0x70, 0x88, 0x08, 0x10, 0x20, 0x40, 0xF8, 0x00,	// Char 050 (2)
	0x70, 0x88, 0x08, 0x10, 0x08, 0x88, 0x70, 0x00,	// Char 051 (3)
	0x08, 0x18, 0x28, 0x48, 0xFC, 0x08, 0x08, 0x00,	// Char 052 (4)
	0xF8, 0x80, 0x80, 0xF0, 0x08, 0x88, 0x70, 0x00,	// Char 053 (5)
	0x20, 0x40, 0x80, 0xF0, 0x88, 0x88, 0x70, 0x00,	// Char 054 (6)
	0xF8, 0x08, 0x10, 0x20, 0x40, 0x40, 0x40, 0x00,	// Char 055 (7)
	0x70, 0x88, 0x88, 0x70, 0x88, 0x88, 0x70, 0x00,	// Char 056 (8)
	0x70, 0x88, 0x88, 0x78, 0x08, 0x08, 0x70, 0x00,	// Char 057 (9)
	0x00, 0x00, 0x60, 0x60, 0x00, 0x60, 0x60, 0x00,	// Char 058 (:)
	0x00, 0x00, 0x60, 0x60, 0x00, 0x60, 0x60, 0x20,	// Char 059 (;)
	0x10, 0x20, 0x40, 0x80, 0x40, 0x20, 0x10, 0x00,	// Char 060 (<)
	0x00, 0x00, 0xF8, 0x00, 0xF8, 0x00, 0x00, 0x00,	// Char 061 (=)
	0x80, 0x40, 0x20, 0x10, 0x20, 0x40, 0x80, 0x00,	// Char 062 (>)
	0x78, 0x84, 0x04, 0x08, 0x10, 0x00, 0x10, 0x00,	// Char 063 (?)
	0x70, 0x88, 0x88, 0xA8, 0xB8, 0x80, 0x78, 0x00,	// Char 064 (@)
	0x20, 0x50, 0x88, 0x88, 0xF8, 0x88, 0x88, 0x00,	// Char 065 (A)
	0xF0, 0x88, 0x88, 0xF0, 0x88, 0x88, 0xF0, 0x00,	// Char 066 (B)
	0x70, 0x88, 0x80, 0x80, 0x80, 0x88, 0x70, 0x00,	// Char 067 (C)
	0xF0, 0x88, 0x88, 0x88, 0x88, 0x88, 0xF0, 0x00,	// Char 068 (D)
	0xF8, 0x80, 0x80, 0xE0, 0x80, 0x80, 0xF8, 0x00,	// Char 069 (E)
	0xF8, 0x80, 0x80, 0xE0, 0x80, 0x80, 0x80, 0x00,	// Char 070 (F)
	0x70, 0x88, 0x80, 0x80, 0x98, 0x88, 0x78, 0x00,	// Char 071 (G)
	0x88, 0x88, 0x88, 0xF8, 0x88, 0x88, 0x88, 0x00,	// Char 072 (H)
	0xE0, 0x40, 0x40, 0x40, 0x40, 0x40, 0xE0, 0x00,	// Char 073 (I)
	0x38, 0x10, 0x10, 0x10, 0x10, 0x90, 0x60, 0x00,	// Char 074 (J)
	0x88, 0x90, 0xA0, 0xC0, 0xA0, 0x90, 0x88, 0x00,	// Char 075 (K)
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xF8, 0x00,	// Char 076 (L)
	0x82, 0xC6, 0xAA, 0x92, 0x82, 0x82, 0x82, 0x00,	// Char 077 (M)
	0x84, 0xC4, 0xA4, 0x94, 0x8C, 0x84, 0x84, 0x00,	// Char 078 (N)
	0x70, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00,	// Char 079 (O)
	0xF0, 0x88, 0x88, 0xF0, 0x80, 0x80, 0x80, 0x00,	// Char 080 (P)
	0x70, 0x88, 0x88, 0x88, 0xA8, 0x90, 0x68, 0x00,	// Char 081 (Q)
	0xF0, 0x88, 0x88, 0xF0, 0xA0, 0x90, 0x88, 0x00,	// Char 082 (R)
	0x70, 0x88, 0x80, 0x70, 0x08, 0x88, 0x70, 0x00,	// Char 083 (S)
	0xF8, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00,	// Char 084 (T)
	0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00,	// Char 085 (U)
	0x88, 0x88, 0x88, 0x50, 0x50, 0x20, 0x20, 0x00,	// Char 086 (V)
	0x82, 0x82, 0x82, 0x82, 0x92, 0x92, 0x6C, 0x00,	// Char 087 (W)
	0x88, 0x88, 0x50, 0x20, 0x50, 0x88, 0x88, 0x00,	// Char 088 (X)
	0x88, 0x88, 0x88, 0x50, 0x20, 0x20, 0x20, 0x00,	// Char 089 (Y)
	0xF8, 0x08, 0x10, 0x20, 0x40, 0x80, 0xF8, 0x00,	// Char 090 (Z)
	0xE0, 0x80, 0x80, 0x80, 0x80, 0x80, 0xE0, 0x00,	// Char 091 ([)
	0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x00,	// Char 092 (\)
	0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, 0x00,	// Char 093 (])
	0x20, 0x50, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 094 (^)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x00,	// Char 095 (_)
	0x40, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 096 (`)
	0x00, 0x00, 0x70, 0x08, 0x78, 0x88, 0x74, 0x00,	// Char 097 (a)
	0x80, 0x80, 0xB0, 0xC8, 0x88, 0xC8, 0xB0, 0x00,	// Char 098 (b)
	0x00, 0x00, 0x70, 0x88, 0x80, 0x88, 0x70, 0x00,	// Char 099 (c)
	0x08, 0x08, 0x68, 0x98, 0x88, 0x98, 0x68, 0x00,	// Char 100 (d)
	0x00, 0x00, 0x70, 0x88, 0xF8, 0x80, 0x70, 0x00,	// Char 101 (e)
	0x30, 0x48, 0x40, 0xE0, 0x40, 0x40, 0x40, 0x00,	// Char 102 (f)
	0x00, 0x00, 0x34, 0x48, 0x48, 0x38, 0x08, 0x30,	// Char 103 (g)
	0x80, 0x80, 0xB0, 0xC8, 0x88, 0x88, 0x88, 0x00,	// Char 104 (h)
	0x20, 0x00, 0x60, 0x20, 0x20, 0x20, 0x70, 0x00,	// Char 105 (i)
	0x10, 0x00, 0x30, 0x10, 0x10, 0x10, 0x90, 0x60,	// Char 106 (j)
	0x80, 0x80, 0x88, 0x90, 0xA0, 0xD0, 0x88, 0x00,	// Char 107 (k)
	0xC0, 0x40, 0x40, 0x40, 0x40, 0x40, 0xE0, 0x00,	// Char 108 (l)
	0x00, 0x00, 0xEC, 0x92, 0x92, 0x92, 0x92, 0x00,	// Char 109 (m)
	0x00, 0x00, 0xB0, 0xC8, 0x88, 0x88, 0x88, 0x00,	// Char 110 (n)
	0x00, 0x00, 0x70, 0x88, 0x88, 0x88, 0x70, 0x00,	// Char 111 (o)
	0x00, 0x00, 0xB0, 0xC8, 0xC8, 0xB0, 0x80, 0x80,	// Char 112 (p)
	0x00, 0x00, 0x68, 0x98, 0x98, 0x68, 0x08, 0x08,	// Char 113 (q)
	0x00, 0x00, 0xB0, 0xC8, 0x80, 0x80, 0x80, 0x00,	// Char 114 (r)
	0x00, 0x00, 0x78, 0x80, 0x70, 0x08, 0xF0, 0x00,	// Char 115 (s)
	0x40, 0x40, 0xE0, 0x40, 0x40, 0x50, 0x20, 0x00,	// Char 116 (t)
	0x00, 0x00, 0x88, 0x88, 0x88, 0x98, 0x68, 0x00,	// Char 117 (u)
	0x00, 0x00, 0x88, 0x88, 0x88, 0x50, 0x20, 0x00,	// Char 118 (v)
	0x00, 0x00, 0x82, 0x82, 0x92, 0x92, 0x6C, 0x00,	// Char 119 (w)
	0x00, 0x00, 0x88, 0x50, 0x20, 0x50, 0x88, 0x00,	// Char 120 (x)
	0x00, 0x00, 0x88, 0x88, 0x98, 0x68, 0x08, 0x70,	// Char 121 (y)
	0x00, 0x00, 0xF8, 0x10, 0x20, 0x40, 0xF8, 0x00,	// Char 122 (z)
	0x10, 0x20, 0x20, 0x40, 0x20, 0x20, 0x10, 0x00,	// Char 123 ({)
	0x40, 0x40, 0x40, 0x00, 0x40, 0x40, 0x40, 0x00,	// Char 124 (|)
	0x40, 0x20, 0x20, 0x10, 0x20, 0x20, 0x40, 0x00,	// Char 125 (})
	0x76, 0xDC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 126 (~)
	0x00, 0x10, 0x38, 0x6C, 0xC6, 0xC6, 0xFE, 0x00	// Char 127 (.)
};
