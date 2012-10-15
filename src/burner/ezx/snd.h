
#define AUDIO_FORMAT	AFMT_S16_LE
#define AUDIO_BLOCKS	8
#define AUDIO_FREGMENT	0x0002000F

typedef struct {
    int channels;
    int samplerate;
    int format;
    int bps;
    int buffersize;
} ao_struct;

extern int dspfd;

int SndInit();
int SndOpen();
void SndClose();
void SndPlay();
void SndExit();

int SndRenderFrame();
void SndFrameRendered();

