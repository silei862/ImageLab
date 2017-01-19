// File	    : plugmgr.h
// Author	: Silei
// Descr	: plugin related utility

#ifndef PLUGMGR_H
#define PLUGMGR_H

#include <wx/wx.h>
#include <wx/dynlib.h>
#include <wx/thread.h>
#include "plugin.h"

wxDECLARE_EVENT(plugmgrEVT_LOADER_START, wxThreadEvent);
wxDECLARE_EVENT(plugmgrEVT_LOADER_PROGRESS, wxThreadEvent);
wxDECLARE_EVENT(plugmgrEVT_LOADER_COMPLETE, wxThreadEvent);

class PluginManager;

class PluginLoader : public wxThreadHelper {

    friend class PluginManager;
public:
    PluginLoader(wxEvtHandler *evthlr = nullptr, const wxString &path = wxEmptyString)
        :evt_handler(evthlr),
          plugin_dir(path){ }

    ~PluginLoader() {
        for(size_t i = 0; i < dl_handles.size(); i++)
            wxDynamicLibrary::Unload(dl_handles[i]);
    }

    void Load();

    void Load(const wxString &path) {
        plugin_dir = path;
        Load();
    }

    bool Append(const wxString &path);

    PluginCreator GetPluginCreator(size_t index) const {
        return creators[index];
    }

    PluginCreator operator[](size_t index) const {
        return creators[index];
    }

private:
    virtual wxThread::ExitCode Entry();

private:
    wxEvtHandler *evt_handler;
    wxString plugin_dir;
    wxVector<PluginCreator> creators;
    wxVector<wxDllType> dl_handles;
};

class PluginManager {

public:
    PluginManager(PluginLoader *ldr = nullptr)
        :loader(ldr){

    }

    ~PluginManager(){

    }

    void BindLoader(PluginLoader *ldr) {
        loader = ldr;
}

    void InitPlugin(wxEvtHandler* handler);

    Plugin* GetPlugin(size_t index) const {
        return plugins[index];
    }

    Plugin* operator[](size_t index) const {
        return plugins[index];
    }

private:
    PluginLoader *loader;
    wxVector<Plugin*> plugins;
};

#endif //PLUGMGR_H
