cmake_minimum_required(VERSION 3.16)
project(RC_Control)

set(CMAKE_EXE_LINKER_FLAGS "-L/lib64")

# Définir le répertoire de base de BlueZ
set(BLUEZ_BASE "${CMAKE_SOURCE_DIR}/bluez-5.49")

# Définir les répertoires d'inclusion
include_directories(
    ${BLUEZ_BASE}
    ${BLUEZ_BASE}/gdbus
    /usr/include/dbus-1.0
    /usr/lib/dbus-1.0/include
    /usr/include/glib-2.0
    /usr/lib/glib-2.0/include
)

# Définir les bibliothèques à lier
link_libraries(
    dbus-1
    glib-2.0
)

# Définir les fichiers source de l'application
set(SOURCE_FILES
    ${BLUEZ_BASE}/gdbus/mainloop.c
    ${BLUEZ_BASE}/gdbus/watch.c
    ${BLUEZ_BASE}/src/shared/io-glib.c
    ble.c
    bleClient.c
)

#set(ENV{PKG_CONFIG_PATH} "/usr/lib/pkgconfig")  # Remplace par le bon chemin
#find_package(PkgConfig REQUIRED)
#pkg_check_modules(BLUETOOTH REQUIRED bluez)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")


# Create your executable target
add_executable(RC_Control src/ble.c src/bleClient.c)

#link directories
link_directories(/usr/lib64)
target_link_libraries(RC_Control bluetooth)

#target_include_directories(RC_Control PRIVATE ${BLUETOOTH_INCLUDE_DIRS})
#target_link_libraries(RC_Control PRIVATE ${BLUETOOTH_LIBRARIES})

target_include_directories(RC_Control PRIVATE includes)

# Compiler avec les options appropriées
target_compile_options(RC_Control PRIVATE
    -g
)

# Lier les bibliothèques nécessaires
target_link_libraries(RC_Control
    dbus-1
    glib-2.0
)
