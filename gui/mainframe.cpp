#include <wx/config.h>
#include <wx/filename.h>
#include <wx/infobar.h>
#include <guievent.h>
#include <imagecanvas.h>
#include <progressbar.h>
#include <plugmgr.h>
#include "gallerypane.h"
#include "mainframe.h"
#include "aboutdialog.h"

MainFrame::MainFrame(wxWindow *parent, PluginLoader *loader, wxWindowID id)
    :MainFrameBase(parent, id), plugin_mgr(loader)
{
    LoadConfigs();
    InitPanes();
    InitPlugins();

    if(!perspective.IsEmpty())
        m_mgr.LoadPerspective(perspective, false);
    m_mgr.Update();
    dir_ctrl->SetPath(cur_path);

    BindEvents();

    Maximize(true);
}

void MainFrame::LoadConfigs()
{
    configs = new wxConfig(APP_NAME);
    configs->Read(KEY_CURDIR, &cur_path, wxFileName::GetHomeDir());
    configs->Read(KEY_PERSPECTIVE, &perspective, wxEmptyString);
}

void MainFrame::SaveConfigs()
{
    configs->Write(KEY_CURDIR, cur_path);
    configs->Write(KEY_PERSPECTIVE, m_mgr.SavePerspective());
    delete configs;
}

void MainFrame::InitPanes() {
    gallery_pane = new GalleryPane(this, ID_GALLERYPANE);
    m_mgr.AddPane(gallery_pane, wxAuiPaneInfo().Name("Gallery").Caption(wxT("图集")).PinButton().CloseButton(false).MinSize(200,100).Left());

    progressbar = new ProgressBar(this, ID_PROGRESSBAR);
    m_mgr.AddPane(progressbar, wxAuiPaneInfo().Name("ProgressBar").Hide().CloseButton(false).MinSize(100,30).Bottom());
}

void MainFrame::InitPlugins()
{
    plugin_mgr.InitPlugin(img_notebook);

    for( size_t i = 0; i < plugin_mgr.GetPluginCount(); i++) {
        PluginCategroy cate = plugin_mgr[i]->GetCategory();
        wxString name = plugin_mgr[i]->GetName();
        wxWindow *gui;

        switch (cate) {
        case PLUG_BASIC:
            gui = plugin_mgr[i]->CreateGUI(basic_book);
            basic_book->AddPage(gui, name);
            break;
        case PLUG_EDGEDETERCTOR:
            gui = plugin_mgr[i]->CreateGUI(edge_book);
            edge_book->AddPage(gui, name);
            break;
        case PLUG_FILTER:
            gui = plugin_mgr[i]->CreateGUI(filter_book);
            filter_book->AddPage(gui, name);
            break;
        case PLUG_OTHER:
            gui = plugin_mgr[i]->CreateGUI(other_book);
            other_book->AddPage(gui, name);
            break;
        default:
            gui = plugin_mgr[i]->CreateGUI(other_book);
            other_book->AddPage(gui, name);
            break;
        }
    }
}

void MainFrame::BindEvents()
{
    Bind(gpEVT_IMAGE_OPEN, &MainFrame::OnImageOpen, this, ID_GALLERYPANE);

    Bind(progrEVT_START, &MainFrame::OnProgressStart, this);
    Bind(progrEVT_UPDATE, &MainFrame::OnProgressUpdate, this);
    Bind(progrEVT_COMPLETE, &MainFrame::OnProgressComplete, this);

    Bind(infoEVT_UPDATE, &MainFrame::OnInfoUpdate, this);
}

void MainFrame::OnMore(wxCommandEvent &event)
{
   AboutDialog *dlg = new AboutDialog(this);
   dlg->Show();
}

void MainFrame::OnCloseFrame(wxCloseEvent &event)
{
    m_mgr.GetPane(progressbar).Hide();
    m_mgr.Update();
    SaveConfigs();
    Destroy();
}

void MainFrame::OnImagePageChanged(wxAuiNotebookEvent &event)
{
    wxWindow *plugin_gui = GetCurrentPluginGUI();
    if(plugin_gui)
        wxQueueEvent(plugin_gui, new wxCommandEvent(plugEVT_PAGE_CHANGED));
}

void MainFrame::OnOpenAction(wxCommandEvent &event)
{
    wxFileDialog *dlg = new wxFileDialog(this,wxT("打开图片"),cur_path, wxEmptyString,
                                        wxT("图片|*.jpg;*.jpeg;*.bmp;*.png;*.xpm;*.tif;*.tiff"));
    if(dlg->ShowModal() == wxID_OK) {
        wxString file_path = dlg->GetPath();
        //Add a image:
        wxImage image(file_path);
        if(image.IsOk()){
            ImageCanvas *canvas = new ImageCanvas(img_notebook);
            img_notebook->AddPage(canvas, wxFileName(file_path).GetName(), true);
            canvas->SetImage(image);
            canvas->FitSize();
            //change current path
            cur_path = wxFileName(file_path).GetPath();
            dir_ctrl->SetPath(cur_path);
        }
    }
}

void MainFrame::OnSaveAction(wxCommandEvent &evnet)
{

}

void MainFrame::OnOriginSize(wxCommandEvent &event)
{
    ImageCanvas *canvas = dynamic_cast<ImageCanvas*>(img_notebook->GetCurrentPage());
    if(!canvas)
        return;
    canvas->OriginSize();
}

void MainFrame::OnZoomOut(wxCommandEvent &event)
{
    ImageCanvas *canvas = dynamic_cast<ImageCanvas*>(img_notebook->GetCurrentPage());
    if(!canvas)
        return;
    canvas->ZoomOut();
    canvas->UpdateCanvas();
}

void MainFrame::OnZoomIn(wxCommandEvent &event)
{
    ImageCanvas *canvas = dynamic_cast<ImageCanvas*>(img_notebook->GetCurrentPage());
    if(!canvas)
        return;
    canvas->ZoomIn();
    canvas->UpdateCanvas();
}

void MainFrame::OnFitSize(wxCommandEvent &event)
{
    ImageCanvas *canvas = dynamic_cast<ImageCanvas*>(img_notebook->GetCurrentPage());
    if(!canvas)
        return;
    canvas->FitSize();
}

void MainFrame::OnDirChanged(wxTreeEvent &event)
{
    cur_path = dir_ctrl->GetPath();
    gallery_pane->StartLoad(cur_path);
}

void MainFrame::OnImageOpen(wxCommandEvent &event)
{
    wxString path = gallery_pane->GetSelectedImage();
    wxImage image(path);
    ImageCanvas *canvas = new ImageCanvas(img_notebook);
    canvas->SetImage(image);
    img_notebook->AddPage(canvas, wxFileName(path).GetName(), true );
    canvas->FitSize();
    m_mgr.Update();
}

void MainFrame::OnProgressStart(wxCommandEvent &event) {
    m_mgr.GetPane(progressbar).Show();
    m_mgr.Update();
    info_ctrl->ShowMessage(event.GetString(), wxICON_INFORMATION);
    wxQueueEvent(progressbar, event.Clone());
}

void MainFrame::OnProgressUpdate(wxCommandEvent &event) {
    wxQueueEvent(progressbar, event.Clone());
}

void MainFrame::OnProgressComplete(wxCommandEvent &event) {
    wxQueueEvent(progressbar, event.Clone());
    m_mgr.GetPane(progressbar).Hide();
    m_mgr.Update();
    gallery_pane->Refresh();
    info_ctrl->ShowMessage(event.GetString(), wxICON_INFORMATION);
}

void MainFrame::OnInfoUpdate(wxCommandEvent &event)
{
    info_ctrl->ShowMessage(event.GetString(), event.GetInt());
}

wxWindow *MainFrame::GetCurrentPluginGUI()
{
    wxPanel *pane = dynamic_cast<wxPanel*>(tool_notebook->GetCurrentPage());
    if(!pane)
        return nullptr;
    wxWindowListNode* node = pane->GetChildren().GetFirst();
    if(!node)
        return nullptr;
    wxChoicebook *nb = dynamic_cast<wxChoicebook*>(node->GetData());
    if(!nb)
        return nullptr;
    return nb->GetCurrentPage();
}
