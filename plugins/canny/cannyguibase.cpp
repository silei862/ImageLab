///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 17 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "cannyguibase.h"

///////////////////////////////////////////////////////////////////////////

CannyGUIBase::CannyGUIBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	this->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("Canny边缘检测"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	m_staticText4->SetFont( wxFont( 15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );
	m_staticText4->SetForegroundColour( wxColour( 5, 75, 149 ) );
	
	bSizer8->Add( m_staticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, wxT("通过滑动条调整下阈值，上阈值=阈值倍率X下阈值。"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	m_staticText5->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_SLANT, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );
	m_staticText5->SetForegroundColour( wxColour( 109, 109, 109 ) );
	
	bSizer9->Add( m_staticText5, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer8->Add( bSizer9, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer8->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	
	bSizer1->Add( bSizer8, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("    低阈值:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer2->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	lowthreshold_text = new wxStaticText( this, wxID_ANY, wxT("90"), wxDefaultPosition, wxDefaultSize, 0 );
	lowthreshold_text->Wrap( -1 );
	bSizer2->Add( lowthreshold_text, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	low_slider = new wxSlider( this, ID_LOWTHRESHOLD, 90, 0, 200, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer2->Add( low_slider, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer1->Add( bSizer2, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText11 = new wxStaticText( this, wxID_ANY, wxT("阈值倍率:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	bSizer21->Add( m_staticText11, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	ratio_text = new wxStaticText( this, wxID_ANY, wxT("3.0"), wxDefaultPosition, wxDefaultSize, 0 );
	ratio_text->Wrap( -1 );
	bSizer21->Add( ratio_text, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	ratio_slider = new wxSlider( this, ID_RATIO, 30, 10, 50, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer21->Add( ratio_slider, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer1->Add( bSizer21, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer91;
	bSizer91 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText7 = new wxStaticText( this, wxID_ANY, wxT("滤波器内核大小:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	bSizer91->Add( m_staticText7, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	kernelsize_combo = new wxComboBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	bSizer91->Add( kernelsize_combo, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer1->Add( bSizer91, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer6->Add( 0, 0, 1, wxEXPAND, 5 );
	
	usel2_check = new wxCheckBox( this, wxID_ANY, wxT("二级梯度"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( usel2_check, 0, wxALL, 5 );
	
	
	bSizer6->Add( 0, 0, 1, wxEXPAND, 5 );
	
	revert_check = new wxCheckBox( this, wxID_ANY, wxT("反色输出"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( revert_check, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer6->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	bSizer1->Add( bSizer6, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticline2 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer7->Add( 0, 0, 1, wxEXPAND, 5 );
	
	apply_button = new wxButton( this, wxID_ANY, wxT("应用"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( apply_button, 0, wxALL, 5 );
	
	
	bSizer7->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	bSizer1->Add( bSizer7, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	// Connect Events
	low_slider->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( CannyGUIBase::OnLowScroll ), NULL, this );
	low_slider->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( CannyGUIBase::OnLowScroll ), NULL, this );
	low_slider->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( CannyGUIBase::OnLowScroll ), NULL, this );
	low_slider->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( CannyGUIBase::OnLowScroll ), NULL, this );
	low_slider->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( CannyGUIBase::OnLowScroll ), NULL, this );
	low_slider->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( CannyGUIBase::OnLowScroll ), NULL, this );
	low_slider->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( CannyGUIBase::OnLowScroll ), NULL, this );
	low_slider->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( CannyGUIBase::OnLowScroll ), NULL, this );
	low_slider->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( CannyGUIBase::OnLowScroll ), NULL, this );
	ratio_slider->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( CannyGUIBase::OnRatioScroll ), NULL, this );
	ratio_slider->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( CannyGUIBase::OnRatioScroll ), NULL, this );
	ratio_slider->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( CannyGUIBase::OnRatioScroll ), NULL, this );
	ratio_slider->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( CannyGUIBase::OnRatioScroll ), NULL, this );
	ratio_slider->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( CannyGUIBase::OnRatioScroll ), NULL, this );
	ratio_slider->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( CannyGUIBase::OnRatioScroll ), NULL, this );
	ratio_slider->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( CannyGUIBase::OnRatioScroll ), NULL, this );
	ratio_slider->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( CannyGUIBase::OnRatioScroll ), NULL, this );
	ratio_slider->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( CannyGUIBase::OnRatioScroll ), NULL, this );
	apply_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CannyGUIBase::OnApply ), NULL, this );
}

CannyGUIBase::~CannyGUIBase()
{
	// Disconnect Events
	low_slider->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( CannyGUIBase::OnLowScroll ), NULL, this );
	low_slider->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( CannyGUIBase::OnLowScroll ), NULL, this );
	low_slider->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( CannyGUIBase::OnLowScroll ), NULL, this );
	low_slider->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( CannyGUIBase::OnLowScroll ), NULL, this );
	low_slider->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( CannyGUIBase::OnLowScroll ), NULL, this );
	low_slider->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( CannyGUIBase::OnLowScroll ), NULL, this );
	low_slider->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( CannyGUIBase::OnLowScroll ), NULL, this );
	low_slider->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( CannyGUIBase::OnLowScroll ), NULL, this );
	low_slider->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( CannyGUIBase::OnLowScroll ), NULL, this );
	ratio_slider->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( CannyGUIBase::OnRatioScroll ), NULL, this );
	ratio_slider->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( CannyGUIBase::OnRatioScroll ), NULL, this );
	ratio_slider->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( CannyGUIBase::OnRatioScroll ), NULL, this );
	ratio_slider->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( CannyGUIBase::OnRatioScroll ), NULL, this );
	ratio_slider->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( CannyGUIBase::OnRatioScroll ), NULL, this );
	ratio_slider->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( CannyGUIBase::OnRatioScroll ), NULL, this );
	ratio_slider->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( CannyGUIBase::OnRatioScroll ), NULL, this );
	ratio_slider->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( CannyGUIBase::OnRatioScroll ), NULL, this );
	ratio_slider->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( CannyGUIBase::OnRatioScroll ), NULL, this );
	apply_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CannyGUIBase::OnApply ), NULL, this );
	
}
