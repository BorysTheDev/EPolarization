cmake_minimum_required (VERSION 2.6.4)

set (PROJECT EPol)

project (${PROJECT})

#FIND_PACKAGE(Qt4 REQUIRED)
#INCLUDE(${QT_USE_FILE})
#ADD_DEFINITIONS(${QT_DEFINITIONS})

include_directories (.)
#include_directories (./gui)
include_directories (./calculations)
#include_directories (./mt)
include_directories (./gauss)

#add_subdirectory(gui)
add_subdirectory(gauss)

if(CMAKE_COMPILER_IS_GNUCC)
add_definitions (-Wall -pedantic -std=gnu++11)
endif()

set (HEADERS 
  ./calculations/calc_manager.h 
  ./calculations/types.h
  ./calculations/given.h
  ./calculations/field_solver.h
  ./calculations/helper.h
  ./calculations/array.h
  ./calculations/curve.h
 ./calculations/discretization.h
 ./calculations/incident_field.h
 ./calculations/incident_field_package.h
 #./mt/thread.h
 #./mt/parallelism.h
)
set (SOURCES 
    ./main.cpp
    ./calculations/field_solver.cpp
    ./calculations/curve.cpp
    ./calculations/helper.cpp
    ./calculations/given.cpp
    ./calculations/calc_manager.cpp 
    ./calculations/discretization.cpp
    ./calculations/incident_field.cpp
    ./calculations/incident_field_package.cpp
)

source_group ("Header Files" FILES ${HEADERS})
source_group ("Source Files" FILES ${SOURCES})

add_executable (${PROJECT} ${HEADERS} ${SOURCES})

#target_link_libraries(${PROJECT} qts)
#target_link_libraries(${PROJECT} pthread)
#target_link_libraries(${PROJECT} ${QT_LIBRARIES})
