#include "burner.h"
#include "wxbase.h"

int nAppVirtualFps = 6000;			// App fps * 100
bool bRunPause=0;
bool bAlwaysProcessKeyboardInput=0;
//#define frame_timer
#ifdef frame_timer
#include <sys/time.h>
#endif

/* const */ TCHAR* ANSIToTCHAR(const char* pszInString, TCHAR* pszOutString, int nOutSize)
{
#if defined (UNICODE)
	static TCHAR szStringBuffer[1024];

	TCHAR* pszBuffer = pszOutString ? 	ConfigAppLoad(); pszOutString : szStringBuffer;
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


/* const */ char* TCHARToANSI(const TCHAR* pszInString, char* pszOutString, int nOutSize)
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


IMPLEMENT_APP(MainApp) // Initializes the MainApp class and tells our program to run it

bool MainApp::OnInit()
{
	MainFrame *MainWin = new MainFrame("FB Alpha/wx", wxPoint(1,1),wxSize(640, 480)); 
	MainWin->Show(TRUE); 
	return TRUE;
}

void MainApp::OnAssert(char const*, int, char const*, char const*)
{

}


MainFrame::MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
     : wxFrame((wxFrame *) NULL, -1, title, pos, size)
{
	nInterpolation=0;
	///int attribList[15];
     	CreateStatusBar(2);
     	MainMenu = new wxMenuBar();
     	wxMenu *FileMenu = new wxMenu();

     	FileMenu->Append(MENU_Open, "&Open", "Open an existing file");
     	FileMenu->Append(MENU_Close, "&Close", "Close the current document");
     	FileMenu->Append(MENU_Quit, "&Quit", "Quit the editor");

     	MainMenu->Append(FileMenu, "File");
     	SetMenuBar(MainMenu);
/*	attribList[0]=WX_GL_RGBA; // colour bits
	attribList[0]=1;
	attribList[2]=WX_GL_DEPTH_SIZE;
	attribList[3]=1;
	attribList[4]=WX_GL_STENCIL_SIZE;
	attribList[5]=1;
	attribList[6]=WX_GL_MIN_RED;
	attribList[7]=5;
	attribList[8]=WX_GL_MIN_GREEN;
	attribList[9]=5;
	attribList[10]=WX_GL_MIN_BLUE;
	attribList[11]=5;
	attribList[10]=WX_GL_MIN_ALPHA;
	attribList[11]=0;
	attribList[12]=WX_GL_DOUBLEBUFFER; // enable double buffer
   */
  int gl_attrib[20] = { WX_GL_RGBA, WX_GL_MIN_RED, 1, WX_GL_MIN_GREEN, 1,
            WX_GL_MIN_BLUE, 1, WX_GL_DEPTH_SIZE, 1,
            WX_GL_DOUBLEBUFFER, 0 };

	MyGLCanvas = new wxGLCanvas(this, -1, wxPoint(0,0), wxSize(640,480),0, _("some text"), gl_attrib);
	MyGLCanvas->SetCurrent();
	glShadeModel (GL_FLAT);
    	glDisable (GL_POLYGON_SMOOTH);
    	glDisable (GL_LINE_SMOOTH);
    	glDisable (GL_POINT_SMOOTH);
  	glDisable(GL_BLEND); 
	glDisable(GL_DEPTH_TEST);
  	glDepthMask(GL_FALSE);
  	glDisable(GL_CULL_FACE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glRotatef(0.0, 0.0, 0.0, 1.0);
	glOrtho(0, nGamesWidth, nGamesHeight, 0, -1,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

  	MyGLCanvas->SwapBuffers();
	printf( "Vendor     : %s\n", glGetString( GL_VENDOR ) );
	printf( "Renderer   : %s\n", glGetString( GL_RENDERER ) );
	printf( "Version    : %s\n", glGetString( GL_VERSION ) );
	printf( "Extensions : %s\n", glGetString( GL_EXTENSIONS ) );
	SDL_Init(SDL_INIT_TIMER);
	ConfigAppLoad(); 
	BurnLibInit(); 
}

void MainFrame::OpenFile()
{
	RunStart(7);
}

void MainFrame::CloseFile()
{
	RunExit();
	ConfigAppSave();
}

void MainFrame::OpenGL_Draw()
{
    	MyGLCanvas->SetCurrent();
	// wxWidget docs mention a possible race condition if you do not give up some cycles between SetCurrent() and SwapBuffers(). 
	// one way is to do this:
	wxSafeYield();
#ifdef frame_timer
	timeval start , end;
        time_t sec;
        suseconds_t usec;
	gettimeofday(&start,NULL); 
#endif
	glShadeModel (GL_FLAT);
    	glDisable (GL_POLYGON_SMOOTH);
    	glDisable (GL_LINE_SMOOTH);
    	glDisable (GL_POINT_SMOOTH);
  	glDisable(GL_BLEND); 
	glDisable(GL_DEPTH_TEST);
  	glDepthMask(GL_FALSE);
  	glDisable(GL_CULL_FACE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glRotatef(0.0, 0.0, 0.0, 1.0);
	glOrtho(0, nGamesWidth, nGamesHeight, 0, -1,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
  	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  	glTexImage2D(GL_TEXTURE_2D, 0,3 , nTextureWidth, nTextureHeight, 0,GL_RGB, GL_UNSIGNED_SHORT_5_6_5, texture);
   
/*	glBegin(GL_QUADS);
    	glTexCoord2f(0,0);
	glVertex2i(0,0);
    	glTexCoord2f(0,1);
	glVertex2i(0,nTextureHeight);
	glTexCoord2f(1,1);
	glVertex2i(nTextureWidth,nTextureHeight);
	glTexCoord2f(1,0);
	glVertex2i(nTextureWidth,0);
*/
  	glBegin(GL_POLYGON);
    	glTexCoord2f(0,0);
	glVertex2i(0,0);
    	glTexCoord2f(0,1);
	glVertex2i(0,nTextureHeight);
	glTexCoord2f(1,1);
	glVertex2i(nTextureWidth,nTextureHeight);
	glTexCoord2f(1,0);
	glVertex2i(nTextureWidth,0);
  	glEnd();
	glFinish();
  	MyGLCanvas->SwapBuffers();
#ifdef frame_timer
	gettimeofday(&end,NULL);
        sec  = end.tv_sec  - start.tv_sec;
        usec = end.tv_usec - start.tv_usec;
        if(usec < 0){
                usec += 1000000;
                sec--;
        }
	printf("Elapsed time : %ld.%ld\n", sec, usec);
	#endif

}

void MainFrame::Quit()
{
	RunExit();
	ConfigAppSave();
	BurnLibExit();
     	Close(TRUE);     // Tells the OS to quit running this process
}

void MainFrame::OnIdle(wxIdleEvent& event)	{
	RunIdle(); // emulate a frame
	if (bDrvOkay&&bDoPaint) 
	{
		OpenGL_Draw();  // draw the frame
		bDoPaint=false;
	}
	event.RequestMore();
}

