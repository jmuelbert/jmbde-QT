#
 #  SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
 #
 #  SPDX-License-Identifier: MIT
 #

# find_package(jmbdemodels CONFIG REQUIRED)

list(APPEND TEST_CASES tst_models)
foreach(TEST_CASE ${TEST_CASES})
  add_executable(${TEST_CASE} ${CMAKE_CURRENT_SOURCE_DIR}/src/${TEST_CASE}.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/${TEST_CASE}.h)
  target_link_libraries(${TEST_CASE} 
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Test
        jmuelbert::jmbdemodels
        ${CONAN_LIBS}
    )
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
