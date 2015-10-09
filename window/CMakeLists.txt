message("seek to qt window dir")
cmake_minimum_required(VERSION 2.8)
Project(window)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
#qt .ui files
set(QT_UI_FILES
MainWindow.ui
)

#qt .h files
set(QT_HEAD_FILES
MainWindow.h
)

#qt .cxx files
SET(QT_CXX_FILES
MainWindow.cpp
)

QT4_WRAP_UI(UISrcs ${QT_UI_FILES})
QT4_WRAP_CPP(MOCSrcs ${QT_HEAD_FILES})
add_library(window ${QT_CXX_FILES} ${UISrcs} ${MOCSrcs} ${QT_HEAD_FILES})