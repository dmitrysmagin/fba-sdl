// TC0100SCN

#include "tiles_generic.h"

unsigned char *TC0100SCNRam = NULL;
static unsigned char *TC0100SCNChars;
UINT16 TC0100SCNCtrl[8];
static int BgScrollX;
static int BgScrollY;
static int FgScrollX;
static int FgScrollY;
static int CharScrollX;
static int CharScrollY;
static int TC0100SCNTilesNum;
static int TC0100SCNXOffset;
static int TC0100SCNYOffset;
static int TC0100SCNFlipScreenX;

void TC0100SCNCtrlWordWrite(unsigned int Offset, UINT16 Data)
{
	TC0100SCNCtrl[Offset] = Data;
	
	switch (Offset) {
		case 0x00: {
			BgScrollX = -Data;
			return;
		}
		
		case 0x01: {
			FgScrollX = -Data;
			return;
		}
		
		case 0x02: {
			CharScrollX = -Data;
			return;
		}
		
		case 0x03: {
			BgScrollY = -Data;
			return;
		}
		
		case 0x04: {
			FgScrollY = -Data;
			return;
		}
		
		case 0x05: {
			CharScrollY = -Data;
			return;
		}
		
		case 0x06: {
			// Double width stuff
			return;
		}
		
		case 0x07: {
			// flip
			return;
		}
	}
	
	bprintf(PRINT_IMPORTANT, _T("TC0100 Ctrl Word Write %02X, %04X\n"), Offset, Data);
}

int TC0100SCNBottomLayer()
{
	return (TC0100SCNCtrl[6] & 0x08) >> 3;
}

void TC0100SCNRenderBgLayer(int Opaque, unsigned char *pSrc)
{
	int mx, my, Attr, Code, Colour, x, y, TileIndex = 0, Offset, Flip, xFlip, yFlip;
	
	UINT16 *VideoRam = (UINT16*)TC0100SCNRam;
	UINT16 *BgScrollRam = (UINT16*)TC0100SCNRam + (0xc000 / 2);
	
	for (my = 0; my < 64; my++) {
		for (mx = 0; mx < 64; mx++) {
			Offset = 2 * TileIndex;
			Attr = VideoRam[Offset];
			Code = VideoRam[Offset + 1] & (TC0100SCNTilesNum - 1);
			Colour = Attr & 0xff;
			Flip = (Attr & 0xc000) >> 14;
			xFlip = (Flip >> 0) & 0x01;
			yFlip = (Flip >> 1) & 0x01;
			
			x = 8 * mx;
			y = 8 * my;
			
			x -= 16;
			x -= TC0100SCNXOffset;
			y -= TC0100SCNYOffset;
			
			if (TC0100SCNFlipScreenX) {
				xFlip = !xFlip;
				x = nScreenWidth - 8 - x;
			}
			
			int px, py;
			
			UINT32 nPalette = Colour << 4;
			
			for (py = 0; py < 8; py++) {
				for (px = 0; px < 8; px++) {
					unsigned char c = pSrc[(Code * 64) + (py * 8) + px];
					if (xFlip) c = pSrc[(Code * 64) + (py * 8) + (7 - px)];
					if (yFlip) c = pSrc[(Code * 64) + ((7 - py) * 8) + px];
					if (xFlip && yFlip) c = pSrc[(Code * 64) + ((7 - py) * 8) + (7 - px)];
					
					if (c || Opaque) {
						int xPos = x + px;
						int yPos = y + py;
						yPos -= BgScrollY & 0x1ff;
					
						if (yPos < -8) yPos += 512;				
					
						if (yPos >= 0 && yPos < nScreenHeight) {					
							xPos -= ((BgScrollX - BgScrollRam[yPos + TC0100SCNYOffset]) & 0x1ff) * (TC0100SCNFlipScreenX ? -1 : 1);
						
							if (xPos < -8) xPos += 512;
							if (xPos >= 512) xPos -= 512;
						
							unsigned short* pPixel = pTransDraw + (yPos * nScreenWidth);
						
							if (xPos >= 0 && xPos < nScreenWidth) pPixel[xPos] = c | nPalette;
						}
					}
				}
			}
			
			TileIndex++;
		}
	}
}

void TC0100SCNRenderFgLayer(int Opaque, unsigned char *pSrc)
{
	int mx, my, Attr, Code, Colour, x, y, TileIndex = 0, Offset, Flip, xFlip, yFlip;
	
	UINT16 *VideoRam = (UINT16*)TC0100SCNRam + (0x8000 / 2);
	UINT16 *FgScrollRam = (UINT16*)TC0100SCNRam + (0xc400 / 2);
	UINT16 *FgColScrollRam = (UINT16*)TC0100SCNRam + (0xe000 / 2);
	
	for (my = 0; my < 64; my++) {
		for (mx = 0; mx < 64; mx++) {
			Offset = 2 * TileIndex;
			Attr = VideoRam[Offset];
			Code = VideoRam[Offset + 1] & (TC0100SCNTilesNum - 1);
			Colour = Attr & 0xff;
			Flip = (Attr & 0xc000) >> 14;
			xFlip = (Flip >> 0) & 0x01;
			yFlip = (Flip >> 1) & 0x01;
			
			x = 8 * mx;
			y = 8 * my;
			
			x -= 16;
			x -= TC0100SCNXOffset;
			y -= TC0100SCNYOffset;
			
			if (TC0100SCNFlipScreenX) {
				xFlip = !xFlip;
				x = nScreenWidth - 8 - x;
			}
			
			int px, py;
			
			UINT32 nPalette = Colour << 4;
			
			for (py = 0; py < 8; py++) {
				for (px = 0; px < 8; px++) {
					unsigned char c = pSrc[(Code * 64) + (py * 8) + px];
					if (xFlip) c = pSrc[(Code * 64) + (py * 8) + (7 - px)];
					if (yFlip) c = pSrc[(Code * 64) + ((7 - py) * 8) + px];
					if (xFlip && yFlip) c = pSrc[(Code * 64) + ((7 - py) * 8) + (7 - px)];
					
					if (c || Opaque) {
						int xPos = x + px;
						int yPos = y + py;
						yPos -= (FgScrollY - FgColScrollRam[mx]) & 0x1ff;
					
						if (yPos < -8) yPos += 512;				
					
						if (yPos >= 0 && yPos < nScreenHeight) {					
							xPos -= ((FgScrollX - FgScrollRam[yPos + TC0100SCNYOffset]) & 0x1ff) * (TC0100SCNFlipScreenX ? -1 : 1);
						
							if (xPos < -8) xPos += 512;
							if (xPos >= 512) xPos -= 512;
						
							unsigned short* pPixel = pTransDraw + (yPos * nScreenWidth);
						
							if (xPos >= 0 && xPos < nScreenWidth) pPixel[xPos] = c | nPalette;
						}
					}
				}
			}
			
			TileIndex++;
		}
	}
}

static int TC0100SCNPlaneOffsets[2] = { 8, 0 };
static int TC0100SCNXOffsets[8]     = { 0, 1, 2, 3, 4, 5, 6, 7 };
static int TC0100SCNYOffsets[8]     = { 0, 16, 32, 48, 64, 80, 96, 112 };

void TC0100SCNRenderCharLayer()
{
	int mx, my, Attr, Code, Colour, x, y, TileIndex = 0, Flip, xFlip, yFlip;
	
	UINT16 *VideoRam = (UINT16*)TC0100SCNRam + (0x4000 / 2);
	UINT16 *CharRam = (UINT16*)TC0100SCNRam + (0x6000 / 2);
	
	GfxDecode(256, 2, 8, 8, TC0100SCNPlaneOffsets, TC0100SCNXOffsets, TC0100SCNYOffsets, 0x80, (UINT8*)CharRam, TC0100SCNChars);
		
	for (my = 0; my < 64; my++) {
		for (mx = 0; mx < 64; mx++) {
			Attr = VideoRam[TileIndex];
			Code = Attr & 0xff;
			Colour = (Attr >> 6) & 0xfc;
			Flip = (Attr & 0xc000) >> 14;
			xFlip = (Flip >> 0) & 0x01;
			yFlip = (Flip >> 1) & 0x01;
			
			x = 8 * mx;
			y = 8 * my;
		
			x -= CharScrollX & 0x1ff;
			y -= CharScrollY & 0x1ff;
			if (x < -8) x += 512;
			if (y < -8) y += 512;
			
			x -= 16;
			x -= TC0100SCNXOffset;
			y -= TC0100SCNYOffset;
			
			if (TC0100SCNFlipScreenX) {
				xFlip = !xFlip;
				x = nScreenWidth - 8 - x;
			}

			if (x >= 8 && x < (nScreenWidth - 8) && y >= 8 && y < (nScreenHeight - 8)) {
				if (xFlip) {
					if (yFlip) {
						Render8x8Tile_Mask_FlipXY(pTransDraw, Code, x, y, Colour, 2, 0, 0, TC0100SCNChars);
					} else {
						Render8x8Tile_Mask_FlipX(pTransDraw, Code, x, y, Colour, 2, 0, 0, TC0100SCNChars);
					}
				} else {
					if (yFlip) {
						Render8x8Tile_Mask_FlipY(pTransDraw, Code, x, y, Colour, 2, 0, 0, TC0100SCNChars);
					} else {
						Render8x8Tile_Mask(pTransDraw, Code, x, y, Colour, 2, 0, 0, TC0100SCNChars);
					}
				}
			} else {
				if (xFlip) {
					if (yFlip) {
						Render8x8Tile_Mask_FlipXY_Clip(pTransDraw, Code, x, y, Colour, 2, 0, 0, TC0100SCNChars);
					} else {
						Render8x8Tile_Mask_FlipX_Clip(pTransDraw, Code, x, y, Colour, 2, 0, 0, TC0100SCNChars);
					}
				} else {
					if (yFlip) {
						Render8x8Tile_Mask_FlipY_Clip(pTransDraw, Code, x, y, Colour, 2, 0, 0, TC0100SCNChars);
					} else {
						Render8x8Tile_Mask_Clip(pTransDraw, Code, x, y, Colour, 2, 0, 0, TC0100SCNChars);
					}
				}
			}
			
			
			TileIndex++;
		}
	}
}

void TC0100SCNReset()
{
	memset(TC0100SCNChars, 0, 256 * 8 * 8);
	memset(TC0100SCNCtrl, 0, 8);
	BgScrollX = 0;
	BgScrollY = 0;
	FgScrollX = 0;
	FgScrollY = 0;
	CharScrollX = 0;
	CharScrollY = 0;
}

void TC0100SCNInit(int nRamSize, int nNumTiles, int xOffset, int yOffset, int xFlip)
{
	TC0100SCNRam = (unsigned char*)malloc(nRamSize);
	memset(TC0100SCNRam, 0, nRamSize);
	TC0100SCNChars = (unsigned char*)malloc(256 * 8 * 8);
	memset(TC0100SCNChars, 0, 256 * 8 * 8);
	
	TC0100SCNTilesNum = nNumTiles;
	
	TC0100SCNXOffset = xOffset;
	TC0100SCNYOffset = yOffset;
	
	TC0100SCNFlipScreenX = xFlip;
}

void TC0100SCNExit()
{
	free(TC0100SCNRam);
	TC0100SCNRam = NULL;
	
	free(TC0100SCNChars);
	TC0100SCNChars = NULL;
	
	memset(TC0100SCNCtrl, 0, 8);
	BgScrollX = 0;
	BgScrollY = 0;
	FgScrollX = 0;
	FgScrollY = 0;
	CharScrollX = 0;
	CharScrollY = 0;
	
	TC0100SCNTilesNum = 0;
	TC0100SCNXOffset = 0;
	TC0100SCNYOffset = 0;
	TC0100SCNFlipScreenX = 0;
}

void TC0100SCNScan(int nAction)
{
	struct BurnArea ba;
	
	if (nAction & ACB_MEMORY_RAM) {
		memset(&ba, 0, sizeof(ba));
		ba.Data	  = TC0100SCNRam;
		ba.nLen	  = 0x10000;
		ba.szName = "TC0100SCN Ram";
		BurnAcb(&ba);
	}
	
	if (nAction & ACB_DRIVER_DATA) {
		SCAN_VAR(TC0100SCNCtrl);
		SCAN_VAR(BgScrollX);
		SCAN_VAR(BgScrollY);
		SCAN_VAR(FgScrollX);
		SCAN_VAR(FgScrollY);
		SCAN_VAR(CharScrollX);
		SCAN_VAR(CharScrollY);
	}
}
