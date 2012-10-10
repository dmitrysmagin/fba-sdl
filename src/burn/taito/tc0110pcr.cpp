// TC0110PCR

#include "burnint.h"

static unsigned char *TC0110PCRRam = NULL;
static int TC0110PCRRamSize;
unsigned int *TC0110PCRPalette = NULL;
static int TC0110PCRAddr;
int TC0110PCRTotalColours;

static inline unsigned char pal5bit(unsigned char bits)
{
	bits &= 0x1f;
	return (bits << 3) | (bits >> 2);
}

UINT16 TC0110PCRWordRead()
{
	UINT16 *PalRam = (UINT16*)TC0110PCRRam;
	return PalRam[TC0110PCRAddr];
}

void TC0110PCRStep1WordWrite(int Offset, UINT16 Data)
{
	switch (Offset) {
		case 0: {
			TC0110PCRAddr = Data & 0xfff;
			return;
		}
		
		case 1: {
			UINT16 *PalRam = (UINT16*)TC0110PCRRam;
			int r, g, b;
			
			PalRam[TC0110PCRAddr] = Data;
			
			r = pal5bit(Data >>  0);
			g = pal5bit(Data >>  5);
			b = pal5bit(Data >> 10);
			
			TC0110PCRPalette[TC0110PCRAddr] = BurnHighCol(r, g, b, 0);
			return;
		}
	}
}

void TC0110PCRStep1RBSwapWordWrite(int Offset, UINT16 Data)
{
	switch (Offset) {
		case 0: {
			TC0110PCRAddr = Data & 0xfff;
			return;
		}
		
		case 1: {
			UINT16 *PalRam = (UINT16*)TC0110PCRRam;
			int r, g, b;
			
			PalRam[TC0110PCRAddr] = Data;
			
			r = pal5bit(Data >> 10);
			g = pal5bit(Data >>  5);
			b = pal5bit(Data >>  0);
			
			TC0110PCRPalette[TC0110PCRAddr] = BurnHighCol(r, g, b, 0);
			return;
		}
	}
}

void TC0110PCRReset()
{
	TC0110PCRAddr = 0;
}

void TC0110PCRInit(int nRamSize, int nNumColours)
{
	TC0110PCRRam = (unsigned char*)malloc(nRamSize);
	memset(TC0110PCRRam, 0, nRamSize);
	TC0110PCRPalette = (unsigned int*)malloc(nNumColours * sizeof(unsigned int));
	memset(TC0110PCRPalette, 0, nNumColours);
	
	TC0110PCRTotalColours = nNumColours;
	TC0110PCRRamSize = nRamSize;
}

void TC0110PCRExit()
{
	free(TC0110PCRRam);
	TC0110PCRRam = NULL;
	
	free(TC0110PCRPalette);
	TC0110PCRPalette = NULL;
	
	TC0110PCRAddr = 0;
	
	TC0110PCRTotalColours = 0;
	TC0110PCRRamSize = 0;
}

void TC0110PCRScan(int nAction)
{
	struct BurnArea ba;
	
	if (nAction & ACB_MEMORY_RAM) {
		memset(&ba, 0, sizeof(ba));
		ba.Data	  = TC0110PCRRam;
		ba.nLen	  = TC0110PCRRamSize;
		ba.szName = "TC0110PCR Ram";
		BurnAcb(&ba);
		
		memset(&ba, 0, sizeof(ba));
		ba.Data	  = TC0110PCRPalette;
		ba.nLen	  = TC0110PCRTotalColours * sizeof(unsigned int);
		ba.szName = "TC0110PCR Palette";
		BurnAcb(&ba);
	}
	
	if (nAction & ACB_DRIVER_DATA) {
		SCAN_VAR(TC0110PCRAddr);
	}
}
