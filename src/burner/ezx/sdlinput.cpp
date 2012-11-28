
#include <SDL/SDL.h>

#include "burner.h"
#include "config.h"
#include "sdlinput.h"

#define BUTTON_LEFT     0x0001
#define BUTTON_RIGHT    0x0002
#define BUTTON_UP       0x0004
#define BUTTON_DOWN     0x0008
#define BUTTON_SELECT   0x0010
#define BUTTON_START    0x0020
#define BUTTON_A        0x0040
#define BUTTON_B        0x0080
#define BUTTON_X        0x0100
#define BUTTON_Y        0x0200
#define BUTTON_SL       0x0400
#define BUTTON_SR       0x0800
#define BUTTON_QT       0x1000
#define BUTTON_PAUSE    0x2000

char joyCount = 0;
SDL_Joystick *joys[4];

unsigned int FBA_KEYPAD[4];
unsigned char ServiceRequest = 0;
unsigned char P1P2Start = 0;

// external variables
extern CFG_OPTIONS config_options; // main.cpp
extern CFG_KEYMAP config_keymap; // main.cpp

extern bool bPauseOn; // run.cpp
extern bool GameLooping; // fba_player.cpp

// external functions
void ChangeFrameskip(); // run.cpp

// don't forget to check orientation BurnDrvGetFlags() & BDF_ORIENTATION_VERTICAL)
// because we should change dpad directions
unsigned int sdl_input_read() // called from do_keypad() in fba_player.cpp
{
	static int pckeydata = 0;
	SDL_Event event;

	while(SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYUP) {
			if (event.key.keysym.sym == config_keymap.up) pckeydata &= ~BUTTON_UP;
			if (event.key.keysym.sym == config_keymap.down) pckeydata &= ~BUTTON_DOWN;
			if (event.key.keysym.sym == config_keymap.left) pckeydata &= ~BUTTON_LEFT;
			if (event.key.keysym.sym == config_keymap.right) pckeydata &= ~BUTTON_RIGHT;
			if (event.key.keysym.sym == config_keymap.fire1) pckeydata &= ~BUTTON_A;
			if (event.key.keysym.sym == config_keymap.fire2) pckeydata &= ~BUTTON_B;
			if (event.key.keysym.sym == config_keymap.fire3) pckeydata &= ~BUTTON_X;
			if (event.key.keysym.sym == config_keymap.fire4) pckeydata &= ~BUTTON_Y;
			if (event.key.keysym.sym == config_keymap.fire5) pckeydata &= ~BUTTON_SL;
			if (event.key.keysym.sym == config_keymap.fire6) pckeydata &= ~BUTTON_SR;
			if (event.key.keysym.sym == config_keymap.coin1) pckeydata &= ~BUTTON_SELECT;
			if (event.key.keysym.sym == config_keymap.start1) pckeydata &= ~BUTTON_START;
			if (event.key.keysym.sym == config_keymap.quit) pckeydata &= ~BUTTON_QT;
			if (event.key.keysym.sym == config_keymap.pause) pckeydata &= ~BUTTON_PAUSE;
		}
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == config_keymap.up) pckeydata |= BUTTON_UP;
			if (event.key.keysym.sym == config_keymap.down) pckeydata |= BUTTON_DOWN;
			if (event.key.keysym.sym == config_keymap.left) pckeydata |= BUTTON_LEFT;
			if (event.key.keysym.sym == config_keymap.right) pckeydata |= BUTTON_RIGHT;
			if (event.key.keysym.sym == config_keymap.fire1) pckeydata |= BUTTON_A;
			if (event.key.keysym.sym == config_keymap.fire2) pckeydata |= BUTTON_B;
			if (event.key.keysym.sym == config_keymap.fire3) pckeydata |= BUTTON_X;
			if (event.key.keysym.sym == config_keymap.fire4) pckeydata |= BUTTON_Y;
			if (event.key.keysym.sym == config_keymap.fire5) pckeydata |= BUTTON_SL;
			if (event.key.keysym.sym == config_keymap.fire6) pckeydata |= BUTTON_SR;
			if (event.key.keysym.sym == config_keymap.coin1) pckeydata |= BUTTON_SELECT;
			if (event.key.keysym.sym == config_keymap.start1) pckeydata |= BUTTON_START;
			if (event.key.keysym.sym == config_keymap.quit) pckeydata |= BUTTON_QT;
			if (event.key.keysym.sym == config_keymap.pause) pckeydata |= BUTTON_PAUSE;
		}
	}

	return pckeydata;
}

void do_keypad()
{
	static int pausecnt = 0;
	unsigned int joy = sdl_input_read();
	int bVert = (BurnDrvGetFlags() & BDF_ORIENTATION_VERTICAL);

	FBA_KEYPAD[0] = 0;
	FBA_KEYPAD[1] = 0;
	FBA_KEYPAD[2] = 0;
	FBA_KEYPAD[3] = 0;
	ServiceRequest = 0;
	P1P2Start = 0;

	if (joy & BUTTON_UP) FBA_KEYPAD[0] |= bVert ? 0x0004 : 0x0001;
	if (joy & BUTTON_DOWN) FBA_KEYPAD[0] |= bVert ? 0x0008 : 0x0002;
	if (joy & BUTTON_LEFT) FBA_KEYPAD[0] |= bVert ? 0x0002 : 0x0004;
	if (joy & BUTTON_RIGHT) FBA_KEYPAD[0] |= bVert ? 0x0001 : 0x0008;

	if (joy & BUTTON_SELECT) FBA_KEYPAD[0] |= 0x0010;
	if (joy & BUTTON_START) FBA_KEYPAD[0] |= 0x0020;

	if (joy & BUTTON_A) FBA_KEYPAD[0] |= 0x0040;		// A
	if (joy & BUTTON_B) FBA_KEYPAD[0] |= 0x0080;		// B
	if (joy & BUTTON_X) FBA_KEYPAD[0] |= 0x0100;		// C
	if (joy & BUTTON_Y) FBA_KEYPAD[0] |= 0x0200;		// D
	if (joy & BUTTON_SL) FBA_KEYPAD[0] |= 0x0400;	// E
	if (joy & BUTTON_SR) FBA_KEYPAD[0] |= 0x0800;	// F

	if (joy & BUTTON_QT) GameLooping=false;
	if (pausecnt > 0) pausecnt--;
	if ((joy & BUTTON_PAUSE) && (pausecnt==0))
	{
		bPauseOn=!bPauseOn;
		pausecnt=20;
		if (config_options.option_sound_enable == 2) SDL_PauseAudio(bPauseOn);
	}

	if ((joy & BUTTON_SL) && (joy & BUTTON_SR)) {
		if (joy & BUTTON_Y) ChangeFrameskip();
		else if (joy & BUTTON_START) GameLooping = false;
		else if (joy & BUTTON_SELECT) ServiceRequest = 1;
	}
	else if (joy & BUTTON_START && joy & BUTTON_SELECT) P1P2Start = 1; // put enter GUI here later
}

void sdl_input_init()
{
	joyCount = SDL_NumJoysticks();
	if (joyCount > 5) joyCount = 5;
	printf("%d Joystick(s) Found\n", joyCount);

	if (joyCount > 0) {
		for (int i = 0; i < joyCount; i++) {
			printf("%s\t",SDL_JoystickName(i));
			joys[i] = SDL_JoystickOpen(i);
			printf("Hats %d\t",SDL_JoystickNumHats(joys[i]));
			printf("Buttons %d\t",SDL_JoystickNumButtons(joys[i]));
			printf("Axis %d\n",SDL_JoystickNumAxes(joys[i]));
		}
	}

}
