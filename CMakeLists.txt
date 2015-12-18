cmake_minimum_required(VERSION 2.8)

project(ArgumentParser)

include_directories("include")
file(GLOB sources src/*.cpp)
add_library(ArgumentParser ${sources})

