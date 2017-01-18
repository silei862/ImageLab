project(PixeLab)

cmake_minimum_required(VERSION 2.8)

if(MINGW)
    set(OpenCV_INSTALL_PATH /home/silei/.local/x86_64-w64-mingw32)
endif(MINGW)

find_package(wxWidgets REQUIRED core base aui xrc)

find_package(OpenCV REQUIRED)

add_subdirectory(utils)
add_subdirectory(plugmgr)
add_subdirectory(plugins)
add_subdirectory(gui)
