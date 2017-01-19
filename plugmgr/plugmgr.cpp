// File	    : plugmgr.h
// Author	: Silei
// Descr	: plugin related utility

#include <wx/dir.h>
#include <wx/filename.h>
#include "plugmgr.h"

wxDEFINE_EVENT(plugmgrEVT_LOADER_START, wxThreadEvent);
wxDEFINE_EVENT(plugmgrEVT_LOADER_PROGRESS, wxThreadEvent);
wxDEFINE_EVENT(plugmgrEVT_LOADER_COMPLETE, wxThreadEvent);


bool PluginLoader::Append(const wxString &path) {
    wxDynamicLibrary dll_loader;
    dll_loader.Load(path);

    if(!dll_loader.IsLoaded())
        return false;

    PluginCreator creator = reinterpret_cast<PluginCreator>(dll_loader.GetSymbol("CreatePlugin"));
    if(!creator) {
        dll_loader.Unload();
        return false;
    }
    //Save key data
    creators.push_back(creator);
    wxDllType dl_handle = dll_loader.Detach();
    dl_handles.push_back(dl_handle);
    return true;
}

void PluginLoader::Load() {
    if(CreateThread() != wxTHREAD_NO_ERROR) {
        wxLogError("Create plugin loading thread failed!");
        return;
    }

    if(GetThread()->Run() != wxTHREAD_NO_ERROR) {
        wxLogError("Start plugin loading thread failed!");
        return;
    }
}

wxThread::ExitCode PluginLoader::Entry() {
   wxArrayString pathes;
  //>>>>>>>>>>>>>>> To-do : complete plugin loading:
}

void PluginManager::InitPlugin(wxEvtHandler *handler){
    if(!loader)
        return;
    for(auto creator : loader->creators) {
        Plugin* plugin = (creator)(handler);
        plugins.push_back(plugin);
    }
}

