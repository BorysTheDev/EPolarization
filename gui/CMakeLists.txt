cmake_minimum_required(VERSION 2.6.4)

#PROJECT (qts C CXX)
FIND_PACKAGE(Qt4 REQUIRED)

set(CMAKE_CXX_FLAGS "-g -O2 -std=gnu++11 -Wall")

SET(qts_SOURCES 
  main_window.cpp)

SET(qts_HEADERS 
  main_window.h)

SET(qts_RESOURCES gui.qrc)

QT4_WRAP_CPP(qts_HEADERS_MOC ${qts_HEADERS})
QT4_ADD_RESOURCES(qts_RESOURCES_RCC ${qts_RESOURCES})

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

include_directories(${CMAKE_SOURCE_DIR}/calculation)
include_directories(${CMAKE_SOURCE_DIR})

ADD_LIBRARY( qts ${qts_HEADERS_MOC} ${qts_SOURCES})



