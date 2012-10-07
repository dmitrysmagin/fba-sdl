// Media module
#include "burner.h"

int MediaInit()
{
	if (ScrnInit()) {					// Init the Scrn Window
		AppError(_T("ScrnInit Failed"), 0);
		return 1;
	}

	InputInit();						// Init Input

	nAppVirtualFps = nBurnFPS;

	AudSoundInit();						// Init Sound (not critical if it fails)

	nBurnSoundRate = 0;					// Assume no sound
	pBurnSoundOut = NULL;
	if (bAudOkay) {
		nBurnSoundRate = nAudSampleRate;
		nBurnSoundLen = nAudSegLen;
	}

	return 0;
}

int MediaExit(bool bRestart)
{
	nBurnSoundRate = 0;					// Blank sound
	pBurnSoundOut = NULL;

	AudSoundExit();						// Exit Dsound

	VidExit();

	InputExit();

	DestroyWindow(hInpsDlg);			// Make sure the Input Set dialog is exitted
	DestroyWindow(hInpdDlg);			// Make sure the Input Dialog is exitted

	ScrnExit(bRestart);					// Exit the Scrn Window

	return 0;
}
