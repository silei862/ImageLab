// File		: mainframe.h
// Author	: silei
// Descr	: MainFrame header

#ifndef MAINFRAME_H
#define MAINFRAME_H

//#include "wx_pch.h"
#include <wx/wx.h>
#include <wx/aui/aui.h>
#include <wx/dirctrl.h>
#include <wx/filefn.h>
#include <wx/config.h>
#include "progressbar.h"
#include "imagecanvas.h"
#include "gallery.h"

class MainFrame : public wxFrame {
	enum _IDS {
		ID_EXIT = wxID_HIGHEST,
		ID_FILEOPEN,
		ID_FILESAVE,
        ID_HELP,
        ID_STOP,

		ID_ZOOMOUT,
		ID_ZOOMIN,
		ID_FITWIN,

        ID_GRAYLIZE,

		ID_DIRCTRL,
        ID_GALLERY,
	};
	enum _CONST {
		MIN_FRM_WIDTH = 1024,
        MIN_FRM_HIGHT = 768,
	};
	const static wxString APP_NAME;
	const static wxString KEY_CUR_DIR;
	const static wxString KEY_PERSPECTIVE;
public:
	MainFrame(wxWindow *parent, wxWindowID id, const wxString &title,
			const wxPoint &pos = wxDefaultPosition,
			const wxSize &size = wxDefaultSize,
			long style = wxDEFAULT_FRAME_STYLE,
			const wxString &name = wxFrameNameStr);
	~MainFrame();
	
	inline void InitGUI();
	inline void InitMenubar();
	inline void InitToolbar();
	inline void InitPanes();
	inline void BindEvtProc();
	inline void LoadConfigs();
	inline void SaveConfigs();

//------------------------------------------------------------------
public:
	void OnExit(wxCommandEvent &event);
	void OnFileOpen(wxCommandEvent &event);
	void OnFileSave(wxCommandEvent &event);
    void OnStop(wxCommandEvent &event);
	void OnHelp(wxCommandEvent &event);

	void OnZoomOut(wxCommandEvent &event);
	void OnZoomIn(wxCommandEvent &event);
	void OnFitWin(wxCommandEvent &event);

    void OnGraylize(wxCommandEvent &event);

	void OnFileActived(wxTreeEvent &event);
    void OnDirChanged(wxTreeEvent &event);
    void OnImageClicked(wxCommandEvent &event);
    void OnGalleryProgress(wxCommandEvent &event);
    void OnGalleryComplete(wxCommandEvent &event);

//------------------------------------------------------------------
private:
	void UpdateInfo(bool update_tree=true);
//------------------------------------------------------------------
private:
	wxAuiManager mgr;
    wxAuiToolBar *toolbar_file;
    wxAuiNotebook *notebook;
	wxGenericDirCtrl *dir_ctrl;
    Gallery *gallery;
	ProgressBar *progress_bar;
	wxConfig *configs;
	wxString cur_dir;
	wxString cur_file;
	wxString perspective;
	bool image_changed;
};

#endif //MAINFRAME_H
