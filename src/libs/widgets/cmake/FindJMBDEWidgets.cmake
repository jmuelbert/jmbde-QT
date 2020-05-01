# FindJMBDEWidgets.cmake
#
# Finds the Widgets library
#
# https://github.com/jmuelbert/jmbde-QT
#
# This will define the following variables
#
# JMBDEWidgets_FOUND JMBDEWidgets_VERSION JMBDEWidgets_INCLUDE_DIRS
#
# and the following import targets
#
# jmuelbert::jmbdeWidgets
#
# Author Jürgen Mülbert - juergen.muelbert@gmail.com
#

find_package(PkgConfig)
pkg_check_modules(PC_JMBDEWidgets QUIET JMBDEWidgets)

find_path(
  JMBDEWidgets_INCLUDE_DIR
  NAMES datacontext.h
  PATHS ${PC_JMBDEWidgets_INCLUDE_DIRS}
  PATH_SUFFIXES jmbdeWidgets)

set(JMBDEWidgets_VERSION ${PC_JMBDEWidgets_VERSION})

mark_as_advanced(JMBDEWidgets_FOUND JMBDEWidgets_INCLUDE_DIR
                 JMBDEWidgets_VERSION)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  JMBDEWidgets REQUIRED_VARS JMBDEWidgets_INCLUDE_DIR VERSION_VAR
  JMBDEWidgets_VERSION)

if(JMBDEWidgets_FOUND)
  # Set include dirs to parent, to enable includes like #include
  # <rapidjson/document.h>
  get_filename_component(JMBDEWidgets_INCLUDE_DIRS ${JMBDEWidgets_INCLUDE_DIR}
                         DIRECTORY)
endif()

if(JMBDEWidgets_FOUND AND NOT TARGET JMBDEWidgetsJSON::JMBDEWidgets)
  add_library(JMBDEWidgets::JMBDEWidgets INTERFACE IMPORTED)
  set_target_properties(
    JMBDEWidgets::JMBDEWidgets PROPERTIES INTERFACE_INCLUDE_DIRECTORIES
                                          "${JMBDEWidgets_INCLUDE_DIRS}")
endif()
