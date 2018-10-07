@rem  JMBDE DAILY BUILD SCRIPT
@echo off

rem The following assumes US date format!

set VERSION=%DATE:~10,4%-%DATE:~4,2%-%DATE:~7,2%

set JMBDE_SOURCE_DIR=E:\Projects\jmbde
set JMBDE_BUILD_DIR=E:\Builds\jmbde-daily-qt5
set QTDIR=E:\Qt\5.3\msvc2013_opengl
set ARCH=32
set MAKE=E:\Qt\Tools\QtCreator\bin\jom.exe
set GIT="C:\Program Files (x86)\Git\cmd\git.exe"
set SCP="C:\Program Files (x86)\Git\bin\scp.exe"
# set DESTINATION=bjorn@files.mapeditor.org:public_html/files.mapeditor.org/public/daily/

echo Waiting a bit for the network to come up...
ping -n 3 127.0.0.1 > nul

pushd %JMBDE_SOURCE_DIR%
%GIT% fetch
%GIT% diff --quiet origin/master
if %ERRORLEVEL% == 0 (
    echo No change, nothing to do.
    popd
    goto done
) else if %ERRORLEVEL% == 1 (
   %GIT% reset --hard origin/master
)
popd

FOR /F "tokens=*" %%i in ('%GIT% describe') do SET COMMITNOW=%%i

echo Building JMBDE daily %VERSION%... (from %COMMITNOW%)

call %QTDIR%\bin\qtenv2.bat
call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" x86

rem This allows the executable to run on Windows XP
set LINK=/SUBSYSTEM:WINDOWS,5.01

mkdir %JMBDE_BUILD_DIR%
pushd %JMBDE_BUILD_DIR%
qmake.exe -r %JMBDE_SOURCE_DIR%\jmbde.pro "CONFIG+=release" "QMAKE_CXXFLAGS+=-DJMBDE_VERSION=%COMMITNOW%"
%MAKE%
popd

echo Building Installer...
pushd %JMBDE_SOURCE_DIR%\dist\win
makensis.exe jmbde-vs2013.nsi

echo Uploading installer...
# %SCP% -B JMBDE-%VERSION%-win32-setup.exe %DESTINATION%

popd

:done

echo Shutting down in 30 seconds...
ping -n 31 127.0.0.1 > nul
shutdown -s