cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(jmbde VERSION 0.4.25 LANGUAGES CXX)

cmake_policy( SET CMP0020 NEW )
cmake_policy( SET CMP0042 NEW )
cmake_policy( SET CMP0053 NEW )
cmake_policy (SET CMP0063 NEW)

set ( CMAKE_EXPORT_COMPILE_COMMANDS ON )
set ( VERBOSE OFF )
set ( DEBUG_SYMBOL OFF CACHE BOOL "DEBUG_SYMBOL" )

set( APP_SOURCE_DIR ${CMAKE_SOURCE_DIR} )
set( APP_BINARY_DIR ${CMAKE_BINARY_DIR} )

option( WITH_QT5 "Include QT5" ON )
option( WITH_AUTO_TESTS "Include Auto-Tests" ON)
option( WITH_QML_GUI_TEST "Generate Quick-GUI" ON)

if ( WIN32 )
  set( CMAKE_INSTALL_PREFIX "C:/${PROJECT}" )
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS "TRUE") # For Windows Visual Studio # Doesn't seem to do anything though!
elseif( APPLE )
  set( CMAKE_INSTALL_PREFIX "/opt/${PROJECT}" )
else()
  set( CMAKE_INSTALL_PREFIX "/opt/${PROJECT}" )
endif()



if (APPLE)
  set( CPACK_SET_DESTDIR ON )
  set( APP_QT5_RUNTIME_INSTALL_DIRECTORY "lib/${PROJECT_NAME}" )
  set( APP_COMMON_RUNTIME_INSTALL_DIRECTORY "lib/${PROJECT_NAME}" )
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mmacosx-version-min=10.12" )
  set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mmacosx-version-min=10.12" )
elseif(WIN32)
  set( CPACK_SET_DESTDIR OFF )  # WiX does not support this, and raise an error
  set( CPACK_WIX_UPGRADE_GUID "B794E12A-3D7B-4AC8-8732-1406DBA1FAA4" )
  set( CPACK_WIX_PROGRAM_MENU_FOLDER "${PROJECT_NAME}" )
  set( CPACK_WIX_CMAKE_PACKAGE_REGISTRY "${PROJECT_NAME}" ) # HLM\Software\Kitware\CMake\Packages\QtPlatz
  set( CPACK_PACKAGE_INSTALL_DIRECTORY "${CMAKE_INSTALL_PREFIX}" )
  set( CPACK_WIX_SKIP_PROGRAM_FOLDER ON )
  set( APP_QT5_RUNTIME_INSTALL_DIRECTORY "bin" )
  set( APP_COMMON_RUNTIME_INSTALL_DIRECTORY "bin" )
else() # Linux
  set( CPACK_SET_DESTDIR ON )
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fext-numeric-literals -Wno-psabi" )
  set( APP_QT5_RUNTIME_INSTALL_DIRECTORY "lib" )
  set( APP_COMMON_RUNTIME_INSTALL_DIRECTORY "lib/${PROJECT_NAME}" )
endif()

if (APPLE)
  set(CMAKE_DEBUG_POSTFIX "_debug")
elseif(WIN32)
  set(CMAKE_DEBUG_POSTFIX "d")
else()
endif()

if (WIN32)
  if ( DEBUG_SYMBOL )
    set( CMAKE_SHARED_LINKER_FLAGS_RELEASE "/DEBUG" )
    set( CMAKE_MODULE_LINKER_FLAGS_RELEASE "/DEBUG" )
    set( CMAKE_CXX_FLAGS_RELEASE "/MD /Zi /O2 /Ob2 /D NDEBUG" )
  endif()
else()
  if ( DEBUG_SYMBOL )
    set( CMAKE_CXX_FLAGS_RELEASE "-g" )
  endif()

endif()

## Add paths to check for cmake modules:
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set( CMAKE_POSITION_INDEPENDENT_CODE ON )

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_definitions(-DUNICODE -D_UNICODE)

if(NOT DEFINED CMAKE_INSTALL_RPATH_USE_LINK_PATH)
  set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()

# Enable the test harness
enable_testing()


find_package(Qt5 
    COMPONENTS Core Gui Widgets Sql Network PrintSupport Help
    Qml Quick QuickWidgets LinguistTools
    REQUIRED
)

add_subdirectory(scripts)
add_subdirectory(src)
add_subdirectory(docs)

if (WITH_AUTO_TESTS)
  find_package(Qt5
    COMPONENTS Test  
  )
  add_subdirectory(tests)
endif()

if (WITH_QML_GUI_TEST)
  add_subdirectory(src/jmbdequick)
endif()

if (BUILD_PACKAGES)
  add_subdirectory(dist)
endif()


# target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
# target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Quick)

message( STATUS "# TARGET_ARCHITECTURE   : "  ${__arch} )
if ( CROSS_COMPILING )
  message( STATUS "# PACKAGE_ARCHITECTURE  : "  ${CPACK_DEBIAN_PACKAGE_ARCHITECTURE} )
endif()
message( STATUS "# CMAKE_BUILD_TYPE      : "  ${CMAKE_BUILD_TYPE} )
message( STATUS "# CMAKE_GENERATOR       : "  ${CMAKE_GENERATOR} )
message( STATUS "# VERSION               : "  ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}.${VERSION_TWEAK} )
message( STATUS "# CMAKE_INSTALL_PREFIX  : "  ${CMAKE_INSTALL_PREFIX} )
message( STATUS "# CPACK_PACKAGE_INSTALL_DIRECTORY: " ${CPACK_PACKAGE_INSTALL_DIRECTORY} )
message( STATUS "# CMAKE_CXX_STANDARD    : " ${CMAKE_CXX_STANDARD} )
message( STATUS "# Qt5_DIR               : " ${Qt5_DIR} "\tQt5_FOUND=" ${Qt5_FOUND} )
message( STATUS "# QTDIR                 : " ${QTDIR} )
message( STATUS "# QMAKE                 : " ${QMAKE} )
if ( WITH_QT5 AND DEFINED $ENV{QT_PLUGIN_PATH} )
  message( STATUS "################## WARNING ###################" )
  message( STATUS "QT_PLUGIN_PATH has set to $ENV{QT_PLUGIN_PATH}" )
  message( STATUS "################## WARNING ###################" )
endif()
message( STATUS "---------- END SUMMARY ------------" )
