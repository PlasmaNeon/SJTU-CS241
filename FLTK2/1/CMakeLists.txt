cmake_minimum_required(VERSION 3.17)
project(1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(1
        BarChart.cpp
        BarChart.h
        Graph.cpp
        Graph.h
        GUI.cpp
        GUI.h
        main1.cpp
        Point.h
        Simple_window.cpp
        Simple_window.h
        std_lib_facilities.h
        Window.cpp
        Window.h)

find_package(FLTK REQUIRED)
include_directories(${FLTK_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${FLTK_LIBRARIES})
