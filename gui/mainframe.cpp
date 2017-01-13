// File	: mainframe.cpp
// Author	: silei
// Descr	: MainFrame source

//#include "wx_pch.h"
#include <wx/wx.h>
#include <wx/artprov.h>
#include <wx/filedlg.h>
#include <wx/filename.h>
#include <wx/dir.h>

#include "mainframe.h"
#include "imagecanvas.h"
#include "progressbar.h"
#include "utility.h"

const wxString MainFrame::APP_NAME        = _ ( "ImageLab" );
const wxString MainFrame::KEY_CUR_DIR     = _ ( "CurrentDir" );
const wxString MainFrame::KEY_PERSPECTIVE = _ ( "Perspective" );

MainFrame::MainFrame ( wxWindow *parent, wxWindowID id, const wxString &title,
                       const wxPoint &pos, const wxSize &size, long style,
                       const wxString &name )
  :wxFrame ( parent, id, title, pos, size, style, name ),
   image_changed ( false )
{

  LoadConfigs();
  InitGUI();
  BindEvtProc();
}

MainFrame::~MainFrame()
{
  SaveConfigs();
  mgr.UnInit();
}

inline void MainFrame::InitGUI()
{
  //InitMenubar();
  InitToolbar();
  InitPanes();

//--------------Initialize Status Bar--------------------
  CreateStatusBar ( 2 );
  SetStatusText ( _ ( "Welcome to PiexLab" ), 0 );
  SetStatusText ( _ ( "Version 0.1" ), 1 );

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

inline void MainFrame::InitMenubar()
{

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

inline void MainFrame::InitToolbar()
{
//------------- Toolbar Processor ---------------------------
    wxAuiToolBar *toolbar_proc = new wxAuiToolBar(this, wxID_ANY,
                                                  wxDefaultPosition, wxDefaultSize, wxAUI_TBTOOL_TEXT_BOTTOM);
    toolbar_proc->AddTool( ID_GRAYLIZE, _("Graylize"),
                           wxArtProvider::GetBitmap(wxART_HELP),
                           _("Make the Image Gray"));

    toolbar_proc->Realize();
    mgr.AddPane(toolbar_proc, wxAuiPaneInfo().Name("ToolBarImageProc").ToolbarPane().Top().Dockable());

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

inline void MainFrame::InitPanes()
{
  notebook = new wxAuiNotebook(this, wxID_ANY);
  mgr.AddPane(notebook, wxAuiPaneInfo().Name("Notebook").CenterPane().CloseButton(false).PaneBorder(false));

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

inline void MainFrame::BindEvtProc()
{
  Bind ( wxEVT_COMMAND_TOOL_CLICKED     , &MainFrame::OnExit        , this , ID_EXIT );
  Bind ( wxEVT_COMMAND_TOOL_CLICKED     , &MainFrame::OnHelp        , this , ID_HELP );
  Bind ( wxEVT_COMMAND_TOOL_CLICKED     , &MainFrame::OnFileOpen    , this , ID_FILEOPEN );
  Bind ( wxEVT_COMMAND_TOOL_CLICKED     , &MainFrame::OnFileSave    , this , ID_FILESAVE );
  Bind ( wxEVT_COMMAND_TOOL_CLICKED     , &MainFrame::OnStop        , this , ID_STOP );

  Bind ( wxEVT_COMMAND_TOOL_CLICKED , &MainFrame::OnZoomOut , this , ID_ZOOMOUT );
  Bind ( wxEVT_COMMAND_TOOL_CLICKED , &MainFrame::OnZoomIn  , this , ID_ZOOMIN );
  Bind ( wxEVT_COMMAND_TOOL_CLICKED , &MainFrame::OnFitWin  , this , ID_FITWIN );

  Bind (wxEVT_COMMAND_TOOL_CLICKED , &MainFrame::OnGraylize, this , ID_GRAYLIZE);

  Bind ( wxEVT_DIRCTRL_FILEACTIVATED    , &MainFrame::OnFileActived , this , ID_DIRCTRL );
  Bind ( wxEVT_DIRCTRL_SELECTIONCHANGED , &MainFrame::OnDirChanged, this, ID_DIRCTRL );

  Bind ( wxEVT_LISTBOX_DCLICK, &MainFrame::OnImageClicked, this, ID_GALLERY );
  Bind ( pxEVT_GALLERY_PROGRESS, &MainFrame::OnGalleryProgress, this, ID_GALLERY );
  Bind ( pxEVT_GALLERY_COMPLETE, &MainFrame::OnGalleryComplete, this, ID_GALLERY );
}

inline void MainFrame::LoadConfigs()
{
  configs = new wxConfig ( APP_NAME );
  configs->Read ( KEY_CUR_DIR, &cur_dir, wxFileName::GetHomeDir() );
  configs->Read ( KEY_PERSPECTIVE, &perspective, wxEmptyString );
}

inline void MainFrame::SaveConfigs()
{
  configs->Write ( KEY_CUR_DIR, cur_dir );
  configs->Write ( KEY_PERSPECTIVE, mgr.SavePerspective() );
  delete configs;
}

void MainFrame::OnHelp ( wxCommandEvent &event )
{
//To-Do: add help dialog ui
}

void MainFrame::OnStop ( wxCommandEvent &event )
{
  gallery->StopLoad();
}

void MainFrame::OnExit ( wxCommandEvent &event )
{
  Close ( true );
}

void MainFrame::OnZoomOut ( wxCommandEvent &event )
{
  ImageCanvas *canvas = reinterpret_cast<ImageCanvas*>(notebook->GetCurrentPage());
  if(canvas){
    canvas->ZoomOut();
    canvas->UpdateCanvas();
  }
}

void MainFrame::OnZoomIn ( wxCommandEvent &event )
{
  ImageCanvas *canvas = reinterpret_cast<ImageCanvas*>(notebook->GetCurrentPage());
  if(canvas){
    canvas->ZoomIn();
    canvas->UpdateCanvas();
  }
}

void MainFrame::OnFitWin ( wxCommandEvent &event )
{
  ImageCanvas *canvas = reinterpret_cast<ImageCanvas*>(notebook->GetCurrentPage());
  if(canvas)
    canvas->FitSize();

}

void MainFrame::OnGraylize(wxCommandEvent &event){
    ImageCanvas *canvas = reinterpret_cast<ImageCanvas*>(notebook->GetCurrentPage());
    if(!canvas)
        return;
    wxImage image = canvas->GetImage();
    int page_index = notebook->GetPageIndex(canvas);
    wxString title = notebook->GetPageText(page_index);
    if(image.IsOk()) {
        image = GrayLize(image);
        ImageCanvas *result_canvas = new ImageCanvas(this);
        notebook->AddPage(result_canvas,title+"[gray]");
        result_canvas->SetImage(image);
        result_canvas->FitSize();
        result_canvas->UpdateCanvas();
        notebook->SetSelection(notebook->GetPageIndex(result_canvas));
    }
}

void MainFrame::OnFileOpen ( wxCommandEvent &event )
{
  wxFileDialog fopen_dlg ( this, _ ( "Open a Image" ), cur_dir, wxEmptyString,
                           "Jepg Files(*.jpg;*.jepg)|*.jpg;*.jpeg|PNG Files(*.png)|*.png|BMP Files(*.bmp)|*.bmp",
                           wxFD_OPEN|wxFD_FILE_MUST_EXIST );
  if ( fopen_dlg.ShowModal() == wxID_CANCEL )
    return;

  cur_file = fopen_dlg.GetPath();
  wxImage image ( cur_file );
  if ( image.IsOk() )
    {
      ImageCanvas *canvas = new ImageCanvas(this);
      canvas->SetImage(image);
      notebook->AddPage(canvas, wxFileName(cur_file).GetName());
      canvas->FitSize();
      canvas->UpdateCanvas();
      notebook->SetSelection(notebook->GetPageIndex(canvas));
    }
  UpdateInfo();
}

void MainFrame::OnFileSave ( wxCommandEvent &event )
{

}

void MainFrame::OnFileActived ( wxTreeEvent &event )
{

}

void MainFrame::OnDirChanged ( wxTreeEvent &event )
{
  gallery->StartLoad ( dir_ctrl->GetPath() );
  progress_bar->SetValue ( 0.0 );
  mgr.GetPane ( progress_bar ).Show();
  toolbar_file->EnableTool ( ID_STOP, true );
  mgr.Update();
}

void MainFrame::OnGalleryProgress ( wxCommandEvent &event )
{
  SetStatusText ( _( "Caching Preview, Please wait..." ) );
  progress_bar->SetValue ( gallery->GetProgressValue() );
  progress_bar->Refresh();
}

void MainFrame::OnGalleryComplete ( wxCommandEvent &event )
{
  mgr.GetPane ( progress_bar ).Hide();
  toolbar_file->EnableTool ( ID_STOP, false );
  mgr.Update();
  SetStatusText ( _( "Caching Complete." ) );
}

void MainFrame::OnImageClicked ( wxCommandEvent &event )
{
  cur_file = gallery->GetSelectImagePath();
  wxImage image ( cur_file );
  if ( image.IsOk() )
    {
      //image_origin->SetImage ( image );
      //image_origin->FitSize();
      //image_origin->UpdateCanvas();
      ImageCanvas *canvas = new ImageCanvas(this);
      canvas->SetImage(image);
      notebook->AddPage(canvas, wxFileName(cur_file).GetName());
      canvas->FitSize();
      canvas->UpdateCanvas();
      notebook->SetSelection(notebook->GetPageIndex(canvas));
    }
  UpdateInfo ( false );
}

void MainFrame::UpdateInfo ( bool update_tree )
{
  wxFileName file_name ( cur_file );
  cur_dir = file_name.GetPath();
  if ( update_tree )
    {
      dir_ctrl->ExpandPath ( cur_dir );
      dir_ctrl->SelectPath ( cur_file );
    }
  SetStatusText ( cur_dir, 0 );
  wxString changed = ( image_changed ) ?"*":" ";
  wxString info = wxString::Format ( "%s %s[%s]-%s", file_name.GetFullName(),changed, cur_dir, APP_NAME );
  SetTitle ( info );
}
