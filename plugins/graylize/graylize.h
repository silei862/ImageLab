// File	    : graylize.h
// Author	: Silei
// Descr	: graylize plugin

#ifndef GRAYLIZE_H
#define GRAYLIZE_H

#include <wx/wx.h>
#include "plugin.h"

class GraylizeGUI : public wxWindow, public ImagePluginAgent {
    enum _IDS {
        ID_APPLY = wxID_HIGHEST,
        ID_CANCEL,
    };

public:
    GraylizeGUI(wxWindow *parent, ImagePlugin *plug, wxWindowID id = wxID_ANY);
    ~GraylizeGUI();

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
        :ImagePlugin(handler, _("Graylize")), gui(nullptr){  }

    virtual wxWindow *CreateGUI(wxWindow *parent, wxWindowID id = wxID_ANY) {
        gui = new GraylizeGUI(parent, this, id);
        return gui;
    }
    virtual wxWindow *GetGUI() const { return gui; }
    virtual void ImageRecived() { gui->Excute(); }

private:
    GraylizeGUI *gui;
};

#endif //GRAYLIZE_H
