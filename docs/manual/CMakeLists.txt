#
# jmbde a BDE Tool for companies Copyright (C) 2013-2020  Jürgen Mülbert
#
# This program is free software: you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation, either version 3 of the License, or (at your option) any later
# version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
# details.

# minimal requirements
cmake_minimum_required(VERSION 3.12...3.18 FATAL_ERROR)

if(${CMAKE_VERSION} VERSION_LESS 3.18)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
  cmake_policy(VERSION 3.18)
endif()

find_package(Sphinx REQUIRED)

#
# Part for sphinx
#

set(SPHINX_SOURCE ${CMAKE_CURRENT_SOURCE_DIR})
set(SPHINX_BUILD ${CMAKE_CURRENT_BINARY_DIR}/html)
set(SPHINX_INDEX_FILE ${SPHINX_BUILD}/index.html)
set(SPHINX_FILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/config.py.in)
set(SPHINX_FILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/config.py)
set(SPHINX_THEME "alabaster")

# Doxygen won't create this for us
file(MAKE_DIRECTORY ${SPHINX_BUILD})

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/conf.py.in"
               "${CMAKE_CURRENT_BINARY_DIR}/conf.py" @ONLY)

# Only regenerate Sphinx when: - Doxygen has rerun - Our doc files have been
# updated - The Sphinx config has been updated
add_custom_command(
  OUTPUT ${SPHINX_INDEX_FILE}
  COMMAND
    ${SPHINX_EXECUTABLE} -b html -c ${CMAKE_CURRENT_BINARY_DIR}
    # Tell Breathe where to find the Doxygen output
    -Dbreathe_projects.Application=${DOXYGEN_OUTPUT_DIR} ${SPHINX_SOURCE}
    ${SPHINX_BUILD}
  WORKING_DIRECTORY ${SPHINX_BUILD}
  DEPENDS # Othe docs files you want to track should go here (or in some
          # variable)
          ${SPHINX_SOURCE}/index.rst
  MAIN_DEPENDENCY ${SPHINX_SOURCE}/conf.py.in
  COMMENT "Generating documentation with Sphinx")

# Nice named target so we can run the job easily
add_custom_target(Sphinx ALL DEPENDS ${SPHINX_INDEX_FILE})

# Add an install target to install the docs
install(DIRECTORY ${SPHINX_BUILD} DESTINATION ${DOC_INSTALL_DIR})
