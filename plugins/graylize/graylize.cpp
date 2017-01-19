// File	    : graylize.cpp
// Author	: Silei
// Descr	: graylize plugin

#include <wx/panel.h>
#include <wx/image.h>
#include <wx/button.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include "cvbridge.h"
#include "graylize.h"


GraylizePane::GraylizePane(wxWindow *parent, ImagePlugin *plug, wxWindowID id)
    :PluginGUI(parent, plug, id){

    wxSizer *main_sizer = new wxBoxSizer(wxVERTICAL);

    grey_eq = new wxCheckBox(this, wxID_ANY, _("Grey level equaliztion"));
    main_sizer->Add(grey_eq, 0, wxALL, 5);

    { //================ Button group ====================
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
    origin = GetPlugin()->GetImage();
    //>>>>>> For debug
    if(!origin.IsOk()) {
        wxLogError("origin Image broken!");
        return;
    }
    //<<<<<<<

    wxImage result;
    cv::Mat normal, gray;
    origin>>normal;
    cv::cvtColor(normal, gray, CV_RGB2GRAY);

    //need equaliztion?
    if(grey_eq->IsChecked()) {
        cv::Mat gray_eq;
        cv::equalizeHist(gray, gray_eq);
        gray_eq>>result;
    } else
        gray>>result;
    GetPlugin()->SendImage(result);
}

void GraylizePane::OnApply(wxCommandEvent &event) {
    GetPlugin()->RequestImage();
}

void GraylizePane::OnCancel(wxCommandEvent &event) {
    GetPlugin()->SendImage(origin);
}

DEFINE_PLUGIN_CREATOR(GraylizePlugin)

wxWindow* GraylizePlugin::GetWindow(wxWindow *parent, wxWindowID id) {
    pane = new GraylizePane(parent, this, id);
    return pane;
}

void GraylizePlugin::ImageRecived(){
    pane->Excute();
}
