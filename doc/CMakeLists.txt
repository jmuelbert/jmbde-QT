# --------------------------------------------------------------------------------------------------------------------
# #
#
# Copyright (c) 2021 C++ Modern Framework
#
# --------------------------------------------------------------------------------------------------------------------
# #
cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

# Root project
set(ROOT_PROJECT ModernSharedLibTemplate)
set(ROOT_PROJECT_ID MLT)

# --------------------------------------------------------------------------------------------------------------------
# # Early includes
# --------------------------------------------------------------------------------------------------------------------
# #
include(../cmake/CPM.cmake)

# --------------------------------------------------------------------------------------------------------------------
# # Add project dependencies
#
# Some dependencies are added using CPM see https://github.com/TheLartians/CPM.cmake for more info.
# --------------------------------------------------------------------------------------------------------------------
# #
CPMAddPackage(NAME ${ROOT_PROJECT} SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
CPMAddPackage(
  NAME awesome-css
  GIT_REPOSITORY https://github.com/jothepro/doxygen-awesome-css.git
  VERSION 1.6.1
)

# --------------------------------------------------------------------------------------------------------------------
# # Project configuration
# --------------------------------------------------------------------------------------------------------------------
# #
project(${ROOT_PROJECT}_Doc)

# --------------------------------------------------------------------------------------------------------------------
# # Find Doxygen & Customise see : https://cmake.org/cmake/help/latest/module/FindDoxygen.html see :
# https://www.doxygen.nl/manual/config.html
# --------------------------------------------------------------------------------------------------------------------
# #
find_package(Doxygen REQUIRED)
# Get Project infos from CMake
set(DOXYGEN_PROJECT_NAME ${${ROOT_PROJECT_ID}_PROJECT_NAME})
set(DOXYGEN_PROJECT_BRIEF ${${ROOT_PROJECT_ID}_PROJECT_DESCRIPTION})
set(DOXYGEN_PROJECT_COPYRIGHT ${${ROOT_PROJECT_ID}_PROJECT_COPYRIGHT})
set(DOXYGEN_PROJECT_NUMBER ${${ROOT_PROJECT_ID}_VERSION})
set(DOXYGEN_AUTHOR_ORGANIZATION ${${ROOT_PROJECT_ID}_AUTHOR_ORGANIZATION})
set(DOXYGEN_AUTHOR_DOMAIN ${${ROOT_PROJECT_ID}_AUTHOR_DOMAIN})
set(DOXYGEN_AUTHOR_MAINTAINER ${${ROOT_PROJECT_ID}_AUTHOR_MAINTAINER})

# Configuration see: https://www.doxygen.nl/manual/config.html
set(DOXYGEN_FULL_PATH_NAMES YES)
set(DOXYGEN_STRIP_FROM_PATH ${${ROOT_PROJECT}_SOURCE_DIR})
set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_EXTRACT_PRIVATE YES)
set(DOXYGEN_EXTRACT_STATIC YES)
set(DOXYGEN_RECURSIVE YES)
set(DOXYGEN_SOURCE_BROWSER YES)
set(DOXYGEN_INLINE_SOURCES YES)

# Custom theme see: https://github.com/jothepro/doxygen-awesome-css
set(DOXYGEN_GENERATE_TREEVIEW YES)
set(DOXYGEN_HTML_EXTRA_STYLESHEET
    ${awesome-css_SOURCE_DIR}/doxygen-awesome.css ${awesome-css_SOURCE_DIR}/doxygen-awesome-sidebar-only.css
    ${awesome-css_SOURCE_DIR}/doxygen-awesome-sidebar-only-darkmode-toggle.css custom.css
)
set(DOXYGEN_HTML_EXTRA_FILES ${awesome-css_SOURCE_DIR}/doxygen-awesome-darkmode-toggle.js)
set(DOXYGEN_HTML_HEADER ${CMAKE_BINARY_DIR}/header.html)
set(DOXYGEN_HTML_FOOTER ${CMAKE_BINARY_DIR}/footer.html)

# Add md files
set(DOXYGEN_USE_MDFILE_AS_MAINPAGE ../README.md)

# Define output
set(DOXYGEN_OUTPUT_DIRECTORY .)

# Generate header and footer
configure_file(${CMAKE_CURRENT_LIST_DIR}/header.html.in ${CMAKE_BINARY_DIR}/header.html)
configure_file(${CMAKE_CURRENT_LIST_DIR}/footer.html.in ${CMAKE_BINARY_DIR}/footer.html)

# --------------------------------------------------------------------------------------------------------------------
# # Add target for generating documentation with Doxygen
# --------------------------------------------------------------------------------------------------------------------
# #
doxygen_add_docs(generate_documentation ../README.md ../include ../src)
