// File	    : greylize.h
// Author	: Silei
// Descr	: greylize plugin, design plugin gui by wxFormbuilder

#ifndef GREYLIZE_H
#define GREYLIZE_H

#include "plugin.h"
#include "greylizepanebase.h"

class GreylizePane : public GreylizePaneBase, public ImagePluginAgent {

    const static wxString FormatStr;
public:
    GreylizePane(wxWindow *parent, ImagePlugin* plug, wxWindowID id = wxID_ANY);

    void OnApply(wxCommandEvent &event) { RequestImage(); }

    void OnCancel(wxCommandEvent &event) {
        SendImage(origin);
        cancelButton->Disable();
    }

    void OnRedThumbRelease(wxScrollEvent &event);
    void OnGreenThumbRelease(wxScrollEvent &event);
    void OnBlueThumbRelease(wxScrollEvent &event);

    void OnRedCheckChanged(wxCommandEvent &event);
    void OnGreenCheckChanged(wxCommandEvent &event);
    void OnBlueCheckChanged(wxCommandEvent &event);

    void Convert();

private:
    void GetSliderValue(int &r, int &g , int &b, int &max);
    void UpdateValue(int r , int g , int b);
    bool LimitValue(int sum , int &active, int &passive);

private:

    wxImage origin;
};


class GreylizePlugin : public ImagePlugin {

public:
    GreylizePlugin(wxEvtHandler *hdl)
        :ImagePlugin(hdl, _("Greylize")), pane(nullptr) { }

    virtual wxWindow *CreateGUI(wxWindow *parent, wxWindowID id = wxID_ANY) {
        pane = new GreylizePane(parent, this, id);
        return pane;
    }

    virtual wxWindow *GetGUI() const { return pane; }

    virtual void ImageRecived() { pane->Convert(); }

private:
    GreylizePane *pane;
};

#endif //GREYLIZE_H
