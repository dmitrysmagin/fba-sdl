#include "tmnt.h"
// TMNT - Tiles
/////////////////////////////////
// All the code is pretty much stolen from DTMNT and MAME, then hacked till it worked. 
// Thanks to Dave for releasing the source to DMNT and the MAME team
//
// Todo:
// Black garbage on the title screen of tmnt 
// add support for zoom
// Rewrite the slow drawing stuff
// Add a bit more flexability to the code to allow other games to work. See WIP MIA driver.
// Fix the shadows
//
// -Kev

static unsigned int nPageBase[4]={0,0,0,0};
static short nScrollX[3]={12*8,0,0},nScrollY[3]={2*8,0,0};

int count=0;


void RawTileClip(unsigned int nTile,unsigned int nPal, int xpos, int ypos)
// Draw a background layer with a primitive form of clipping. A pretty slow and rubish function really :)
{
	unsigned int *ps; 
	int y,x;
	unsigned int s;  
	unsigned char *pPix;
	unsigned int *Pal;
	bool draw;
	nPal<<=4; 
	nPal&=0x3f0; 
	Pal=TmntPal+nPal;
	nTile<<=5;  
	if (nTile>=0x300000-0x20) 
	{
		return;
	}

	ps=(unsigned int *)(TmntTile+nTile); 

	for (y=0;y<8; y++,ps++)
	{
		s=*ps;
		pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
		for (x=0; x<8; xpos++ ,x++,pPix+=nBurnBpp,s<<=4)
		{
			draw=1;
			unsigned char p;
			p=(unsigned char)((s>>28)&15);
			if (p)
			{
				if ((xpos>=0)&&(ypos>=0)&&(ypos<224)&&(xpos<304)) {
					*((unsigned int *)pPix)=Pal[p];
				}
			}
		}
		xpos-=8;
		ypos++;
	}
}

// Work out and draw the Fixed/A/B layers
void TmntTileLayer(int nLayer)
{
	
	unsigned char PalBase[3]={0,0x20,0x28};
    int sx,sy;
	unsigned char *pSrc;
	int nTile;
	int xoff=nScrollX[nLayer];
	int yoff=nScrollY[nLayer];
	int nPal;	
	int p;
	
	int x=0; 
	int y=0;
	for ( y=0; y<29; y++ )
	{
		for ( x=1; x<40; x++ )
		{
			pSrc=TmntRam10+(nLayer<<13);
			sx=x+(xoff>>3); 
			sy=y+(yoff>>3);
			sx&=63; 
			sy&=31;
			pSrc+=(sy<<7)+(sx<<1);
			nTile=*((unsigned short *)pSrc);
			// Get palette
			nPal=(nTile>>13)&7;		
			nPal+=PalBase[nLayer];

			// Get tile page (0-3)
			p=(nTile>>10)&3; 
			nTile=((nTile&0x1000)>>2) | (nTile&0x03ff);
			if (p) 
				nTile+=nPageBase[p];
			if (nTile!=0x10) // blank tile?
				RawTileClip(nTile,nPal,((x-1)*8)-(xoff&7),(y*8)-(yoff&7));
		}
	}
}

int K051960Draw(K051960Sprite sprite)
// Draw the selected sprite. Very Slooooowly.
{
	unsigned char *temp;
	int x,y;
	int xpos,ypos;
	int TempPix;

	sprite.pal_offset<<=4; 
	sprite.pal_offset&=0x3f0; 

	if (sprite.zoomx == 0x10000 && sprite.zoomy == 0x10000)
	{

		if (sprite.flipx && sprite.flipy)
		{
			for (y=sprite.h-1;y>=0;y--)
			{
   				ypos=sprite.y+y;
				for (x=0;x<(sprite.w);x++)
				{
					xpos=-x+(sprite.x+(sprite.w)-1);
					temp=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
					TempPix=TmntSprite[sprite.number^1];
					sprite.number++;
					if ((xpos>=0)&&(ypos>=0)&&(ypos<224)&&(xpos<304)) 
					{
						if (TempPix) 
						{
							if (TempPix < 15)
							{
								*((unsigned int *)temp)=TmntPal[TempPix+sprite.pal_offset];
							}
							else
							{
								if (*temp==0)
								{
									*((unsigned int *)temp)=TmntPal[TempPix+sprite.pal_offset];
								}
								else
								{
							 		*((unsigned int *)temp)=(*temp & 0x00FEFEFE)>>1;
								}
							}
						}
					}
				}
			}
		}

		else if (sprite.flipy)
		{
			for (y=sprite.h-1;y>=0;y--)
			{
				ypos=sprite.y+y;
				for (x=0;x<(sprite.w);x++)
				{
					xpos=sprite.x+x+1;
					temp=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
					TempPix=TmntSprite[sprite.number^1];
					sprite.number++;
					if ((xpos>=0)&&(ypos>=0)&&(ypos<224)&&(xpos<304)) 
					{
						if (TempPix) 
						{
							if (TempPix < 15)
							{
								*((unsigned int *)temp)=TmntPal[TempPix+sprite.pal_offset];
							}
							else
							{
								if (*temp==0)
								{
									*((unsigned int *)temp)=TmntPal[TempPix+sprite.pal_offset];
								}
								else
								{
							 		*((unsigned int *)temp)=(*temp & 0x00FEFEFE)>>1;
								}
							}
						}
					}
				}
			}
		}

		else if (sprite.flipx)
		{
			for (y=0;y<sprite.h;y++) 
			{
				ypos=sprite.y+y;
				for (x=0;x<(sprite.w);x++)
				{
					xpos=-x+(sprite.x+(sprite.w)-1);
					temp=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
					TempPix=TmntSprite[sprite.number^1];
					sprite.number++;
					if ((xpos>=0)&&(ypos>=0)&&(ypos<224)&&(xpos<304)) 
					{
						if (TempPix) 
						{
							if (TempPix < 15)
							{
								*((unsigned int *)temp)=TmntPal[TempPix+sprite.pal_offset];
							}
							else
							{
								if (*temp==0)
								{
									*((unsigned int *)temp)=TmntPal[TempPix+sprite.pal_offset];
								}
								else
								{
							 		*((unsigned int *)temp)=(*temp & 0x00FEFEFE)>>1;
								}
							}
						}
					}
				}
			}
		}
		else for (y=0;y<sprite.h;y++) 
		{
			for (x=0;x<sprite.w;x++)
			{
				xpos=sprite.x+x;
				ypos=sprite.y+y;
				temp=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
				TempPix=TmntSprite[sprite.number^1];
				sprite.number++;
				if ((xpos>=0)&&(ypos>=0)&&(ypos<224)&&(xpos<304)) 
				{
					if (TempPix) 
					{
						if (TempPix < 15)
						{
							*((unsigned int *)temp)=TmntPal[TempPix+sprite.pal_offset];
						}
						else
						{
							if (*temp==0)
							{
								*((unsigned int *)temp)=TmntPal[TempPix+sprite.pal_offset];
							}
							else
							{
						 		*((unsigned int *)temp)=(*temp & 0x00FEFEFE)>>1;
							}
						}
					}
				}
			}
		}
	}
	return 0;
}


void K051960Decode(int i)
{
  // Decodes a sprite and returns a sprite structure. Partally taken from MAME, DMNT and my imagination
	 static int size_table[16]=
	 {16,16,32,16,
	 16,32,32,32,
	 64,32,32,64,
	 64,64,128,128};

	int sproff=0x000000;
	struct K051960Sprite sprite;
	int c=0,offset=0;

	sproff+=i*8;

	if ((K051960Ram[(sproff+0)^1]&0x80)==0) 
		return;   //sprite is not enabled

	sprite.x=(( 256* K051960Ram[(sproff+6)^1] + K051960Ram[(sproff+7)^1]) & 0x01ff)-110;
	sprite.y=240- (( 256* K051960Ram[(sproff+4)^1] + K051960Ram[(sproff+5)^1]) & 0x01ff);

	sprite.zoomx = (K051960Ram[(sproff+6)^1] & 0xfc) >> 2;
	sprite.zoomy = (K051960Ram[(sproff+4)^1] & 0xfc) >> 2;
	sprite.zoomx = 0x10000 / 128 * (128 - sprite.zoomx);
	sprite.zoomy = 0x10000 / 128 * (128 - sprite.zoomy);

	sprite.flipx=(K051960Ram[(sproff+6)^1]&2)?1:0; 
	sprite.flipy=(K051960Ram[(sproff+4)^1]&2)?1:0;  

	// c is the code for the sprite size
	c=(K051960Ram[(sproff+1)^1]>>4)&0xE;  
	sprite.w=size_table[c];
	sprite.h=size_table[c+1];

	offset=(K051960Ram[(sproff+1)^1]&0x1f); 
	offset<<=15;
	offset|=(K051960Ram[(sproff+2)^1]<<7);  

	if (((offset&0x00700)==0x00200)&&(c==0x0a)) offset+=0x200;
	if (((offset&0x001e0)==0x00080)&&(c==0x04)) offset+=0x080;

	offset*=2;

	if (K051960Ram[(sproff+3)^1]&0x10)
		sprite.number=offset;
	else
		sprite.number=0x200000+offset;
	
	sprite.pal_offset=(K051960Ram[(sproff+3)^1]&0x0F)+0x10;  


	if (sprite.number < 0x3FFFC0) // if not a valid sprite so save on the function call.
		K051960Draw(sprite);
}



int K051960DrawSprites()
// Maximum of 128 sprites a frame (TMNT only uses 64)
{
	for (int i=128;i>=0;i--){
		K051960Decode(i);
	}
	return 0;
}



int TmntTileDraw()
// This needs a lot of work but basically works out and draws all the graphics for TMNT
{
	int priority;
	unsigned char da,db;
	short s;

	// Get the two tile page decoders
	da=TmntRam10[0x6b00^1];
	db=TmntRam10[0x6e00^1];

	// Find the tile page base for each
                              
	nPageBase[1]=(da&0xf0)<<7;
	nPageBase[2]=(db&0x0f)<<11; 
	nPageBase[3]=(db&0xf0)<<7;


	// Get the scroll-x values
	s =TmntRam10[0x6402^1]; 
	s<<=8;
	s|=TmntRam10[0x6400^1]; 
	s+=12*8; 
	nScrollX[1]=s;
	
	s =TmntRam10[0x6403^1]; 
	s<<=8;
	s|=TmntRam10[0x6401^1]; 
	s+=12*8; 
	nScrollX[2]=s;
	
	// Get the scroll-y values
	s=TmntRam10[0x6018^1];  // ==  vpage[n].offy=MEMB(vidmem,0x006018+n-1); 
	s+=16; 
	nScrollY[1]=s;
	s=TmntRam10[0x6019^1]; 
	s+=16; 
	nScrollY[2]=s;

	count++;

	// Figure out which order to draw everything . . . .
	priority=PriRam[0x00000]&0x04;
	if (!priority)	
	{
		TmntTileLayer(2);
		TmntTileLayer(1);
		K051960DrawSprites();
		TmntTileLayer(0);
	}
	else 	
	{
		TmntTileLayer(2);
		K051960DrawSprites();
		TmntTileLayer(1);
		TmntTileLayer(0);
	}

  return 0;
}

