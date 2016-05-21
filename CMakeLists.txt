cmake_minimum_required(VERSION 3.1)
project(square)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if (WIN32)
    include_directories( include )
    link_directories( win32/dll )
    link_libraries( glfw3 glew32 opengl32 )

    set(SOURCE_FILES main.cpp Square.h Position.h)
    add_executable(square ${SOURCE_FILES})
#    target_link_libraries( square glew32)
endif (WIN32)

#if (APPLE)
#    find_package(GLEW REQUIRED)
#    if (GLEW_FOUND)
#        include_directories(${GLEW_INCLUDE_DIRS})
#        link_libraries(${GLEW_LIBRARIES})
#    endif()
#
#    add_subdirectory(vendor/glfw)
#    include_directories(vendor/glfw/include)
#    target_link_libraries(square glfw ${GLFW_LIBRARIES} ${OPENGL_gl_LIBRARY})
#endif (APPLE)


