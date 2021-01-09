cmake_minimum_required(VERSION 3.19)
project(stb_image)

add_library(
        stbi STATIC
        stb_image.h stb_image.cpp
        stb_image_write.h)