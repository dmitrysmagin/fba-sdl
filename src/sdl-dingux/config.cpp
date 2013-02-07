// Burner Config file module
#include "burner.h"
int nIniVersion = 0;

static void CreateConfigName(char* szConfig)
{
#if 0
	memcpy(szConfig, "fbasdl.ini", 12);
#endif
	return;
}

// Read in the config file for the whole application
int ConfigAppLoad()
{
#if 0
	char szConfig[MAX_PATH];
	char szLine[256];
	FILE *h;

	CreateConfigName(szConfig);

	if ((h = fopen(szConfig,"rt")) == NULL) {
		return 1;
	}

	// Go through each line of the config file
	while (fgets(szLine, sizeof(szLine), h)) {
		int nLen;

		nLen = strlen(szLine);

		// Get rid of the linefeed at the end
		if (szLine[nLen - 1] == 10) {
			szLine[nLen - 1] = 0;
			nLen--;
		}

#define VAR(x) { char *szValue = LabelCheck(szLine,#x);		\
  if (szValue) x = strtol(szValue, NULL, 0); }
#define FLT(x) { char *szValue = LabelCheck(szLine,#x);		\
  if (szValue) x = atof(szValue); }
#define STR(x) { char *szValue = LabelCheck(szLine,#x " ");	\
  if (szValue) strcpy(x,szValue); }

		VAR(nIniVersion);
	//	VAR(nVidSelect); // video mode select
		VAR(bBurnUseASMCPUEmulation); // if you have a poor mans PC

		// Other
		STR(szAppRomPaths[0]);
		STR(szAppRomPaths[1]);
		STR(szAppRomPaths[2]);
		STR(szAppRomPaths[3]);
		STR(szAppRomPaths[4]);
		STR(szAppRomPaths[5]);
		STR(szAppRomPaths[6]);
		STR(szAppRomPaths[7]);
#undef STR
#undef FLT
#undef VAR
	}

	fclose(h);
#endif
	return 0;
}

// Write out the config file for the whole application
int ConfigAppSave()
{
#if 0
	char szConfig[MAX_PATH];
	FILE *h;

	CreateConfigName(szConfig);

	if ((h = fopen(szConfig, "wt")) == NULL) {
		return 1;
	}


#define VAR(x) fprintf(h, #x " %d\n", x)
#define FLT(x) fprintf(h, #x " %f\n", x)
#define STR(x) fprintf(h, #x " %s\n", x)

	fprintf(h,"\n// The application version this file was saved from\n");
	// We can't use the macros for this!
	fprintf(h, "nIniVersion 0x%06X", nBurnVer);

	fprintf(h,"\n// video mode 0 = standard SDL 1= (very expiermental) opengl\n");
	//VAR(nVidSelect); // video mode select

	fprintf(h,"\n// use asm cpu cores (i.e. you need to buy a new PC)\n");
	VAR(bBurnUseASMCPUEmulation);

	fprintf(h,"\n// The paths to search for rom zips. (include trailing backslash)\n");
	STR(szAppRomPaths[0]);
	STR(szAppRomPaths[1]);
	STR(szAppRomPaths[2]);
	STR(szAppRomPaths[3]);
	STR(szAppRomPaths[4]);
	STR(szAppRomPaths[5]);
	STR(szAppRomPaths[6]);
	STR(szAppRomPaths[7]);

	fprintf(h,"\n\n\n");

#undef STR
#undef FLT
#undef VAR

	fclose(h);
#endif
	return 0;
}

int ConfigGameLoad()
{
	FILE *f;
	char arg1[128];
	signed long argd;
	char line[256];
	char cfgname[MAX_PATH];

	sprintf((char*)cfgname, "%s/%s.cfg", szAppConfigPath, BurnDrvGetTextA(DRV_NAME));

	if ((f = fopen(cfgname,"r")) == NULL) {
		// set default values and exit
		return 0;
	}

	if (!f) return 0;

	while(fgets(line,sizeof(line),f) != NULL) {
		sscanf(line, "%s %d", &arg1, &argd);

		if (argd > 0) {
			if (strcmp(arg1,"#") != 0) {
				if (strcmp(arg1, "KEY_UP") == 0) config_keymap.up = argd;
				if (strcmp(arg1, "KEY_DOWN") == 0) config_keymap.down = argd;
				if (strcmp(arg1, "KEY_LEFT") == 0) config_keymap.left = argd;
				if (strcmp(arg1, "KEY_COIN1") == 0) config_keymap.coin1 = argd;
				if (strcmp(arg1, "KEY_START1") == 0) config_keymap.start1 = argd;
				if (strcmp(arg1, "KEY_RIGHT") == 0) config_keymap.right = argd;
				if (strcmp(arg1, "KEY_FIRE1") == 0) config_keymap.fire1 = argd;
				if (strcmp(arg1, "KEY_FIRE2") == 0) config_keymap.fire2 = argd;
				if (strcmp(arg1, "KEY_FIRE3") == 0) config_keymap.fire3 = argd;
				if (strcmp(arg1, "KEY_FIRE4") == 0) config_keymap.fire4 = argd;
				if (strcmp(arg1, "KEY_FIRE5") == 0) config_keymap.fire5 = argd;
				if (strcmp(arg1, "KEY_FIRE6") == 0) config_keymap.fire6 = argd;
				if (strcmp(arg1, "KEY_QUIT") == 0) config_keymap.quit = argd;
				if (strcmp(arg1, "KEY_PAUSE") == 0) config_keymap.pause = argd;
			}
		}
	}

	fclose(f);

	return 1;
}

int ConfigGameSave()
{
	FILE *fp;
	char cfgname[MAX_PATH];

	sprintf((char*)cfgname, "%s/%s.cfg", szAppConfigPath, BurnDrvGetTextA(DRV_NAME));
	fp = fopen(cfgname, "w");
	if(!fp) return 0;

	fprintf(fp,"KEY_UP %d\n", config_keymap.up);
	fprintf(fp,"KEY_DOWN %d\n", config_keymap.down);
	fprintf(fp,"KEY_LEFT %d\n", config_keymap.left);
	fprintf(fp,"KEY_RIGHT %d\n", config_keymap.right);
	fprintf(fp,"KEY_COIN1 %d\n", config_keymap.coin1); 
	fprintf(fp,"KEY_START1 %d\n", config_keymap.start1);
	fprintf(fp,"KEY_FIRE1 %d\n", config_keymap.fire1);
	fprintf(fp,"KEY_FIRE2 %d\n", config_keymap.fire2);
	fprintf(fp,"KEY_FIRE3 %d\n", config_keymap.fire3);
	fprintf(fp,"KEY_FIRE4 %d\n", config_keymap.fire4);
	fprintf(fp,"KEY_FIRE5 %d\n", config_keymap.fire5);
	fprintf(fp,"KEY_FIRE6 %d\n", config_keymap.fire6);
	fprintf(fp,"KEY_QUIT %d\n", config_keymap.quit);
	fprintf(fp,"KEY_PAUSE %d\n", config_keymap.pause);
	fclose(fp);
	return 1;
}
