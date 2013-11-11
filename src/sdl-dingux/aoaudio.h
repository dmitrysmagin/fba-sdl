#ifndef _AOAUDIO_H_
#define _AOAUDIO_H_

#ifdef USE_LIBAO
int  libao_open(int rate, int channels, int format);
void libao_close(void);
int  libao_play(unsigned char *data, int len);
void libao_pause(int flag);
#endif

#endif // _AOAUDIO_H_