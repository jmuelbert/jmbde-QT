#
#  SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
#
#  SPDX-License-Identifier: GPL-3.0-or-later
#

# minimal requirements
cmake_minimum_required(VERSION 3.10...3.21 FATAL_ERROR)

if(${CMAKE_VERSION} VERSION_LESS 3.21)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
  cmake_policy(VERSION 3.20)
endif()

if(ENABLE_CONAN)
  include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
  conan_basic_setup()
endif()

find_package(
  Qt${QT_VERSION_MAJOR} REQUIRED
  COMPONENTS Core
             Gui
             Widgets
             Sql
             PrintSupport
             Test)

# find_package(jmbdequick CONFIG REQUIRED)

list(APPEND TEST_CASES tst_quicktest)
foreach(TEST_CASE ${TEST_CASES})
  add_executable(${TEST_CASE} ${CMAKE_CURRENT_SOURCE_DIR}/src/${TEST_CASE}.cpp)
  target_link_libraries(${TEST_CASE} PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Test ${CONAN_LIBS})
  target_compile_options(${TEST_CASE} PRIVATE ${compiler_options})
  target_compile_definitions(${TEST_CASE} PRIVATE ${compiler_definitions} $<$<BOOL:${OPENSSL_FOUND}>:WITH_OPENSSL>)
  target_link_options(${TEST_CASE} PRIVATE ${linker_flags})

  target_include_directories(
    ${TEST_CASE}
    PUBLIC $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/exports>
    PRIVATE ${TARGET_INCLUDE_FOLDER}
            # Any other extra include required
  )

  add_test(NAME ${TEST_CASE} COMMAND ${TEST_CASE})
endforeach(TEST_CASE ${TEST_CASES})
