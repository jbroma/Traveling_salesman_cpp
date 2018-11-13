cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME TSP)

project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "-g -Wall -Werror -Wno-missing-braces -pedantic")
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

find_package(Boost 1.60 REQUIRED COMPONENTS graph)

if(Boost_FOUND)
    message ("boost found")
else()
    message (FATAL_ERROR "Cannot find Boost")
endif()

file(GLOB_RECURSE HEADER "include/*.h" "include/.hpp")
file(GLOB_RECURSE SOURCE "src/*.cpp")

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} 
                        PRIVATE
                        Boost::graph
                        stdc++fs)
