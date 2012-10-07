#include "burnint.h"
static unsigned char *Mem                  = NULL;
static unsigned char *MemEnd               = NULL;
static unsigned char *RamStart             = NULL;
static unsigned char *RamEnd               = NULL;

unsigned char *robocopSpriteRam   = NULL;

unsigned int  *robocopPalette     = NULL;
unsigned char *robocopSprites     = NULL;
unsigned char *robocopChars	  = NULL;
unsigned char *robocopBG1	  = NULL;
unsigned char *robocopBG2	  = NULL;

unsigned char *dec0_pf1_data	 =NULL;
unsigned char *dec0_pf1_control_0=NULL;
unsigned char *dec0_pf1_control_1=NULL;
unsigned char *dec0_pf1_colscroll=NULL;
unsigned char *dec0_pf1_rowscroll=NULL;

unsigned char *dec0_pf2_data	 =NULL;
unsigned char *dec0_pf2_control_0=NULL;
unsigned char *dec0_pf2_control_1=NULL;
unsigned char *dec0_pf2_colscroll=NULL;
unsigned char *dec0_pf2_rowscroll=NULL;

unsigned char *dec0_pf3_data	 =NULL;
unsigned char *dec0_pf3_control_0=NULL;
unsigned char *dec0_pf3_control_1=NULL;
unsigned char *dec0_pf3_colscroll=NULL;
unsigned char *dec0_pf3_rowscroll=NULL;

unsigned char *robocopPaletteRam1   = NULL;
unsigned char *robocopPaletteRam2   = NULL;

static bool sprite_flash = 0;

static int MemIndex()
{
	unsigned char *Next; Next = Mem;

	RamStart = Next;
	robocopPaletteRam1   = Next; Next += 0x00800;
	robocopPaletteRam2   = Next; Next += 0x00800;

	robocopSpriteRam    = Next; Next += 0x02000;
	dec0_pf1_data 	    = Next; Next += 0x1FFF;
	dec0_pf2_data	    = Next; Next += 0x7FF;
	dec0_pf3_data       = Next; Next += 0x7FF;
	dec0_pf1_control_0=Next; Next +=0x10;
	dec0_pf1_control_1=Next; Next +=0x10;
	dec0_pf1_colscroll=Next; Next +=0x80;
	dec0_pf1_rowscroll=Next; Next +=0x400;

	dec0_pf2_control_0=Next; Next +=0x10;
	dec0_pf2_control_1=Next;Next +=0x10;
	dec0_pf2_colscroll=Next; Next +=0x80;
	dec0_pf2_rowscroll=Next; Next +=0x400;

	dec0_pf3_control_0=Next;Next +=0x10;
	dec0_pf3_control_1=Next;Next +=0x10;
	dec0_pf3_colscroll=Next; Next +=0x80;
	dec0_pf3_rowscroll=Next; Next +=0x400;

	RamEnd = Next;

	robocopSprites      = Next; Next += 0xC0000;
	robocopChars	    = Next; Next += 0x18000;
	robocopBG1 	    = Next; Next += 0xc0000;
	robocopBG2	    = Next; Next += 0xc0000;
	robocopPalette      = (unsigned int*)Next; 
			      Next += 0x00400 * sizeof(unsigned int);
	MemEnd = Next;
	return 0;
}

int decvid_init()
{
	int nLen;

	// Allocate and Blank all required memory
	Mem = NULL;
	MemIndex();
	nLen = MemEnd - (unsigned char *)0;
	if ((Mem = (unsigned char *)malloc(nLen)) == NULL) return 1;
	memset(Mem, 0, nLen);
	MemIndex();

	return 0;
}

int decvid_exit()
{
	free(Mem);
	Mem = NULL;
	return 0;
}

unsigned int CalcCol(unsigned short nColour,unsigned short nColour2)
{
	int r, g, b;

	r = (nColour >>  0) & 0xFF;
	g = (nColour >>  8) & 0xFF;
	b = (nColour2 >> 0) & 0xFF;
	return BurnHighCol(r, g, b, 0);
}

int decvid_calcpal()
{
	int i;
	unsigned short* ps;
	unsigned short* ps2;
	unsigned int* pd;

	for (i = 0, ps = (unsigned short*)robocopPaletteRam1, ps2=(unsigned short*)robocopPaletteRam2, pd = robocopPalette; i < 0x400; i++, ps++,ps2++, pd++)
	{
		*pd = CalcCol(*ps,*ps2);
	}

	return 0;
}

inline void dec0_chartest(int Number, int Startx, int Starty, int Colour)
{
	int x, y, tempCol, sx, sy;
	unsigned char *temp;

	for (y = 0; y < 8; y++) {
		for (x = 0; x < 8; x++) {
			tempCol = robocopChars[(Number * 64) + (y * 8) + x];

			if (tempCol == 0) 
				continue;	// pixel is transparent
			
			sx = Startx + x;
			sy = Starty + y;
			
			if (sx >= 0 && sx < 256 && sy >= 0 && sy <256) {
				temp = pBurnDraw + (nBurnPitch * sy) + (nBurnBpp * sx);
				PutPix(temp,robocopPalette[tempCol | (Colour<<4)]);
			}
		}
	}
}


void dec0_spritetest(int Number, int Startx, int Starty, int Colour, bool flipx,bool flipy)
{
	int x, y, tempCol, sx, sy;
	unsigned char *temp;

	if (flipx&&flipy)
	{
	Startx+=15;
	Starty+=15;
	for (y = 0; y < 16; y++) {
		for (x = 0; x < 16; x++) {
			tempCol =  robocopSprites[(Number * 256) + (y * 16) + x];

			if (tempCol == 0) 
				continue;	// pixel is transparent
			
			sx = Startx - x;
			sy = Starty - y;
			
			if (sx >= 0 && sx < 256 && sy >= 0 && sy <256) {
				temp = pBurnDraw + (nBurnPitch * sy) + (nBurnBpp * sx);
				PutPix(temp, robocopPalette[tempCol | (Colour << 4)]);
			}
		}
	}
	return;
	}

	if (flipx)
	{
	Startx+=15;
	for (y = 0; y < 16; y++) {
		for (x = 0; x < 16; x++) {
			tempCol = robocopSprites[(Number * 256) + (y * 16) + x];

			if (tempCol == 0) continue;	// pixel is transparent
			
			sx = Startx - x;
			sy = Starty + y;
			
			if (sx >= 0 && sx < 256 && sy >= 0 && sy <256) {
				temp = pBurnDraw + (nBurnPitch * sy) + (nBurnBpp * sx);
				PutPix(temp, robocopPalette[tempCol | (Colour << 4)]);
			}
		}
	}
	return;
	}

	if (flipy)
	{
	Starty+=15;
	for (y = 0; y < 16; y++) {
		for (x = 0; x < 16; x++) {
			tempCol = robocopSprites[(Number * 256) + (y * 16) + x];

			if (tempCol == 0) continue;	// pixel is transparent
			
			sx = Startx + x;
			sy = Starty - y;
			
			if (sx >= 0 && sx < 256 && sy >= 0 && sy <256) {
				temp = pBurnDraw + (nBurnPitch * sy) + (nBurnBpp * sx);
				PutPix(temp, robocopPalette[tempCol | (Colour << 4)]);
			}
		}
	}
	return;
	}

	for (y = 0; y < 16; y++) {
		for (x = 0; x < 16; x++) {
			tempCol = robocopSprites[(Number * 256) + (y * 16) + x];

			if (tempCol == 0) 
				continue;	// pixel is transparent
			
			sx = Startx + x;
			sy = Starty + y;
			
			if (sx >= 0 && sx < 256 && sy >= 0 && sy <256) {
				temp = pBurnDraw + (nBurnPitch * sy) + (nBurnBpp * sx);
				PutPix(temp,robocopPalette[tempCol | (Colour<<4)]);
			}
		}
	}
}

inline void dec0_BG1test(int Number, int Startx, int Starty, int Colour)
{
	int x, y, tempCol, sx, sy;
	unsigned char *temp;

	for (y = 0; y < 16; y++) {
		for (x = 0; x < 16; x++) {
			tempCol = robocopBG1[(Number * 256) + (y * 16) + x];

			if (tempCol == 0) 
				continue;	// pixel is transparent
			
			sx = Startx + x;
			sy = Starty + y;
			
			if (sx > 0 && sx < 256 && sy > 0 && sy < 256) {
				temp = pBurnDraw + (nBurnPitch * sy) + (nBurnBpp * sx);
				PutPix(temp,robocopPalette[tempCol | (Colour<<4)]);
			}
		}
	}
}

inline void dec0_BG2test(int Number, int Startx, int Starty, int Colour)
{
	int x, y, tempCol, sx, sy;
	unsigned char *temp;

	if (Number >= 0xC00)
		return;

	for (y = 0; y < 16; y++) {
		for (x = 0; x < 16; x++) {
			tempCol = robocopBG2[(Number * 256) + (y * 16) + x];

			if (tempCol == 0) 
				continue;	// pixel is transparent
			
			sx = Startx + x;
			sy = Starty + y;
			
			if (sx > 0 && sx < 256 && sy > 0 && sy < 256) {
				temp = pBurnDraw + (nBurnPitch * sy) + (nBurnBpp * sx);
				PutPix(temp,robocopPalette[tempCol | (Colour<<4)]);
			}
		}
	}
}


void decvid_drawsprites(int pri_mask,int pri_val)
{
	int offs;
	unsigned short* dec0_spriteram = ((unsigned short*)robocopSpriteRam);
	sprite_flash=!sprite_flash;  // Must be a better way of doing this - looks rubbish. :)
	for (offs = 0;offs < 0x400;offs += 4)
	{
		int x,y,sprite,colour,multi,fx,fy,inc,flash,mult;

		y = dec0_spriteram[offs];
		if ((y&0x8000) == 0)
			continue;

		x = dec0_spriteram[offs+2];
		colour = x >> 12;
		if ((colour & pri_mask) != pri_val) 
			continue;

		flash=x&0x800;
		if (flash && sprite_flash) 
		{
			continue;
		}

		fx = y & 0x2000;
		fy = y & 0x4000;
		multi = (1 << ((y & 0x1800) >> 11)) - 1;	/* 1x, 2x, 4x, 8x height */
								/* multi = 0   1   3   7 */

		sprite = dec0_spriteram[offs+1] & 0x0fff;

		x = x & 0x01ff;
		y = y & 0x01ff;
		if (x >= 256) 
			x -= 512;
		if (y >= 256) 
			y -= 512;
		x = 240 - x;
		y = 240 - y;

		if (x>256) 
			continue; /* Speedup */

		sprite &= ~multi;
		
		if (fy)
			inc = -1;
		else
		{
			sprite += multi;
			inc = 1;
		}

		mult=-16;

		while (multi >= 0)
		{
			dec0_spritetest(sprite - multi * inc,x,y + mult * multi,colour+16,fx,fy);
			multi--;
		}
	}
}


void decvid_drawchars()
{
	unsigned int mx, my, Code, Colour, x, y, TileIndex = 0;
 	unsigned short* dec0_pf1_control_ram = ((unsigned short*)dec0_pf1_control_1);

	for (my = 0; my < 64 ; my++) {
		for (mx = 0; mx < 32; mx++) {
			Code = dec0_pf1_data[TileIndex + 0] ;
			Colour = dec0_pf1_data[TileIndex + 1]>> 4;
			Code &= 0x0fff;
			x = 8 * mx;
			y = 8 * my;

			x += dec0_pf1_control_ram[0];
			y += dec0_pf1_control_ram[1];
			if (Code!=0) 
			{
				dec0_chartest(Code, x, y , Colour);
			}
			TileIndex += 2 ;
		}
	}
}


void decvid_drawbg1()
{	
	int dwI=0;
	int mx, my, Code, Colour, x, y, TileIndex = 0;
 	unsigned short* dec0_pf2_control_ram = ((unsigned short*)dec0_pf2_control_1);

	for (my = 0; my < 32 ; my++) {
		for (mx = 0; mx < 32; mx++) {
			Code = dec0_pf2_data[TileIndex + 0] | ((dec0_pf2_data[TileIndex + 1])<<8) ;
			Colour = dec0_pf2_data[TileIndex + 1]>> 4;
			Code &= 0x0fff;
			x = ((( dwI & 0x200 ) ? 0x100 : 0 ) + ( ( dwI & 0xff ) % 16 ) * 16);
			y = ((( dwI & 0x100 ) ? 0x100 : 0 ) + ( ( dwI & 0xff ) / 16 ) * 16);
			dwI++;
			x-=dec0_pf2_control_ram[0];
			y-=dec0_pf2_control_ram[1];
			if (x < -16)
			{
				x &= 0x1FF;
			}
			if (y < -16)
			{
				y &= 0x1ff;				
			}
			dec0_BG1test(Code, x, y , Colour+32);
			TileIndex += 2 ;
		}
	}
}

void decvid_drawbg2()
{
	int dwI=0;
	int mx, my, Code, Colour, x, y, TileIndex = 0;
 	unsigned short* dec0_pf3_control_ram = ((unsigned short*)dec0_pf3_control_1);
	for (my = 0; my < 32; my++) {
		for (mx = 0; mx < 32; mx++) {
			Code = dec0_pf3_data[TileIndex + 0] | ((dec0_pf3_data[TileIndex + 1])<<8) ;
			Colour = dec0_pf3_data[TileIndex + 1]>> 4;
			Code &= 0x0fff;
			x = ((( dwI & 0x200 ) ? 0x100 : 0 ) + ( ( dwI & 0xff ) % 16 ) * 16);
			y = ((( dwI & 0x100 ) ? 0x100 : 0 ) + ( ( dwI & 0xff ) / 16 ) * 16);
			dwI++;
			x -= dec0_pf3_control_ram[0];
			y -= dec0_pf3_control_ram[1];
			if (x < -16)
			{
				x &= 0x1FF;
			}
			if (y < -16)
			{
				y &= 0x1ff;				
			}
				
			dec0_BG2test(Code, x, y , Colour+48);

			TileIndex+=2;
		}
	}




}





void decodechars(int dwGraphic, unsigned char * rBitmap, unsigned char *pbBits, int size)
{
	unsigned long  xbits[8]= {0,  1,  2,  3,  4,  5,  6,  7 }; // x bit offsets 
	unsigned long  ybits[8]= {0,  8, 16, 24, 32, 40, 48, 56 }; // y bit offsets 
	unsigned long  bpoffsets[4] = { 0,size*2,size, size*3}; // start bit of bit planes
	unsigned long  xsize=8; // x size in pixels
	unsigned long  ysize=8; // y size in pixels
	unsigned long  bytespertile=64;

	//  The current bit plane.
	unsigned long bCurPlane;

	//  The current pixel row and column in the destination buffer.
	unsigned long dwCurRow;
	unsigned long dwCurCol;

	//  The source bit of interest.
	unsigned long dwSourceBit;

	//  The value of the current pixel in the bitmap.
	unsigned long dwValue;

	//  The offset.
	unsigned long dwOffset = dwGraphic * bytespertile;

	//  Loop through each row and column of the graphic.
	for( dwCurRow = 0 ; dwCurRow < ysize ; ++dwCurRow )
	{
		for( dwCurCol = 0 ; dwCurCol < xsize ; ++dwCurCol )
		{
			//  Initialize the value.
			dwValue = 0;

			//  Loop through each bit plane for the character.
			for( bCurPlane = 0 ; bCurPlane < 4 ; ++bCurPlane )
			{
				//  Shift the value to make room for the new plane.
				dwValue <<= 1;

				//  Calculate the source bit.
				dwSourceBit = dwOffset + bpoffsets[ bCurPlane ] + ybits[ dwCurRow ] +  xbits[ dwCurCol ];

				//  Add the bit from the current bit plane to the 
				//  destination byte.
				dwValue |= ( pbBits[ dwSourceBit >> 3 ] >> (7 - ( dwSourceBit & 7 ))) & 0x01;
				//  Set the pixel value in the bitmap.
				rBitmap[(bytespertile*dwGraphic)+dwCurCol+(dwCurRow*ysize)]= dwValue ;
			}
		}
	}
}

void decodesprite(int dwGraphic, unsigned char * rBitmap, unsigned char *pbBits)
{
	unsigned long  xbits[16]= {128, 129, 130, 131, 132, 133, 134, 135, 0,   1,   2,   3,   4,   5,   6,   7 }; // x offset layout
	unsigned long  ybits[16]= { 0,   8,  16,  24,  32,  40,  48,  56, 64,  72,  80,  88,  96, 104, 112, 120 }; // y offset layout
	unsigned long  bpoffsets[4] = { 786432, 2359296, 0, 1572864 }; // start bit of bit planes
	unsigned long  xsize=16; // x size in pixels
	unsigned long  ysize=16; // y size in pixels
	unsigned long  bytespertile=256;

	//  The current bit plane.
	unsigned long bCurPlane;

	//  The current pixel row and column in the destination buffer.
	unsigned long dwCurRow;
	unsigned long dwCurCol;

	//  The source bit of interest.
	unsigned long dwSourceBit;

	//  The value of the current pixel in the bitmap.
	unsigned long dwValue;

	//  The offset.
	unsigned long dwOffset = dwGraphic * bytespertile;

	//  Loop through each row and column of the graphic.
	for( dwCurRow = 0 ; dwCurRow < ysize ; ++dwCurRow )
	{
		for( dwCurCol = 0 ; dwCurCol < xsize ; ++dwCurCol )
		{
			//  Initialize the value.
			dwValue = 0;

			//  Loop through each bit plane for the character.
			for( bCurPlane = 0 ; bCurPlane < 4 ; ++bCurPlane )
			{
				//  Shift the value to make room for the new plane.
				dwValue <<= 1;

				//  Calculate the source bit.
				dwSourceBit = dwOffset + bpoffsets[ bCurPlane ] + ybits[ dwCurRow ] +  xbits[ dwCurCol ];

				//  Add the bit from the current bit plane to the 
				//  destination byte.
				dwValue |= ( pbBits[ dwSourceBit >> 3 ] >> (7 - ( dwSourceBit & 7 ))) & 0x01;
				//  Set the pixel value in the bitmap.
				rBitmap[(bytespertile*dwGraphic)+dwCurCol+(dwCurRow*ysize)]= dwValue ;
			}
		}
	}
}
void decodeBG1(int dwGraphic, unsigned char * rBitmap, unsigned char *pbBits)
{
	unsigned long  xbits[16]= {128, 129, 130, 131, 132, 133, 134, 135, 0,   1,   2,   3,   4,   5,   6,   7 }; // x offset layout
	unsigned long  ybits[16]= { 0,   8,  16,  24,  32,  40,  48,  56, 64,  72,  80,  88,  96, 104, 112, 120 }; // y offset layout
	unsigned long  bpoffsets[4] = { 524288, 1572864, 0, 1048576  }; // start bit of bit planes
	unsigned long  xsize=16; // x size in pixels
	unsigned long  ysize=16; // y size in pixels
	unsigned long  bytespertile=256;

	//  The current bit plane.
	unsigned long bCurPlane;

	//  The current pixel row and column in the destination buffer.
	unsigned long dwCurRow;
	unsigned long dwCurCol;

	//  The source bit of interest.
	unsigned long dwSourceBit;

	//  The value of the current pixel in the bitmap.
	unsigned long dwValue;

	//  The offset.
	unsigned long dwOffset = dwGraphic * bytespertile;

	//  Loop through each row and column of the graphic.
	for( dwCurRow = 0 ; dwCurRow < ysize ; ++dwCurRow )
	{
		for( dwCurCol = 0 ; dwCurCol < xsize ; ++dwCurCol )
		{
			//  Initialize the value.
			dwValue = 0;

			//  Loop through each bit plane for the character.
			for( bCurPlane = 0 ; bCurPlane < 4 ; ++bCurPlane )
			{
				//  Shift the value to make room for the new plane.
				dwValue <<= 1;

				//  Calculate the source bit.
				dwSourceBit = dwOffset + bpoffsets[ bCurPlane ] + ybits[ dwCurRow ] +  xbits[ dwCurCol ];

				//  Add the bit from the current bit plane to the 
				//  destination byte.
				dwValue |= ( pbBits[ dwSourceBit >> 3 ] >> (7 - ( dwSourceBit & 7 ))) & 0x01;
				//  Set the pixel value in the bitmap.
				rBitmap[(bytespertile*dwGraphic)+dwCurCol+(dwCurRow*ysize)]= dwValue ;
			}
		}
	}
}

void decodeBG2(int dwGraphic, unsigned char * rBitmap, unsigned char *pbBits)
{
	unsigned long  xbits[16]= {128, 129, 130, 131, 132, 133, 134, 135, 0,   1,   2,   3,   4,   5,   6,   7 }; // x offset layout
	unsigned long  ybits[16]= { 0,   8,  16,  24,  32,  40,  48,  56, 64,  72,  80,  88,  96, 104, 112, 120 }; // y offset layout
	unsigned long  bpoffsets[4] = {262144, 786432, 0, 524288  }; // start bit of bit planes
	unsigned long  xsize=16; // x size in pixels
	unsigned long  ysize=16; // y size in pixels
	unsigned long  bytespertile=256;

	//  The current bit plane.
	unsigned long bCurPlane;

	//  The current pixel row and column in the destination buffer.
	unsigned long dwCurRow;
	unsigned long dwCurCol;

	//  The source bit of interest.
	unsigned long dwSourceBit;

	//  The value of the current pixel in the bitmap.
	unsigned long dwValue;

	//  The offset.
	unsigned long dwOffset = dwGraphic * bytespertile;

	//  Loop through each row and column of the graphic.
	for( dwCurRow = 0 ; dwCurRow < ysize ; ++dwCurRow )
	{
		for( dwCurCol = 0 ; dwCurCol < xsize ; ++dwCurCol )
		{
			//  Initialize the value.
			dwValue = 0;

			//  Loop through each bit plane for the character.
			for( bCurPlane = 0 ; bCurPlane < 4 ; ++bCurPlane )
			{
				//  Shift the value to make room for the new plane.
				dwValue <<= 1;

				//  Calculate the source bit.
				dwSourceBit = dwOffset + bpoffsets[ bCurPlane ] + ybits[ dwCurRow ] +  xbits[ dwCurCol ];

				//  Add the bit from the current bit plane to the 
				//  destination byte.
				dwValue |= ( pbBits[ dwSourceBit >> 3 ] >> (7 - ( dwSourceBit & 7 ))) & 0x01;
				//  Set the pixel value in the bitmap.
				rBitmap[(bytespertile*dwGraphic)+dwCurCol+(dwCurRow*ysize)]= dwValue ;
			}
		}
	}
}
