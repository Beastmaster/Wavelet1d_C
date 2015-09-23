message("seek to qt serial port")
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ECG)

find_package(Qt4 REQUIRED)
FIND_PACKAGE(Qwt REQUIRED)

include(${QT_USE_FILE})
#for qwt configuration
include_directories(${QWT_INCLUDE_DIRS})


include_directories(
${PROJECT_SOURCE_DIR} 
${CMAKE_CURRENT_SOURCE_DIR} 
${CMAKE_CURRENT_BINARY_DIR}
)
include_directories(
serialport
window
)
add_subdirectory(serialport)
add_subdirectory(window)

add_library(wavelet_c wavelet.c wavelet.h)
add_library(wavelet_cpp Wavelet.cpp Wavelet.hpp)


add_executable(ECG main.cpp)
target_link_libraries(ECG qexserialport wavelet_c wavelet_cpp window)
TARGET_LINK_LIBRARIES(ECG ${QT_LIBRARIES})
#for qwt configuration
TARGET_LINK_LIBRARIES(ECG ${QWT_LIBRARIES})

