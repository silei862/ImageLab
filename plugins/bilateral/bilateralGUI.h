///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 17 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __BILATERALGUI_H__
#define __BILATERALGUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/spinctrl.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>
#include <wx/button.h>
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class BilateralBase
///////////////////////////////////////////////////////////////////////////////
class BilateralBase : public wxPanel 
{
	private:
	
	protected:
		wxStaticText* m_staticText4;
		wxStaticText* m_staticText5;
		wxSpinCtrl* filtersize_spin;
		wxStaticText* m_staticText6;
		wxTextCtrl* colorsigma_text;
		wxStaticText* m_staticText7;
		wxTextCtrl* spacesigma_text;
		wxButton* apply_button;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnApply( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		BilateralBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxTAB_TRAVERSAL ); 
		~BilateralBase();
	
};

#endif //__BILATERALGUI_H__
