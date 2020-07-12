# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "debug")
  file(REMOVE_RECURSE
  "src/app/CMakeFiles/jmbde_autogen.dir/AutogenUsed.txt"
  "src/app/CMakeFiles/jmbde_autogen.dir/ParseCache.txt"
  "src/app/jmbde_autogen"
  "src/appquick/CMakeFiles/jmbdeappquick_autogen.dir/AutogenUsed.txt"
  "src/appquick/CMakeFiles/jmbdeappquick_autogen.dir/ParseCache.txt"
  "src/appquick/jmbdeappquick_autogen"
  "src/libs/models/CMakeFiles/jmbdemodels_autogen.dir/AutogenUsed.txt"
  "src/libs/models/CMakeFiles/jmbdemodels_autogen.dir/ParseCache.txt"
  "src/libs/models/jmbdemodels_autogen"
  "src/libs/models/tests/CMakeFiles/tst_acount_autogen.dir/AutogenUsed.txt"
  "src/libs/models/tests/CMakeFiles/tst_acount_autogen.dir/ParseCache.txt"
  "src/libs/models/tests/CMakeFiles/tst_datacontext_autogen.dir/AutogenUsed.txt"
  "src/libs/models/tests/CMakeFiles/tst_datacontext_autogen.dir/ParseCache.txt"
  "src/libs/models/tests/tst_acount_autogen"
  "src/libs/models/tests/tst_datacontext_autogen"
  "src/libs/quick/CMakeFiles/jmbdequick_autogen.dir/AutogenUsed.txt"
  "src/libs/quick/CMakeFiles/jmbdequick_autogen.dir/ParseCache.txt"
  "src/libs/quick/jmbdequick_autogen"
  "src/libs/quick/tests/CMakeFiles/tst_quicktest_autogen.dir/AutogenUsed.txt"
  "src/libs/quick/tests/CMakeFiles/tst_quicktest_autogen.dir/ParseCache.txt"
  "src/libs/quick/tests/tst_quicktest_autogen"
  "src/libs/widgets/CMakeFiles/jmbdewidgets_autogen.dir/AutogenUsed.txt"
  "src/libs/widgets/CMakeFiles/jmbdewidgets_autogen.dir/ParseCache.txt"
  "src/libs/widgets/jmbdewidgets_autogen"
  "src/libs/widgets/tests/CMakeFiles/tst_widgetstest_autogen.dir/AutogenUsed.txt"
  "src/libs/widgets/tests/CMakeFiles/tst_widgetstest_autogen.dir/ParseCache.txt"
  "src/libs/widgets/tests/tst_widgetstest_autogen"
  "tests/CMakeFiles/tst_test_autogen.dir/AutogenUsed.txt"
  "tests/CMakeFiles/tst_test_autogen.dir/ParseCache.txt"
  "tests/tst_test_autogen"
  )
endif()
