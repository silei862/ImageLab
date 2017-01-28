// File   : gallery.cpp
// Author : Silei
// Descr  : Provide Image Gallery preview box

#include <wx/dc.h>
#include <wx/dir.h>
#include <wx/filename.h>
#include <wx/log.h>
#include "guievent.h"
#include "gallery.h"

const wxString image_spec[] = { "*.jpg" , "*.jpeg" , "*.png" , "*.pnm" , "*.ico",
                                "*.pcx" , "*.gif"  , "*.bmp" , "*.tif" , "*.tiff"
                              };

wxDEFINE_EVENT(pxEVT_IMAGE_LOADED, wxThreadEvent);
wxDEFINE_EVENT(pxEVT_PROGRESS_START, wxThreadEvent);
wxDEFINE_EVENT(pxEVT_PROGRESS_UPDATE, wxThreadEvent);
wxDEFINE_EVENT(pxEVT_PROGRESS_COMPLETE, wxThreadEvent);

Gallery::Gallery(wxWindow *parent, wxWindowID id,
                 const wxPoint &pos, const wxSize &size,
                 long style, const wxString &name)
    :wxVListBox(parent, id, pos, size, style, name),
     wxThreadHelper(wxTHREAD_DETACHED),
     bitmap_size(DEF_BMP_WIDTH, DEF_BMP_HEIGHT) {

    // Bind the Post processor
    Bind(pxEVT_IMAGE_LOADED, &Gallery::OnImageLoaded, this);
    Bind(pxEVT_PROGRESS_START, &Gallery::OnProgressStart, this);
    Bind(pxEVT_PROGRESS_UPDATE, &Gallery::OnProgressUpdate, this);
    Bind(pxEVT_PROGRESS_COMPLETE, &Gallery::OnProgressComplete, this);
    Bind(wxEVT_DESTROY, &Gallery::OnClose, this);
};

Gallery::~Gallery() {

};

void Gallery::OnClose(wxWindowDestroyEvent &event) {
    if(GetThread())
        GetThread()->Delete();
    while(GetThread()) {
        wxThread::This()->Sleep(1);
    }
}

void Gallery::OnDrawItem( wxDC &dc, const wxRect &rect, size_t n ) const {
    int w, h;
    GetClientSize(&w, &h);
    int x = rect.GetPosition().x + (w - previews[n].GetWidth())/2;
    int y = rect.GetPosition().y + 5;
    dc.DrawBitmap(previews[n], x, y);
    wxFileName name(image_pathes[n]);
    dc.DrawText(name.GetFullName(), x, y + previews[n].GetHeight());
}

wxCoord Gallery::OnMeasureItem( size_t n ) const {
    return previews[n].GetHeight() + 30;
}

void Gallery::OnImageLoaded(wxThreadEvent &event) {
    if(image_queue.IsEmpty() || path_queue.IsEmpty())
        return;
    wxImage preview;
    wxString path;
    image_queue>>preview;
    path_queue>>path;
    if(preview.IsOk()) {
        previews.push_back(wxBitmap(preview));
        image_pathes.push_back(path);
    }
    SetItemCount(previews.size());

    // Inform the parent window to update informations
    SendProgressStatus(progrEVT_UPDATE,wxT("缓存中，请稍等..."),event.GetExtraLong());
}

void Gallery::OnProgressStart(wxThreadEvent &event)
{
    // Redirect image loading progress:
    SendProgressStatus(progrEVT_START, wxT("图片缓存中，请稍等..."),event.GetExtraLong());
}

void Gallery::OnProgressUpdate(wxThreadEvent &event) {
    SendProgressStatus(progrEVT_UPDATE, wxT("缓存中，请稍等..."),event.GetExtraLong());
}

void Gallery::OnProgressComplete(wxThreadEvent &event) {
    SetItemCount(previews.size());
    SendProgressStatus(progrEVT_COMPLETE, wxT("缓存完成."),event.GetExtraLong());
}

void Gallery::StartLoad(const wxString &path) {
    if(GetThread())
        GetThread()->Delete();
    while(GetThread())
        wxThread::This()->Sleep(1);

    {
        wxCriticalSectionLocker lock(dir_path_cs);
        dir_path = path;
    }

    SetItemCount(0);
    image_queue.Clear();
    path_queue.Clear();
    previews.clear();
    image_pathes.Clear();

    if(CreateThread(wxTHREAD_DETACHED) != wxTHREAD_NO_ERROR) {
        wxLogError("Create loading thread failed!");
        return;
    }

    if(GetThread()->Run() != wxTHREAD_NO_ERROR) {
        wxLogError("Start loading thread failed!");
        return;
    }
}

void Gallery::StopLoad() {
    if(GetThread()) {
        GetThread()->Delete();
    }
    while (GetThread())
        wxThread::This()->Sleep(1);

}

wxThread::ExitCode Gallery::Entry() {

    wxArrayString pathes;
    if(pathes.size())
        pathes.clear();

    {
        wxCriticalSectionLocker lock(dir_path_cs);
        for( auto spec : image_spec)
            wxDir::GetAllFiles(dir_path, &pathes, spec, wxDIR_FILES | wxDIR_HIDDEN );
    }

    // Send Start event
    wxThreadEvent event(pxEVT_PROGRESS_START);
    event.SetExtraLong(pathes.size());
    wxQueueEvent(this->GetEventHandler(), event.Clone());

    wxImage image;
    for(size_t i = 0; i < pathes.size() ; i++ ) {
        // Make sure the image is readable
        if(wxImage::CanRead(pathes[i]))
            image.LoadFile(pathes[i], wxBITMAP_TYPE_ANY);
            if(image.IsOk()) {
                //Make image fit to gallery
                wxSize gsize = GetFitSize(image.GetSize());
                int w = gsize.GetWidth();
                int h = gsize.GetHeight();
                image.Rescale(w,h);
                //put them in transfer queue
                image_queue<<image;
                path_queue<<pathes[i];
                //send image loaded event
                event.SetEventType(pxEVT_IMAGE_LOADED);
                event.SetExtraLong(i);
                wxQueueEvent(this->GetEventHandler(), event.Clone());
            }
            else {
                event.SetEventType(pxEVT_PROGRESS_UPDATE);
                event.SetExtraLong(i);
                wxQueueEvent(this->GetEventHandler(), event.Clone());
        }
        if(GetThread()->TestDestroy())
            break;
    }
    event.SetEventType(pxEVT_PROGRESS_COMPLETE);
    wxQueueEvent(this->GetEventHandler(), event.Clone());
    return wxThread::ExitCode(0);
}

const wxString& Gallery::GetSelectImagePath() {
    return image_pathes[GetSelection()];
}

const wxString &Gallery::GetDirPath()
{
    wxCriticalSectionLocker lock(dir_path_cs);
    return dir_path;
}

wxSize Gallery::GetFitSize(const wxSize &size) {
    int w = size.GetWidth();
    int h = size.GetHeight();
    int bw = bitmap_size.GetWidth();
    int bh = bitmap_size.GetHeight();
    wxDouble wscale = wxDouble(bw)/wxDouble(w);
    wxDouble hscale = wxDouble(bh)/wxDouble(h);
    wxDouble scale = (wscale < hscale) ? wscale : hscale;
    return wxSize(w*scale, h*scale);
}

void Gallery::SendProgressStatus(wxEventType type, const wxString &info, size_t n)
{
    wxCommandEvent event(type);
    event.SetId(GetId());
    event.SetExtraLong(n);
    event.SetString(info);
    wxQueueEvent(GetParent(), event.Clone());
}
