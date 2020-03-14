# Cleanup
Remove-Item -LiteralPath "build" -Force -Recurse

$ENV:PLATFORM="x64"
$ENV:CMAKE_GENERATOR="Ninja"
$ENV:CONFIGURATION="release-fastbuild"

$ENV:CMAKEDIR="$ENV:ProgramFiles" + "\Cmake\bin"
$ENV:QTDIR="C:\Qt\5.14.1\msvc2017_64"
$ENV:QTBIN=$ENV:QTDIR + "/bin"
$ENV:VCPKGROOT="C:\tools\vcpkg"
$ENV:VCPKGDir="C:\tools\vcpkg"
$ENV:VCPKGToolChainFile = $ENV:VCPKGDir + "\scripts\buildsystems\vcpkg.cmake"
$ENV:VCREDIST_CRT_DIR="${ENV:ProgramFiles(x86)}\Microsoft Visual Studio\2019\Community\VC\Redist\MSVC\%RedistVersion%\x64\Microsoft.VC141.CRT"
$ENV:VCREDIST_CXXAMP_DIR="${ENV:ProgramFiles(x86)}\Microsoft Visual Studio\2019\Community\VC\Redist\MSVC\%RedistVersion%\x64\Microsoft.VC141.CXXAMP"
$ENV:VCREDIST_OPENMP_DIR="${ENV:ProgramFiles(x86)}\Microsoft Visual Studio\2019\Community\VC\Redist\MSVC\%RedistVersion%\x64\Microsoft.VC141.OpenMP"
$ENV:REDIST="${ENV:ProgramFiles(x86)}\Microsoft Visual Studio\2019\Community\VC\Redist\MSVC\%RedistVersion%\vcredist_%PLATFORM%.exe"
$ENV:VCVARSALL="${ENV:ProgramFiles(x86)}\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat"

cmd /c 'set /p RedistVersion=<"%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\Microsoft.VCRedistVersion.default.txt"'
$ENV:PATH += ";" + $ENV:VCPKGDIR
$ENV:PATH += ";" + $ENV:CMAKEDIR
$ENV:PATH += ";" + $ENV:QTBIN
$ENV:PATH += ";" + $ENV:ISSDIR

vcpkg install ecm
vcpkg upgrade
vcpkg list


# Before Build
Get-ChildItem ENV:PATH
# local
cmd /c 'call "%ProgramFiles(x86)%\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvarsall.bat"' %PLATFORM%
# appveyor
cmd /c 'call "%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat"' %PLATFORM%
cmd /c 'call "%QTDIR%\bin\qtenv2.bat"'
# Set-Location "$ENV:APPVEYOR_BUILD_FOLDER"
New-Item -itemtype directory -path ./build
Set-Location "build"
Write-Host "Generate the Project with the $ENV:CMAKE_GENERATOR gnerator and the configuration $ENV:CONFIGURATION and $ENV:VCPKGToolChainFile"
cmd /c "set(VCPKG_BUILD_TYPE release) >> C:\tools\vcpkg\triplets\%PLATFORM%-windows-static.cmake"
vcpkg remove --outdated --recurse
vcpkg install --triplet %PLATFORM%-windows-static %PACKAGES% 

# Build
New-Item -itemtype directory ./program
cmake -G "$ENV:CMAKE_GENERATOR"  -DCMAKE_BUILD_TYPE="$ENV:CONFIGURATION"  -DCMAKE_PREFIX_PATH="%QTDIR%" -DBUILD_SHARED_LIBS=ON ..
cmake --build . --config $ENV:CONFIGURATION --target install

# after_build
Set-Location "$ENV:APPVEYOR_BUILD_FOLDER\build"
Write-Host "$ENV:APPVEYOR_REPO_TAG_NAME"
cpack -C $ENV:CONFIGURATION -G NSIS64

Set-Location "$ENV:APPVEYOR_BUILD_FOLDER\build"
windeployqt program/jmbde.exe program/jmbdewidgets.dll program/jmbdemodels.dll
%APPVEYOR_BUILD_FOLDER%/packaging/win/installer_%PLATFORM%.iss .
$installerfile="installer_" + $ENV:PLATFORM + ".iss"
iscc $installerfile
cpack .

# test_script:
ctest -C "$ENV:CONFIGURATION" -VV