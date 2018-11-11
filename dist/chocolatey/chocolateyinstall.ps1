$ErrorActionPreference = 'Stop'

$qbsBaseUrl = "https://github.com/jmuelbert/jmbde-QT/releases/$qbsVersion"
$checksumType = 'md5'
$checksums = @{}
ForEach ($line in (New-Object Net.WebClient).DownloadString("$qbsBaseUrl/${checksumType}sums.txt").Split(`
        "`n", [System.StringSplitOptions]::RemoveEmptyEntries)) {
    $items = $line.Split(" ", [System.StringSplitOptions]::RemoveEmptyEntries)
    $checksums.Add($items[1], $items[0])
}

$qbs32 = "jmbde-windows-x86-$qbsVersion.zip"
$qbs64 = "qbs-windows-x86_64-$qbsVersion.zip"

Install-ChocolateyZipPackage `
    -PackageName 'qbs' `
    -Url "$qbsBaseUrl/$qbs32" `
    -UnzipLocation "$(Split-Path -parent $MyInvocation.MyCommand.Definition)" `
    -Url64bit "$qbsBaseUrl/$qbs64" `
    -Checksum $checksums[$qbs32] `
    -ChecksumType $checksumType `
    -Checksum64 $checksums[$qbs64] `
    -ChecksumType64 $checksumType