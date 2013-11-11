
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "version.h"
#include "burner.h"
#include "sdlaudio.h"

// ============================================================================
// SDL backend
SDL_mutex *sound_mutex;
SDL_cond *sound_cv;

// sdl-related buffers
int BUFFSIZE;
static unsigned char *buffer;
static unsigned int buf_read_pos=0;
static unsigned int buf_write_pos=0;

static int buffered_bytes=0;

static int sdl_write_buffer(unsigned char* data, int len)
{
	SDL_LockMutex(sound_mutex);
#if 0
	while(BUFFSIZE - buffered_bytes < len) SDL_CondWait(sound_cv, sound_mutex);

	if(buf_write_pos + len <= BUFFSIZE ) {
		memcpy(buffer + buf_write_pos, data, len);
	} else {
		int tail = BUFFSIZE - buf_write_pos;
		memcpy(buffer + buf_write_pos, data, tail);
		memcpy(buffer, data + tail, len - tail);
	}
	buf_write_pos = (buf_write_pos + len) % BUFFSIZE;
	buffered_bytes += len;
#else
	for(int i = 0; i < len; i += 4) {
		while(buffered_bytes == BUFFSIZE) SDL_CondWait(sound_cv, sound_mutex);

		*(int*)((char*)(buffer + buf_write_pos)) = *(int*)((char*)(data + i));
		//memcpy(buffer + buf_write_pos, data + i, 4);
		buf_write_pos = (buf_write_pos + 4) % BUFFSIZE;
		buffered_bytes += 4;
	}
#endif
	SDL_CondSignal(sound_cv);
	SDL_UnlockMutex(sound_mutex);
	return len;
}

static int sdl_read_buffer(unsigned char* data,int len)
{
	SDL_LockMutex(sound_mutex);

	while(buffered_bytes < len) SDL_CondWait(sound_cv, sound_mutex);

	if(buffered_bytes >= len) {
		if(buf_read_pos + len <= BUFFSIZE ) {
			memcpy(data, buffer + buf_read_pos, len);
		} else {
			int tail = BUFFSIZE - buf_read_pos;
			memcpy(data, buffer + buf_read_pos, tail);
			memcpy(data + tail, buffer, len - tail);
		}
		buf_read_pos = (buf_read_pos + len) % BUFFSIZE;
		buffered_bytes -= len;
	}

	SDL_CondSignal(sound_cv);
	SDL_UnlockMutex(sound_mutex);
	return len;
}


// end ring buffer stuff

// SDL Callback function
void sdl_callback(void *unused, Uint8 *stream, int len)
{
	sdl_read_buffer(stream, len);
}

static inline int sdl_calc_samples(int rate)
{
	int s;

	// Find the value which is slighly bigger than nBurnSoundLen*2
	for(s = 512; s < (nBurnSoundLen * 2); s += 256); 

	return s;
}

int sdl_open(int rate, int channels, int format)
{
	int SAMPLESIZE;
	SDL_AudioSpec aspec, obtained;

	SAMPLESIZE = sdl_calc_samples(rate);
	BUFFSIZE = SAMPLESIZE * channels * 2 * 6;
	buffer = (unsigned char *) malloc(BUFFSIZE);

	// add some silence to the buffer
	buffered_bytes = SAMPLESIZE * channels * 2;
	buf_read_pos = 0;
	buf_write_pos = buffered_bytes;

	aspec.format   = format;
	aspec.freq     = rate;
	aspec.channels = channels;
	aspec.samples  = SAMPLESIZE;
	aspec.callback = sdl_callback;
	aspec.userdata = NULL;

	/* initialize the SDL Audio system */
	if (SDL_InitSubSystem (SDL_INIT_AUDIO | SDL_INIT_NOPARACHUTE)) {
		printf("SDL: Initializing of SDL Audio failed: %s.\n", SDL_GetError());
		return 0;
	}

	/* Open the audio device and start playing sound! */
	if(SDL_OpenAudio(&aspec, &obtained) < 0) {
			printf("SDL: Unable to open audio: %s\n", SDL_GetError());
			return(0);
	}

	sound_mutex = SDL_CreateMutex();
	sound_cv = SDL_CreateCond();

	printf("audio frequency %d\n", obtained.freq);
	printf("audio samples %d\n", obtained.samples);
	printf("audio channels %d\n", obtained.channels);

	SDL_PauseAudio(0);

	return 1;
}

// close audio device
void sdl_close(void)
{
	SDL_PauseAudio(1);

	SDL_LockMutex(sound_mutex);
	buffered_bytes = BUFFSIZE;
	SDL_CondSignal(sound_cv);
	SDL_UnlockMutex(sound_mutex);
	SDL_Delay(100);

	SDL_DestroyCond(sound_cv);
	SDL_DestroyMutex(sound_mutex);
	SDL_CloseAudio();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
	free(buffer);
	buffer = NULL;
}

// stop playing, keep buffers (for pause)
void sdl_pause(int flag)
{
	SDL_PauseAudio(flag);
}

// plays 'len' bytes of 'data'
// it should round it down to outburst*n
// return: number of bytes played
int sdl_play(unsigned char *data, int len)
{
	return sdl_write_buffer(data, len);
}
