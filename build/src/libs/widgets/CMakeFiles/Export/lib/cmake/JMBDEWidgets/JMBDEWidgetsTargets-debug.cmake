#----------------------------------------------------------------
# Generated CMake target import file for configuration "debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "jmbde::JMBDEWidgets" for configuration "debug"
set_property(TARGET jmbde::JMBDEWidgets APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(jmbde::JMBDEWidgets PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "Qt5::Widgets;Qt5::PrintSupport;Qt5::Sql;Qt5::Qml;Qt5::QuickWidgets"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/./jmbde.app/Contents/Frameworks/libjmbdewidgets_debug.0.1.1.dylib"
  IMPORTED_SONAME_DEBUG "libjmbdewidgets_debug.0.dylib"
  )

list(APPEND _IMPORT_CHECK_TARGETS jmbde::JMBDEWidgets )
list(APPEND _IMPORT_CHECK_FILES_FOR_jmbde::JMBDEWidgets "${_IMPORT_PREFIX}/./jmbde.app/Contents/Frameworks/libjmbdewidgets_debug.0.1.1.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
