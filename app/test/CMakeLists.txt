# test dependencies
include(CTest)

# ----------------------------------------------------------------------------------------------------------------------
# test the executable part
add_test(
  # calling jmbde_exe executable directly
  NAME jmbde_exe_test
  COMMAND jmbde_exe ""
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# ----------------------------------------------------------------------------------------------------------------------
# test the library part
add_executable(jmbde_exe_lib_tests "./tests.cpp")
target_link_libraries(
  jmbde_exe_lib_tests
  PRIVATE jmbde_project_warnings
          jmbde_project_options
          catch2_test_common
          jmbde_exe_lib)

# use xml reporter if coverage is enabled
if(${ENABLE_COVERAGE})
  set(COVERAGE_ARGS REPORTER xml)
endif()

# automatically discover tests that are defined in catch based test files you can modify the tests
catch_discover_tests(jmbde_exe_lib_tests ${COVERAGE_ARGS})
