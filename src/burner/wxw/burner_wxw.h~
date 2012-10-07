//wahhhhhhhh - this is nessecary otherwise wxWidgets complains that the libs are not debug. 
#ifdef _DEBUG
#undef _DEBUG
#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <wx/datetime.h>
#include "SDL.h"
#define _DEBUG
#else
#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <wx/datetime.h>
#include "SDL.h"
#endif
// end of wahhhhhhhh

#ifndef _WIN32
typedef struct tagRECT {
	int left;
	int top;
	int right;
	int bottom;
} RECT,*PRECT,*LPRECT;
typedef const RECT *LPCRECT;
#endif


#ifndef MAX_PATH
#define MAX_PATH 511
#endif

#ifndef __cdecl
#define __cdecl
#endif

//main.cpp
int SetBurnHighCol(int nDepth);
extern int nAppVirtualFps;
extern bool bRunPause;
extern bool bAlwaysProcessKeyboardInput;
TCHAR* ANSIToTCHAR(const char* pszInString, TCHAR* pszOutString, int nOutSize);
char* TCHARToANSI(const TCHAR* pszInString, char* pszOutString, int nOutSize);
bool AppProcessKeyboardInput();

//config.cpp
int ConfigAppLoad();	
int ConfigAppSave();

// drv.cpp
extern int bDrvOkay; // 1 if the Driver has been initted okay, and it's okay to use the BurnDrv functions
extern char szAppRomPaths[DIRS_MAX][MAX_PATH];
int DrvInit(int nDrvNum, bool bRestore);
int DrvInitCallback(); // Used when Burn library needs to load a game. DrvInit(nBurnSelect, false)
int DrvExit();
int ProgressUpdateBurner(double dProgress, const TCHAR* pszText, bool bAbs);
int AppError(TCHAR* szText, int bWarning);

//run.cpp
int RunStart(int nGameNumber);
int RunExit();
int RunReset();
int RunIdle();

//inpdipsw.cpp
void InpDIPSWResetDIPs();

//interface/inp_interface.cpp
int InputInit();
int InputExit();
int InputMake(bool bCopy);

//video stuff
extern unsigned char* texture;
extern unsigned char* gamescreen;
extern int nTextureWidth;
extern int nTextureHeight;
extern int nGamesWidth;
extern int nGamesHeight;
extern bool bDoPaint;
//TODO:
#define szAppBurnVer 1

