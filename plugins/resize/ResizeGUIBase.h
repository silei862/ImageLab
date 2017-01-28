///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 17 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __RESIZEGUIBASE_H__
#define __RESIZEGUIBASE_H__

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
#include <wx/choice.h>
#include <wx/checkbox.h>
#include <wx/statbox.h>
#include <wx/button.h>
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class ResizeGUIBase
///////////////////////////////////////////////////////////////////////////////
class ResizeGUIBase : public wxPanel 
{
	private:
	
	protected:
		wxStaticText* m_staticText13;
		wxStaticText* m_staticText10;
		wxSpinCtrl* width_spin;
		wxStaticText* m_staticText101;
		wxSpinCtrl* height_spin;
		wxStaticText* m_staticText14;
		wxChoice* alg_choice;
		wxCheckBox* lockratio_check;
		wxButton* apply_button;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnWidthSpinChanged( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnHeightSpinChanged( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnApply( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		ResizeGUIBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,600 ), long style = wxTAB_TRAVERSAL ); 
		~ResizeGUIBase();
	
};

#endif //__RESIZEGUIBASE_H__
