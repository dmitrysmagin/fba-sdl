// 680x0 (Sixty Eight K) Interface
#include "burnint.h"
#include "m68000_intf.h"
#include "m68000_debug.h"

INT32 nSekCpuCore = SEK_CORE_M68K;  // 0 - c68k, 1 - m68k, 2 - a68k
INT32 DebugStep = 0; // 0 - off, 1 - on

#ifdef EMU_M68K
INT32 nSekM68KContextSize[SEK_MAX];
INT8* SekM68KContext[SEK_MAX];
#endif
 
#ifdef EMU_C68K
c68k_struc * SekC68KCurrentContext = NULL;
c68k_struc * SekC68KContext[SEK_MAX];
#endif

INT32 nSekCount = -1;						// Number of allocated 68000s
struct SekExt *SekExt[SEK_MAX] = { NULL, }, *pSekExt = NULL;

INT32 nSekActive = -1;						// The cpu which is currently being emulated
INT32 nSekCyclesTotal, nSekCyclesScanline, nSekCyclesSegment, nSekCyclesDone, nSekCyclesToDo;

INT32 nSekCPUType[SEK_MAX], nSekCycles[SEK_MAX], nSekIRQPending[SEK_MAX];

#if defined (FBA_DEBUG)

void (*SekDbgBreakpointHandlerRead)(UINT32, INT32) = NULL;
void (*SekDbgBreakpointHandlerFetch)(UINT32, INT32) = NULL;
void (*SekDbgBreakpointHandlerWrite)(UINT32, INT32) = NULL;

UINT32 (*SekDbgFetchByteDisassembler)(UINT32) = NULL;
UINT32 (*SekDbgFetchWordDisassembler)(UINT32) = NULL;
UINT32 (*SekDbgFetchLongDisassembler)(UINT32) = NULL;

static struct { UINT32 address; INT32 id; } BreakpointDataRead[9]  = { { 0, 0 }, };
static struct { UINT32 address; INT32 id; } BreakpointDataWrite[9] = { { 0, 0 }, };
static struct { UINT32 address; INT32 id; } BreakpointFetch[9] = { { 0, 0 }, };

#endif

#if defined (EMU_A68K)
static void UpdateA68KContext()
{
#if 0
	if (M68000_regs.srh & 20) {		// Supervisor mode
		M68000_regs.isp = M68000_regs.a[7];
	} else {						// User mode
		M68000_regs.usp = M68000_regs.a[7];
	}

	M68000_regs.sr  = (M68000_regs.srh <<  8) & 0xFF00;	// T, S, M, I
	M68000_regs.sr |= (M68000_regs.xc  <<  4) & 0x0010;	// X
	M68000_regs.sr |= (M68000_regs.ccr >>  4) & 0x0008;	// N
	M68000_regs.sr |= (M68000_regs.ccr >>  4) & 0x0004;	// Z
	M68000_regs.sr |= (M68000_regs.ccr >> 10) & 0x0002;	// V
	M68000_regs.sr |= (M68000_regs.ccr      ) & 0x0001;	// C
#endif
}

static UINT32 GetA68KSR()
{
	UpdateA68KContext();

	return M68000_regs.sr;
}

static UINT32 GetA68KISP()
{
	UpdateA68KContext();

	return M68000_regs.isp;
}

static UINT32 GetA68KUSP()
{
	UpdateA68KContext();

	return M68000_regs.usp;
}
#endif

#if defined (FBA_DEBUG)

inline static void CheckBreakpoint_R(UINT32 a, const UINT32 m)
{
	a &= m;

	for (INT32 i = 0; BreakpointDataRead[i].address; i++) {
		if ((BreakpointDataRead[i].address & m) == a) {

#ifdef EMU_A68K
			UpdateA68KContext();
#endif

			if(SekDbgBreakpointHandlerRead)
				SekDbgBreakpointHandlerRead(a, BreakpointDataRead[i].id);
			return;
		}
	}
}

inline static void CheckBreakpoint_W(UINT32 a, const UINT32 m)
{
	a &= m;

	for (INT32 i = 0; BreakpointDataWrite[i].address; i++) {
		if ((BreakpointDataWrite[i].address & m) == a) {

#ifdef EMU_A68K
			UpdateA68KContext();
#endif

			if(SekDbgBreakpointHandlerWrite)
				SekDbgBreakpointHandlerWrite(a, BreakpointDataWrite[i].id);
			return;
		}
	}
}

inline static void CheckBreakpoint_PC()
{
	for (INT32 i = 0; BreakpointFetch[i].address; i++) {
		if (BreakpointFetch[i].address == (UINT32)SekGetPC(-1)) {

#ifdef EMU_A68K
			UpdateA68KContext();
#endif

			if(SekDbgBreakpointHandlerFetch)
				SekDbgBreakpointHandlerFetch(SekGetPC(-1), BreakpointFetch[i].id);
			return;
		}
	}
}

inline static void SingleStep_PC()
{
#ifdef EMU_A68K
	UpdateA68KContext();
#endif

	if(SekDbgBreakpointHandlerFetch)
		SekDbgBreakpointHandlerFetch(SekGetPC(-1), 0);
}

#endif

// ----------------------------------------------------------------------------
// Default memory access handlers

UINT8 __fastcall DefReadByte(UINT32) { return 0; }
void __fastcall DefWriteByte(UINT32, UINT8) { }

#define DEFWORDHANDLERS(i)																				\
	UINT16 __fastcall DefReadWord##i(UINT32 a) { SEK_DEF_READ_WORD(i, a) }				\
	void __fastcall DefWriteWord##i(UINT32 a, UINT16 d) { SEK_DEF_WRITE_WORD(i, a ,d) }
#define DEFLONGHANDLERS(i)																				\
	UINT32 __fastcall DefReadLong##i(UINT32 a) { SEK_DEF_READ_LONG(i, a) }					\
	void __fastcall DefWriteLong##i(UINT32 a, UINT32 d) { SEK_DEF_WRITE_LONG(i, a , d) }

DEFWORDHANDLERS(0)
DEFLONGHANDLERS(0)

#if SEK_MAXHANDLER >= 2
 DEFWORDHANDLERS(1)
 DEFLONGHANDLERS(1)
#endif

#if SEK_MAXHANDLER >= 3
 DEFWORDHANDLERS(2)
 DEFLONGHANDLERS(2)
#endif

#if SEK_MAXHANDLER >= 4
 DEFWORDHANDLERS(3)
 DEFLONGHANDLERS(3)
#endif

#if SEK_MAXHANDLER >= 5
 DEFWORDHANDLERS(4)
 DEFLONGHANDLERS(4)
#endif

#if SEK_MAXHANDLER >= 6
 DEFWORDHANDLERS(5)
 DEFLONGHANDLERS(5)
#endif

#if SEK_MAXHANDLER >= 7
 DEFWORDHANDLERS(6)
 DEFLONGHANDLERS(6)
#endif

#if SEK_MAXHANDLER >= 8
 DEFWORDHANDLERS(7)
 DEFLONGHANDLERS(7)
#endif

#if SEK_MAXHANDLER >= 9
 DEFWORDHANDLERS(8)
 DEFLONGHANDLERS(8)
#endif

#if SEK_MAXHANDLER >= 10
 DEFWORDHANDLERS(9)
 DEFLONGHANDLERS(9)
#endif

// ----------------------------------------------------------------------------
// Memory access functions

// Mapped Memory lookup (               for read)
#define FIND_R(x) pSekExt->MemMap[ x >> SEK_SHIFT]
// Mapped Memory lookup (+ SEK_WADD     for write)
#define FIND_W(x) pSekExt->MemMap[(x >> SEK_SHIFT) + SEK_WADD]
// Mapped Memory lookup (+ SEK_WADD * 2 for fetch)
#define FIND_F(x) pSekExt->MemMap[(x >> SEK_SHIFT) + SEK_WADD * 2]

// Normal memory access functions
inline static UINT8 ReadByte(UINT32 a)
{
	UINT8* pr;

	a &= 0xFFFFFF;

	pr = FIND_R(a);
#ifdef FBA_DEBUG
	CheckBreakpoint_R(a, ~0);
#endif
	if ((uintptr_t)pr >= SEK_MAXHANDLER) {
		a ^= 1;
		return pr[a & SEK_PAGEM];
	}
	return pSekExt->ReadByte[(uintptr_t)pr](a);
}

inline static UINT8 FetchByte(UINT32 a)
{
	UINT8* pr;

	a &= 0xFFFFFF;

//	bprintf(PRINT_NORMAL, _T("fetch8 0x%08X\n"), a);

	pr = FIND_F(a);
	if ((uintptr_t)pr >= SEK_MAXHANDLER) {
		a ^= 1;
		return pr[a & SEK_PAGEM];
	}
	return pSekExt->ReadByte[(uintptr_t)pr](a);
}

inline static void WriteByte(UINT32 a, UINT8 d)
{
	UINT8* pr;

	a &= 0xFFFFFF;

	pr = FIND_W(a);
#ifdef FBA_DEBUG
	CheckBreakpoint_W(a, ~0);
#endif
	if ((uintptr_t)pr >= SEK_MAXHANDLER) {
		a ^= 1;
		pr[a & SEK_PAGEM] = (UINT8)d;
		return;
	}
	pSekExt->WriteByte[(uintptr_t)pr](a, d);
}

inline static void WriteByteROM(UINT32 a, UINT8 d)
{
	UINT8* pr;

	a &= 0xFFFFFF;

	pr = FIND_R(a);
	if ((uintptr_t)pr >= SEK_MAXHANDLER) {
		a ^= 1;
		pr[a & SEK_PAGEM] = (UINT8)d;
		return;
	}
	pSekExt->WriteByte[(uintptr_t)pr](a, d);
}

inline static UINT16 ReadWord(UINT32 a)
{
	UINT8* pr;

	a &= 0xFFFFFF;

	pr = FIND_R(a);
#ifdef FBA_DEBUG
	CheckBreakpoint_R(a, ~1);
#endif
	if ((uintptr_t)pr >= SEK_MAXHANDLER) {
		return BURN_ENDIAN_SWAP_INT16(*((UINT16*)(pr + (a & SEK_PAGEM))));
	}
	return pSekExt->ReadWord[(uintptr_t)pr](a);
}

inline static UINT16 FetchWord(UINT32 a)
{
	UINT8* pr;

	a &= 0xFFFFFF;

//	bprintf(PRINT_NORMAL, _T("fetch16 0x%08X\n"), a);

	pr = FIND_F(a);
	if ((uintptr_t)pr >= SEK_MAXHANDLER) {
		return BURN_ENDIAN_SWAP_INT16(*((UINT16*)(pr + (a & SEK_PAGEM))));
	}
	return pSekExt->ReadWord[(uintptr_t)pr](a);
}

inline static void WriteWord(UINT32 a, UINT16 d)
{
	UINT8* pr;

	a &= 0xFFFFFF;

	pr = FIND_W(a);
#ifdef FBA_DEBUG
	CheckBreakpoint_W(a, ~1);
#endif
	if ((uintptr_t)pr >= SEK_MAXHANDLER) {
		*((UINT16*)(pr + (a & SEK_PAGEM))) = (UINT16)BURN_ENDIAN_SWAP_INT16(d);
		return;
	}
	pSekExt->WriteWord[(uintptr_t)pr](a, d);
}

inline static void WriteWordROM(UINT32 a, UINT16 d)
{
	UINT8* pr;

	a &= 0xFFFFFF;

	pr = FIND_R(a);
	if ((uintptr_t)pr >= SEK_MAXHANDLER) {
		*((UINT16*)(pr + (a & SEK_PAGEM))) = (UINT16)d;
		return;
	}
	pSekExt->WriteWord[(uintptr_t)pr](a, d);
}

inline static UINT32 ReadLong(UINT32 a)
{
	UINT8* pr;

	a &= 0xFFFFFF;

	pr = FIND_R(a);
#ifdef FBA_DEBUG
	CheckBreakpoint_R(a, ~1);
#endif
	if ((uintptr_t)pr >= SEK_MAXHANDLER) {
		UINT32 r = *((UINT32*)(pr + (a & SEK_PAGEM)));
		r = (r >> 16) | (r << 16);
		return BURN_ENDIAN_SWAP_INT32(r);
	}
	return pSekExt->ReadLong[(uintptr_t)pr](a);
}

inline static UINT32 FetchLong(UINT32 a)
{
	UINT8* pr;

	a &= 0xFFFFFF;

//	bprintf(PRINT_NORMAL, _T("fetch32 0x%08X\n"), a);

	pr = FIND_F(a);
	if ((uintptr_t)pr >= SEK_MAXHANDLER) {
		UINT32 r = *((UINT32*)(pr + (a & SEK_PAGEM)));
		r = (r >> 16) | (r << 16);
		return BURN_ENDIAN_SWAP_INT32(r);
	}
	return pSekExt->ReadLong[(uintptr_t)pr](a);
}

inline static void WriteLong(UINT32 a, UINT32 d)
{
	UINT8* pr;

	a &= 0xFFFFFF;

	pr = FIND_W(a);
#ifdef FBA_DEBUG
	CheckBreakpoint_W(a, ~1);
#endif
	if ((uintptr_t)pr >= SEK_MAXHANDLER) {
		d = (d >> 16) | (d << 16);
		*((UINT32*)(pr + (a & SEK_PAGEM))) = BURN_ENDIAN_SWAP_INT32(d);
		return;
	}
	pSekExt->WriteLong[(uintptr_t)pr](a, d);
}

inline static void WriteLongROM(UINT32 a, UINT32 d)
{
	UINT8* pr;

	a &= 0xFFFFFF;

	pr = FIND_R(a);
	if ((uintptr_t)pr >= SEK_MAXHANDLER) {
		d = (d >> 16) | (d << 16);
		*((UINT32*)(pr + (a & SEK_PAGEM))) = d;
		return;
	}
	pSekExt->WriteLong[(uintptr_t)pr](a, d);
}

// ----------------------------------------------------------------------------
// A68K variables

#ifdef EMU_A68K
struct A68KContext* SekRegs[SEK_MAX] = { NULL, };
#endif

struct A68KInter {
	void (__fastcall *DebugCallback) ();
	UINT8  (__fastcall *Read8) (UINT32 a);
	UINT16 (__fastcall *Read16)(UINT32 a);
	UINT32   (__fastcall *Read32)(UINT32 a);
	void (__fastcall *Write8)  (UINT32 a, UINT8 d);
	void (__fastcall *Write16) (UINT32 a, UINT16 d);
	void (__fastcall *Write32) (UINT32 a, UINT32 d);
	void (__fastcall *ChangePc)(UINT32 a);
	UINT8  (__fastcall *PcRel8) (UINT32 a);
	UINT16 (__fastcall *PcRel16)(UINT32 a);
	UINT32   (__fastcall *PcRel32)(UINT32 a);
	UINT16 (__fastcall *Dir16)(UINT32 a);
	UINT32   (__fastcall *Dir32)(UINT32 a);
};

extern "C" {

#ifdef EMU_A68K
 UINT8* OP_ROM = NULL;
 UINT8* OP_RAM = NULL;

#ifndef EMU_M68K
 INT32 m68k_ICount = 0;
#endif

 UINT32 mem_amask = 0xFFFFFF;			// 24-bit bus
#endif

 UINT32 mame_debug = 0, cur_mrhard = 0, m68k_illegal_opcode = 0, illegal_op = 0, illegal_pc = 0, opcode_entry = 0;

 //struct A68KInter a68k_memory_intf;
}

extern "C" struct A68KInter a68k_memory_intf;

UINT8  __fastcall A68KRead8 (UINT32 a) { return ReadByte(a);}
UINT16 __fastcall A68KRead16(UINT32 a) { return ReadWord(a);}
UINT32   __fastcall A68KRead32(UINT32 a) { return ReadLong(a);}
UINT8  __fastcall A68KFetch8 (UINT32 a) { return FetchByte(a);}
UINT16 __fastcall A68KFetch16(UINT32 a) { return FetchWord(a);}
UINT32   __fastcall A68KFetch32(UINT32 a) { return FetchLong(a);}
void __fastcall A68KWrite8 (UINT32 a,UINT8 d)  { WriteByte(a,d);}
void __fastcall A68KWrite16(UINT32 a,UINT16 d) { WriteWord(a,d);}
void __fastcall A68KWrite32(UINT32 a,UINT32 d)   { WriteLong(a,d);}

#if defined (FBA_DEBUG)
void __fastcall A68KCheckBreakpoint() { CheckBreakpoint_PC(); }
void __fastcall A68KSingleStep() { SingleStep_PC(); }
#endif

#ifdef EMU_A68K
void __fastcall A68KChangePC(UINT32 pc)
{
	pc &= 0xFFFFFF;

	// Adjust OP_ROM to the current bank
	OP_ROM = FIND_F(pc) - (pc & ~SEK_PAGEM);

	// Set the current bank number
	M68000_regs.nAsmBank = pc >> SEK_BITS;
}
#endif

#ifdef EMU_M68K
extern "C" {
UINT32 __fastcall M68KReadByte(UINT32 a) { return (UINT32)ReadByte(a); }
UINT32 __fastcall M68KReadWord(UINT32 a) { return (UINT32)ReadWord(a); }
UINT32 __fastcall M68KReadLong(UINT32 a) { return               ReadLong(a); }

UINT32 __fastcall M68KFetchByte(UINT32 a) { return (UINT32)FetchByte(a); }
UINT32 __fastcall M68KFetchWord(UINT32 a) { return (UINT32)FetchWord(a); }
UINT32 __fastcall M68KFetchLong(UINT32 a) { return               FetchLong(a); }

#ifdef FBA_DEBUG
void M68KCheckBreakpoint() { CheckBreakpoint_PC(); }
void M68KSingleStep() { SingleStep_PC(); }

UINT32 (__fastcall *M68KReadByteDebug)(UINT32);
UINT32 (__fastcall *M68KReadWordDebug)(UINT32);
UINT32 (__fastcall *M68KReadLongDebug)(UINT32);

void (__fastcall *M68KWriteByteDebug)(UINT32, UINT32);
void (__fastcall *M68KWriteWordDebug)(UINT32, UINT32);
void (__fastcall *M68KWriteLongDebug)(UINT32, UINT32);
#endif

void __fastcall M68KWriteByte(UINT32 a, UINT32 d) { WriteByte(a, d); }
void __fastcall M68KWriteWord(UINT32 a, UINT32 d) { WriteWord(a, d); }
void __fastcall M68KWriteLong(UINT32 a, UINT32 d) { WriteLong(a, d); }
}
#endif

#ifdef EMU_C68K
extern "C" {
UINT8 C68KReadByte(UINT32 a) { return ReadByte(a); }
UINT16 C68KReadWord(UINT32 a) { return ReadWord(a); }
UINT8 C68KFetchByte(UINT32 a) { return FetchByte(a); }
UINT16 C68KFetchWord(UINT32 a) { return FetchWord(a); }
void C68KWriteByte(UINT32 a, UINT8 d) { WriteByte(a, d); }
void C68KWriteWord(UINT32 a, UINT16 d) { WriteWord(a, d); }

UINT32 C68KRebasePC(UINT32 pc) {
//	bprintf(PRINT_NORMAL, _T("C68KRebasePC 0x%08x\n"), pc);
	pc &= 0xFFFFFF;
	SekC68KCurrentContext->BasePC = (UINT32)FIND_F(pc) - (pc & ~SEK_PAGEM);
	return SekC68KCurrentContext->BasePC + pc;
}

INT32 C68KInterruptCallBack(INT32 irqline)
{
	if (nSekIRQPending[nSekActive] & (CPU_IRQSTATUS_AUTO << 12)) {
		SekC68KContext[nSekActive]->IRQState = 0;	//CLEAR_LINE
		SekC68KContext[nSekActive]->IRQLine = 0;
	}
	
	nSekIRQPending[nSekActive] = 0;
	
	if (pSekExt->IrqCallback) {
		return pSekExt->IrqCallback(irqline);
	}

	return C68K_INTERRUPT_AUTOVECTOR_EX + irqline;
}

void C68KResetCallBack()
{
	if ( pSekExt->ResetCallback )
		pSekExt->ResetCallback();
}

}
#endif

#ifdef EMU_A68K

struct A68KInter a68k_inter_normal = {
	NULL,
	A68KRead8,
	A68KRead16,
	A68KRead32,
	A68KWrite8,
	A68KWrite16,
	A68KWrite32,
	A68KChangePC,
	A68KFetch8,
	A68KFetch16,
	A68KFetch32,
	A68KRead16,	// unused
	A68KRead32,	// unused
};

#endif

// ----------------------------------------------------------------------------
// Memory accesses (non-emu specific)

UINT32 SekReadByte(UINT32 a) { return (UINT32)ReadByte(a); }
UINT32 SekReadWord(UINT32 a) { return (UINT32)ReadWord(a); }
UINT32 SekReadLong(UINT32 a) { return ReadLong(a); }

UINT32 SekFetchByte(UINT32 a) { return (UINT32)FetchByte(a); }
UINT32 SekFetchWord(UINT32 a) { return (UINT32)FetchWord(a); }
UINT32 SekFetchLong(UINT32 a) { return FetchLong(a); }

void SekWriteByte(UINT32 a, UINT8 d) { WriteByte(a, d); }
void SekWriteWord(UINT32 a, UINT16 d) { WriteWord(a, d); }
void SekWriteLong(UINT32 a, UINT32 d) { WriteLong(a, d); }

void SekWriteByteROM(UINT32 a, UINT8 d) { WriteByteROM(a, d); }
void SekWriteWordROM(UINT32 a, UINT16 d) { WriteWordROM(a, d); }
void SekWriteLongROM(UINT32 a, UINT32 d) { WriteLongROM(a, d); }


// ----------------------------------------------------------------------------
// Callbacks for A68K

#ifdef EMU_A68K
static INT32 A68KIRQAcknowledge(INT32 nIRQ)
{
	if (nSekIRQPending[nSekActive] & (CPU_IRQSTATUS_AUTO << 12)) {
		M68000_regs.irq &= 0x78;
		nSekIRQPending[nSekActive] = 0;
	}

	nSekIRQPending[nSekActive] = 0;
	
	if (pSekExt->IrqCallback) {
		return pSekExt->IrqCallback(nIRQ);
	}

	return -1;
}

static INT32 A68KResetCallback()
{
	if (pSekExt->ResetCallback == NULL) {
		return 0;
	}
	return pSekExt->ResetCallback();
}


static INT32 A68KRTECallback()
{
	if (pSekExt->RTECallback == NULL) {
		return 0;
	}
	return pSekExt->RTECallback();
}

static INT32 A68KCmpCallback(UINT32 val, INT32 reg)
{
	if (pSekExt->CmpCallback == NULL) {
		return 0;
	}
	return pSekExt->CmpCallback(val, reg);
}


static INT32 SekSetup(struct A68KContext* psr)
{
	psr->IrqCallback = A68KIRQAcknowledge;
	psr->ResetCallback = A68KResetCallback;
	psr->RTECallback = A68KRTECallback;
	psr->CmpCallback = A68KCmpCallback;

	return 0;
}
#endif

// ----------------------------------------------------------------------------
// Callbacks for Musashi

#ifdef EMU_M68K
extern "C" INT32 M68KIRQAcknowledge(INT32 nIRQ)
{
	if (nSekIRQPending[nSekActive] & (CPU_IRQSTATUS_AUTO << 12)) {
		m68k_set_irq(0);
		nSekIRQPending[nSekActive] = 0;
	}
	
	if (pSekExt->IrqCallback) {
		return pSekExt->IrqCallback(nIRQ);
	}

	return M68K_INT_ACK_AUTOVECTOR;
}

extern "C" void M68KResetCallback()
{
	if (pSekExt->ResetCallback) {
		pSekExt->ResetCallback();
	}
}

extern "C" void M68KRTECallback()
{
	if (pSekExt->RTECallback) {
		pSekExt->RTECallback();
	}
}

extern "C" void M68KcmpildCallback(UINT32 val, INT32 reg)
{
	if (pSekExt->CmpCallback) {
		pSekExt->CmpCallback(val, reg);
	}
}

extern "C" INT32 M68KTASCallback()
{
	if (pSekExt->TASCallback) {
		return pSekExt->TASCallback();
	}

	return 1; // enable by default
}
#endif

// ----------------------------------------------------------------------------
// Initialisation/exit/reset

#ifdef EMU_A68K
static INT32 SekInitCPUA68K(INT32 nCount, INT32 nCPUType)
{
	if (nCPUType != 0x68000) {
		return 1;
	}

	nSekCPUType[nCount] = 0;

	// Allocate emu-specific cpu states
	SekRegs[nCount] = (struct A68KContext*)malloc(sizeof(struct A68KContext));
	if (SekRegs[nCount] == NULL) {
		return 1;
	}

	// Setup each cpu context
	memset(SekRegs[nCount], 0, sizeof(struct A68KContext));
	SekSetup(SekRegs[nCount]);

	// Init cpu emulator
	M68000_RESET();

	return 0;
}
#endif

#ifdef EMU_M68K
static INT32 SekInitCPUM68K(INT32 nCount, INT32 nCPUType)
{
	nSekCPUType[nCount] = nCPUType;

	switch (nCPUType) {
		case 0x68000:
			m68k_set_cpu_type(M68K_CPU_TYPE_68000);
			break;
		case 0x68010:
			m68k_set_cpu_type(M68K_CPU_TYPE_68010);
			break;
		case 0x68EC020:
			m68k_set_cpu_type(M68K_CPU_TYPE_68EC020);
			break;
		default:
			return 1;
	}

	nSekM68KContextSize[nCount] = m68k_context_size();
	SekM68KContext[nCount] = (INT8*)malloc(nSekM68KContextSize[nCount]);
	if (SekM68KContext[nCount] == NULL) {
		return 1;
	}
	memset(SekM68KContext[nCount], 0, nSekM68KContextSize[nCount]);
	m68k_get_context(SekM68KContext[nCount]);

	return 0;
}
#endif

#ifdef EMU_C68K
static INT32 SekInitCPUC68K(INT32 nCount, INT32 nCPUType)
{
	if (nCPUType != 0x68000) return 1;
	nSekCPUType[nCount] = 0;

	SekC68KContext[nCount] = (c68k_struc *)malloc( sizeof( c68k_struc ) );
	if (SekC68KContext[nCount] == NULL)	return 1;

	memset(SekC68KContext[nCount], 0, sizeof( c68k_struc ));
	SekC68KCurrentContext = SekC68KContext[nCount];

	SekC68KCurrentContext->Rebase_PC = C68KRebasePC;
	
	SekC68KCurrentContext->Read_Byte = C68KReadByte;
	SekC68KCurrentContext->Read_Word = C68KReadWord;
	SekC68KCurrentContext->Read_Byte_PC_Relative = C68KFetchByte;
	SekC68KCurrentContext->Read_Word_PC_Relative = C68KFetchWord;
	SekC68KCurrentContext->Write_Byte = C68KWriteByte;
	SekC68KCurrentContext->Write_Word = C68KWriteWord;
	
	SekC68KCurrentContext->Interrupt_CallBack = C68KInterruptCallBack;
	SekC68KCurrentContext->Reset_CallBack = C68KResetCallBack;
	return 0;
}
#endif


void SekNewFrame()
{
	for (INT32 i = 0; i <= nSekCount; i++) {
		nSekCycles[i] = 0;
	}

	nSekCyclesTotal = 0;
}

void SekSetCyclesScanline(INT32 nCycles)
{
	nSekCyclesScanline = nCycles;
}

INT32 SekInit(INT32 nCount, INT32 nCPUType)
{
	struct SekExt* ps = NULL;

	if (nSekActive >= 0) {
		SekClose();
		nSekActive = -1;
	}

	if (nCount > nSekCount) {
		nSekCount = nCount;
	}

	// only m68k supports 68010 and 68EC020
	if(nCount == 0 && nCPUType != 0x68000 && nSekCpuCore != SEK_CORE_M68K) nSekCpuCore = SEK_CORE_M68K;

	// Allocate cpu extenal data (memory map etc)
	SekExt[nCount] = (struct SekExt*)malloc(sizeof(struct SekExt));
	if (SekExt[nCount] == NULL) {
		SekExit();
		return 1;
	}
	memset(SekExt[nCount], 0, sizeof(struct SekExt));

	// Put in default memory handlers
	ps = SekExt[nCount];

	for (INT32 j = 0; j < SEK_MAXHANDLER; j++) {
		ps->ReadByte[j]  = DefReadByte;
		ps->WriteByte[j] = DefWriteByte;
	}

	ps->ReadWord[0]  = DefReadWord0;
	ps->WriteWord[0] = DefWriteWord0;
	ps->ReadLong[0]  = DefReadLong0;
	ps->WriteLong[0] = DefWriteLong0;

#if SEK_MAXHANDLER >= 2
	ps->ReadWord[1]  = DefReadWord1;
	ps->WriteWord[1] = DefWriteWord1;
	ps->ReadLong[1]  = DefReadLong1;
	ps->WriteLong[1] = DefWriteLong1;
#endif

#if SEK_MAXHANDLER >= 3
	ps->ReadWord[2]  = DefReadWord2;
	ps->WriteWord[2] = DefWriteWord2;
	ps->ReadLong[2]  = DefReadLong2;
	ps->WriteLong[2] = DefWriteLong2;
#endif

#if SEK_MAXHANDLER >= 4
	ps->ReadWord[3]  = DefReadWord3;
	ps->WriteWord[3] = DefWriteWord3;
	ps->ReadLong[3]  = DefReadLong3;
	ps->WriteLong[3] = DefWriteLong3;
#endif

#if SEK_MAXHANDLER >= 5
	ps->ReadWord[4]  = DefReadWord4;
	ps->WriteWord[4] = DefWriteWord4;
	ps->ReadLong[4]  = DefReadLong4;
	ps->WriteLong[4] = DefWriteLong4;
#endif

#if SEK_MAXHANDLER >= 6
	ps->ReadWord[5]  = DefReadWord5;
	ps->WriteWord[5] = DefWriteWord5;
	ps->ReadLong[5]  = DefReadLong5;
	ps->WriteLong[5] = DefWriteLong5;
#endif

#if SEK_MAXHANDLER >= 7
	ps->ReadWord[6]  = DefReadWord6;
	ps->WriteWord[6] = DefWriteWord6;
	ps->ReadLong[6]  = DefReadLong6;
	ps->WriteLong[6] = DefWriteLong6;
#endif

#if SEK_MAXHANDLER >= 8
	ps->ReadWord[7]  = DefReadWord7;
	ps->WriteWord[7] = DefWriteWord7;
	ps->ReadLong[7]  = DefReadLong7;
	ps->WriteLong[7] = DefWriteLong7;
#endif

#if SEK_MAXHANDLER >= 9
	ps->ReadWord[8]  = DefReadWord8;
	ps->WriteWord[8] = DefWriteWord8;
	ps->ReadLong[8]  = DefReadLong8;
	ps->WriteLong[8] = DefWriteLong8;
#endif

#if SEK_MAXHANDLER >= 10
	ps->ReadWord[9]  = DefReadWord9;
	ps->WriteWord[9] = DefWriteWord9;
	ps->ReadLong[9]  = DefReadLong9;
	ps->WriteLong[9] = DefWriteLong9;
#endif

#if SEK_MAXHANDLER >= 11
	for (int j = 10; j < SEK_MAXHANDLER; j++) {
		ps->ReadWord[j]  = DefReadWord0;
		ps->WriteWord[j] = DefWriteWord0;
		ps->ReadLong[j]  = DefReadLong0;
		ps->WriteLong[j] = DefWriteLong0;
	}
#endif

	// Map the normal memory handlers
	SekDbgDisableBreakpoints();

#ifdef FBA_DEBUG
	SekDbgFetchByteDisassembler = &SekFetchByte;
	SekDbgFetchWordDisassembler = &SekFetchWord;
	SekDbgFetchLongDisassembler = &SekFetchLong;
#endif

#ifdef EMU_A68K
	if(nSekCpuCore == SEK_CORE_A68K) {
		if (nCPUType == 0x68000) {
			if (SekInitCPUA68K(nCount, nCPUType)) {
				SekExit();
				return 1;
			}
		}
	}
#endif


#ifdef EMU_M68K
	if(nSekCpuCore == SEK_CORE_M68K) {
		m68k_init();
		if (SekInitCPUM68K(nCount, nCPUType)) {
			SekExit();
			return 1;
		}
	}
#endif

#ifdef EMU_C68K
	if(nSekCpuCore == SEK_CORE_C68K) {
		if(SekInitCPUC68K(nCount, nCPUType)) {
			SekExit();
			return 1;
		}
		C68k_Init( SekC68KCurrentContext );
	}
#endif

	nSekCycles[nCount] = 0;
	nSekIRQPending[nCount] = 0;

	nSekCyclesTotal = 0;
	nSekCyclesScanline = 0;
	return 0;
}

#ifdef EMU_A68K
static void SekCPUExitA68K(INT32 i)
{
	free(SekRegs[i]);
	SekRegs[i] = NULL;
}
#endif

#ifdef EMU_M68K
static void SekCPUExitM68K(INT32 i)
{
		free(SekM68KContext[i]);
		SekM68KContext[i] = NULL;
}
#endif

#ifdef EMU_C68K
static void SekCPUExitC68K(INT32 i)
{
		free(SekC68KContext[i]);
		SekC68KContext[i] = NULL;
}
#endif

INT32 SekExit()
{
	// Deallocate cpu extenal data (memory map etc)
	for (INT32 i = 0; i <= nSekCount; i++) {

#ifdef EMU_A68K
		if(nSekCpuCore == SEK_CORE_A68K) SekCPUExitA68K(i);
#endif

#ifdef EMU_M68K
		if(nSekCpuCore == SEK_CORE_M68K) SekCPUExitM68K(i);
#endif

#ifdef EMU_C68K
		if(nSekCpuCore == SEK_CORE_C68K) SekCPUExitC68K(i);
#endif

		// Deallocate other context data
		free(SekExt[i]);
		SekExt[i] = NULL;
	}
#ifdef EMU_C68K
	if(nSekCpuCore == SEK_CORE_C68K) C68k_Exit();
#endif
	pSekExt = NULL;

	nSekActive = -1;
	nSekCount = -1;
	return 0;
}

void SekReset()
{
#ifdef EMU_A68K
	if(nSekCpuCore == SEK_CORE_A68K) {
		// A68K has no internal support for resetting the processor, so do what's needed ourselves
		M68000_regs.a[7] = FetchLong(0);	// Get initial stackpointer (register A7)
		M68000_regs.pc = FetchLong(4);		// Get initial PC
		M68000_regs.srh = 0x27;				// start in supervisor state
		A68KChangePC(M68000_regs.pc);
	}
#endif

#ifdef EMU_M68K
	if(nSekCpuCore == SEK_CORE_M68K) m68k_pulse_reset();
#endif

#ifdef EMU_C68K
	if(nSekCpuCore == SEK_CORE_C68K) C68k_Reset( SekC68KCurrentContext );
#endif

#ifdef FBA_DEBUG
	if(DebugStep)
		SekDbgEnableSingleStep();
#endif
}

// ----------------------------------------------------------------------------
// Control the active CPU

// Open a CPU
void SekOpen(const INT32 i)
{
	if (i != nSekActive) {
		nSekActive = i;

		pSekExt = SekExt[nSekActive];						// Point to cpu context

#ifdef EMU_A68K
		if(nSekCpuCore == SEK_CORE_A68K) {
			memcpy(&M68000_regs, SekRegs[nSekActive], sizeof(M68000_regs));
			A68KChangePC(M68000_regs.pc);
		}
#endif

#ifdef EMU_M68K
		if(nSekCpuCore == SEK_CORE_M68K) m68k_set_context(SekM68KContext[nSekActive]);
#endif

#ifdef EMU_C68K
		if(nSekCpuCore == SEK_CORE_C68K) SekC68KCurrentContext = SekC68KContext[nSekActive];
#endif

		nSekCyclesTotal = nSekCycles[nSekActive];
	}
}

// Close the active cpu
void SekClose()
{

#ifdef EMU_A68K
	if(nSekCpuCore == SEK_CORE_A68K) {
		memcpy(SekRegs[nSekActive], &M68000_regs, sizeof(M68000_regs));
	}
#endif

#ifdef EMU_M68K
	if(nSekCpuCore == SEK_CORE_M68K) m68k_get_context(SekM68KContext[nSekActive]);
#endif

#ifdef EMU_C68K
	// ....
#endif

	nSekCycles[nSekActive] = nSekCyclesTotal;
	
	nSekActive = -1;
}

// Get the current CPU
INT32 SekGetActive()
{
#if defined FBA_DEBUG
	if (!DebugCPU_SekInitted) bprintf(PRINT_ERROR, _T("SekGetActive called without init\n"));
#endif

	return nSekActive;
}

// Set the status of an IRQ line on the active CPU
void SekSetIRQLine(const INT32 line, const INT32 nstatus)
{
	INT32 status = nstatus << 12; // needed for compatibility

//	bprintf(PRINT_NORMAL, _T("  - irq line %i -> %i\n"), line, status);

	if (status) {
		nSekIRQPending[nSekActive] = line | status;

#ifdef EMU_A68K
		if(nSekCpuCore == SEK_CORE_A68K) {
			nSekCyclesTotal += (nSekCyclesToDo - nSekCyclesDone) - m68k_ICount;
			nSekCyclesDone += (nSekCyclesToDo - nSekCyclesDone) - m68k_ICount;

			M68000_regs.irq = line;
			m68k_ICount = nSekCyclesToDo = -1;					// Force A68K to exit
		}
#endif

#ifdef EMU_M68K
		if(nSekCpuCore == SEK_CORE_M68K) m68k_set_irq(line);
#endif

#ifdef EMU_C68K
		if(nSekCpuCore == SEK_CORE_C68K) {
			//m68k_set_irq(line);
			SekC68KCurrentContext->IRQState = 1;	//ASSERT_LINE
			SekC68KCurrentContext->IRQLine = line;
			SekC68KCurrentContext->HaltState = 0;
		}
#endif

		return;
	}

	nSekIRQPending[nSekActive] = 0;

#ifdef EMU_A68K
	if(nSekCpuCore == SEK_CORE_A68K)  {
		M68000_regs.irq &= 0x78;
	}
#endif

#ifdef EMU_M68K
	if(nSekCpuCore == SEK_CORE_M68K) m68k_set_irq(0);
#endif

#ifdef EMU_C68K
	if(nSekCpuCore == SEK_CORE_C68K) {
		SekC68KCurrentContext->IRQState = 0;	//CLEAR_LINE
		SekC68KCurrentContext->IRQLine = 0;
	}
#endif

}

// Adjust the active CPU's timeslice
void SekRunAdjust(const INT32 nCycles)
{
#if defined(EMU_A68K) || defined(EMU_M68K)
	if(nSekCpuCore == SEK_CORE_A68K || nSekCpuCore == SEK_CORE_M68K) {
		if (nCycles < 0 && m68k_ICount < -nCycles) {
			SekRunEnd();
			return;
		}
	}
#endif

#ifdef EMU_A68K
	if(nSekCpuCore == SEK_CORE_A68K) {
		m68k_ICount += nCycles;
		nSekCyclesToDo += nCycles;
		nSekCyclesSegment += nCycles;
	}
#endif

#ifdef EMU_M68K
	if(nSekCpuCore == SEK_CORE_M68K) {
		nSekCyclesToDo += nCycles;
		m68k_modify_timeslice(nCycles);
	}
#endif

#ifdef EMU_C68K
	if(nSekCpuCore == SEK_CORE_C68K) {
		if (nCycles < 0 && c68k_ICount < -nCycles) {
			SekRunEnd();
			return;
		}
		nSekCyclesToDo += nCycles;
		c68k_ICount += nCycles;
		nSekCyclesSegment += nCycles;
	}
#endif

}

// End the active CPU's timeslice
void SekRunEnd()
{
#ifdef EMU_A68K
	if(nSekCpuCore == SEK_CORE_A68K) {
		nSekCyclesTotal += (nSekCyclesToDo - nSekCyclesDone) - m68k_ICount;
		nSekCyclesDone += (nSekCyclesToDo - nSekCyclesDone) - m68k_ICount;
		nSekCyclesSegment = nSekCyclesDone;
		m68k_ICount = nSekCyclesToDo = -1;						// Force A68K to exit
	}
#endif

#ifdef EMU_M68K
	if(nSekCpuCore == SEK_CORE_M68K) m68k_end_timeslice();
#endif

#ifdef EMU_C68K
	if(nSekCpuCore == SEK_CORE_C68K) {
		nSekCyclesTotal += (nSekCyclesToDo - nSekCyclesDone) - c68k_ICount;
		nSekCyclesDone += (nSekCyclesToDo - nSekCyclesDone) - c68k_ICount;
		nSekCyclesSegment = nSekCyclesDone;
		nSekCyclesToDo = c68k_ICount = -1;
	}
#endif
}

// Run the active CPU
INT32 SekRun(const INT32 nCycles)
{
#ifdef EMU_A68K
	if(nSekCpuCore == SEK_CORE_A68K) {
		nSekCyclesDone = 0;
		nSekCyclesSegment = nCycles;
		do {
			m68k_ICount = nSekCyclesToDo = nSekCyclesSegment - nSekCyclesDone;

			if (M68000_regs.irq == 0x80) {						// Cpu is in stopped state till interrupt
				nSekCyclesDone = nSekCyclesSegment;
				nSekCyclesTotal += nSekCyclesSegment;
			} else {
				M68000_RUN();
				nSekCyclesDone += nSekCyclesToDo - m68k_ICount;
				nSekCyclesTotal += nSekCyclesToDo - m68k_ICount;
			}
		} while (nSekCyclesDone < nSekCyclesSegment);

		nSekCyclesSegment = nSekCyclesDone;
		nSekCyclesToDo = m68k_ICount = -1;
		nSekCyclesDone = 0;

		return nSekCyclesSegment;								// Return the number of cycles actually done
	}
#endif

#ifdef EMU_M68K
	if(nSekCpuCore == SEK_CORE_M68K)  {
		nSekCyclesToDo = nCycles;

		nSekCyclesSegment = m68k_execute(nCycles);

		nSekCyclesTotal += nSekCyclesSegment;
		nSekCyclesToDo = m68k_ICount = -1;

		return nSekCyclesSegment;
	}
#endif

#ifdef EMU_C68K
	if(nSekCpuCore == SEK_CORE_C68K) {
		nSekCyclesToDo = nCycles;
		nSekCyclesSegment = C68k_Exec(SekC68KCurrentContext, nCycles);
		nSekCyclesTotal += nSekCyclesSegment;
		nSekCyclesToDo = c68k_ICount = -1;

		return nSekCyclesSegment;
	}
#endif

	return 0;
}
// ----------------------------------------------------------------------------
// Breakpoint support

void SekDbgDisableBreakpoints()
{
#if defined FBA_DEBUG && defined EMU_M68K
	if(nSekCpuCore == SEK_CORE_M68K) {
		m68k_set_instr_hook_callback(NULL);

		M68KReadByteDebug = M68KReadByte;
		M68KReadWordDebug = M68KReadWord;
		M68KReadLongDebug = M68KReadLong;

		M68KWriteByteDebug = M68KWriteByte;
		M68KWriteWordDebug = M68KWriteWord;
		M68KWriteLongDebug = M68KWriteLong;
	}
#endif

#ifdef EMU_A68K
	if(nSekCpuCore == SEK_CORE_A68K) a68k_memory_intf = a68k_inter_normal;
#endif

	mame_debug = 0;
}

#if defined (FBA_DEBUG)

void SekDbgEnableBreakpoints()
{
	if (BreakpointDataRead[0].address || BreakpointDataWrite[0].address || BreakpointFetch[0].address) {
#ifdef EMU_M68K
		if(nSekCpuCore == SEK_CORE_M68K) {
			SekDbgDisableBreakpoints();

			if (BreakpointFetch[0].address) {
				m68k_set_instr_hook_callback(M68KCheckBreakpoint);
			}
		}
#endif

#ifdef EMU_A68K
		if(nSekCpuCore == SEK_CORE_A68K) {
			if (BreakpointFetch[0].address) {
				a68k_memory_intf.DebugCallback = A68KCheckBreakpoint;
				mame_debug = 255;
			} else {
				a68k_memory_intf.DebugCallback = NULL;
				mame_debug = 0;
			}
		}
#endif
	} else {
		SekDbgDisableBreakpoints();
	}
}

void SekDbgEnableSingleStep()
{
#if defined FBA_DEBUG && defined EMU_M68K
	if(nSekCpuCore == SEK_CORE_M68K) m68k_set_instr_hook_callback(M68KSingleStep);
#endif

#ifdef EMU_A68K
	if(nSekCpuCore == SEK_CORE_A68K) {
		a68k_memory_intf.DebugCallback = A68KSingleStep;
		mame_debug = 254;
	}
#endif

#ifdef EMU_C68K
	if(nSekCpuCore == SEK_CORE_C68K) {
		SekC68KCurrentContext->Dbg_CallBack = SingleStep_PC;
	}
#endif
}

INT32 SekDbgSetBreakpointDataRead(UINT32 nAddress, INT32 nIdentifier)
{
	for (INT32 i = 0; i < 8; i++) {
		if (BreakpointDataRead[i].id == nIdentifier) {

			if	(nAddress) {							// Change breakpoint
				BreakpointDataRead[i].address = nAddress;
			} else {									// Delete breakpoint
				for ( ; i < 8; i++) {
					BreakpointDataRead[i] = BreakpointDataRead[i + 1];
				}
			}

			SekDbgEnableBreakpoints();
			return 0;
		}
	}

	// No breakpoints present, add it to the 1st slot
	BreakpointDataRead[0].address = nAddress;
	BreakpointDataRead[0].id = nIdentifier;

	SekDbgEnableBreakpoints();
	return 0;
}

INT32 SekDbgSetBreakpointDataWrite(UINT32 nAddress, INT32 nIdentifier)
{
	for (INT32 i = 0; i < 8; i++) {
		if (BreakpointDataWrite[i].id == nIdentifier) {

			if (nAddress) {								// Change breakpoint
				BreakpointDataWrite[i].address = nAddress;
			} else {									// Delete breakpoint
				for ( ; i < 8; i++) {
					BreakpointDataWrite[i] = BreakpointDataWrite[i + 1];
				}
			}

			SekDbgEnableBreakpoints();
			return 0;
		}
	}

	// No breakpoints present, add it to the 1st slot
	BreakpointDataWrite[0].address = nAddress;
	BreakpointDataWrite[0].id = nIdentifier;

	SekDbgEnableBreakpoints();
	return 0;
}

INT32 SekDbgSetBreakpointFetch(UINT32 nAddress, INT32 nIdentifier)
{
	for (INT32 i = 0; i < 8; i++) {
		if (BreakpointFetch[i].id == nIdentifier) {

			if (nAddress) {								// Change breakpoint
				BreakpointFetch[i].address = nAddress;
			} else {									// Delete breakpoint
				for ( ; i < 8; i++) {
					BreakpointFetch[i] = BreakpointFetch[i + 1];
				}
			}

			SekDbgEnableBreakpoints();
			return 0;
		}
	}

	// No breakpoints present, add it to the 1st slot
	BreakpointFetch[0].address = nAddress;
	BreakpointFetch[0].id = nIdentifier;

	SekDbgEnableBreakpoints();
	return 0;
}

#endif

// ----------------------------------------------------------------------------
// Memory map setup

// Note - each page is 1 << SEK_BITS.
INT32 SekMapMemory(UINT8* pMemory, UINT32 nStart, UINT32 nEnd, INT32 nType)
{
	UINT8* Ptr = pMemory - nStart;
	UINT8** pMemMap = pSekExt->MemMap + (nStart >> SEK_SHIFT);

	// Special case for ROM banks
	if (nType == MAP_ROM) {
		for (UINT32 i = (nStart & ~SEK_PAGEM); i <= nEnd; i += SEK_PAGE_SIZE, pMemMap++) {
			pMemMap[0]			  = Ptr + i;
			pMemMap[SEK_WADD * 2] = Ptr + i;
		}

		return 0;
	}

	for (UINT32 i = (nStart & ~SEK_PAGEM); i <= nEnd; i += SEK_PAGE_SIZE, pMemMap++) {

		if (nType & MAP_READ) {					// Read
			pMemMap[0]			  = Ptr + i;
		}
		if (nType & MAP_WRITE) {					// Write
			pMemMap[SEK_WADD]	  = Ptr + i;
		}
		if (nType & MAP_FETCH) {					// Fetch
			pMemMap[SEK_WADD * 2] = Ptr + i;
		}
	}

	return 0;
}

INT32 SekMapHandler(UINT32 nHandler, UINT32 nStart, UINT32 nEnd, INT32 nType)
{
	UINT8** pMemMap = pSekExt->MemMap + (nStart >> SEK_SHIFT);

	// Add to memory map
	for (UINT32 i = (nStart & ~SEK_PAGEM); i <= nEnd; i += SEK_PAGE_SIZE, pMemMap++) {

		if (nType & MAP_READ) {					// Read
			pMemMap[0]			  = (UINT8*)nHandler;
		}
		if (nType & MAP_WRITE) {					// Write
			pMemMap[SEK_WADD]	  = (UINT8*)nHandler;
		}
		if (nType & MAP_FETCH) {					// Fetch
			pMemMap[SEK_WADD * 2] = (UINT8*)nHandler;
		}
	}
	return 0;
}

// Set callbacks
INT32 SekSetResetCallback(pSekResetCallback pCallback)
{
	pSekExt->ResetCallback = pCallback;
	return 0;
}

INT32 SekSetRTECallback(pSekRTECallback pCallback)
{
	pSekExt->RTECallback = pCallback;
	return 0;
}

INT32 SekSetIrqCallback(pSekIrqCallback pCallback)
{
	pSekExt->IrqCallback = pCallback;
	return 0;
}

INT32 SekSetCmpCallback(pSekCmpCallback pCallback)
{
	pSekExt->CmpCallback = pCallback;
	return 0;
}

INT32 SekSetTASCallback(pSekTASCallback pCallback)
{
	pSekExt->TASCallback = pCallback;

	return 0;
}

// Set handlers
INT32 SekSetReadByteHandler(INT32 i, pSekReadByteHandler pHandler)
{
	if (i >= SEK_MAXHANDLER) {
		return 1;
	}
	pSekExt->ReadByte[i] = pHandler;
	return 0;
}

INT32 SekSetWriteByteHandler(INT32 i, pSekWriteByteHandler pHandler)
{
	if (i >= SEK_MAXHANDLER) {
		return 1;
	}
	pSekExt->WriteByte[i] = pHandler;
	return 0;
}

INT32 SekSetReadWordHandler(INT32 i, pSekReadWordHandler pHandler)
{
	if (i >= SEK_MAXHANDLER) {
		return 1;
	}
	pSekExt->ReadWord[i] = pHandler;
	return 0;
}

INT32 SekSetWriteWordHandler(INT32 i, pSekWriteWordHandler pHandler)
{
	if (i >= SEK_MAXHANDLER) {
		return 1;
	}
	pSekExt->WriteWord[i] = pHandler;
	return 0;
}

INT32 SekSetReadLongHandler(INT32 i, pSekReadLongHandler pHandler)
{
	if (i >= SEK_MAXHANDLER) {
		return 1;
	}
	pSekExt->ReadLong[i] = pHandler;
	return 0;
}

INT32 SekSetWriteLongHandler(INT32 i, pSekWriteLongHandler pHandler)
{
	if (i >= SEK_MAXHANDLER) {
		return 1;
	}
	pSekExt->WriteLong[i] = pHandler;
	return 0;
}

// ----------------------------------------------------------------------------
// Query register values

UINT32 SekGetPC(INT32 n)
{
#ifdef EMU_A68K
	if(nSekCpuCore == SEK_CORE_A68K) {
		if (n < 0) {								// Currently active CPU
		  return M68000_regs.pc;
		} else {
			return SekRegs[n]->pc;					// Any CPU
		}
	}
#endif

#ifdef EMU_M68K
	if(nSekCpuCore == SEK_CORE_M68K) return m68k_get_reg(NULL, M68K_REG_PC);
#endif

#ifdef EMU_C68K
	if(nSekCpuCore == SEK_CORE_C68K)  return SekC68KCurrentContext->PC - SekC68KCurrentContext->BasePC;
#endif

	return 0;
}

INT32 SekDbgGetCPUType()
{
#if 0
	if(nSekCpuCore == SEK_CORE_M68K) {
		switch (nSekCPUType[nSekActive]) {
			case 0:
			case 0x68000:
				return M68K_CPU_TYPE_68000;
			case 0x68010:
				return M68K_CPU_TYPE_68010;
			case 0x68EC020:
				return M68K_CPU_TYPE_68EC020;
		}
	}
#endif
	return 0;
}

INT32 SekDbgGetPendingIRQ()
{
	return nSekIRQPending[nSekActive] & 7;
}

UINT32 SekDbgGetRegister(SekRegister nRegister)
{
#ifdef FBA_DEBUG
	if(nSekCpuCore == SEK_CORE_A68K) {
		switch (nRegister) {
			case SEK_REG_D0:
				return M68000_regs.d[0];
			case SEK_REG_D1:
				return M68000_regs.d[1];
			case SEK_REG_D2:
				return M68000_regs.d[2];
			case SEK_REG_D3:
				return M68000_regs.d[3];
			case SEK_REG_D4:
				return M68000_regs.d[4];
			case SEK_REG_D5:
				return M68000_regs.d[5];
			case SEK_REG_D6:
				return M68000_regs.d[6];
			case SEK_REG_D7:
				return M68000_regs.d[7];

			case SEK_REG_A0:
				return M68000_regs.a[0];
			case SEK_REG_A1:
				return M68000_regs.a[1];
			case SEK_REG_A2:
				return M68000_regs.a[2];
			case SEK_REG_A3:
				return M68000_regs.a[3];
			case SEK_REG_A4:
				return M68000_regs.a[4];
			case SEK_REG_A5:
				return M68000_regs.a[5];
			case SEK_REG_A6:
				return M68000_regs.a[6];
			case SEK_REG_A7:
				return M68000_regs.a[7];

			case SEK_REG_PC:
				return M68000_regs.pc;

			case SEK_REG_SR:
				return GetA68KSR();

			case SEK_REG_SP:
				return M68000_regs.a[7];
			case SEK_REG_USP:
				return GetA68KUSP();
			case SEK_REG_ISP:
				return GetA68KISP();

			case SEK_REG_CCR:
				return M68000_regs.ccr;
			default:
				return 0;
		}
	}

	if(nSekCpuCore == SEK_CORE_M68K) {
		switch (nRegister) {
			case SEK_REG_D0:
				return m68k_get_reg(NULL, M68K_REG_D0);
			case SEK_REG_D1:
				return m68k_get_reg(NULL, M68K_REG_D1);
			case SEK_REG_D2:
				return m68k_get_reg(NULL, M68K_REG_D2);
			case SEK_REG_D3:
				return m68k_get_reg(NULL, M68K_REG_D3);
			case SEK_REG_D4:
				return m68k_get_reg(NULL, M68K_REG_D4);
			case SEK_REG_D5:
				return m68k_get_reg(NULL, M68K_REG_D5);
			case SEK_REG_D6:
				return m68k_get_reg(NULL, M68K_REG_D6);
			case SEK_REG_D7:
				return m68k_get_reg(NULL, M68K_REG_D7);

			case SEK_REG_A0:
				return m68k_get_reg(NULL, M68K_REG_A0);
			case SEK_REG_A1:
				return m68k_get_reg(NULL, M68K_REG_A1);
			case SEK_REG_A2:
				return m68k_get_reg(NULL, M68K_REG_A2);
			case SEK_REG_A3:
				return m68k_get_reg(NULL, M68K_REG_A3);
			case SEK_REG_A4:
				return m68k_get_reg(NULL, M68K_REG_A4);
			case SEK_REG_A5:
				return m68k_get_reg(NULL, M68K_REG_A5);
			case SEK_REG_A6:
				return m68k_get_reg(NULL, M68K_REG_A6);
			case SEK_REG_A7:
				return m68k_get_reg(NULL, M68K_REG_A7);

			case SEK_REG_PC:
				return m68k_get_reg(NULL, M68K_REG_PC);

			case SEK_REG_SR:
				return m68k_get_reg(NULL, M68K_REG_SR);

			case SEK_REG_SP:
				return m68k_get_reg(NULL, M68K_REG_SP);
			case SEK_REG_USP:
				return m68k_get_reg(NULL, M68K_REG_USP);
			case SEK_REG_ISP:
				return m68k_get_reg(NULL, M68K_REG_ISP);
			case SEK_REG_MSP:
				return m68k_get_reg(NULL, M68K_REG_MSP);

			case SEK_REG_VBR:
				return m68k_get_reg(NULL, M68K_REG_VBR);

			case SEK_REG_SFC:
				return m68k_get_reg(NULL, M68K_REG_SFC);
			case SEK_REG_DFC:
				return m68k_get_reg(NULL, M68K_REG_DFC);

			case SEK_REG_CACR:
				return m68k_get_reg(NULL, M68K_REG_CACR);
			case SEK_REG_CAAR:
				return m68k_get_reg(NULL, M68K_REG_CAAR);

			default:
				return 0;
		}
	}

	if(nSekCpuCore == SEK_CORE_C68K) {
		switch (nRegister) {
			case SEK_REG_D0:
				return SekC68KCurrentContext->D[0];
			case SEK_REG_D1:
				return SekC68KCurrentContext->D[1];
			case SEK_REG_D2:
				return SekC68KCurrentContext->D[2];
			case SEK_REG_D3:
				return SekC68KCurrentContext->D[3];
			case SEK_REG_D4:
				return SekC68KCurrentContext->D[4];
			case SEK_REG_D5:
				return SekC68KCurrentContext->D[5];
			case SEK_REG_D6:
				return SekC68KCurrentContext->D[6];
			case SEK_REG_D7:
				return SekC68KCurrentContext->D[7];

			case SEK_REG_A0:
				return SekC68KCurrentContext->A[0];
			case SEK_REG_A1:
				return SekC68KCurrentContext->A[1];
			case SEK_REG_A2:
				return SekC68KCurrentContext->A[2];
			case SEK_REG_A3:
				return SekC68KCurrentContext->A[3];
			case SEK_REG_A4:
				return SekC68KCurrentContext->A[4];
			case SEK_REG_A5:
				return SekC68KCurrentContext->A[5];
			case SEK_REG_A6:
				return SekC68KCurrentContext->A[6];
			case SEK_REG_A7:
				return SekC68KCurrentContext->A[7];

			case SEK_REG_PC:
				return SekC68KCurrentContext->PC - SekC68KCurrentContext->BasePC;

			case SEK_REG_SR:
				return 0;

			case SEK_REG_SP:
				return SekC68KCurrentContext->A[7];
			case SEK_REG_USP:
				return SekC68KCurrentContext->USP;
			case SEK_REG_ISP:
				return 0;

			case SEK_REG_CCR:
				return (SekC68KCurrentContext->flag_X << 4) |
					(SekC68KCurrentContext->flag_N << 3) |
					(SekC68KCurrentContext->flag_Z << 2) |
					(SekC68KCurrentContext->flag_V << 1) |
					(SekC68KCurrentContext->flag_C << 0);

			default:
				return 0;
		}
	}
#else
	return 0;
#endif
}

bool SekDbgSetRegister(SekRegister nRegister, UINT32 nValue)
{
#if 0
	switch (nRegister) {
		case SEK_REG_D0:
		case SEK_REG_D1:
		case SEK_REG_D2:
		case SEK_REG_D3:
		case SEK_REG_D4:
		case SEK_REG_D5:
		case SEK_REG_D6:
		case SEK_REG_D7:
			break;

		case SEK_REG_A0:
		case SEK_REG_A1:
		case SEK_REG_A2:
		case SEK_REG_A3:
		case SEK_REG_A4:
		case SEK_REG_A5:
		case SEK_REG_A6:
		case SEK_REG_A7:
			break;

		case SEK_REG_PC:
			if (nSekCPUType[nSekActive] == 0) {
				M68000_regs.pc = nValue;
				A68KChangePC(M68000_regs.pc);
			} else {
				m68k_set_reg(M68K_REG_PC, nValue);
			}
			SekClose();
			return true;

		case SEK_REG_SR:
			break;

		case SEK_REG_SP:
		case SEK_REG_USP:
		case SEK_REG_ISP:
		case SEK_REG_MSP:
			break;

		case SEK_REG_VBR:
			break;

		case SEK_REG_SFC:
		case SEK_REG_DFC:
			break;

		case SEK_REG_CACR:
		case SEK_REG_CAAR:
			break;

		default:
			break;
	}
#else
	return false;
#endif
}

// ----------------------------------------------------------------------------
// Savestate support

INT32 SekScan(INT32 nAction)
{
	// Scan the 68000 states
	struct BurnArea ba;

	if ((nAction & ACB_DRIVER_DATA) == 0) {
		return 1;
	}

	memset(&ba, 0, sizeof(ba));

	nSekActive = -1;

	for (INT32 i = 0; i <= nSekCount; i++) {
		char szName[] = "MC68000 #n";
		INT32 nType = nSekCPUType[i];

		szName[9] = '0' + i;

		SCAN_VAR(nSekCPUType[i]);
		SCAN_VAR(nSekIRQPending[i]); // fix for Gradius 2 s.states -dink feb.3.2015

#if 0 //defined EMU_A68K && defined EMU_M68K
		// Switch to another core if needed
		if ((nAction & ACB_WRITE) && nType != nSekCPUType[i]) {
			if (nType != 0 && nType != 0x68000 && nSekCPUType[i] != 0 && nSekCPUType[i] != 0x68000) {
				continue;
			}

			if (nSekCPUType[i] == 0x68000) {
				SekCPUExitA68K(i);
				if (SekInitCPUM68K(i, 0x68000)) {
					return 1;
				}
			} else {
				SekCPUExitM68K(i);
				if (SekInitCPUA68K(i, 0x68000)) {
					return 1;
				}
			}
		}
#endif

#ifdef EMU_A68K
		if(nSekCpuCore == SEK_CORE_A68K) {
			if (nSekCPUType[i] == 0) {
				ba.Data = SekRegs[i];
				ba.nLen = sizeof(A68KContext);
				ba.szName = szName;

				if (nAction & ACB_READ) {
					// Blank pointers
					SekRegs[i]->IrqCallback = NULL;
					SekRegs[i]->ResetCallback = NULL;
				}

				BurnAcb(&ba);

				// Restore pc
				A68KChangePC(SekRegs[i]->pc);
				// Re-setup each cpu on read/write
				if (nAction & ACB_ACCESSMASK) {
					SekSetup(SekRegs[i]);
				}
			}
		}
#endif

#ifdef EMU_M68K
		if(nSekCpuCore == SEK_CORE_M68K) {
			if (nSekCPUType[i] != 0) {
				ba.Data = SekM68KContext[i];
				// for savestate portability: preserve our cpu's pointers, they are set up in DrvInit() and can be specific to different systems.
				// Therefore we scan the cpu context structure up until right before the pointers
				ba.nLen = m68k_context_size_no_pointers();
				ba.szName = szName;
				BurnAcb(&ba);
			}
		}
#endif

#ifdef EMU_C68K
			if(nSekCpuCore == SEK_CORE_C68K) {
				// PC must contain regular m68000 value
				SekC68KContext[i]->PC -= SekC68KContext[i]->BasePC;

				ba.Data = SekC68KContext[i];
				ba.nLen = (UINT32)&(SekC68KContext[i]->BasePC) - (UINT32)SekC68KContext[i];
				ba.szName = szName;
				BurnAcb(&ba);

				// restore pointer in PC
				SekC68KContext[i]->BasePC = (UINT32)FIND_F(SekC68KContext[i]->PC) - (SekC68KContext[i]->PC & ~SEK_PAGEM);
				SekC68KContext[i]->PC += SekC68KContext[i]->BasePC;
			}
#endif
	}
	return 0;
}

INT32 SekIdle(INT32 nCycles)
{
	nSekCyclesTotal += nCycles;

	return nCycles;
}

INT32 SekSegmentCycles()
{
#if defined(EMU_A68K) || defined(EMU_M68K)
	if(nSekCpuCore == SEK_CORE_A68K || nSekCpuCore == SEK_CORE_M68K) return nSekCyclesDone + nSekCyclesToDo - m68k_ICount;
#endif
#ifdef EMU_C68K
	if(nSekCpuCore == SEK_CORE_C68K) return nSekCyclesDone + nSekCyclesToDo - c68k_ICount;
#endif
}

INT32 SekTotalCycles()
{
#if defined(EMU_A68K) || defined(EMU_M68K)
	if(nSekCpuCore == SEK_CORE_A68K || nSekCpuCore == SEK_CORE_M68K) return nSekCyclesTotal + nSekCyclesToDo - m68k_ICount;
#endif
#ifdef EMU_C68K
	if(nSekCpuCore == SEK_CORE_C68K) return nSekCyclesTotal + nSekCyclesToDo - c68k_ICount;
#endif
}

INT32 SekCurrentScanline()
{
	return SekTotalCycles() / nSekCyclesScanline;
}


