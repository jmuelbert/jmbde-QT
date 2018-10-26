$qt_stub = "qt-5.11.2-dynamic-msvc2017-x86_64"

$url = "https://bitbucket.org/skunkos/qt5-minimalistic-builds/downloads/$qt_stub.7z"
$output = "qt.7z"

cd C:\jmbde-QT

Invoke-WebRequest -Uri $url -OutFile $output

choco install 7zip.install
choco install nsis
choco install sed

if (-not (test-path "$env:ProgramFiles\7-Zip\7z.exe")) {throw "$env:ProgramFiles\7-Zip\7z.exe needed"}
set-alias sz "$env:ProgramFiles\7-Zip\7z.exe"
sz x $output


cd .\$qt_stub\bin
& ".\qtbinpatcher.exe"