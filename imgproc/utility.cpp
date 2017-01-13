// File   : utility.cpp
// Author : Silei
// Descr  : Provide basic utility for image process

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <wx/image.h>
#include "cvbridge.h"
#include "utility.h"

wxImage GrayLize(const wxImage &image){
    cv::Mat origin_image, gray_image, hist_image;
    image>>origin_image;
    cv::cvtColor(origin_image, gray_image, CV_RGB2GRAY );
    cv::equalizeHist(gray_image, hist_image);
    wxImage ret_image;
    hist_image>>ret_image;
    return ret_image;
}
