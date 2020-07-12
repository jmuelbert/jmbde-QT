# Install script for directory: /Users/runner/work/jmbde-QT/jmbde-QT/src/app

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/Applications")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE DIRECTORY FILES "/Users/runner/work/jmbde-QT/jmbde-QT/build/bin/jmbde.app" USE_SOURCE_PERMISSIONS)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./jmbde.app/Contents/MacOS/jmbde" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./jmbde.app/Contents/MacOS/jmbde")
    execute_process(COMMAND "/usr/bin/install_name_tool"
      -change "/Users/runner/work/jmbde-QT/jmbde-QT/build/bin/libjmbdemodels_debug.0.dylib" "libjmbdemodels_debug.0.dylib"
      -change "/Users/runner/work/jmbde-QT/jmbde-QT/build/bin/libjmbdewidgets_debug.0.dylib" "libjmbdewidgets_debug.0.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./jmbde.app/Contents/MacOS/jmbde")
  endif()
endif()

