cmake_minimum_required(VERSION 2.8.11)

project(jmbde)

# The Version number.
set(jmbde_VERSION_MAJOR 0)
set(jmbde_VERSION_MINOR 4)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file(
    "${PROJECT_SOURCE_DIR}/src/constants.h.in"
    "${PROJECT_SOURCE_DIR}/src/constants.h"
    )

# Find includes in correspondending build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc atomatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(Qt5Sql)
find_package(Qt5Printsupport)
find_package(Qt5Help)

# Tell CMake to Create the jmbde executable
add_executable(jmbde WIN32 src/main.cpp)

# Use the Widgets module from Qt5
target_link_libraries(jmbde Qt5::Core Qt5::Widgets Qt5:Printsupport Qt5::Sql Qt5:Help)
