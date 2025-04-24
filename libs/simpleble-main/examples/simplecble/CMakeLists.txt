cmake_minimum_required(VERSION 3.21)

include(${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/prelude.cmake)
project(simpleble_examples)
include(${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/epilogue.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

option(SIMPLEBLE_LOCAL "Use local SimpleBLE" ON)

if (SIMPLEBLE_LOCAL)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../../simpleble ${CMAKE_BINARY_DIR}/simpleble)
else()
    cmake_policy(SET CMP0144 OLD) # NOTE: This broke on older versions of CMake
    find_package(simpleble CONFIG REQUIRED)
endif()

# C
add_executable(example_connect_c c/connect.c)
target_link_libraries(example_connect_c simpleble::simpleble-c)

add_executable(example_notify_c c/notify.c)
target_link_libraries(example_notify_c simpleble::simpleble-c)

add_executable(example_scan_c c/scan.c)
target_link_libraries(example_scan_c simpleble::simpleble-c)
