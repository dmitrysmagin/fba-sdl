#include "burner.h"
#include "version.h"
#include "build_details.h"
#include <richedit.h>

// Print text surrounded by a black outline
static void myDrawText(HDC hDC, RECT* pRect, TCHAR* szText, int nSizeDelta, int nColour, UINT uFormat)
{
	TCHAR szName[32];
	RECT rect;
	HFONT hFont, myFont;
	TEXTMETRIC myMetric;

	GetTextFace(hDC, 32, szName);
	GetTextMetrics(hDC, &myMetric);
	myFont = CreateFont(myMetric.tmHeight + nSizeDelta, 0, 0, 0, FW_BLACK, 0, 0, 0, 0, 0, 0, ANTIALIASED_QUALITY, 0, szName);
	hFont = (HFONT)SelectObject(hDC, myFont);
	SetBkMode(hDC, TRANSPARENT);

	// Shrink the rect to allow space for the outline
	memcpy(&rect, pRect, sizeof(RECT));
	rect.left += 1;
	rect.top += 1;
	rect.right -= 1;
	rect.bottom -= 1;

	// Print the outline first
	SetTextColor(hDC, 0);
	rect.left -= 1;
	rect.right -= 1;
	DrawText(hDC, szText, -1, &rect, uFormat);
	rect.top -= 1;
	rect.bottom -= 1;
	DrawText(hDC, szText, -1, &rect, uFormat);
	rect.left += 1;
	rect.right += 1;
	DrawText(hDC, szText, -1, &rect, uFormat);
	rect.left += 1;
	rect.right += 1;
	DrawText(hDC, szText, -1, &rect, uFormat);
	rect.top += 1;
	rect.bottom += 1;
	DrawText(hDC, szText, -1, &rect, uFormat);
	rect.top += 1;
	rect.bottom += 1;
	DrawText(hDC, szText, -1, &rect, uFormat);
	rect.left -= 1;
	rect.right -= 1;
	DrawText(hDC, szText, -1, &rect, uFormat);
	rect.left -= 1;
	rect.right -= 1;
	DrawText(hDC, szText, -1, &rect, uFormat);
	rect.left += 1;
	rect.right += 1;
	rect.top -= 1;
	rect.bottom -= 1;

	// Then print the text on top
	SetTextColor(hDC, nColour);
	DrawText(hDC, szText, -1, &rect, uFormat);

	SelectObject(hDC, hFont);
	DeleteObject(myFont);
}

static bool AboutDrawStrings(unsigned int nControlID, LPDRAWITEMSTRUCT pdis)
{
	switch (nControlID) {
		case IDC_FBA_VER: {
			TCHAR szVerString[128];
			if ((nBurnVer & 0xFFFF) > 0x9990) {

				int nVer1 = ((nBurnVer >> 16) & 0xFF) + 1;
				if ((nVer1 & 0x0F) > 9) {
					nVer1 += 6;
				}
				int nVer2 = nVer1 & 0x0F;
				nVer1 >>= 4;

				_stprintf(szVerString, _T(APP_TITLE) _T(" v%s (v%i.%i Release Candidate %i)"), szAppBurnVer, nVer1, nVer2, nBurnVer & 0x0F);
			} else {
				if (nBurnVer & 0x00FF) {
					_stprintf(szVerString, _T(APP_TITLE) _T(" v%s (alpha version)"), szAppBurnVer);
				} else {
					if (nBurnVer & 0xFF00) {
						_stprintf(szVerString, _T(APP_TITLE) _T(" v%s (beta version)"), szAppBurnVer);
					} else {
						_stprintf(szVerString, _T(APP_TITLE) _T(" v%s (release version)"), szAppBurnVer);
					}
				}
			}

			myDrawText(pdis->hDC, &pdis->rcItem, szVerString, 2, RGB(0xFF, 0xF7, 0xDF), DT_CENTER);

			return true;
		}
		case IDC_SPECIALSTRING: {

#ifdef SPECIALBUILD
			char* szSpecialBuild = MAKE_STRING(SPECIALBUILD);

			myDrawText(pdis->hDC, &pdis->rcItem, szSpecialBuild, -1, RGB(0xFF, 0xCF, 0x7F), DT_CENTER);
#else
			TCHAR szBuild[256] = _T("");

			RECT rect = pdis->rcItem;
			rect.top += 1;

			_stprintf(szBuild, _T("built on ") _T(MAKE_STRING(BUILD_DATE)) _T(", ") _T(MAKE_STRING(BUILD_TIME)) _T(" (") _T(MAKE_STRING(BUILD_CHAR)) _T(", ") _T(MAKE_STRING(BUILD_COMP)) _T(", ") _T(MAKE_STRING(BUILD_CPU)) _T("%s)"), MMX ? _T(", MMX") : _T(""));

			myDrawText(pdis->hDC, &rect, szBuild, -2, RGB(0xDB, 0xDB, 0xDB), DT_CENTER);
#endif
			return true;
		}
	}
	
	return false;
}

// ----------------------------------------------------------------------------

static BOOL CALLBACK AboutProc(HWND hDlg ,UINT Msg, WPARAM wParam, LPARAM lParam)
{
	if (Msg == WM_INITDIALOG) {
		WndInMid(hDlg, hScrnWnd);
		return TRUE;
	}

	if (Msg == WM_DRAWITEM) {
		if (AboutDrawStrings(wParam, (LPDRAWITEMSTRUCT)lParam)) {
			return TRUE;
		}

		return 0;
	}

	if (Msg == WM_COMMAND && HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) == IDC_SHOWLICENSE) {
		RECT rect = { 0, 0, 0, 80 };

		SendMessage(hDlg, WM_NEXTDLGCTL, (WPARAM)GetDlgItem(hDlg, IDOK), TRUE);
		EnableWindow(GetDlgItem(hDlg, IDC_SHOWLICENSE), FALSE);

		SendDlgItemMessage(hDlg, IDC_LICENSE, EM_SETMARGINS, EC_LEFTMARGIN, 3);
//		SendDlgItemMessage(hDlg, IDC_LICENSE, EM_SETTYPOGRAPHYOPTIONS, TO_ADVANCEDTYPOGRAPHY, TO_ADVANCEDTYPOGRAPHY);

		{
			TCHAR* pszLicense = NULL;
			int nSize = 1024;

			do {
				nSize <<= 1;
				free(pszLicense);
				pszLicense = (TCHAR*)malloc(nSize * sizeof(TCHAR));
			} while (pszLicense && LoadString(hAppInst, ID_LICENSE, pszLicense, nSize) == nSize - 1);

			if (pszLicense) {
				SendDlgItemMessage(hDlg, IDC_LICENSE, WM_SETTEXT, (WPARAM)0, (LPARAM)pszLicense);
			}

			free(pszLicense);
		}

		MapDialogRect(hDlg, &rect);
		int nSize = rect.bottom;
		GetWindowRect(hDlg, &rect);
		MoveWindow(hDlg, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top + nSize, TRUE);

		WndInMid(hDlg, hScrnWnd);
		return 0;
	}

	if (Msg == WM_CLOSE) {
		EndDialog(hDlg,0);
	}
	if (Msg == WM_COMMAND && HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) == IDOK) {
		SendMessage(hDlg, WM_CLOSE, 0, 0);
	}

	return 0;
}

int AboutCreate()
{
	DialogBox(hAppInst, MAKEINTRESOURCE(IDD_ABOUT), hScrnWnd, AboutProc);

	return 0;
}

// ----------------------------------------------------------------------------

static BOOL CALLBACK FirstProc(HWND hDlg ,UINT Msg, WPARAM wParam, LPARAM lParam)
{
	static bool bLicenseDisplayed;

	if (Msg == WM_INITDIALOG) {
		TCHAR szWarningString[1024];

		WndInMid(hDlg, NULL);
		bLicenseDisplayed = false;

		SendDlgItemMessage(hDlg, IDC_LICENSE, EM_SETMARGINS, EC_LEFTMARGIN, 3);
//		SendDlgItemMessage(hDlg, IDC_LICENSE, EM_SETTYPOGRAPHYOPTIONS, TO_ADVANCEDTYPOGRAPHY, TO_ADVANCEDTYPOGRAPHY);

		_stprintf(szWarningString, _T("This appears to be the first time you run ") _T(APP_TITLE) _T(" v%.20s.\n\n"), szAppBurnVer);

 #if VER_ALPHA > 0 && (VER_ALPHA < 90 || VER_BETA < 99)
		_stprintf(szWarningString + _tcslen(szWarningString), _T("Note that this is alpha quality software. As such, it likely will exhibit problems, including audio/video options not behaving correctly, the emulation of some games misses some features, and may exhibit stability problems. CAVEAT LECTOR!\n\n"));
 #elif VER_BETA > 0 && VER_BETA < 99
		_stprintf(szWarningString + _tcslen(szWarningString), _T("Note that this is beta quality software. As such, it likely may be missing some features, or exhibit some problems with your system.\n\n"));
 #endif
		_stprintf(szWarningString + _tcslen(szWarningString), _T("Please take some time to match the audio/video settings to your system capabilities and personal preferences. If you continue to use and/or distribute this software, you must agree to be bound by the terms of license agreement, which is always accessible via the about dialog."));

		SendDlgItemMessage(hDlg, IDC_LICENSE, WM_SETTEXT, (WPARAM)0, (LPARAM)szWarningString);

		ShowWindow(GetDlgItem(hDlg, IDC_ACCEPTLICENSE), SW_HIDE);

		return TRUE;
	}

	if (Msg == WM_DRAWITEM) {
		if (AboutDrawStrings(wParam, (LPDRAWITEMSTRUCT)lParam)) {
			return TRUE;
		}

		return 0;
	}

	if (Msg == WM_COMMAND && HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) == IDOK) {

		if (bLicenseDisplayed) {
			SendMessage(hDlg, WM_CLOSE, 0, 0);
			return 0;
		}

		bLicenseDisplayed = true;

		EnableWindow(GetDlgItem(hDlg, IDOK), FALSE);
		ShowWindow(GetDlgItem(hDlg, IDC_ACCEPTLICENSE), SW_SHOW);
		SendMessage(hDlg, WM_NEXTDLGCTL, (WPARAM)GetDlgItem(hDlg, IDC_ACCEPTLICENSE), TRUE);

		{
			TCHAR* pszLicense = NULL;
			int nSize = 1024;

			do {
				nSize <<= 1;
				free(pszLicense);
				pszLicense = (TCHAR*)malloc(nSize * sizeof(TCHAR));
			} while (pszLicense && LoadString(hAppInst, ID_LICENSE, pszLicense, nSize) == nSize - 1);

			if (pszLicense) {
				SendDlgItemMessage(hDlg, IDC_LICENSE, WM_SETTEXT, (WPARAM)0, (LPARAM)pszLicense);
			}

			free(pszLicense);
		}

		return 0;
	}
	if (Msg == WM_COMMAND && LOWORD(wParam) == IDC_ACCEPTLICENSE) {
		if (SendDlgItemMessage(hDlg, IDC_ACCEPTLICENSE, BM_GETSTATE, 0, 0) & BST_CHECKED) {
			EnableWindow(GetDlgItem(hDlg, IDOK), TRUE);
		} else {
			EnableWindow(GetDlgItem(hDlg, IDOK), FALSE);
		}
	}

	if (Msg == WM_CLOSE) {
		EndDialog(hDlg,0);
	}
	if (Msg == WM_COMMAND && HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) == IDOK) {
	}

	return 0;
}

int FirstUsageCreate()
{
	DialogBox(hAppInst, MAKEINTRESOURCE(IDD_FIRST), hScrnWnd, FirstProc);

	return 0;
}

