// File	    : plugmgr.h
// Author	: Silei
// Descr	: plugin related utility

#include <wx/dir.h>
#include <wx/filename.h>
#include <wx/aui/auibook.h>
#include <wx/choicebk.h>
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
    wxDllType hdl = dll_loader.Detach();
    dl_handles.push_back(hdl);
    return true;
}

void PluginLoader::Load() {
    if(CreateThread(wxTHREAD_DETACHED) != wxTHREAD_NO_ERROR) {
        wxLogError("Create plugin loading thread failed!");
        return;
    }

    if(GetThread()->Run() != wxTHREAD_NO_ERROR) {
        wxLogError("Start plugin loading thread failed!");
        return;
    }
}

wxThread::ExitCode PluginLoader::Entry() {
    wxString dll_ext = wxDynamicLibrary::GetDllExt(wxDL_MODULE);
    wxArrayString pathes;
    wxDir::GetAllFiles(plugin_dir, &pathes, "*"+dll_ext);

    if(pathes.size() <= 0)
        return wxThread::ExitCode(0);

    SendStatus(plugmgrEVT_LOADER_START, pathes.size());

    for(size_t i = 0; i < pathes.size(); i++){
        Append(pathes[i]);
        SendStatus(plugmgrEVT_LOADER_PROGRESS, i + 1);
    }

    SendStatus(plugmgrEVT_LOADER_COMPLETE);
    return wxThread::ExitCode(0);
}

void PluginManager::InitPlugin(wxAuiNotebook* image_book){
    if(!loader)
        return;
    for(auto creator : loader->creators) {
        IPlugin* plugin = (creator)(image_book);
        plugins.push_back(plugin);
    }
}

void PluginManager::InitPluginPane(wxAuiNotebook *tool_book)
{
    wxChoicebook* books[PLUG_MAXCATE];
    for(int i = 0; i < PLUG_MAXCATE; i++){
        books[i] = new wxChoicebook(tool_book, wxID_ANY);
        tool_book->AddPage(books[i], PluginCategroyName[i]);
    }

    for(auto plugin : plugins) {
        PluginCategroy cate = plugin->GetCategory();
        wxWindow *gui = plugin->CreateGUI(books[cate]);
        books[cate]->AddPage(gui, plugin->GetName());
    }
}
