///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 17 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GREYLIZEPANEBASE_H__
#define __GREYLIZEPANEBASE_H__

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
#include <wx/slider.h>
#include <wx/checkbox.h>
#include <wx/button.h>
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class GreylizePaneBase
///////////////////////////////////////////////////////////////////////////////
class GreylizePaneBase : public wxPanel 
{
	private:
	
	protected:
		enum
		{
			ID_REDSLIDER = 1000,
			ID_GREENSLIDER,
			ID_BLUESLIDER,
			ID_REDLOCK,
			ID_GREENLOCK,
			ID_BLUELOCK,
			ID_APPLY,
			ID_CANCEL
		};
		
		wxStaticText* m_staticText5;
		wxStaticText* m_staticText6;
		wxStaticText* m_staticText7;
		wxStaticText* redval_text;
		wxStaticText* greenval_text;
		wxStaticText* blueval_text;
		wxSlider* red_slider;
		wxSlider* green_slider;
		wxSlider* blue_slider;
		wxCheckBox* red_check;
		wxCheckBox* green_check;
		wxCheckBox* blue_check;
		wxCheckBox* eqhist_check;
		wxButton* applyButton;
		wxButton* cancelButton;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnRedThumbRelease( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnGreenThumbRelease( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnBlueThumbRelease( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnRedCheckChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnGreenCheckChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBlueCheckChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnApply( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancel( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GreylizePaneBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxNO_BORDER|wxTAB_TRAVERSAL, const wxString& name = wxT("GreylizePane") ); 
		~GreylizePaneBase();
	
};

#endif //__GREYLIZEPANEBASE_H__
