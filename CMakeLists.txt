cmake_minimum_required(VERSION 3.19)
project(mhRad)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(deps/stb_image)
add_subdirectory(Project/src)

add_executable(main main.cpp)
target_link_libraries(main Maze)
