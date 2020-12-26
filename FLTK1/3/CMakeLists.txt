cmake_minimum_required(VERSION 3.17)
project(3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(3
        Binary_tree.cpp
        Binary_tree.h
        main3.cpp
        TriangleBinary_tree.cpp
        TriangleBinary_tree.h
        Graph.cpp
        Graph.h
        GUI.cpp
        GUI.h
        Point.h
        Simple_window.cpp
        Simple_window.h
        std_lib_facilities.h
        Window.cpp
        Window.h
        )

find_package(FLTK REQUIRED)
include_directories(${FLTK_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${FLTK_LIBRARIES})