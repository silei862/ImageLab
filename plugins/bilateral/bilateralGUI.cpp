///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 17 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "bilateralGUI.h"

///////////////////////////////////////////////////////////////////////////

BilateralBase::BilateralBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("双边滤波器"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	m_staticText4->SetFont( wxFont( 15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );
	m_staticText4->SetForegroundColour( wxColour( 0, 62, 129 ) );
	
	bSizer10->Add( m_staticText4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("参数") ), wxVERTICAL );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText5 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("邻域直径："), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	bSizer11->Add( m_staticText5, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	filtersize_spin = new wxSpinCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 20, 9 );
	bSizer11->Add( filtersize_spin, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizer1->Add( bSizer11, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText6 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("色差容限："), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	bSizer12->Add( m_staticText6, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	colorsigma_text = new wxTextCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxT("15.0"), wxDefaultPosition, wxDefaultSize, 0 );
	colorsigma_text->SetMinSize( wxSize( 130,-1 ) );
	
	bSizer12->Add( colorsigma_text, 0, wxALL, 5 );
	
	
	sbSizer1->Add( bSizer12, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText7 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("空间容差："), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	bSizer13->Add( m_staticText7, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	spacesigma_text = new wxTextCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxT("10.0"), wxDefaultPosition, wxDefaultSize, 0 );
	spacesigma_text->SetMinSize( wxSize( 130,-1 ) );
	
	bSizer13->Add( spacesigma_text, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizer1->Add( bSizer13, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	
	bSizer10->Add( sbSizer1, 0, wxEXPAND, 5 );
	
	apply_button = new wxButton( this, wxID_ANY, wxT("应用"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer10->Add( apply_button, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	this->SetSizer( bSizer10 );
	this->Layout();
	
	// Connect Events
	apply_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BilateralBase::OnApply ), NULL, this );
}

BilateralBase::~BilateralBase()
{
	// Disconnect Events
	apply_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BilateralBase::OnApply ), NULL, this );
	
}
