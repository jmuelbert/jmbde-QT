#!/bin/bash

set -e
set -x

rm -rf build
mkdir build
pushd build

conan install ..
# Activate all options
export CMAKE_BUILD_TYPE=Debug
cmake .. -DBUILD_EXAMPLES=true -DBUILD_MANUAL=true -DBUILD_API_DOCS=true -DBUILD_TRANSLATIONS=true -DBUILD_COVERAGE=true -DBUILD_SHARED_LIBS=true -DENABLE_CLANG_TIDY=true -DENABLE_CLANG_FORMAT=true -DENABLE_CCACHE=true -DUSE_GIT_VERSION=true 
cmake --build .
