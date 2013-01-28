
#ifndef _SDLVIDEO_H_
#define _SDLVIDEO_H_

extern unsigned short *VideoBuffer;
extern int VideoBufferWidth;
extern int VideoBufferHeight;
extern int PhysicalBufferWidth;

extern unsigned short *BurnVideoBuffer;

int VideoInit();
void VideoExit();

void SystemInit();
void SystemExit(char *frontend);

void VideoFlip(void);
void VideoClear();

#endif // _SDLVIDEO_H_
