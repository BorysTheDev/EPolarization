cmake_minimum_required (VERSION 2.8)

set (PROJECT EPol)

project (${PROJECT})

#FIND_PACKAGE(Qt4 REQUIRED)
#INCLUDE(${QT_USE_FILE})
#ADD_DEFINITIONS(${QT_DEFINITIONS})

include_directories (.)
include_directories (./curves)
#include_directories (./gui)
include_directories (./calculations)
#include_directories (./mt)
include_directories (./gauss)

#add_subdirectory(gui)
add_subdirectory(gauss)

if(CMAKE_COMPILER_IS_GNUCC)
add_definitions (-Wall -pedantic -std=gnu++11 -O2 -fopenmp)
endif()

set (HEADERS 
  ./types.h

  ./curves/curve.h
  ./curves/ellipse.h
  ./curves/cubic_spline.h
  ./curves/discretize_curve.h

  ./calculations/calc_manager.h 

  ./calculations/given.h
  ./calculations/field_solver.h
  ./calculations/helper.h
  ./calculations/discretization.h
  ./calculations/incident_field.h
  ./calculations/incident_field_package.h

  ./hpolarization/h_core.h

  ./math/hankel.h
  ./math/simple_math.h
)

set (SOURCES 
  ./curves/curve.cpp
  ./curves/ellipse.cpp
  ./curves/cubic_spline.cpp

  ./main.cpp
  ./calculations/field_solver.cpp

  ./calculations/helper.cpp
  ./calculations/given.cpp
  ./calculations/calc_manager.cpp
  ./calculations/discretization.cpp
  ./calculations/incident_field.cpp
  ./calculations/incident_field_package.cpp

 ./hpolarization/h_core.cpp
)

source_group ("Header Files" FILES ${HEADERS})
source_group ("Source Files" FILES ${SOURCES})

add_executable (${PROJECT} ${HEADERS} ${SOURCES})

#target_link_libraries(${PROJECT} qts)
if(CMAKE_COMPILER_IS_GNUCC)
  target_link_libraries(${PROJECT} pthread libgomp-1)
endif()
#target_link_libraries(${PROJECT} ${QT_LIBRARIES})
