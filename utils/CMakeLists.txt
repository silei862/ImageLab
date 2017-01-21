set(LIB_NAME "utils")
aux_source_directory(. SRC_LIST)

include(${wxWidgets_USE_FILE})
include_directories(${OpenCV_INCLUDE_DIRS})

if(UNIX OR MINGW)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif(UNIX OR MINGW)

add_library(${LIB_NAME} ${SRC_LIST})
set_property(TARGET ${LIB_NAME} PROPERTY CXX_STANDARD 11)
