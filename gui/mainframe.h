#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "gui.h"

#define APP_NAME        wxT("ImageLab")
#define KEY_CURDIR      wxT("CurrentDir")
#define KEY_PERSPECTIVE wxT("Perspective")

class wxConfig;
class GalleryPane;
class ProgressBar;
class PluginManager;

class MainFrame : public MainFrameBase
{
    enum _IDS {
        ID_GALLERYPANE = wxID_HIGHEST,
        ID_PROGRESSBAR,

    };

public:
    MainFrame(wxWindow *parent, PluginLoader *loader, wxWindowID id = wxID_ANY );

    ~MainFrame(){

    }

private:
    void LoadConfigs();
    void SaveConfigs();
    void InitPanes();
    void InitPlugins();
    void BindEvents();

//============================= Event handler ==================================
public:
    //Main frame:
    void OnCloseFrame(wxCloseEvent &event);
    void OnImagePageChanged(wxAuiNotebookEvent &event);
    //File operation:
    void OnOpenAction(wxCommandEvent &event);
    void OnSaveAction(wxCommandEvent &evnet);
    //View operation:
    void OnOriginSize(wxCommandEvent &event);
    void OnZoomOut(wxCommandEvent &event);
    void OnZoomIn(wxCommandEvent &event);
    void OnFitSize(wxCommandEvent &event);

    //Dir control:
    void OnDirChanged(wxTreeEvent &event);

    //Gallery:
    void OnImageOpen(wxCommandEvent &event);

    //Progress bar:
    void OnProgressStart(wxCommandEvent &event);
    void OnProgressUpdate(wxCommandEvent &event);
    void OnProgressComplete(wxCommandEvent &event);

    //Information bar:
    void OnInfoUpdate(wxCommandEvent &event);

private:
    wxWindow* GetCurrentPluginGUI();

private:
    wxConfig *configs;
    wxString perspective;

    GalleryPane *gallery_pane;
    ProgressBar *progressbar;

    PluginManager plugin_mgr;

    wxString cur_path;
};

#endif // MAINFRAME_H
