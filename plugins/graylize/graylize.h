


#ifndef GRAYLIZE_H
#define GRAYLIZE_H

class wxPanel;
class wxAuiNotebook;
class wxImage;

#include <wx/wx.h>
#include "plugin.h"

class GraylizePlugin;

class GraylizePane : public wxPanel {
    enum _IDS {
        ID_APPLY = wxID_HIGHEST,
        ID_CANCEL,
    };

public:
    GraylizePane(wxWindow *parent, GraylizePlugin *plug, wxWindowID id = wxID_ANY);
    ~GraylizePane();

    void OnApply(wxCommandEvent &event);
    void OnCancel(wxCommandEvent &event);

    void Excute();

private:
    wxImage origin;
    GraylizePlugin *plugin;
};

class GraylizePlugin : public ImagePlugin {

public:
    GraylizePlugin(wxEvtHandler* handler)
        :ImagePlugin(handler),
          pane(nullptr) { }

    virtual wxWindow* GetWindow(wxWindow *parent, wxWindowID id);
    virtual wxString GetPluginName() { return wxString("Graylize"); }
    virtual void ImageRecived();

private:
    GraylizePane *pane;
};

#endif //GRAYLIZE_H
