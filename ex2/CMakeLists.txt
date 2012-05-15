cmake_minimum_required (VERSION 2.6)
project (Parallel_Ex2)


find_package(Boost COMPONENTS timer REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories ( ${Boost_LIBRARY_DIRS} )

IF(UNIX AND NOT WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3")
ENDIF(UNIX AND NOT WIN32)

add_executable(ex2 main.cpp)
target_link_libraries(ex2)
