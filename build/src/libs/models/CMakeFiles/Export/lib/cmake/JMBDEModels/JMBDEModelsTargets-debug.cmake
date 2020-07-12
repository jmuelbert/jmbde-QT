#----------------------------------------------------------------
# Generated CMake target import file for configuration "debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "jmbde::JMBDEModels" for configuration "debug"
set_property(TARGET jmbde::JMBDEModels APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(jmbde::JMBDEModels PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "Qt5::Gui;Qt5::Widgets;Qt5::PrintSupport;Qt5::Sql"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/./jmbdemodels.app/Contents/Frameworks/libjmbdemodels_debug.0.1.2.dylib"
  IMPORTED_SONAME_DEBUG "libjmbdemodels_debug.0.dylib"
  )

list(APPEND _IMPORT_CHECK_TARGETS jmbde::JMBDEModels )
list(APPEND _IMPORT_CHECK_FILES_FOR_jmbde::JMBDEModels "${_IMPORT_PREFIX}/./jmbdemodels.app/Contents/Frameworks/libjmbdemodels_debug.0.1.2.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
