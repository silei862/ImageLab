// File	    : mainframe.cpp
// Author	: Silei
// Descr	: MainFrame source

//#include "wx_pch.h"
#include <wx/wx.h>
#include <wx/artprov.h>
#include <wx/filedlg.h>
#include <wx/filename.h>
#include <wx/xrc/xmlres.h>
#include <wx/dir.h>
#include <wx/dynlib.h>

#include "mainframe.h"
#include "imagecanvas.h"
#include "progressbar.h"
#include "plugin.h"
#include "plugmgr.h"

const wxString MainFrame::APP_NAME        = _ ( "ImageLab" );
const wxString MainFrame::KEY_CUR_DIR     = _ ( "CurrentDir" );
const wxString MainFrame::KEY_PERSPECTIVE = _ ( "Perspective" );

MainFrame::MainFrame (wxWindow *parent, PluginLoader *loader, wxWindowID id, const wxString &title,
                       const wxPoint &pos, const wxSize &size, long style,
                       const wxString &name )
    :plugin_mgr(loader),
      wxFrame ( parent, id, title, pos, size, style, name ),
      image_changed ( false ) {

    LoadConfigs();
    InitGUI();
    BindEvtProc();
}

MainFrame::~MainFrame() {
    SaveConfigs();
    mgr.UnInit();
}

inline void MainFrame::InitGUI() {
    //InitMenubar();
    InitToolbar();
    InitPanes();

//--------------Initialize Status Bar--------------------
    CreateStatusBar ( 2 );
    SetStatusText ( _( "Welcome to PiexLab" ), 0 );
    SetStatusText ( _( "Version 0.1" ), 1 );

//--------------Initialize Aui Manager-------------------
    mgr.SetManagedWindow ( this );
    if ( !perspective.IsEmpty() )
        mgr.LoadPerspective ( perspective, false );
    mgr.GetPane ( progress_bar ).Hide();
    mgr.Update();

    SetSize ( wxSize ( MIN_FRM_WIDTH, MIN_FRM_HIGHT ) );
    SetMinSize ( wxSize ( MIN_FRM_WIDTH, MIN_FRM_HIGHT ) );
    Maximize ( true );
    Center();
}

inline void MainFrame::InitMenubar() {
//---------------Menu File-------------------------------
    wxMenu *menu_file = new wxMenu();
    menu_file->Append ( ID_FILEOPEN, _ ( "&Open" ), _ ( "Open a image file" ) );
    menu_file->Append ( ID_FILESAVE, _ ( "&Save" ), _ ( "Save current image file" ) );
    menu_file->AppendSeparator();
    menu_file->Append ( ID_EXIT, _ ( "&Exit" ), _ ( "Exit this program." ) );

//---------------Menu Help-------------------------------
    wxMenu *menu_help = new wxMenu();
    menu_help->Append ( ID_HELP, _ ( "&Help" ),
                      _ ( "Show the help of this program." ) );
    menu_help->AppendSeparator();

//--------------Add all to menubar------------------------
    wxMenuBar *menu_bar = new wxMenuBar();
    menu_bar->Append ( menu_file, _ ( "&File" ) );
    menu_bar->Append ( menu_help, _ ( "&Help" ) );
    SetMenuBar ( menu_bar );
}

inline void MainFrame::InitToolbar() {

//------------- Toolbar View --------------------------------
    wxAuiToolBar *toolbar_view = new wxAuiToolBar ( this, wxID_ANY,
                                                    wxDefaultPosition, wxDefaultSize, wxAUI_TBTOOL_TEXT_BOTTOM );

    toolbar_view->AddTool ( ID_ZOOMOUT, _( "Zoom Out" ),
                            wxArtProvider::GetBitmap ( wxART_GO_UP ),
                            _( "Zoom out the image" ) );

    toolbar_view->AddTool ( ID_ZOOMIN, _( "Zoom In" ),
                            wxArtProvider::GetBitmap ( wxART_GO_DOWN ),
                            _( "Zoom in the image" ) );

    toolbar_view->AddTool ( ID_FITWIN, _( "Fit Window" ),
                            wxArtProvider::GetBitmap ( wxART_GO_HOME ),
                            _( "Fit the window size" ) );
    toolbar_view->Realize();
    mgr.AddPane ( toolbar_view, wxAuiPaneInfo().Name ( "ToolBarView" ).ToolbarPane().Top().Dockable() );

//------------- Toolbar File --------------------------------
    toolbar_file = new wxAuiToolBar ( this, wxID_ANY,
                                      wxDefaultPosition, wxDefaultSize, wxAUI_TBTOOL_TEXT_BOTTOM );

    toolbar_file->AddTool ( ID_FILEOPEN, _ ( "Open" ),
                            wxArtProvider::GetBitmap ( wxART_FILE_OPEN ),
                            _ ( "Open a image file." ) );

    toolbar_file->AddTool ( ID_FILESAVE, _ ( "Save" ),
                            wxArtProvider::GetBitmap ( wxART_FILE_SAVE ),
                            _ ( "Save current image" ) );

    toolbar_file->AddTool ( ID_STOP, _ ( "Stop" ),
                            wxArtProvider::GetBitmap ( wxART_CLOSE ),
                            _ ( "Stop all procedure." ) );
    toolbar_file->EnableTool ( ID_STOP, false );

    toolbar_file->AddTool ( ID_EXIT, _ ( "Exit" ),
                            wxArtProvider::GetBitmap ( wxART_QUIT ),
                            _ ( "Exit this program" ) );

    toolbar_file->AddTool ( ID_HELP, _ ( "Help" ),
                            wxArtProvider::GetBitmap ( wxART_HELP_PAGE ),
                            _ ( "About this program" ) );

    toolbar_file->Realize();
    mgr.AddPane ( toolbar_file, wxAuiPaneInfo().Name ( "ToolBarFile" ).ToolbarPane().Top().Dockable() );
}

inline void MainFrame::InitPanes() {
    imagebook = new wxAuiNotebook(this, wxID_ANY);
    mgr.AddPane(imagebook, wxAuiPaneInfo().Name("Imagebook").CenterPane().Floatable());

    toolbook = new wxChoicebook(this, wxID_ANY);
    wxPanel *about_pane = wxXmlResource::Get()->LoadPanel(toolbook,"AboutPane");
    toolbook->AddPage(about_pane,"About", true);

    //================================== Init Plugin GUIs =============================
    plugin_mgr.InitPlugin(toolbook, ID_HIGHEST);
    for(size_t i = 0; i < plugin_mgr.GetPluginNum(); i++) {
        wxWindow *plugin_gui = plugin_mgr.GetPluginGUI(i);
        toolbook->AddPage(plugin_gui, plugin_mgr[i]->GetPluginName(), true);
    }

    mgr.AddPane(toolbook, wxAuiPaneInfo().Name("Toolbook").Right().CloseButton(false).MinSize(300,600));

    gallery = new Gallery ( this, ID_GALLERY );
    mgr.AddPane ( gallery, wxAuiPaneInfo().Name ( "Gallery" ).Left().CloseButton ( false ).MinSize ( wxSize ( 200,200 ) ) );

    dir_ctrl = new wxGenericDirCtrl ( this, ID_DIRCTRL );
    dir_ctrl->SetWindowStyle ( wxDIRCTRL_DIR_ONLY );
    dir_ctrl->SetPath ( cur_dir );
    mgr.AddPane ( dir_ctrl, wxAuiPaneInfo().Name ( "DirCtrl" ).Left().CloseButton ( false ).MinSize ( wxSize ( 200,300 ) ) );

    progress_bar = new ProgressBar ( this );
    progress_bar->SetValue ( 0.0 );
    mgr.AddPane ( progress_bar, wxAuiPaneInfo().Name ( "ProgressBar" ).Floatable ( false ).CloseButton ( false ).Bottom().MinSize ( 100,30 ) );
}

inline void MainFrame::BindEvtProc() {

    Bind ( wxEVT_COMMAND_TOOL_CLICKED     , &MainFrame::OnExit        , this , ID_EXIT );
    Bind ( wxEVT_COMMAND_TOOL_CLICKED     , &MainFrame::OnHelp        , this , ID_HELP );
    Bind ( wxEVT_COMMAND_TOOL_CLICKED     , &MainFrame::OnFileOpen    , this , ID_FILEOPEN );
    Bind ( wxEVT_COMMAND_TOOL_CLICKED     , &MainFrame::OnFileSave    , this , ID_FILESAVE );
    Bind ( wxEVT_COMMAND_TOOL_CLICKED     , &MainFrame::OnStop        , this , ID_STOP );

    Bind ( wxEVT_COMMAND_TOOL_CLICKED , &MainFrame::OnZoomOut , this , ID_ZOOMOUT );
    Bind ( wxEVT_COMMAND_TOOL_CLICKED , &MainFrame::OnZoomIn  , this , ID_ZOOMIN );
    Bind ( wxEVT_COMMAND_TOOL_CLICKED , &MainFrame::OnFitWin  , this , ID_FITWIN );

    Bind ( wxEVT_DIRCTRL_FILEACTIVATED    , &MainFrame::OnFileActived , this , ID_DIRCTRL );
    Bind ( wxEVT_DIRCTRL_SELECTIONCHANGED , &MainFrame::OnDirChanged  , this , ID_DIRCTRL );

    Bind ( wxEVT_LISTBOX_DCLICK  , &MainFrame::OnImageClicked   , this, ID_GALLERY );

    //progress bar related event:
    Bind ( progrEVT_START, &MainFrame::OnProgressStart, this );
    Bind ( progrEVT_UPDATE, &MainFrame::OnProgressUpdate, this );
    Bind ( progrEVT_COMPLETE, &MainFrame::OnProgressComplete, this );

    Bind ( plugEVT_REQUEST_IMAGE, &MainFrame::OnImageRequest, this);
    Bind ( plugEVT_NEW_IMAGE, &MainFrame::OnImageUpdate, this);
}

inline void MainFrame::LoadConfigs() {
    configs = new wxConfig ( APP_NAME );
    configs->Read ( KEY_CUR_DIR, &cur_dir, wxFileName::GetHomeDir() );
    configs->Read ( KEY_PERSPECTIVE, &perspective, wxEmptyString );
}

inline void MainFrame::SaveConfigs() {
    configs->Write ( KEY_CUR_DIR, cur_dir );
    configs->Write ( KEY_PERSPECTIVE, mgr.SavePerspective() );
    delete configs;
}

void MainFrame::OnHelp ( wxCommandEvent &event ) {
//To-Do: add help dialog ui
}

void MainFrame::OnStop ( wxCommandEvent &event ) {
    gallery->StopLoad();
}

void MainFrame::OnExit ( wxCommandEvent &event ) {
    Close( true );
}

void MainFrame::OnZoomOut ( wxCommandEvent &event ) {
    ImageCanvas *canvas = dynamic_cast<ImageCanvas*>(imagebook->GetCurrentPage());
    if(canvas){
        canvas->ZoomOut();
        canvas->UpdateCanvas();
    }
}

void MainFrame::OnZoomIn ( wxCommandEvent &event ) {
    ImageCanvas *canvas = dynamic_cast<ImageCanvas*>(imagebook->GetCurrentPage());
    if(canvas){
      canvas->ZoomIn();
      canvas->UpdateCanvas();
    }
}

void MainFrame::OnFitWin ( wxCommandEvent &event ) {
    ImageCanvas *canvas = dynamic_cast<ImageCanvas*>(imagebook->GetCurrentPage());
    if(canvas)
        canvas->FitSize();
}

void MainFrame::OnFileOpen ( wxCommandEvent &event ) {
    wxFileDialog fopen_dlg ( this, _ ( "Open a Image" ), cur_dir, wxEmptyString,
                             "Jepg Files(*.jpg;*.jepg)|*.jpg;*.jpeg|PNG Files(*.png)|*.png|BMP Files(*.bmp)|*.bmp",
                             wxFD_OPEN|wxFD_FILE_MUST_EXIST );
    if ( fopen_dlg.ShowModal() == wxID_CANCEL )
        return;

    cur_file = fopen_dlg.GetPath();
    wxImage image ( cur_file );
    if ( image.IsOk() ){
        ImageCanvas *canvas = new ImageCanvas(imagebook);
        imagebook->AddPage(canvas, wxFileName(cur_file).GetName(),true);
        canvas->SetImage(image);
        canvas->FitSize();
        mgr.Update();
    }
    UpdateInfo();
}

void MainFrame::OnFileSave ( wxCommandEvent &event ) {

}

void MainFrame::OnFileActived ( wxTreeEvent &event ) {

}

void MainFrame::OnDirChanged ( wxTreeEvent &event ) {
    gallery->StartLoad ( dir_ctrl->GetPath() );
}

void MainFrame::OnImageClicked ( wxCommandEvent &event ) {
    cur_file = gallery->GetSelectImagePath();
    wxImage image ( cur_file );
    if ( image.IsOk() ){
        ImageCanvas *canvas = new ImageCanvas(imagebook);
        imagebook->AddPage(canvas, wxFileName(cur_file).GetName(),true);
        canvas->SetImage(image);
        canvas->FitSize();
        mgr.Update();
    }
    UpdateInfo ( false );
}

void MainFrame::OnProgressStart(wxCommandEvent &event)
{
    //Adjust main GUI to processing status
    toolbar_file->EnableTool(ID_STOP, true);
    mgr.GetPane(progress_bar).Show();
    mgr.Update();
    //Redirect event
    wxQueueEvent(progress_bar->GetEventHandler(), event.Clone());
}

void MainFrame::OnProgressUpdate(wxCommandEvent &event)
{
    wxQueueEvent(progress_bar->GetEventHandler(), event.Clone());
    SetStatusText ( _( "Caching Preview, Please wait..." ) );
}

void MainFrame::OnProgressComplete(wxCommandEvent &event)
{
    wxQueueEvent(progress_bar->GetEventHandler(), event.Clone());
    //Adjust main GUI to normal status
    toolbar_file->EnableTool(ID_STOP, true);
    mgr.GetPane(progress_bar).Hide();
    mgr.Update();
    SetStatusText ( _( "Caching Complete." ) );
}

void MainFrame::UpdateInfo ( bool update_tree )
{
    wxFileName file_name ( cur_file );
    cur_dir = file_name.GetPath();
    if ( update_tree ) {
        dir_ctrl->ExpandPath ( cur_dir );
        dir_ctrl->SelectPath ( cur_file );
    }
    SetStatusText ( cur_dir, 0 );
    wxString changed = ( image_changed ) ?"*":" ";
    wxString info = wxString::Format ( "%s %s[%s]-%s", file_name.GetFullName(),changed, cur_dir, APP_NAME );
    SetTitle ( info );
}

void MainFrame::OnImageRequest(wxCommandEvent &event) {
    ImageCanvas *canvas = dynamic_cast<ImageCanvas*>(imagebook->GetCurrentPage());
    wxWindow *win = toolbook->GetCurrentPage();
    if(!canvas || !win)
        return;
    ImagePlugin *plug = dynamic_cast<ImagePlugin*>(plugin_mgr[win]);
    if(!plug)
        return;
    wxImage image = canvas->GetImage();
    if(!image.IsOk())
        return;
    plug->SetImage(image);
    wxQueueEvent(plug, new wxCommandEvent(plugEVT_NEW_IMAGE));
}

void MainFrame::OnImageUpdate(wxCommandEvent &event) {
    ImageCanvas *canvas = dynamic_cast<ImageCanvas*>(imagebook->GetCurrentPage());
    wxWindow *win = toolbook->GetCurrentPage();
    if(!canvas || !win)
        return;
    ImagePlugin *plug = dynamic_cast<ImagePlugin*>(plugin_mgr[win]);
    wxImage image = plug->GetImage();
    if(image.IsOk())
        canvas->SetImage(image);
}
