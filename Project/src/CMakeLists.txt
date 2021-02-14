cmake_minimum_required(VERSION 3.19)

add_library(
        Maze STATIC
        util/Random.h util/PathfindingAlg.h util/StopWatch.h util/ImageProcessing.h util/ImageProcessing.cpp
        Maze/MatrixMaze.h Maze/MatrixMaze.cpp Maze/Graph.cpp Maze/Graph.h Maze/MazeInterface.h
        AntAlg/AntAlgGraph.cpp AntAlg/AntAlgGraph.h SimulatedAnnealing/SimAnnGraph.cpp SimulatedAnnealing/SimAnnGraph.h )

target_include_directories(
        Maze PUBLIC
        ${CMAKE_SOURCE_DIR}/Project/src
        ${CMAKE_SOURCE_DIR}/deps/stb_image
)

target_link_libraries(
        Maze PUBLIC
        stbi
)
