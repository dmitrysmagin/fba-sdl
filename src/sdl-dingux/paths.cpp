
// Paths module
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include "burner.h"

char szAppHomePath[MAX_PATH] = "./.fba";			// ~/.fba
char szAppSavePath[MAX_PATH] = "./.fba/saves";		// ~/.fba/saves
char szAppHiscorePath[MAX_PATH] = "./.fba/hiscore";	// ~/.fba/hiscore depends on src/burn/hiscore.cpp
char szAppSamplesPath[MAX_PATH] = "./.fba/samples";	// ~/.fba/samples depends on src/burn/snd/samples.cpp
char szAppIpsPath[MAX_PATH] = "./.fba/ips";			// ~/.fba/ips depends on src/sdl-dingux/ips_manager.cpp

void BurnPathsInit()
{
#ifndef WIN32
	char *home = getenv("HOME");
	if(home) sprintf(szAppHomePath, "%s/.fba", home);
	mkdir(szAppHomePath, 0777);
	if(!errno) {
		getcwd(szAppHomePath, MAX_PATH);
		strcat(szAppHomePath, "/.fba");
		mkdir(szAppHomePath, 0777);
	}

	sprintf(szAppSavePath, "%s/saves", szAppHomePath);
	mkdir(szAppSavePath, 0777);
#else
	getcwd(szAppHomePath, MAX_PATH);
	strcat(szAppHomePath, "/.fba");
	mkdir(szAppHomePath);

	sprintf(szAppSavePath, "%s/saves", szAppHomePath);
	mkdir(szAppSavePath);
#endif
}
