cmake_minimum_required(VERSION 3.16)
project(RC_Control)

set(CMAKE_C_STANDARD 99)

# Output folders
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")


# Create your executable target
add_executable(RC_Control src/main.c src/scan.c src/throttleinput.c)

target_include_directories(RC_Control PRIVATE includes)


#add_subdirectory(libs/simpleble-main/simplecble ${CMAKE_BINARY_DIR}/simplecble)
#target_link_libraries(RC_Control simplecble::simplecble)

add_subdirectory(libs/simpleble-main/simpleble ${CMAKE_BINARY_DIR}/simpleble)
target_link_libraries(RC_Control simpleble::simpleble-c)