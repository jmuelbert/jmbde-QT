#!/bin/sh

mkdir -p ../build-mingw64
cd ../build-mingw64
cmake .. \
    -DCMAKE_SYSTEM_NAME=Windows \
    -DCMAKE_PROCESSOR=x86_64 \
    -DCMAKE_C_COMPILER=x86_64-w64-mingw32-gcc \
    -DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++ \
    -DCMAKE_FIND_ROOT_PATH=/usr/x86_64-w64-mingw32 \
    -DCMAKE_FIND_ROOT_PATH_MODE_PROGRAM=NEVER \
    -DCMAKE_FIND_ROOT_PATH_MODE_LIBRARY=ONLY \
    -DCMAKE_FIND_ROOT_PATH_MODE_INCLUDE=ONLY \
    -DCMAKE_FIND_ROOT_PATH_MODE_PACKAGE=ONLY \
    -DQT_BINARY_DIR=/usr/x86_64-w64-mingw32/bin \
    -DQT_INCUDE_DIRS_NO_SYSTEM=ON \
    -DCMAKE_RC_COMPILER=x86_64-w64-mingw32-windres \
    -DCMAKE_RC_COMPILER=x86_64-w64-mingw32-windmc \
    -DBoost_THREADAPI=win32 \
    -DCMAKE_Fortran_Compiler:FILEPATH=x86_64-w64-mingw32-gfortran \
    -DCMAKE_AR:FILEPATH=x86_64-w64-mingw32-ar \
    -DCMAKE_RANLIB:FILEPATH=x86_64-w64-mingw3-ranlib \
    -DCMAKE_INSTALL_PREFIX=Program

cmake --build . --target install
