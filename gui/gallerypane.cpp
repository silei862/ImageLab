
#include <gallery.h>
#include <guievent.h>
#include "gallerypane.h"

wxDEFINE_EVENT(gpEVT_IMAGE_OPEN, wxCommandEvent);

GalleryPane::GalleryPane(wxWindow *parent, wxWindowID id)
    :GalleryPaneBase(parent, id)
{
    stop_button->Disable();
    wxBoxSizer *gsizer = new wxBoxSizer(wxVERTICAL);
    gallery = new Gallery(this, ID_GALLERY);
    gsizer->Add(gallery, 1 , wxEXPAND, 5);

    wxSizer *sizer = GetSizer();
    sizer->Add(gsizer, 1, wxEXPAND | wxALIGN_CENTER_HORIZONTAL, 5);

    Bind(wxEVT_LISTBOX_DCLICK, &GalleryPane::OnImageDClicked, this , ID_GALLERY);
    Bind(progrEVT_START, &GalleryPane::OnLoadStart, this, ID_GALLERY);
    Bind(progrEVT_UPDATE, &GalleryPane::OnLoadUpdate, this, ID_GALLERY);
    Bind(progrEVT_COMPLETE, &GalleryPane::OnLoadComplete, this, ID_GALLERY);
}

void GalleryPane::StartLoad(const wxString &dir)
{
    cur_dir = dir;
    gallery->StartLoad(cur_dir);
}

const wxString &GalleryPane::GetSelectedImage()
{
    return gallery->GetSelectImagePath();
}

void GalleryPane::OnImageDClicked(wxCommandEvent &event)
{
    wxQueueEvent(GetParent(), new wxCommandEvent(gpEVT_IMAGE_OPEN, GetId()));
}

void GalleryPane::OnLoadStart(wxCommandEvent &event)
{
    refresh_button->Disable();
    stop_button->Enable();
    wxQueueEvent(GetParent(), event.Clone());
}

void GalleryPane::OnLoadUpdate(wxCommandEvent &event)
{
    wxQueueEvent(GetParent(), event.Clone());
}

void GalleryPane::OnLoadComplete(wxCommandEvent &event)
{
    wxQueueEvent(GetParent(), event.Clone());
    stop_button->Disable();
    refresh_button->Enable();
}

void GalleryPane::OnRefreshClicked(wxCommandEvent &event)
{
    if(cur_dir.IsEmpty())
        return;
    gallery->StartLoad(cur_dir);
}

void GalleryPane::OnStopClicked(wxCommandEvent &event)
{
    gallery->StopLoad();
}

void GalleryPane::OnOpenClicked(wxCommandEvent &event)
{
    wxQueueEvent(GetParent(), new wxCommandEvent(gpEVT_IMAGE_OPEN, GetId()));
}
