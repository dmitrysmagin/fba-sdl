// Memory card support module

#include "burner.h"

static TCHAR szMemoryCardFile[MAX_PATH];

int nMemoryCardStatus = 0;
int nMemoryCardSize;

static int MakeOfn()
{
	memset(&ofn, 0, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hScrnWnd;
	ofn.lpstrFile = szMemoryCardFile;
	ofn.nMaxFile = sizeof(szMemoryCardFile);
	ofn.lpstrInitialDir = _T(".");
	ofn.Flags = OFN_NOCHANGEDIR | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = _T("fc");

	return 0;
}

static int __cdecl MemCardDoGetSize(struct BurnArea* pba)
{
	nMemoryCardSize = pba->nLen;

	return 0;
}

static int MemCardGetSize()
{
	BurnAcb = MemCardDoGetSize;
	BurnAreaScan(ACB_MEMCARD, NULL);

	return 0;
}

int	MemCardCreate()
{
	int nRet;

	_stprintf (szMemoryCardFile, _T("memorycard"));
	MakeOfn();
	ofn.lpstrTitle = _T("Create new memory card");
	ofn.lpstrFilter = _T("FB Alpha Memory cards (*.fc)\0*.fc\0\0");
	ofn.Flags |= OFN_OVERWRITEPROMPT;

	int bOldPause = bRunPause;
	bRunPause = 1;
	nRet = GetSaveFileName(&ofn);
	bRunPause = bOldPause;

	if (nRet == 0) {
		return 1;
	}

	FILE* fp = _tfopen(szMemoryCardFile, _T("wb"));
	if (fp == NULL) {
		return 1;
	} else {
		unsigned char* pCard;

		MemCardGetSize();

		pCard = (unsigned char*)malloc(nMemoryCardSize);
		memset(pCard, 0, nMemoryCardSize);

		fwrite(pCard, 1, nMemoryCardSize, fp);
		fclose(fp);

		free(pCard);
	}

	nMemoryCardStatus = 1;
	MenuEnableItems();

	return 0;
}

int	MemCardSelect()
{
	int nRet;

	_stprintf (szMemoryCardFile, _T("memcard"));
	MakeOfn();
	ofn.lpstrTitle = _T("Select memory card");
	ofn.lpstrFilter = _T("All Memory cards (*.fc, MEMCARD.\?\?\?)\0*.fc;MEMCARD.\?\?\?\0FB Alpha Memory cards (*.fc)\0*.fc\0MAME Memory cards (MEMCARD.\?\?\?)\0MEMCARD.\?\?\?\0\0");

	int bOldPause = bRunPause;
	bRunPause = 1;
	nRet = GetOpenFileName(&ofn);
	bRunPause = bOldPause;

	if (nRet == 0) {
		return 1;
	}

	MemCardGetSize();

	if (nMemoryCardSize <= 0) {
		return 1;
	}

	nMemoryCardStatus = 1;
	MenuEnableItems();

	return 0;
}

static int __cdecl MemCardDoInsert(struct BurnArea* pba)
{
	FILE* fp = _tfopen(szMemoryCardFile, _T("rb"));
	if (fp) {
		fread((unsigned char*)pba->Data, 1, pba->nLen, fp);
		fclose(fp);

		nMemoryCardStatus |= 2;
		MenuEnableItems();

		return 0;
	}

	return 1;
}

int	MemCardInsert()
{
	if ((nMemoryCardStatus & 1) && (nMemoryCardStatus & 2) == 0) {
		BurnAcb = MemCardDoInsert;
		BurnAreaScan(ACB_WRITE | ACB_MEMCARD, NULL);
	}

	return 0;
}

static int __cdecl MemCardDoEject(struct BurnArea* pba)
{
	FILE* fp = _tfopen(szMemoryCardFile, _T("wb"));
	if (fp) {
		fwrite((unsigned char*)pba->Data, 1, pba->nLen, fp);
		fclose(fp);

		nMemoryCardStatus &= ~2;
		MenuEnableItems();

		return 0;
	}

	return 1;
}

int	MemCardEject()
{
	if ((nMemoryCardStatus & 1) && (nMemoryCardStatus & 2)) {
		BurnAcb = MemCardDoEject;
		BurnAreaScan(ACB_READ | ACB_MEMCARD, NULL);
	}

	return 0;
}

int	MemCardToggle()
{
	if (nMemoryCardStatus & 1) {
		if (nMemoryCardStatus & 2) {
			return MemCardEject();
		} else {
			return MemCardInsert();
		}
	}

	return 1;
}
