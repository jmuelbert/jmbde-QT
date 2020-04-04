#!/bin/bash

set -e
set -x

rm -rf build
mkdir build
pushd build

# conan remote add bincrafters "https://api.bintray.com/conan/bincrafters/public-conan"
conan create ../conan/ECM
# conan build ../src/libs/models
conan install ..

cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON -DBUILD_TESTING=ON -DCMAKE_INSTALL_PREFIX:PATH=instdir
make all
make install
cpack .
