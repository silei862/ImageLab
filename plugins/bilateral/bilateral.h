
#ifndef BILATERAL_H
#define BILATERAL_H

#include <plugin.h>
#include "bilateralGUI.h"
#include <wx/valnum.h>

class BilateralPane : public BilateralBase, PluginHelper {

public:
    BilateralPane(wxWindow *parent, Plugin *plug, wxWindowID id = wxID_ANY);

    void OnApply(wxCommandEvent &event);

private:
    double color_sigma;
    wxFloatingPointValidator<double> colorsigma_vali;
    double space_sigma;
    wxFloatingPointValidator<double> spacesigma_vali;
};

class BilateralPlugin : public Plugin {

public:
    BilateralPlugin(wxAuiNotebook *img_book)
        :Plugin(img_book, PLUG_FILTER, wxT("双边滤波器")){ }

    wxWindow* CreateGUI(wxWindow *parent, wxWindowID id) { return new BilateralPane(parent, this, id); }

};

DEFINE_PLUGIN_CREATOR(BilateralPlugin)

#endif //BILATERAL_H
