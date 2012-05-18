cmake_minimum_required (VERSION 2.6)
project (Parallel_Ex2)


find_package(Boost COMPONENTS timer system chrono filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories ( ${Boost_LIBRARY_DIRS} )

include(FindOpenMP)
if(OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
else()
    MESSAGE(STATUS "No OpenMP, wait forever")
endif()

include_directories(${CMAKE_SOURCE_DIR}/inc)

IF(UNIX AND NOT WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3")
ENDIF(UNIX AND NOT WIN32)

add_executable(ex2 main.cpp inc/Testable.h src/File.cpp src/TestRunner.cpp src/SequentialAlgorithm.cpp
    src/OpenMPAlgorithm.cpp)
target_link_libraries(ex2 ${Boost_LIBRARIES})
