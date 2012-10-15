
#include "ezxaudio.h"

#define AUDIO_FORMAT	AFMT_S16_LE

//#define AUDIO_BITRATE	8000

#define AUDIO_BLOCKS	8

//#define AUDIO_FREGMENT	(10 | 8 << 16)
#define AUDIO_FREGMENT	0x0002000F

//#define BUFFSIZE 4096
//#define BUFFSIZE 2048
//#define NUM_BUFS 5


typedef struct {
    int channels;
    int samplerate;
    int format;
    int bps;
    int buffersize;
} ao_struct;


extern int dspfd;

//#define	EzxAudioBufferSize	(1024 * 10)


int SndInit();
int SndOpen();
void SndClose();
void SndPlay();
void SndExit();

int SegAim();

int SndRenderFrame();
void SndFrameRendered();

