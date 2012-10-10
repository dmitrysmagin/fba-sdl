extern unsigned int *TC0110PCRPalette;
extern int TC0110PCRTotalColours;

extern UINT16 TC0110PCRWordRead();
extern void TC0110PCRStep1WordWrite(int Offset, UINT16 Data);
extern void TC0110PCRStep1RBSwapWordWrite(int Offset, UINT16 Data);
extern void TC0110PCRReset();
extern void TC0110PCRInit(int nRamSize, int nNumColours);
extern void TC0110PCRExit();
void TC0110PCRScan(int nAction);

