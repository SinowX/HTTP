cmake_minimum_required(VERSION 3.16)
project(SiHttp CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED)
set(CMAKE_CXX_FLAGS "-g")

include_directories(.)
include_directories(src)
include_directories(src/fs)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output/lib)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/output/lib)

add_subdirectory(src)

