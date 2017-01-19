// File	    : plugin.cpp
// Author	: Silei
// Descr	: plugin related utility


#include "plugin.h"

wxDEFINE_EVENT(plugEVT_IMAGE, plugImageEvent);
wxDEFINE_EVENT(plugEVT_IMAGE_REQUEST, wxCommandEvent);

ImagePlugin::ImagePlugin(wxEvtHandler *hdl) {
    handler = hdl;
    Bind(plugEVT_IMAGE, &ImagePlugin::OnImageRecived, this);
}

void ImagePlugin::SetParentEvtHandler(wxEvtHandler *handler) {
    this->handler = handler;
}

void ImagePlugin::RequestImage() {
    if(handler)
        wxQueueEvent(handler, new wxCommandEvent(plugEVT_IMAGE_REQUEST));
}

void ImagePlugin::SendImage(const wxImage &image) {
    plugImageEvent event;
    event.SetImage(image);
    wxQueueEvent(handler, event.Clone());
}

void ImagePlugin::OnImageRecived(plugImageEvent &event) {
    image = event.GetImage();
    this->ImageRecived();
}

void ImagePlugin::ImageRecived() {

}
