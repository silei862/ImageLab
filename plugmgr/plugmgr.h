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
    PluginLoader(wxEvtHandler *evthdlr = nullptr, const wxString &path = wxEmptyString)
        :evt_handler(evthdlr),
          plugin_dir(path){ }

    ~PluginLoader() {
        //Wait loading thread to finish
        if(GetThread() && GetThread()->IsRunning()) {
            GetThread()->Delete();
            while(GetThread() && GetThread()->IsRunning())
                wxThread::This()->Sleep(1);
        }

        for(auto hdl : dl_handles)
            if(hdl)
                wxDynamicLibrary::Unload(hdl);
    }

    void BindEvtHandler(wxEvtHandler *evthdlr) {
        evt_handler = evthdlr;
    }

    void Load();

    void Load(const wxString &path) {
        plugin_dir = path;
        Load();
    }

    void Wait() {
        while(GetThread() && GetThread()->IsRunning())
            wxThread::This()->Sleep(1);
    }

    bool Append(const wxString &path);

    PluginCreator GetPluginCreator(size_t index) const {
        return creators[index];
    }

    PluginCreator operator[](size_t index) const {
        return creators[index];
    }

private:
    void SendStatus(wxEventType type, size_t n = 0) {
        if(evt_handler) {
            wxThreadEvent event(type);
            event.SetExtraLong(n);
            wxQueueEvent(evt_handler, event.Clone());
        }
    }

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

    PluginLoader *GetLoader() const {
        return loader;
    }

    void InitPlugin(wxEvtHandler* handler);

    Plugin* GetPlugin(size_t index) const {
        return plugins[index];
    }

    Plugin* operator[](size_t index) const {
        return plugins[index];
    }

    size_t GetPluginNum() const {
        return plugins.size();
    }

private:
    PluginLoader *loader;
    wxVector<Plugin*> plugins;
};

#endif //PLUGMGR_H
