cmake_minimum_required(VERSION 3.6)

project(stb_image)

add_library(stb_image STATIC)
target_sources(stb_image PRIVATE "src/stb_image.cpp")
target_include_directories(stb_image PUBLIC include)
