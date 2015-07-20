cmake_minimum_required(VERSION 3.0)

set (PROJECT QSLOG)

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

target_link_libraries( ${PROJECT} Qt5::Widgets )



