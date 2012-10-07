#include "burner.h"
#include "vid_support.h"
#include "vid_softfx.h"

static int nInitedSubsytems = 0;

int nGamesWidth = 0;
int nGamesHeight = 0;			// screen size
unsigned char* texture = NULL;
unsigned char* gamescreen=NULL; 

int nTextureWidth=512;
int nTextureHeight=512;
   
static int nSize;
static int nUseBlitter;

static int nRotateGame = 0;

bool bDoPaint=false;

// Standard callbacks for 16/24/32 bit color:
static unsigned int __cdecl HighCol15GL(int r, int g, int b, int  /* i */)
{
	unsigned int t;
	t =(b<<7)&0x7c00; // 0rrr rr00 0000 0000
	t|=(g<<2)&0x03e0; // 0000 00gg ggg0 0000
	t|=(r>>3)&0x001f; // 0000 0000 000b bbbb
	return t;
}

static unsigned int __cdecl HighCol16GL(int r, int g, int b, int /* i */)
{
	unsigned int t;
	t =(r<<8)&0xf800; // rrrr r000 0000 0000
	t|=(g<<3)&0x07e0; // 0000 0ggg ggg0 0000
	t|=(b>>3)&0x001f; // 0000 0000 000b bbbb
	return t;
}

// 24-bit/32-bit
static unsigned int __cdecl HighCol24GL(int r, int g, int b, int  /* i */)
{
	unsigned int t;
	t =(b<<16)&0xff0000;
	t|=(g<<8 )&0x00ff00;
	t|=(r    )&0x0000ff;

	return t;
}

int SetBurnHighColGL(int nDepth)
{
	VidRecalcPal();

	if (nDepth == 15) {
		VidHighCol = HighCol15GL;
	}
	if (nDepth == 16) {
		VidHighCol = HighCol16GL;
	}
	if (nDepth > 16) {
		VidHighCol = HighCol24GL;
	}
	if (bDrvOkay && !(BurnDrvGetFlags() & BDF_16BIT_ONLY) || nDepth <= 16) {
		BurnHighCol = VidHighCol;
	}

	return 0;
}



static int GetTextureSize(int Size)
{
	int nTextureSize = 128;
	while (nTextureSize < Size) {
		nTextureSize <<= 1;
	}
	return nTextureSize;
}

static int BlitFXInit()
{
	nVidImageWidth = nGamesWidth;
	nVidImageHeight = nGamesHeight;

	nVidImageDepth =16;// bDrvOkay ? 16 : 32;
	nVidImageBPP = (nVidImageDepth + 7) >> 3;
	nBurnBpp = nVidImageBPP;
	printf("%d\n",nBurnBpp);
	SetBurnHighColGL(nVidImageDepth);

	int nMemLen = 0;
	if (!nRotateGame)
	{
		nVidImagePitch = nVidImageWidth * nVidImageBPP;
	}
	else
	{
		nVidImagePitch = nVidImageHeight * nVidImageBPP;
	}
	nMemLen = (nVidImageHeight) * nVidImagePitch;
	gamescreen=(unsigned char*)malloc(nMemLen);
	nBurnPitch=nVidImagePitch;

	texture = (unsigned char*)malloc(nTextureWidth*nTextureHeight*nVidImageBPP);
	
	if (gamescreen) {
		memset(gamescreen, 0, nMemLen);
		pVidImage = gamescreen + nVidImagePitch;
		return 0;
	} else {
		pVidImage = NULL;
		return 1;
	}

	return 0;
}

void init_gl()
{
    	glShadeModel (GL_FLAT);
    	glDisable (GL_POLYGON_SMOOTH);
    	glDisable (GL_LINE_SMOOTH);
    	glDisable (GL_POINT_SMOOTH);
  	glDisable(GL_BLEND); 
	glDisable(GL_DEPTH_TEST);
  	glDepthMask(GL_FALSE);
  	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
  	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  	glTexImage2D(GL_TEXTURE_2D, 0, nVidImageBPP, nTextureWidth, nTextureHeight, 0,GL_RGB, GL_UNSIGNED_BYTE, texture);
	
	glMatrixMode(GL_PROJECTION);
  	glLoadIdentity();
	if (!nRotateGame)
	{
		glRotatef(0.0, 0.0, 0.0, 1.0);
	 	glOrtho(0, nGamesWidth, nGamesHeight, 0, -1,1);
	}
	else
	{
		glRotatef(90.0, 0.0, 0.0, 1.0);
	 	glOrtho(0, nGamesHeight, nGamesWidth, 0, -1,5);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	printf("opengl config done . . . \n");
}


static int Init()
{
	nGamesWidth = nVidImageWidth; 
	nGamesHeight = nVidImageHeight;

	nRotateGame = 0;
	if (bDrvOkay) 
	{
		printf("VidInit + bDrvOkay\n");
		// Get the game screen size
		BurnDrvGetVisibleSize(&nGamesWidth, &nGamesHeight);

	    	if (BurnDrvGetFlags() & BDF_ORIENTATION_VERTICAL) 
		{
			if (nVidRotationAdjust & 1) 
			{
				int n = nGamesWidth;
				nGamesWidth = nGamesHeight;
				nGamesHeight = n;
				nRotateGame |= (nVidRotationAdjust & 2);
			} 
			else 
			{
				nRotateGame |= 1;
			}
		}

		if (BurnDrvGetFlags() & BDF_ORIENTATION_FLIPPED) 
		{
			nRotateGame ^= 2;
		}
	}
	
	if(!nRotateGame)
	{
		nTextureWidth=GetTextureSize(nGamesWidth);
		nTextureHeight=GetTextureSize(nGamesHeight);
	}else
	{	
		nTextureWidth=GetTextureSize(nGamesHeight);
		nTextureHeight=GetTextureSize(nGamesWidth);
	}
	nSize = 2;
	bVidScanlines = 0;

	RECT test_rect;
	test_rect.left=0;
	test_rect.right= nGamesWidth;
	test_rect.top=0;
	test_rect.bottom=nGamesHeight;
	printf("correctx before %d, %d\n",test_rect.right,test_rect.bottom );
	// Initialize the buffer surfaces
	BlitFXInit();
	//Init opengl
	//init_gl();
	return 0;
}

static int Exit()
{
	free(texture);
	free(gamescreen);
	nRotateGame = 0;
	nInitedSubsytems = 0;
	return 0;
}

static int Frame(bool bRedraw)						// bRedraw = 0
{
	if (pVidImage == NULL) {
		return 1;
	}

	if (bDrvOkay) 
	{
		if (bRedraw) 
		{								// Redraw current frame
			if (BurnDrvRedraw()) 
			{
				BurnDrvFrame();						// No redraw function provided, advance one frame
			}
		} 
		else 
		{
			BurnDrvFrame();							// Run one frame and draw the screen
		}
	}
	return 0;
}


static int Paint(int bValidate)
{
	unsigned char* Surf = (unsigned char*)gamescreen;
	int nPitch = nVidImagePitch;
	unsigned char* VidSurf = (unsigned char*)texture;
	int nVidPitch = nTextureWidth*nVidImageBPP;
	
	unsigned char *pd, *ps;
	
	int nHeight = nGamesHeight;
	pd = VidSurf; ps = Surf;
	for (int y = 0; y < nHeight; y++, pd += nVidPitch, ps += nPitch) 
	{
		memcpy(pd, ps, nPitch);
	}
	bDoPaint=true;
	return 0;
}

static int vidScale(RECT* , int, int)
{
	return 0;
}

static int GetSettings(InterfaceInfo* pInfo)
{
	TCHAR szString[MAX_PATH] = _T("");


	return 0;
}

struct VidOut VidOutWXWOpenGL = { Init, Exit, Frame, Paint, vidScale, GetSettings, _T("SDL OpenGL Video output") };
