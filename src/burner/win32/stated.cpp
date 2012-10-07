// State dialog module
#include "burner.h"

int bDrvSaveAll = 0;

static int MakeOfn()
{
	memset(&ofn, 0, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hScrnWnd;
	ofn.lpstrFilter = _T("FB Alpha Save States (*.fs, *.fr)\0*.fs;*.fr\0\0");
	ofn.lpstrFile = szChoice;
	ofn.nMaxFile = sizeof(szChoice) / sizeof(TCHAR);
	ofn.lpstrInitialDir = _T(".\\savestates");
	ofn.Flags = OFN_NOCHANGEDIR | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = _T("fs");
	return 0;
}

// The automatic save
int StatedAuto(int bSave)
{
	static TCHAR szName[32] = _T("");
	int nRet;

	_stprintf(szName, _T("config\\games\\%.8s.fs"), BurnDrvGetText(DRV_NAME));

	if (bSave == 0) {
		nRet = BurnStateLoad(szName, bDrvSaveAll, NULL);		// Load ram
		if (nRet && bDrvSaveAll)	{
			nRet = BurnStateLoad(szName, 0, NULL);				// Couldn't get all - okay just try the nvram
		}
	} else {
		nRet = BurnStateSave(szName, bDrvSaveAll);				// Save ram
	}

	return nRet;
}

static void CreateStateName(int nSlot)
{
	_stprintf(szChoice, _T(".\\savestates\\%s slot %02x.fs"), BurnDrvGetText(DRV_NAME), nSlot);
}

int StatedLoad(int nSlot)
{
	int nRet;
	int bOldPause;

	if (nSlot) {
		CreateStateName(nSlot);
	} else {
		if (bDrvOkay) {
			_stprintf(szChoice, _T("%.8s*.fs"), BurnDrvGetText(DRV_NAME));
		} else {
			_stprintf(szChoice, _T("savestate"));
		}
		MakeOfn();
		ofn.lpstrTitle = _T("Load State");

		bOldPause = bRunPause;
		bRunPause = 1;
		nRet = GetOpenFileName(&ofn);
		bRunPause = bOldPause;

		if (nRet == 0) {		// Error
			return 1;
		}
	}

	nRet = BurnStateLoad(szChoice, 1, &DrvInitCallback);

	// Describe any possible errors:
	if (nRet == 3) {
		AppError(_T("The save state is for the wrong game."), 0);
	} else {
		if (nRet == 4) {
			AppError(_T("This state is too old and cannot be loaded."), 0);
		} else {
			if (nRet == 5) {
				AppError(_T("Emulator is too old to load this state."), 0);
			} else {
				if (nRet && !nSlot) {
					AppError(_T("Error loading state"), 0);
				}
			}
		}
	}

	return nRet;
}

int StatedSave(int nSlot)
{
	int nRet;
	int bOldPause;

	if (bDrvOkay == 0) {
		return 1;
	}

	if (nSlot) {
		CreateStateName(nSlot);
	} else {
		_stprintf(szChoice, _T("%.8s"), BurnDrvGetText(DRV_NAME));
		MakeOfn();
		ofn.lpstrTitle = _T("Save State");
		ofn.Flags |= OFN_OVERWRITEPROMPT;

		bOldPause = bRunPause;
		bRunPause = 1;
		nRet = GetSaveFileName(&ofn);
		bRunPause = bOldPause;

		if (nRet == 0) {		// Error
			return 1;
		}
	}

	nRet = BurnStateSave(szChoice, 1);

	if (nRet && !nSlot) {
		AppError(_T("Error saving state"), 1);
	}

	return nRet;
}
