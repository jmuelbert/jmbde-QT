#----------------------------------------------------------------
# Generated CMake target import file for configuration "debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "jmbde::JMBDEQuick" for configuration "debug"
set_property(TARGET jmbde::JMBDEQuick APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(jmbde::JMBDEQuick PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "Qt5::Gui;Qt5::Qml"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/./jmbde.app/Contents/Frameworks/libjmbdequick_debug.0.1.0.dylib"
  IMPORTED_SONAME_DEBUG "libjmbdequick_debug.0.dylib"
  )

list(APPEND _IMPORT_CHECK_TARGETS jmbde::JMBDEQuick )
list(APPEND _IMPORT_CHECK_FILES_FOR_jmbde::JMBDEQuick "${_IMPORT_PREFIX}/./jmbde.app/Contents/Frameworks/libjmbdequick_debug.0.1.0.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
