// FB Alpha - Emulator for MC68000/Z80 based arcade games
//            Refer to the "license.txt" file for more info

// Main module

// #define USE_SDL					// define if SDL is used
// #define DONT_DISPLAY_SPLASH		// Prevent Splash screen from being displayed
// #define APP_DEBUG_LOG			// log debug messages to zzBurnDebug.txt

#ifdef USE_SDL
 #include <SDL.h>
#endif

#include "burner.h"

#ifdef _MSC_VER
  #include <winable.h>
 #ifdef _DEBUG
  #include <crtdbg.h>
 #endif
#endif

#include "kailleraclient.h"
#include "version.h"

HINSTANCE hAppInst = NULL;			// Application Instance
HANDLE hMainThread;
long int nMainThreadID;
int nAppThreadPriority = THREAD_PRIORITY_NORMAL;
int nAppShowCmd;

static TCHAR szCmdLine[1024] = _T("");

HACCEL hAccel = NULL;

int nAppVirtualFps = 6000;			// App fps * 100

TCHAR szAppBurnVer[16] = _T("");
TCHAR szAppExeName[EXE_NAME_SIZE + 1];

bool bCmdOptUsed = 0;
bool bAlwaysProcessKeyboardInput = false;

static bool bNumlockStatus;

// Used for the load/save dialog in commdlg.h (savestates, input replay, wave logging)
TCHAR szChoice[MAX_PATH] = _T("");
OPENFILENAME ofn;

/* const */ char* TCHARToANSI(const TCHAR* pszInString, char* pszOutString, int nOutSize)
{
#if defined (UNICODE)
	static char szStringBuffer[1024];
	memset(szStringBuffer, 0, sizeof(szStringBuffer));

	char* pszBuffer = pszOutString ? pszOutString : szStringBuffer;
	int nBufferSize = pszOutString ? nOutSize * 2 : sizeof(szStringBuffer);

	if (WideCharToMultiByte(CP_ACP, 0, pszInString, -1, pszBuffer, nBufferSize, NULL, NULL)) {
		return pszBuffer;
	}

	return NULL;
#else
	if (pszOutString) {
		strcpy(pszOutString, pszInString);
		return pszOutString;
	}

	return (char*)pszInString;
#endif
}

/* const */ TCHAR* ANSIToTCHAR(const char* pszInString, TCHAR* pszOutString, int nOutSize)
{
#if defined (UNICODE)
	static TCHAR szStringBuffer[1024];

	TCHAR* pszBuffer = pszOutString ? pszOutString : szStringBuffer;
	int nBufferSize  = pszOutString ? nOutSize * 2 : sizeof(szStringBuffer);

	if (MultiByteToWideChar(CP_ACP, 0, pszInString, -1, pszBuffer, nBufferSize)) {
		return pszBuffer;
	}

	return NULL;
#else
	if (pszOutString) {
		_tcscpy(pszOutString, pszInString);
		return pszOutString;
	}

	return (TCHAR*)pszInString;
#endif
}

#if defined (FBA_DEBUG)
 static TCHAR szConsoleBuffer[1024];
 static int nPrevConsoleStatus = -1;

 static HANDLE DebugBuffer;
 static FILE *DebugLog = NULL;
 static bool bEchoLog = true; // false;
#endif

// Debug printf to a file
static int __cdecl AppDebugPrintf(int nStatus, TCHAR* szFormat, ...)
{
#if defined (FBA_DEBUG)
	va_list vaFormat;

	va_start(vaFormat, szFormat);

	if (DebugLog) {

		if (nStatus != nPrevConsoleStatus) {
			switch (nStatus) {
				case PRINT_ERROR:
					_ftprintf(DebugLog, _T("</font><font color=#FF3F3F>"));
					break;
				case PRINT_IMPORTANT:
					_ftprintf(DebugLog, _T("</font><font color=#000000>"));
					break;
				default:
					_ftprintf(DebugLog, _T("</font><font color=#009F00>"));
			}
		}
		_vftprintf(DebugLog, szFormat, vaFormat);
		fflush(DebugLog);
	}

	if (!DebugLog || bEchoLog) {
		_vsntprintf(szConsoleBuffer, 1024, szFormat, vaFormat);

		if (nStatus != nPrevConsoleStatus) {
			switch (nStatus) {
				case PRINT_UI:
					SetConsoleTextAttribute(DebugBuffer, FOREGROUND_INTENSITY);
					break;
				case PRINT_IMPORTANT:
					SetConsoleTextAttribute(DebugBuffer, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
					break;
				case PRINT_ERROR:
					SetConsoleTextAttribute(DebugBuffer, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
					break;
				default:
					SetConsoleTextAttribute(DebugBuffer, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			}
		}

		WriteConsole(DebugBuffer, szConsoleBuffer, _tcslen(szConsoleBuffer), NULL, NULL);
	}

	if (nStatus != nPrevConsoleStatus) {
		nPrevConsoleStatus = nStatus;
	}

	va_end(vaFormat);
#endif

	return 0;
}

int dprintf(TCHAR* szFormat, ...)
{
#if defined (FBA_DEBUG)
	va_list vaFormat;
	va_start(vaFormat, szFormat);

	_vsntprintf(szConsoleBuffer, 1024, szFormat, vaFormat);

	if (nPrevConsoleStatus != PRINT_UI) {
		if (DebugLog) {
			_ftprintf(DebugLog, _T("</font><font color=#9F9F9F>"));
		}
		SetConsoleTextAttribute(DebugBuffer, FOREGROUND_INTENSITY);
		nPrevConsoleStatus = PRINT_UI;
	}

	if (DebugLog) {
		_ftprintf(DebugLog, szConsoleBuffer);
		fflush(DebugLog);
	}
	WriteConsole(DebugBuffer, szConsoleBuffer, _tcslen(szConsoleBuffer), NULL, NULL);
	va_end(vaFormat);
#else
	(void)szFormat;
#endif

	return 0;
}

void CloseDebugLog()
{
#if defined (FBA_DEBUG)
	if (DebugLog) {
	
		_ftprintf(DebugLog, _T("</pre></body></html>"));
	
		fclose(DebugLog);
		DebugLog = NULL;
	}

	if (DebugBuffer) {	
		CloseHandle(DebugBuffer);
		DebugBuffer = NULL;
	}
	
	FreeConsole();
#endif
}

int OpenDebugLog()
{
#if defined (FBA_DEBUG)
 #if defined (APP_DEBUG_LOG)

    time_t nTime;
	tm* tmTime;

	time(&nTime);
	tmTime = localtime(&nTime);

	{
		// Initialise the debug log file

  #ifdef _UNICODE
		DebugLog = _tfopen(_T("zzBurnDebug.html"), _T("wb"));

		if (ftell(DebugLog) == 0) {
			WRITE_UNICODE_BOM(DebugLog);

			_ftprintf(DebugLog, _T("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">"));
			_ftprintf(DebugLog, _T("<html><head><meta http-equiv=Content-Type content=\"text/html; charset=unicode\"></head><body><pre>"));
		}
  #else
		DebugLog = _tfopen(_T("zzBurnDebug.html"), _T("wt"));

		if (ftell(DebugLog) == 0) {
			_ftprintf(DebugLog, _T("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">"));
			_ftprintf(DebugLog, _T("<html><head><meta http-equiv=Content-Type content=\"text/html; charset=windows-%i\"></head><body><pre>"), GetACP());
		}
  #endif

		_ftprintf(DebugLog, _T("</font><font size=larger color=#000000>"));
		_ftprintf(DebugLog, _T("Debug log created by ") _T(APP_TITLE) _T(" v%.20s on %s\n<br>"), szAppBurnVer, _tasctime(tmTime));
	}
 #endif

	{
		// Initialise the debug console

		COORD DebugBufferSize = { 80, 1000 };

		{
		
			// Since AttachConsole is only present in Windows XP, import it manually

#if _WIN32_WINNT >= 0x0500 && defined (_MSC_VER)
// #error Manually importing AttachConsole() function, but compiling with _WIN32_WINNT >= 0x0500
			if (!AttachConsole(ATTACH_PARENT_PROCESS)) {
				AllocConsole();
			}
#else
 #define ATTACH_PARENT_PROCESS ((DWORD)-1)

			BOOL (WINAPI* pAttachConsole)(DWORD dwProcessId) = NULL;
			HINSTANCE hKernel32DLL = LoadLibrary(_T("kernel32.dll"));
			if (hKernel32DLL) {
				pAttachConsole = (BOOL (WINAPI*)(DWORD))GetProcAddress(hKernel32DLL, "AttachConsole");
			}
			if (pAttachConsole) {
				if (!pAttachConsole(ATTACH_PARENT_PROCESS)) {
					AllocConsole();
				}
			} else {
				AllocConsole();
			}
			if (hKernel32DLL) {
				FreeLibrary(hKernel32DLL);
			}

 #undef ATTACH_PARENT_PROCESS
#endif

		}

		DebugBuffer = CreateConsoleScreenBuffer(GENERIC_WRITE, FILE_SHARE_READ, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		SetConsoleScreenBufferSize(DebugBuffer, DebugBufferSize);
		SetConsoleActiveScreenBuffer(DebugBuffer);
		SetConsoleTitle(_T(APP_TITLE) _T(" Debug console"));

		SetConsoleTextAttribute(DebugBuffer, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		_sntprintf(szConsoleBuffer, 1024, _T("Welcome to the ") _T(APP_TITLE) _T(" debug console.\n"));
		WriteConsole(DebugBuffer, szConsoleBuffer, _tcslen(szConsoleBuffer), NULL, NULL);

		SetConsoleTextAttribute(DebugBuffer, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		if (DebugLog) {
			_sntprintf(szConsoleBuffer, 1024, _T("Debug messages are logged in zzBurnDebug.html"));
			if (!DebugLog || bEchoLog) {
				_sntprintf(szConsoleBuffer + _tcslen(szConsoleBuffer), 1024 - _tcslen(szConsoleBuffer), _T(", and echod to this console"));
			}
			_sntprintf(szConsoleBuffer + _tcslen(szConsoleBuffer), 1024 - _tcslen(szConsoleBuffer), _T(".\n\n"));
		} else {
			_sntprintf(szConsoleBuffer, 1024, _T("Debug messages are echod to this console.\n\n"));
		}
		WriteConsole(DebugBuffer, szConsoleBuffer, _tcslen(szConsoleBuffer), NULL, NULL);
	}

	bprintf = AppDebugPrintf;							// Redirect Burn library debug to our function
#endif

	return 0;
}

bool SetNumLock(bool bState)
{
	BYTE keyState[256];

	GetKeyboardState(keyState);
	if ((bState && !(keyState[VK_NUMLOCK] & 1)) || (!bState && (keyState[VK_NUMLOCK] & 1))) {
		keybd_event(VK_NUMLOCK, 0, KEYEVENTF_EXTENDEDKEY, 0 );

		keybd_event(VK_NUMLOCK, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
	}

	return keyState[VK_NUMLOCK] & 1;
}

// Show a message box with an error message
int AppError(TCHAR* szText, int bWarning)
{
	SplashDestroy(1);

	AudSoundStop();
	MessageBox(hScrnWnd, szText, (bWarning ? _T(APP_TITLE) _T(" Warning") : _T(APP_TITLE) _T(" Error")), MB_OK | (bWarning ? MB_ICONWARNING : MB_ICONERROR) | MB_SETFOREGROUND);
	AudSoundPlay();

	return 0;
}

static int AppInit()
{

#if defined (_MSC_VER) && defined (_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_CHECK_ALWAYS_DF);			// Check for memory corruption
	_CrtSetDbgFlag(_CRTDBG_DELAY_FREE_MEM_DF);			//
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF);				//
#endif

	OpenDebugLog();

	// Create a handle to the main thread of execution
	DuplicateHandle(GetCurrentProcess(), GetCurrentThread(), GetCurrentProcess(), &hMainThread, 0, false, DUPLICATE_SAME_ACCESS);

	kailleraInit();

	// Load config for the application
	if (ConfigAppLoad()) {
		ConfigAppSave();			// create initial config file
	}

	FBALocaliseInit();
	
#if 1 || !defined (FBA_DEBUG)
	// print a warning if we're running for the 1st time
	if (nIniVersion < nBurnVer) {
		SplashDestroy(1);
		FirstUsageCreate();
	}
#endif

	// Set the thread priority for the main thread
	SetThreadPriority(GetCurrentThread(), nAppThreadPriority);

	bCheatsAllowed = true;

#ifdef USE_SDL
	SDL_Init(0);
#endif

	// Init the Burn library
	BurnLibInit();

	ComputeGammaLUT();

	hAccel = LoadAccelerators(hAppInst, MAKEINTRESOURCE(IDR_ACCELERATOR));

	// Build the ROM information
	CreateROMInfo();

	bNumlockStatus = SetNumLock(false);

	return 0;
}

static int AppExit()
{
	SetNumLock(bNumlockStatus);

	DrvExit();						// Make sure any game driver is exitted
	FreeROMInfo();
	MediaExit(true);
	BurnLibExit();					// Exit the Burn library

#ifdef USE_SDL
	SDL_Quit();
#endif

	kailleraShutdown();

	FBALocaliseExit();

	if (hAccel) {
		DestroyAcceleratorTable(hAccel);
		hAccel = NULL;
	}

	SplashDestroy(1);

	CloseHandle(hMainThread);

	CloseDebugLog();

	return 0;
}

void AppCleanup()
{
	StopReplay();
	WaveLogStop();

	AppExit();
}

int AppMessage(MSG *pMsg)
{
	if (IsDialogMessage(hInpdDlg, pMsg)) return 0;
	if (IsDialogMessage(hInpCheatDlg, pMsg)) return 0;
	if (IsDialogMessage(hInpDIPSWDlg, pMsg)) return 0;
	if (IsDialogMessage(hDbgDlg, pMsg)) return 0;

	if (IsDialogMessage(hInpsDlg, pMsg)) return 0;
	if (IsDialogMessage(hInpcDlg, pMsg)) return 0;

	return 1; // Didn't process this message
}

bool AppProcessKeyboardInput()
{
	if (hwndChat) {
		return false;
	}

	return true;
}

int ProcessCmdLine()
{
	unsigned int i;
	int nOptX = 0, nOptY = 0, nOptD = 0;
	int nOpt1Size;
	TCHAR szOpt2[2] = _T("");
	TCHAR szName[MAX_PATH];

	if (szCmdLine[0] == _T('\"')) {
		int nLen = _tcslen(szCmdLine);
		nOpt1Size = 1;
		while (szCmdLine[nOpt1Size] != _T('\"') && nOpt1Size < nLen) {
			nOpt1Size++;
		}
		if (nOpt1Size == nLen) {
			szName[0] = 0;
		} else {
			nOpt1Size++;
			_tcsncpy(szName, szCmdLine + 1, nOpt1Size - 2);
			szName[nOpt1Size - 2] = 0;
		}
	} else {
		int nLen = _tcslen(szCmdLine);
		nOpt1Size = 0;
		while (szCmdLine[nOpt1Size] != _T(' ') && nOpt1Size < nLen) {
			nOpt1Size++;
		}
		_tcsncpy(szName, szCmdLine, nOpt1Size);
		szName[nOpt1Size] = 0;
	}

	if (_tcslen(szName)) {
		if (_tcscmp(szName, _T("-listinfo")) == 0) {
			write_datfile(0, stdout);
			return 1;
		}
	}

	_stscanf(&szCmdLine[nOpt1Size], _T("%2s %i x %i x %i"), szOpt2, &nOptX, &nOptY, &nOptD);

	if (_tcslen(szName)) {
		bool bFullscreen = 1;
		bCmdOptUsed = 1;

		if (_tcscmp(szOpt2, _T("-r")) == 0) {
			if (nOptX && nOptY) {
				nVidWidth = nOptX;
				nVidHeight = nOptY;
			}
			if (nOptD) {
				nVidDepth = nOptD;
			}
		} else {
			if (_tcscmp(szOpt2, _T("-a")) == 0) {
				bVidArcaderes = 1;
			} else {
				if (_tcscmp(szOpt2, _T("-w")) == 0) {
					bCmdOptUsed = 0;
					bFullscreen = 0;
				}
			}
		}

		if (bFullscreen) {
			nVidFullscreen = 1;
		}

		if (_tcscmp(&szName[_tcslen(szName) - 3], _T(".fs")) == 0) {
			if (BurnStateLoad(szName, 1, &DrvInitCallback)) {
				return 1;
			} else {
				bRunPause = 1;
			}
		} else {
			if (_tcscmp(&szName[_tcslen(szName) - 3], _T(".fr")) == 0) {
				if (StartReplay(szName)) {
					return 1;
				}
			} else {
				for (i = 0; i < nBurnDrvCount; i++) {
					nBurnDrvSelect = i;
					if (_tcscmp(BurnDrvGetText(DRV_NAME), szName) == 0) {
						MediaInit();
						DrvInit(i, true);
						break;
					}
				}
				if (i == nBurnDrvCount) {
					TCHAR szErrorString[128];
					_stprintf(szErrorString, _T("%s is not supported by ") _T(APP_TITLE) _T("."), szName);
					AppError(szErrorString, 0);
					return 1;
				}
			}
		}
	}

	if (!nVidFullscreen) {
		MenuEnableItems();
	}

	return 0;
}

// Main program entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nShowCmd)
{
	// Provide a custom exception handler
	SetUnhandledExceptionFilter(ExceptionFilter);

	hAppInst = hInstance;

	// Make version string
	if (nBurnVer & 0xFF) {
		// private version (alpha)
		_stprintf(szAppBurnVer, _T("%x.%x.%x.%x"), nBurnVer >> 20, (nBurnVer >> 16) & 0x0F, (nBurnVer >> 8) & 0xFF, nBurnVer & 0xFF);
	} else {
		// public version
		_stprintf(szAppBurnVer, _T("%x.%x.%x"), nBurnVer >> 20, (nBurnVer >> 16) & 0x0F, (nBurnVer >> 8) & 0xFF);
	}

#if !defined (DONT_DISPLAY_SPLASH)
	SplashCreate();
#endif

	nAppShowCmd = nShowCmd;

	AppDirectory();								// Set current directory to be the applications directory

	// Make sure there are roms and cfg subdirectories
	CreateDirectory(_T("config"), NULL);
	CreateDirectory(_T("config\\games"), NULL);
	CreateDirectory(_T("config\\presets"), NULL);
	CreateDirectory(_T("savestates"), NULL);
	CreateDirectory(_T("cheats"), NULL);
	CreateDirectory(_T("previews"), NULL);
	CreateDirectory(_T("recordings"), NULL);
	CreateDirectory(_T("ROMs"), NULL);
	CreateDirectory(_T("screenshots"), NULL);

	{
		INITCOMMONCONTROLSEX initCC = {
			sizeof(INITCOMMONCONTROLSEX),
			ICC_BAR_CLASSES | ICC_COOL_CLASSES | ICC_LISTVIEW_CLASSES | ICC_PROGRESS_CLASS | ICC_TREEVIEW_CLASSES,
		};

		if (!InitCommonControlsEx(&initCC)) {
			TCHAR szErrorString[] = _T("Sorry, ") _T(APP_TITLE) _T(" cannot run on this system.");
			AppError(szErrorString, 0);

			return 0;
		}
	}

	if (lpCmdLine) {
		_tcscpy(szCmdLine, ANSIToTCHAR(lpCmdLine, NULL, 0));
	}

	if (!(AppInit())) {							// Init the application
		if (!(ProcessCmdLine())) {
			RunMessageLoop();					// Run the application message loop
		}
	}

	AppExit();									// Exit the application

	ConfigAppSave();							// Save config for the application

	return 0;
}
