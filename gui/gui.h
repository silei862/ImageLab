///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 17 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUI_H__
#define __GUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/dirctrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/aui/aui.h>
#include <wx/aui/auibar.h>
#include <wx/aui/auibook.h>
#include <wx/choicebk.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/hyperlink.h>
#include <wx/infobar.h>
#include <wx/frame.h>
#include <wx/bmpbuttn.h>
#include <wx/html/htmlwin.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class MainFrameBase
///////////////////////////////////////////////////////////////////////////////
class MainFrameBase : public wxFrame 
{
	private:
	
	protected:
		enum
		{
			ID_DIRCTRL = 1000,
			ID_MORE
		};
		
		wxGenericDirCtrl* dir_ctrl;
		wxAuiToolBar* file_toolbar;
		wxAuiToolBarItem* open_tool; 
		wxAuiToolBarItem* save_tool; 
		wxAuiToolBar* view_toolbar;
		wxAuiToolBarItem* origin_tool; 
		wxAuiToolBarItem* zoomout_tool; 
		wxAuiToolBarItem* zoomin_tool; 
		wxAuiToolBarItem* fitsize_tool; 
		wxAuiNotebook* img_notebook;
		wxAuiNotebook* tool_notebook;
		wxPanel* basic_pane;
		wxChoicebook* basic_book;
		wxPanel* filter_pane;
		wxChoicebook* filter_book;
		wxPanel* edge_pane;
		wxChoicebook* edge_book;
		wxPanel* other_pane;
		wxChoicebook* other_book;
		wxPanel* about_pane;
		wxStaticText* m_staticText5;
		wxStaticText* m_staticText6;
		wxButton* more_button;
		wxStaticText* m_staticText7;
		wxHyperlinkCtrl* m_hyperlink6;
		wxHyperlinkCtrl* m_hyperlink7;
		wxHyperlinkCtrl* m_hyperlink8;
		wxHyperlinkCtrl* m_hyperlink9;
		wxStaticText* m_staticText8;
		wxHyperlinkCtrl* m_hyperlink11;
		wxHyperlinkCtrl* m_hyperlink10;
		wxInfoBar* info_ctrl;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseFrame( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnDirChanged( wxTreeEvent& event ) { event.Skip(); }
		virtual void OnOpenAction( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSaveAction( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOriginSize( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnZoomOut( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnZoomIn( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFitSize( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnImagePageChanged( wxAuiNotebookEvent& event ) { event.Skip(); }
		virtual void OnMore( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		MainFrameBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("图像实验室"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1024,768 ), long style = wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		wxAuiManager m_mgr;
		
		~MainFrameBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GalleryPaneBase
///////////////////////////////////////////////////////////////////////////////
class GalleryPaneBase : public wxPanel 
{
	private:
	
	protected:
		enum
		{
			ID_REFRESH = 1000,
			ID_STOP,
			ID_OPEN
		};
		
		wxBitmapButton* refresh_button;
		wxBitmapButton* stop_button;
		wxBitmapButton* open_button;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnRefreshClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnStopClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOpenClicked( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GalleryPaneBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxTAB_TRAVERSAL ); 
		~GalleryPaneBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class AboutDialogBase
///////////////////////////////////////////////////////////////////////////////
class AboutDialogBase : public wxDialog 
{
	private:
	
	protected:
		enum
		{
			ID_OKBUTTON = 1000
		};
		
		wxHtmlWindow* about_html;
		wxButton* ok_button;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnOkButton( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		AboutDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("关于..."), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCAPTION|wxCLOSE_BOX ); 
		~AboutDialogBase();
	
};

#endif //__GUI_H__
