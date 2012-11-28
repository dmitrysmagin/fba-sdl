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

#ifdef __cplusplus
 extern "C" {
#endif

void gp2x_initialize();
void gp2x_terminate(char *frontend);

void gp2x_video_flip(void);
void gp2x_clear_framebuffers();

#ifdef __cplusplus
 } // End of extern "C"
#endif

#endif
