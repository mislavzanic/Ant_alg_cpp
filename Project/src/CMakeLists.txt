cmake_minimum_required(VERSION 3.19)

add_library(
        Maze STATIC
        Maze/Maze.h Maze/Maze.cpp
        AntAlg/AntAlg.cpp AntAlg/AntAlg.h SimulatedAnnealing/SimAnn.cpp SimulatedAnnealing/SimAnn.h 
        util/Random.h util/PathfindingAlg.h util/StopWatch.h
)

target_include_directories(
        Maze PUBLIC
        ${CMAKE_SOURCE_DIR}/Project/src
        ${CMAKE_SOURCE_DIR}/deps/stb_image
)

target_link_libraries(
        Maze PUBLIC
        stbi
)
