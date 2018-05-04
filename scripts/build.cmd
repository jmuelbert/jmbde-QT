SET VERSION=0.4.12
SET RELEASE=1
SET QTDIR=C:\Qt\5.10.0\msvc2015
SET QBSDIR=C:\Qt\Tools\QtCreator\bin
SET VC=""

SET PATH=%PATH%;%QTDIR%;
FOR /F "tokens=*" %%i in ('git describe') do set COMMITNOW=%%i
set VERSION_DATE=%DATE:~10,4%.%DATE:~4,2%.%DATE:~7,2%

qbs --version
qbs setup-toolchains --detect
qbs setup-qt %QTDIR%\bin\qmake.exe qt
qbs config defaultProfile qt
qbs build --all-products release projects.jmbde.windowsInstaller:true
