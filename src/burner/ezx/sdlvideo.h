
#ifndef _SDLVIDEO_H_
#define _SDLVIDEO_H_

extern int VideoBufferWidth;
extern int VideoBufferHeight;
extern int PhysicalBufferWidth;

extern unsigned short *BurnVideoBuffer;

int VideoInit();
void VideoExit();

#endif // _SDLVIDEO_H_
