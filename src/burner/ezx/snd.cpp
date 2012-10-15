#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include "burner.h"
#include "snd.h"
#include "config.h"
#include "SDL/SDL.h"
#include "gamewidget.h"

//FILE * outputfile;

int BUFFSIZE;
int NUM_BUFS;

int expectedperframe;
unsigned int sampletime;

extern bool GameMute;
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

static bool exitSoundThread = false;
static pthread_t soundthread_p = (pthread_t) -1;

//int soundbuffersize=2048;
ao_struct ao_data;
// General purpose Ring-buffering routines
int SAMPLESIZE=1024;
//int bytestopass;

static unsigned char *buffer[15];

static unsigned int buf_read=0;
static unsigned int buf_write=0;
static unsigned int buf_read_pos=0;
static unsigned int buf_write_pos=0;
int volume=126;
static int full_buffers=0;
static int buffered_bytes=0;


static int write_buffer(unsigned char* data,int len){
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

static int read_buffer(unsigned char* data,int len){
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

static int configure(int rate,int channels,int format){

	/* SDL Audio Specifications */
	SDL_AudioSpec aspec, obtained;
	char drv_name[80];

	ao_data.channels=channels;
	ao_data.samplerate=rate;
	ao_data.format=format;

	ao_data.bps=channels*rate;
	if(format != AUDIO_U8 && format != AUDIO_S8)
	  ao_data.bps*=2;

	aspec.format   = format;

	/* The desired audio frequency in samples-per-second. */
	aspec.freq     = rate;

	/* Number of channels (mono/stereo) */
	aspec.channels = channels;

	/* The desired size of the audio buffer in samples. This number should be a power of two, and may be adjusted by the audio driver to a value more suitable for the hardware. Good values seem to range between 512 and 8192 inclusive, depending on the application and CPU speed. Smaller values yield faster response time, but can lead to underflow if the application is doing heavy processing and cannot fill the audio buffer in time. A stereo sample consists of both right and left channels in LR ordering. Note that the number of samples is directly related to time by the following formula: ms = (samples*1000)/freq */
	aspec.samples  = SAMPLESIZE;

	/* This should be set to a function that will be called when the audio device is ready for more data. It is passed a pointer to the audio buffer, and the length in bytes of the audio buffer. This function usually runs in a separate thread, and so you should protect data structures that it accesses by calling SDL_LockAudio and SDL_UnlockAudio in your code. The callback prototype is:
void callback(void *userdata, Uint8 *stream, int len); userdata is the pointer stored in userdata field of the SDL_AudioSpec. stream is a pointer to the audio buffer you want to fill with information and len is the length of the audio buffer in bytes. */
	aspec.callback = outputaudio;

	/* This pointer is passed as the first parameter to the callback function. */
	aspec.userdata = NULL;

	/* initialize the SDL Audio system */
        if (SDL_Init (SDL_INIT_AUDIO/*|SDL_INIT_NOPARACHUTE*/)) {
  //              MSG_ERR("SDL: Initializing of SDL Audio failed: %s.\n", SDL_GetError());
                return 0;
        }

	/* Open the audio device and start playing sound! */
	if(SDL_OpenAudio(&aspec, &obtained) < 0) {
    //    	MSG_ERR("SDL: Unable to open audio: %s\n", SDL_GetError());
        	return(0);
	}

	/* did we got what we wanted ? */
	ao_data.channels=obtained.channels;
	ao_data.samplerate=obtained.freq;

	ao_data.buffersize=obtained.size;

	printf("audio format %d\n",obtained.format);
	printf("audio samples %d\n",obtained.samples);

	SDL_AudioDriverName(drv_name, sizeof(drv_name));

	SDL_PauseAudio(0);

	return 1;
}

// close audio device
static void uninit(void){
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
static int play(unsigned char* data,int len,int flags){

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

// return: delay in seconds between first and last sample in buffer
static float get_delay(void){
    return (float)(buffered_bytes + ao_data.buffersize)/(float)ao_data.bps;
}


//static bool exitSoundThread = false;
//static pthread_t soundthread_p = (pthread_t) -1;

void *soundthread_f (void *a)
{
	while (!exitSoundThread)
	{
		AudioCurBlock++;

		if (AudioCurBlock >= 8) AudioCurBlock = 0;

		write(dspfd, (void *)pOutput[AudioCurBlock], EzxAudioBuffer[1]);
		ioctl(dspfd, SOUND_PCM_SYNC, 0);
	}
	return NULL;

}


int SndInit()
{
	if (config_options.option_sound_enable)
	{
		if ((BurnDrvGetHardwareCode() == HARDWARE_CAPCOM_CPS1) || (BurnDrvGetHardwareCode() == HARDWARE_CAPCOM_CPS1_GENERIC))
		//if (1==0)
		{
			/*nBurnSoundRate = 11025;
			nAudioChannels = 1;
			BUFFSIZE=512;
            NUM_BUFS=4;
            expectedperframe=734;*/
			nAudioChannels = 2;
			nBurnSoundRate = 11025;
            BUFFSIZE=2048/2;
            NUM_BUFS=6;
            expectedperframe=1468/2;
        //    printf("using low snd for cps1\n");
		}
		else
		{
			switch(config_options.option_samplerate)
			{
				case 1:
					nBurnSoundRate = 22050;
                    BUFFSIZE=2048;
                    NUM_BUFS=6;
                    expectedperframe=1468;
				break;
				case 2:
					nBurnSoundRate = 44100;
					BUFFSIZE=4096;
                    NUM_BUFS=10;
                    expectedperframe=2936;
				break;
				default:
					nBurnSoundRate = 11025;
					BUFFSIZE=1024;
                    NUM_BUFS=5;
                    expectedperframe=734;
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
unsigned int bufferStart;

	BufferSize = (nBurnSoundLen * nAudioChannels * AUDIO_BLOCKS)*2+512;
	EzxAudioBuffer= (unsigned short *)malloc(BufferSize);
	AudioBufferSize = nBurnSoundLen * nAudioChannels * 2;
	memset(EzxAudioBuffer,0,BufferSize);
	EzxAudioBuffer[1]=(EzxAudioBuffer[0]=(nBurnSoundLen * nAudioChannels * 2));
	EzxAudioBuffer[2]=(1000000000/nBurnSoundRate)&0xFFFF;
	EzxAudioBuffer[3]=(1000000000/nBurnSoundRate)>>16;
	bufferStart = (unsigned int)&EzxAudioBuffer[4];
	pOutput[0] = (short*)bufferStart;
	pOutput[1] = (short*)(bufferStart+1*EzxAudioBuffer[1]);
	pOutput[2] = (short*)(bufferStart+2*EzxAudioBuffer[1]);
	pOutput[3] = (short*)(bufferStart+3*EzxAudioBuffer[1]);
	pOutput[4] = (short*)(bufferStart+4*EzxAudioBuffer[1]);
	pOutput[5] = (short*)(bufferStart+5*EzxAudioBuffer[1]);
	pOutput[6] = (short*)(bufferStart+6*EzxAudioBuffer[1]);
	pOutput[7] = (short*)(bufferStart+7*EzxAudioBuffer[1]);
	if ( !GameMute )
	{
	int frag = 10 + config_options.option_samplerate;
    	frag |= 2 << 16;


		if (config_options.option_sound_enable==1)
		{
		    dspfd = ezx_open_dsp ( nBurnSoundRate, nAudioChannels, AUDIO_FORMAT, frag );
            if (dspfd >= 0)
            {
                pthread_create(&soundthread_p, NULL, &soundthread_f, NULL);
                return 0;
            }
		}
		if (config_options.option_sound_enable==2)
		{
            for(int i=0;i<NUM_BUFS;i++) buffer[i]=(unsigned char *) malloc(BUFFSIZE);
            SAMPLESIZE=512;  //lowest value accepted by audio driver
            dspfd=configure(nBurnSoundRate,nAudioChannels,AUDIO_S16);
		}
		// printf("SOUND: Init done (%d)\n", dspfd);
		if (((dspfd > 0)  && (config_options.option_sound_enable==2))  || ((dspfd>=0) && (config_options.option_sound_enable==1)))
		{
		    if (config_options.option_sound_enable==2) pBurnSoundOut  = (short*)pOutput[0];
		    if (config_options.option_sound_enable==2) audio_resume();


			return 0;
		}
		else
		{
			nBurnSoundRate	= 0;
			nBurnSoundLen	= 0;
		}
	}
	sampletime=EZX_GetTicks();
	return -1;
}

void SndClose()
{
	if ((dspfd > 0) && (config_options.option_sound_enable==2)) uninit();
    if ((dspfd >= 0) && (config_options.option_sound_enable==1)) ezx_close_dsp(dspfd);
	dspfd = -1;
}

void SndPlay()
{
}

void SndExit()
{
	if ((dspfd > 0) && (config_options.option_sound_enable==2)) uninit();
    if ((dspfd >= 0) && (config_options.option_sound_enable==1)) ezx_close_dsp(dspfd);


	pBurnSoundOut = NULL;
	dspfd = -1;
	if (EzxAudioBuffer)
	{
	    free(EzxAudioBuffer);
	    EzxAudioBuffer=NULL;
	}

}

int SegAim()
{
  int aim=AudioCurBlock;

  aim--; if (aim<0) aim+=8;

  return aim;

}


void SndFrameRendered()
{
    //AudioBufferSize=1470;
    if ((dspfd > 0) && (config_options.option_sound_enable==2))
    {
      //  unsigned int gtime=EZX_GetTicks();
//        unsigned int temp;
        //write(dspfd, (void *)pOutput[currentbuffer], AudioBufferSize);
/*        if (gtime-sampletime>16667)
        {
            temp=(expectedperframe*(gtime-sampletime))/16667;
            if (temp-AudioBufferSize<AudioBufferSize)
            {
                unsigned int skip=AudioBufferSize/(temp-AudioBufferSize);
                unsigned char *p;
                p=(unsigned char*)malloc(temp);
                unsigned char *r;
                r=p;
                unsigned char *q;
                q=(unsigned char*)pOutput[currentbuffer];
                for (int i=0;i<AudioBufferSize;i+=skip)
                {
                    memcpy(p,q,skip);
                    p+=skip;
                    q+=skip;
                    memcpy(p,q,2);
                    p+=2;
                }
                memcpy((unsigned char*)pOutput[currentbuffer],r,temp);
                free(r);
            }
            else
            {
                printf ("temp %d\n",temp);
                unsigned int skip=temp/AudioBufferSize;
                printf ("skip %d\n",skip);
                unsigned char *p;
                p=(unsigned char*)malloc(temp+(skip*2));

                unsigned char *q;
                q=(unsigned char*)pOutput[currentbuffer];
                unsigned int z=0;
                for (int i=0;i<AudioBufferSize;i+=2)
                {
                    for (int x=0;x<skip;x++)
                    {
                        //p[z]=q[i];
                        //p[z+1]=q[i+1];
                        z+=2;
                    }
                }
                //memcpy(q,p,temp);
                free(p);
                temp=AudioBufferSize;
            }

        }
        else temp=AudioBufferSize;
*/
        play((unsigned char *)pOutput[currentbuffer], AudioBufferSize,0);
        ++ currentbuffer &= 7;
        pBurnSoundOut = (short*)pOutput[currentbuffer];
  //      printf("bs: %d\n",AudioBufferSize);
   //     sampletime=EZX_GetTicks();

  /*      AudioCurBlock++;

		if (AudioCurBlock >= 8) AudioCurBlock = 0;

		play((unsigned char *)pOutput[AudioCurBlock], EzxAudioBuffer[1],0);*/
    }

    if ((dspfd >= 0) && (config_options.option_sound_enable==1))
    {
        //printf("audiobufsz %d\n",AudioBufferSize);
        write(dspfd, (void *)pOutput[currentbuffer],AudioBufferSize);
        ioctl(dspfd, SOUND_PCM_SYNC, 0);
        //ezx_play_dsp(dspfd,(char *)pOutput[currentbuffer], AudioBufferSize);
        //play((unsigned char *)pOutput[currentbuffer], AudioBufferSize,0);
        ++ currentbuffer &= 7;
        pBurnSoundOut = (short*)pOutput[currentbuffer];

    }
}

