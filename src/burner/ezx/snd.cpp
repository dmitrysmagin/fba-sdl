
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "version.h"
#include "burner.h"
#include "snd.h"
#include "config.h"

int BUFFSIZE;
int NUM_BUFS;

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
int sample_sizes[3] = {256, 512, 768}; // 11025, 22050, 44100
int sample_rates[3] = {11025, 22050, 32000 };

static unsigned char *buffer[16];

static unsigned int buf_read=0;
static unsigned int buf_write=0;
static unsigned int buf_read_pos=0;
static unsigned int buf_write_pos=0;

static int full_buffers=0;
static int buffered_bytes=0;

static int write_buffer(unsigned char* data,int len)
{
	SDL_LockMutex(sound_mutex);
	while(len>0){
		//if(full_buffers == NUM_BUFS) break; // this may cause clicks on some occasions, but CondWait reduces fps
		while(full_buffers == NUM_BUFS) SDL_CondWait(sound_cv, sound_mutex);

		*(buffer[buf_write] + buf_write_pos++) = *data++;
		len--;
		buffered_bytes++;

		if(buf_write_pos>=BUFFSIZE){
			// block is full, find next!
			buf_write=(buf_write+1)%NUM_BUFS;
			++full_buffers;
			buf_write_pos=0;
		}
	}
	SDL_CondSignal(sound_cv);
	SDL_UnlockMutex(sound_mutex);
	return 0;
}

static int read_buffer(unsigned char* data,int len)
{
	while(len>0){
		if(full_buffers == 0) return 0;

		*data++ = *(buffer[buf_read] + buf_read_pos++);
		len--;
		buffered_bytes--;

		if(buf_read_pos >= BUFFSIZE){
			// block is empty, find next!
			buf_read=(buf_read+1)%NUM_BUFS;
			--full_buffers;
			buf_read_pos=0;
		}
	}
	return 0;
}


// end ring buffer stuff

// SDL Callback function
void outputaudio(void *unused, Uint8 *stream, int len)
{
	SDL_LockMutex(sound_mutex);
	read_buffer(stream, len);
	SDL_CondSignal(sound_cv);
	SDL_UnlockMutex(sound_mutex);
}

static int configure(int rate,int channels,int format)
{
	SDL_AudioSpec aspec, obtained;

	aspec.format   = format;
	aspec.freq     = rate;
	aspec.channels = channels;
	aspec.samples  = SAMPLESIZE;
	aspec.callback = outputaudio;
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
static void uninit(void)
{
	SDL_DestroyMutex(sound_mutex);
	SDL_DestroyCond(sound_cv);
	SDL_CloseAudio();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
}


// stop playing and empty buffers (for seeking/pause)
static void reset_audio(void){

	/* Reset ring-buffer state */
	buf_read=0;
	buf_write=0;
	buf_read_pos=0;
	buf_write_pos=0;

	full_buffers=0;
	buffered_bytes=0;

}

// stop playing, keep buffers (for pause)
static void audio_pause(void)
{
	SDL_PauseAudio(1);
}

// resume playing, after audio_pause()
static void audio_resume(void)
{
	SDL_PauseAudio(0);
}

// plays 'len' bytes of 'data'
// it should round it down to outburst*n
// return: number of bytes played
static int play(unsigned char* data,int len,int flags)
{
	return write_buffer(data, len);
}

int SndInit()
{
	if (config_options.option_sound_enable)
	{
		int i = config_options.option_samplerate;
		
		if(i > 2) i = 0;

		if ((BurnDrvGetHardwareCode() == HARDWARE_CAPCOM_CPS1) || (BurnDrvGetHardwareCode() == HARDWARE_CAPCOM_CPS1_GENERIC))
		{
			if(BURN_VERSION == 0x029671) nAudioChannels = 1; // fix for v 0.2.96.71
			i = 0;
			printf("using low snd for cps1\n");
		}

		SAMPLESIZE = sample_sizes[i];
		nBurnSoundRate = sample_rates[i];
		BUFFSIZE=SAMPLESIZE*2*nAudioChannels;
		NUM_BUFS=8;

		nBurnSoundLen = ((nBurnSoundRate * 100) / nBurnFPS );
	}
	pBurnSoundOut	= NULL;

	dspfd = -1;

	return 0;
}

int SndOpen()
{
	AudioBufferSize = nBurnSoundLen * nAudioChannels * 2;
	nBurnSoundBuffer= (unsigned short *)malloc(AudioBufferSize);
	memset(nBurnSoundBuffer,0,AudioBufferSize);

	printf("SND: AudioBufferSize: %i\n", AudioBufferSize);

	if (config_options.option_sound_enable==2)
	{
		for(int i=0;i<NUM_BUFS;i++) buffer[i]=(unsigned char *) malloc(BUFFSIZE);
		SAMPLESIZE=sample_sizes[config_options.option_samplerate];  //lowest value accepted by audio driver
		dspfd = configure(nBurnSoundRate, nAudioChannels, AUDIO_S16);

		if (dspfd > 0)
		{
			pBurnSoundOut  = (short *)nBurnSoundBuffer;
			audio_resume();
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
	if ((dspfd > 0) && (config_options.option_sound_enable==2)) uninit();
	dspfd = -1;
}

void SndPlay()
{
}

void SndExit()
{
	if ((dspfd > 0) && (config_options.option_sound_enable==2)) uninit();

	pBurnSoundOut = NULL;
	dspfd = -1;
	if (nBurnSoundBuffer)
	{
		free(nBurnSoundBuffer);
		nBurnSoundBuffer=NULL;
	}
}

void SndFrameRendered()
{
	if ((dspfd > 0) && (config_options.option_sound_enable==2))
	{
		play((unsigned char *)nBurnSoundBuffer, AudioBufferSize,0);
	}
}

