cmake_minimum_required(VERSION 3.0)
project(clyth)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin CACHE INTERNAL "" FORCE)
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -g -std=gnu99 -pedantic -Wall -Wextra -Wfloat-equal -Wshadow -Wunused-parameter")

add_executable(clyth
        ${PROJECT_SOURCE_DIR}/src/main.c
        ${PROJECT_SOURCE_DIR}/src/string_ex.c)
