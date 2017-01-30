
#ifndef RESIZE_H
#define RESIZE_H

#include <plugin.h>
#include "ResizeGUIBase.h"

class ResizeGui : public ResizeGUIBase, public PluginHelper {

    const static wxImageResizeQuality quality[];

public:
    ResizeGui(wxWindow* parent, Plugin* plug, wxWindowID id = wxID_ANY)
        :ResizeGUIBase(parent, id), PluginHelper(plug)
    {
        Bind(plugEVT_PAGE_CHANGED, &ResizeGui::OnImagePageChanged, this);
    }

    void OnWidthSpinChanged(wxSpinEvent &event);
    void OnHeightSpinChanged(wxSpinEvent &event);
    void OnApply(wxCommandEvent &event);
    void OnImagePageChanged(wxCommandEvent &event) { UpdateSizeValue(); }

private:
    void UpdateSizeValue();

    wxDouble ratio;
};

class ResizePlugin : public Plugin {

public:
    ResizePlugin(wxAuiNotebook *image_book)
        :Plugin(image_book, PLUG_BASIC, wxT("图片尺寸")) { }

    wxWindow* CreateGUI(wxWindow *parent, wxWindowID id) { return new ResizeGui(parent, this, id); }
};

DEFINE_PLUGIN_CREATOR(ResizePlugin)

#endif //RESIZE_H
