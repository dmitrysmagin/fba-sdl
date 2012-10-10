#include "burnint.h"
#include "burn_sound.h"
#include "burn_ym2612.h"

#define MAX_YM2612	2

void (*BurnYM2612Update)(int nSegmentEnd);

static int (*BurnYM2612StreamCallback)(int nSoundRate);

static int nBurnYM2612SoundRate;

static short* pBuffer;
static short* pYM2612Buffer[6 * MAX_YM2612];

static int* pAYBuffer;
static int* pAYBuffer2;

static int nYM2612Position;
static int nAY8910Position;

static unsigned int nSampleSize;
static unsigned int nFractionalPosition;

static int nNumChips = 0;

// ----------------------------------------------------------------------------
// Dummy functions

static void YM2612UpdateDummy(int /* nSegmentEnd */)
{
	return;
}

static int YM2612StreamCallbackDummy(int /* nSoundRate */)
{
	return 0;
}

// ----------------------------------------------------------------------------
// Execute YM2612 for part of a frame

static void AY8910Render(int nSegmentLength)
{
	if (nAY8910Position >= nSegmentLength) {
		return;
	}

//	bprintf(PRINT_NORMAL, _T("    AY8910 render %i %6i -> %6i\n"), chip, nAY8910Position[chip], nSegmentLength);

	nSegmentLength -= nAY8910Position;

	pYM2612Buffer[2] = pBuffer + 2 * 4096 + 4 + nAY8910Position;
	pYM2612Buffer[3] = pBuffer + 3 * 4096 + 4 + nAY8910Position;
	pYM2612Buffer[4] = pBuffer + 4 * 4096 + 4 + nAY8910Position;

	AY8910Update(0, &pYM2612Buffer[2], nSegmentLength);
		
	if (nNumChips > 1) {
		pYM2612Buffer[8] = pBuffer + 8 * 4096 + 4 + nAY8910Position;
		pYM2612Buffer[9] = pBuffer + 9 * 4096 + 4 + nAY8910Position;
		pYM2612Buffer[10] = pBuffer + 10 * 4096 + 4 + nAY8910Position;

		AY8910Update(1, &pYM2612Buffer[8], nSegmentLength);
	}

	nAY8910Position += nSegmentLength;
}

static void YM2612Render(int nSegmentLength)
{
	if (nYM2612Position >= nSegmentLength) {
		return;
	}

//	bprintf(PRINT_NORMAL, _T("    YM2612 render %6i -> %6i\n", nYM2612Position, nSegmentLength));

	nSegmentLength -= nYM2612Position;
	
	pYM2612Buffer[0] = pBuffer + 0 * 4096 + 4 + nYM2612Position;
	pYM2612Buffer[1] = pBuffer + 1 * 4096 + 4 + nYM2612Position;

	YM2612UpdateOne(0, &pYM2612Buffer[0], nSegmentLength);
		
	if (nNumChips > 1) {
		pYM2612Buffer[6] = pBuffer + 6 * 4096 + 4 + nYM2612Position;
		pYM2612Buffer[7] = pBuffer + 7 * 4096 + 4 + nYM2612Position;

		YM2612UpdateOne(1, &pYM2612Buffer[6], nSegmentLength);
	}

	nYM2612Position += nSegmentLength;
}

// ----------------------------------------------------------------------------
// Update the sound buffer

static void YM2612UpdateResample(int nSegmentEnd)
{
	short* pSoundBuf = pBurnSoundOut;
	int nSegmentLength = nSegmentEnd;
	int nSamplesNeeded = nSegmentEnd * nBurnYM2612SoundRate / nBurnSoundRate + 1;

//	bprintf(PRINT_NORMAL, _T("    YM2612 update        -> %6i\n", nSegmentLength));

	if (nSamplesNeeded < nAY8910Position) {
		nSamplesNeeded = nAY8910Position;
	}
	if (nSamplesNeeded < nYM2612Position) {
		nSamplesNeeded = nYM2612Position;
	}

	if (nSegmentLength > nBurnSoundLen) {
		nSegmentLength = nBurnSoundLen;
	}
	nSegmentLength <<= 1;

	YM2612Render(nSegmentEnd);
	AY8910Render(nSamplesNeeded);

	pYM2612Buffer[0] = pBuffer + 0 * 4096 + 4;
	pYM2612Buffer[1] = pBuffer + 1 * 4096 + 4;
	pYM2612Buffer[2] = pBuffer + 2 * 4096 + 4;
	pYM2612Buffer[3] = pBuffer + 3 * 4096 + 4;
	pYM2612Buffer[4] = pBuffer + 4 * 4096 + 4;
	pYM2612Buffer[5] = pBuffer + 5 * 4096 + 4;
	
	if (nNumChips > 1) {
		pYM2612Buffer[6] = pBuffer + 6 * 4096 + 4;
		pYM2612Buffer[7] = pBuffer + 7 * 4096 + 4;
		pYM2612Buffer[8] = pBuffer + 8 * 4096 + 4;
		pYM2612Buffer[9] = pBuffer + 9 * 4096 + 4;
		pYM2612Buffer[10] = pBuffer + 10 * 4096 + 4;
		pYM2612Buffer[11] = pBuffer + 11 * 4096 + 4;
	}

	for (int i = (nFractionalPosition >> 16) - 4; i < nSamplesNeeded; i++) {
		pYM2612Buffer[5][i] = (((int)pYM2612Buffer[2][i] + pYM2612Buffer[3][i] + pYM2612Buffer[4][i]) * (4096 * 60 / 100)) >> 12;
		if (nNumChips > 1) pYM2612Buffer[11][i] = (((int)pYM2612Buffer[8][i] + pYM2612Buffer[9][i] + pYM2612Buffer[10][i]) * (4096 * 60 / 100)) >> 12;
	}

	for (int i = (nFractionalPosition & 0xFFFF0000) >> 15; i < nSegmentLength; i += 2, nFractionalPosition += nSampleSize) {
		int nSample;

#define CLIP(A) ((A) < -0x8000 ? -0x8000 : (A) > 0x7fff ? 0x7fff : (A))

		// Left channel
		nSample = INTERPOLATE4PS_16BIT((nFractionalPosition >> 4) & 0x0FFF,
									   pYM2612Buffer[0][(nFractionalPosition >> 16) - 3] + pYM2612Buffer[5][(nFractionalPosition >> 16) - 3],
									   pYM2612Buffer[0][(nFractionalPosition >> 16) - 2] + pYM2612Buffer[5][(nFractionalPosition >> 16) - 2],
									   pYM2612Buffer[0][(nFractionalPosition >> 16) - 1] + pYM2612Buffer[5][(nFractionalPosition >> 16) - 1],
									   pYM2612Buffer[0][(nFractionalPosition >> 16) - 0] + pYM2612Buffer[5][(nFractionalPosition >> 16) - 0]);
		if (nNumChips > 1) nSample += INTERPOLATE4PS_16BIT((nFractionalPosition >> 4) & 0x0FFF,
									   pYM2612Buffer[6][(nFractionalPosition >> 16) - 3] + pYM2612Buffer[11][(nFractionalPosition >> 16) - 3],
									   pYM2612Buffer[6][(nFractionalPosition >> 16) - 2] + pYM2612Buffer[11][(nFractionalPosition >> 16) - 2],
									   pYM2612Buffer[6][(nFractionalPosition >> 16) - 1] + pYM2612Buffer[11][(nFractionalPosition >> 16) - 1],
									   pYM2612Buffer[6][(nFractionalPosition >> 16) - 0] + pYM2612Buffer[11][(nFractionalPosition >> 16) - 0]);
		pSoundBuf[i + 0] = CLIP(nSample);

		// Right channel
		nSample = INTERPOLATE4PS_16BIT((nFractionalPosition >> 4) & 0x0FFF,
									   pYM2612Buffer[1][(nFractionalPosition >> 16) - 3] + pYM2612Buffer[5][(nFractionalPosition >> 16) - 3],
									   pYM2612Buffer[1][(nFractionalPosition >> 16) - 2] + pYM2612Buffer[5][(nFractionalPosition >> 16) - 2],
									   pYM2612Buffer[1][(nFractionalPosition >> 16) - 1] + pYM2612Buffer[5][(nFractionalPosition >> 16) - 1],
									   pYM2612Buffer[1][(nFractionalPosition >> 16) - 0] + pYM2612Buffer[5][(nFractionalPosition >> 16) - 0]);
		if (nNumChips > 1) nSample += INTERPOLATE4PS_16BIT((nFractionalPosition >> 4) & 0x0FFF,
									   pYM2612Buffer[7][(nFractionalPosition >> 16) - 3] + pYM2612Buffer[11][(nFractionalPosition >> 16) - 3],
									   pYM2612Buffer[7][(nFractionalPosition >> 16) - 2] + pYM2612Buffer[11][(nFractionalPosition >> 16) - 2],
									   pYM2612Buffer[7][(nFractionalPosition >> 16) - 1] + pYM2612Buffer[11][(nFractionalPosition >> 16) - 1],
									   pYM2612Buffer[7][(nFractionalPosition >> 16) - 0] + pYM2612Buffer[11][(nFractionalPosition >> 16) - 0]);
									   
		pSoundBuf[i + 1] = CLIP(nSample);

#undef CLIP

	}

	if (nSegmentEnd >= nBurnSoundLen) {
		int nExtraSamples = nSamplesNeeded - (nFractionalPosition >> 16);

//		bprintf(PRINT_NORMAL, _T("   %6i rendered, %i extra, %i <- %i\n"), nSamplesNeeded, nExtraSamples, nExtraSamples, (nFractionalPosition >> 16) + nExtraSamples - 1);

		for (int i = -4; i < nExtraSamples; i++) {
			pYM2612Buffer[0][i] = pYM2612Buffer[0][(nFractionalPosition >> 16) + i];
			pYM2612Buffer[1][i] = pYM2612Buffer[1][(nFractionalPosition >> 16) + i];
			pYM2612Buffer[2][i] = pYM2612Buffer[2][(nFractionalPosition >> 16) + i];
			pYM2612Buffer[3][i] = pYM2612Buffer[3][(nFractionalPosition >> 16) + i];
			pYM2612Buffer[4][i] = pYM2612Buffer[4][(nFractionalPosition >> 16) + i];
			
			if (nNumChips > 1) {
				pYM2612Buffer[6][i] = pYM2612Buffer[6][(nFractionalPosition >> 16) + i];
				pYM2612Buffer[7][i] = pYM2612Buffer[7][(nFractionalPosition >> 16) + i];
				pYM2612Buffer[8][i] = pYM2612Buffer[8][(nFractionalPosition >> 16) + i];
				pYM2612Buffer[9][i] = pYM2612Buffer[9][(nFractionalPosition >> 16) + i];
				pYM2612Buffer[10][i] = pYM2612Buffer[10][(nFractionalPosition >> 16) + i];
			}
		}

		nFractionalPosition &= 0xFFFF;

		nYM2612Position = nExtraSamples;
		nAY8910Position = nExtraSamples;

		dTime += 100.0 / nBurnFPS;
	}
}

static void YM2612UpdateNormal(int nSegmentEnd)
{
	short* pSoundBuf = pBurnSoundOut;
	int nSegmentLength = nSegmentEnd;
	int i;

//	bprintf(PRINT_NORMAL, _T("    YM2612 update        -> %6i\n", nSegmentLength));

	if (nSegmentEnd < nAY8910Position) {
		nSegmentEnd = nAY8910Position;
	}
	if (nSegmentEnd < nYM2612Position) {
		nSegmentEnd = nYM2612Position;
	}

	if (nSegmentLength > nBurnSoundLen) {
		nSegmentLength = nBurnSoundLen;
	}
	
	YM2612Render(nSegmentEnd);
	AY8910Render(nSegmentEnd);

	pYM2612Buffer[0] = pBuffer + 4 + 0 * 4096;
	pYM2612Buffer[1] = pBuffer + 4 + 1 * 4096;
	pYM2612Buffer[2] = pBuffer + 4 + 2 * 4096;
	pYM2612Buffer[3] = pBuffer + 4 + 3 * 4096;
	pYM2612Buffer[4] = pBuffer + 4 + 4 * 4096;
	if (nNumChips > 1) {
		pYM2612Buffer[6] = pBuffer + 4 + 6 * 4096;
		pYM2612Buffer[7] = pBuffer + 4 + 7 * 4096;
		pYM2612Buffer[8] = pBuffer + 4 + 8 * 4096;
		pYM2612Buffer[9] = pBuffer + 4 + 9 * 4096;
		pYM2612Buffer[10] = pBuffer + 4 + 10 * 4096;
	}

	if (bBurnUseMMX) {
		for (int n = nFractionalPosition; n < nSegmentLength; n++) {
			pAYBuffer[n] = pYM2612Buffer[2][n] + pYM2612Buffer[3][n] + pYM2612Buffer[4][n];
			if (nNumChips > 1) pAYBuffer2[n] = pYM2612Buffer[8][n] + pYM2612Buffer[9][n] + pYM2612Buffer[10][n];;
		}
		BurnSoundCopy_FM_OPN_A(pYM2612Buffer[0], pAYBuffer, pSoundBuf, nSegmentLength, 65536 * 60 / 100, 65536 * 60 / 100);
		if (nNumChips > 1) BurnSoundCopy_FM_OPN_Add_A(pYM2612Buffer[6], pAYBuffer2, pSoundBuf, nSegmentLength, 65536 * 60 / 100, 65536 * 60 / 100);
	} else {
		for (int n = nFractionalPosition; n < nSegmentLength; n++) {
			int nAYSample, nTotalSample;

			nAYSample  = pYM2612Buffer[2][n];
			nAYSample += pYM2612Buffer[3][n];
			nAYSample += pYM2612Buffer[4][n];
			if (nNumChips > 1) {
				nAYSample += pYM2612Buffer[8][n];
				nAYSample += pYM2612Buffer[9][n];
				nAYSample += pYM2612Buffer[10][n];
			}

			nAYSample  *= 4096 * 60 / 100;
			nAYSample >>= 12;

			nTotalSample = nAYSample + pYM2612Buffer[0][n];
			if (nNumChips > 1) nTotalSample += pYM2612Buffer[6][n];
			if (nTotalSample < -32768) {
				nTotalSample = -32768;
			} else {
				if (nTotalSample > 32767) {
					nTotalSample = 32767;
				}
			}
			pSoundBuf[(n << 1) + 0] = nTotalSample;

			nTotalSample = nAYSample + pYM2612Buffer[1][n];
			if (nNumChips > 1) nTotalSample += pYM2612Buffer[7][n];
			if (nTotalSample < -32768) {
				nTotalSample = -32768;
			} else {
				if (nTotalSample > 32767) {
					nTotalSample = 32767;
				}
			}
			pSoundBuf[(n << 1) + 1] = nTotalSample;
			
			
			
			
		}
	}

	nFractionalPosition = nSegmentLength;

	if (nSegmentEnd >= nBurnSoundLen) {
		int nExtraSamples = nSegmentEnd - nBurnSoundLen;

		for (i = 0; i < nExtraSamples; i++) {
			pYM2612Buffer[0][i] = pYM2612Buffer[0][nBurnSoundLen + i];
			pYM2612Buffer[1][i] = pYM2612Buffer[1][nBurnSoundLen + i];
			pYM2612Buffer[2][i] = pYM2612Buffer[2][nBurnSoundLen + i];
			pYM2612Buffer[3][i] = pYM2612Buffer[3][nBurnSoundLen + i];
			pYM2612Buffer[4][i] = pYM2612Buffer[4][nBurnSoundLen + i];
			if (nNumChips > 1) {
				pYM2612Buffer[6][i] = pYM2612Buffer[6][nBurnSoundLen + i];
				pYM2612Buffer[7][i] = pYM2612Buffer[7][nBurnSoundLen + i];
				pYM2612Buffer[8][i] = pYM2612Buffer[8][nBurnSoundLen + i];
				pYM2612Buffer[9][i] = pYM2612Buffer[9][nBurnSoundLen + i];
				pYM2612Buffer[10][i] = pYM2612Buffer[10][nBurnSoundLen + i];
			}
		}

		nFractionalPosition = 0;

		nYM2612Position = nExtraSamples;
		nAY8910Position = nExtraSamples;

		dTime += 100.0 / nBurnFPS;
	}
}

// ----------------------------------------------------------------------------
// Callbacks for YM2612 core

void BurnYM2612UpdateRequest()
{
	YM2612Render(BurnYM2612StreamCallback(nBurnYM2612SoundRate));
}

static void BurnAY8910UpdateRequest()
{
	AY8910Render(BurnYM2612StreamCallback(nBurnYM2612SoundRate));
}

// ----------------------------------------------------------------------------
// Initialisation, etc.

void BurnYM2612Reset()
{
	BurnTimerReset();
	
	for (int i = 0; i < nNumChips; i++) {
		YM2612ResetChip(i);
		AY8910Reset(i);
	}
}

void BurnYM2612Exit()
{
	YM2612Shutdown();

	for (int i = 0; i < nNumChips; i++) {
		AY8910Exit(i);
	}

	BurnTimerExit();

	free(pBuffer);
	free(pAYBuffer);
	if (nNumChips > 1) free(pAYBuffer2);
	
	nNumChips = 0;
}

int BurnYM2612Init(int num, int nClockFrequency, FM_IRQHANDLER IRQCallback, int (*StreamCallback)(int), double (*GetTimeCallback)())
{
	if (num > MAX_YM2612) num = MAX_YM2612;

	BurnTimerInit(&YM2612TimerOver, GetTimeCallback);

	if (nBurnSoundRate <= 0) {
		BurnYM2612StreamCallback = YM2612StreamCallbackDummy;

		BurnYM2612Update = YM2612UpdateDummy;

		for (int i = 0; i < nNumChips; i++) {
			AY8910InitYM(i, nClockFrequency, 11025, NULL, NULL, NULL, NULL, BurnAY8910UpdateRequest);
		}
		YM2612Init(num, nClockFrequency, 11025, &BurnOPNTimerCallback, IRQCallback);
		return 0;
	}

	BurnYM2612StreamCallback = StreamCallback;

	if (nFMInterpolation == 3) {
		// Set YM2612 core samplerate to match the hardware
		nBurnYM2612SoundRate = nClockFrequency / (144 * num);
		// Bring YM2612 core samplerate within usable range
		while (nBurnYM2612SoundRate > nBurnSoundRate * 3) {
			nBurnYM2612SoundRate >>= 1;
		}

		BurnYM2612Update = YM2612UpdateResample;

		nSampleSize = (unsigned int)nBurnYM2612SoundRate * (1 << 16) / nBurnSoundRate;
	} else {
		nBurnYM2612SoundRate = nBurnSoundRate;

		BurnYM2612Update = YM2612UpdateNormal;
	}

	for (int i = 0; i < num; i++) {
		AY8910InitYM(i, nClockFrequency, nBurnYM2612SoundRate, NULL, NULL, NULL, NULL, BurnAY8910UpdateRequest);
	}
	
	YM2612Init(num, nClockFrequency, nBurnYM2612SoundRate, &BurnOPNTimerCallback, IRQCallback);

	pBuffer = (short*)malloc(4096 * 6 * num * sizeof(short));
	memset(pBuffer, 0, 4096 * 6 * num * sizeof(short));
		
	pAYBuffer = (int*)malloc(4096 * sizeof(int));
	memset(pAYBuffer, 0, 4096 * sizeof(int));
	
	if (num > 1) {
		pAYBuffer2 = (int*)malloc(4096 * sizeof(int));
		memset(pAYBuffer2, 0, 4096 * sizeof(int));
	}
	
	for (int i = 0; i < num; i++) {
		nYM2612Position = 0;
		nAY8910Position = 0;
		nFractionalPosition = 0;
	}
	
	nNumChips = num;

	return 0;
}

void BurnYM2612Scan(int nAction, int* pnMin)
{
	BurnTimerScan(nAction, pnMin);
	AY8910Scan(nAction, pnMin);

	if (nAction & ACB_DRIVER_DATA) {
		SCAN_VAR(nYM2612Position);
		SCAN_VAR(nAY8910Position);
	}
}

#undef MAX_YM2612
