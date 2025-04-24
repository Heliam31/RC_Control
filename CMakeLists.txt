cmake_minimum_required(VERSION 3.16)
project(RC_Control)




#set(ENV{PKG_CONFIG_PATH} "/usr/lib/pkgconfig")  # Remplace par le bon chemin
#find_package(PkgConfig REQUIRED)
#pkg_check_modules(BLUETOOTH REQUIRED bluez)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")


# Create your executable target
add_executable(RC_Control src/main.c src/throttleinput.c)

target_include_directories(RC_Control PRIVATE includes)


add_subdirectory(libs/simpleble-main/simplecble)
target_link_libraries(RC_Control simpleble::simpleble)