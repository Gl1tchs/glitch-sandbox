cmake_minimum_required(VERSION 3.25)

project(glitch-sandbox)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package(Glitch REQUIRED)

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
    ${GLITCH_INCLUDE_DIRS} 
)

target_link_directories(glitch-sandbox
    PUBLIC
    ${CMAKE_SOURCE_DIR}/third_party/glitch
)

target_link_libraries(glitch-sandbox
    PUBLIC
    ${GLITCH_LIBRARIES}
)

target_precompile_headers(glitch-sandbox PUBLIC src/pch.h)
