


#include <wx/panel.h>
#include <wx/image.h>
#include <wx/button.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include "cvbridge.h"
#include "graylize.h"


GraylizePane::GraylizePane(wxWindow *parent, GraylizePlugin *plug, wxWindowID id)
    :wxPanel(parent, id),
      plugin(plug){

    wxSizer *main_sizer = new wxBoxSizer(wxVERTICAL);

    { //================Plugin Control====================
        wxSizer *plugctrl_sizer = new wxBoxSizer(wxHORIZONTAL);

        wxButton *apply_btn = new wxButton(this, ID_APPLY, _("Apply"));
        plugctrl_sizer->Add(apply_btn, 1, wxALIGN_CENTER_VERTICAL | wxALL, 5);

        plugctrl_sizer->Add(0, 0, 1, wxEXPAND, 5);

        wxButton *cancel_btn = new wxButton(this, ID_CANCEL, _("Cancel"));
        plugctrl_sizer->Add(cancel_btn, 1, wxALIGN_CENTER_VERTICAL | wxALL, 5);

        main_sizer->Add(plugctrl_sizer, 0, wxALL, 5);
    }

    SetSizer(main_sizer);
    Layout();

    //====================Bind Event Proc==================
    Bind(wxEVT_COMMAND_BUTTON_CLICKED, &GraylizePane::OnApply, this, ID_APPLY);
    Bind(wxEVT_COMMAND_BUTTON_CLICKED, &GraylizePane::OnCancel, this, ID_CANCEL);
}

GraylizePane::~GraylizePane(){

}

void GraylizePane::Excute() {
    origin = plugin->GetImage();
    if(!origin.IsOk()) {
        wxLogError("origin Image broken!");
        return;
    }
    wxImage result;
    cv::Mat normal, gray;
    origin>>normal;
    cv::cvtColor(normal, gray, CV_RGB2GRAY);
    gray>>result;
    plugin->SendImage(result);
}

void GraylizePane::OnApply(wxCommandEvent &event) {
    plugin->RequestImage();
}

void GraylizePane::OnCancel(wxCommandEvent &event) {
    plugin->SendImage(origin);
}

DEFINE_PLUGIN_CREATOR(GraylizePlugin)

wxWindow* GraylizePlugin::GetWindow(wxWindow *parent, wxWindowID id) {
    pane = new GraylizePane(parent, this, id);
    return pane;
}

void GraylizePlugin::ImageRecived(){
    pane->Excute();
}
