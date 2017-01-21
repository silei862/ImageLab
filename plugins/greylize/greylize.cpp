// File	    : greylize.cpp
// Author	: Silei
// Descr	: greylize plugin, design plugin gui by wxFormbuilder

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <cvbridge.h>
#include "greylize.h"

const wxString GreylizePane::FormatStr = "%.3f%%";

GreylizePane::GreylizePane(wxWindow *parent, ImagePlugin *plug, wxWindowID id)
    :GreylizePaneBase(parent, id),
      ImagePluginAgent(plug){

}

void GreylizePane::OnRedThumbRelease(wxScrollEvent &event)
{
    int red, green, blue, max_value;
    GetSliderValue(red, green, blue, max_value);

    if(green_check->IsChecked()){ // green locked
        if(LimitValue(max_value - green, red, blue))
            red_slider->SetValue(red);
        blue_slider->SetValue(blue);
    } else { // blue locked
        if(LimitValue(max_value - blue, red, green))
            red_slider->SetValue(red);
        green_slider->SetValue(green);
    }
    UpdateValue(red, green, blue);
}

void GreylizePane::OnGreenThumbRelease(wxScrollEvent &event)
{
    int red, green, blue, max_value;
    GetSliderValue(red, green, blue, max_value);

    if(red_check->IsChecked()){ // red locked
        if(LimitValue(max_value - red, green, blue))
            green_slider->SetValue(green);
        blue_slider->SetValue(blue);
    } else { // blue locked
        if(LimitValue(max_value - blue, green, red))
            green_slider->SetValue(green);
        red_slider->SetValue(red);
    }
    UpdateValue(red, green, blue);
}

void GreylizePane::OnBlueThumbRelease(wxScrollEvent &event)
{
    int red, green, blue, max_value;
    GetSliderValue(red, green, blue, max_value);

    if(green_check->IsChecked()){ // green locked
        if(LimitValue(max_value - green, blue, red))
            blue_slider->SetValue(blue);
        red_slider->SetValue(red);
    } else { // red locked
        if(LimitValue(max_value - red, blue, green))
            blue_slider->SetValue(blue);
        green_slider->SetValue(green);
    }
    UpdateValue(red, green, blue);
}


void GreylizePane::OnRedCheckChanged(wxCommandEvent &event)
{
   if(red_check->IsChecked()){
       red_slider->Disable();
       green_slider->Enable();
       blue_slider->Enable();
       green_check->SetValue(false);
       blue_check->SetValue(false);
   }
}

void GreylizePane::OnGreenCheckChanged(wxCommandEvent &event)
{
    if(green_check->IsChecked()){
        green_slider->Disable();
        red_slider->Enable();
        blue_slider->Enable();
        red_check->SetValue(false);
        blue_check->SetValue(false);
    }
}

void GreylizePane::OnBlueCheckChanged(wxCommandEvent &event)
{
   if(blue_check->IsChecked()){
       blue_slider->Disable();
       red_slider->Enable();
       green_slider->Enable();
       red_check->SetValue(false);
       green_check->SetValue(false);
   }
}

void GreylizePane::GetSliderValue(int &r, int &g, int &b, int &max)
{
    r = red_slider->GetValue();
    g = green_slider->GetValue();
    b = blue_slider->GetValue();
    max = red_slider->GetMax();
}

void GreylizePane::UpdateValue(int r, int g, int b)
{
    int max_value = red_slider->GetMax();
    wxString redval, greenval, blueval;
    redval.Printf(FormatStr, wxDouble(r)/wxDouble(max_value));
    greenval.Printf(FormatStr, wxDouble(g)/wxDouble(max_value));
    blueval.Printf(FormatStr, wxDouble(b)/wxDouble(max_value));

    redval_text->SetLabelText(redval);
    greenval_text->SetLabelText(greenval);
    blueval_text->SetLabelText(blueval);
}

bool GreylizePane::LimitValue(int sum, int &active, int &passive)
{
    int prepassive = sum - active;
    if(prepassive < 0) {
        passive = 0;
        active = sum;
        return true;
    } else {
        passive = prepassive;
        return false;
    }
}

void GreylizePane::Convert()
{
    wxImage image = GetImage();
    origin = image;
    int w = image.GetWidth();
    int h = image.GetHeight();
    unsigned char *img_data = image.GetData();

    int red, green, blue, max;
    GetSliderValue(red, green, blue, max);

    wxDouble w_red = wxDouble(red)/wxDouble(max);
    wxDouble w_green = wxDouble(green)/wxDouble(max);
    wxDouble w_blue = wxDouble(blue)/wxDouble(max);

    for(int i = 0; i < w*h; i++ ){
        int val = img_data[i*3]*w_red + img_data[i*3 + 1]*w_green + img_data[i*3 + 2]*w_blue;
        val = (val > 255) ? 255 : val;
        img_data[i*3] = val;
        img_data[i*3 + 1] = val;
        img_data[i*3 + 2] = val;
    }

    if(eqhist_check->IsChecked()) {
        cv::Mat mat, grey_mat, eq_mat;
        image>>mat;
        cv::cvtColor(mat, grey_mat, CV_RGB2GRAY);
        cv::equalizeHist(grey_mat, eq_mat);
        eq_mat>>image;
    }
    SendImage(image);
}

DEFINE_PLUGIN_CREATOR(GreylizePlugin)
