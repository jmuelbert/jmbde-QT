REM Cleanup
REM ECHO OFF
rmdir /S /Q "build"

SET PLATFORM=x64
SET CMAKE_GENERATOR="Visual Studio 16 2019"
SET CONFIGURATION="Release"


SET QTDIR=C:\Qt\5.14.1\msvc2017_64
SET QTBIN=%QTDIR%\bin
SET ISSDIR="C:\Program Files (x86)\Inno Setup 6"
SET NSISDIR=%ProgramFiles(x86)%\NSIS
SET VCPKGROOT=C:\tools\vcpkg
SET VCPKGDir=c:\tools\vcpkg
SET VCPKG_BUILD_TYPE=%CONFIGURATION%
SET VCPKGToolChainFile = %VCPKGDir%\scripts\buildsystems\vcpkg.cmake
SET VCREDIST_CRT_DIR="%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Community\VC\Redist\MSVC\%RedistVersion%\x64\Microsoft.VC141.CRT"
SET VCREDIST_CXXAMP_DIR="%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Community\VC\Redist\MSVC\%RedistVersion%\x64\Microsoft.VC141.CXXAMP"
SET VCREDIST_OPENMP_DIR="%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Community\VC\Redist\MSVC\%RedistVersion%\x64\Microsoft.VC141.OpenMP"
SET REDIST="%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Community\VC\Redist\MSVC\%RedistVersion%\vcredist_%PLATFORM%.exe"
SET VCVARSALL="%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat"

set /p RedistVersion=<"%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\Microsoft.VCRedistVersion.default.txt"
SET Path=%Path%;%VCPKGDir%;%QTBIN%
SET Path=%Path%;%NSISDIR%

vcpkg install ecm
vcpkg upgrade
vcpkg list

REM  Before Build
REM Get-ChildItem ENV:PATH
REM local
call "%ProgramFiles(x86)%\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" %PLATFORM%
REM call %QTDIR%\bin\qtenv2.bat
REM appveyor
REM cmd /c 'call "%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat"' %PLATFORM%
REM cmd /c 'call "%QTDIR%\bin\qtenv2.bat"'
REM Set-Location "$ENV:APPVEYOR_BUILD_FOLDER"
mkdir build
cd build
Echo "Generate the Project with the %CMAKE_GENERATOR% generator and the configuration %CONFIGURATION% and %VCPKGToolChainFile%"
REM cmd /c "set(VCPKG_BUILD_TYPE release) >> C:\tools\vcpkg\triplets\%PLATFORM%-windows-static.cmake"
vcpkg remove --outdated --recurse
REM vcpkg install --triplet %PLATFORM%-windows-static %PACKAGES%

REM Build
REM New-Item -itemtype directory ./program
mkdir program
cmake -G %CMAKE_GENERATOR%  -DCMAKE_BUILD_TYPE=%CONFIGURATION%  -DCMAKE_PREFIX_PATH="%QTDIR%" -DBUILD_SHARED_LIBS=ON ..
cmake --build . --config %CONFIGURATION% --target install

REM after_build
REM Set-Location "$ENV:APPVEYOR_BUILD_FOLDER\build"
REM Write-Host "$ENV:APPVEYOR_REPO_TAG_NAME"
cpack -C %CONFIGURATION% -G NSIS64

REM Set-Location "$ENV:APPVEYOR_BUILD_FOLDER\build"
windeployqt program/jmbde.exe program/jmbdewidgets.dll program/jmbdemodels.dll
REM %APPVEYOR_BUILD_FOLDER%/packaging/win/installer_%PLATFORM%.iss .
SET INSTALLERFILE="../packaging/win/installer_" + %PLATFORM% + ".iss"
"C:\Program Files (x86)\Inno Setup 6\iscc" %INSTALLERFILE%
cpack .
REM test_script:
ctest -C "%CONFIGURATION%" -VV
