#!/usr/bin/env bash

# Format cmake files
cmake-format -i CMakeLists.txt
cmake-format -i CMakeLists_files.cmake
cmake-format -i doc/CMakeLists.txt
cmake-format -i tests/CMakeLists.txt
cmake-format -i packaging/CMakelists.txt
cmake-format -i src/3rd-party/qtsingleapplication/CMakelists.txt
cmake-format -i src/app/CMakelists.txt
cmake-format -i src/appquick/CMakelists.txt
cmake-format -i src/libs/CMakelists.txt
cmake-format -i src/libs/CMakelists.txt
cmake-format -i src/libs/models/CMakelists.txt
cmake-format -i src/libs/models/tests/CMakelists.txt
cmake-format -i src/libs/quick/CMakelists.txt
cmake-format -i src/libs/quick/tests/CMakelists.txt
cmake-format -i src/libs/widgets/CMakelists.txt
cmake-format -i src/libs/widgets/tests/CMakelists.txt
cmake-format -i translations/CMakelists.txt
