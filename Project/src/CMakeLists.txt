cmake_minimum_required(VERSION 3.19)

add_library(
        Maze STATIC
        Maze/Maze.h Maze/Maze.cpp
        AntAlg/AntAlgMaze.cpp AntAlg/AntAlgMaze.h SimulatedAnnealing/SimAnn.cpp SimulatedAnnealing/SimAnn.h
        util/Random.h util/PathfindingAlg.h util/StopWatch.h
        AntAlg/AntAlgGraph.cpp AntAlg/AntAlgGraph.h AntAlg/AntAlgGraph.cpp AntAlg/AntAlgGraph.h SimulatedAnnealing/SimAnnGraph.cpp SimulatedAnnealing/SimAnnGraph.h Maze/Graph.cpp Maze/Graph.h Maze/MazeInterface.cpp Maze/MazeInterface.h)

target_include_directories(
        Maze PUBLIC
        ${CMAKE_SOURCE_DIR}/Project/src
        ${CMAKE_SOURCE_DIR}/deps/stb_image
)

target_link_libraries(
        Maze PUBLIC
        stbi
)
