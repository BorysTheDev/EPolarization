cmake_minimum_required (VERSION 2.6.4)

set (PROJECT EPol)

project (${PROJECT})

FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

include_directories (.)
include_directories (./gui)
include_directories (./calculations)
include_directories (./mt)

add_subdirectory(gui)
add_subdirectory(mt)

if (MSVC)
	add_definitions (/W4)
elseif (CMAKE_COMPILER_IS_GNUCXX)
	add_definitions (-Wall -pedantic -std=gnu++11)
else ()
	message ("Unknown compiler")
endif ()

set (HEADERS 
  ./calculations/calc_manager.h 
  ./calculations/helper.h
  ./calculations/array.h
  ./calculations/matrix.h
  ./calculations/curve.h
 ./calculations/discretization.h
 ./calculations/incident_field.h
 ./calculations/incident_field_package.h
 ./calculations/equation_matrix_solver.h
 ./mt/thread.h
)
set (SOURCES ./main.cpp)

source_group ("Header Files" FILES ${HEADERS})
source_group ("Source Files" FILES ${SOURCES})

add_executable (${PROJECT} ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT} qts)
target_link_libraries(${PROJECT} ${QT_LIBRARIES})
