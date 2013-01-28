#ifndef _TCHAR_H_
#define _TCHAR_H_

#define	__TEXT(q)	q


//#define	TCHAR char
typedef char TCHAR;

#include <wchar.h>


// WTF? This is a normal string function!
// damn linux. :)
#define wcslen(void)

#define _tcslen     strlen
#define _tcscpy     strcpy
#define _tcsncpy    strncpy

#define _tprintf    printf
#define _vstprintf  vsprintf
#define _vsntprintf vsnprintf
#define _stprintf   sprintf
#define _sntprintf  snprintf
#define _ftprintf   fprintf
#define _tsprintf   sprintf

#define _tcscmp     strcmp
#define _tcsncmp    strncmp
#define _tcsicmp    strcasecmp
#define _tcsnicmp   strncasecmp
#define _tcstol     strtol
#define _tcsstr     strstr

#define _fgetts     fgets
#define _fputts     fputs

#define	_istspace	isspace

#define _tfopen     fopen

#define _stricmp strcmp
#define _strnicmp strncmp

#ifdef WIN32
#define strnlen(A, B) (strlen(A))
#endif

#undef __fastcall
#undef _fastcall
#define __fastcall			/*what does this correspond to?*/
#define _fastcall			/*same as above - what does this correspond to?*/

//#define uintptr_t unsigned int

// FBA function, change this!
#define dprintf printf


#endif //_TCHAR_H_

#define _TEXT(x)	__TEXT(x)
#define	_T(x)		__TEXT(x)

