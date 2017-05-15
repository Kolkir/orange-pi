cmake_minimum_required(VERSION 2.8)
project(rpc)

set(CMAKE_VERBOSE_MAKEFILE ON)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra")

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

file(GLOB SOURCES "*.cpp" "*.h")

add_executable(${PROJECT_NAME} ${SOURCES})

