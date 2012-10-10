
#include "cps3.h"

#define CPS3_VOICES		16

#define CPS3_SND_INT_RATE		60
#define CPS3_SND_RATE			(42954500 / 3 / 384)
#define CPS3_SND_BUFFER_SIZE	(CPS3_SND_RATE / CPS3_SND_INT_RATE)
#define CPS3_SND_LINEAR_SHIFT	16

typedef struct {
	unsigned int regs[8];
	unsigned int pos;
	unsigned short frac;
} cps3_voice;

typedef struct {
	cps3_voice voice[CPS3_VOICES];
	unsigned short key;

	unsigned char * rombase;
	signed short buffer[ (CPS3_SND_BUFFER_SIZE + 1) * 2 ];
	unsigned int delta;

} cps3snd_chip;

static cps3snd_chip * chip;

unsigned char __fastcall cps3SndReadByte(unsigned int addr)
{
	//addr &= 0x000003ff;
	bprintf(PRINT_NORMAL, _T("SND Attempt to read byte value of location %8x\n"), addr);
	return 0;
}

unsigned short __fastcall cps3SndReadWord(unsigned int addr)
{
	addr &= 0x000003ff;
	
	if (addr < 0x200)	{
		unsigned int * p = & (chip->voice[addr >> 5].regs[(addr>>2) & 7]);
		if (addr & 0x02)
			return  (*p) & 0xffff;
		else
			return  (*p) >> 16;
	} else
	if (addr == 0x200)	{
		return chip->key;
	} else

	bprintf(PRINT_NORMAL, _T("SND Attempt to read word value of location %8x\n"), addr);
	return 0;
}

unsigned int __fastcall cps3SndReadLong(unsigned int addr)
{
	addr &= 0x000003ff;
	
	bprintf(PRINT_NORMAL, _T("SND Attempt to read long value of location %8x\n"), addr);
	return 0;
}

void __fastcall cps3SndWriteByte(unsigned int addr, unsigned char data)
{
	addr &= 0x000003ff;
	bprintf(PRINT_NORMAL, _T("SND Attempt to write byte value %2x to location %8x\n"), data, addr);
}

void __fastcall cps3SndWriteWord(unsigned int addr, unsigned short data)
{
	addr &= 0x000003ff;
	
	if (addr < 0x200) {
		unsigned int * p = & (chip->voice[addr >> 5].regs[(addr>>2) & 7]);
		if (addr & 0x02)
			*p = (*p & 0xffff0000) | data;
		else
			*p = (*p & 0x0000ffff) | (data << 16);
		
		//bprintf(PRINT_NORMAL, _T("SND Attempt to write word value %4x to Chip[%02d][%02d] %s\n"), data, addr >> 5, (addr>>2) & 7, (addr & 0x02) ? "lo" : "hi" );
		
	} else
	if (addr == 0x200) {
		unsigned short key = data;
		for (int i = 0; i < CPS3_VOICES; i++) {
			// Key off -> Key on
			if ((key & (1 << i)) && !(chip->key & (1 << i)))	{
				chip->voice[i].frac = 0;
				chip->voice[i].pos = 0;
			}
		}
		chip->key = key;
	} else
		bprintf(PRINT_NORMAL, _T("SND Attempt to write word value %4x to location %8x\n"), data, addr);
	
}

void __fastcall cps3SndWriteLong(unsigned int addr, unsigned int data)
{
	addr &= 0x000003ff;
	bprintf(PRINT_NORMAL, _T("SND Attempt to write long value %8x to location %8x\n"), data, addr);
}

int cps3SndInit(unsigned char * sndrom)
{
	chip = (cps3snd_chip *) malloc( sizeof(cps3snd_chip) );
	if ( chip ) {
		memset( chip, 0, sizeof(cps3snd_chip) );
		chip->rombase = sndrom;
		
		/* 
		 * CPS-3 Sound chip clock: 42954500 / 3 / 384 = 37286.89
		 * Sound interupt 80Hz 
		 */
		
		if (nBurnSoundRate) {
			chip->delta = (CPS3_SND_BUFFER_SIZE << CPS3_SND_LINEAR_SHIFT) / nBurnSoundLen;
			//chip->burnlen = nBurnSoundRate / CPS3_SND_INT_RATE;
			//bprintf(0, _T("BurnSnd %08x, %d, %d\n"), chip->delta, chip->burnlen, nBurnSoundLen);
		}
		
		return 0;
	}
	return 1;
}

void cps3SndReset()
{
}

void cps3SndExit()
{
	free( chip );
}

void cps3SndUpdate()
{
	if (!pBurnSoundOut) {
		// TODO: ???
		// chip->key = 0;
		return;	
	}
	
	memset(chip->buffer, 0, (CPS3_SND_BUFFER_SIZE + 1) * 2 * 2 );
	
	signed char * base = (signed char *)chip->rombase;
	
	cps3_voice *vptr = &chip->voice[0];

	for(int i=0; i<CPS3_VOICES; i++, vptr++) {
		if (chip->key & (1 << i)) {
			
			#define SWAP(a) ((a >> 16) | ((a & 0xffff) << 16))

			unsigned int start = vptr->regs[1];
			unsigned int end   = vptr->regs[5];
			unsigned int loop  = (vptr->regs[3] & 0xffff) + ((vptr->regs[4] & 0xffff) << 16);
			unsigned int step  = (vptr->regs[3] >> 16);

			/*
			 * Can Sound Volume less then zero ???
			 * pre amp. to reduce some noise 
			 */
			//signed short vol_l = (vptr->regs[7] & 0xffff);
			//signed short vol_r = ((vptr->regs[7] >> 16) & 0xffff);
			int vol_l = (((vptr->regs[7] >>  0) & 0x7fff) * 12) >> 4;
			int vol_r = (((vptr->regs[7] >> 16) & 0x7fff) * 12) >> 4;

			unsigned int pos = vptr->pos;
			unsigned short frac = vptr->frac;
			
			/* TODO */
			start = SWAP(start) - 0x400000;
			end = SWAP(end) - 0x400000;
			loop -= 0x400000;
			
			/* Go through the buffer and add voice contributions */
			signed short * buffer = &(chip->buffer[0]);
			
			for (unsigned int j=0; j<CPS3_SND_BUFFER_SIZE; j++) {
				signed int sample;

				pos += (frac >> 12);
				frac &= 0xfff;

				if (start + pos >= end) {
					if (vptr->regs[2]) {
						pos = loop - start;
					} else {
						chip->key &= ~(1 << i);
						break;
					}
				}

				/*
				 * 8bit sample store with 16bit bigend ???
				 */
				sample = base[(start + pos) ^ 1];
				frac += step;
				
				//buffer[0] += (sample * (vol_l >> 8));
				//buffer[1] += (sample * (vol_r >> 8));
				buffer[0] += (sample * vol_l) >> 8;
				buffer[1] += (sample * vol_r) >> 8;

				buffer += 2;
			}


			vptr->pos = pos;
			vptr->frac = frac;
		}
	}
	

	{
		unsigned int * pOut = (unsigned int *)pBurnSoundOut;
		unsigned int * pSrc = (unsigned int *)(&(chip->buffer[0]));
		unsigned int pos = 0;
		for(int i=0; i<nBurnSoundLen; i++) {

			//if ((pos >> CPS3_SND_LINEAR_SHIFT) >= CPS3_SND_BUFFER_SIZE) {
			//	bprintf(0, _T("BurnSnd out renge %d\n"), pos >> CPS3_SND_LINEAR_SHIFT);
			//	pos = (CPS3_SND_BUFFER_SIZE - 1) << CPS3_SND_LINEAR_SHIFT;
			//}
			
			*pOut = pSrc[pos >> CPS3_SND_LINEAR_SHIFT];
	
			pOut ++;
			pos += chip->delta;
		}
	}
}

int cps3SndScan(int nAction)
{
	if (nAction & ACB_DRIVER_DATA) {
		
		SCAN_VAR( chip->voice );
		SCAN_VAR( chip->key );
		
	}
	return 0;
}

