# Add a file containing a set of constexpr tests
add_executable(my_lib_constexpr_tests "./constexpr_tests.cpp")

target_link_libraries(
  jmbde_models_lib_constexpr_tests
  PRIVATE jmbde_models_lib
          jmbde_project_warnings
          jmbde_project_options
          catch2_test_common)

catch_discover_tests(my_lib_constexpr_tests ${COVERAGE_ARGS})

# Disable the constexpr portion of the test, and build again this allows us to have an executable that we can debug when
# things go wrong with the constexpr testing
add_executable(my_lib_relaxed_constexpr_tests "./constexpr_tests.cpp")

target_link_libraries(
  jmbde_models_lib_relaxed_constexpr_tests
  PRIVATE jmbde_models_lib
          jmnde_project_warnings
          jmbde_project_options
          catch2_test_common)
target_compile_definitions(jmbde_models_lib_relaxed_constexpr_tests
                           PRIVATE -DCATCH_CONFIG_RUNTIME_STATIC_REQUIRE)

catch_discover_tests(jmbde_models_lib_relaxed_constexpr_tests ${COVERAGE_ARGS})
