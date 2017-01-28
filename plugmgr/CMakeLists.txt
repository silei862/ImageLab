set(LIB_NAME "plugmgr")
aux_source_directory(. SRC_LIST)

if(UNIX OR MINGW)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif(UNIX OR MINGW)

include(${wxWidgets_USE_FILE})
include_directories(../guictrl)
add_library(${LIB_NAME} ${SRC_LIST})
target_link_libraries(guictrl)
set_property(TARGET ${LIB_NAME} PROPERTY CXX_STANDARD 11)
