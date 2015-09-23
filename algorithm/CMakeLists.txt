message("seek to qt serial port")
cmake_minimum_required(VERSION 2.8)


PROJECT(wavelet_algorithm)

add_library(firwin firwin.c firwin.h)
add_library(wavelet_c wavelet.c wavelet.h)
add_library(wavelet_cpp Wavelet.cpp Wavelet.hpp)

include_directories(
${CMAKE_CURRENT_SOURCE_DIR} 
)

#test files
option(enable_test "Test wavelet algorithm?" "ON")
if(${enable_test} STREQUAL "ON")
add_executable(wavelet_algorithm test.cpp)
target_link_libraries(wavelet_algorithm wavelet_c wavelet_cpp firwin)
endif()