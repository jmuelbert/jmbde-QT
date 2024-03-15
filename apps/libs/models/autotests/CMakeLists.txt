#
# SPDX-FileCopyrightText: 2013-2024 Jürgen Mülbert <juergen.muelbert@gmail.com>
#
# SPDX-License-Identifier: MIT
#

include(ECMMarkAsTest)

find_package(Qt6Test ${QT_MIN_VERSION} CONFIG REQUIRED)

# add given tests to run in offscreen rendering
macro(jmbde_executable_tests)
  foreach(_testname ${ARGN})
    add_executable(${_testname} ${_testname}.cpp tests.qrc)
    target_link_libraries(
      ${_testname}
      PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Test
              jmuelbert::jmbdemodels ${CONAN_LIBS} ${CONAN_LIBS_QT})
    add_test(NAME ${_testname} COMMAND $<TARGET_FILE:${_testname}>)
    ecm_mark_as_test(${_testname})
  endforeach()
endmacro()

if(WIN32)
  jmbde_executable_tests(json_utils_test)
else()
  jmbde_executable_tests(json_utils_test)
endif()
