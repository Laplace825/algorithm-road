cmake_minimum_required(VERSION 3.15)

project(algorithm-road)
set(CMAKE_CXX_STANDARD 23)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# Release
set(CMAKE_BUILD_TYPE "Release")

# Debug
#set(CMAKE_BUILD_TYPE "Debug")
add_subdirectory(Algorithm-Question-Solutions)
add_subdirectory(Data-Structure)
