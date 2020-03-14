rmdir /s build

set PLATFORM="x64"
set APPVEYOR_BUILD_FOLDER=%CD%
set Configuration="release-fastbuild"
set CMAKE_GENERATOR="Ninja"