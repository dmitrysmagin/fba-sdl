#ifndef __BASE_H                // Make sure to only declare these classes once
#define __BASE_H

class MainApp: public wxApp // MainApp is the class for our application
{ // MainApp just acts as a container for the window,
     public: // or frame in MainFrame
          virtual bool OnInit();
		void OnAssert(char const*, int, char const*, char const*);
};

class MainFrame: public wxFrame // MainFrame is the class for our window,
{ // It contains the window and all objects in it
     public:
          MainFrame( const wxString &title, const wxPoint &pos, const wxSize &size );
          wxMenuBar *MainMenu;
	  wxGLCanvas *MyGLCanvas;
          void Quit();
          void OpenFile();
          void CloseFile();
	  void OnIdle(wxIdleEvent& event);
	  void OpenGL_Draw();

          DECLARE_EVENT_TABLE()
};

enum
{
     TEXT_Main = wxID_HIGHEST + 1, // declares an id which will be used to call our button
          MENU_Open,
          MENU_Close,
          MENU_Quit
};

BEGIN_EVENT_TABLE ( MainFrame, wxFrame )
          EVT_MENU(MENU_Open, MainFrame::OpenFile)
          EVT_MENU(MENU_Close, MainFrame::CloseFile)
          EVT_MENU(MENU_Quit, MainFrame::Quit)
	  EVT_IDLE(MainFrame::OnIdle)
END_EVENT_TABLE()
#endif
