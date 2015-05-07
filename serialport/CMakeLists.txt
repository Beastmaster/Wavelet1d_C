message("seek to qt serial port")
cmake_minimum_required(VERSION 2.8)
 
PROJECT(qexserialport)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

#qt .ui files
#set(QT_UI_FILES
#${FMRI_MODULE_ui_dir}/Dialog_Paradigm_Advance.ui
#)

#qt .h files
set(QT_HEAD_FILES
qextserialbase.h
qextserialport.h
win_qextserialport.h
)

#qt .cxx files
SET(QT_CXX_FILES
qextserialbase.cpp
qextserialport.cpp
win_qextserialport.cpp
)

QT4_WRAP_UI(UISrcs ${UI_FILES})
QT4_WRAP_CPP(MOCSrcs ${QT_HEAD_FILES})
add_library(qexserialport ${QT_CXX_FILES} ${UISrcs} ${MOCSrcs} ${QT_HEAD_FILES})

