#include "burnint.h"

extern unsigned char* pTileData;
extern int nScreenWidth, nScreenHeight;

int GenericTilesInit();
int GenericTilesExit();

void Render8x8Tile(unsigned short* pDestDraw, int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile);
void Render8x8Tile_Clip(unsigned short* pDestDraw, int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile);
void Render8x8Tile_FlipX(unsigned short* pDestDraw, int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile);
void Render8x8Tile_FlipX_Clip(unsigned short* pDestDraw, int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile);
void Render8x8Tile_FlipY(unsigned short* pDestDraw, int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile);
void Render8x8Tile_FlipY_Clip(unsigned short* pDestDraw, int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile);
void Render8x8Tile_FlipXY(unsigned short* pDestDraw, int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile);
void Render8x8Tile_FlipXY_Clip(unsigned short* pDestDraw, int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile);

void Render8x8Tile_Mask(unsigned short* pDestDraw, int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile);
void Render8x8Tile_Mask_Clip(unsigned short* pDestDraw, int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile);
void Render8x8Tile_Mask_FlipX(unsigned short* pDestDraw, int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile);
void Render8x8Tile_Mask_FlipX_Clip(unsigned short* pDestDraw, int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile);
void Render8x8Tile_Mask_FlipY(unsigned short* pDestDraw, int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile);
void Render8x8Tile_Mask_FlipY_Clip(unsigned short* pDestDraw, int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile);
void Render8x8Tile_Mask_FlipXY(unsigned short* pDestDraw, int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile);
void Render8x8Tile_Mask_FlipXY_Clip(unsigned short* pDestDraw, int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile);

void Render16x16Tile(unsigned short* pDestDraw, int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile);
void Render16x16Tile_Clip(unsigned short* pDestDraw, int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile);
void Render16x16Tile_FlipX(unsigned short* pDestDraw, int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile);
void Render16x16Tile_FlipX_Clip(unsigned short* pDestDraw, int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile);
void Render16x16Tile_FlipY(unsigned short* pDestDraw, int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile);
void Render16x16Tile_FlipY_Clip(unsigned short* pDestDraw, int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile);
void Render16x16Tile_FlipXY(unsigned short* pDestDraw, int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile);
void Render16x16Tile_FlipXY_Clip(unsigned short* pDestDraw, int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nPaletteOffset, unsigned char *pTile);

void Render16x16Tile_Mask(unsigned short* pDestDraw, int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile);
void Render16x16Tile_Mask_Clip(unsigned short* pDestDraw, int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile);
void Render16x16Tile_Mask_FlipX(unsigned short* pDestDraw, int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile);
void Render16x16Tile_Mask_FlipX_Clip(unsigned short* pDestDraw, int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile);
void Render16x16Tile_Mask_FlipY(unsigned short* pDestDraw, int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile);
void Render16x16Tile_Mask_FlipY_Clip(unsigned short* pDestDraw, int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile);
void Render16x16Tile_Mask_FlipXY(unsigned short* pDestDraw, int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile);
void Render16x16Tile_Mask_FlipXY_Clip(unsigned short* pDestDraw, int nTileNumber, int StartX, int StartY, int nTilePalette, int nColourDepth, int nMaskColour, int nPaletteOffset, unsigned char *pTile);
