# FindJMBDEQuick.cmake
#
# Finds the Quick library
#
# https://github.com/jmuelbert/jmbde-QT
#
# This will define the following variables
#
# JMBDEQuick_FOUND JMBDEQuick_VERSION JMBDEQuick_INCLUDE_DIRS
#
# and the following import targets
#
# jmuelbert::jmbdeQuick
#
# Author Jürgen Mülbert - juergen.muelbert@gmail.com
#

find_package(PkgConfig)
pkg_check_modules(PC_JMBDEQuick QUIET jmbdequick)

find_path(
  JMBDEQuick_INCLUDE_DIR
  NAMES maincontroller.h
  PATHS ${PC_JMBDEQuick_INCLUDE_DIRS}
  PATH_SUFFIXES jmbdequick)

set(JMBDEQuick_VERSION ${PC_JMBDEQuick_VERSION})

mark_as_advanced(JMBDEQuick_FOUND JMBDEQuick_INCLUDE_DIR JMBDEQuick_VERSION)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  JMBDEQuick
  REQUIRED_VARS JMBDEQuick_INCLUDE_DIR
  VERSION_VAR JMBDEQuick_VERSION)

if(JMBDEQuick_FOUND)
  # Set include dirs to parent, to enable includes like #include
  # <rapidjson/document.h>
  get_filename_component(JMBDEQuick_INCLUDE_DIRS ${JMBDEQuick_INCLUDE_DIR}
                         DIRECTORY)
endif()

if(JMBDEQuick_FOUND AND NOT TARGET jmuelbert::jmbdequick)
  add_library(jmuelbert::jmbdequick INTERFACE IMPORTED)
  set_target_properties(
    jmuelbert::jmbdequick PROPERTIES INTERFACE_INCLUDE_DIRECTORIES
                                     "${JMBDEQuick_INCLUDE_DIRS}")
endif()
