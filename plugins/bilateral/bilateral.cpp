
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <cvbridge.h>
#include "bilateral.h"

BilateralPane::BilateralPane(wxWindow *parent, Plugin *plug, wxWindowID id)
        :BilateralBase(parent, id), PluginHelper(plug),
          colorsigma_vali(1, &color_sigma), spacesigma_vali(1, &space_sigma)
{
    colorsigma_text->SetValidator(colorsigma_vali);
    spacesigma_text->SetValidator(spacesigma_vali);
    color_sigma=9.527;
    space_sigma=0.9527;
}

void BilateralPane::OnApply(wxCommandEvent &event)
{
    wxImage image = GetImage().Copy();

    //prepare parameters:
    int d = filtersize_spin->GetValue();
    double cf_sigma, sp_sigma;
    if(!colorsigma_text->GetValue().ToDouble(&cf_sigma))
        cf_sigma = 10.0;
    if(!spacesigma_text->GetValue().ToDouble(&sp_sigma))
        sp_sigma = 5.0;
    cv::Mat img, rimg;
    image>>img;
    cv::bilateralFilter(img, rimg, d, cf_sigma, sp_sigma);
    rimg>>image;

    AddImage(image, GetCurrentPageText() + "[bfiltered]");
}
