# Install script for directory: /Users/runner/work/jmbde-QT/jmbde-QT/src/libs/widgets

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/./jmbde.app/Contents/Frameworks" TYPE SHARED_LIBRARY FILES
    "/Users/runner/work/jmbde-QT/jmbde-QT/build/bin/libjmbdewidgets_debug.0.1.1.dylib"
    "/Users/runner/work/jmbde-QT/jmbde-QT/build/bin/libjmbdewidgets_debug.0.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./jmbde.app/Contents/Frameworks/libjmbdewidgets_debug.0.1.1.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./jmbde.app/Contents/Frameworks/libjmbdewidgets_debug.0.dylib"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      execute_process(COMMAND "/usr/bin/install_name_tool"
        -id "libjmbdewidgets_debug.0.dylib"
        -change "/Users/runner/work/jmbde-QT/jmbde-QT/build/bin/libjmbdemodels_debug.0.dylib" "libjmbdemodels_debug.0.dylib"
        "${file}")
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/./jmbde.app/Contents/Frameworks" TYPE SHARED_LIBRARY FILES "/Users/runner/work/jmbde-QT/jmbde-QT/build/bin/libjmbdewidgets_debug.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./jmbde.app/Contents/Frameworks/libjmbdewidgets_debug.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./jmbde.app/Contents/Frameworks/libjmbdewidgets_debug.dylib")
    execute_process(COMMAND "/usr/bin/install_name_tool"
      -id "libjmbdewidgets_debug.0.dylib"
      -change "/Users/runner/work/jmbde-QT/jmbde-QT/build/bin/libjmbdemodels_debug.0.dylib" "libjmbdemodels_debug.0.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./jmbde.app/Contents/Frameworks/libjmbdewidgets_debug.dylib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/Users/runner/work/jmbde-QT/jmbde-QT/src/libs/widgets/include/")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/JMBDEWidgets/JMBDEWidgetsTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/JMBDEWidgets/JMBDEWidgetsTargets.cmake"
         "/Users/runner/work/jmbde-QT/jmbde-QT/build/src/libs/widgets/CMakeFiles/Export/lib/cmake/JMBDEWidgets/JMBDEWidgetsTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/JMBDEWidgets/JMBDEWidgetsTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/JMBDEWidgets/JMBDEWidgetsTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/JMBDEWidgets" TYPE FILE FILES "/Users/runner/work/jmbde-QT/jmbde-QT/build/src/libs/widgets/CMakeFiles/Export/lib/cmake/JMBDEWidgets/JMBDEWidgetsTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/JMBDEWidgets" TYPE FILE FILES "/Users/runner/work/jmbde-QT/jmbde-QT/build/src/libs/widgets/CMakeFiles/Export/lib/cmake/JMBDEWidgets/JMBDEWidgetsTargets-debug.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/JMBDEWidgets" TYPE FILE FILES
    "/Users/runner/work/jmbde-QT/jmbde-QT/src/libs/widgets/cmake/FindJMBDEWidgets.cmake"
    "/Users/runner/work/jmbde-QT/jmbde-QT/build/src/libs/widgets/JMBDEWidgetsConfig.cmake"
    "/Users/runner/work/jmbde-QT/jmbde-QT/build/src/libs/widgets/JMBDEWidgetsConfigVersion.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/runner/work/jmbde-QT/jmbde-QT/build/src/libs/widgets/tests/cmake_install.cmake")
endif()

