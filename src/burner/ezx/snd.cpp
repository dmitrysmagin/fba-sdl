
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "burner.h"
#include "snd.h"
#include "config.h"

int BUFFSIZE;
int NUM_BUFS;

bool GameMute;
extern CFG_OPTIONS config_options;
extern int nBurnFPS;

int dspfd = -1;

unsigned short *EzxAudioBuffer;
volatile short *pOutput[8];

static int AudioCurBlock = 0;
static int AudioPlayBlock = 0;
static int nAudioChannels=2;
static int AudioBufferSize = 0;
static int currentbuffer = 0;

static volatile int S_SndRenderFrame = 0;

ao_struct ao_data;

// General purpose Ring-buffering routines
int SAMPLESIZE=256;
int sample_sizes[3] = {256, 512, 1024}; // 11025, 22050, 44100

static unsigned char *buffer[16];

static unsigned int buf_read=0;
static unsigned int buf_write=0;
static unsigned int buf_read_pos=0;
static unsigned int buf_write_pos=0;
int volume=126;
static int full_buffers=0;
static int buffered_bytes=0;


static int write_buffer(unsigned char* data,int len)
{
	int len2=0;
	int x;
	while(len>0){
		if(full_buffers==NUM_BUFS) break;
		x=BUFFSIZE-buf_write_pos;
		if(x>len) x=len;
		memcpy(buffer[buf_write]+buf_write_pos,data+len2,x);
		len2+=x; len-=x;
		buffered_bytes+=x; buf_write_pos+=x;
		if(buf_write_pos>=BUFFSIZE){
			// block is full, find next!
			buf_write=(buf_write+1)%NUM_BUFS;
			++full_buffers;
			buf_write_pos=0;
		}
	}
	return len2;
}

static int read_buffer(unsigned char* data,int len)
{
	int len2=0;
	int x;
	while(len>0){
		if(full_buffers==0) break; // no more data buffered!
		x=BUFFSIZE-buf_read_pos;
		if(x>len) x=len;
		memcpy(data+len2,buffer[buf_read]+buf_read_pos,x);
		SDL_MixAudio(data+len2, data+len2, x, volume);
		len2+=x; len-=x;
		buffered_bytes-=x; buf_read_pos+=x;
		if(buf_read_pos>=BUFFSIZE){
			// block is empty, find next!
			buf_read=(buf_read+1)%NUM_BUFS;
			--full_buffers;
			buf_read_pos=0;
		}
	}
	return len2;
}

// end ring buffer stuff

// SDL Callback function
void outputaudio(void *unused, Uint8 *stream, int len) {
	read_buffer(stream, len);
}

static int configure(int rate,int channels,int format)
{
	SDL_AudioSpec aspec, obtained;
	char drv_name[80];

	ao_data.channels=channels;
	ao_data.samplerate=rate;
	ao_data.format=format;

	ao_data.bps=channels*rate;
	if(format != AUDIO_U8 && format != AUDIO_S8)
		ao_data.bps*=2;

	aspec.format   = format;
	aspec.freq	 = rate;
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

	/* did we got what we wanted ? */
	ao_data.channels=obtained.channels;
	ao_data.samplerate=obtained.freq;

	ao_data.buffersize=obtained.size;

	printf("audio frequency %d\n", obtained.freq);
	printf("audio samples %d\n", obtained.samples);
	printf("audio channels %d\n", obtained.channels);

	SDL_AudioDriverName(drv_name, sizeof(drv_name));

	SDL_PauseAudio(0);

	return 1;
}

// close audio device
static void uninit(void)
{
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


// return: how many bytes can be played without blocking
static int get_space(void){
	return (NUM_BUFS-full_buffers)*BUFFSIZE - buf_write_pos;
}

// plays 'len' bytes of 'data'
// it should round it down to outburst*n
// return: number of bytes played
static int play(unsigned char* data,int len,int flags)
{
#if 0
	int ret;

	/* Audio locking prohibits call of outputaudio */
	SDL_LockAudio();
	// copy audio stream into ring-buffer
	ret = write_buffer(data, len);
	SDL_UnlockAudio();

		return ret;
#else
	return write_buffer(data, len);
#endif
}

int SndInit()
{
	if (config_options.option_sound_enable)
	{
		if ((BurnDrvGetHardwareCode() == HARDWARE_CAPCOM_CPS1) || (BurnDrvGetHardwareCode() == HARDWARE_CAPCOM_CPS1_GENERIC))
		{
			nAudioChannels = 2;
			nBurnSoundRate = 11025;
			BUFFSIZE=256*4;
			NUM_BUFS=8;
			printf("using low snd for cps1\n");
		}
		else
		{
			switch(config_options.option_samplerate)
			{
				case 1:
					nBurnSoundRate = 22050;
					BUFFSIZE=256*4*2;
					NUM_BUFS=8;
				break;
				case 2:
					nBurnSoundRate = 44100;
					BUFFSIZE=256*4*4;
					NUM_BUFS=8;
				break;
				default:
					nBurnSoundRate = 11025;
					BUFFSIZE=256*4;
					NUM_BUFS=8;
				break;
			}
		}
		nBurnSoundLen = ((nBurnSoundRate * 100 /*+ 3000*/) / nBurnFPS );
	}
	pBurnSoundOut	= NULL;

	AudioCurBlock	= 0;

	dspfd = -1;

	return 0;
}

int SndOpen()
{
	unsigned int BufferSize;

	BufferSize = nBurnSoundLen * nAudioChannels * 2 * AUDIO_BLOCKS; printf("SND: BufferSize: %i\n", BufferSize);
	EzxAudioBuffer= (unsigned short *)malloc(BufferSize);
	memset(EzxAudioBuffer,0,BufferSize);

	AudioBufferSize = nBurnSoundLen * nAudioChannels * 2;
	printf("SND: AudioBufferSize: %i\n", AudioBufferSize);

	pOutput[0] = (short*)EzxAudioBuffer;
	pOutput[1] = (short*)(EzxAudioBuffer+1*AudioBufferSize/2);
	pOutput[2] = (short*)(EzxAudioBuffer+2*AudioBufferSize/2);
	pOutput[3] = (short*)(EzxAudioBuffer+3*AudioBufferSize/2);
	pOutput[4] = (short*)(EzxAudioBuffer+4*AudioBufferSize/2);
	pOutput[5] = (short*)(EzxAudioBuffer+5*AudioBufferSize/2);
	pOutput[6] = (short*)(EzxAudioBuffer+6*AudioBufferSize/2);
	pOutput[7] = (short*)(EzxAudioBuffer+7*AudioBufferSize/2);

	if ( !GameMute )
	{
		if (config_options.option_sound_enable==2)
		{
			for(int i=0;i<NUM_BUFS;i++) buffer[i]=(unsigned char *) malloc(BUFFSIZE);
			SAMPLESIZE=sample_sizes[config_options.option_samplerate];  //lowest value accepted by audio driver
			dspfd=configure(nBurnSoundRate,nAudioChannels,AUDIO_S16);

			// printf("SOUND: Init done (%d)\n", dspfd);
			if (dspfd > 0)
			{
				pBurnSoundOut  = (short*)pOutput[0];
				audio_resume();
				return 0;
			}
			else
			{
				nBurnSoundRate = 0;
				nBurnSoundLen = 0;
			}
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
	if (EzxAudioBuffer)
	{
		free(EzxAudioBuffer);
		EzxAudioBuffer=NULL;
	}
}

void SndFrameRendered()
{
	if ((dspfd > 0) && (config_options.option_sound_enable==2))
	{
		play((unsigned char *)pOutput[currentbuffer], AudioBufferSize,0);
		++ currentbuffer &= 7;
		pBurnSoundOut = (short*)pOutput[currentbuffer];
	}
}

