#
# SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

# minimal requirements
cmake_minimum_required(VERSION 3.10...3.21 FATAL_ERROR)

if(${CMAKE_VERSION} VERSION_LESS 3.21)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
  cmake_policy(VERSION 3.21)
endif()


set(TARGET_ID Utils)
string(TOLOWER ${TARGET_ID} TARGET_ID_LOWER)
set(TARGET_NAMESPACE jmbde)
set(TARGET_NAME utils)
set(TARGET_DESCRIPTION "Utils for jmdbde")
set(TARGET_COPYRIGHT "© 2021 Jürgen Mülbert")
set(TARGET_URL "https://github.com/jmuelbert/jmdbe-QT")
set(TARGET_VERSION_MAJOR 0)
set(TARGET_VERSION_MINOR 1)
set(TARGET_VERSION_PATCH 0)
set(TARGET_VERSION ${TARGET_VERSION_MAJOR}.${TARGET_VERSION_MINOR}.${TARGET_VERSION_PATCH})
set(TARGET_SO_VERSION ${TARGET_VERSION_MAJOR})
set(TARGET_AUTHOR_ORGANIZATION "Jürgen Mülbert")
set(TARGET_AUTHOR_DOMAIN "https://github.com/jmuelbert")
set(TARGET_AUTHOR_MAINTAINER "Jürgen Mülbert")

message(STATUS "Building ${TARGET_NAME}" " Version ${TARGET_VERSION} SO_Version ${TARGET_SO_VERSION}"
               " in ${CMAKE_BUILD_TYPE} mode"
)


# -------------------------------------------------------------------------------------------------------------------- #
# Define Target according to options
# -------------------------------------------------------------------------------------------------------------------- #
if(BUILD_SHARED_LIBS)
    add_library(${TARGET_NAME} SHARED "")
else()
    add_library(${TARGET_NAME} STATIC "")
endif()

add_library(${TARGET_NAMESPACE}::${TARGET_NAME} ALIAS ${TARGET_NAME} )

# -------------------------------------------------------------------------------------------------------------------- #
# Get the Sources and the include directory
# -------------------------------------------------------------------------------------------------------------------- #
set(TARGET_INCLUDE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/include)
# Define source files for the library
include(CMakeLists_files.cmake)

target_sources(
  ${TARGET_NAME}
  PRIVATE ${SOURCES}
)

# -------------------------------------------------------------------------------------------------------------------- #
# Define Target properties and optional Dependencies
# -------------------------------------------------------------------------------------------------------------------- #

# generate an export header to expose symbols when using the library
generate_export_header(${TARGET_NAME} EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/exports/${TARGET_NAME}_export.h)

# add target properties such as debug postfix, MSVC Runtime and library version
# DEBUG_POSTFIX "-d"
set_target_properties(${TARGET_NAME} PROPERTIES
                        MSVC_RUNTIME_LIBRARY "${MSVC_RUNTIME_TYPE}"
                        VERSION ${TARGET_VERSION}
                        SOVERSION ${TARGET_SO_VERSION})

# set target compile options as defined in the cmake/compiler_options.cmake Module
target_compile_options(${TARGET_NAME} PRIVATE ${compiler_options})

# add compiler definition 
target_compile_definitions(${TARGET_NAME} PRIVATE ${compiler_definitions} "$<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:${TARGET_NAME}_STATIC_DEFINE>")

# set target link options as defined in the cmake/compiler_options.cmake Module
target_link_options(${TARGET_NAME} PRIVATE ${linker_flags})

# -------------------------------------------------------------------------------------------------------------------- #
# Finding Qt5 or Qt6
# -------------------------------------------------------------------------------------------------------------------- #
find_package(Qt${QT_VERSION_MAJOR} CONFIG COMPONENTS Core)

target_link_libraries(${TARGET_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core)

# BUILD_INTERFACE specifies where to find includes during build time here we set the include directory to be our src
# include directory as well as CMAKE_CURRENT_BINARY_DIR, which is where the generated export.h file is located. the
# command must be included in double quotes so the two directories, separated by a ';' can both be used (cmake needs it
# to be a string)
# include all the necessary directories
target_include_directories(${TARGET_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/exports>
  PRIVATE 
    ${TARGET_INCLUDE_FOLDER}
    # include OpenSSL directories if present
    # $<$<BOOL:${OPENSSL_FOUND}>:${OPENSSL_INCLUDE_DIR}>
    # Any other extra include required
)

if(BUILD_TESTING)
  find_package(Qt${QT_VERSION_MAJOR} CONFIG COMPONENTS Core Test)

  list(APPEND TEST_CASES
  tst_logger
  )
  foreach(TEST_CASE ${TEST_CASES})
    add_executable(${TEST_CASE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/${TEST_CASE}.cpp)
    target_link_libraries(${TEST_CASE} PRIVATE ${TARGET_NAME} Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Test)
    target_compile_options(${TEST_CASE} PRIVATE ${compiler_options})
    target_compile_definitions(${TEST_CASE} PRIVATE ${compiler_definitions} $<$<BOOL:${OPENSSL_FOUND}>:WITH_OPENSSL>)
    target_link_options(${TEST_CASE} PRIVATE ${linker_flags})

    target_include_directories(${TEST_CASE}
      PUBLIC
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/exports>
      PRIVATE
        ${TARGET_INCLUDE_FOLDER}
        # Any other extra include required
    )

    add_test(NAME ${TEST_CASE} COMMAND ${TEST_CASE})
  endforeach(TEST_CASE ${TEST_CASES})
endif()
