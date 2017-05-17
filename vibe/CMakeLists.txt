cmake_minimum_required(VERSION 2.8)

project(main)

find_package(OpenCV REQUIRED)

include_directories(${OPENCV_INCLUDE_DIRS})


add_executable(main src/main-opencv.cpp src/vibe-background-sequential.c)  
target_link_libraries(main ${OpenCV_LIBS})  

