cmake_minimum_required(VERSION 3.0)
project(serve)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin CACHE INTERNAL "" FORCE)
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c99 -pedantic -Wall -Wextra -Wfloat-equal -Wshadow -Wunused-parameter")

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(serve
        ${PROJECT_SOURCE_DIR}/src/main.c
        ${PROJECT_SOURCE_DIR}/src/serve/http.c
        ${PROJECT_SOURCE_DIR}/src/stdex/int.c
        ${PROJECT_SOURCE_DIR}/src/stdex/string.c)
