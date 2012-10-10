// burn_ym2612.h
#include "driver.h"
extern "C" {
 #include "ay8910.h"
 #include "fm.h"
}
#include "timer.h"

extern "C" void BurnYM2612UpdateRequest();

int BurnYM2612Init(int num, int nClockFrequency, FM_IRQHANDLER IRQCallback, int (*StreamCallback)(int), double (*GetTimeCallback)());
void BurnYM2612Reset();
void BurnYM2612Exit();
extern void (*BurnYM2612Update)(int nSegmentEnd);
void BurnYM2612Scan(int nAction, int* pnMin);

#define BurnYM2612Write(i, a, n) YM2612Write(i, a, n)
#define BurnYM2612Read(i, a) YM2612Read(i, a)


#define BurnYM3438Init(i, n, a, b, c) BurnYM2612Init(i, n, a, b, c)
#define BurnYM3438Reset() BurnYM2612Reset()
#define BurnYM3438Exit() BurnYM2612Exit()
#define BurnYM3438Update(i) BurnYM2612Update(i)
#define BurnYM3438Scan(n, i) BurnYM2612Scan(n, i)

#define BurnYM3438Write(i, a, n) YM2612Write(i, a, n)
#define BurnYM3438Read(i, a) YM2612Read(i, a)
