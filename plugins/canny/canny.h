// File	    : canny.h
// Author	: Silei
// Descr	: canny plugin, design plugin gui by wxFormbuilder

#ifndef CANNY_H
#define CANNY_H

#include <plugin.h>
#include "cannyguibase.h"

class CannyGUI : public CannyGUIBase , public PluginHelper{

public:
    CannyGUI(wxWindow *parent, Plugin *plug, wxWindowID id);

    void OnLowScroll(wxScrollEvent &event);
    void OnRatioScroll(wxScrollEvent &event);
    void OnApply(wxCommandEvent &event);
};

class CannyPlugin : public Plugin {

public:
    CannyPlugin(wxAuiNotebook *img_book)
        :Plugin(img_book, PLUG_EDGEDETERCTOR, wxT("Canny边缘检测")){ }

    virtual wxWindow *CreateGUI(wxWindow *parent, wxWindowID id){
        return new CannyGUI(parent, this, id);
    }
};

DEFINE_PLUGIN_CREATOR(CannyPlugin)

#endif //CANNY_H
