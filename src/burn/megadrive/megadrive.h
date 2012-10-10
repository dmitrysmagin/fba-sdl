extern unsigned char MegadriveReset;
extern unsigned char bMegadriveRecalcPalette;
extern unsigned char MegadriveJoy1[12];
extern unsigned char MegadriveJoy2[12];
extern unsigned char MegadriveDIP[2];

extern int MegadriveInit();
extern int MegadriveNoByteswapInit();
extern int MegadriveExit();
extern int MegadriveFrame();
extern int MegadriveScan(int nAction, int *pnMin);
