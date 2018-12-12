cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME TSP)

project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "-g -Wall -Werror -Wno-missing-braces -pedantic")
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 

find_package(Boost 1.60 REQUIRED COMPONENTS graph program_options)

file(GLOB_RECURSE HEADER "include/*.h" "include/.hpp")
file(GLOB_RECURSE SOURCE "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCE})

target_include_directories(${PROJECT_NAME}
                            PRIVATE 
                            ${Boost_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} 
                        PRIVATE
                        Boost::graph
                        Boost::program_options
                        stdc++fs)
