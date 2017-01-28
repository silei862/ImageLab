///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 17 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "ResizeGUIBase.h"

///////////////////////////////////////////////////////////////////////////

ResizeGUIBase::ResizeGUIBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText13 = new wxStaticText( this, wxID_ANY, wxT("更改图片大小"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	m_staticText13->SetFont( wxFont( 15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );
	m_staticText13->SetForegroundColour( wxColour( 0, 55, 114 ) );
	
	bSizer11->Add( m_staticText13, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("参数") ), wxVERTICAL );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText10 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("宽:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	bSizer12->Add( m_staticText10, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	width_spin = new wxSpinCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100000, 200 );
	bSizer12->Add( width_spin, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizer1->Add( bSizer12, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer121;
	bSizer121 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText101 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("高:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText101->Wrap( -1 );
	bSizer121->Add( m_staticText101, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	height_spin = new wxSpinCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100000, 200 );
	bSizer121->Add( height_spin, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizer1->Add( bSizer121, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText14 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("缩放算法:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	bSizer21->Add( m_staticText14, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString alg_choiceChoices[] = { wxT("邻域插值"), wxT("双线性插值"), wxT("双三次插值") };
	int alg_choiceNChoices = sizeof( alg_choiceChoices ) / sizeof( wxString );
	alg_choice = new wxChoice( sbSizer1->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, alg_choiceNChoices, alg_choiceChoices, 0 );
	alg_choice->SetSelection( 0 );
	bSizer21->Add( alg_choice, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizer1->Add( bSizer21, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	lockratio_check = new wxCheckBox( sbSizer1->GetStaticBox(), wxID_ANY, wxT("锁定高宽比"), wxDefaultPosition, wxDefaultSize, 0 );
	lockratio_check->SetValue(true); 
	sbSizer1->Add( lockratio_check, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer11->Add( sbSizer1, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 10 );
	
	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer18->Add( 0, 0, 1, wxEXPAND, 5 );
	
	apply_button = new wxButton( this, wxID_ANY, wxT("确定"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer18->Add( apply_button, 0, wxALL, 5 );
	
	
	bSizer18->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	bSizer11->Add( bSizer18, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	this->SetSizer( bSizer11 );
	this->Layout();
	
	// Connect Events
	width_spin->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( ResizeGUIBase::OnWidthSpinChanged ), NULL, this );
	height_spin->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( ResizeGUIBase::OnHeightSpinChanged ), NULL, this );
	apply_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ResizeGUIBase::OnApply ), NULL, this );
}

ResizeGUIBase::~ResizeGUIBase()
{
	// Disconnect Events
	width_spin->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( ResizeGUIBase::OnWidthSpinChanged ), NULL, this );
	height_spin->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( ResizeGUIBase::OnHeightSpinChanged ), NULL, this );
	apply_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ResizeGUIBase::OnApply ), NULL, this );
	
}
