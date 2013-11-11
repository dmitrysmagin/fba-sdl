/*
 * FinalBurn Alpha for Dingux/OpenDingux
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <getopt.h>

#include "burner.h"
#include "fba_player.h"
#include "snd.h"
#include "sdlvideo.h"

CFG_OPTIONS config_options;
CFG_KEYMAP config_keymap;

int FindDrvByFileName(const char * fn)
{
	char sfn[60] = {0, };
	for (int i=strlen(fn)-1; i>=0; i-- ) {
		if (fn[i] == '/' || fn[i] == '\\' ) {
			strcpy( sfn, fn + i + 1 );
			break;
		}
	}
	if (sfn[0] == 0 ) strcpy( sfn, fn );
	char * p = strrchr( sfn, '.' );
	if (p) *p = 0;

	for (nBurnDrvSelect[0]=0; nBurnDrvSelect[0]<nBurnDrvCount; nBurnDrvSelect[0]++)
		if ( strcasecmp(sfn, BurnDrvGetText(DRV_NAME)) == 0 )
			return nBurnDrvSelect[0];
	nBurnDrvSelect[0] = 0;
	return -1;
}

void parse_cmd(int argc, char *argv[], char *path)
{
	int option_index, c;
	int val;
	char *p;
	printf("num args: %d\n",argc);
	for (c=0;c<argc;c++)
	{
		printf("args %d is %s\n",c,argv[c]);
	}

	static struct option long_opts[] = {
		{"sound-sdl-old", 0, &config_options.option_sound_enable, 3},
		{"sound-sdl", 0, &config_options.option_sound_enable, 2},
		{"sound-ao", 0, &config_options.option_sound_enable, 1},
		{"no-sound", 0, &config_options.option_sound_enable, 0},
		{"samplerate", required_argument, 0, 'r'},
		{"frameskip", required_argument, 0, 'c'},
		{"scaling", required_argument, 0, 'a'},
		{"rotate", required_argument, 0, 'o'},
		{"sense", required_argument, 0, 'd'},
		{"showfps", 0, &config_options.option_showfps, 1},
		{"no-showfps", 0, &config_options.option_showfps, 0},
		{"create-lists", 0, &config_options.option_create_lists, 1},
		{"use-swap", 0, &config_options.option_useswap, 1},
		{"68kcore", required_argument, 0, 's'},
		{"z80core", required_argument, 0, 'z'},
		{"frontend", required_argument, 0, 'f'}
	};

	option_index=optind=0;

	int z2;

	while((c=getopt_long(argc, argv, "", long_opts, &option_index))!=EOF) {
		switch(c) {
			case 'r':
				if(!optarg) continue;
				if(strcmp(optarg, "11025") == 0) config_options.option_samplerate = 0;
				if(strcmp(optarg, "16000") == 0) config_options.option_samplerate = 1;
				if(strcmp(optarg, "22050") == 0) config_options.option_samplerate = 2;
				if(strcmp(optarg, "32000") == 0) config_options.option_samplerate = 3;
				if(strcmp(optarg, "44100") == 0) config_options.option_samplerate = 4;
				break;
			case 'c':
				if(!optarg) continue;
				if(strcmp(optarg, "auto") == 0) config_options.option_frameskip = -1;
				else {
					z2=0;
					sscanf(optarg,"%d",&z2);
					if ((z2>60) || (z2<0)) z2=0;
					config_options.option_frameskip = z2;
				}
				break;
			case 's':
				if(!optarg) continue;
				z2=0;
				sscanf(optarg,"%d",&z2);
				if ((z2>2) || (z2<0)) z2=0;
				config_options.option_68kcore = z2;
				break;
			case 'z':
				if(!optarg) continue;
				z2=0;
				sscanf(optarg,"%d",&z2);
				if ((z2>2) || (z2<0)) z2=0;
				config_options.option_z80core = z2;
				break;
			case 'a':
				if(!optarg) continue;
				z2=0;
				sscanf(optarg,"%d",&z2);
				if ((z2>3) || (z2<0)) z2=0;
				config_options.option_rescale = z2;
				break;
			case 'o':
				if(!optarg) continue;
				z2=0;
				sscanf(optarg,"%d",&z2);
				if ((z2>2) || (z2<0)) z2=0;
				config_options.option_rotate = z2;
				break;
			case 'd':
				if(!optarg) continue;
				z2=0;
				sscanf(optarg,"%d",&z2);
				if ((z2>100) || (z2<10)) z2=100;
				config_options.option_sense = z2;
				break;
			case 'f':
				if(!optarg) continue;
				p = strrchr(optarg, '/');
				if(p == NULL)
					sprintf(config_options.option_frontend, "%s%s", "./", optarg);
				else
					strcpy(config_options.option_frontend, optarg);
				break;
		}
	}

	if(optind < argc) {
		strcpy(path, argv[optind]);
	}
}

/*
 * application main()
 */
#undef main
int main(int argc, char **argv )
{
	char path[MAX_PATH];

	if (argc < 2)
	{
		int c;
		printf ("Usage: %s <path to rom><shortname>.zip\n   ie: %s ./uopoko.zip\n Note: Path and .zip extension are mandatory.\n\n",argv[0], argv[0]);
		printf ("Supported (but not necessarily working via fba-gp2x) roms:\n\n");

		BurnLibInit();
		for (nBurnDrvSelect[0]=0; nBurnDrvSelect[0]<nBurnDrvCount; nBurnDrvSelect[0]++)
		{
			nBurnDrvActive=nBurnDrvSelect[0];
			printf ("%-20s ", BurnDrvGetTextA(DRV_NAME)); c++;
			if (c == 3)
			{
				c = 0;
				printf ("\n");
			}
		}
		printf ("\n\n");
		CreateCapexLists(); // generate rominfo.fba and zipname.fba
		return 0;
	}

	//Initialize configuration options
	config_options.option_sound_enable = 2;
	config_options.option_rescale = 0; // no scaling by default
	config_options.option_rotate = 0;
	config_options.option_samplerate = 3; // 0 - 11025, 1 - 16000, 2 - 22050, 3 - 32000
	config_options.option_showfps = 0;
	config_options.option_frameskip = -1; // auto frameskip by default
	config_options.option_create_lists=0;
	config_options.option_68kcore=1; // 0 - c68k, 1 - m68k, 2 - a68k
	config_options.option_z80core=0;
	config_options.option_sense=100;
	config_options.option_useswap=0; // use internal swap for legacy dingux
	#ifdef WIN32
	strcpy(config_options.option_frontend, "./fbacapex.exe");
	#else
	strcpy(config_options.option_frontend, "./fbacapex.dge");
	#endif
	printf("about to parse cmd\n");
	parse_cmd(argc, argv,path);
	printf("finished parsing\n");

	config_keymap.up=SDLK_UP;
	config_keymap.down=SDLK_DOWN;
	config_keymap.left=SDLK_LEFT;
	config_keymap.right=SDLK_RIGHT;
	config_keymap.fire1=SDLK_LCTRL;		// A
	config_keymap.fire2=SDLK_LALT;		// B
	config_keymap.fire3=SDLK_SPACE;		// X
	config_keymap.fire4=SDLK_LSHIFT;	// Y
	config_keymap.fire5=SDLK_TAB;		// L
	config_keymap.fire6=SDLK_BACKSPACE;	// R
	config_keymap.coin1=SDLK_ESCAPE;	// SELECT
	config_keymap.start1=SDLK_RETURN;	// START
	config_keymap.pause=SDLK_p;
	config_keymap.quit=SDLK_q;
	config_keymap.qsave=SDLK_s;      // quick save
	config_keymap.qload=SDLK_l;      // quick load

	extern int nSekCpuCore; // 0 - c68k, 1 - m68k, 2 - a68k
	nSekCpuCore = config_options.option_68kcore;

	bForce60Hz = true;

	// Run emu loop
	run_fba_emulator (path);

	return 0;
}


TCHAR* ANSIToTCHAR(const char* pszInString, TCHAR* pszOutString, int nOutSize)
{
#if defined (UNICODE)
	static TCHAR szStringBuffer[1024];

	TCHAR* pszBuffer = pszOutString ? pszOutString : szStringBuffer;
	int nBufferSize  = pszOutString ? nOutSize * 2 : sizeof(szStringBuffer);

	if (MultiByteToWideChar(CP_ACP, 0, pszInString, -1, pszBuffer, nBufferSize)) {
		return pszBuffer;
	}

	return NULL;
#else
	if (pszOutString) {
		_tcscpy(pszOutString, pszInString);
		return pszOutString;
	}

	return (TCHAR*)pszInString;
#endif
}


char* TCHARToANSI(const TCHAR* pszInString, char* pszOutString, int nOutSize)
{
#if defined (UNICODE)
	static char szStringBuffer[1024];
	memset(szStringBuffer, 0, sizeof(szStringBuffer));

	char* pszBuffer = pszOutString ? pszOutString : szStringBuffer;
	int nBufferSize = pszOutString ? nOutSize * 2 : sizeof(szStringBuffer);

	if (WideCharToMultiByte(CP_ACP, 0, pszInString, -1, pszBuffer, nBufferSize, NULL, NULL)) {
		return pszBuffer;
	}

	return NULL;
#else
	if (pszOutString) {
		strcpy(pszOutString, pszInString);
		return pszOutString;
	}

	return (char*)pszInString;
#endif
}
