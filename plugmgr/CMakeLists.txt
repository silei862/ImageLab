set(LIB_NAME "plugmgr")
aux_source_directory(. SRC_LIST)

if(UNIX)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif(UNIX)

include(${wxWidgets_USE_FILE})
add_library(${LIB_NAME} ${SRC_LIST})
set_property(TARGET ${LIB_NAME} PROPERTY CXX_STANDARD 11)
