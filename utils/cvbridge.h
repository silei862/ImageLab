#ifndef CVBRIDGE_H
#define CVBRIDGE_H

#include <wx/image.h>
#include <opencv/cv.h>

void wxImage2cvMat(const wxImage& img , cv::Mat& mat);
void cvMat2wxImage(const cv::Mat& mat , wxImage& img);

cv::Mat& operator>>(const wxImage& img , cv::Mat& mat);
wxImage& operator>>(const cv::Mat& mat , wxImage& img);

#endif // CVBRIDGE_H

