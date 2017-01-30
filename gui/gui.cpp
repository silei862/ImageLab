///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 17 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wx_pch.h"

#include "gui.h"

///////////////////////////////////////////////////////////////////////////

MainFrameBase::MainFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 1024,768 ), wxDefaultSize );
	m_mgr.SetManagedWindow(this);
	m_mgr.SetFlags(wxAUI_MGR_DEFAULT);
	
	dir_ctrl = new wxGenericDirCtrl( this, ID_DIRCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDIRCTRL_3D_INTERNAL|wxDIRCTRL_DIR_ONLY|wxSUNKEN_BORDER, wxEmptyString, 0 );
	
	dir_ctrl->ShowHidden( false );
	m_mgr.AddPane( dir_ctrl, wxAuiPaneInfo() .Name( wxT("DirCtrl") ).Left() .Caption( wxT("文件系统") ).CloseButton( false ).PinButton( true ).Dock().Resizable().FloatingSize( wxDefaultSize ).BottomDockable( false ).TopDockable( false ).MinSize( wxSize( 200,200 ) ) );
	
	file_toolbar = new wxAuiToolBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_TEXT ); 
	open_tool = file_toolbar->AddTool( wxID_ANY, wxT("打开"), wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 
	
	save_tool = file_toolbar->AddTool( wxID_ANY, wxT("保存"), wxArtProvider::GetBitmap( wxART_FILE_SAVE, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 
	
	file_toolbar->Realize();
	m_mgr.AddPane( file_toolbar, wxAuiPaneInfo().Name( wxT("FileToolbar") ).Top().Caption( wxT("文件") ).CloseButton( false ).PinButton( true ).Dock().Resizable().FloatingSize( wxDefaultSize ).Layer( 10 ).ToolbarPane() );
	
	view_toolbar = new wxAuiToolBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_TEXT ); 
	origin_tool = view_toolbar->AddTool( wxID_ANY, wxT("原始大小"), wxArtProvider::GetBitmap( wxART_GO_BACK, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 
	
	zoomout_tool = view_toolbar->AddTool( wxID_ANY, wxT("放大"), wxArtProvider::GetBitmap( wxART_GO_UP, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 
	
	zoomin_tool = view_toolbar->AddTool( wxID_ANY, wxT("缩小"), wxArtProvider::GetBitmap( wxART_GO_DOWN, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 
	
	fitsize_tool = view_toolbar->AddTool( wxID_ANY, wxT("适合窗口"), wxArtProvider::GetBitmap( wxART_GO_HOME, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 
	
	view_toolbar->Realize();
	m_mgr.AddPane( view_toolbar, wxAuiPaneInfo().Name( wxT("ViewToolbar") ).Top().Caption( wxT("视图") ).CloseButton( false ).PinButton( true ).Dock().Resizable().FloatingSize( wxDefaultSize ).Layer( 10 ).ToolbarPane() );
	
	img_notebook = new wxAuiNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_NB_DEFAULT_STYLE|wxAUI_NB_WINDOWLIST_BUTTON );
	m_mgr.AddPane( img_notebook, wxAuiPaneInfo() .Name( wxT("ImageNotebook") ).Left() .Caption( wxT("图片") ).CloseButton( false ).Movable( false ).Dock().Resizable().FloatingSize( wxDefaultSize ).DockFixed( true ).BottomDockable( false ).TopDockable( false ).LeftDockable( false ).RightDockable( false ).Floatable( false ).CentrePane() );
	
	
	tool_notebook = new wxAuiNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_NB_WINDOWLIST_BUTTON );
	m_mgr.AddPane( tool_notebook, wxAuiPaneInfo() .Name( wxT("ToolNotebook") ).Right() .Caption( wxT("工具") ).CloseButton( false ).PinButton( true ).Dock().Resizable().FloatingSize( wxDefaultSize ).BottomDockable( false ).TopDockable( false ).MinSize( wxSize( 300,200 ) ) );
	
	
	info_ctrl = new wxInfoBar( this );
	info_ctrl->SetShowHideEffects( wxSHOW_EFFECT_SLIDE_TO_RIGHT, wxSHOW_EFFECT_SLIDE_TO_RIGHT );
	info_ctrl->SetEffectDuration( 500 );
	m_mgr.AddPane( info_ctrl, wxAuiPaneInfo() .Name( wxT("InfoCtrl") ).Bottom() .Caption( wxT("消息") ).CloseButton( false ).PinButton( true ).Dock().Resizable().FloatingSize( wxSize( -1,-1 ) ).MinSize( wxSize( 100,20 ) ) );
	
	
	m_mgr.Update();
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrameBase::OnCloseFrame ) );
	dir_ctrl->Connect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( MainFrameBase::OnDirChanged ), NULL, this );
	this->Connect( open_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrameBase::OnOpenAction ) );
	this->Connect( save_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrameBase::OnSaveAction ) );
	this->Connect( origin_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrameBase::OnOriginSize ) );
	this->Connect( zoomout_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrameBase::OnZoomOut ) );
	this->Connect( zoomin_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrameBase::OnZoomIn ) );
	this->Connect( fitsize_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrameBase::OnFitSize ) );
	img_notebook->Connect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, wxAuiNotebookEventHandler( MainFrameBase::OnImagePageChanged ), NULL, this );
}

MainFrameBase::~MainFrameBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrameBase::OnCloseFrame ) );
	dir_ctrl->Disconnect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( MainFrameBase::OnDirChanged ), NULL, this );
	this->Disconnect( open_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrameBase::OnOpenAction ) );
	this->Disconnect( save_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrameBase::OnSaveAction ) );
	this->Disconnect( origin_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrameBase::OnOriginSize ) );
	this->Disconnect( zoomout_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrameBase::OnZoomOut ) );
	this->Disconnect( zoomin_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrameBase::OnZoomIn ) );
	this->Disconnect( fitsize_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrameBase::OnFitSize ) );
	img_notebook->Disconnect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, wxAuiNotebookEventHandler( MainFrameBase::OnImagePageChanged ), NULL, this );
	
	m_mgr.UnInit();
	
}

GalleryPaneBase::GalleryPaneBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* main_sizer;
	main_sizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer7->Add( 0, 0, 1, wxEXPAND, 5 );
	
	refresh_button = new wxBitmapButton( this, ID_REFRESH, wxArtProvider::GetBitmap( wxART_REDO, wxART_BUTTON ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	bSizer7->Add( refresh_button, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	stop_button = new wxBitmapButton( this, ID_STOP, wxArtProvider::GetBitmap( wxART_CROSS_MARK, wxART_BUTTON ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	bSizer7->Add( stop_button, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer7->Add( 0, 0, 1, wxEXPAND, 5 );
	
	open_button = new wxBitmapButton( this, ID_OPEN, wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_BUTTON ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	bSizer7->Add( open_button, 0, wxALL, 5 );
	
	
	bSizer7->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	main_sizer->Add( bSizer7, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	
	this->SetSizer( main_sizer );
	this->Layout();
	
	// Connect Events
	refresh_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GalleryPaneBase::OnRefreshClicked ), NULL, this );
	stop_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GalleryPaneBase::OnStopClicked ), NULL, this );
	open_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GalleryPaneBase::OnOpenClicked ), NULL, this );
}

GalleryPaneBase::~GalleryPaneBase()
{
	// Disconnect Events
	refresh_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GalleryPaneBase::OnRefreshClicked ), NULL, this );
	stop_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GalleryPaneBase::OnStopClicked ), NULL, this );
	open_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GalleryPaneBase::OnOpenClicked ), NULL, this );
	
}

AboutDialogBase::AboutDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 600,600 ), wxSize( 600,600 ) );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	about_html = new wxHtmlWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_AUTO );
	bSizer3->Add( about_html, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer11->Add( 0, 0, 1, wxEXPAND, 5 );
	
	ok_button = new wxButton( this, ID_OKBUTTON, wxT("确定"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer11->Add( ok_button, 0, wxALL|wxALIGN_CENTER_VERTICAL, 20 );
	
	
	bSizer11->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	bSizer3->Add( bSizer11, 0, wxALIGN_CENTER_HORIZONTAL, 20 );
	
	
	this->SetSizer( bSizer3 );
	this->Layout();
	bSizer3->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	ok_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboutDialogBase::OnOkButton ), NULL, this );
}

AboutDialogBase::~AboutDialogBase()
{
	// Disconnect Events
	ok_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboutDialogBase::OnOkButton ), NULL, this );
	
}

AboutPanelBase::AboutPanelBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, wxT("图像实验室"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	m_staticText5->SetFont( wxFont( 15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );
	m_staticText5->SetForegroundColour( wxColour( 26, 59, 93 ) );
	
	bSizer10->Add( m_staticText5, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 20 );
	
	m_staticText6 = new wxStaticText( this, wxID_ANY, wxT("wxWidgets和OpenCV整合性测试程序，本软件遵循GPL v3协议；欢迎测试，期待您的宝贵意见。"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	m_staticText6->SetMinSize( wxSize( -1,80 ) );
	
	bSizer10->Add( m_staticText6, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 10 );
	
	more_button = new wxButton( this, ID_MORE, wxT("更多信息..."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer10->Add( more_button, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 15 );
	
	m_staticText7 = new wxStaticText( this, wxID_ANY, wxT("特别感谢"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	m_staticText7->SetFont( wxFont( 13, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );
	m_staticText7->SetForegroundColour( wxColour( 64, 64, 64 ) );
	
	bSizer10->Add( m_staticText7, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 15 );
	
	m_hyperlink6 = new wxHyperlinkCtrl( this, wxID_ANY, wxT("wxWidgets"), wxT("http://www.wxwidgets.org"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
	bSizer10->Add( m_hyperlink6, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_hyperlink7 = new wxHyperlinkCtrl( this, wxID_ANY, wxT("OpenCV"), wxT("http://opencv.org"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
	bSizer10->Add( m_hyperlink7, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_hyperlink8 = new wxHyperlinkCtrl( this, wxID_ANY, wxT("QtCreator"), wxT("https://www.qt.io/ide/"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
	bSizer10->Add( m_hyperlink8, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_hyperlink9 = new wxHyperlinkCtrl( this, wxID_ANY, wxT("wxFormbuilder"), wxT("http://www.wxformbuilder.org"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
	bSizer10->Add( m_hyperlink9, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer10->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticText8 = new wxStaticText( this, wxID_ANY, wxT("作者：滇中刀客"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	m_staticText8->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_SLANT, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );
	
	bSizer10->Add( m_staticText8, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_hyperlink11 = new wxHyperlinkCtrl( this, wxID_ANY, wxT("github主页"), wxT("https://github.com/silei862/ImageLab"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
	bSizer10->Add( m_hyperlink11, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_hyperlink10 = new wxHyperlinkCtrl( this, wxID_ANY, wxT("silei862@gmail.com"), wxT("mailto:silei862@gmail.com"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
	bSizer10->Add( m_hyperlink10, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	this->SetSizer( bSizer10 );
	this->Layout();
	
	// Connect Events
	more_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboutPanelBase::OnMore ), NULL, this );
}

AboutPanelBase::~AboutPanelBase()
{
	// Disconnect Events
	more_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboutPanelBase::OnMore ), NULL, this );
	
}
