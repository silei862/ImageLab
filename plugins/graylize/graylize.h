// File	    : graylize.h
// Author	: Silei
// Descr	: graylize plugin

#ifndef GRAYLIZE_H
#define GRAYLIZE_H

class wxPanel;
class wxAuiNotebook;
class wxImage;

#include <wx/wx.h>
#include "plugin.h"

class GraylizePlugin;

class GraylizePane : public PluginGUI {
    enum _IDS {
        ID_APPLY = wxID_HIGHEST,
        ID_CANCEL,
    };

public:
    GraylizePane(wxWindow *parent, ImagePlugin *plug, wxWindowID id = wxID_ANY);
    ~GraylizePane();

    void OnApply(wxCommandEvent &event);
    void OnCancel(wxCommandEvent &event);

    void Excute();

private:
    wxCheckBox *grey_eq;
    wxImage origin;
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
