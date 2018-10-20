$qt_stub = "qt-5.11.2-dynamic-msvc2017-x86_64"

$url = "https://bitbucket.org/skunkos/qt5-minimalistic-builds/downloads/$qt_stub.7z"
$output = "qt.7z"

cd C:\jmbde-QT

Invoke-WebRequest -Uri $url -OutFile $output

choco install 7zip.install
choco install nsis
choco install sed


'C:\Program Files\7-Zip\7z.exe' x $output


cd .\$qt_stub\bin
& ".\qtbinpatcher.exe"