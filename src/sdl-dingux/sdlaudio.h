#ifndef _SDLAUDIO_H_
#define _SDLAUDIO_H_

int  sdl_open(int rate, int channels, int format);
void sdl_close(void);
int  sdl_play(unsigned char *data, int len);
void sdl_pause(int flag);

#endif // _SDLAUDIO_H_