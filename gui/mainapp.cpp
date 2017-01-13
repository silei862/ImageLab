// File		: mainapp.cpp
// Author	: Silei
// Descr	: mainprogram entry

//#include "wx_pch.h"
#include <wx/wx.h>
#include "mainframe.h"

class MainApp : public wxApp
{

public:
  bool OnInit();
};

wxIMPLEMENT_APP ( MainApp );

bool MainApp::OnInit()
{
  bool wxsOK = true;
  wxInitAllImageHandlers();
  if ( wxsOK )
    {
      MainFrame* frm = new MainFrame ( NULL, wxID_ANY, _ ( "Image Lab" ) );
      SetTopWindow ( frm );
      frm->Show();
    }
  return wxsOK;
}
