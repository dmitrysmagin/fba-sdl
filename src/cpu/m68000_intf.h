// 68000 (Sixty Eight K) Interface - header file

#ifndef _SEK_H_
#define _SEK_H_

#include <stdint.h>

#ifndef FASTCALL
 #undef __fastcall
 #define __fastcall
#endif

#if defined BUILD_A68K
 #define EMU_A68K								// Use A68K Assembler 68000 emulator
#endif

#ifdef BUILD_C68K
 #define EMU_C68K
 #include "c68k.h"
#endif

#ifdef BUILD_M68K
 #define EMU_M68K
 #include "m68k.h"
#endif

#ifndef M68K_INT_ACK_AUTOVECTOR // if musashi core is completely disabled
 #define M68K_INT_ACK_AUTOVECTOR 0xffffffff
#endif

#ifndef m68k_set_reg
 #define m68k_set_reg(A, B) 
#endif
 
#define SEK_MAX	(4)								// Maximum number of CPUs supported

// Number of bits used for each page in the fast memory map
#define SEK_BITS		(10)					// 10 = 0x0400 page size
#define SEK_PAGE_COUNT  (1 << (24 - SEK_BITS))	// Number of pages
#define SEK_SHIFT		(SEK_BITS)				// Shift value = page bits
#define SEK_PAGE_SIZE	(1 << SEK_BITS)			// Page size
#define SEK_PAGEM		(SEK_PAGE_SIZE - 1)
#define SEK_WADD		(SEK_PAGE_COUNT)		// Value to add for write section = Number of pages
#define SEK_MASK		(SEK_WADD - 1)
#define SEK_MAXHANDLER	(10)						// Max. number of handlers for memory access

#if SEK_MAXHANDLER < 1
 #error At least one set of handlers for memory access must be used.
#endif

#ifdef EMU_A68K
 extern "C" void __cdecl M68000_RUN();
 extern "C" void __cdecl M68000_RESET();

 // The format of the data in a68k.asm (at the _M68000_regs location)
 struct A68KContext {
	UINT32 d[8], a[8];
	UINT32 isp, srh, ccr, xc, pc, irq, sr;
	INT32 (*IrqCallback) (INT32 nIrq);
	UINT32 ppc;
	INT32 (*ResetCallback)();
	INT32 (*RTECallback)();
	INT32 (*CmpCallback)(UINT32 val, INT32 reg);
	UINT32 sfc, dfc, usp, vbr;
	UINT32 nAsmBank, nCpuVersion;
 };
 extern "C" struct A68KContext M68000_regs;
 extern     struct A68KContext* SekRegs[SEK_MAX];

 extern "C" UINT8* OP_ROM;
 extern "C" UINT8* OP_RAM;
 extern "C" INT32 m68k_ICount;
#endif

#ifdef EMU_M68K
 extern "C" INT32 m68k_ICount;
 extern "C" INT32 nSekM68KContextSize[SEK_MAX];
 extern "C" INT8* SekM68KContext[SEK_MAX];
#endif

#ifdef EMU_C68K
 extern "C" c68k_struc * SekC68KCurrentContext;
 extern "C" c68k_struc * SekC68KContext[SEK_MAX]; 
 #define c68k_ICount	(SekC68KCurrentContext->ICount)
#endif

typedef UINT8 (__fastcall *pSekReadByteHandler)(UINT32 a);
typedef void (__fastcall *pSekWriteByteHandler)(UINT32 a, UINT8 d);
typedef UINT16 (__fastcall *pSekReadWordHandler)(UINT32 a);
typedef void (__fastcall *pSekWriteWordHandler)(UINT32 a, UINT16 d);
typedef UINT32 (__fastcall *pSekReadLongHandler)(UINT32 a);
typedef void (__fastcall *pSekWriteLongHandler)(UINT32 a, UINT32 d);

typedef INT32 (__fastcall *pSekResetCallback)();
typedef INT32 (__fastcall *pSekRTECallback)();
typedef INT32 (__fastcall *pSekIrqCallback)(INT32 irq);
typedef INT32 (__fastcall *pSekCmpCallback)(UINT32 val, INT32 reg);
typedef INT32 (__fastcall *pSekTASCallback)();

extern INT32 nSekCycles[SEK_MAX], nSekCPUType[SEK_MAX];

// Mapped memory pointers to Rom and Ram areas (Read then Write)
// These memory areas must be allocated multiples of the page size
// with a 4 byte over-run area lookup for each page (*3 for read, write and fetch)
struct SekExt {
	UINT8* MemMap[SEK_PAGE_COUNT * 3];

	// If MemMap[i] < SEK_MAXHANDLER, use the handler functions
	pSekReadByteHandler ReadByte[SEK_MAXHANDLER];
	pSekWriteByteHandler WriteByte[SEK_MAXHANDLER];
	pSekReadWordHandler ReadWord[SEK_MAXHANDLER];
	pSekWriteWordHandler WriteWord[SEK_MAXHANDLER];
	pSekReadLongHandler ReadLong[SEK_MAXHANDLER];
	pSekWriteLongHandler WriteLong[SEK_MAXHANDLER];

	pSekResetCallback ResetCallback;
	pSekRTECallback RTECallback;
	pSekIrqCallback IrqCallback;
	pSekCmpCallback CmpCallback;
	pSekTASCallback TASCallback;
};

#define SEK_DEF_READ_WORD(i, a) { UINT16 d; d = (UINT16)(pSekExt->ReadByte[i](a) << 8); d |= (UINT16)(pSekExt->ReadByte[i]((a) + 1)); return d; }
#define SEK_DEF_WRITE_WORD(i, a, d) { pSekExt->WriteByte[i]((a),(UINT8)((d) >> 8)); pSekExt->WriteByte[i]((a) + 1, (UINT8)((d) & 0xff)); }
#define SEK_DEF_READ_LONG(i, a) { UINT32 d; d = pSekExt->ReadWord[i](a) << 16; d |= pSekExt->ReadWord[i]((a) + 2); return d; }
#define SEK_DEF_WRITE_LONG(i, a, d) { pSekExt->WriteWord[i]((a),(UINT16)((d) >> 16)); pSekExt->WriteWord[i]((a) + 2,(UINT16)((d) & 0xffff)); }

#define SEK_CORE_A68K (2)
#define SEK_CORE_M68K (1)
#define SEK_CORE_C68K (0)

extern INT32 nSekCpuCore; // 0 - c68k, 1 - m68k, 2 - a68k
extern INT32 DebugStep; // 0 - off, 1 - on

extern struct SekExt *SekExt[SEK_MAX], *pSekExt;
extern INT32 nSekActive;										// The cpu which is currently being emulated
extern INT32 nSekCyclesTotal, nSekCyclesScanline, nSekCyclesSegment, nSekCyclesDone, nSekCyclesToDo;

UINT32 SekReadByte(UINT32 a);
UINT32 SekReadWord(UINT32 a);
UINT32 SekReadLong(UINT32 a);

UINT32 SekFetchByte(UINT32 a);
UINT32 SekFetchWord(UINT32 a);
UINT32 SekFetchLong(UINT32 a);

void SekWriteByte(UINT32 a, UINT8 d);
void SekWriteWord(UINT32 a, UINT16 d);
void SekWriteLong(UINT32 a, UINT32 d);

void SekWriteByteROM(UINT32 a, UINT8 d);
void SekWriteWordROM(UINT32 a, UINT16 d);
void SekWriteLongROM(UINT32 a, UINT32 d);

INT32 SekInit(INT32 nCount, INT32 nCPUType);
INT32 SekExit();

void SekNewFrame();
void SekSetCyclesScanline(INT32 nCycles);

void SekClose();
void SekOpen(const INT32 i);
INT32 SekGetActive();

void SekSetIRQLine(const INT32 line, const INT32 status);
void SekReset();

void SekRunEnd();
void SekRunAdjust(const INT32 nCycles);

INT32 SekRun(const INT32 nCycles);

INT32 SekIdle(INT32 nCycles);

INT32 SekSegmentCycles();

INT32 SekTotalCycles();

INT32 SekCurrentScanline();

// Map areas of memory
INT32 SekMapMemory(UINT8* pMemory, UINT32 nStart, UINT32 nEnd, INT32 nType);
INT32 SekMapHandler(UINT32 nHandler, UINT32 nStart, UINT32 nEnd, INT32 nType);

// Set handlers
INT32 SekSetReadByteHandler(INT32 i, pSekReadByteHandler pHandler);
INT32 SekSetWriteByteHandler(INT32 i, pSekWriteByteHandler pHandler);
INT32 SekSetReadWordHandler(INT32 i, pSekReadWordHandler pHandler);
INT32 SekSetWriteWordHandler(INT32 i, pSekWriteWordHandler pHandler);
INT32 SekSetReadLongHandler(INT32 i, pSekReadLongHandler pHandler);
INT32 SekSetWriteLongHandler(INT32 i, pSekWriteLongHandler pHandler);

// Set callbacks
INT32 SekSetResetCallback(pSekResetCallback pCallback);
INT32 SekSetRTECallback(pSekRTECallback pCallback);
INT32 SekSetIrqCallback(pSekIrqCallback pCallback);
INT32 SekSetCmpCallback(pSekCmpCallback pCallback);
INT32 SekSetTASCallback(pSekTASCallback pCallback);

// Get a CPU's PC
UINT32 SekGetPC(INT32 n);

INT32 SekScan(INT32 nAction);

#endif //_SEK_H_
