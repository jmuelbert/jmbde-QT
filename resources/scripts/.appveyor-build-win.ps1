ls

$qt_stub = "qt-5.11.2-dynamic-msvc2017-x86_64"

cd "C:\jmbde-QT"

ls

mkdir "jmbde-build"
cd "jmbde-build"

ls

#$mak_path = "C:\jmbde-QT\jmbde-build\Makefile"
$env:PATH = "C:\jmbde-QT\$qt_stub\bin\;" + $env:PATH

if (-not (test-path "C:\jmbde-QT\jmbde.pro")) {throw "C:\jmbde-QT\jmbde.pro needed"}

& "C:\jmbde-QT\$qt_stub\bin\qmake.exe" "C:\jmbde-QT\jmbde.pro" "-r" "CONFIG+=release"

#$mak_contents = [System.IO.File]::ReadAllText($mak_path).Replace(" qjp2.lib", "")
#[System.IO.File]::WriteAllText($mak_path, $mak_contents)

& "nmake"

cd "src\jmbde"

& "nmake" install

ls 

ls "..\"
ls "..\libjmbde"



cd "app"

& "C:\jmbde-QT\$qt_stub\bin\windeployqt.exe" --no-translations "jmbde.exe" "libjmbde.dll"
Copy-Item -Path C:\jmbde-QT\$qt_stub\bin\*eay* -Destination .\

cd ..

& "nmake" windows_all