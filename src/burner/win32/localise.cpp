#include "burner.h"
#include <ddeml.h>

static int nFBACodepage;

struct LocaliseControlInfo { int nID; wchar_t szCaption[QUOTE_MAX]; };
struct LocaliseResourceInfo { int nID; wchar_t szCaption[QUOTE_MAX]; LocaliseControlInfo* pControlInfo[256]; };

LocaliseResourceInfo* FBALocaliseInfo = NULL;

typedef struct {
	WORD dlgVer;
	WORD signature;
	DWORD helpID;
	DWORD exStyle;
	DWORD style;
	WORD cDlgItems;
	short x;
	short y;
	short cx;
	short cy;
//	sz_Or_Ord menu;
//	sz_Or_Ord windowClass;
//	WCHAR title[titleLen];
//	WORD pointsize;
//	WORD weight;
//	BYTE italic;
//	BYTE charset;
//	WCHAR typeface[stringLen];
} DLGTEMPLATEEX;

typedef struct {
	DWORD helpID;
	DWORD exStyle;
	DWORD style;
	short x;
	short y;
	short cx;
	short cy;
	WORD id;
//	sz_Or_Ord windowClass;
//	sz_Or_Ord title;
//	WORD extraCount;
} DLGITEMTEMPLATEEX;

static char* pTemplateDataOut = NULL;


INT_PTR FBADialogBox(HINSTANCE, LPTSTR, HWND, DLGPROC);

static bool bUseLocalisation = false;


static LocaliseResourceInfo* FindResourceInfo(int /*nID*/)
{
	return FBALocaliseInfo;
}

#define CATCH_UP { int nCopySize = pTemplateDataIn - pTemplateDataInSync;								\
				   int nTotalSize = pTemplateDataOutSync - pTemplateDataOut;							\
				   pTemplateDataOut = (char*)realloc(pTemplateDataOut, nTotalSize + nCopySize);			\
				   memcpy(pTemplateDataOut + nTotalSize, pTemplateDataInSync, nCopySize);				\
				   pTemplateDataInSync = pTemplateDataIn;												\
				   pTemplateDataOutSync = pTemplateDataOut + nTotalSize + nCopySize; }

#define ALIGN(a) { int nTotalSize = (pTemplateDataOutSync - pTemplateDataOut + a - 1) & ~(a - 1);		\
				   pTemplateDataOut = (char*)realloc(pTemplateDataOut, nTotalSize);						\
				   pTemplateDataOutSync = pTemplateDataOut + nTotalSize; }

#define ADD_STRING(s) { int nTotalSize = pTemplateDataOutSync - pTemplateDataOut;						\
						int nExtraSize = wcslen((wchar_t*)s) * sizeof(wchar_t) + sizeof(wchar_t);		\
						pTemplateDataOut = (char*)realloc(pTemplateDataOut, nTotalSize + nExtraSize);	\
						wcscpy((wchar_t*)(pTemplateDataOut + nTotalSize), s);							\
						pTemplateDataOutSync = pTemplateDataOut + nTotalSize + nExtraSize; }

void ParseDlgTemplateEx(const DLGTEMPLATEEX* pTemplate)
{
	// 26 is sizeof(DLGTEMPLATEEX)
	char* pTemplateDataIn = (char*)(((UINT32)pTemplate + 26 + sizeof(WORD) - 1) & ~(sizeof(WORD) - 1));

#if 0
	dprintf(_T("\n"));
	char* pData = (char*)pTemplate;
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				unsigned int n = *pData;
				dprintf(_T("%02X"), n & 255);
				pData++;
			}
			dprintf(_T(" "));
		}
		dprintf(_T("\n"));
	}
	dprintf(_T("\n"));
#endif

	// Menu
	switch (*((WORD*)pTemplateDataIn)) {
		case 0x0000:
			pTemplateDataIn += 1 * sizeof(WORD);
			break;
		case 0xFFFF:
			dprintf(_T("   menu is %04X.\n"), *((UINT16*)pTemplateDataIn + sizeof(WORD)));
			pTemplateDataIn += 2 * sizeof(WORD);
			break;
		default:
			dprintf(_T("   menu is \"%ls\".\n"), (wchar_t*)pTemplateDataIn);
			pTemplateDataIn += wcslen((wchar_t*)pTemplateDataIn) * sizeof(wchar_t) + sizeof(wchar_t);
			break;
	}

//	pTemplateDataIn = (char*)(((UINT32)pTemplateDataIn + sizeof(WORD) - 1) & ~(sizeof(WORD) - 1));

	// Class
	switch (*((WORD*)pTemplateDataIn)) {
		case 0x0000:
			pTemplateDataIn += 1 * sizeof(WORD);
			break;
		case 0xFFFF:
			dprintf(_T("   class is %04X.\n"), *((UINT16*)pTemplateDataIn + sizeof(WORD)));
			pTemplateDataIn += 2 * sizeof(WORD);
			break;
		default:
			dprintf(_T("   class is \"%ls\".\n"), (wchar_t*)pTemplateDataIn);
			pTemplateDataIn += wcslen((wchar_t*)pTemplateDataIn) * sizeof(wchar_t) + sizeof(wchar_t);
			break;
	}

//	pTemplateDataIn = (char*)(((UINT32)pTemplateDataIn + sizeof(WORD) - 1) & ~(sizeof(WORD) - 1));

	// Caption
	dprintf(_T("   "));
	switch (*((WORD*)pTemplateDataIn)) {
		case 0x0000:
			pTemplateDataIn += 1 * sizeof(WORD);
			break;
		case 0xFFFF:
			dprintf(_T("icon is %04X, "), *((UINT16*)pTemplateDataIn + sizeof(WORD)));
			pTemplateDataIn += 2 * sizeof(WORD);
			break;
		default:
			dprintf(_T("caption is \"%ls\".\n"), (wchar_t*)pTemplateDataIn);
			pTemplateDataIn += wcslen((wchar_t*)pTemplateDataIn) * sizeof(wchar_t) + sizeof(wchar_t);
			break;
	}
	
	// Font
	if (pTemplate->style & (DS_SETFONT | DS_SHELLFONT)) {
		dprintf(_T("   Font: \"%ls\", %i pt.\n"), (wchar_t*)(pTemplateDataIn + 2 + 2 * sizeof(WORD)), *((WORD*)pTemplateDataIn));
		pTemplateDataIn += 2 + 2 * sizeof(WORD);
		pTemplateDataIn += wcslen((wchar_t*)pTemplateDataIn) * sizeof(wchar_t) + sizeof(wchar_t);
	}

	// Controls
	dprintf(_T("   %i controls used.\n"), pTemplate->cDlgItems);
	for (int i = 0; i < pTemplate->cDlgItems; i++) {
		pTemplateDataIn = (char*)(((UINT32)pTemplateDataIn + sizeof(DWORD) - 1) & ~(sizeof(DWORD) - 1));

		dprintf(_T("      control %02i, ID is %05i, pos %03ix%03i, size %03ix%03i\n"), i, ((DLGITEMTEMPLATEEX*)pTemplateDataIn)->id, ((DLGITEMTEMPLATEEX*)pTemplateDataIn)->x, ((DLGITEMTEMPLATEEX*)pTemplateDataIn)->y, ((DLGITEMTEMPLATEEX*)pTemplateDataIn)->cx, ((DLGITEMTEMPLATEEX*)pTemplateDataIn)->cy);

		pTemplateDataIn = (char*)(((UINT32)pTemplateDataIn + sizeof(DLGITEMTEMPLATEEX) + sizeof(WORD) - 1) & ~(sizeof(WORD) - 1));

		dprintf(_T("         "));

		// Class
		switch (*((WORD*)pTemplateDataIn)) {
			case 0x0000:
				pTemplateDataIn += 1 * sizeof(WORD);
				break;
			case 0xFFFF:
				dprintf(_T("class is %04X, "), *((UINT16*)pTemplateDataIn + sizeof(WORD)));
				pTemplateDataIn += 2 * sizeof(WORD);
				break;
			default:
				dprintf(_T("class is \"%ls\", "), (wchar_t*)pTemplateDataIn);
				pTemplateDataIn += wcslen((wchar_t*)pTemplateDataIn) * sizeof(wchar_t) + sizeof(wchar_t);
				break;
		}
		
//		pTemplateDataIn = (char*)(((UINT32)pTemplateDataIn + sizeof(WORD) - 1) & ~(sizeof(WORD) - 1));

		if (*((WORD*)pTemplateDataIn) == 0xFFFF) {
			pTemplateDataIn += 4;
		}

		dprintf(_T("title is \"%ls\".\n"), (wchar_t*)pTemplateDataIn);
		pTemplateDataIn += wcslen((wchar_t*)pTemplateDataIn) * sizeof(wchar_t) + sizeof(wchar_t);
		if (*((WORD*)pTemplateDataIn)) {	
			dprintf(_T("         %i bytes of extra data present.\n"), *((WORD*)pTemplateDataIn));
		}
		pTemplateDataIn += sizeof(WORD) + *((WORD*)pTemplateDataIn);
	}
}

DLGTEMPLATE* TranslateDlgTemplateEx(const DLGTEMPLATEEX* pTemplate)
{
	// 26 is sizeof(DLGTEMPLATEEX)
	char* pTemplateDataIn = (char*)(((UINT32)pTemplate + 26 + sizeof(WORD) - 1) & ~(sizeof(WORD) - 1));
	char* pTemplateDataInSync = NULL;
	char* pTemplateDataOutSync = NULL;

	if (pTemplateDataOut) {
		return (DLGTEMPLATE*)pTemplateDataOut;
	}

	LocaliseResourceInfo* pCurrentResource = FindResourceInfo(0);
	if (pCurrentResource == NULL) {
		return NULL;
	}

	dprintf(_T("Translating dialogex template:\n"));

	pTemplateDataOut = (char*)malloc(26);
	memcpy(pTemplateDataOut, (char*)pTemplate, 26);
	pTemplateDataInSync = pTemplateDataIn;
	pTemplateDataOutSync = pTemplateDataOut + 26;

#if 0
	dprintf(_T("\n"));
	char* pData = (char*)pTemplate;
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				unsigned int n = *pData;
				dprintf(_T("%02X"), n & 255);
				pData++;
			}
			dprintf(_T(" "));
		}
		dprintf(_T("\n"));
	}
	dprintf(_T("\n"));
#endif

	// Menu
	switch (*((WORD*)pTemplateDataIn)) {
		case 0x0000:
			pTemplateDataIn += 1 * sizeof(WORD);
			break;
		case 0xFFFF:
			dprintf(_T("   menu is %04X.\n"), *((UINT16*)pTemplateDataIn + sizeof(WORD)));
			pTemplateDataIn += 2 * sizeof(WORD);
			break;
		default:
			dprintf(_T("   menu is \"%ls\".\n"), (wchar_t*)pTemplateDataIn);
			pTemplateDataIn += wcslen((wchar_t*)pTemplateDataIn) * sizeof(wchar_t) + sizeof(wchar_t);
			break;
	}

//	pTemplateDataIn = (char*)(((UINT32)pTemplateDataIn + sizeof(WORD) - 1) & ~(sizeof(WORD) - 1));

	// Class
	switch (*((WORD*)pTemplateDataIn)) {
		case 0x0000:
			pTemplateDataIn += 1 * sizeof(WORD);
			break;
		case 0xFFFF:
			dprintf(_T("   class is %04X.\n"), *((UINT16*)pTemplateDataIn + sizeof(WORD)));
			pTemplateDataIn += 2 * sizeof(WORD);
			break;
		default:
			dprintf(_T("   class is \"%ls\".\n"), (wchar_t*)pTemplateDataIn);
			pTemplateDataIn += wcslen((wchar_t*)pTemplateDataIn) * sizeof(wchar_t) + sizeof(wchar_t);
			break;
	}

//	pTemplateDataIn = (char*)(((UINT32)pTemplateDataIn + sizeof(WORD) - 1) & ~(sizeof(WORD) - 1));

	// Caption
	dprintf(_T("   "));
	if (*((WORD*)pTemplateDataIn) == 0xFFFF) {
		dprintf(_T("icon is %04X, "), *((UINT16*)pTemplateDataIn + sizeof(WORD)));
		pTemplateDataIn += 2 * sizeof(WORD);
	}
	CATCH_UP;
	if (pCurrentResource->szCaption) {
		ADD_STRING(pCurrentResource->szCaption);
	} else {
		ADD_STRING((wchar_t*)pTemplateDataIn);
	}

	switch (*((WORD*)pTemplateDataIn)) {
		case 0x0000:
			pTemplateDataIn += 1 * sizeof(WORD);
			break;
		default:
			dprintf(_T("caption is \"%ls\".\n"), (wchar_t*)pTemplateDataIn);
			pTemplateDataIn += wcslen((wchar_t*)pTemplateDataIn) * sizeof(wchar_t) + sizeof(wchar_t);
			break;
	}
	pTemplateDataInSync = pTemplateDataIn;
	
	// Font
	if (pTemplate->style & (DS_SETFONT | DS_SHELLFONT)) {
		dprintf(_T("   Font: \"%ls\", %i pt.\n"), (wchar_t*)(pTemplateDataIn + 2 + 2 * sizeof(WORD)), *((WORD*)pTemplateDataIn));
		pTemplateDataIn += 2 + 2 * sizeof(WORD);

#if 0
		CATCH_UP;
		ADD_STRING(L"Times New Roman");
		pTemplateDataIn += wcslen((wchar_t*)pTemplateDataIn) * sizeof(wchar_t) + sizeof(wchar_t);
		pTemplateDataInSync = pTemplateDataIn;
#else
		pTemplateDataIn += wcslen((wchar_t*)pTemplateDataIn) * sizeof(wchar_t) + sizeof(wchar_t);
#endif

	}

	// Controls
	dprintf(_T("   %i controls used.\n"), pTemplate->cDlgItems);
	for (int i = 0; i < pTemplate->cDlgItems; i++) {

		CATCH_UP;
		ALIGN(sizeof(DWORD));

		pTemplateDataIn = pTemplateDataInSync = (char*)(((UINT32)pTemplateDataIn + sizeof(DWORD) - 1) & ~(sizeof(DWORD) - 1));

		dprintf(_T("      control %02i, ID is %05i, pos %03ix%03i, size %03ix%03i\n"), i, ((DLGITEMTEMPLATEEX*)pTemplateDataIn)->id, ((DLGITEMTEMPLATEEX*)pTemplateDataIn)->x, ((DLGITEMTEMPLATEEX*)pTemplateDataIn)->y, ((DLGITEMTEMPLATEEX*)pTemplateDataIn)->cx, ((DLGITEMTEMPLATEEX*)pTemplateDataIn)->cy);

		pTemplateDataIn = (char*)(((UINT32)pTemplateDataIn + sizeof(DLGITEMTEMPLATEEX) + sizeof(WORD) - 1) & ~(sizeof(WORD) - 1));

		dprintf(_T("         "));

		// Class
		switch (*((WORD*)pTemplateDataIn)) {
			case 0x0000:
				pTemplateDataIn += 1 * sizeof(WORD);
				break;
			case 0xFFFF:
				dprintf(_T("class is %04X, "), *((UINT16*)pTemplateDataIn + sizeof(WORD)));
				pTemplateDataIn += 2 * sizeof(WORD);
				break;
			default:
				dprintf(_T("class is \"%ls\", "), (wchar_t*)pTemplateDataIn);
				pTemplateDataIn += wcslen((wchar_t*)pTemplateDataIn) * sizeof(wchar_t) + sizeof(wchar_t);
				break;
		}
		
//		pTemplateDataIn = (char*)(((UINT32)pTemplateDataIn + sizeof(WORD) - 1) & ~(sizeof(WORD) - 1));

		if (*((WORD*)pTemplateDataIn) == 0xFFFF) {
			pTemplateDataIn += 4;
		}

		CATCH_UP;
		if (pCurrentResource->pControlInfo[i] && pCurrentResource->pControlInfo[i]->szCaption) {
			ADD_STRING(pCurrentResource->pControlInfo[i]->szCaption);
		} else {
			ADD_STRING((wchar_t*)pTemplateDataIn);
		}

		dprintf(_T("title is \"%ls\".\n"), (wchar_t*)pTemplateDataIn);
		pTemplateDataIn += wcslen((wchar_t*)pTemplateDataIn) * sizeof(wchar_t) + sizeof(wchar_t);
		pTemplateDataInSync = pTemplateDataIn;
		if (*((WORD*)pTemplateDataIn)) {	
			dprintf(_T("         %i bytes of extra data present.\n"), *((WORD*)pTemplateDataIn));
		}
		pTemplateDataIn += sizeof(WORD) + *((WORD*)pTemplateDataIn);
	}

	CATCH_UP;

	dprintf(_T("Parsing translated template:\n"));

	if (((DLGTEMPLATEEX*)pTemplate)->signature == 0xFFFF) {
		ParseDlgTemplateEx((DLGTEMPLATEEX*)pTemplateDataOut);
	}

	dprintf(_T("Done.\n"));
	
	return (DLGTEMPLATE*)pTemplateDataOut;
}

INT_PTR FBADialogBox(HINSTANCE hInst, LPTSTR pResource, HWND hWnd, DLGPROC pDlgProc)
{
	if (bUseLocalisation) {
		TCHAR szID[1024] = _T("");
		LPCDLGTEMPLATE pTemplateOriginal, pTemplateTranslated;
	
		if ((int)pResource & 0xFFFF0000) {
			_tcscpy(szID, pResource);
		} else {
			_stprintf(szID, _T("#%10i"), (int)pResource);
		}
		pTemplateOriginal = (LPCDLGTEMPLATE)LoadResource(hInst, FindResource(hInst, szID, RT_DIALOG));
		if (LockResource((HGLOBAL)pTemplateOriginal)) {
			if (((DLGTEMPLATEEX*)pTemplateOriginal)->signature == 0xFFFF && ((DLGTEMPLATEEX*)pTemplateOriginal)->dlgVer == 1) {

				// Translate the structure
				pTemplateTranslated = TranslateDlgTemplateEx((DLGTEMPLATEEX*)pTemplateOriginal);

				// Create the dialog and return
				if (pTemplateTranslated) {
					return DialogBoxIndirect(hInst, pTemplateTranslated, hWnd, pDlgProc);
				}
			}
		}
	}

	// Localisation disabled or couldn't lock resource, so use normal function
	return DialogBox(hInst, pResource, hWnd, pDlgProc);
}

MENUTEMPLATE* TranslateMenuTemplate(const  MENUTEMPLATE* pTemplate)
{
	// 26 is sizeof(DLGTEMPLATEEX)
	char* pTemplateDataIn = (char*)pTemplate + sizeof(MENUITEMTEMPLATEHEADER);
	char* pTemplateDataInSync = NULL;
	char* pTemplateDataOutSync = NULL;

//	if (pTemplateDataOut) {
//		return NULL;
//	}

	LocaliseResourceInfo* pCurrentResource = FindResourceInfo(0);
	if (pCurrentResource == NULL) {
		return NULL;
	}

	dprintf(_T("Translating menu template:\n"));

//	pTemplateDataOut = (char*)malloc(sizeof(MENUITEMTEMPLATEHEADER));
//	memcpy(pTemplateDataOut, (char*)pTemplate, sizeof(MENUITEMTEMPLATEHEADER) + ((MENUITEMTEMPLATEHEADER)pTemplate)->offset);
//	pTemplateDataInSync = pTemplateDataIn;
//	pTemplateDataOutSync = pTemplateDataOut + sizeof(MENUITEMTEMPLATEHEADER) + ((MENUITEMTEMPLATEHEADER)pTemplate)->offset;

#if 0
	dprintf(_T("\n"));
	char* pData = (char*)pTemplate;
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				unsigned int n = *pData;
				dprintf(_T("%02X"), n & 255);
				pData++;
			}
			dprintf(_T(" "));
		}
		dprintf(_T("\n"));
	}
	dprintf(_T("\n"));
#endif

	int i = 0;
	bool bLastPopup = false, bLastItem = false;
	do {

//		CATCH_UP;
//		ALIGN(sizeof(DWORD));
//		pTemplateDataIn = pTemplateDataInSync = (char*)(((UINT32)pTemplateDataIn + sizeof(DWORD) - 1) & ~(sizeof(DWORD) - 1));

		if (((MENUITEMTEMPLATE*)pTemplateDataIn)->mtOption & MF_POPUP) {
			bLastPopup = false;
			bLastItem = false;
			if (((MENUITEMTEMPLATE*)pTemplateDataIn)->mtOption & MF_END) {
				bLastPopup = true;
			}
			dprintf(_T("   popup %03i "), i);
			pTemplateDataIn += sizeof(WORD);
		} else {
			if (((MENUITEMTEMPLATE*)pTemplateDataIn)->mtOption & MF_END) {
				bLastItem = true;
			}
			dprintf(_T("   item %03i ID is %05i "), i, ((MENUITEMTEMPLATE*)pTemplateDataIn)->mtID);
			pTemplateDataIn += sizeof(WORD) * 2;
		}

//		pTemplateDataIn = (char*)(((UINT32)pTemplateDataIn + sizeof(DLGITEMTEMPLATEEX) + sizeof(WORD) - 1) & ~(sizeof(WORD) - 1));

//		CATCH_UP;
//		if (pCurrentResource->pControlInfo[i] && pCurrentResource->pControlInfo[i]->szCaption) {
//			ADD_STRING(pCurrentResource->pControlInfo[i]->szCaption);
//		} else {
//			ADD_STRING((wchar_t*)pTemplateDataIn);
//		}

		dprintf(_T("\"%ls\".\n"), ((wchar_t*)pTemplateDataIn));
		pTemplateDataIn += wcslen((wchar_t*)pTemplateDataIn) * sizeof(wchar_t) + sizeof(wchar_t);
		pTemplateDataInSync = pTemplateDataIn;
	} while (i++ < 250 && !(bLastPopup && bLastItem));

//	CATCH_UP;

//	dprintf(_T("Parsing translated template:\n"));
//	ParseDlgTemplateEx((DLGTEMPLATEEX*)pTemplateDataOut);

	dprintf(_T("Done.\n"));
	
	return NULL;

}

HMENU FBALoadMenu(HINSTANCE hInst, LPTSTR pResource)
{
	if (bUseLocalisation) {
		TCHAR szID[1024] = _T("");
		MENUTEMPLATE* pTemplateOriginal;
		MENUTEMPLATE* pTemplateTranslated;
	
		if ((int)pResource & 0xFFFF0000) {
			_tcscpy(szID, pResource);
		} else {
			_stprintf(szID, _T("#%10i"), (int)pResource);
		}
		pTemplateOriginal = (MENUTEMPLATE*)LoadResource(hInst, FindResource(hInst, szID, RT_MENU));
		if (LockResource((HGLOBAL)pTemplateOriginal)) {
			if (((MENUITEMTEMPLATEHEADER*)pTemplateOriginal)->versionNumber == 0) {

				// Translate the structure
				pTemplateTranslated = TranslateMenuTemplate((MENUTEMPLATE*)pTemplateOriginal);

				// Create the dialog and return
				if (pTemplateTranslated) {
					return LoadMenuIndirect(pTemplateDataOut);
				}
			}
		}
	}

	// Localisation disabled or couldn't lock resource, so use normal function
	return LoadMenu(hInst, pResource);
}

static int FBALocaliseParseFile(TCHAR* pszFilename)
{
#define INSIDE_NOTHING (0xFFFF)

	TCHAR szLine[1024];
	TCHAR* s;
	TCHAR* t;
	int nLen;

	int nLine = 0;
	TCHAR nInside = INSIDE_NOTHING;

	LocaliseResourceInfo* pCurrentResource = NULL;

	FILE* h = _tfopen(pszFilename, _T("rb"));
	if (h == NULL) {
		return 1;
	}

	{
		unsigned char szBOM[4] = { 0, };
	
		fread(szBOM, 1, sizeof(szBOM), h);

		// See if it's a UTF-8 file
		if (szBOM[0] == 0xEF && szBOM[1] == 0xBB && szBOM[2] == 0xBF) {
			nFBACodepage = CP_UTF8;
		}

#ifdef _UNICODE
		// See if it's a UTF-16 file
		if (szBOM[0] == 0xFF && szBOM[1] == 0xFE) {
			nFBACodepage = CP_WINUNICODE;

			fseek(h, 2, SEEK_SET);
		}
#endif

	}

	if (nFBACodepage != CP_WINUNICODE) {
		fclose(h);
		h = _tfopen(pszFilename, _T("rt"));
		if (h == NULL) {
			return 1;
		}
		
		if (nFBACodepage == CP_UTF8) {
			fseek(h, 3, SEEK_SET);
		}
		
	}

	while (1) {

#ifdef _UNICODE
		char szTemp[1024];

		if (nFBACodepage != CP_WINUNICODE) {
			if (fgets(szTemp, sizeof(szTemp), h) == NULL) {
				break;
			}
			MultiByteToWideChar(nFBACodepage, 0, szTemp, -1, szLine, sizeof(szLine) / sizeof(TCHAR));
		} else {
#endif

			if (_fgetts(szLine, sizeof(szLine), h) == NULL) {
				break;
			}

#ifdef _UNICODE
		}
#endif

		nLine++;

		nLen = _tcslen(szLine);
		// Get rid of the linefeed at the end
		while (szLine[nLen - 1] == 0x0A || szLine[nLen - 1] == 0x0D) {
			szLine[nLen - 1] = 0;
			nLen--;
		}

		s = szLine;													// Start parsing

		if (s[0] == _T('/') && s[1] == _T('/')) {					// Comment
			continue;
		}


		if ((t = LabelCheck(s, _T("codepage"))) != 0) {				// Set codepage
			s = t;

			SKIP_WS(s);

			nFBACodepage = _tcstol(s, &t, 0);
			
			s = t;

			continue;
		}


		if ((t = LabelCheck(s, _T("resource"))) != 0) {				// Add new cheat
			s = t;

			SKIP_WS(s);

			int nID = _tcstol(s, &t, 0);
			s = t;

			// Read cheat name
			TCHAR* szQuote = NULL;
			TCHAR* szEnd = NULL;

			QuoteRead(&szQuote, &szEnd, s);

			s = szEnd;

			SKIP_WS(s);

			if (nInside == _T('{')) {
//				CheatError(pszFilename, nLine, pCurrentCheat, _T("missing closing bracket"), NULL);
				break;
			}

			nInside = *s;

//			// Link new node into the list
//			CheatInfo* pPreviousCheat = pCurrentCheat;
			pCurrentResource = (LocaliseResourceInfo*)malloc(sizeof(LocaliseResourceInfo));
			if (FBALocaliseInfo == NULL) {
				FBALocaliseInfo = pCurrentResource;
			}

			memset(pCurrentResource, 0, sizeof(LocaliseResourceInfo));
//			pCurrentCheat->pPrevious = pPreviousCheat;
//			if (pPreviousCheat) {
//				pPreviousCheat->pNext = pCurrentCheat;
//			}

			pCurrentResource->nID = nID;

#ifdef _UNICODE
			memcpy(pCurrentResource->szCaption, szQuote, QUOTE_MAX * sizeof(TCHAR));
#else
			MultiByteToWideChar(nFBACodepage, 0, szQuote, -1, pCurrentResource->szCaption, QUOTE_MAX * sizeof(wchar_t));
#endif

			continue;
		}

		int n = _tcstol(s, &t, 0);
		if (t != s) {				   								// New control

			if (nInside == INSIDE_NOTHING || pCurrentResource == NULL) {
//				CheatError(pszFilename, nLine, pCurrentCheat, _T("rogue option"), szLine);
				break;
			}

			// Link a new control info structure
			if (n < 256) {
				s = t;

				// Read option name
				TCHAR* szQuote = NULL;
				TCHAR* szEnd = NULL;
				if (QuoteRead(&szQuote, &szEnd, s)) {
//					CheatError(pszFilename, nLine, pCurrentCheat, _T("option name omitted"), szLine);
					break;
				}
				s = szEnd;

				if (pCurrentResource->pControlInfo[n] == NULL) {
					pCurrentResource->pControlInfo[n] = (LocaliseControlInfo*)malloc(sizeof(LocaliseControlInfo));
				}
				memset(pCurrentResource->pControlInfo[n], 0, sizeof(LocaliseControlInfo));

#ifdef _UNICODE
				memcpy(pCurrentResource->pControlInfo[n]->szCaption, szQuote, QUOTE_MAX * sizeof(TCHAR));
#else
				MultiByteToWideChar(CP_ACP, 0, szQuote, -1, pCurrentResource->pControlInfo[n]->szCaption, QUOTE_MAX * sizeof(wchar_t));
#endif

			}

			continue;
		}

		SKIP_WS(s);
		if (*s == _T('}')) {
			if (nInside != _T('{')) {
//				CheatError(pszFilename, nLine, pCurrentCheat, _T("missing opening bracket"), NULL);
				break;
			}

			nInside = INSIDE_NOTHING;
		}

		// Line isn't (part of) a valid cheat
#if 0
		if (*s) {
			CheatError(pszFilename, nLine, NULL, _T("rogue line"), szLine);
			break;
		}
#endif

	}

	if (h) {
		fclose(h);
	}

	return 0;
	
#undef INSIDE_NOTHING

}

void FBALocaliseExit()
{
	bUseLocalisation = false;

	if (FBALocaliseInfo) {
		LocaliseResourceInfo* pCurrentResource = FBALocaliseInfo;
		LocaliseResourceInfo* pNextResource = NULL;
		do {
			for (int i = 0; i < 255; i++) {
				free(pCurrentResource->pControlInfo[i]);
			}
			free(pCurrentResource);
		} while ((pCurrentResource = pNextResource) != 0);
	}

	FBALocaliseInfo = NULL;

	return;
}

int FBALocaliseInit()
{
	bUseLocalisation = false;
	nFBACodepage = GetACP();

	TCHAR szFilename[MAX_PATH] = _T("");

#if 0
	_stprintf(szFilename, _T("config\\language\\dutch.txt"));
	if (FBALocaliseParseFile(szFilename)) {
		return 1;
	}
#endif

	if (FBALocaliseInfo) {
		bUseLocalisation = true;
	}

	return 0;
}

