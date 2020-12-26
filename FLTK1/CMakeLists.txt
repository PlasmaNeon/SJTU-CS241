cmake_minimum_required(VERSION 3.17)
project(hwFLTK)

set(CMAKE_CXX_STANDARD 20)

add_executable(part1
        main1.cpp
        revised-gui/Graph.cpp
        revised-gui/Graph.h
        revised-gui/GUI.cpp
        revised-gui/GUI.h
        revised-gui/Point.h
        revised-gui/Simple_window.cpp
        revised-gui/Simple_window.h
        revised-gui/std_lib_facilities.h
        revised-gui/Window.cpp
        revised-gui/Window.h
        hyperelliptic.h
        hyperelliptic.cpp

        )


find_package(FLTK REQUIRED)
#find_package(OpenGL REQUIRED)
include_directories(${FLTK_INCLUDE_DIR})

target_link_libraries(part1 ${FLTK_LIBRARIES})
#target_link_libraries(part1 ${OPENGL_LIBRARIES})
#target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})