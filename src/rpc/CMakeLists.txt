cmake_minimum_required(VERSION 2.8)
project(rpc)

set(CMAKE_VERBOSE_MAKEFILE ON)

SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)
find_package(Boost REQUIRED COMPONENTS system thread program_options)

if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  link_directories(${Boost_LIBRARY_DIRS})
endif(Boost_FOUND)

set(USED_LIBS ${Boost_SYSTEM_LIBRARY}
              ${Boost_THREAD_LIBRARY}
              ${Boost_PROGRAM_OPTIONS_LIBRARY})

list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra")

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

set(SERVER_SOURCES "server.cpp"
                   "server.h"
                   "connection.cpp"
                   "connection.h"
                   "server_main.cpp")

add_executable(server ${SERVER_SOURCES})
target_link_libraries(server ${USED_LIBS})

