
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef USE_LIBAO
#include <ao/ao.h>

#include "aoaudio.h"

ao_device *ao_dev;
ao_sample_format ao;

int libao_open(int rate, int channels, int format)
{
	ao_initialize();
	ao.bits = format;
	ao.rate = rate;
	ao.channels = channels;
	ao.byte_format = AO_FMT_LITTLE;
	ao.matrix = NULL;
	ao_dev = ao_open_live(ao_default_driver_id(), &ao, NULL);

	if(ao_dev) return 1; else return 0;
}

void libao_close(void)
{
	ao_close(ao_dev);
	ao_shutdown();
}

int libao_play(unsigned char *data, int len)
{
	ao_play(ao_dev, (char *)data, len);
}

void libao_pause(int flag)
{
	; // dummy
}
#endif
