
#include "burnint.h"
#include "M6502.h"


#ifndef HARDWARE_SUPERVISION
#define HARDWARE_SUPERVISION (HARDWARE_PREFIX_MISC)
#endif

unsigned char  supervInputPort0[9] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned char  supervDip[2]         = {0, 0};
unsigned char  drvReset = 0;

static struct BurnInputInfo supervInputList[]=
{
	{"Start 1"           , BIT_DIGITAL  , supervInputPort0 + 7, "p1 start"  },
	{"P1 Up"             , BIT_DIGITAL  , supervInputPort0 + 0, "p1 up"     },
	{"P1 Down"           , BIT_DIGITAL  , supervInputPort0 + 1, "p1 down"   },
	{"P1 Left"           , BIT_DIGITAL  , supervInputPort0 + 2, "p1 left"   },
	{"P1 Right"          , BIT_DIGITAL  , supervInputPort0 + 3, "p1 right"  },
	{"P1 Fire 1"         , BIT_DIGITAL  , supervInputPort0 + 6, "p1 fire 1" },
	{"P1 Fire 2"         , BIT_DIGITAL  , supervInputPort0 + 4, "p1 fire 2" },
	{"P1 Fire 3"         , BIT_DIGITAL  , supervInputPort0 + 5, "p1 fire 3" },
	{"Reset"			 , BIT_DIGITAL	, &drvReset				 , "reset"     },
	{"Dip 1"             , BIT_DIPSWITCH, supervDip + 0        , "dip"       },
	{"Dip 2"             , BIT_DIPSWITCH, supervDip + 1        , "dip"       },
};
static struct BurnDIPInfo supervDIPList[]=
{
	// Defaults
	{0x0c, 0xff, 0xff, 0x00, NULL                     },
	{0x0d, 0xff, 0xff, 0x00, NULL                     },
};

STDDIPINFO(superv);
STDINPUTINFO(superv);

static unsigned char *cart_rom;

#define RGB555(R,G,B) ((((int)(B))<<10)|(((int)(G))<<5)|(((int)(R))))

// gfx
static unsigned short	*supervision_palette;
static unsigned char    gpu_regs[4];

// memory
static unsigned char	*memorymap_programRom;
static unsigned char	*memorymap_lowerRam;
static unsigned char	*memorymap_upperRam;
static unsigned char	*memorymap_lowerRomBank;
static unsigned char	*memorymap_upperRomBank;
static unsigned char	*memorymap_regs;

static unsigned int   memorymap_programRomSize;

// controls

static unsigned char controls_state;

// timer
static unsigned char timer_regs[2];
static int timer_cycles;
static bool   timer_activated;

// controls

void controls_reset()
{
	bprintf(1, "controls: reset\n");
	controls_state = 0x00;
}

unsigned char controls_read(unsigned int addr)
{
	return(controls_state^0xff); 
}

bool controls_update(void)
{
	//	unsigned char *keystate = SDL_GetKeyState(NULL);

	controls_state = 0;

	if (supervInputPort0[3])	
		controls_state|=0x01;
	if (supervInputPort0[2])	
		controls_state|=0x02;
	if (supervInputPort0[1])	
		controls_state|=0x04;
	if (supervInputPort0[0])		
		controls_state|=0x08;
	if (supervInputPort0[6])		
		controls_state|=0x10;
	if (supervInputPort0[4])		
		controls_state|=0x20;
	if (supervInputPort0[7])		
		controls_state|=0x80;
	if (supervInputPort0[5])		
		controls_state|=0x40;

	return(true);
}

/// end controls


///////
// M6502

static M6502	m6502_registers;

byte Loop6502(register M6502 *R)
{
	return(INT_QUIT);
}

M6502	*supervision_get6502regs(void)
{
	return(&m6502_registers);
}

/////
// end M6502
////







//////
// Sound

//#include <math.h>

static unsigned char    sound_regs[2][4];
static unsigned int   sound_channel_size[2];
static unsigned int	sound_channel_pos[2];

static short    *sound_buffers[2];
static unsigned char    audioDma_regs[8];

#define BPS			22050
#define BPSMAX		AUDIO_MAX_FREQUENCY
#define BPSMIN		AUDIO_MIN_FREQUENCY
#define BUFSIZE		BPS
#define POFF		128
#define PDIV		3
#define PH			POFF+PDIV*8
#define PL			POFF-PDIV*7
/*
AUDIOINFO	audio_info;
AUDIOCAPS	audio_caps;
HAC			audio_FmVoice[2];
AUDIOWAVE	audio_FmWave[2];
HAC			audio_NoiseVoice;
AUDIOWAVE   audio_NoiseWave;
HAC			audio_AudioDmaVoice;
AUDIOWAVE   audio_AudioDmaWave;
bool		audio_FmVoicePlaying[2];
bool        audio_NoiseVoicePlaying;
bool        audio_AudioDmaVoicePlaying;

bool		audio_FmVoicePlayingOld[2];
bool        audio_NoiseVoicePlayingOld;
bool        audio_AudioDmaVoicePlayingOld;

unsigned char       RandData[BUFSIZE];
unsigned int audio_mrand(unsigned int Degree);
*/
const long TblChVol[16]={				// n/15 n=0~15
	-10000,-2352,-1750,-1398,-1148,-954,-796,-662,
    -546,-444,-352,-269,-194,-124,-60,0
};

void audio_NoiseVoiceFreq(int freq, int volume)
{
 //   for(int j=0;j<(BUFSIZE);j++)
	//	RandData[j] = ((audio_mrand(15)*volume)/127);

	//memcpy(audio_NoiseWave.lpData,		RandData, audio_NoiseWave.dwLength);
	//AWriteAudioData(&audio_NoiseWave,	0, audio_NoiseWave.dwLength);
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
//
//
//
//
////////////////////////////////////////////////////////////////////////////////
void audio_FmVoicePlay(int channel, bool bPlay)
{
	//if (audio_FmVoicePlaying[channel] == bPlay)
	//	return;

	//audio_FmVoicePlaying[channel] = bPlay;

	//if (bPlay)
	//	APlayVoice(audio_FmVoice[channel], &audio_FmWave[channel]);
	//else
	//	AStopVoice(audio_FmVoice[channel]);
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
//
//
//
//
////////////////////////////////////////////////////////////////////////////////
void audio_FmVoiceFreq(int channel, int freq, int volume)
{
//	int size;
//
//	volume = (127*volume)/15;
//
//	//fprintf(log_get()," volume: %i\n", volume);
//	if (freq==0)
//	{
//		audio_FmVoicePlay(channel, false);
//		return;
//	}
//	size = (BUFSIZE/freq);
//	
//	if (size == 0)
//	{
//		audio_FmVoicePlay(channel, false);
//		return;
//	}
//
//    for(int j=0;j<(BUFSIZE);j++)
//	{
//		RandData[j] = (((unsigned int)(((j%size)<(size>>1))?127:-128))*volume)/127;
////		RandData[j] = (char)(127.0f*sin((((float)j)*((float)freq)*2*3.14159)/((float)BUFSIZE)));
//	}
//	memcpy(audio_FmWave[channel].lpData,		RandData, audio_FmWave[channel].dwLength);
//	AWriteAudioData(&audio_FmWave[channel],	0, audio_FmWave[channel].dwLength);
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
//
//
//
//
////////////////////////////////////////////////////////////////////////////////
void audio_AudioDmaSetSample(unsigned int offset, unsigned int length, unsigned int freq, unsigned int cartSpace)
{
	//float scale = ((float)freq)/((float)audio_AudioDmaWave.dwLength);

	//for (int i = 0; i < audio_AudioDmaWave.dwLength; i++)
	//{
	//	short data;

	//	int offs = ((i>>1)*scale);
	//	if (offs>= (length>>1))
	//		data =0;
	//	else
	//		data = (cartSpace)?(memorymap_getRomPointer()[offset + offs]):Rd6502(offset + offs);
	//	
	//	if (i&0x01)
	//		data = ((data>>4)-8)*8;
	//	else
	//		data = ((data&0x0f)-8)*8;

	//	RandData[i] = (char)(data);
	//}
	//memcpy(audio_AudioDmaWave.lpData, RandData, audio_AudioDmaWave.dwLength);
	//AWriteAudioData(&audio_AudioDmaWave,	0, audio_AudioDmaWave.dwLength);
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
//
//
//
//
////////////////////////////////////////////////////////////////////////////////
void audio_NoiseVoiceVolume(int volume)
{
	//ASetVoiceVolume(audio_NoiseVoice, TblChVol[volume]);
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
//
//
//
//
////////////////////////////////////////////////////////////////////////////////
void audio_AudioDmaVoiceVolume(int volume)
{
	//ASetVoiceVolume(audio_AudioDmaVoice, TblChVol[volume]);
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
//
//
//
//
////////////////////////////////////////////////////////////////////////////////
void audio_NoiseVoicePlay(bool bPlay)
{
	//if (audio_NoiseVoicePlaying == bPlay)
	//	return;

	//audio_NoiseVoicePlaying = bPlay;

	//if (bPlay)
	//	APlayVoice(audio_NoiseVoice, &audio_NoiseWave);
	//else
		//AStopVoice(audio_NoiseVoice);
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
//
//
//
//
////////////////////////////////////////////////////////////////////////////////
void audio_AudioDmaVoicePlay(bool bPlay)
{
	//if (audio_AudioDmaVoicePlaying == bPlay)
	//	return;

	//audio_AudioDmaVoicePlaying = bPlay;

	//if (bPlay)
	//	APlayVoice(audio_AudioDmaVoice, &audio_AudioDmaWave);
	//else
	//	AStopVoice(audio_AudioDmaVoice);
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
//
//
//
//
////////////////////////////////////////////////////////////////////////////////
void audio_FmVoiceVolume(int channel, int volume)
{
	//ASetVoiceVolume(audio_FmVoice[channel], TblChVol[volume]);
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
//
//
//
//
////////////////////////////////////////////////////////////////////////////////
void audio_turnSound(bool bOn)
{
	//if (bOn)
	//{
	//	audio_FmVoicePlay(0, audio_FmVoicePlayingOld[0]);
	//	audio_FmVoicePlay(1, audio_FmVoicePlayingOld[1]);
	//	audio_NoiseVoicePlay(audio_NoiseVoicePlayingOld);
	//	audio_AudioDmaVoicePlay(audio_AudioDmaVoicePlayingOld);
	//} 
	//else
	//{
	//	audio_FmVoicePlayingOld[0] = audio_FmVoicePlaying[0];
	//	audio_FmVoicePlayingOld[1] = audio_FmVoicePlaying[1];
	//	audio_NoiseVoicePlayingOld = audio_NoiseVoicePlaying;
	//	audio_AudioDmaVoicePlayingOld = audio_AudioDmaVoicePlaying;
	//	audio_FmVoicePlay(0, false);
	//	audio_FmVoicePlay(1, false);
	//	audio_NoiseVoicePlay(false);
	//	audio_AudioDmaVoicePlay(false);
	//}
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
//
//
//
//
////////////////////////////////////////////////////////////////////////////////
unsigned int audio_mrand(unsigned int Degree)
{
#define BIT(n) (1<<n)
	typedef struct {
		unsigned int N;
    	int InputBit;
    	int Mask;
	} POLYNOMIAL;

	static POLYNOMIAL TblMask[]=
	{
		{ 2,BIT(2) ,BIT(0)|BIT(1)},
		{ 3,BIT(3) ,BIT(0)|BIT(1)},
		{ 4,BIT(4) ,BIT(0)|BIT(1)},
		{ 5,BIT(5) ,BIT(0)|BIT(2)},
		{ 6,BIT(6) ,BIT(0)|BIT(1)},
		{ 7,BIT(7) ,BIT(0)|BIT(1)},
		{ 8,BIT(8) ,BIT(0)|BIT(2)|BIT(3)|BIT(4)},
		{ 9,BIT(9) ,BIT(0)|BIT(4)},
		{10,BIT(10),BIT(0)|BIT(3)},
		{11,BIT(11),BIT(0)|BIT(2)},
		{12,BIT(12),BIT(0)|BIT(1)|BIT(4)|BIT(6)},
		{13,BIT(13),BIT(0)|BIT(1)|BIT(3)|BIT(4)},
		{14,BIT(14),BIT(0)|BIT(1)|BIT(4)|BIT(5)},
		{15,BIT(15),BIT(0)|BIT(1)},
		{NULL,NULL,NULL},
	};

	static POLYNOMIAL *pTbl=TblMask;
	static int ShiftReg=pTbl->InputBit-1;
	int XorReg=0;
	int Masked;

    if(pTbl->N!=Degree)
    {
    	pTbl=TblMask;
		while(pTbl->N)
		{
			if(pTbl->N==Degree)
			{
				break;
			}
        	pTbl++;
		}
		if(!pTbl->N)
		{
			pTbl--;
		}

    	ShiftReg&=pTbl->InputBit-1;
		if(!ShiftReg)
		{
			ShiftReg=pTbl->InputBit-1;
		}
    }

	Masked=ShiftReg&pTbl->Mask;
	while(Masked)
	{
		XorReg^=Masked&0x01;
		Masked>>=1;
	}

	if(XorReg)
	{
		ShiftReg|=pTbl->InputBit;
	}
	else
	{
		ShiftReg&=~pTbl->InputBit;
	}
	ShiftReg>>=1;

	return ShiftReg;
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
//
//
//
//
////////////////////////////////////////////////////////////////////////////////
void audio_createFmVoices()
{
	//for (int i = 0;i<2;i++)
	//{
	//	ACreateAudioVoice(&audio_FmVoice[i]);
	//	ASetVoiceVolume  ( audio_FmVoice[i], AUDIO_MAX_VOLUME);
	//	ASetVoicePanning ( audio_FmVoice[i], AUDIO_MAX_PANNING>>1);
	//	ASetVoiceFrequency(audio_FmVoice[i],audio_info.nSampleRate);

	//	audio_FmWave[i].nSampleRate		= audio_info.nSampleRate;
	//	audio_FmWave[i].dwLength		= BUFSIZE;
	//	audio_FmWave[i].dwLoopStart		= 0;
	//	audio_FmWave[i].dwLoopEnd		= audio_FmWave[i].dwLength;
	//	audio_FmWave[i].wFormat			= AUDIO_FORMAT_8BITS | AUDIO_FORMAT_MONO | AUDIO_FORMAT_LOOP;
	//	ACreateAudioData(&audio_FmWave[i]);
	//}
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
//
//
//
//
////////////////////////////////////////////////////////////////////////////////
void audio_createNoiseVoice()
{
	//ACreateAudioVoice(&audio_NoiseVoice);
	//ASetVoiceVolume  ( audio_NoiseVoice, AUDIO_MAX_VOLUME);
	//ASetVoicePanning ( audio_NoiseVoice, AUDIO_MAX_PANNING>>1);
	//ASetVoiceFrequency(audio_NoiseVoice,audio_info.nSampleRate);

	//audio_NoiseWave.nSampleRate		= audio_info.nSampleRate;
	//audio_NoiseWave.dwLength		= BUFSIZE;
	//audio_NoiseWave.dwLoopStart		= 0;
	//audio_NoiseWave.dwLoopEnd		= audio_NoiseWave.dwLength;
	//audio_NoiseWave.wFormat			= AUDIO_FORMAT_8BITS | AUDIO_FORMAT_MONO | AUDIO_FORMAT_LOOP;
	//ACreateAudioData(&audio_NoiseWave);
	//audio_NoiseVoiceFreq(50, 127);
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
//
//
//
//
////////////////////////////////////////////////////////////////////////////////
void audio_createAudioDmaVoice()
{
	//ACreateAudioVoice(&audio_AudioDmaVoice);
	//ASetVoiceVolume  ( audio_AudioDmaVoice, AUDIO_MAX_VOLUME);
	//ASetVoicePanning ( audio_AudioDmaVoice, AUDIO_MAX_PANNING>>1);
	//ASetVoiceFrequency(audio_AudioDmaVoice, audio_info.nSampleRate);

	//audio_AudioDmaWave.nSampleRate		= audio_info.nSampleRate;
	//audio_AudioDmaWave.dwLength		= BUFSIZE;
	//audio_AudioDmaWave.dwLoopStart		= 0;
	//audio_AudioDmaWave.dwLoopEnd		= audio_AudioDmaWave.dwLength;
	//audio_AudioDmaWave.wFormat			= AUDIO_FORMAT_8BITS | AUDIO_FORMAT_MONO;// | AUDIO_FORMAT_LOOP;
	//ACreateAudioData(&audio_AudioDmaWave);
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
//
//
//
//
////////////////////////////////////////////////////////////////////////////////
void audio_done()
{/*
	fprintf(log_get(), "sound: fm voice %i was %s\n", 0, (audio_FmVoicePlaying[0]?"playing":"not playing"));
	fprintf(log_get(), "sound: fm voice %i was %s\n", 1, (audio_FmVoicePlaying[1]?"playing":"not playing"));
	fprintf(log_get(), "sound: noise voice was %s\n", (audio_NoiseVoicePlaying?"playing":"not playing"));
	fprintf(log_get(), "sound: audio dma voice was %s\n", (audio_AudioDmaVoicePlaying?"playing":"not playing"));
*/
	//for (int i = 0;i<2;i++)
	//{
	//	ADestroyAudioData(&audio_FmWave[i]);
	//	ADestroyAudioVoice(audio_FmVoice[i]);
	//}
	//ADestroyAudioData(&audio_NoiseWave);
	//ADestroyAudioVoice(audio_NoiseVoice);
	//ADestroyAudioData(&audio_AudioDmaWave);
	//ADestroyAudioVoice(audio_AudioDmaVoice);
	//ACloseVoices();
 //   ACloseAudio();
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
//
//
//
//
////////////////////////////////////////////////////////////////////////////////
void audio_init()
{
    unsigned short		rc;
	unsigned short		nDevId;

	//fprintf(log_get(),"audio: using seal audio library\n");
 //   /* initialize audio library */
	//AInitialize();

 //   /* show registered device drivers */
 //   fprintf(log_get(),"audio: registered sound devices:\n");
 //   for (nDevId = 0; nDevId < AGetAudioNumDevs(); nDevId++) {
 //       AGetAudioDevCaps(nDevId, &audio_caps);
 //       fprintf(log_get(),"audio:   %2d. %s\n", nDevId, audio_caps.szProductName);
 //   }
 //   /* open audio device */
 //   audio_info.nDeviceId = AUDIO_DEVICE_MAPPER;
 //   audio_info.wFormat   = AUDIO_FORMAT_16BITS | AUDIO_FORMAT_STEREO;//|AUDIO_MIXER_BASS;
 //   audio_info.nSampleRate = 22050;
 //   if ((rc = AOpenAudio(&audio_info)) != AUDIO_ERROR_NONE) 
	//{
 //       CHAR szText[80];
 //       AGetErrorText(rc, szText, sizeof(szText) - 1);
 //       fprintf(log_get(),"audio: error: %s\n", szText);
 //       return;
 //   }
	//
	//AOpenVoices(4);
	//audio_createFmVoices();
	//audio_createNoiseVoice();
	//audio_createAudioDmaVoice();
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
//
//
//
//
//
////////////////////////////////////////////////////////////////////////////////
void sound_init()
{
	//fprintf(log_get(), "sound: init\n");
	//memory_malloc_secure((void**)&sound_buffers[0],  22050*sizeof(short), "Right sound buffer");
	//memory_malloc_secure((void**)&sound_buffers[1],  22050*sizeof(short), "Left sound buffer");
	//
	//memset(sound_buffers[0], 0x00, 22050*sizeof(short));
	//memset(sound_buffers[1], 0x00, 22050*sizeof(short));

	//audio_init();
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
//
//
//
//
//
////////////////////////////////////////////////////////////////////////////////
void sound_reset()
{
	//fprintf(log_get(), "sound: reset\n");
	//memset(sound_regs, 0, 8);
	//memset(sound_channel_size, 0, 2*sizeof(unsigned int));
	//memset(sound_channel_pos,  0, 2*sizeof(unsigned int));
	//memset(audioDma_regs, 0, 8);
	//audio_FmVoicePlaying[0] = true;
	//audio_FmVoicePlaying[1] = true;
	//audio_FmVoicePlay(0, false);
	//audio_FmVoicePlay(1, false);
	//audio_NoiseVoicePlaying = true;
	//audio_NoiseVoicePlay(false);
	//audio_AudioDmaVoicePlaying = true;
	//audio_AudioDmaVoicePlay(false);
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
//
//
//
//
//
////////////////////////////////////////////////////////////////////////////////
void sound_done()
{
	//fprintf(log_get(), "sound: done\n");
	//audio_done();
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
//
//
//
//
//
////////////////////////////////////////////////////////////////////////////////
void sound_audio_dma(unsigned int Addr, unsigned char data)
{
	//// fprintf(log_get(), "sound: writing 0x%2x at 0x%.4x (audio dma voice)\n", data, Addr);
	//
	//audioDma_regs[Addr&0x07] = data;

	//switch (Addr&0x07)
	//{

	//case 0x04: {
	//				if (data&0x80)
	//				{
	//					unsigned int offset = ((unsigned short)audioDma_regs[0])|(((unsigned short)audioDma_regs[1])<<8);
	//					unsigned int length = ((unsigned short)audioDma_regs[2])*32;
	//					audio_AudioDmaSetSample(offset, length, 12000/(1+(audioDma_regs[3]&0x03)), audioDma_regs[3]&(1<<5));
	//					if (Rd6502(0x2026)&0x04)
	//					{
	//						Wr6502(0x2027, Rd6502(0x2027)|0x02);
	//						interrupts_irq();
	//					}
	//					audio_AudioDmaVoicePlay(false);
	//					audio_AudioDmaVoicePlay(true);
	//				}
	//				else
	//					audio_AudioDmaVoicePlay(false);
	//				break;	
	//		   }
	//}
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
//
//
//
//
//
////////////////////////////////////////////////////////////////////////////////
void sound_noise_write(unsigned int Addr, unsigned char data)
{
	// fprintf(log_get(), "sound: writing 0x%2x at 0x%.4x (noise voice)\n", data, Addr);

	//switch (Addr)
	//{
	//case 0:
	//		if ((data&0x07)==0)
	//			audio_NoiseVoicePlay(false);
	//		else
	//		{
	//			audio_NoiseVoiceFreq((22050/16)*(15-((data>>4)&0x0f)), (127*(data&0x0f))/15);
	//			audio_NoiseVoicePlay(true);
	//		}
	//		break;
	//case 2: if ((data&0x10)||((data&0x0c)!=0))
	//			audio_NoiseVoicePlay(true);
	//		else
	//			audio_NoiseVoicePlay(false);
	//}
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
//
//
//
//
//
////////////////////////////////////////////////////////////////////////////////
void sound_write(unsigned int Addr, unsigned char data)
{
	//unsigned int channel = ((Addr&0x4)>>2);
	//Addr&=0x03;
	//sound_regs[channel][Addr] = data;

	// // fprintf(log_get(), "sound: writing 0x%.2x at 0x%.4x (channel %i)\n", data, Addr, channel);
	//switch (Addr) 
	//{
 //   case 0:
	//		// fprintf(log_get(),"sound: channel %i, freq 0x%.2x\n", channel, data);
 //   case 1:
	//case 2: 
	//		if (sound_regs[channel][0]) 
	//		{
	//			unsigned int v1 = sound_regs[channel][0];
	//			unsigned int v2 = sound_regs[channel][1]&0x07;
	//			
	//			unsigned int counter = (v1|(v2<<8));
	//			
	//			audio_FmVoiceFreq(channel, 4000000/(counter*32), sound_regs[channel][2]&0x0f);
	//			audio_FmVoicePlay(channel, true);
	//		}
	//		else 
	//			audio_FmVoicePlay(channel, false);
	//			
	//		sound_channel_pos[channel] = 0;
	//		break;
 //   }
}




////
// sound end







////
// Audio

void supervision_turnSound(bool bOn)
{
	audio_turnSound(bOn);
}

///
// End audio

static unsigned char *Mem=NULL,*MemEnd=NULL;
static unsigned char *RamStart=NULL,*RamEnd=NULL;


static int MemIndex()
{
	unsigned char *Next; Next=Mem;
	cart_rom  =Next;   Next+=0x400000; // game rom	
	RamStart =Next;		
	memorymap_lowerRam=Next;   Next+= 0x2000;
	memorymap_upperRam=Next;   Next+= 0x2000;
	memorymap_regs=Next;   Next+=  0x2000;
	RamEnd   =Next;
	supervision_palette = (unsigned short*)Next; Next += 4 * sizeof(unsigned short);

	MemEnd=Next;
	return 0;
}



/////
// graphics


void gpu_reset(void)
{
	bprintf(1, "gpu: reset\n"); 
	supervision_palette[3] = RGB555(0,0,0);
	supervision_palette[2] = RGB555(10,10,10);
	supervision_palette[1] = RGB555(20,20,20);
	supervision_palette[0] = RGB555(30,30,30);
	memset(gpu_regs, 0, 4);
}

void gpu_write(unsigned int addr, unsigned char data)
{
	gpu_regs[(addr&0x03)] = data;
}

unsigned char gpu_read(unsigned int addr)
{
	return(gpu_regs[(addr&0x03)]);
}


// end graphics

void interrupts_irq()
{
	Int6502(supervision_get6502regs(), INT_IRQ);
}



/// timer 
void timer_reset()
{
	bprintf(1, "timer: reset\n");
	memset(timer_regs, 0, 2);
	timer_cycles = 0;
	timer_activated = false;
}

void timer_write(unsigned int addr, unsigned char data)
{
	//	fprintf(log_get(), "timer: writing 0x%.2x at 0x%.4x\n", data, addr);
	timer_regs[addr&0x01] = data;

	if (addr&0x01)
	{
		timer_cycles = ((unsigned int)data)*256;
		timer_activated = true;
		timer_regs[0]&=0xfe;
	}
}

unsigned char timer_read(unsigned int addr)
{
	return(timer_regs[addr&0x01]);
}

void timer_exec(unsigned int cycles)
{
	if (timer_activated)
	{
		timer_cycles-=cycles;

		if (timer_cycles<0)
		{
			timer_regs[0]|=0x01;
			//			fprintf(log_get(), "timer: irq\n");
			interrupts_irq();
			timer_activated=false;
		}
	}
}


//end timer 


/////
// mem map

unsigned char *memorymap_getRomPointer(void)
{
	return(memorymap_programRom);
}



void memorymap_reset()
{
	bprintf(1, "memorymap: reset\n");
	memorymap_lowerRomBank = memorymap_programRom + 0x0000;
	memorymap_upperRomBank = memorymap_programRom + (memorymap_programRomSize==0x10000?0xc000:0x4000);

	memset(memorymap_lowerRam, 0x00, 0x2000);
	memset(memorymap_upperRam, 0x00, 0x2000);
}

unsigned char  memorymap_registers_read(unsigned int Addr)
{
	switch (Addr&0x1fff)
	{
	case 0x00:
	case 0x01:
	case 0x02:
	case 0x03: return(gpu_read(Addr));
	case 0x20: return(controls_read(Addr));
	case 0x21:  //return(io_read(Addr));
	case 0x23:
	case 0x24: return(timer_read(Addr));
	}
	unsigned char data = memorymap_regs[Addr&0x1fff]; 
	//	fprintf(log_get(), "regs: reading 0x%.2x from 0x%.4x\n", data, Addr);
	return(data);
}

void memorymap_registers_write(unsigned int Addr, unsigned char Value)
{
	memorymap_regs[Addr&0x1fff] = Value;

	switch (Addr&0x1fff)
	{
	case 0x00:
	case 0x01:
	case 0x02:
	case 0x03:  gpu_write(Addr, Value);
		break;
	case 0x22:	///io_write(Addr, Value);
		break;
	case 0x23:
	case 0x24:  timer_write(Addr, Value);
		break;
	case 0x26:
		//fprintf(log_get(), "memorymap: writing 0x%.2x to rom bank register\n", Value);
		memorymap_lowerRomBank = memorymap_programRom + ((((unsigned int)Value) & 0x60) << 9);
		memorymap_upperRomBank = memorymap_programRom + (memorymap_programRomSize==0x10000?0xc000:0x4000); 
		return;
	case 0x27: 	//fprintf(log_get(), "regs: writing 0x%.2x from 0x%.4x\n", Value, Addr);		
		break;
	case 0x10:
	case 0x11:
	case 0x12:	
	case 0x14:
	case 0x15:
	case 0x16:	sound_write(Addr&7, Value); break;
	case 0x28:
	case 0x29:
	case 0x2a:  sound_noise_write(Addr&0x07, Value); break;
	case 0x18:
	case 0x19:
	case 0x1a:
	case 0x1b:
	case 0x1c:  sound_audio_dma(Addr&0x07, Value); break;
	}
}

void Wr6502(register word Addr,register byte Value)
{
	Addr&=0xffff;
	switch (Addr>>12)
	{
	case 0x0:
	case 0x1:	memorymap_lowerRam[Addr] = Value;			return;
	case 0x2:
	case 0x3:	memorymap_registers_write(Addr, Value);	return;
	case 0x4:
	case 0x5:	memorymap_upperRam[Addr&0x1fff] = Value;	return;
	}
}

byte Rd6502(register word Addr)
{	
	Addr&=0xffff;

	switch (Addr>>12)
	{
	case 0x0:
	case 0x1:	return(memorymap_lowerRam[Addr]);
	case 0x2:
	case 0x3:	return(memorymap_registers_read(Addr));
	case 0x4:
	case 0x5:	return(memorymap_upperRam[Addr&0x1fff]);
	case 0x6:
	case 0x7:	return(memorymap_programRom[Addr&0x1fff]);
	case 0x8:
	case 0x9:
	case 0xa:
	case 0xb: 	return(memorymap_lowerRomBank[Addr&0x3fff]);
	case 0xc:
	case 0xd:
	case 0xe:
	case 0xf: 	return(memorymap_upperRomBank[Addr&0x3fff]);
	}
	return(0xff);
}

void memorymap_load(unsigned char *rom, unsigned int size)
{
	memorymap_programRomSize = size;
	memorymap_programRom = rom;

	if (memorymap_programRomSize == 32768)
	{
		unsigned char *tmp = (unsigned char*)malloc(0x10000);
		memcpy(tmp+0x0000, memorymap_programRom, 0x8000);
		memcpy(tmp+0x8000, memorymap_programRom, 0x8000);
		free(memorymap_programRom);
		memorymap_programRom = tmp;
		memorymap_programRomSize = 0x10000;
	}
}

unsigned char *memorymap_getUpperRamPointer(void)
{
	return(memorymap_upperRam);
}



//end memmap

void supervReset()
{
	memorymap_reset();
	gpu_reset();
	timer_reset();
	controls_reset();
	sound_reset();

	Reset6502(&m6502_registers);
}

int supervInit()
{
	int nLen=0;

	Mem=NULL;
	MemIndex();
	nLen=MemEnd-(unsigned char *)0;
	Mem=(unsigned char *)malloc(nLen);
	if (Mem==NULL)
		return 1;
	memset(Mem,0,nLen); // blank all memory
	MemIndex(); // Index the allocated memory

	sound_init();
	struct BurnRomInfo ri;

	BurnDrvGetRomInfo(&ri, 0);
	BurnLoadRom(cart_rom,0,1);

	memorymap_load(cart_rom, ri.nLen);
	supervReset();
	return 0;

}

int supervExit()
{
	free(Mem);
	sound_done();
	return 0;
}

int supervFrame()
{
	if (drvReset)
	{
		supervReset();
	}
	controls_update();

	short *backbuffer = (short *)pBurnDraw;

	for (unsigned int supervision_scanline = 0; supervision_scanline < 160; supervision_scanline++)
	{
		m6502_registers.ICount = 512;
		timer_exec(m6502_registers.ICount);
//		sound_exec(22050/160);
		Run6502(&m6502_registers);
		if (pBurnDraw)
		{
			unsigned char *vram_line = &(memorymap_getUpperRamPointer())[(gpu_regs[2] / 4) + (supervision_scanline*0x30)];
			unsigned int x;

			for (x = 0; x < 160; x += 4)
			{
				unsigned char b = *(vram_line++);
				backbuffer[3] = supervision_palette[((b >> 6) & 0x03)];
				backbuffer[2] = supervision_palette[((b >> 4) & 0x03)];
				backbuffer[1] = supervision_palette[((b >> 2) & 0x03)];
				backbuffer[0] = supervision_palette[((b >> 0) & 0x03)];
				backbuffer += 4;
			}
		}

	}

	if (Rd6502(0x2026)&0x01)
	{
		Int6502(supervision_get6502regs(), INT_NMI);
	}

	return 0;
}


int supervScan(int /*nAction*/,int * /*pnMin*/)
{
	return 0;
}


static struct BurnRomInfo SVAlienRomDesc[]={
	{ "Alien.sv", 65536, 0x8dBB2c53, BRF_PRG }, 
};

STD_ROM_PICK(SVAlien);
STD_ROM_FN(SVAlien);

struct BurnDriver BurnDrvSVAlien = {
	"Alien (199x) (Supervision)", NULL, NULL, "1990",
	"Alien (199x) (Supervision)\0", NULL, "?????", "SuperVision",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 1, HARDWARE_SUPERVISION,
	NULL, SVAlienRomInfo, SVAlienRomName, supervInputInfo, supervDIPInfo,
	supervInit, supervExit, supervFrame, NULL, supervScan,
	NULL, 160, 160, 4, 3
};


static struct BurnRomInfo SVballfgRomDesc[]={
	{ "Bf.sv", 65536, 0x8188b755, BRF_PRG }, 
};

STD_ROM_PICK(SVballfg);
STD_ROM_FN(SVballfg);

struct BurnDriver BurnDrvSVballfg = {
	"Balloon Fight (199x) (Watara)", NULL, NULL, "1990",
	"Balloon Fight (199x) (Watara)\0", NULL, "?????", "SuperVision",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 1, HARDWARE_SUPERVISION,
	NULL, SVballfgRomInfo, SVballfgRomName, supervInputInfo, supervDIPInfo,
	supervInit, supervExit, supervFrame, NULL, supervScan,
	NULL, 160, 160, 4, 3
};
