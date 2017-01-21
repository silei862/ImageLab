///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 17 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "greylizepanebase.h"

///////////////////////////////////////////////////////////////////////////

GreylizePaneBase::GreylizePaneBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	this->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText71 = new wxStaticText( this, wxID_ANY, _("Greylize Operator"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText71->Wrap( -1 );
	m_staticText71->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );
	m_staticText71->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHT ) );
	
	bSizer11->Add( m_staticText71, 1, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer10->Add( 0, 0, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText8 = new wxStaticText( this, wxID_ANY, _("Use the slider to adjust Weight of each RGB channel."), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	m_staticText8->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_SLANT, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );
	m_staticText8->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_GRAYTEXT ) );
	
	bSizer10->Add( m_staticText8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer10->Add( 0, 0, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer11->Add( bSizer10, 1, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	m_staticline1->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );
	
	bSizer11->Add( m_staticline1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer6->Add( bSizer11, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, _("Red:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	bSizer1->Add( m_staticText5, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxALIGN_RIGHT, 5 );
	
	m_staticText6 = new wxStaticText( this, wxID_ANY, _("Green:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	bSizer1->Add( m_staticText6, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxALIGN_RIGHT, 5 );
	
	m_staticText7 = new wxStaticText( this, wxID_ANY, _("Blue:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	bSizer1->Add( m_staticText7, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	
	bSizer4->Add( bSizer1, 0, wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	redval_text = new wxStaticText( this, wxID_ANY, _("0.350"), wxDefaultPosition, wxDefaultSize, 0 );
	redval_text->Wrap( -1 );
	bSizer2->Add( redval_text, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	greenval_text = new wxStaticText( this, wxID_ANY, _("0.350"), wxDefaultPosition, wxDefaultSize, 0 );
	greenval_text->Wrap( -1 );
	bSizer2->Add( greenval_text, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	blueval_text = new wxStaticText( this, wxID_ANY, _("0.300"), wxDefaultPosition, wxDefaultSize, 0 );
	blueval_text->Wrap( -1 );
	bSizer2->Add( blueval_text, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer4->Add( bSizer2, 0, wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	red_slider = new wxSlider( this, ID_REDSLIDER, 350, 0, 1000, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer3->Add( red_slider, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	green_slider = new wxSlider( this, ID_GREENSLIDER, 350, 0, 1000, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer3->Add( green_slider, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	blue_slider = new wxSlider( this, ID_BLUESLIDER, 300, 0, 1000, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	blue_slider->Enable( false );
	
	bSizer3->Add( blue_slider, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	
	bSizer4->Add( bSizer3, 1, wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	red_check = new wxCheckBox( this, ID_REDLOCK, _("Lock"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( red_check, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	green_check = new wxCheckBox( this, ID_GREENLOCK, _("Lock"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( green_check, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	blue_check = new wxCheckBox( this, ID_BLUELOCK, _("Lock"), wxDefaultPosition, wxDefaultSize, 0 );
	blue_check->SetValue(true); 
	bSizer5->Add( blue_check, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer4->Add( bSizer5, 0, wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	
	bSizer6->Add( bSizer4, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );
	
	eqhist_check = new wxCheckBox( this, wxID_ANY, _("Grey Level Equalization "), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8->Add( eqhist_check, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer6->Add( bSizer8, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_staticline2 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer6->Add( m_staticline2, 0, wxEXPAND|wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer7->Add( 0, 0, 1, wxEXPAND, 5 );
	
	applyButton = new wxButton( this, ID_APPLY, _("Apply"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( applyButton, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer7->Add( 0, 0, 1, wxEXPAND, 5 );
	
	cancelButton = new wxButton( this, ID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( cancelButton, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer7->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	bSizer6->Add( bSizer7, 0, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer6 );
	this->Layout();
	
	// Connect Events
	red_slider->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GreylizePaneBase::OnRedThumbRelease ), NULL, this );
	green_slider->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GreylizePaneBase::OnGreenThumbRelease ), NULL, this );
	blue_slider->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GreylizePaneBase::OnBlueThumbRelease ), NULL, this );
	red_check->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GreylizePaneBase::OnRedCheckChanged ), NULL, this );
	green_check->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GreylizePaneBase::OnGreenCheckChanged ), NULL, this );
	blue_check->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GreylizePaneBase::OnBlueCheckChanged ), NULL, this );
	applyButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GreylizePaneBase::OnApply ), NULL, this );
	cancelButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GreylizePaneBase::OnCancel ), NULL, this );
}

GreylizePaneBase::~GreylizePaneBase()
{
	// Disconnect Events
	red_slider->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GreylizePaneBase::OnRedThumbRelease ), NULL, this );
	green_slider->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GreylizePaneBase::OnGreenThumbRelease ), NULL, this );
	blue_slider->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GreylizePaneBase::OnBlueThumbRelease ), NULL, this );
	red_check->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GreylizePaneBase::OnRedCheckChanged ), NULL, this );
	green_check->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GreylizePaneBase::OnGreenCheckChanged ), NULL, this );
	blue_check->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GreylizePaneBase::OnBlueCheckChanged ), NULL, this );
	applyButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GreylizePaneBase::OnApply ), NULL, this );
	cancelButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GreylizePaneBase::OnCancel ), NULL, this );
	
}
