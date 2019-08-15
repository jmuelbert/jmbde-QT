$ErrorActionPreference = 'Stop'

$appBaseUrl = "https://github.com/jmuelbert/jmbde-QT/releases/$appVersion"
$checksumType = 'md5'
$checksums = @{ }
ForEach ($line in (New-Object Net.WebClient).DownloadString("$appBaseUrl/${checksumType}sums.txt").Split(`
            "`n", [System.StringSplitOptions]::RemoveEmptyEntries)) {
    $items = $line.Split(" ", [System.StringSplitOptions]::RemoveEmptyEntries)
    $checksums.Add($items[1], $items[0])
}

$app32 = "jmbde-windows-x86-$appVersion.zip"
$app64 = "qbs-windows-x86_64-$appVersion.zip"

Install-ChocolateyZipPackage `
    -PackageName 'jmbde' `
    -Url "$appBaseUrl/$app32" `
    -UnzipLocation "$(Split-Path -parent $MyInvocation.MyCommand.Definition)" `
    -Url64bit "$appBaseUrl/$app64" `
    -Checksum $checksums[$app32] `
    -ChecksumType $checksumType `
    -Checksum64 $checksums[$app64] `
    -ChecksumType64 $checksumType