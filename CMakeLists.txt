PROJECT(PixeLab)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

IF(WIN32)
    SET(wxWidgets_ROOT_DIR "D:/apps/wxWidgets-3.1.0")
    SET(wxWidgets_LIB_DIR "D:/apps/wxWidgets-3.1.0/lib/vc_dll")
ENDIF(WIN32)
FIND_PACKAGE(wxWidgets REQUIRED core base aui)

FIND_PACKAGE(OpenCV REQUIRED)

ADD_SUBDIRECTORY(utils)
ADD_SUBDIRECTORY(imgproc)
ADD_SUBDIRECTORY(gui)
