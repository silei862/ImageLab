project(ImageLab)

cmake_minimum_required(VERSION 2.8)

find_package(wxWidgets REQUIRED core base aui xrc adv html)
find_package(OpenCV REQUIRED)

add_subdirectory(utils)
add_subdirectory(guictrl)
add_subdirectory(plugmgr)
add_subdirectory(gui)

add_subdirectory(plugins)
