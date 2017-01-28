// File	    : canny.h
// Author	: Silei
// Descr	: canny plugin, design plugin gui by wxFormbuilder

#include "canny.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <cvbridge.h>

CannyGUI::CannyGUI(wxWindow *parent, Plugin *plug, wxWindowID id)
    :CannyGUIBase(parent, id), PluginHelper(plug){

    for(int val = 3; val < 8; val += 2)
        kernelsize_combo->Append(wxString::Format("%d x %d", val, val));
    kernelsize_combo->SetSelection(0);
}

void CannyGUI::OnLowScroll(wxScrollEvent &event){
    int val = low_slider->GetValue();
    lowthreshold_text->SetLabelText(wxString::Format("%d",val));
}

void CannyGUI::OnRatioScroll(wxScrollEvent &event){
    wxDouble val = wxDouble(ratio_slider->GetValue())*5.0;
    val /= wxDouble(ratio_slider->GetMax());
    ratio_text->SetLabelText(wxString::Format("%.1f",val));
}

void CannyGUI::OnApply(wxCommandEvent &event){
    wxImage image = GetImage().Copy();

    // Get all paramenter:
    double low_threshold = double(low_slider->GetValue());
    double ratio = double(ratio_slider->GetValue())*5.0;
    ratio /= double(ratio_slider->GetMax());
    double high_threshold = low_threshold * ratio;

    int ksize = kernelsize_combo->GetSelection()*2+3;

    bool l2gradient = usel2_check->IsChecked();

    cv::Mat mat, edges;
    image >> mat;
    cv::Canny(mat, edges, low_threshold, high_threshold, ksize, l2gradient );

    if(revert_check->IsChecked()){
        cv::Mat redges;
        cv::bitwise_not(edges, redges);
        redges >> image;
    } else
        edges >>image;

    wxString cap = GetCurrentPageText() + "[edge]";
    AddImage(image, cap);
}
