
// stubs module for null functions
#include "burner.h"

// replaces ips_manager.cpp
bool bDoIpsPatch = 0;
void IpsApplyPatches(UINT8* base, char* rom_name) {}

// replaces hiscore.cpp
INT32 EnableHiscores = 0;

void HiscoreInit() {}
void HiscoreReset() {}
void HiscoreApply() {}
void HiscoreExit() {}
