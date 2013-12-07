cmake_minimum_required (VERSION 2.8.11)

set (PROJECT EPol)

project (${PROJECT})

#-------------QT--------------------------------------

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets)
#-----------------------------------------------------


include_directories (.)
include_directories (./ui)
include_directories (./patterns)
include_directories (./calculations)
include_directories (./calculations/curves)
include_directories (./gauss)

add_subdirectory(gauss)

if(CMAKE_COMPILER_IS_GNUCC)
add_definitions (-Wall -pedantic -std=gnu++11 -g)
endif()

set (HEADERS 
  ./calculations/calc_manager.h 
  ./calculations/types.h
  ./calculations/given.h
  ./calculations/field_solver.h
  ./calculations/helper.h
  ./calculations/array.h
  ./calculations/discretization.h
  ./calculations/incident_field.h
  ./calculations/incident_field.h
  ./patterns/prototype.h
  ./patterns/singleton.h
)
set (SOURCES 
    ./main.cpp
    ./calculations/field_solver.cpp
    ./calculations/curves/curve.cpp
    ./calculations/curves/discretize_curve.cpp
    ./calculations/helper.cpp
    ./calculations/given.cpp
    ./calculations/calc_manager.cpp 
    ./calculations/discretization.cpp
    ./calculations/incident_field.cpp
    ./ui/json_ui.cpp
)

source_group ("Header Files" FILES ${HEADERS})
source_group ("Source Files" FILES ${SOURCES})

add_executable (${PROJECT} ${HEADERS} ${SOURCES})


target_link_libraries(${PROJECT} Qt5::Widgets)
