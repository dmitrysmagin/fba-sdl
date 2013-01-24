// State dialog module
#include "burner.h"

int nSavestateSlot = 0;
 
static char szSavestateName[512];

// The automatic save
int StatedAuto(int bSave)
{
	return 0;
}

int StatedLoad(int nSlot)
{
	sprintf(szSavestateName, "./%s%i.sav", BurnDrvGetText(DRV_NAME), nSlot);
	printf("StatedLoad: %s\n", szSavestateName);
	return BurnStateLoad(szSavestateName, 1, &DrvInitCallback);
}

int StatedSave(int nSlot)
{
	sprintf(szSavestateName, "./%s%i.sav", BurnDrvGetText(DRV_NAME), nSlot);
	printf("StatedSave: %s\n", szSavestateName);
	return BurnStateSave(szSavestateName, 1);
}
