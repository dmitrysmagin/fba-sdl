extern unsigned char TC0220IOCInputPort0[8];
extern unsigned char TC0220IOCInputPort1[8];
extern unsigned char TC0220IOCInputPort2[8];
extern unsigned char TC0220IOCDip[2];
extern unsigned char TC0220IOCInput[3];

extern UINT8 TC0220IOCPortRead();
extern UINT8 TC0220IOCHalfWordPortRead();
extern UINT8 TC0220IOCPortRegRead();
extern UINT8 TC0220IOCHalfWordRead(int Offset);
extern UINT8 TC0220IOCRead(UINT8 Port);
extern void TC0220IOCWrite(UINT8 Port, UINT8 Data);
extern void TC0220IOCHalfWordPortRegWrite(UINT16 Data);
extern void TC0220IOCHalfWordPortWrite(UINT16 Data);
extern void TC0220IOCHalfWordWrite(int Offset, UINT16 Data);
extern void TC0220IOCReset();
extern void TC0220IOCExit();
extern void TC0220IOCScan(int nAction);
