// File	    : greylize.h
// Author	: Silei
// Descr	: greylize plugin, design plugin gui by wxFormbuilder

#ifndef GREYLIZE_H
#define GREYLIZE_H

#include "plugin.h"
#include "greylizepanebase.h"

class GreylizePane : public GreylizePaneBase, public PluginHelper {

    const static wxString FormatStr;

public:
    GreylizePane(wxWindow *parent, Plugin* plug, wxWindowID id = wxID_ANY);

    void OnApply(wxCommandEvent &event);

    void OnRedScroll(wxScrollEvent &event);
    void OnGreenScroll(wxScrollEvent &event);
    void OnBlueScroll(wxScrollEvent &event);

    void OnRedCheckChanged(wxCommandEvent &event);
    void OnGreenCheckChanged(wxCommandEvent &event);
    void OnBlueCheckChanged(wxCommandEvent &event);

private:
    void GetSliderValue(int &r, int &g , int &b, int &max);
    void UpdateValue(int r , int g , int b);
    bool LimitValue(int sum , int &active, int &passive);
};


class GreylizePlugin : public Plugin {

public:
    GreylizePlugin(wxAuiNotebook *image_book)
        :Plugin(image_book, PLUG_BASIC, wxT("灰度化")) { }

    wxWindow *CreateGUI(wxWindow *parent, wxWindowID id = wxID_ANY) {
        return new GreylizePane(parent, this, id);
    }
};

#endif //GREYLIZE_H
