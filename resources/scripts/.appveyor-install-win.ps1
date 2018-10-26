$OutputEncoding = New-Object -typename System.Text.UTF8Encoding
chcp 65001
$OutputEncoding

cd C:\jmbde-QT\jmbde-build\src\jmbde

git clone -q --depth=1 https://github.com/jmuelbert/jmbde.wiki.git C:\jmbde-wiki
git config --global credential.helper store
Add-Content "$env:USERPROFILE\.git-credentials" "https://$($env:access_token):x-oauth-basic@github.com`n"
git config --global user.email "juergen.muelbert@gmail.com"
git config --global user.name "jmuelbert"

$git_revision = git rev-parse --short HEAD
$date = (Get-Date).ToUniversalTime().ToString("MM-dd-yyyy HH:mm:ss")
$wikifile = 'C:\jmbde-wiki\Development-builds.md'

$file = (Get-ChildItem '*.7z').Name

if (!$file) {
  Break
}

echo "File to upload: $file"
$url = curl.exe --upload-file "$file" "https://transfer.sh/$file" --silent
echo "Obtained URL: $url"

$regex = "\| Windows \|.+transfer\.sh \(7z\).+\|  "
$wikiline = "| Windows | $date | [$git_revision](https://github.com/jmuelbert/jmbde-QT/commit/$git_revision) | [transfer.sh (7z)]($url) |  "

(Get-Content $wikifile) -replace $regex, $wikiline | Set-Content -Encoding "utf8" $wikifile

$file = (Get-ChildItem '*win64.exe').Name
echo "File to upload: $file"
$url = curl.exe --upload-file "$file" "https://transfer.sh/$file" --silent
echo "Obtained URL: $url"

$regex = "\| Windows \|.+transfer\.sh \(exe\).+\|  "
$wikiline = "| Windows | $date | [$git_revision](https://github.com/jmuelbert/jmbde-QT/commit/$git_revision) | [transfer.sh (exe)]($url) |  "

(Get-Content $wikifile) -replace $regex, $wikiline | Set-Content -Encoding "utf8" $wikifile

cd C:\jmbde-wiki
git add *.*
git commit -m "New files."
git pull origin master
git push origin master -v