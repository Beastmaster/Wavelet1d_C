message("seek to qt serial port")
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ECG)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

include_directories(${PROJECT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
add_subdirectory(serialport)

add_library(wavelet_c wavelet.c wavelet.h)
add_library(wavelet_cpp Wavelet.cpp Wavelet.hpp)


add_executable(ECG main.cpp)
target_link_libraries(ECG qexserialport wavelet_c wavelet_cpp)

