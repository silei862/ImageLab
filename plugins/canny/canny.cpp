
#include "canny.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <cvbridge.h>

CannyGUI::CannyGUI(wxWindow *parent, ImagePlugin *plug, wxWindowID id)
    :CannyGUIBase(parent, id), ImagePluginAgent(plug){

    for(int val = 3; val < 8; val += 2)
        kernelsize_combo->Append(wxString::Format("%d", val));
    kernelsize_combo->SetSelection(0);
    cancel_button->Disable();
}

void CannyGUI::OnLowThumbRelease(wxScrollEvent &event){
    int val = low_slider->GetValue();
    lowthreshold_text->SetLabelText(wxString::Format("%d",val));
}

void CannyGUI::OnRatioThumbRelease(wxScrollEvent &event){
    wxDouble val = wxDouble(ratio_slider->GetValue())*5.0;
    val /= wxDouble(ratio_slider->GetMax());
    ratio_text->SetLabelText(wxString::Format("%.1f",val));
}

void CannyGUI::Execute(){
    origin = GetImage();
    wxImage image = origin;

    // Get all paramenter:
    double low_threshold = double(low_slider->GetValue());
    double ratio = double(ratio_slider->GetValue())*5.0;
    ratio /= double(ratio_slider->GetMax());
    double high_threshold = low_threshold * ratio;

    long ksize;
    if(!kernelsize_combo->GetStringSelection().ToLong(&ksize)) {
        ksize = 3;
    }

    bool l2gradient = usel2_check->IsChecked();

    cv::Mat mat, edges;
    image >> mat;
    cv::Canny(mat, edges, low_threshold, high_threshold, int(ksize), l2gradient );

    if(revert_check->IsChecked()){
        cv::Mat redges;
        cv::bitwise_not(edges, redges);
        redges >> image;
    } else
        edges >>image;

    SendImage(image);
    cancel_button->Enable();
}
