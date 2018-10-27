#!/bin/bash

# Setup Qt build environment.
source /opt/qt59/bin/qt59-env.sh

env

git_revision=$(git rev-parse --short HEAD)
git_tag_name=$TRAVIS_BRANCH

mkdir jmbde-build && cd jmbde-build

# Build application.
qmake -spec linux-g++ -r "WITH_UBUNTU=true" ../jmbde.pro 
make
make install

cd src/jmbde

# Obtain linuxdeployqt.
wget -c https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage
chmod a+x linuxdeployqt-continuous-x86_64.AppImage 

# Create AppImage.
find . -type f
unset QTDIR; unset QT_PLUGIN_PATH ; unset LD_LIBRARY_PATH
./linuxdeployqt-continuous-x86_64.AppImage "./AppDir/usr/share/applications/io.github.jmuelbert.jmbde-QT.desktop" -bundle-non-qt-libs -no-translations
./linuxdeployqt-continuous-x86_64.AppImage "./AppDir/usr/share/applications/io.github.jmuelbert.jmbde-QT.desktop" -appimage -no-translations

set -- j*.AppImage
rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi

imagename="$1"

# Workaround to increase compatibility with older systems; see https://github.com/darealshinji/AppImageKit-checkrt for details
mkdir -p AppDir/usr/optional/
wget -c https://github.com/darealshinji/AppImageKit-checkrt/releases/download/continuous/exec-x86_64.so -O ./AppDir/usr/optional/exec.so
mkdir -p AppDir/usr/optional/libstdc++/
cp /usr/lib/x86_64-linux-gnu/libstdc++.so.6 ./AppDir/usr/optional/libstdc++/
( cd AppDir ; rm AppRun ; wget -c https://github.com/darealshinji/AppImageKit-checkrt/releases/download/continuous/AppRun-patched-x86_64 -O AppRun ; chmod a+x AppRun)
.
# Manually invoke appimagetool so that libstdc++ gets bundled and the modified AppRun stays intact
./linuxdeployqt*.AppImage --appimage-extract
export PATH=$(readlink -f ./squashfs-root/usr/bin):$PATH
./squashfs-root/usr/bin/appimagetool -g ./AppDir/ $imagename

# Upload image.
git config --global user.email "juergen.muelbert@gmail.com"
git config --global user.name "jmuelbert"
git clone https://jmuelbert:${GH_TOKEN}@github.com/jmuelbert/jmbde-QT.wiki.git ./build-wiki

ls ../
ls ../libjmbde

imagenamenospace="jmbde-${git_tag_name}-${git_revision}-linux64.AppImage"

mv "$imagename" "$imagenamenospace"
imagename="$imagenamenospace"

echo "File to upload: $imagename"
echo "URL ending: $imagenamenospace"

url=$(curl --upload-file "./$imagename" "https://transfer.sh/$imagenamenospace" --silent)

rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi

wikiline="| Linux | $(date +'%m-%d-%Y %T') | [$git_revision](https\://github.com/jmuelbert/jmbde-QT/commit/$git_revision) | [transfer.sh]($url) |  "
wikifile="./build-wiki/Development-builds.md"
wikifilenew="./build-wiki/Development-builds.md.new"

echo "Line to add: $wikiline"
cat "$wikifile" | sed -e "s@| Linux | .\+$USE_WEBENGINE |  @$wikiline@g" > "$wikifilenew"

cat "$wikifilenew"
mv "$wikifilenew" "$wikifile"

cd ./build-wiki
git commit -a -m "New files."
git pull origin master
git push origin master

rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi

echo "Current git commit has is $(git rev-parse HEAD)."
echo "Travis branch $TRAVIS_BRANCH and Travis tag $TRAVIS_TAG."

if [[ $TRAVIS_BRANCH == $TRAVIS_TAG ]]; then
#if [[ true ]]; then
  # We will trigger stuff for Flathub.
  cd ../../..
  chmod +x ../resources/scripts/.flathub-release.sh
  ../resources/scripts/.flathub-release.sh $TRAVIS_TAG $(git rev-parse HEAD)
fi