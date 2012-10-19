#include "burnint.h"

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef WIN32
#include <sys/mman.h>
#else

// emulate mmap/munmap on windows, just replace with malloc/free
#define PROT_READ 0
#define MAP_PRIVATE 0 

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
	int fsize;
	char *p;

	fsize = lseek( fd, 0, SEEK_END );
	p = (char *)malloc(fsize);
	if(!p) return (void *)(-1);

	lseek( fd, 0, SEEK_SET );
	read( fd, p, fsize );
	return (void *)p;
}

int munmap(void *addr, size_t length)
{
	if(addr) free(addr);
	return 0;
}

#endif

int bBurnUseRomCache = 0;
static int pBurnCacheFile = 0;

static struct BurnCacheHeader {
	unsigned int ver;		// min fba version
	char name[12];				// ROM Name
	struct BurnCacheBlock {
		unsigned int offset;	// block offset in cache file
		char desc[12];			// describe of this block
	} blocks[15];
} bcHeader;

//static void * blocks_map[14];
static void * BurnCacheBase = 0;
static int BurnCacheSize = 0;

extern char szAppRomPaths[20][20];
void show_rom_loading_text(char * szText, int nSize, int nTotalSize);	// fba_player.cpp

void DisableReadAhead()
{
#ifndef WIN32
	char * value = "0\r";
	int fReadAhead = open("/proc/sys/vm/max-readahead",O_RDWR|O_TRUNC);
	if (fReadAhead)
	{
		write(fReadAhead,value,2);
		close(fReadAhead);
	}
	fReadAhead = open("/proc/sys/vm/min-readahead",O_RDWR|O_TRUNC);
	if (fReadAhead)
	{
		write(fReadAhead,value,2);
		close(fReadAhead);
	}
#endif
}

int BurnCacheInit(const char * cfname, char *rom_name)
{
	pBurnCacheFile = 0;
	BurnCacheBase = 0;
	
	strcpy(szAppRomPaths[0], cfname);
	char * p = strrchr(szAppRomPaths[0], '/');
	if (p) {
		p++;
		strcpy(rom_name, p);
		
		*p = 0;
		p = strrchr(rom_name, '.');
		if (p) {
			
			if ( strcmp( p, ".zip" ) == 0 ) {
				*p = 0;
				return 0;
			} else {
				// cache file 
				pBurnCacheFile = open(cfname, O_RDONLY);
				if ( pBurnCacheFile ) {
					
					lseek( pBurnCacheFile, 0, SEEK_SET );
					read( pBurnCacheFile, &bcHeader, sizeof(bcHeader) );
					strcpy(rom_name, bcHeader.name);
					
					for (int i=0;i<15;i++)
						if ( bcHeader.blocks[i].offset ) 
							BurnCacheSize = bcHeader.blocks[i].offset;
						else break;
					
					//show_rom_loading_text("Cache", 0x100, BurnCacheSize);
					
					BurnCacheBase = mmap(0, BurnCacheSize, PROT_READ, MAP_PRIVATE, pBurnCacheFile, 0);
					if ((int)BurnCacheBase == -1) {
						BurnCacheBase = 0;
						return -3;
					}
					bBurnUseRomCache = 1;
					DisableReadAhead();
					return 0;
					
				} else return -2;
			}
		}
	}
	return -1;
}

unsigned int BurnCacheBlockSize(int blockid)
{
	return  bcHeader.blocks[blockid+1].offset - bcHeader.blocks[blockid].offset;
}

int BurnCacheRead(unsigned char * dst, int blockid)
{
	if ( pBurnCacheFile ) {
		show_rom_loading_text(bcHeader.blocks[blockid].desc, bcHeader.blocks[blockid+1].offset-bcHeader.blocks[blockid].offset, BurnCacheSize);
		lseek( pBurnCacheFile, bcHeader.blocks[blockid].offset, SEEK_SET );
		read( pBurnCacheFile, dst, bcHeader.blocks[blockid+1].offset - bcHeader.blocks[blockid].offset );
		return 0;
	} 
	return 1;
}

void * BurnCacheMap(int blockid)
{
	if ( BurnCacheBase ) {
		if ( (bcHeader.blocks[blockid+1].offset - bcHeader.blocks[blockid].offset) > 0 ) {
			show_rom_loading_text(bcHeader.blocks[blockid].desc, bcHeader.blocks[blockid+1].offset-bcHeader.blocks[blockid].offset, BurnCacheSize);
			return (unsigned char *)BurnCacheBase + bcHeader.blocks[blockid].offset;
		} else return 0;
	} else
		return 0;
}

void BurnCacheExit()
{	
	if ( BurnCacheBase ) {
		munmap( BurnCacheBase, BurnCacheSize );
		BurnCacheBase = 0;
		BurnCacheSize = 0;
	}

	if (pBurnCacheFile) {
		close(pBurnCacheFile);
		pBurnCacheFile = 0;
	}

	bBurnUseRomCache = 0;
}


