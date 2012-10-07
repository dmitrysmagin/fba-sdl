/*
#ifdef _UNICODE
#define WARNING: you have enabled unicode which is currently untested!!
//TODO: bah
#include <wchar.h>
#define	__TEXT(q)	L##q

typedef	wchar_t	TCHAR;
typedef wchar_t _TCHAR;

#else

*/
#include <wchar.h>
#ifndef RC_INVOKED
typedef char	TCHAR;
typedef char	_TCHAR;
#endif

#define _stprintf   sprintf

#define _tsprintf   sprintf
#define _tcslen     strlen
#define _tcscpy     strcpy
#define _tcsncpy    strncpy
#define _vstprintf  vsprintf
#define _vsntprintf vsnprintf
#define	_istspace	isspace
#define _tcscmp     strcmp
#define _tcsncmp    strncmp
#define _tcsicmp    strcasecmp
#define _tcsnicmp   strncasecmp
#define _tcstol     strtol
#define _sntprintf  snprintf
#define _tfopen     fopen

#define _stricmp strcmp
#define _strnicmp strncmp

#define _tprintf    printf



#define _ftprintf   fprintf
#define _tsprintf   sprintf



#define _fgetts     fgets
#define _fputts     fputs

#define dprintf printf
#define	__TEXT(q)	q
#define _TEXT(x)	__TEXT(x)
#define	_T(x)		__TEXT(x)
// WTF? This is a normal string function!
// damn linux. :)
//#define wcslen(void)
/*














// FBA function, change this!



//#endif


*/
