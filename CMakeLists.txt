cmake_minimum_required(VERSION 3.25)

project(glitch-sandbox)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

file(GLOB_RECURSE SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/src/*.h"
    "${CMAKE_CURRENT_LIST_DIR}/examples/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/examples/*.h"
)

add_executable(glitch-sandbox ${SOURCES})

target_include_directories(glitch-sandbox
    PUBLIC
    src
    ${CMAKE_CURRENT_LIST_DIR}
    third_party/glitch/include
)

target_link_directories(glitch-sandbox
    PUBLIC
    ${CMAKE_SOURCE_DIR}/third_party/glitch
)

target_link_libraries(glitch-sandbox
    PUBLIC
    glitch
)

target_precompile_headers(glitch-sandbox
    PUBLIC
    third_party/glitch/include/pch.h
)

