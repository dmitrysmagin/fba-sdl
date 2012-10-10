extern unsigned char *TC0100SCNRam;
extern UINT16 TC0100SCNCtrl[8];

extern void TC0100SCNCtrlWordWrite(unsigned int Offset, UINT16 Data);
extern int TC0100SCNBottomLayer();
extern void TC0100SCNRenderBgLayer(int Opaque, unsigned char *pSrc);
extern void TC0100SCNRenderFgLayer(int Opaque, unsigned char *pSrc);
extern void TC0100SCNRenderCharLayer();
extern void TC0100SCNReset();
extern void TC0100SCNInit(int nRamSize, int nNumTiles, int xOffset, int yOffset, int xFlip);
extern void TC0100SCNExit();
extern void TC0100SCNScan(int nAction);

