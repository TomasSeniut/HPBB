cmake_minimum_required(VERSION 3.7.2)
project(HPBB C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "-fopenmp")

add_library(HPBB
        HPBB.c
        include/HPBB.h
        DataStructure/LinkedQueue.h
        DataStructure/LinkedQueue.c
        DataStructure/ParallelStack.h
        DataStructure/ParallelStack.c
        DataStructure/Data.h
        Solver/Solver.c)

set_target_properties(HPBB PROPERTIES PUBLIC_HEADER include/HPBB.h)

target_include_directories(HPBB PRIVATE include)
target_include_directories(HPBB PRIVATE .)

install(TARGETS HPBB
        LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/../build/
        ARCHIVE DESTINATION ${CMAKE_SOURCE_DIR}/../build/
        PUBLIC_HEADER DESTINATION ${CMAKE_SOURCE_DIR}/../build/include/)
