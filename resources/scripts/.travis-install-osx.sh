#!/bin/sh

# Build application.
git_revision=$(git rev-parse --short HEAD)
git_tag_name=$TRAVIS_BRANCH

mkdir jmbde-build && cd jmbde-build
qmake ../jmbde.pro 
make
make install

cd src/jmbde


# Make app directory (not DMG image).
make frameworks
otool -L "jmBDE.app/Contents/MacOS/jmbde"

dmgnamenospace="jmbde-${git_tag_name}-${git_revision}-mac64.7z"

7za a -t7z "$dmgnamenospace" "jmBDE.app"

echo "File to upload: $dmgnamenospace"

echo "Parent Dir"
ls ../

echo "libjmbde Dir"
ls ../libjmbde


# DMG is finished, upload it.
git config --global user.email "juergen.muelbert@gmail.com"
git config --global user.name "jmuelbert"
git clone https://jmuelbert:${GH_TOKEN}@github.com/jmuelbert/jmbde-QT.wiki.git ./build-wiki

url=$(curl --upload-file "./$dmgnamenospace" "https://transfer.sh/$dmgnamenospace" --silent)

rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi

wikiline="| Mac OS X | $(date +'%m-%d-%Y %T') | [$git_revision](https\://github.com/jmuelbert/jmbde-QT/commit/$git_revision) | [transfer.sh]($url) |  "
wikifile="./build-wiki/Development-builds.md"
wikifilenew="./build-wiki/Development-builds.md.new"

echo "Line to add: $wikiline"
cat "$wikifile" | sed -e "s@| Mac .*|  @$wikiline@g" > "$wikifilenew"

cat "$wikifilenew"
mv "$wikifilenew" "$wikifile"

cd ./build-wiki
git commit -a -m "New files."
git pull origin master
git push origin master