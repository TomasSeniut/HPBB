cmake_minimum_required(VERSION 3.7.2)
project(TravelingSalesman C)

set(CMAKE_C_FLAGS "-fopenmp")
set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES
        main.c
        utils.c
        utils.h
        IO/IO.h
        IO/IO.c
        DataStructure.h heuristics.c)

include_directories(${CMAKE_SOURCE_DIR}/../../build/include)
link_directories(${CMAKE_SOURCE_DIR}/../../build/)

add_executable(TravelingSalesman ${SOURCE_FILES})
target_link_libraries(TravelingSalesman m HPBB)

