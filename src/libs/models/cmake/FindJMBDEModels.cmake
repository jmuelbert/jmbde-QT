#FindJMBDEModels.cmake
#
# Finds the models library
# 
# https://github.com/jmuelbert/jmbde-QT
#
# This will define the following variables
#
#       JMBDEModels_FOUND
#       JMBDEModels_VERSION
#       JMBDEModels_INCLUDE_DIRS
#
# and the following import targets
#
#       jmuelbert::jmbdemodels
#
# Author Jürgen Mülbert - juergen.muelbert@gmail.com
#

find_package((PkgConfig)
pkg_check_modules(PC_JMBDEModels QUIET JMBDEModels)

find_path(JMBDEModels_INCLUDE_DIR
    NAMES datacontext.h
    PATHS ${PC_JMBDEModels_INCLUDE_DIRS}
    PATH_SUFFIXES jmbdemodels
)

set(JMBDEModels_VERSION ${PC_JMBDEModels_VERSION})

mark_as_advanced(JMBDEModels_FOUND JMBDEModels_INCLUDE_DIR JMBDEModels_VERSION)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(JMBDEModels
    REQUIRED_VARS JMBDEModels_INCLUDE_DIR
    VERSION_VAR RJMBDEModels_VERSION
)

if(JMBDEModels_FOUND)
    #Set include dirs to parent, to enable includes like #include <rapidjson/document.h>
    get_filename_component(JMBDEModels_INCLUDE_DIRS ${JMBDEModels_INCLUDE_DIR} DIRECTORY)
endif()

if(JMBDEModels_FOUND AND NOT TARGET JMBDEModelsJSON::JMBDEModels)
    add_library(JMBDEModels::JMBDEModels INTERFACE IMPORTED)
    set_target_properties(JMBDEModels::JMBDEModels PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${JMBDEModels_INCLUDE_DIRS}"
    )
endif()