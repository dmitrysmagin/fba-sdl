
// stubs module for null functions
#include "burner.h"

// replaces ips_manager.cpp
bool bDoIpsPatch = 0;
void IpsApplyPatches(UINT8* base, char* rom_name) {}

// needed by cps3run.cpp and dataeast/d_backfire.cpp
void Reinitialise() {}

// needed by neo_run.cpp
void	wav_exit() {}
int bRunPause;
