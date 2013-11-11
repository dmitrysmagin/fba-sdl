#ifndef _SDLAUDIO_H_
#define _SDLAUDIO_H_

// with mutexes
int  sdl_open_m(int rate, int channels, int format);
void sdl_close_m(void);
int  sdl_play_m(unsigned char *data, int len);
void sdl_pause(int flag);

// with SDL_LockAudio
int  sdl_open(int rate, int channels, int format);
void sdl_close(void);
int  sdl_play(unsigned char *data, int len);

#endif // _SDLAUDIO_H_