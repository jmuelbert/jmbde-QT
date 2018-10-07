$ErrorActionPreference = 'Stop'

$qbsBaseUrl = "https://github.com/jmuelbert/jmbde-QT/releases/$jmbdeVersion"
$checksumType = 'md5'
$checksums = @{}
ForEach ($line in (New-Object Net.WebClient).DownloadString("$jmbdeBaseUrl/${checksumType}sums.txt").Split(`
        "`n", [System.StringSplitOptions]::RemoveEmptyEntries)) {
    $items = $line.Split(" ", [System.StringSplitOptions]::RemoveEmptyEntries)
    $checksums.Add($items[1], $items[0])
}

$qbs32 = "jmbde-windows-x86-$jmbdeVersion.zip"
$qbs64 = "jmbde-windows-x86_64-$jmbdeVersion.zip"

Install-ChocolateyZipPackage `
    -PackageName 'jmbde' `
    -Url "$jmbdeBaseUrl/$qbs32" `
    -UnzipLocation "$(Split-Path -parent $MyInvocation.MyCommand.Definition)" `
    -Url64bit "$jmbdeBaseUrl/$jmbde64" `
    -Checksum $checksums[$qbs32] `
    -ChecksumType $checksumType `
    -Checksum64 $checksums[$qbs64] `
    -ChecksumType64 $checksumType