
// Run module
#include <SDL/SDL.h>

#include "burner.h"
#include "fba_player.h"
#include "snd.h"
#include "font.h"
#include "pandorasdk.h"
#include "config.h"
#include "sdlvideo.h"
#include "sdlinput.h"

extern unsigned int FBA_KEYPAD[4]; // sdlinput.cpp
extern CFG_OPTIONS config_options;

bool bShowFPS = false;
bool bPauseOn = false;

int InpMake(unsigned int[]);

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
	if (!bPauseOn)
	{
		nFramesEmulated++;
		nCurrentFrame++;

		pBurnDraw = NULL;
		if ( bDraw )
		{
			nFramesRendered++;
			pBurnDraw = (unsigned char *)BurnVideoBuffer; 
		}

		BurnDrvFrame();

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
	} else {
		DrawString ("PAUSED", (unsigned short *) &VideoBuffer[0], (PhysicalBufferWidth>>1)-24, 120,PhysicalBufferWidth);
		gp2x_video_flip();
	}
	return 0;
}

void ChangeFrameskip()
{
	bShowFPS = !bShowFPS;
	gp2x_clear_framebuffers();
	nFramesRendered = 0;
}
