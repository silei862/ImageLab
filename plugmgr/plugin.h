
#ifndef PLUGIN_H
#define PLUGIN_H

#include "wx_pch.h"

enum PluginCategroy {
    PLUG_OTHER = 0,
    PLUG_BASIC,
    PLUG_FILTER,
    PLUG_EDGEDETERCTOR,
};

const static wxString Default_PluginName = wxT("插件");

class IPlugin {
public:
    virtual wxWindow* CreateGUI(wxWindow *parent, wxWindowID id=wxID_ANY) = 0;
    virtual const wxString& GetName() const = 0;
    virtual PluginCategroy GetCategory() const = 0;
};

class wxAuiNotebook;

#ifdef __WIN32__
    #define DEFINE_PLUGIN_CREATOR(name) \
    extern "C" __declspec(dllexport) Plugin* CreatePlugin(wxAuiNotebook *image_book){ return new name(image_book);}
#else
    #define DEFINE_PLUGIN_CREATOR(name) \
    extern "C" Plugin* CreatePlugin(wxAuiNotebook* image_book){ return new name(image_book);}
#endif //__WIN32__

#ifndef PLUGIN_CREATOR
#define PLUGIN_CREATOR
    typedef IPlugin* (*PluginCreator)(wxAuiNotebook*);
#endif //PLUGIN_CREATOR

class Plugin : public IPlugin {

public:
    Plugin(wxAuiNotebook *book, PluginCategroy cate = PLUG_OTHER, const wxString &plug_name = Default_PluginName);
    ~Plugin(){ }

    virtual wxWindow* CreateGUI(wxWindow *parent, wxWindowID id) = 0;

    virtual const wxString& GetName() const { return name; }
    virtual PluginCategroy GetCategory() const { return categroy; }

    wxAuiNotebook* GetImageBook() const { return image_book; }
    wxImage& GetImage() const;
    void SetImage(const wxImage &image);
    void AddImage(const wxImage &image, const wxString &cap);
    wxString GetCurrentPageText();

protected:
    void SetCategory(PluginCategroy cate) { categroy = cate; }
    void SetName(const wxString &plug_name) { name = plug_name; }

private:
    wxAuiNotebook *image_book;
    PluginCategroy categroy;
    wxString name;
};

wxDECLARE_EVENT(plugEVT_PAGE_CHANGED, wxCommandEvent);

class PluginHelper {

public:
    PluginHelper(Plugin *plug) :plugin(plug){ }
    wxImage& GetImage() const { return plugin->GetImage(); }
    void SetImage(const wxImage &image){ plugin->SetImage(image); }
    void AddImage(const wxImage &image, const wxString &cap) { plugin->AddImage(image, cap); }
    wxString GetCurrentPageText() { return plugin->GetCurrentPageText(); }

private:
    Plugin *plugin;
};

#endif //PLUGIN_H
