cmake_minimum_required(VERSION 3.0)
project(serve)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin CACHE INTERNAL "" FORCE)

if (UNIX)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -std=c99 -pedantic -Wall -Wextra -Wfloat-equal -Wshadow -Wunused-parameter")
endif (UNIX)


include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(serve
        ${PROJECT_SOURCE_DIR}/src/main.c
        ${PROJECT_SOURCE_DIR}/src/serve/http.c
        ${PROJECT_SOURCE_DIR}/src/stdex/int.c
        ${PROJECT_SOURCE_DIR}/src/stdex/string.c)

if(WIN32)
  target_link_libraries(serve wsock32 ws2_32)
endif()