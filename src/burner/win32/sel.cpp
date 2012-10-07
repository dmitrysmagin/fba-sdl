// Driver Selector module
// TreeView Version by HyperYagami

#include "burner.h"
#include "png.h"

// Disable selecting non-available sets
#define DISABLE_NON_AVAILABLE_SELECT 0
// Preview directory
#define PREVIEW_DIRECTORY _T("previews\\")
// Prompt user on loading non-working sets
#define NON_WORKING_PROMPT_ON_LOAD 1

static HWND hSelDlg = NULL;
static HWND hSelList = NULL;
static int nDialogSelect = -1;									// The driver which this dialog selected

static HBITMAP hBmp = NULL;
static HBITMAP hPreview = NULL;
static HWND hInfoLabel[4] = { NULL, NULL, NULL, NULL };			// 4 things in our Info-box
static HWND hInfoText[4] = {NULL, NULL, NULL, NULL};			// 4 things in our Info-box

static HBRUSH hWhiteBGBrush;

static HICON hExpand, hCollapse;
static HICON hNotWorking, hNotFoundEss, hNotFoundNonEss;

static char TreeBuilding = 0;									// if 1, ignore TVN_SELCHANGED messages

#define MASKCPS		(1 << (HARDWARE_PREFIX_CAPCOM	>> 24))
#define MASKNEOGEO	(1 << (HARDWARE_PREFIX_SNK		>> 24))
#define MASKSEGA	(1 << (HARDWARE_PREFIX_SEGA		>> 24))
#define MASKTOAPLAN (1 << (HARDWARE_PREFIX_TOAPLAN	>> 24))
#define MASKCAVE	(1 << (HARDWARE_PREFIX_CAVE		>> 24))
#define MASKMISC	(1 << (HARDWARE_PREFIX_MISC		>> 24))
#define MASKALL		(MASKCPS | MASKNEOGEO | MASKSEGA | MASKTOAPLAN | MASKCAVE)

#define SHOWSHORT	(1 << 16)

int bLoadMenuAutoExpand = 0;
int nLoadMenuShowX = 0;

static int bImageOrientation;

UINT_PTR nTimer = 0;

struct NODEINFO {
	int nBurnDrvNo;
	bool bIsParent;
	char* pszROMName;
	HTREEITEM hTreeHandle;
};

static NODEINFO* nBurnDrv;
static unsigned int nTmpDrvCount;

// Check if a specified driver is working
static bool CheckWorkingStatus(int nDriver)
{
	int nOldnBurnDrvSelect = nBurnDrvSelect;
	nBurnDrvSelect = nDriver;
	bool bStatus = BurnDrvIsWorking();
	nBurnDrvSelect = nOldnBurnDrvSelect;

	return bStatus;
}

static TCHAR* MangleGamename(const TCHAR* szOldName, bool bRemoveArticle)
{
	static TCHAR szNewName[256] = _T("");

	TCHAR* pszName = szNewName;

	if (_tcsnicmp(szOldName, _T("the "), 4) == 0) {
		int x = 0, y = 0;
		while (szOldName[x] && szOldName[x] != _T('(') && szOldName[x] != _T('-')) {
			x++;
		}
		y = x;
		while (y && szOldName[y - 1] == _T(' ')) {
			y--;
		}
		_tcsncpy(pszName, szOldName + 4, y - 4);
		pszName[y - 4] = _T('\0');
		pszName += y - 4;

		if (!bRemoveArticle) {
			pszName += _stprintf(pszName, _T(", the"));
		}
		if (szOldName[x]) {
			_stprintf(pszName, _T(" %s"), szOldName + x);
		}
	} else {
		_tcscpy(pszName, szOldName);
	}

	return szNewName;
}

// Make a tree-view control with all drivers
static int SelListMake()
{
	unsigned int i, j;

	free(nBurnDrv);
	nBurnDrv = (NODEINFO*)malloc(nBurnDrvCount * sizeof(NODEINFO));
	memset(nBurnDrv, 0, nBurnDrvCount * sizeof(NODEINFO));

	nTmpDrvCount = 0;

	if (hSelList == NULL) {
		return 1;
	}

	// Add all the driver names to the list

	// 1st: parents
	for (i = 0; i < nBurnDrvCount; i++) {
		TV_INSERTSTRUCT TvItem;

		nBurnDrvSelect = i;													// Switch to driver i

		if (BurnDrvGetFlags() & BDF_BOARDROM) {
			continue;
		}
		if (BurnDrvGetText(DRV_PARENT) != NULL && (BurnDrvGetFlags() & BDF_CLONE)) {	// Skip clones
			continue;
		}
		if (avOk && bAvbOnly && !gameAv[i])	{								// Skip non-available games if needed
			continue;
		}

		int nHardware = 1 << (BurnDrvGetHardwareCode() >> 24);
		if ((nHardware & MASKALL) && (nHardware & nLoadMenuShowX) || ((nHardware & MASKALL) == 0) && (nLoadMenuShowX & (1 << (HARDWARE_PREFIX_MISC >> 8)))) {
			continue;
		}

		memset(&TvItem, 0, sizeof(TvItem));
		TvItem.item.mask = TVIF_TEXT | TVIF_PARAM;
		TvItem.hInsertAfter = TVI_SORT;
		TvItem.item.pszText = (nLoadMenuShowX & SHOWSHORT) ? BurnDrvGetText(DRV_NAME) : MangleGamename(BurnDrvGetText(DRV_ASCIIONLY | DRV_FULLNAME), true);
		TvItem.item.lParam = (LPARAM)&nBurnDrv[nTmpDrvCount];
		nBurnDrv[nTmpDrvCount].hTreeHandle = (HTREEITEM)SendMessage(hSelList, TVM_INSERTITEM, 0, (LPARAM)&TvItem);
		nBurnDrv[nTmpDrvCount].nBurnDrvNo = i;
		nBurnDrv[nTmpDrvCount].pszROMName = BurnDrvGetTextA(DRV_NAME);
		nBurnDrv[nTmpDrvCount].bIsParent = true;
		nTmpDrvCount++;
	}

	// 2nd: clones
	for (i = 0; i < nBurnDrvCount; i++) {
		TV_INSERTSTRUCT TvItem;

		nBurnDrvSelect = i;													// Switch to driver i

		if (BurnDrvGetFlags() & BDF_BOARDROM) {
			continue;
		}

		if (BurnDrvGetTextA(DRV_PARENT) == NULL || !(BurnDrvGetFlags() & BDF_CLONE)) {	// Skip parents
			continue;
		}
		if (avOk && bAvbOnly && !gameAv[i])	{								// Skip non-available games if needed
			continue;
		}

		int nHardware = 1 << (BurnDrvGetHardwareCode() >> 24);
		if ((nHardware & MASKALL) && (nHardware & nLoadMenuShowX) || ((nHardware & MASKALL) == 0) && (nLoadMenuShowX & (1 << (HARDWARE_PREFIX_MISC >> 8)))) {
			continue;
		}

		memset(&TvItem, 0, sizeof(TvItem));
		TvItem.item.mask = TVIF_TEXT | TVIF_PARAM;
		TvItem.hInsertAfter = TVI_SORT;
		TvItem.item.pszText = (nLoadMenuShowX & SHOWSHORT) ? BurnDrvGetText(DRV_NAME) : MangleGamename(BurnDrvGetText(DRV_ASCIIONLY | DRV_FULLNAME), true);

		// Find the parent's handle
		for (j = 0; j < nTmpDrvCount; j++) {
			if (nBurnDrv[j].bIsParent) {
				if (!_stricmp(BurnDrvGetTextA(DRV_PARENT), nBurnDrv[j].pszROMName)) {
					TvItem.hParent = nBurnDrv[j].hTreeHandle;
					break;
				}
			}
		}

		// Find the parent and add a branch to the tree
		if (!TvItem.hParent) {
			char szTempName[9];
			strcpy(szTempName, BurnDrvGetTextA(DRV_PARENT));
			int nTempBurnDrvSelect = nBurnDrvSelect;
			for (j = 0; j < nBurnDrvCount; j++) {
				nBurnDrvSelect = j;
				if (!strcmp(szTempName, BurnDrvGetTextA(DRV_NAME))) {
					TV_INSERTSTRUCT TempTvItem;
					memset(&TempTvItem, 0, sizeof(TempTvItem));
					TempTvItem.item.mask = TVIF_TEXT | TVIF_PARAM;
					TempTvItem.hInsertAfter = TVI_SORT;
					TempTvItem.item.pszText = (nLoadMenuShowX & SHOWSHORT) ? BurnDrvGetText(DRV_NAME) : MangleGamename(BurnDrvGetText(DRV_ASCIIONLY | DRV_FULLNAME), true);
					TempTvItem.item.lParam = (LPARAM)&nBurnDrv[nTmpDrvCount];
					nBurnDrv[nTmpDrvCount].hTreeHandle = (HTREEITEM)SendMessage(hSelList, TVM_INSERTITEM, 0, (LPARAM)&TempTvItem);
					nBurnDrv[nTmpDrvCount].nBurnDrvNo = j;
					nBurnDrv[nTmpDrvCount].bIsParent = true;
					nBurnDrv[nTmpDrvCount].pszROMName = BurnDrvGetTextA(DRV_NAME);
					TvItem.item.lParam = (LPARAM)&nBurnDrv[nTmpDrvCount];
					TvItem.hParent = nBurnDrv[nTmpDrvCount].hTreeHandle;
					nTmpDrvCount++;
					break;
				}
			}
			nBurnDrvSelect = nTempBurnDrvSelect;
		}

		TvItem.item.lParam = (LPARAM)&nBurnDrv[nTmpDrvCount];
		nBurnDrv[nTmpDrvCount].hTreeHandle = (HTREEITEM)SendMessage(hSelList, TVM_INSERTITEM, 0, (LPARAM)&TvItem);
		nBurnDrv[nTmpDrvCount].pszROMName = BurnDrvGetTextA(DRV_NAME);
		nBurnDrv[nTmpDrvCount].nBurnDrvNo = i;
		nTmpDrvCount++;
	}

	for (i = 0; i < nTmpDrvCount; i++) {

		// See if we need to expand the branch of an unavailable or non-working parent
		if (nBurnDrv[i].bIsParent && (bLoadMenuAutoExpand || !gameAv[nBurnDrv[i].nBurnDrvNo] || !CheckWorkingStatus(nBurnDrv[i].nBurnDrvNo))) {
			for (j = 0; j < nTmpDrvCount; j++) {

				// Expand the branch only if a working clone is available
				if (gameAv[nBurnDrv[j].nBurnDrvNo]) {
					nBurnDrvSelect = nBurnDrv[j].nBurnDrvNo;
					if (BurnDrvGetTextA(DRV_PARENT)) {
						if (strcmp(nBurnDrv[i].pszROMName, BurnDrvGetTextA(DRV_PARENT)) == 0) {
							SendMessage(hSelList, TVM_EXPAND,TVE_EXPAND, (LPARAM)nBurnDrv[i].hTreeHandle);
							break;
						}
					}
				}
			}
		}
	}

	return 0;
}

static void MyEndDialog()
{
	if (nTimer) {
		KillTimer(hSelDlg, nTimer);
		nTimer = 0;
	}

	SendDlgItemMessage(hSelDlg, IDC_SCREENSHOT_H, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)NULL);
	SendDlgItemMessage(hSelDlg, IDC_SCREENSHOT_V, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)NULL);

	if (hBmp) {
		DeleteObject((HGDIOBJ)hBmp);
		hBmp = NULL;
	}
	if (hPreview) {
		DeleteObject((HGDIOBJ)hPreview);
		hPreview = NULL;
	}

	if (hExpand) {
		DestroyIcon(hExpand);
		hExpand = NULL;
	}
	if (hCollapse) {
		DestroyIcon(hCollapse);
		hCollapse = NULL;
	}
	if (hNotWorking) {
		DestroyIcon(hNotWorking);
		hNotWorking = NULL;
	}
	if (hNotFoundEss) {
		DestroyIcon(hNotFoundEss);
		hNotFoundEss = NULL;
	}
	if (hNotFoundNonEss) {
		DestroyIcon(hNotFoundNonEss);
		hNotFoundNonEss = NULL;
	}

	EndDialog(hSelDlg, 0);
}

// User clicked ok for a driver in the list
static void SelOkay()
{
	TV_ITEM TvItem;
	unsigned int nSelect = 0;
	HTREEITEM hSelectHandle = (HTREEITEM)SendMessage(hSelList, TVM_GETNEXTITEM, TVGN_CARET, ~0U);

	if (!hSelectHandle)	{			// Nothing is selected, return without closing the window
		return;
	}

	TvItem.hItem = hSelectHandle;
	TvItem.mask = TVIF_PARAM;
	SendMessage(hSelList, TVM_GETITEM, 0, (LPARAM)&TvItem);
	nSelect = ((NODEINFO*)TvItem.lParam)->nBurnDrvNo;

#if DISABLE_NON_AVAILABLE_SELECT
	if (!gameAv[nSelect]) {			// Game not available, return without closing the window
		return;
	}
#endif

#if NON_WORKING_PROMPT_ON_LOAD
	if (!CheckWorkingStatus(nSelect)) {
		if (MessageBox(hSelDlg, _T("This game isn't working. Load it anyway?"), _T("Warning!"), MB_YESNO | MB_DEFBUTTON2 | MB_ICONWARNING) == IDNO) {
			return;
		}
	}
#endif

	nDialogSelect = nSelect;
	MyEndDialog();
}

static void RefreshPanel()
{
	// clear preview shot
	if (hBmp) {
		DeleteObject((HGDIOBJ)hBmp);
		hBmp = NULL;
	}
	if (nTimer) {
		KillTimer(hSelDlg, nTimer);
		nTimer = 0;
	}

	SendDlgItemMessage(hSelDlg, IDC_SCREENSHOT_H, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hPreview);
	SendDlgItemMessage(hSelDlg, IDC_SCREENSHOT_V, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)NULL);

	// Clear the things in our Info-box
	for (int i = 0; i < 4; i++) {
		SendMessage(hInfoText[i], WM_SETTEXT, (WPARAM)0, (LPARAM)_T(""));
		EnableWindow(hInfoLabel[i], FALSE);
	}

	CheckDlgButton(hSelDlg, IDC_CHECKCPS, nLoadMenuShowX & MASKCPS ? BST_UNCHECKED : BST_CHECKED);
	CheckDlgButton(hSelDlg, IDC_CHECKNEOGEO, nLoadMenuShowX & MASKNEOGEO ? BST_UNCHECKED : BST_CHECKED);
	CheckDlgButton(hSelDlg, IDC_CHECKSEGA, nLoadMenuShowX & MASKSEGA ? BST_UNCHECKED : BST_CHECKED);
	CheckDlgButton(hSelDlg, IDC_CHECKTOAPLAN, nLoadMenuShowX & MASKTOAPLAN ? BST_UNCHECKED : BST_CHECKED);
	CheckDlgButton(hSelDlg, IDC_CHECKCAVE, nLoadMenuShowX & MASKCAVE ? BST_UNCHECKED : BST_CHECKED);
	CheckDlgButton(hSelDlg, IDC_CHECKMISC, nLoadMenuShowX & MASKMISC ? BST_UNCHECKED : BST_CHECKED);

	CheckDlgButton(hSelDlg, IDC_CHECKAUTOEXPAND, bLoadMenuAutoExpand ? BST_CHECKED : BST_UNCHECKED);
	CheckDlgButton(hSelDlg, IDC_CHECKAVAILABLEONLY, bAvbOnly ? BST_CHECKED : BST_UNCHECKED);

	CheckDlgButton(hSelDlg, IDC_SEL_SHORTNAME, nLoadMenuShowX & SHOWSHORT ? BST_CHECKED : BST_UNCHECKED);
};

static void RebuildEverything()
{
	RefreshPanel();

	TreeBuilding = 1;
	SendMessage(hSelList, WM_SETREDRAW, (WPARAM)FALSE,(LPARAM)TVI_ROOT);	// disable redraw
	SendMessage(hSelList, TVM_DELETEITEM, 0, (LPARAM)TVI_ROOT);				// Destory all nodes
	SelListMake();
	SendMessage(hSelList, WM_SETREDRAW, (WPARAM)TRUE, (LPARAM)TVI_ROOT);	// enable redraw

	// Clear the things in our Info-box
	for (int i = 0; i < 4; i++) {
		SendMessage(hInfoText[i], WM_SETTEXT, (WPARAM)0, (LPARAM)_T(""));
		EnableWindow(hInfoLabel[i], FALSE);
	}

	TreeBuilding = 0;
}

#define PNG_SIG_CHECK_BYTES 8
#define PNG_XSIZE_HORI 160
#define PNG_YSIZE_HORI 120
#define PNG_XSIZE_VERT PNG_YSIZE_HORI
#define PNG_YSIZE_VERT PNG_XSIZE_HORI

typedef struct tagIMAGE {
	LONG    width;
	LONG    height;
	DWORD   rowbytes;
	DWORD   imgbytes;
	BYTE**	rowptr;
	BYTE*	bmpbits;
} IMAGE;

static void img_free(IMAGE* img)
{
	free(img->rowptr);
	free(img->bmpbits);
}

static int img_alloc(IMAGE* img)
{
	img->rowbytes = ((DWORD)img->width * 24 + 31) / 32 * 4;
	img->imgbytes = img->rowbytes * img->height;
	img->rowptr = (BYTE**)malloc((size_t)img->height * sizeof(BYTE*));
	img->bmpbits = (BYTE*)malloc((size_t)img->imgbytes);

	if (img->rowptr == NULL || img->bmpbits == NULL) {
		img_free(img);
		return 0;
	}

	for (int y = 0; y < img->height; y++) {
		img->rowptr[img->height - y - 1] = img->bmpbits + y * img->rowbytes;
	}

	return 1;
}

// Resize the image to the required size using point filtering
static int img_resize(IMAGE* img)
{
	IMAGE new_img;

	memset(&new_img, 0, sizeof(IMAGE));
	new_img.width = bImageOrientation ? 120 : 160;
	new_img.height = bImageOrientation ? 160 : 120;
	img_alloc(&new_img);

	for (int y = 0; y < new_img.height; y++) {
		int row = img->height * y / new_img.height;
		for (int x = 0; x < new_img.width; x++) {
			new_img.rowptr[y][x * 3 + 0] = img->rowptr[row][img->width * x / new_img.width * 3 + 0];
			new_img.rowptr[y][x * 3 + 1] = img->rowptr[row][img->width * x / new_img.width * 3 + 1];
			new_img.rowptr[y][x * 3 + 2] = img->rowptr[row][img->width * x / new_img.width * 3 + 2];
		}
	}

	img_free(img);

	memcpy(img, &new_img, sizeof(IMAGE));

	return 0;
}

static HBITMAP LoadPNG(HWND hDlg, FILE* fp)
{
	IMAGE img;
	png_uint_32 width, height;
	int bit_depth, color_type;

	// check signature
	unsigned char pngsig[PNG_SIG_CHECK_BYTES];
	fread(pngsig, 1, PNG_SIG_CHECK_BYTES, fp);
	if (png_sig_cmp(pngsig, 0, PNG_SIG_CHECK_BYTES)) {
		return 0;
	}

	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr) {
		return 0;
	}

	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
		return 0;
	}

	memset(&img, 0, sizeof(IMAGE));
	png_init_io(png_ptr, fp);
	png_set_sig_bytes(png_ptr, PNG_SIG_CHECK_BYTES);
	png_read_info(png_ptr, info_ptr);
	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, NULL, NULL, NULL);

	if (setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
		return 0;
	}

	if (width > 1024 || height > 1024) {
		longjmp(png_ptr->jmpbuf, 1);
	}

	// Instruct libpng to convert the image to 24-bit RGB format
	if (color_type == PNG_COLOR_TYPE_PALETTE) {
		png_set_palette_to_rgb(png_ptr);
	}
	if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
		png_set_gray_to_rgb(png_ptr);
	}
	if (bit_depth == 16) {
		png_set_strip_16(png_ptr);
	}
	if (color_type & PNG_COLOR_MASK_ALPHA) {
		png_set_strip_alpha(png_ptr);
	}

	// We need the image to be either 160x120x24 or 120x160x24
	img.width = (LONG)width;
	img.height = (LONG)height;

	// Initialize our img structure
	if (!img_alloc(&img)) {
		longjmp(png_ptr->jmpbuf, 1);
	}

	if (img.width > img.height) {
		bImageOrientation = 0;
	} else {
		bImageOrientation = 1;
	}

	// If bad things happen in libpng we need to do img_free(&img) as well
	if (setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
		img_free(&img);
		return 0;
	}

	// Read the .PNG image
	png_set_bgr(png_ptr);
	png_read_update_info(png_ptr, info_ptr);
	png_read_image(png_ptr, img.rowptr);
	png_read_end(png_ptr, (png_infop)NULL);
	png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);

	if (!((img.width == PNG_XSIZE_HORI && img.height == PNG_YSIZE_HORI) || (img.width == PNG_XSIZE_VERT && img.height == PNG_YSIZE_VERT))) {
		if (img_resize(&img)) {
			img_free(&img);
			return 0;
		}
	}

	// Create a bitmap for the image
	BITMAPINFO* bi = (BITMAPINFO*)LocalAlloc(LPTR, sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD));
	if (bi == NULL) {
		img_free(&img);
		return 0;
	}

	bi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi->bmiHeader.biWidth = img.width;
	bi->bmiHeader.biHeight = img.height;
	bi->bmiHeader.biPlanes = 1;
	bi->bmiHeader.biBitCount = 24;
	bi->bmiHeader.biCompression = BI_RGB;
	bi->bmiHeader.biSizeImage = img.imgbytes;
	bi->bmiHeader.biXPelsPerMeter = 0;
	bi->bmiHeader.biYPelsPerMeter = 0;
	bi->bmiHeader.biClrUsed = 0;
	bi->bmiHeader.biClrImportant = 0;

	HDC hDC = GetDC(hDlg);
	BYTE* pBits = NULL;
	HBITMAP hNewBmp = CreateDIBSection(hDC, (BITMAPINFO*)bi, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);
	if (pBits) {
		memcpy(pBits, img.bmpbits, img.imgbytes);
	}
	ReleaseDC(hDlg, hDC);
	LocalFree(bi);
	img_free(&img);

	return hNewBmp;
}

static int UpdatePreview(bool bReset)
{
	static int nIndex;
	int nOldIndex;

	TCHAR szBaseName[MAX_PATH];
	TCHAR szFileName[MAX_PATH];

	FILE* fp = NULL;
	HBITMAP hNewImage = NULL;

	nOldIndex = nIndex;
	nIndex++;
	if (bReset) {
		nIndex = 1;
		nOldIndex = -1;
		if (hBmp) {
			DeleteObject((HGDIOBJ)hBmp);
			hBmp = NULL;
		}
		if (nTimer) {
			KillTimer(hSelDlg, nTimer);
			nTimer = 0;
		}
	}

	nBurnDrvSelect = nDialogSelect;

	do {
		// Try to load a .PNG preview image
		_tcscpy(szBaseName, PREVIEW_DIRECTORY);
		_tcscat(szBaseName, BurnDrvGetText(DRV_NAME));
		if (nIndex == 1) {
			_stprintf(szFileName, _T("%s.png"), szBaseName);
			fp = _tfopen(szFileName, _T("rb"));
		}
		if (!fp) {
			_stprintf(szFileName, _T("%s-p%02i.png"), szBaseName, nIndex);
			fp = _tfopen(szFileName, _T("rb"));
		}

		if (!fp && BurnDrvGetText(DRV_PARENT)) {						// Try the parent
			_tcscpy(szBaseName, PREVIEW_DIRECTORY);
			_tcscat(szBaseName, BurnDrvGetText(DRV_PARENT));
			if (nIndex == 1) {
				_stprintf(szFileName, _T("%s.png"), szBaseName);
				fp = _tfopen(szFileName, _T("rb"));
			}
			if (!fp) {
				_stprintf(szFileName, _T("%s-p%02i.png"), szBaseName, nIndex);
				fp = _tfopen(szFileName, _T("rb"));
			}
		}
		
		if (nIndex == 1) {
			break;
		}

		if (!fp) {
			nIndex = 1;
		}

	} while (!fp);

	if (fp && nIndex != nOldIndex) {
		hNewImage = LoadPNG(hSelDlg, fp);
		fclose(fp);
	}

	if (hNewImage) {												// Show the preview image
		DeleteObject((HGDIOBJ)hBmp);
		hBmp = hNewImage;

		if (bImageOrientation == 0) {
			SendDlgItemMessage(hSelDlg, IDC_SCREENSHOT_H, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBmp);
			SendDlgItemMessage(hSelDlg, IDC_SCREENSHOT_V, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)NULL);
		} else {
			SendDlgItemMessage(hSelDlg, IDC_SCREENSHOT_H, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)NULL);
			SendDlgItemMessage(hSelDlg, IDC_SCREENSHOT_V, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBmp);
		}

		nTimer = SetTimer(hSelDlg, 1, 2500, NULL);
	} else {

		// We couldn't load a new image for this game, so kill the timer (it will be restarted when a new game is selected)
		if (nTimer) {
			KillTimer(hSelDlg, nTimer);
			nTimer = 0;
		}

		if (!hBmp) {
			SendDlgItemMessage(hSelDlg, IDC_SCREENSHOT_H, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hPreview);
			SendDlgItemMessage(hSelDlg, IDC_SCREENSHOT_V, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)NULL);
		}
	}
	
	return 0;
}

static BOOL CALLBACK DialogProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	if (Msg == WM_INITDIALOG) {

		TCHAR szOldTitle[1024] = _T("");;
		TCHAR szNewTitle[1024] = _T("");;

		hSelDlg = hDlg;

		SendDlgItemMessage(hDlg, IDC_SCREENSHOT_H, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)NULL);
		SendDlgItemMessage(hDlg, IDC_SCREENSHOT_V, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)NULL);

		hWhiteBGBrush = CreateSolidBrush(RGB(0xFF,0xFF,0xFF));
		hPreview = LoadBitmap(hAppInst, MAKEINTRESOURCE(BMP_PREVIEW));

		hExpand = (HICON)LoadImage(hAppInst, MAKEINTRESOURCE(IDI_TV_PLUS), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
		hCollapse = (HICON)LoadImage(hAppInst, MAKEINTRESOURCE(IDI_TV_MINUS), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);

		hNotWorking = (HICON)LoadImage(hAppInst, MAKEINTRESOURCE(IDI_TV_NOTWORKING), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
		hNotFoundEss = (HICON)LoadImage(hAppInst, MAKEINTRESOURCE(IDI_TV_NOTFOUND_ESS), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
		hNotFoundNonEss = (HICON)LoadImage(hAppInst, MAKEINTRESOURCE(IDI_TV_NOTFOUND_NON), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);

		GetWindowText(hSelDlg, szOldTitle, 1024);
		_sntprintf(szNewTitle, 1024, _T(APP_TITLE) _T(SEPERATOR_1) _T("%s"), szOldTitle);
		SetWindowText(hSelDlg, szNewTitle);
		
		hSelList = GetDlgItem(hSelDlg, IDC_TREE1);
		hInfoLabel[0] = GetDlgItem(hSelDlg, IDC_LABELROMNAME);
		hInfoLabel[1] = GetDlgItem(hSelDlg, IDC_LABELROMINFO);
		hInfoLabel[2] = GetDlgItem(hSelDlg, IDC_LABELSYSTEM);
		hInfoLabel[3] = GetDlgItem(hSelDlg, IDC_LABELCOMMENT);
		hInfoText[0] = GetDlgItem(hSelDlg, IDC_TEXTROMNAME);
		hInfoText[1] = GetDlgItem(hSelDlg, IDC_TEXTROMINFO);
		hInfoText[2] = GetDlgItem(hSelDlg, IDC_TEXTSYSTEM);
		hInfoText[3] = GetDlgItem(hSelDlg, IDC_TEXTCOMMENT);

#if 0 && !defined FBA_DEBUG
		EnableWindow(GetDlgItem(hDlg, IDC_CHECKSEGA), FALSE);
#endif

		bool bFoundROMs = false;
		for (unsigned int i = 0; i < nBurnDrvCount; i++) {
			if (gameAv[i]) {
				bFoundROMs = true;
				break;
			}
		}
		if (!bFoundROMs) {
			RomsDirCreate();
		}

		RebuildEverything();

		if (nDialogSelect > -1) {
			for (unsigned int i = 0; i < nTmpDrvCount; i++) {
				if (nBurnDrv[i].nBurnDrvNo == nDialogSelect) {
					SendMessage(hSelList, TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)nBurnDrv[i].hTreeHandle);
					break;
				}
			}

			SendMessage(hDlg, WM_NEXTDLGCTL, (WPARAM)hSelList, TRUE);
		}

		WndInMid(hDlg, hScrnWnd);

		return TRUE;
	}

	if (Msg == WM_COMMAND) {
		if (HIWORD(wParam) == BN_CLICKED) {
			int wID = LOWORD(wParam);
			switch (wID) {
				case IDOK:
					SelOkay();
					break;
				case IDROM:
					RomsDirCreate();
					RebuildEverything();
					break;
				case IDRESCAN:
					bRescanRoms = true;
					CreateROMInfo();
					RebuildEverything();
					break;
				case IDCANCEL:
					SendMessage(hDlg, WM_CLOSE, 0, 0);
					return 0;

				case IDC_CHECKCPS:
					nLoadMenuShowX ^= MASKCPS;
					RebuildEverything();
					break;
				case IDC_CHECKNEOGEO:
					nLoadMenuShowX ^= MASKNEOGEO;
					RebuildEverything();
					break;
				case IDC_CHECKSEGA:
					nLoadMenuShowX ^= MASKSEGA;
					RebuildEverything();
					break;
				case IDC_CHECKTOAPLAN:
					nLoadMenuShowX ^= MASKTOAPLAN;
					RebuildEverything();
					break;
				case IDC_CHECKCAVE:
					nLoadMenuShowX ^= MASKCAVE;
					RebuildEverything();
					break;
				case IDC_CHECKMISC:
					nLoadMenuShowX ^= MASKMISC;
					RebuildEverything();
					break;

				case IDC_CHECKAVAILABLEONLY:
					bAvbOnly = !bAvbOnly;
					RebuildEverything();
					break;
				case IDC_CHECKAUTOEXPAND:
					bLoadMenuAutoExpand = !bLoadMenuAutoExpand;
					RebuildEverything();
					break;

				case IDC_SEL_SHORTNAME:
					nLoadMenuShowX ^= SHOWSHORT;
					RebuildEverything();
					break;
			}
		}
	}

	if (Msg == WM_CLOSE) {
		nDialogSelect = -1;
		MyEndDialog();
		DeleteObject(hWhiteBGBrush);
		return 0;
	}

	if (Msg == WM_TIMER) {
		UpdatePreview(false);
		return 0;
	}	

	if (Msg == WM_CTLCOLORSTATIC) {
		for (int i = 0; i < 4; i++) {
			if ((HWND)lParam == hInfoLabel[i]) {
				return (BOOL)hWhiteBGBrush;
			}
			if ((HWND)lParam == hInfoText[i]) {
				return (BOOL)hWhiteBGBrush;
			}
		}
	}
	if (Msg == WM_NOTIFY) {
		NMHDR* pNmHdr = (NMHDR*)lParam;

		if (pNmHdr->code == NM_DBLCLK) {
			SelOkay();

			// disable double-click node-expand
			SetWindowLong(hSelDlg, DWL_MSGRESULT, 1);

			return 1;
		}

		if (pNmHdr->code == NM_CUSTOMDRAW && LOWORD(wParam) == IDC_TREE1) {
			LPNMLVCUSTOMDRAW lplvcd = (LPNMLVCUSTOMDRAW)lParam;
			HTREEITEM hSelectHandle;

			switch (lplvcd->nmcd.dwDrawStage) {
				case CDDS_PREPAINT: {
					SetWindowLong(hSelDlg, DWL_MSGRESULT, CDRF_NOTIFYITEMDRAW);
					return 1;
				}

				case CDDS_ITEMPREPAINT:	{
					hSelectHandle = (HTREEITEM)(lplvcd->nmcd.dwItemSpec);
					HBRUSH hBackBrush;
					RECT rect;

					TV_ITEM TvItem;
					TvItem.hItem = hSelectHandle;
					TvItem.mask = TVIF_PARAM | TVIF_STATE | TVIF_CHILDREN;
					SendMessage(hSelList, TVM_GETITEM, 0, (LPARAM)&TvItem);

//					dprintf(_T("  - Item (%i×%i) - (%i×%i) %hs\n"), lplvcd->nmcd.rc.left, lplvcd->nmcd.rc.top, lplvcd->nmcd.rc.right, lplvcd->nmcd.rc.bottom, ((NODEINFO*)TvItem.lParam)->pszROMName);

					// Set the foreground and background colours unless the item is highlighted
					if (!(TvItem.state & (TVIS_SELECTED | TVIS_DROPHILITED))) {

						// Set less contrasting colours for clones
						if (!((NODEINFO*)TvItem.lParam)->bIsParent) {
							lplvcd->clrTextBk = RGB(0xF7, 0xF7, 0xF7);
							lplvcd->clrText = RGB(0x3F, 0x3F, 0x3F);
						}

						// For parents, change the colour of the background, for clones, change only the text colour
						if (!CheckWorkingStatus(((NODEINFO*)TvItem.lParam)->nBurnDrvNo)) {
							lplvcd->clrText = RGB(0x7F, 0x7F, 0x7F);
						}
					}

					rect.left = lplvcd->nmcd.rc.left;
					rect.right = lplvcd->nmcd.rc.right;
					rect.top = lplvcd->nmcd.rc.top;
					rect.bottom = lplvcd->nmcd.rc.bottom;
					
					hBackBrush = CreateSolidBrush(lplvcd->clrTextBk);

					nBurnDrvSelect = ((NODEINFO*)TvItem.lParam)->nBurnDrvNo;

					{
						// Fill background

						FillRect(lplvcd->nmcd.hdc, &lplvcd->nmcd.rc, hBackBrush);
					}
					
					{
						// Draw plus and minus buttons
						if (((NODEINFO*)TvItem.lParam)->bIsParent) {
							if (TvItem.state & TVIS_EXPANDED) {
								DrawIconEx(lplvcd->nmcd.hdc, rect.left + 4, rect.top, hCollapse, 16, 16, 0, NULL, DI_NORMAL);
							} else {
								if (TvItem.cChildren) {
									DrawIconEx(lplvcd->nmcd.hdc, rect.left + 4, rect.top, hExpand, 16, 16, 0, NULL, DI_NORMAL);
								}
							}
						}
						
						rect.left += 24;
					}

					{
						// Draw text

						TCHAR szText[1024] = _T("");
						TCHAR* pszPosition = szText;
						TCHAR* pszName;
						SIZE size = { 0, 0 };

						SetTextColor(lplvcd->nmcd.hdc, lplvcd->clrText);
						SetBkMode(lplvcd->nmcd.hdc, TRANSPARENT);

						// Display the short name if needed
						if (nLoadMenuShowX & SHOWSHORT) {
							DrawText(lplvcd->nmcd.hdc, BurnDrvGetText(DRV_NAME), -1, &rect, DT_LEFT);
							rect.left += 56;
						}


						{
							// Draw icons if needed
							if (!CheckWorkingStatus(((NODEINFO*)TvItem.lParam)->nBurnDrvNo)) {
								DrawIconEx(lplvcd->nmcd.hdc, rect.left, rect.top, hNotWorking, 16, 16, 0, NULL, DI_NORMAL);
								rect.left += 20;
							} else {
								if (!(gameAv[((NODEINFO*)TvItem.lParam)->nBurnDrvNo])) {
									DrawIconEx(lplvcd->nmcd.hdc, rect.left, rect.top, hNotFoundEss, 16, 16, 0, NULL, DI_NORMAL);
									rect.left += 20;
								} else {
									if (!(gameAv[((NODEINFO*)TvItem.lParam)->nBurnDrvNo] & 2)) {
										DrawIconEx(lplvcd->nmcd.hdc, rect.left, rect.top, hNotFoundNonEss, 16, 16, 0, NULL, DI_NORMAL);
										rect.left += 20;
									}
								}
							}
						}

						_tcsncpy(szText, MangleGamename(BurnDrvGetText(DRV_FULLNAME), false), 1024);
						szText[1023] = _T('\0');

						GetTextExtentPoint32(lplvcd->nmcd.hdc, szText, _tcslen(szText), &size);

						DrawText(lplvcd->nmcd.hdc, szText, -1, &rect, DT_NOPREFIX | DT_SINGLELINE | DT_LEFT | DT_VCENTER);

						// Display extra info if needed
						szText[0] = _T('\0');

						pszName = BurnDrvGetText(DRV_FULLNAME);
						while ((pszName = BurnDrvGetText(DRV_NEXTNAME | DRV_FULLNAME)) != NULL) {
							if (pszPosition + _tcslen(pszName) - 1024 > szText) {
								break;
							}
							pszPosition += _stprintf(pszPosition, _T(SEPERATOR_2) _T("%s"), pszName);
						}
						if (szText[0]) {
							szText[255] = _T('\0');

							unsigned int r = ((lplvcd->clrText >> 16 & 255) * 2 + (lplvcd->clrTextBk >> 16 & 255)) / 3;
							unsigned int g = ((lplvcd->clrText >>  8 & 255) * 2 + (lplvcd->clrTextBk >>  8 & 255)) / 3;
							unsigned int b = ((lplvcd->clrText >>  0 & 255) * 2 + (lplvcd->clrTextBk >>  0 & 255)) / 3;
						
							rect.left += size.cx;
							SetTextColor(lplvcd->nmcd.hdc, (r << 16) | (g <<  8) | (b <<  0));
							DrawText(lplvcd->nmcd.hdc, szText, -1, &rect, DT_NOPREFIX | DT_SINGLELINE | DT_LEFT | DT_VCENTER);
						}
					}

					DeleteObject(hBackBrush);
					
					SetWindowLong(hSelDlg, DWL_MSGRESULT, CDRF_SKIPDEFAULT);
					return 1;
				}

				default: {
					SetWindowLong(hSelDlg, DWL_MSGRESULT, CDRF_DODEFAULT);
					return 1;
				}
			}
		}

		if (pNmHdr->code == TVN_ITEMEXPANDING && !TreeBuilding) {
			SendMessage(hSelList, TVM_SELECTITEM, TVGN_CARET, (LPARAM)((LPNMTREEVIEW)lParam)->itemNew.hItem);
			return FALSE;
		}

		if (pNmHdr->code == TVN_SELCHANGED && !TreeBuilding) {
			HTREEITEM hSelectHandle = (HTREEITEM)SendMessage(hSelList, TVM_GETNEXTITEM, TVGN_CARET, ~0U);

			// Search through nBurnDrv[] for the nBurnDrvNo according to the returned hSelectHandle
			for (unsigned int i = 0; i < nTmpDrvCount; i++) {
				if (hSelectHandle == nBurnDrv[i].hTreeHandle) {
					nBurnDrvSelect = nBurnDrv[i].nBurnDrvNo;
					break;
				}
			}
			
			nDialogSelect = nBurnDrvSelect;

			// Get the text from the drivers via BurnDrvGetText()
			for (int i = 0; i < 4; i++) {
				TCHAR szItemText[256];
				szItemText[0] = _T('\0');

				switch (i) {
					case 0: {
						bool bBracket = false;

						_stprintf(szItemText, _T("%s"), BurnDrvGetText(DRV_NAME));
						if ((BurnDrvGetFlags() & BDF_CLONE) && BurnDrvGetTextA(DRV_PARENT)) {
							int nOldDrvSelect = nBurnDrvSelect;
							TCHAR* pszName = BurnDrvGetText(DRV_PARENT);

							_stprintf(szItemText + _tcslen(szItemText), _T(" (clone of %s"), BurnDrvGetText(DRV_PARENT));

							for (nBurnDrvSelect = 0; nBurnDrvSelect < nBurnDrvCount; nBurnDrvSelect++) {
								if (!_tcsicmp(pszName, BurnDrvGetText(DRV_NAME))) {
									break;
								}
							}
							if (nBurnDrvSelect < nBurnDrvCount) {
								if (BurnDrvGetText(DRV_PARENT)) {
									_stprintf(szItemText + _tcslen(szItemText), _T(", uses ROMs from %s"), BurnDrvGetText(DRV_PARENT));
								}
							}
							nBurnDrvSelect = nOldDrvSelect;
							bBracket = true;
						} else {
							if (BurnDrvGetTextA(DRV_PARENT)) {
								_stprintf(szItemText + _tcslen(szItemText), _T("%suses ROMs from %s"), bBracket ? _T(", ") : _T(" ("), BurnDrvGetText(DRV_PARENT));
								bBracket = true;
							}
						}
						if (bBracket) {
							_stprintf(szItemText + _tcslen(szItemText), _T(")"));
						}
						SendMessage(hInfoText[i], WM_SETTEXT, (WPARAM)0, (LPARAM)szItemText);
						EnableWindow(hInfoLabel[i], TRUE);
						break;
					}
					case 1: {
						bool bUseInfo = false;

						if (BurnDrvGetFlags() & BDF_PROTOTYPE) {
							_stprintf(szItemText + _tcslen(szItemText), _T("prototype"));
							bUseInfo = true;
						}
						if (BurnDrvGetFlags() & BDF_BOOTLEG) {
							_stprintf(szItemText + _tcslen(szItemText), _T("%sbootleg / hack"), bUseInfo ? _T(", ") : _T(""));
							bUseInfo = true;
						}
						_stprintf(szItemText + _tcslen(szItemText), _T("%s%i player%s"), bUseInfo ? _T(", ") : _T(""), BurnDrvGetMaxPlayers(), (BurnDrvGetMaxPlayers() != 1) ? _T("s max") : _T(""));
						bUseInfo = true;
						if (BurnDrvGetText(DRV_BOARDROM)) {
							_stprintf(szItemText + _tcslen(szItemText), _T("%suses board-ROMs from %s"), bUseInfo ? _T(", ") : _T(""), BurnDrvGetText(DRV_BOARDROM));
							SendMessage(hInfoText[i], WM_SETTEXT, (WPARAM)0, (LPARAM)szItemText);
							EnableWindow(hInfoLabel[i], TRUE);
							bUseInfo = true;
						}
						SendMessage(hInfoText[i], WM_SETTEXT, (WPARAM)0, (LPARAM)szItemText);
						EnableWindow(hInfoLabel[i], bUseInfo);
						break;
					}
					case 2: {
						_stprintf(szItemText, _T("%s (%s, %s hardware)"), BurnDrvGetTextA(DRV_MANUFACTURER) ? BurnDrvGetText(DRV_MANUFACTURER) : _T("unknown"), BurnDrvGetText(DRV_DATE), BurnDrvGetText(DRV_SYSTEM));
						SendMessage(hInfoText[i], WM_SETTEXT, (WPARAM)0, (LPARAM)szItemText);
						EnableWindow(hInfoLabel[i], TRUE);
						break;
					}
					case 3: {
						TCHAR szText[1024] = _T("");
						TCHAR* pszPosition = szText;
						TCHAR* pszName = BurnDrvGetText(DRV_FULLNAME);

						pszPosition += _sntprintf(szText, 1024, pszName);

						pszName = BurnDrvGetText(DRV_FULLNAME);
						while ((pszName = BurnDrvGetText(DRV_NEXTNAME | DRV_FULLNAME)) != NULL) {
							if (pszPosition + _tcslen(pszName) - 1024 > szText) {
								break;
							}
							pszPosition += _stprintf(pszPosition, _T(SEPERATOR_2) _T("%s"), pszName);
						}
						if (BurnDrvGetText(DRV_COMMENT)) {
							pszPosition += _sntprintf(pszPosition, szText + 1024 - pszPosition, _T(" (%s)"), BurnDrvGetText(DRV_COMMENT));
						}
						SendMessage(hInfoText[i], WM_SETTEXT, (WPARAM)0, (LPARAM)szText);
						if (szText[0]) {
							EnableWindow(hInfoLabel[i], TRUE);
						} else {
							EnableWindow(hInfoLabel[i], FALSE);
						}
					}
				}
			}

			UpdatePreview(true);
		}
	}

	return 0;
}

INT_PTR FBADialogBox(HINSTANCE, LPTSTR, HWND, DLGPROC);

int SelDialog()
{
//	DialogBox(hAppInst, MAKEINTRESOURCE(IDD_SELNEW), hScrnWnd, DialogProc);

	int nOldSelect = nBurnDrvSelect;

	FBADialogBox(hAppInst, MAKEINTRESOURCE(IDD_SELNEW), hScrnWnd, DialogProc);

	hSelDlg = NULL;
	hSelList = NULL;

	free(nBurnDrv);
	nBurnDrv = NULL;

	nBurnDrvSelect = nOldSelect;

	return nDialogSelect;
}
