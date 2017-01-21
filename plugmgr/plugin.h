// File	    : plugin.h
// Author	: Silei
// Descr	: plugin related utility

#ifndef PLUGIN_H
#define PLUGIN_H

#include <wx/wx.h>

//======================= Image update event =============================
wxDECLARE_EVENT(plugEVT_REQUEST_IMAGE, wxCommandEvent);
wxDECLARE_EVENT(plugEVT_NEW_IMAGE, wxCommandEvent);

class plugImageEvent;
// event carry with image
wxDECLARE_EVENT(plugEVT_IMAGE, plugImageEvent);

class plugImageEvent : public wxCommandEvent {

public:
    plugImageEvent(wxEventType commandType = plugEVT_IMAGE,
                   int id = wxID_ANY)
        :wxCommandEvent(commandType, id){ }

    plugImageEvent(const plugImageEvent& event)
        :wxCommandEvent(event) {
        this->image = event.image;
    }

    wxEvent* Clone() const { return new plugImageEvent(*this); }

    wxImage GetImage() const { return image; }
    void SetImage(const wxImage& image){ this->image = image; }

private:
    wxImage image;
};

typedef void (wxEvtHandler::*plugImageEventFunction)(plugImageEvent&);

#define plugImageEventHandler(func) wxEVENT_HANDLER_CAST(plugImageEventFunction, func)

#define EVT_IMAGE(id, func) \
    wx__DECLARE_EVT1(plugEVT_IMAGE, id, plugImageEventHandler(func))

//================================ Plugin =======================================
class Plugin : public wxEvtHandler {

public:
    virtual wxWindow* CreateGUI(wxWindow *parent, wxWindowID id = wxID_ANY) = 0;
    virtual wxWindow* GetGUI() const = 0;
    virtual void SetParentEvtHandler(wxEvtHandler *handler) = 0;
    virtual wxString GetPluginName() = 0;
};

#ifdef __WIN32__
    #define DEFINE_PLUGIN_CREATOR(name) \
    extern "C" __declspec(dllexport) Plugin* CreatePlugin(wxEvtHandler* handler){ return new name(handler);};
#else
    #define DEFINE_PLUGIN_CREATOR(name) \
    extern "C" Plugin* CreatePlugin(wxEvtHandler* handler){ return new name(handler);};
#endif //__WIN32__

#ifndef PLUGIN_CREATOR
#define PLUGIN_CREATOR
    typedef Plugin* (*PluginCreator)(wxEvtHandler*);
#endif //PLUGIN_CREATOR

//============================= ImagePlugIn =====================================
class ImagePlugin : public Plugin {

public:

    ImagePlugin(wxEvtHandler *hdl = nullptr, const wxString &plug_name = _("ImagePlugin"))
        :name(plug_name), handler(hdl) {

        Bind(plugEVT_IMAGE, &ImagePlugin::OnImageRecived, this);
    }

    virtual wxWindow* CreateGUI(wxWindow *parent, wxWindowID id = wxID_ANY ) = 0;
    virtual void ImageRecived() = 0;
    virtual wxWindow* GetGUI() const = 0;

    virtual void SetParentEvtHandler(wxEvtHandler *hdl){ handler = hdl;}
    virtual wxString GetPluginName(){ return name; }

    wxImage GetImage() const { return image; }
    void SetImage(const wxImage &img);

    void RequestImage();
    void SendImage(const wxImage &image);
    void SendImageByEvent(const wxImage &image);
    void OnImageRecived(plugImageEvent &event);

protected:
    wxString name;

private:
    wxImage image;
    wxEvtHandler *handler;
};

class ImagePluginAgent {

public:
    ImagePluginAgent(ImagePlugin *plug) :plugin(plug){ }

    wxImage GetImage() const { return plugin->GetImage(); }
    void RequestImage() { plugin->RequestImage(); }
    void SendImage(const wxImage &image) { plugin->SendImage(image); }
    void SendImageByEvent( const wxImage &image ) { plugin->SendImageByEvent(image); }

private:
    ImagePlugin *plugin;
};

#endif //PLUGIN_H
