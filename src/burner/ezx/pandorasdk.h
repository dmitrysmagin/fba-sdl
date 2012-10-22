#ifndef _GP2XSDK_
#define _GP2XSDK_

#include <math.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdarg.h>

#define MY_LEFT                     (1)
#define MY_RIGHT                     (2)
#define MY_UP                     (4)
#define MY_DOWN                     (8)
#define MY_BUTT_A                   (16)
#define MY_BUTT_B                   (32)
#define MY_BUTT_X                     (64)
#define MY_BUTT_SL                   (128)
#define MY_BUTT_SR                   (256)
#define MY_START                     (512)
#define MY_QT                       (1024)
#define MY_VOL_UP                   (2048)
#define MY_VOL_DOWN                 (4096)
#define MY_BUTT_Y                     (8192)
#define MY_SELECT                     (16384)
#define MY_PAUSE                    (32768)



enum{
	GP2X_UP=0x1,
	GP2X_UP_LEFT=1<<1,
	GP2X_LEFT=1<<2,
	GP2X_DOWN_LEFT=1<<3,
	GP2X_DOWN=1<<4,
	GP2X_DOWN_RIGHT=1<<5,
	GP2X_RIGHT=1<<6,
	GP2X_UP_RIGHT=1<<7,
    GP2X_START=1<<8,
	GP2X_SELECT=1<<9,
	GP2X_L=1<<10,
	GP2X_R=1<<11,
    GP2X_A=1<<12,
	GP2X_B=1<<13,
	GP2X_X=1<<14,
	GP2X_Y=1<<15,
    GP2X_VOL_UP=1<<23,
	GP2X_VOL_DOWN=1<<22,
	GP2X_PUSH=1<<27 };

#ifdef __cplusplus
 extern "C" {
#endif

void gp2x_initialize();
void gp2x_terminate(char *frontend);

unsigned long gp2x_joystick_read(void);
void gp2x_video_flip(void);
void gp2x_clear_framebuffers();

#ifdef __cplusplus
 } // End of extern "C"
#endif

#endif
