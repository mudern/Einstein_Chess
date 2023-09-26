cmake_minimum_required(VERSION 3.25)
project(Einstein_Chess)

set(CMAKE_CXX_STANDARD 17)

#声明FLTK头文件路径
set(INC_DIR_FLTK ./fltk_x64-windows/include)

#声明FLTK链接库路径
set(LINK_DIR_FLTK ./fltk_x64-windows/lib)

#引入FLTK头文件
include_directories(${INC_DIR_FLTK})

#引入FLTK库文件
link_directories(${LINK_DIR_FLTK})

#声明ChessPiece头文件路径
set(INC_DIR_CHESS_PIECE ./ChessPiece)

#引入ChessPiece头文件
include_directories(${INC_DIR_CHESS_PIECE})

add_executable(Einstein_Chess main.cpp)

#将第三方库链接在一起
target_link_libraries(Einstein_Chess libfltk_forms.a libfltk.a libfltk_gl.a libfltk_images.a libcomctl32.a)