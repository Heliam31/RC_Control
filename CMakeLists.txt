cmake_minimum_required(VERSION 3.16)
project(RC_Control)

set(CMAKE_EXE_LINKER_FLAGS "-L/lib64")

#set(ENV{PKG_CONFIG_PATH} "/usr/lib/pkgconfig")  # Remplace par le bon chemin
#find_package(PkgConfig REQUIRED)
#pkg_check_modules(BLUETOOTH REQUIRED bluez)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# Create your game executable target as usual
add_executable(RC_Control src/mainBLE.c )
link_directories(/usr/lib64)
#/usr/lib64/libbluetooth.so.3.19.15
target_link_libraries(RC_Control bluetooth)

#target_include_directories(RC_Control PRIVATE ${BLUETOOTH_INCLUDE_DIRS})
#target_link_libraries(RC_Control PRIVATE ${BLUETOOTH_LIBRARIES})

target_include_directories(RC_Control PRIVATE includes)