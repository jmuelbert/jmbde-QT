#!/bin/bash

set -e
set -x


rm -rf build
mkdir build
pushd build
pwd

# conan remote add bincrafters "https://api.bintray.com/conan/bincrafters/public-conan"
conan create ../conan/ECM
# conan build ../src/libs/models
conan install ..
# Activate all options
export CMAKE_BUILD_TYPE=Debug

export BUILD_TRANSLATIONS=true
export BUILD_COVERAGE=false
export BUILD_SHARED_LIBS=OFF
export ENABLE_CLANG_TIDY=true
export ENABLE_CLANG_FORMAT=true
export ENABLE_CCACHE=true
export USE_GIT_VERSION=true
cmake ..   -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=OFF -DBUILD_TRANSLATIONS=ON -DENABLE_CLANG_TIDY=ON -DENABLE_CLANG_FORMAT=TRUE -DENABLE_CCACHE=TRUE -DUSE_GIT_VERSION=ON -DBUILD_EXAMPLES=ON -DBUILD_MANUAL=ON -DBUILD_API_DOCS=ON
cmake --build .
cpack .
