# FindJMBDEModels.cmake
#
# Finds the models library
#
# https://github.com/jmuelbert/jmbde-QT
#
# This will define the following variables
#
# JMBDEModels_FOUND JMBDEModels_VERSION JMBDEModels_INCLUDE_DIRS
#
# and the following import targets
#
# jmuelbert::jmbdeutils
#
# Author Jürgen Mülbert - juergen.muelbert@gmail.com
#

find_package(PkgConfig)
pkg_check_modules(PC_JMBDEUtils QUIET JMBDEUtils)

find_path(
  JMBDEUtils_INCLUDE_DIR
  NAMES logger.h
  PATHS ${PC_JMBDEUtils_INCLUDE_DIRS}
  PATH_SUFFIXES jmbdeutils)

set(JMBDEUtils_VERSION ${PC_JMBDEUtils_VERSION})

mark_as_advanced(JMBDEUtils_FOUND JMBDEUtils_INCLUDE_DIR JMBDEUtils_VERSION)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  JMBDEUtils
  REQUIRED_VARS JMBDEUtils_INCLUDE_DIR
  VERSION_VAR JMBDEUtils_VERSION)

if(JMBDEUtils_FOUND)
  # Set include dirs to parent, to enable includes like #include
  # <rapidjson/document.h>
  get_filename_component(JMBDEUtils_INCLUDE_DIRS ${JMBDEUtils_INCLUDE_DIR} DIRECTORY)
endif()

if(JMBDEUtils_FOUND AND NOT TARGET jmuelbert::jmbdeutils)
  add_library(jmuelbert::jmbdeutils INTERFACE IMPORTED)
  set_target_properties(jmuelbert::jmbdeutils PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${JMBDEUtils_INCLUDE_DIRS}")
endif()
