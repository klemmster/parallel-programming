cmake_minimum_required (VERSION 2.6)

# force gcc on apple to ensure openMP support
# can't use IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") since this is only
# available after calling project() and CMAKE_CXX_COMPULER have to be set
# befor calling project()


IF(APPLE)
	MESSAGE(STATUS "switch compiler to gcc-4.7")
	SET( CMAKE_CXX_COMPILER "gcc-mp-4.7" )
ENDIF(APPLE)

project (Parallel_Ex2)

MESSAGE(STATUS "linker: ${CMAKE_LINKER}")

find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories ( ${Boost_LIBRARY_DIRS} )

find_package(OpenSSL)
if(OPENSSL_FOUND)
	include_directories(${OPENSSL_INCLUDE_DIR})
	link_directories(${OPENSSL_LIBRARY_DIR})
else()
	MESSAGE(STATUS "OpenSSL not found!")
endif()

include(FindOpenMP)
if(OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
else()
    MESSAGE(STATUS "No OpenMP, wait forever")
endif()

# link standard c++ library on osx systems
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

include_directories(${CMAKE_SOURCE_DIR}/inc)

IF(UNIX AND NOT WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -Wall -O3")
ENDIF(UNIX AND NOT WIN32)

IF(WIN32)
	set(CMAKE_CXX_COMPILER "g++")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -sse4.2 -Wall -O3")
ENDIF(WIN32)

file (GLOB_RECURSE headers *.h)

add_executable(ex2 main.cpp inc/Testable.h src/File.cpp src/TestRunner.cpp src/SequentialAlgorithm.cpp src/SequentialOptimizedAlgorithm.cpp
    src/OpenMPAlgorithm.cpp src/OpenMPAlgorithmTasks.cpp src/SequentialOptimizedAlgorithm2.cpp ${headers})
target_link_libraries(ex2 ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES})
