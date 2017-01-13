#include "cvbridge.h"
#include <iostream>

inline void RGB2BGR(const unsigned char* RGBData,
                    unsigned char* BGRData,
                    int len){
    for(int i=0;i<len;i++){
        BGRData[i*3]    =RGBData[i*3+2];
        BGRData[i*3+1]  =RGBData[i*3+1];
        BGRData[i*3+2]  =RGBData[i*3];
    }
}

inline void BGR2RGB(const unsigned char* BGRData,
                    unsigned char* RGBData,
                    int len){
    RGB2BGR(BGRData,RGBData,len);
}

inline void Gray2RGB(const unsigned char* GreyData,
                     unsigned char* RGBData,
                     int len){
    for(int i=0;i<len;i++){
        RGBData[i*3]    =GreyData[i];
        RGBData[i*3+1]  =GreyData[i];
        RGBData[i*3+2]  =GreyData[i];
    }
}

void wxImage2cvMat(const wxImage& img , cv::Mat& mat){
    int width=img.GetWidth();
    int height=img.GetHeight();
    mat.create(height,width,CV_8UC3);
    unsigned char* wxImg=img.GetData();

    for(int j=0;j<height;j++){
        unsigned char* wxRow=wxImg+j*width*3;
        uchar* cvRow=mat.ptr<uchar>(j);
        RGB2BGR(wxRow,cvRow,width);
    }
}

void cvMat2wxImage(const cv::Mat& mat , wxImage& img){
    int width=mat.cols;
    int height=mat.rows;
    img.Create(width,height);
    unsigned char* wxImg=img.GetData();

    int channels=mat.channels();

    switch(channels) {
    case 1:
        for(int j=0;j<height;j++){
            unsigned char* wxRow=wxImg+j*width*3;
            const uchar* cvRow=mat.ptr(j);
            Gray2RGB(cvRow,wxRow,width);
        }
        break;
    case 3:
        for(int j=0;j<height;j++){
           unsigned char* wxRow=wxImg+j*width*3;
           const uchar* cvRow=mat.ptr(j);
           BGR2RGB(cvRow,wxRow,width);
        }
        break;
    default:
        return;
    }
}

cv::Mat& operator>>(const wxImage& img , cv::Mat& mat){
    wxImage2cvMat(img,mat);
    return mat;
}

wxImage& operator>>(const cv::Mat& mat , wxImage& img){
    cvMat2wxImage(mat,img);
    return img;
}
