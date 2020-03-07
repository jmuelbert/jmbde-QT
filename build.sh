#!/bin/bash

set -e
set -x

rm -rf build
mkdir build
pushd build

# conan install ..
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF -DBUILD_TESTING=ON
cmake --build .
