cmake_minimum_required(VERSION 3.25)
project(fltk_learn)

set(CMAKE_CXX_STANDARD 17)

#声明头文件路径
set(INC_DIR ./fltk_x64-windows/include)

#声明链接库路径
set(LINK_DIR ./fltk_x64-windows/lib)

#引入头文件
include_directories(${INC_DIR})

#引入库文件
link_directories(${LINK_DIR})

add_executable(fltk_learn main.cpp)

#将第三方库链接在一起
target_link_libraries(fltk_learn libfltk_forms.a libfltk.a libfltk_gl.a libfltk_images.a libcomctl32.a)



#find_package(FLTK REQUIRED)find_package(FLTK REQUIRED)
#include_directories(${FLTK_INCLUDE_DIRS})
#
#add_executable(fltk_learn main.cpp)
#target_link_libraries(fltk_learn ${FLTK_LIBRARIES})