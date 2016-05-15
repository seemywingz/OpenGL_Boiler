cmake_minimum_required(VERSION 3.1)
project(square)
include_directories( ./include )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
link_directories( dll )
link_libraries( glfw3 glew32 opengl32 )

set(SOURCE_FILES main.cpp)
add_executable(square ${SOURCE_FILES} Square.h)