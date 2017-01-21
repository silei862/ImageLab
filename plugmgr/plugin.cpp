// File	    : plugin.cpp
// Author	: Silei
// Descr	: plugin related utility


#include "plugin.h"

wxDEFINE_EVENT(plugEVT_IMAGE, plugImageEvent);
wxDEFINE_EVENT(plugEVT_REQUEST_IMAGE, wxCommandEvent);
wxDEFINE_EVENT(plugEVT_NEW_IMAGE, wxCommandEvent);

void ImagePlugin::RequestImage() {
    if(handler)
        wxQueueEvent(handler, new wxCommandEvent(plugEVT_REQUEST_IMAGE));
}

void ImagePlugin::SendImageByEvent(const wxImage &image) {
    plugImageEvent event;
    event.SetImage(image);
    wxQueueEvent(handler, event.Clone());
}

void ImagePlugin::SendImage(const wxImage &img) {
   image = img;
   wxQueueEvent(handler, new wxCommandEvent(plugEVT_NEW_IMAGE));
}

void ImagePlugin::OnImageRecived(plugImageEvent &event) {
    image = event.GetImage();
    this->ImageRecived();
}

void ImagePlugin::SetImage(const wxImage &img)
{
    image = img;
    this->ImageRecived();
}
