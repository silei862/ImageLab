
#ifndef CANNY_H
#define CANNY_H

#include <plugin.h>
#include "cannyguibase.h"

class CannyGUI : public CannyGUIBase , public ImagePluginAgent{

public:
    CannyGUI(wxWindow *parent, ImagePlugin *plug, wxWindowID id);

    void OnLowThumbRelease(wxScrollEvent &event);
    void OnRatioThumbRelease(wxScrollEvent &event);
    void OnApply(wxCommandEvent &event){ RequestImage(); }
    void OnCancel(wxCommandEvent &event){
        SendImage(origin);
        cancel_button->Disable();
    }

    void Execute();
private:
    wxImage origin;
};

class CannyPlugin : public ImagePlugin {

public:
    CannyPlugin(wxEvtHandler *hdl)
        :ImagePlugin(hdl, _("Canny Operator")){ }

    virtual wxWindow *CreateGUI(wxWindow *parent, wxWindowID id){
        pane = new CannyGUI(parent, this, id);
        return pane;
    }

    virtual wxWindow *GetGUI() const{ return pane; }

    virtual void ImageRecived(){ pane->Execute(); }

private:
    CannyGUI *pane;
};

DEFINE_PLUGIN_CREATOR(CannyPlugin)

#endif //CANNY_H
