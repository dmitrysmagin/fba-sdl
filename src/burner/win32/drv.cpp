// Driver Init module
#include "burner.h"

int bDrvOkay = 0;						// 1 if the Driver has been initted okay, and it's okay to use the BurnDrv functions

TCHAR szAppRomPaths[DIRS_MAX][MAX_PATH] = {{_T("roms\\")}, };

static bool bSaveRAM = false;

static int DoLibInit()					// Do Init of Burn library driver
{
	int nRet;

	BzipOpen(FALSE);

	// If there is an error with the romset, report it
	if (nBzipError) {
		TCHAR *szTitle;
		int nIcon, nButton;

		// Make the correct title and icon
		if (nBzipError & 1) {
			nIcon = MB_ICONERROR;
			szTitle = _T(APP_TITLE) _T(" Error");
		} else {
			nIcon = MB_ICONWARNING;
			szTitle = _T(APP_TITLE) _T(" Warning");
		}

		if (nBzipError & 0x08) {
			nButton = MB_OK;		// no data at all - pretty basic!
		} else {
			BzipText.Add(_T("\nWould you like more detailed information?\n(For experts only!)\n"));
			nButton = MB_DEFBUTTON2 | MB_YESNO;
		}

		// We can't use AppError, so use MessageBox directly
		if (MessageBox(hScrnWnd, BzipText.szText, szTitle, nButton | nIcon | MB_SETFOREGROUND) == IDYES) {
			// Give the more detailed information string
			MessageBox(hScrnWnd, BzipDetail.szText, szTitle, MB_OK | nIcon | MB_SETFOREGROUND);
		}
	}

	ProgressCreate();

	nRet = BurnDrvInit();

	BzipClose();

	ProgressDestroy();

	if (nRet) {
		return 1;
	} else {
		return 0;
	}
}

// Catch calls to BurnLoadRom() once the emulation has started;
// Intialise the zip module before forwarding the call, and exit cleanly.
static int __cdecl DrvLoadRom(unsigned char* Dest, int* pnWrote, int i)
{
	int nRet;

	BzipOpen(FALSE);

	if ((nRet = BurnExtLoadRom(Dest, pnWrote, i)) != 0) {
		TCHAR szText[256] = _T("");
		char* pszFilename;

		BurnDrvGetRomName(&pszFilename, i, 0);
		_stprintf(szText, _T("Error loading %hs, requested by %s.\nThe emulation will likely suffer problems."), pszFilename, BurnDrvGetText(DRV_NAME));
		AppError(szText, 0);
	}

	BzipClose();

	BurnExtLoadRom = DrvLoadRom;

	ScrnTitle();

	return nRet;
}

int DrvInit(int nDrvNum, bool bRestore)
{
	DrvExit();						// Make sure exitted

	MediaExit(true);
	MediaInit();

	nBurnDrvSelect = nDrvNum;		// Set the driver number

	// Define nMaxPlayers early; GameInpInit() needs it (normally defined in DoLibInit()).
	nMaxPlayers = BurnDrvGetMaxPlayers();
	GameInpInit();					// Init game input

	ConfigGameLoad(true);
	InputMake(true);

	GameInpDefault();

	if (kNetGame) {
		nBurnCPUSpeedAdjust = 0x0100;
	}

	if (DoLibInit()) {				// Init the Burn library's driver
		TCHAR szTemp[512];

		BurnDrvExit();				// Exit the driver

		ScrnTitle();
		_stprintf (szTemp, _T("There was an error starting '%s'.\n"), BurnDrvGetText(DRV_FULLNAME));
		AppError(szTemp, 0);

		PostMessage(NULL, WM_APP + 0, 0, 0);
		return 1;
	}

	BurnExtLoadRom = DrvLoadRom;

	bDrvOkay = 1;					// Okay to use all BurnDrv functions

	bSaveRAM = false;
	if (kNetGame) {
		KailleraInitInput();
		KailleraGetInput();
	} else {
		if (bRestore) {
			StatedAuto(0);
			bSaveRAM = true;

			ConfigCheatLoad();
		}
	}

	nBurnLayer = 0xFF;				// show all layers

	// Reset the speed throttling code, so we don't 'jump' after the load
	RunReset();

	PostMessage(NULL, WM_APP + 0, 0, 0);

	return 0;
}

int DrvInitCallback()
{
	return DrvInit(nBurnDrvSelect, false);
}

int DrvExit()
{
	if (bDrvOkay) {

		StopReplay();

		VidExit();

		InvalidateRect(hScrnWnd, NULL, 1);
		UpdateWindow(hScrnWnd);			// Blank screen window

		DestroyWindow(hInpdDlg);		// Make sure the Input Dialog is exited
		DestroyWindow(hInpDIPSWDlg);	// Make sure the DipSwitch Dialog is exited
		DestroyWindow(hInpCheatDlg);	// Make sure the Cheat Dialog is exited

		if (nBurnDrvSelect < nBurnDrvCount) {

			MemCardEject();				// Eject memory card if present

			if (bSaveRAM) {
				StatedAuto(1);			// Save NV (or full) RAM
				bSaveRAM = false;
			}

			ConfigGameSave(bSaveInputs);

			GameInpExit();				// Exit game input
			BurnDrvExit();				// Exit the driver
		}
	}

	BurnExtLoadRom = NULL;

	bDrvOkay = 0;					// Stop using the BurnDrv functions

	bRunPause = 0;					// Don't pause when exitted

	if (bAudOkay) {
		// Write silence into the sound buffer on exit, and for drivers which don't use pBurnSoundOut
		memset(nAudNextSound, 0, nAudSegLen << 2);
	}

	nBurnDrvSelect = ~0U;			// no driver selected

	return 0;
}
