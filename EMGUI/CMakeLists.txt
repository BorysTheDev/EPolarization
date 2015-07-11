cmake_minimum_required(VERSION 3.0)

set (PROJECT EMGUI)

project (${PROJECT})

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)

find_package(Qt5Widgets REQUIRED)

set ( CMAKE_INCLUDE_CURRENT_DIR ON )


include_directories (.)


if(CMAKE_COMPILER_IS_GNUCC)
add_definitions (-Wall -std=gnu++11 -O2)
endif()



set (HEADERS
  ./axis.h
  ./coor_converter.h
  ./ellipseparamform.h
  ./emgraphicsview.h
  ./lineparamform.h
  ./mainwindow.h
  ./scatterers.h
  ./scatterersparam.h
)

set (SOURCES
  ./axis.cpp
  ./coor_converter.cpp
  ./ellipseparamform.cpp
  ./emgraphicsview.cpp
  ./lineparamform.cpp
  ./main.cpp
  ./mainwindow.cpp
  ./scatterers.cpp
)

source_group ("Header Files" FILES ${HEADERS})
source_group ("Source Files" FILES ${SOURCES})

add_executable (${PROJECT} ${HEADERS} ${SOURCES})
target_link_libraries( ${PROJECT} Qt5::Widgets )



