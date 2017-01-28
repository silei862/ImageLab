
#ifndef GALLERYPANE_H
#define GALLERYPANE_H

#include <wx/event.h>
#include "gui.h"

wxDECLARE_EVENT(gpEVT_IMAGE_OPEN, wxCommandEvent);

class Gallery;

class GalleryPane : public GalleryPaneBase {

    enum _IDS {
        ID_GALLERY = wxID_HIGHEST + 500,
    };

public:
    GalleryPane(wxWindow *parent, wxWindowID id = wxID_ANY);
    ~GalleryPane() { }

    void StartLoad(const wxString &dir);
    const wxString& GetSelectedImage();

    void OnImageDClicked(wxCommandEvent &event);

    void OnLoadStart(wxCommandEvent &event);
    void OnLoadUpdate(wxCommandEvent &event);
    void OnLoadComplete(wxCommandEvent &event);

    void OnStopButton(wxCommandEvent &event);

    void OnRefreshClicked(wxCommandEvent &event);
    void OnStopClicked(wxCommandEvent &event);
    void OnOpenClicked(wxCommandEvent &event);


private:
    Gallery *gallery;
    wxString cur_dir;

};

#endif //GALLERYPANE_H
