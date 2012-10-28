
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#ifdef USE_LIBAO
#include <ao/ao.h>
#endif

#include "version.h"
#include "burner.h"
#include "snd.h"
#include "config.h"

extern bool bPauseOn;

#ifdef USE_LIBAO
ao_device *ao_dev;
ao_sample_format ao;
#endif

SDL_mutex *sound_mutex;
SDL_cond *sound_cv;

extern CFG_OPTIONS config_options;
extern int nBurnFPS;

int dspfd = -1;

unsigned short *nBurnSoundBuffer; // buffer where Burn driver will write snd data

static int nAudioChannels = 2;
static int AudioBufferSize = 0;

// General purpose Ring-buffering routines
int SAMPLESIZE=256;
int sample_sizes[3] = {512, 1024, 1536}; // 11025, 22050, 44100
int sample_rates[3] = {11025, 22050, 44100};

int BUFFSIZE;
static unsigned char *buffer;
static unsigned int buf_read_pos=0;
static unsigned int buf_write_pos=0;

static int buffered_bytes=0;

static int sdl_write_buffer(unsigned char* data, int len)
{
	SDL_LockMutex(sound_mutex);

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

	SDL_CondSignal(sound_cv);
	SDL_UnlockMutex(sound_mutex);
	return len;
}

static int sdl_read_buffer(unsigned char* data,int len)
{
	SDL_LockMutex(sound_mutex);

	//while(buffered_bytes < len) SDL_CondWait(sound_cv, sound_mutex);

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

static int sdl_open_audio(int rate,int channels,int format)
{
	SDL_AudioSpec aspec, obtained;

	aspec.format   = format;
	aspec.freq     = rate;
	aspec.channels = channels;
	aspec.samples  = SAMPLESIZE;
	aspec.callback = sdl_callback;
	aspec.userdata = NULL;

	/* initialize the SDL Audio system */
	if (SDL_Init (SDL_INIT_AUDIO/*|SDL_INIT_NOPARACHUTE*/)) {
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
static void sdl_close_audio(void)
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
}

// stop playing, keep buffers (for pause)
static void sdl_pause_audio(void)
{
	SDL_PauseAudio(1);
}

// resume playing, after sdl_pause_audio()
static void sdl_resume_audio(void)
{
	SDL_PauseAudio(0);
}

// plays 'len' bytes of 'data'
// it should round it down to outburst*n
// return: number of bytes played
static int play(unsigned char* data,int len,int flags)
{
	return sdl_write_buffer(data, len);
}

int SndInit()
{
	if (config_options.option_sound_enable) {
		int i = config_options.option_samplerate;
		
		if(i > 2) i = 0;

		if ((BurnDrvGetHardwareCode() == HARDWARE_CAPCOM_CPS1) || (BurnDrvGetHardwareCode() == HARDWARE_CAPCOM_CPS1_GENERIC))
		{
			if(BURN_VERSION == 0x029671) { // fix for v 0.2.96.71
				nAudioChannels = 1; 
				config_options.option_samplerate = i = 0;
				printf("using low snd for cps1\n");
			}
		}

		nBurnSoundRate = sample_rates[i];
		nBurnSoundLen = ((nBurnSoundRate * 100) / nBurnFPS );
	}

	pBurnSoundOut	= NULL;

	return 0;
}

int SndOpen()
{
	AudioBufferSize = nBurnSoundLen * nAudioChannels * 2;
	nBurnSoundBuffer= (unsigned short *)malloc(AudioBufferSize);
	memset(nBurnSoundBuffer,0,AudioBufferSize);

	printf("SND: AudioBufferSize: %i\n", AudioBufferSize);

	#ifdef USE_LIBAO
	if (config_options.option_sound_enable == 1) {
		ao_initialize();
		ao.bits = 16; // AUDIO_S16
		ao.rate = nBurnSoundRate;
		ao.channels = nAudioChannels;
		ao.byte_format = AO_FMT_LITTLE;
		ao.matrix = NULL;
		ao_dev = ao_open_live(ao_default_driver_id(), &ao, NULL);
		if(ao_dev) {
			pBurnSoundOut  = (short *)nBurnSoundBuffer;
			return 0;
		} else {
			pBurnSoundOut = NULL;
			nBurnSoundRate = 0;
			nBurnSoundLen = 0;
		}
	}
	#endif

	if (config_options.option_sound_enable == 2)
	{
		SAMPLESIZE = sample_sizes[config_options.option_samplerate];
		BUFFSIZE = SAMPLESIZE*2*nAudioChannels * 8;
		buffer = (unsigned char *) malloc(BUFFSIZE);
		dspfd = sdl_open_audio(nBurnSoundRate, nAudioChannels, AUDIO_S16);

		if (dspfd > 0)
		{
			pBurnSoundOut  = (short *)nBurnSoundBuffer;
			sdl_resume_audio();
			return 0;
		}
		else
		{
			nBurnSoundRate = 0;
			nBurnSoundLen = 0;
		}
	}

	return -1;
}

void SndClose()
{
	#ifdef USE_LIBAO
	if(config_options.option_sound_enable == 1) {
		ao_close(ao_dev);
		ao_shutdown();
	}
	#endif
	if ((dspfd > 0) && (config_options.option_sound_enable==2)) {
		sdl_close_audio();
		dspfd = -1;
	}
}

void SndPlay()
{
}

void SndExit()
{
	SndClose();

	pBurnSoundOut = NULL;
	if (nBurnSoundBuffer)
	{
		free(nBurnSoundBuffer);
		nBurnSoundBuffer=NULL;
	}
}

void SndFrameRendered()
{
	if(!bPauseOn) {
		#ifdef USE_LIBAO
		if(config_options.option_sound_enable == 1) {
			ao_play(ao_dev, (char *)nBurnSoundBuffer, AudioBufferSize);
		}
		#endif

		if ((dspfd > 0) && (config_options.option_sound_enable == 2))
		{
			play((unsigned char *)nBurnSoundBuffer, AudioBufferSize,0);
		}
	}
}

