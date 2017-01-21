///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 17 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __CANNYGUIBASE_H__
#define __CANNYGUIBASE_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/slider.h>
#include <wx/combobox.h>
#include <wx/checkbox.h>
#include <wx/button.h>
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////

#define ID_LOWTHRESHOLD 1000
#define ID_RATIO 1001

///////////////////////////////////////////////////////////////////////////////
/// Class CannyGUIBase
///////////////////////////////////////////////////////////////////////////////
class CannyGUIBase : public wxPanel 
{
	private:
	
	protected:
		wxStaticText* m_staticText4;
		wxStaticText* m_staticText5;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticText1;
		wxStaticText* lowthreshold_text;
		wxSlider* low_slider;
		wxStaticText* m_staticText11;
		wxStaticText* ratio_text;
		wxSlider* ratio_slider;
		wxStaticText* m_staticText7;
		wxComboBox* kernelsize_combo;
		wxCheckBox* usel2_check;
		wxCheckBox* revert_check;
		wxStaticLine* m_staticline2;
		wxButton* apply_button;
		wxButton* cancel_button;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnLowThumbRelease( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnRatioThumbRelease( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnApply( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancel( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		CannyGUIBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxTAB_TRAVERSAL ); 
		~CannyGUIBase();
	
};

#endif //__CANNYGUIBASE_H__
