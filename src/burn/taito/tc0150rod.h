extern unsigned char *TC0150RODRom;
extern unsigned char *TC0150RODRam;

extern void TC0150RODDraw(int yOffs, int pOffs, int Type, int RoadTrans, int LowPriority, int HighPriority);
extern void TC0150RODInit(int nRomSize, int nRamSize, int xFlip);
extern void TC0150RODExit();
extern void TC0150RODScan(int nAction);
