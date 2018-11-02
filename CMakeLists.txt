cmake_minimum_required(VERSION 2.6)

set(PROJECT_NAME TSP)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE HEADER "include/*.h" "src/.hpp")
file(GLOB_RECURSE SOURCE "src/*.cpp")

add_executable(../bin/${PROJECT_NAME} src/main.cpp)

