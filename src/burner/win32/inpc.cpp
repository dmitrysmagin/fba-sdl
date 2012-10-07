// Burner Input Constant dialog module
#include "burner.h"

HWND hInpcDlg = NULL;								// Handle to the Input Dialog
unsigned int nInpcInput = 0;						// The input number we are redefining

static HWND hValue = NULL;							// Handle to value edit control
static struct GameInp* pgi = NULL;					// Current GameInp

static int InpcInit()
{
	TCHAR szText[128];
	int nCurrent = 0;

	struct BurnInputInfo bii;						// Info about the input

	hValue = GetDlgItem(hInpcDlg, IDC_INPC_VALUE);	// Get Edit controls

	// Get the extra info about the input
	memset(&bii, 0, sizeof(bii));
	BurnDrvGetInputInfo(&bii, nInpcInput);
	if (bii.szName == NULL) {
		bii.szName= "";
	}

	// Set the dialog title
	_stprintf(szText, _T("Edit %.100hs"), bii.szName, NULL, 0);
	SetWindowText(hInpcDlg, szText);

	pgi = NULL;
	if (nInpcInput >= nGameInpCount) {				// input out of range
		return 1;
	}
	pgi = GameInp + nInpcInput;

	// Get current constant
	if (pgi->nInput == GIT_CONSTANT) {
	nCurrent=pgi->Input.Constant.nConst; }
	_stprintf(szText, _T("0x%.2X"), nCurrent);
	SetWindowText(hValue, szText);

	return 0;
}

static int InpcExit()
{
	pgi=NULL;
	hValue=NULL;
	hInpcDlg=NULL;

	return 0;
}

static BOOL CALLBACK DialogProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM /*lParam*/)
{
	if (Msg == WM_INITDIALOG) {						// 1 = we didn't set focus?
		hInpcDlg = hDlg;
		InpcInit();

		return 1;
	}
	if (Msg == WM_CLOSE){
		DestroyWindow(hInpcDlg);

		return 0;
	}
	if (Msg == WM_DESTROY) {
		InpcExit();

		return 0;
	}

	if (Msg == WM_COMMAND) {
		int Id = LOWORD(wParam);
		int Notify = HIWORD(wParam);
		if (Id == IDOK     && Notify == BN_CLICKED) {		// OK = close
			SendMessage(hDlg, WM_CLOSE, 0, 0);
			return 0;
		}
		if (Id == IDCANCEL && Notify == BN_CLICKED) {		// cancel = close
			SendMessage(hDlg, WM_CLOSE, 0, 0);
			return 0;
		}

		if (Id == IDC_INPC_VALUE && Notify == EN_CHANGE) {
			// Edit box may have been changed
			TCHAR szNew[16] = _T("");
			int nVal = 0;

			if (pgi == NULL) {
				return 0;
			}

			GetWindowText(hValue, szNew, sizeof(szNew));

			// Set new constant
			pgi->nInput = GIT_CONSTANT;
			nVal = _tcstol(szNew, NULL, 0);
			pgi->Input.Constant.nConst = (unsigned char)nVal;

			InpdListMake(0);								// refresh view

			return 0;
		}
	}

	return 0;
}

int InpcCreate()
{
	DestroyWindow(hInpcDlg);
	hInpcDlg = NULL;

	hInpcDlg = CreateDialog(hAppInst, MAKEINTRESOURCE(IDD_INPC), hInpdDlg, DialogProc);
	if (hInpcDlg == NULL) {
		return 1;
	}

	WndInMid(hInpcDlg, hInpdDlg);
	ShowWindow(hInpcDlg, SW_NORMAL);

	return 0;
}
