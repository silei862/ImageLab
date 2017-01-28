#include <wx/wx.h>
#include <plugmgr.h>
#include "mainframe.h"

class MainApp : public wxApp {

public:
    bool OnInit();

private:
    PluginLoader loader;
};

wxIMPLEMENT_APP(MainApp);

bool MainApp::OnInit() {
    bool wxsOK = true;
    wxInitAllImageHandlers();

    if (wxsOK) {
        loader.Load(wxGetCwd()+"/plugins");
        loader.Wait();
        MainFrame *frm = new MainFrame(NULL, &loader, wxID_ANY);
        SetTopWindow(frm);
        frm->Show();
    }
    return wxsOK;
}
