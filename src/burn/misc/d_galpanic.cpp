/*
 * Gal Panic (set 1) driver for FB Alpha 0.2.96.71
 *
 * Port by OopsWare. 2007
 */
 
#include "burnint.h"
#include "driver.h"

#include "msm6295.h"

static unsigned char *Mem = NULL, *MemEnd = NULL;
static unsigned char *RamStart, *RamEnd;

static unsigned char *Rom68K;
static unsigned char *RomGfx;
static unsigned char *DeRomGfx;
static unsigned char *RomSnd;

static unsigned short *RamPal;
static unsigned short *RamFg;
static unsigned short *RamBg;
static unsigned short *RamSpr;

static unsigned short *RamCurPal;
static unsigned short *RamCTB64k;

static unsigned char DrvButton[5] = {0, 0, 0, 0, 0};
static unsigned char DrvJoy1[5] = {0, 0, 0, 0, 0};
static unsigned char DrvJoy2[5] = {0, 0, 0, 0, 0};
static unsigned char DrvInput[6] = {0, 0, 0, 0, 0, 0};
static unsigned char DrvReset = 0;
//static unsigned short GalPanicCoin = 0;

static unsigned char RecalcBgPalette;

static struct BurnInputInfo GalpanicInputList[] = {
	{"P1 Coin",		BIT_DIGITAL,	DrvButton + 2,	"p1 coin"},
	{"P1 Start",	BIT_DIGITAL,	DrvButton + 0,	"p1 start"},

	{"P1 Up",		BIT_DIGITAL,	DrvJoy1 + 0,	"p1 up"},
	{"P1 Down",		BIT_DIGITAL,	DrvJoy1 + 1,	"p1 down"},
	{"P1 Left",		BIT_DIGITAL,	DrvJoy1 + 2,	"p1 left"},
	{"P1 Right",	BIT_DIGITAL,	DrvJoy1 + 3,	"p1 right"},
	{"P1 Button 1",	BIT_DIGITAL,	DrvJoy1 + 4,	"p1 fire 1"},

	{"P2 Coin",		BIT_DIGITAL,	DrvButton + 3,	"p2 coin"},
	{"P2 Start",	BIT_DIGITAL,	DrvButton + 1,	"p2 start"},

	{"P2 Up",		BIT_DIGITAL,	DrvJoy2 + 0,	"p2 up"},
	{"P2 Down",		BIT_DIGITAL,	DrvJoy2 + 1,	"p2 down"},
	{"P2 Left",		BIT_DIGITAL,	DrvJoy2 + 2,	"p2 left"},
	{"P2 Right",	BIT_DIGITAL,	DrvJoy2 + 3,	"p2 right"},
	{"P2 Button 1",	BIT_DIGITAL,	DrvJoy2 + 4,	"p2 fire 1"},

	{"Reset",		BIT_DIGITAL,	&DrvReset,		"reset"},
	{"Service",		BIT_DIGITAL,	DrvButton + 6,	"service"},
	{"Tilt",		BIT_DIGITAL,	DrvButton + 5,	"tilt"},
	{"Dip A",		BIT_DIPSWITCH,	DrvInput + 0,	"dip"},
	{"Dip B",		BIT_DIPSWITCH,	DrvInput + 2,	"dip"},
};

STDINPUTINFO(Galpanic);

static struct BurnDIPInfo GalpanicDIPList[] = {

	// Defaults
	{0x11,	0xFF, 0xFF,	0x00, NULL},
	{0x12,	0xFF, 0xFF,	0x00, NULL},

	// DIP 1
	{0,		0xFE, 0,	2,	  "Service Mode"},
	{0x11,	0x01, 0x04, 0x00, "Off"}, 
	{0x11,	0x01, 0x04, 0x04, "On"},
	{0,		0xFE, 0,	4,	  "Coin 1"},
	{0x11,	0x01, 0x30, 0x00, "1 coin 1 credit"},
	{0x11,	0x01, 0x30, 0x10, "2 coin 1 credit"},
	{0x11,	0x01, 0x30, 0x20, "3 coin 1 credit"},
	{0x11,	0x01, 0x30, 0x30, "4 coin 1 credit"},
	{0,		0xFE, 0,	4,	  "Coin 2"},
	{0x11,	0x01, 0xC0, 0x00, "1 coin 2 credits"},
	{0x11,	0x01, 0xC0, 0x40, "1 coin 3 credits"},
	{0x11,	0x01, 0xC0, 0x80, "1 coin 4 credits"},
	{0x11,	0x01, 0xC0, 0xC0, "1 coin 6 credits"},

	// DIP 2
	{0,		0xFE, 0,	4,	  "Difficulty"},
	{0x12,	0x01, 0x03, 0x00, "Normal"},
	{0x12,	0x01, 0x03, 0x01, "Easy"},
	{0x12,	0x01, 0x03, 0x02, "Hard"},
	{0x12,	0x01, 0x03, 0x03, "Hardest"},
	{0,		0xFE, 0,	4,	  "Lives"},		
	{0x12,	0x01, 0x30, 0x00, "3"},
	{0x12,	0x01, 0x30, 0x10, "4"},
	{0x12,	0x01, 0x30, 0x20, "2"},
	{0x12,	0x01, 0x30, 0x30, "5"},
//	{0,		0xFE, 0,	2,	  "Unknown"},		// demo sounds?
//	{0x12,	0x01, 0x40, 0x00, "Off"},
//	{0x12,	0x01, 0x40, 0x40, "On"},
	{0,		0xFE, 0,	2,	  "Character Test"},
	{0x12,	0x01, 0x80, 0x00, "Off"}, 
	{0x12,	0x01, 0x80, 0x80, "On"},
	
};

STDDIPINFO(Galpanic);

// Rom information
static struct BurnRomInfo GalpanicRomDesc[] = {
	{ "pm110.4m2",    0x080000, 0xae6b17a8, BRF_ESS | BRF_PRG }, // 68000 code 
	{ "pm109.4m1",    0x080000, 0xb85d792d, BRF_ESS | BRF_PRG }, 
	{ "pm112.subic6", 0x020000, 0x7b972b58, BRF_ESS | BRF_PRG }, 
	{ "pm111.subic5", 0x020000, 0x4eb7298d, BRF_ESS | BRF_PRG }, 
	{ "pm004e.8",  	  0x080000, 0xd3af52bc, BRF_ESS | BRF_PRG }, 
	{ "pm005e.7",	  0x080000, 0xd7ec650c, BRF_ESS | BRF_PRG }, 
	{ "pm000e.15", 	  0x080000, 0x5d220f3f, BRF_ESS | BRF_PRG }, 
	{ "pm001e.14",	  0x080000, 0x90433eb1, BRF_ESS | BRF_PRG }, 
	{ "pm002e.17", 	  0x080000, 0x713ee898, BRF_ESS | BRF_PRG }, 
	{ "pm003e.16",	  0x080000, 0x6bb060fd, BRF_ESS | BRF_PRG }, 
	

	{ "pm006e.67",    0x100000, 0x57aec037, BRF_GRA },			  // graphics
	
	{ "pm008e.l",     0x080000, 0xd9379ba8, BRF_SND },			  // PCM
	{ "pm007e.u",     0x080000, 0xc7ed7950, BRF_SND },			  
	
};

STD_ROM_PICK(Galpanic);
STD_ROM_FN(Galpanic);

static int MemIndex()
{
	unsigned char *Next; Next = Mem;
	Rom68K 		= Next; Next += 0x400000;			// 68000 ROM
	RomGfx		= Next; Next += 0x200100;			// Graphics, 1M 16x16x4bit decode to 2M + 64byte safe
	DeRomGfx	= RomGfx     +  0x000100;
	RomSnd		= Next; Next += 0x140000;			// ADPCM - OKI6295
	
	RamStart	= Next;
	
	RamFg		= (unsigned short *) Next; Next += 0x020000;
	RamBg		= (unsigned short *) Next; Next += 0x020000;
	RamPal		= (unsigned short *) Next; Next += 0x000800;
	RamSpr		= (unsigned short *) Next; Next += 0x004800;
	
	RamEnd		= Next;
	
	RamCurPal	= (unsigned short *) Next; Next += 0x000800;
	RamCTB64k	= (unsigned short *) Next; Next += 0x020000;
	
	MemEnd		= Next;
	return 0;
}

static inline unsigned char pal5bit(unsigned char bits)
{
	bits &= 0x1f;
	return (bits << 3) | (bits >> 2);
}

unsigned char __fastcall GalpanicReadByte(unsigned int sekAddress)
{
	switch (sekAddress) {
		case 0x400001:
			return MSM6295ReadStatus(0);
		//default:
		//	printf("Attempt to read byte value of location %x\n", sekAddress);
	}
	return 0;
}

unsigned short __fastcall GalpanicReadWord(unsigned int sekAddress)
{
	switch (sekAddress) {
		case 0x800000:
			return ~(DrvInput[0] | (DrvInput[1] << 8));
		case 0x800002:
			return ~(DrvInput[2] | (DrvInput[3] << 8));
		case 0x800004:
			return ~(DrvInput[4] | (DrvInput[5] << 8));
		//default:
		//	printf("Attempt to read word value of location %x\n", sekAddress);
	}
	return 0;
}

void __fastcall GalpanicWriteByte(unsigned int sekAddress, unsigned char byteValue)
{
	switch (sekAddress) {
		case 0x900000:
			memcpy(&RomSnd[0x30000], &RomSnd[0x40000 + (byteValue & 0x0f) * 0x10000], 0x10000);
			break;
		case 0x400001:
			MSM6295Command(0, byteValue);
			break;
		//case 0xB00000:
		//case 0xC00000:
		//case 0xD00000:
		//	/* NOP */
		//	break;
		//default:
		//	printf("Attempt to write byte value %x to location %x\n", byteValue, sekAddress);
	}
}

void __fastcall GalpanicWriteWord(unsigned int sekAddress, unsigned short wordValue)
{
	switch (sekAddress) {
		case 0xA00000:
//			GalPanicCoin = wordValue;
			break;
		//default:
		//	printf("Attempt to write word value %x to location %x\n", wordValue, sekAddress);
	}
}

static int DrvDoReset()
{
	SekOpen(0);
    SekSetIRQLine(0, SEK_IRQSTATUS_NONE);
	SekReset();
	SekClose();
	MSM6295Reset(0);
	
	return 0;
}

void DeCodeGfx()
{
	for (int c=8192-1; c>=0; c--) {
		int fx = 8;
		for (int y=15; y>=0; y--) {
			if (y == 7) fx = 0;
			DeRomGfx[(c * 256) + (y * 16) + 15] = RomGfx[0x00023 + ((y + fx) * 4) + (c * 128)] & 0x0f;
			DeRomGfx[(c * 256) + (y * 16) + 14] = RomGfx[0x00023 + ((y + fx) * 4) + (c * 128)] >> 4;
			DeRomGfx[(c * 256) + (y * 16) + 13] = RomGfx[0x00022 + ((y + fx) * 4) + (c * 128)] & 0x0f;
			DeRomGfx[(c * 256) + (y * 16) + 12] = RomGfx[0x00022 + ((y + fx) * 4) + (c * 128)] >> 4;
			DeRomGfx[(c * 256) + (y * 16) + 11] = RomGfx[0x00021 + ((y + fx) * 4) + (c * 128)] & 0x0f;
			DeRomGfx[(c * 256) + (y * 16) + 10] = RomGfx[0x00021 + ((y + fx) * 4) + (c * 128)] >> 4;
			DeRomGfx[(c * 256) + (y * 16) +  9] = RomGfx[0x00020 + ((y + fx) * 4) + (c * 128)] & 0x0f;
			DeRomGfx[(c * 256) + (y * 16) +  8] = RomGfx[0x00020 + ((y + fx) * 4) + (c * 128)] >> 4;

			DeRomGfx[(c * 256) + (y * 16) +  7] = RomGfx[0x00003 + ((y + fx) * 4) + (c * 128)] & 0x0f;
			DeRomGfx[(c * 256) + (y * 16) +  6] = RomGfx[0x00003 + ((y + fx) * 4) + (c * 128)] >> 4;
			DeRomGfx[(c * 256) + (y * 16) +  5] = RomGfx[0x00002 + ((y + fx) * 4) + (c * 128)] & 0x0f;
			DeRomGfx[(c * 256) + (y * 16) +  4] = RomGfx[0x00002 + ((y + fx) * 4) + (c * 128)] >> 4;
			DeRomGfx[(c * 256) + (y * 16) +  3] = RomGfx[0x00001 + ((y + fx) * 4) + (c * 128)] & 0x0f;
			DeRomGfx[(c * 256) + (y * 16) +  2] = RomGfx[0x00001 + ((y + fx) * 4) + (c * 128)] >> 4;
			DeRomGfx[(c * 256) + (y * 16) +  1] = RomGfx[0x00000 + ((y + fx) * 4) + (c * 128)] & 0x0f;
			DeRomGfx[(c * 256) + (y * 16) +  0] = RomGfx[0x00000 + ((y + fx) * 4) + (c * 128)] >> 4;
		}
	}
}

static int GalpanicInit()
{
	int nRet;
	
	Mem = NULL;
	MemIndex();
	int nLen = MemEnd - (unsigned char *)0;
	if ((Mem = (unsigned char *)malloc(nLen)) == NULL) {
		return 1;
	}
	memset(Mem, 0, nLen);										// blank all memory
	MemIndex();	
	
	// Load and byte-swap 68000 Program roms
	nRet = BurnLoadRom(Rom68K + 0x000001, 0, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(Rom68K + 0x000000, 1, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(Rom68K + 0x000001, 2, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(Rom68K + 0x000000, 3, 2); if (nRet != 0) return 1;
	
	nRet = BurnLoadRom(Rom68K + 0x100000, 4, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(Rom68K + 0x100001, 5, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(Rom68K + 0x200000, 6, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(Rom68K + 0x200001, 7, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(Rom68K + 0x300000, 8, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(Rom68K + 0x300001, 9, 2); if (nRet != 0) return 1;
	
	nRet = BurnLoadRom(RomGfx + 0x000000, 10, 1); if (nRet != 0) return 1;
	DeCodeGfx();
	
	BurnLoadRom(RomSnd + 0x040000, 11, 1);
	BurnLoadRom(RomSnd + 0x0C0000, 12, 1);
	memcpy(RomSnd, RomSnd + 0x040000, 0x040000);
	
	{
		SekInit(0, 0x68000);										// Allocate 68000
	    SekOpen(0);

		// Map 68000 memory:
		SekMapMemory(Rom68K,		0x000000, 0x3FFFFF, SM_ROM);	// CPU 0 ROM
		SekMapMemory((unsigned char *)RamFg,
									0x500000, 0x51FFFF, SM_RAM);	// f ground
		SekMapMemory((unsigned char *)RamBg,
									0x520000, 0x53FFFF, SM_RAM);	// b ground
		SekMapMemory((unsigned char *)RamPal,
									0x600000, 0x6007FF, SM_RAM);	// palette
		SekMapMemory((unsigned char *)RamSpr,
									0x700000, 0x7047FF, SM_RAM);	// sprites
		
		SekSetReadWordHandler(0, GalpanicReadWord);
		SekSetReadByteHandler(0, GalpanicReadByte);
		SekSetWriteWordHandler(0, GalpanicWriteWord);
		SekSetWriteByteHandler(0, GalpanicWriteByte);

		SekClose();
	}
	
	MSM6295ROM = RomSnd;
	MSM6295Init(0, 12000, 80, 0);
	
	RecalcBgPalette = 1;
	
	DrvDoReset();	
	return 0;
}

static int GalpanicExit()
{
	SekExit();
	MSM6295Exit(0);
	
	free(Mem);
	Mem = NULL;
	
	RecalcBgPalette = 0;
	return 0;
}

static void drawgfx(unsigned int code,unsigned int color,int flipx,int flipy,int sx,int sy)
{
	unsigned short * p = (unsigned short *) pBurnDraw;
	unsigned char * q = DeRomGfx + (code) * 256;
	unsigned short * pal = RamCurPal + 256;
			
	p += sy * 256 + sx;

	if ((sx < 0) || (sx >= 240) || (sy < 0) || (sy >= 208)) {
		
		if ((sx <= -16) || (sx >= 256) || (sy <= -16) || (sy >= 224))
			return ;
		
		// clip 
		if (!flipy) {
			p += 256 * 15;
		
			if (!flipx) {
				
				for (int i=15;i>=0;i--) {
					if (((sy+i)>=0) && ((sy+i)<224)) {
						if (q[ 0] && ((sx + 15) >= 0) && ((sx + 15)<256)) p[15] = pal[ q[ 0] | color];
						if (q[ 1] && ((sx + 14) >= 0) && ((sx + 14)<256)) p[14] = pal[ q[ 1] | color];
						if (q[ 2] && ((sx + 13) >= 0) && ((sx + 13)<256)) p[13] = pal[ q[ 2] | color];
						if (q[ 3] && ((sx + 12) >= 0) && ((sx + 12)<256)) p[12] = pal[ q[ 3] | color];
						if (q[ 4] && ((sx + 11) >= 0) && ((sx + 11)<256)) p[11] = pal[ q[ 4] | color];
						if (q[ 5] && ((sx + 10) >= 0) && ((sx + 10)<256)) p[10] = pal[ q[ 5] | color];
						if (q[ 6] && ((sx +  9) >= 0) && ((sx +  9)<256)) p[ 9] = pal[ q[ 6] | color];
						if (q[ 7] && ((sx +  8) >= 0) && ((sx +  8)<256)) p[ 8] = pal[ q[ 7] | color];
						
						if (q[ 8] && ((sx +  7) >= 0) && ((sx +  7)<256)) p[ 7] = pal[ q[ 8] | color];
						if (q[ 9] && ((sx +  6) >= 0) && ((sx +  6)<256)) p[ 6] = pal[ q[ 9] | color];
						if (q[10] && ((sx +  5) >= 0) && ((sx +  5)<256)) p[ 5] = pal[ q[10] | color];
						if (q[11] && ((sx +  4) >= 0) && ((sx +  4)<256)) p[ 4] = pal[ q[11] | color];
						if (q[12] && ((sx +  3) >= 0) && ((sx +  3)<256)) p[ 3] = pal[ q[12] | color];
						if (q[13] && ((sx +  2) >= 0) && ((sx +  2)<256)) p[ 2] = pal[ q[13] | color];
						if (q[14] && ((sx +  1) >= 0) && ((sx +  1)<256)) p[ 1] = pal[ q[14] | color];
						if (q[15] && ((sx +  0) >= 0) && ((sx +  0)<256)) p[ 0] = pal[ q[15] | color];
					}
					p -= 256;
					q += 16;
				}

			} else {
				
				for (int i=15;i>=0;i--) {
					if (((sy+i)>=0) && ((sy+i)<224)) {
						if (q[ 0] && ((sx +  0) >= 0) && ((sx +  0)<256)) p[ 0] = pal[ q[ 0] | color];
						if (q[ 1] && ((sx +  1) >= 0) && ((sx +  1)<256)) p[ 1] = pal[ q[ 1] | color];
						if (q[ 2] && ((sx +  2) >= 0) && ((sx +  2)<256)) p[ 2] = pal[ q[ 2] | color];
						if (q[ 3] && ((sx +  3) >= 0) && ((sx +  3)<256)) p[ 3] = pal[ q[ 3] | color];
						if (q[ 4] && ((sx +  4) >= 0) && ((sx +  4)<256)) p[ 4] = pal[ q[ 4] | color];
						if (q[ 5] && ((sx +  5) >= 0) && ((sx +  5)<256)) p[ 5] = pal[ q[ 5] | color];
						if (q[ 6] && ((sx +  6) >= 0) && ((sx +  6)<256)) p[ 6] = pal[ q[ 6] | color];
						if (q[ 7] && ((sx +  7) >= 0) && ((sx +  7)<256)) p[ 7] = pal[ q[ 7] | color];
						
						if (q[ 8] && ((sx +  8) >= 0) && ((sx +  8)<256)) p[ 8] = pal[ q[ 8] | color];
						if (q[ 9] && ((sx +  9) >= 0) && ((sx +  9)<256)) p[ 9] = pal[ q[ 9] | color];
						if (q[10] && ((sx + 10) >= 0) && ((sx + 10)<256)) p[10] = pal[ q[10] | color];
						if (q[11] && ((sx + 11) >= 0) && ((sx + 11)<256)) p[11] = pal[ q[11] | color];
						if (q[12] && ((sx + 12) >= 0) && ((sx + 12)<256)) p[12] = pal[ q[12] | color];
						if (q[13] && ((sx + 13) >= 0) && ((sx + 13)<256)) p[13] = pal[ q[13] | color];
						if (q[14] && ((sx + 14) >= 0) && ((sx + 14)<256)) p[14] = pal[ q[14] | color];
						if (q[15] && ((sx + 15) >= 0) && ((sx + 15)<256)) p[15] = pal[ q[15] | color];
					}
					p -= 256;
					q += 16;
				}
			}
			
		} else {
				
			if (!flipx) {
				
				for (int i=0;i<16;i++) {
					if (((sy+i)>=0) && ((sy+i)<224)) {
						if (q[ 0] && ((sx + 15) >= 0) && ((sx + 15)<256)) p[15] = pal[ q[ 0] | color];
						if (q[ 1] && ((sx + 14) >= 0) && ((sx + 14)<256)) p[14] = pal[ q[ 1] | color];
						if (q[ 2] && ((sx + 13) >= 0) && ((sx + 13)<256)) p[13] = pal[ q[ 2] | color];
						if (q[ 3] && ((sx + 12) >= 0) && ((sx + 12)<256)) p[12] = pal[ q[ 3] | color];
						if (q[ 4] && ((sx + 11) >= 0) && ((sx + 11)<256)) p[11] = pal[ q[ 4] | color];
						if (q[ 5] && ((sx + 10) >= 0) && ((sx + 10)<256)) p[10] = pal[ q[ 5] | color];
						if (q[ 6] && ((sx +  9) >= 0) && ((sx +  9)<256)) p[ 9] = pal[ q[ 6] | color];
						if (q[ 7] && ((sx +  8) >= 0) && ((sx +  8)<256)) p[ 8] = pal[ q[ 7] | color];
						
						if (q[ 8] && ((sx +  7) >= 0) && ((sx +  7)<256)) p[ 7] = pal[ q[ 8] | color];
						if (q[ 9] && ((sx +  6) >= 0) && ((sx +  6)<256)) p[ 6] = pal[ q[ 9] | color];
						if (q[10] && ((sx +  5) >= 0) && ((sx +  5)<256)) p[ 5] = pal[ q[10] | color];
						if (q[11] && ((sx +  4) >= 0) && ((sx +  4)<256)) p[ 4] = pal[ q[11] | color];
						if (q[12] && ((sx +  3) >= 0) && ((sx +  3)<256)) p[ 3] = pal[ q[12] | color];
						if (q[13] && ((sx +  2) >= 0) && ((sx +  2)<256)) p[ 2] = pal[ q[13] | color];
						if (q[14] && ((sx +  1) >= 0) && ((sx +  1)<256)) p[ 1] = pal[ q[14] | color];
						if (q[15] && ((sx +  0) >= 0) && ((sx +  0)<256)) p[ 0] = pal[ q[15] | color];
					}
					p += 256;
					q += 16;
				}

			} else {
				
				for (int i=0;i<16;i++) {
					if (((sy+i)>=0) && ((sy+i)<224)) {
						if (q[ 0] && ((sx +  0) >= 0) && ((sx +  0)<256)) p[ 0] = pal[ q[ 0] | color];
						if (q[ 1] && ((sx +  1) >= 0) && ((sx +  1)<256)) p[ 1] = pal[ q[ 1] | color];
						if (q[ 2] && ((sx +  2) >= 0) && ((sx +  2)<256)) p[ 2] = pal[ q[ 2] | color];
						if (q[ 3] && ((sx +  3) >= 0) && ((sx +  3)<256)) p[ 3] = pal[ q[ 3] | color];
						if (q[ 4] && ((sx +  4) >= 0) && ((sx +  4)<256)) p[ 4] = pal[ q[ 4] | color];
						if (q[ 5] && ((sx +  5) >= 0) && ((sx +  5)<256)) p[ 5] = pal[ q[ 5] | color];
						if (q[ 6] && ((sx +  6) >= 0) && ((sx +  6)<256)) p[ 6] = pal[ q[ 6] | color];
						if (q[ 7] && ((sx +  7) >= 0) && ((sx +  7)<256)) p[ 7] = pal[ q[ 7] | color];
						
						if (q[ 8] && ((sx +  8) >= 0) && ((sx +  8)<256)) p[ 8] = pal[ q[ 8] | color];
						if (q[ 9] && ((sx +  9) >= 0) && ((sx +  9)<256)) p[ 9] = pal[ q[ 9] | color];
						if (q[10] && ((sx + 10) >= 0) && ((sx + 10)<256)) p[10] = pal[ q[10] | color];
						if (q[11] && ((sx + 11) >= 0) && ((sx + 11)<256)) p[11] = pal[ q[11] | color];
						if (q[12] && ((sx + 12) >= 0) && ((sx + 12)<256)) p[12] = pal[ q[12] | color];
						if (q[13] && ((sx + 13) >= 0) && ((sx + 13)<256)) p[13] = pal[ q[13] | color];
						if (q[14] && ((sx + 14) >= 0) && ((sx + 14)<256)) p[14] = pal[ q[14] | color];
						if (q[15] && ((sx + 15) >= 0) && ((sx + 15)<256)) p[15] = pal[ q[15] | color];
					}
					p += 256;
					q += 16;
				}
			}	
		}

		return;
	}

	if (!flipy) {
		
		p += 256 * 15;
		
		if (!flipx) {
		
			for (int i=0;i<16;i++) {
				if (q[ 0]) p[15] = pal[ q[ 0] | color];
				if (q[ 1]) p[14] = pal[ q[ 1] | color];
				if (q[ 2]) p[13] = pal[ q[ 2] | color];
				if (q[ 3]) p[12] = pal[ q[ 3] | color];
				if (q[ 4]) p[11] = pal[ q[ 4] | color];
				if (q[ 5]) p[10] = pal[ q[ 5] | color];
				if (q[ 6]) p[ 9] = pal[ q[ 6] | color];
				if (q[ 7]) p[ 8] = pal[ q[ 7] | color];
				
				if (q[ 8]) p[ 7] = pal[ q[ 8] | color];
				if (q[ 9]) p[ 6] = pal[ q[ 9] | color];
				if (q[10]) p[ 5] = pal[ q[10] | color];
				if (q[11]) p[ 4] = pal[ q[11] | color];
				if (q[12]) p[ 3] = pal[ q[12] | color];
				if (q[13]) p[ 2] = pal[ q[13] | color];
				if (q[14]) p[ 1] = pal[ q[14] | color];
				if (q[15]) p[ 0] = pal[ q[15] | color];
	
				p -= 256;
				q += 16;
			}	
		
		} else {

			for (int i=0;i<16;i++) {
				if (q[ 0]) p[ 0] = pal[ q[ 0] | color];
				if (q[ 1]) p[ 1] = pal[ q[ 1] | color];
				if (q[ 2]) p[ 2] = pal[ q[ 2] | color];
				if (q[ 3]) p[ 3] = pal[ q[ 3] | color];
				if (q[ 4]) p[ 4] = pal[ q[ 4] | color];
				if (q[ 5]) p[ 5] = pal[ q[ 5] | color];
				if (q[ 6]) p[ 6] = pal[ q[ 6] | color];
				if (q[ 7]) p[ 7] = pal[ q[ 7] | color];
				
				if (q[ 8]) p[ 8] = pal[ q[ 8] | color];
				if (q[ 9]) p[ 9] = pal[ q[ 9] | color];
				if (q[10]) p[10] = pal[ q[10] | color];
				if (q[11]) p[11] = pal[ q[11] | color];
				if (q[12]) p[12] = pal[ q[12] | color];
				if (q[13]) p[13] = pal[ q[13] | color];
				if (q[14]) p[14] = pal[ q[14] | color];
				if (q[15]) p[15] = pal[ q[15] | color];
	
				p -= 256;
				q += 16;
			}		
		}
		
	} else {
		
		if (!flipx) {
		
			for (int i=0;i<16;i++) {
				if (q[ 0]) p[15] = pal[ q[ 0] | color];
				if (q[ 1]) p[14] = pal[ q[ 1] | color];
				if (q[ 2]) p[13] = pal[ q[ 2] | color];
				if (q[ 3]) p[12] = pal[ q[ 3] | color];
				if (q[ 4]) p[11] = pal[ q[ 4] | color];
				if (q[ 5]) p[10] = pal[ q[ 5] | color];
				if (q[ 6]) p[ 9] = pal[ q[ 6] | color];
				if (q[ 7]) p[ 8] = pal[ q[ 7] | color];
				
				if (q[ 8]) p[ 7] = pal[ q[ 8] | color];
				if (q[ 9]) p[ 6] = pal[ q[ 9] | color];
				if (q[10]) p[ 5] = pal[ q[10] | color];
				if (q[11]) p[ 4] = pal[ q[11] | color];
				if (q[12]) p[ 3] = pal[ q[12] | color];
				if (q[13]) p[ 2] = pal[ q[13] | color];
				if (q[14]) p[ 1] = pal[ q[14] | color];
				if (q[15]) p[ 0] = pal[ q[15] | color];
	
				p += 256;
				q += 16;
			}		
		
		} else {

			for (int i=0;i<16;i++) {
				if (q[ 0]) p[ 0] = pal[ q[ 0] | color];
				if (q[ 1]) p[ 1] = pal[ q[ 1] | color];
				if (q[ 2]) p[ 2] = pal[ q[ 2] | color];
				if (q[ 3]) p[ 3] = pal[ q[ 3] | color];
				if (q[ 4]) p[ 4] = pal[ q[ 4] | color];
				if (q[ 5]) p[ 5] = pal[ q[ 5] | color];
				if (q[ 6]) p[ 6] = pal[ q[ 6] | color];
				if (q[ 7]) p[ 7] = pal[ q[ 7] | color];
				
				if (q[ 8]) p[ 8] = pal[ q[ 8] | color];
				if (q[ 9]) p[ 9] = pal[ q[ 9] | color];
				if (q[10]) p[10] = pal[ q[10] | color];
				if (q[11]) p[11] = pal[ q[11] | color];
				if (q[12]) p[12] = pal[ q[12] | color];
				if (q[13]) p[13] = pal[ q[13] | color];
				if (q[14]) p[14] = pal[ q[14] | color];
				if (q[15]) p[15] = pal[ q[15] | color];
	
				p += 256;
				q += 16;
			}	

		}
		
	}
	
}



static void DrvDraw()
{
 	if (RecalcBgPalette) {
	 	for (int i = 0; i < 32768; i++) {
			int r = pal5bit(i >> 5);
			int g = pal5bit(i >> 10);
			int b = pal5bit(i >> 0);
			RamCTB64k[i] = BurnHighCol(r, g, b, 0);
		}
		
		RecalcBgPalette = 0;
	}
	
 	for (int i = 0; i < 1024; i++) {
 		unsigned short nColour = RamPal[i];
 		int r = pal5bit(nColour >> 6);
 		int g = pal5bit(nColour >> 11);
 		int b = pal5bit(nColour >> 1);
 		RamCurPal[i] = BurnHighCol(r, g, b, 0);
 	} 	
 		
 	unsigned short * d = (unsigned short *)pBurnDraw + ( 224 * 256 ) - 1;
 	unsigned short * s = (unsigned short *)RamBg;
 	unsigned short * f = (unsigned short *)RamFg;
	for (int j=0;j<224;j++) {
		for (int i=0;i<256;i++) {
			if (*f)	*d = RamCurPal[*f];
			else 	*d = RamCTB64k[*s >> 1];
			d--;
			s++;
			f++;
		}
	}
	
	int sx, sy;
	sx = sy = 0;
	for (int offs=0; offs<0x002400; offs+=0x08) {
		int x,y,code,color,flipx,flipy,attr1,attr2;
		
		attr1 = RamSpr[offs + 3];
		x = RamSpr[offs + 4] - ((attr1 & 0x01) << 8);
		y = RamSpr[offs + 5] + ((attr1 & 0x02) << 7);
		if (attr1 & 0x04)	/* multi sprite */
		{
			sx += x;
			sy += y;
		}
		else
		{
			sx = x;
			sy = y;
		}
		
		color = (attr1 & 0xf0);

		/* bit 0 [offs + 0] is used but I don't know what for */

		attr2 = RamSpr[offs + 7];
		code = RamSpr[offs + 6] + ((attr2 & 0x1f) << 8);
		flipx = attr2 & 0x80;
		flipy = attr2 & 0x40;
		
		drawgfx(code, color, flipx, flipy, 256-sx-16, 224-(sy - 16)-16);
		//drawgfx(code, color, flipx, flipy, sx, (sy - 16));
	}

}

static int GalpanicFrame()
{
	if (DrvReset)														// Reset machine
		DrvDoReset();
	
	DrvInput[1] = 0x00;													// Joy1
	DrvInput[3] = 0x00;													// Joy2
	DrvInput[5] = 0x00;													// Buttons
	for (int i = 0; i < 5; i++) {
		DrvInput[1] |= (DrvJoy1[i] & 1) << i;
		DrvInput[3] |= (DrvJoy2[i] & 1) << i;
		DrvInput[5] |= (DrvButton[i] & 1) << i;
	}
		
	//nCyclesTotal = 8000000 / 60;
	//nCyclesDone = 0;
	//SekSetCyclesScanline(nCyclesTotal / 262);

	SekNewFrame();

	SekOpen(0);
	
	SekSetIRQLine(3, SEK_IRQSTATUS_AUTO);						// let game run ???
	SekRun(8000000 / 60);
	SekSetIRQLine(5, SEK_IRQSTATUS_AUTO);						// update palette
	SekRun(1000);
	
	SekClose();
	
	if (pBurnDraw)
		DrvDraw();												// Draw screen if needed
	if (pBurnSoundOut) 
		MSM6295Render(0, pBurnSoundOut, nBurnSoundLen);

	return 0;
}

static int GalpanicScan(int nAction,int *pnMin)
{
struct BurnArea ba;

	if (pnMin != NULL) {			// Return minimum compatible version
		*pnMin = 0x029671;
	}

	if (nAction & ACB_MEMORY_RAM) {		// Scan volatile ram
		memset(&ba, 0, sizeof(ba));
    	ba.Data	  = RamStart;
		ba.nLen	  = RamEnd-RamStart;
		ba.szName = "All Ram";
		BurnAcb(&ba);
		
	}
	
	if (nAction & ACB_DRIVER_DATA) {
		SekScan(nAction & 3);			// Scan 68000
		MSM6295Scan(0, nAction);		// Scan OKIM6295
		// Scan critical driver variables
		SCAN_VAR(DrvInput);
	}
	
	return 0;
}

struct BurnDriver BurnDrvGalpanic = {
	"galpanic", NULL, NULL, "1990",
	"Gals Panic (set 1)\0", NULL, "Kaneko", NULL,
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_ORIENTATION_VERTICAL | BDF_16BIT_ONLY, 2, HARDWARE_MISC_MISC,
	NULL, GalpanicRomInfo, GalpanicRomName, GalpanicInputInfo, GalpanicDIPInfo,
	GalpanicInit, GalpanicExit, GalpanicFrame, NULL, GalpanicScan,
	&RecalcBgPalette, 224, 256, 3, 4
};
