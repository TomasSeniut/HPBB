cmake_minimum_required(VERSION 3.7.2)
project(QuadraticAssignment C)

find_package(MPI REQUIRED)

set(CMAKE_C_FLAGS "-fopenmp")
set(CMAKE_C_STANDARD 99)

include_directories(${MPI_INCLUDE_PATH})

SET(CMAKE_C_COMPILER mpicc)
SET(CMAKE_CXX_COMPILER mpicxx)

set(SOURCE_FILES
        main.c
        utils.c
        utils.h
        IO/IO.h
        IO/IO.c
        DataStructure.h
        heuristics.c)

include_directories(${CMAKE_SOURCE_DIR}/../../build/include)
link_directories(${CMAKE_SOURCE_DIR}/../../build/)

add_executable(QuadraticAssignment ${SOURCE_FILES})
target_link_libraries(QuadraticAssignment m HPBB)