#!/bin/bash
#
# Usage: ./macdeploy.sh <full-path-to-macdeployqt>
#
# macdeployqt is usually located in QTDIR/bin/macdeployqt

if [ -z "$1" ]; then
 echo "Required parameter missing for full path to macdeployqt"
 exit 1
fi

MACDEPLOYQT=$1
QTDIR="`dirname $MACDEPLOYQT`/.."
LIBRARY_NAME="libjmbde.2.dylib"
PLUGINS="jmbde.app/Contents/Resources/plugins"

# cd to directory with bundle
test -d bin || cd ..
cd bin

# copy libjmbde into bundle
cp $LIBRARY_NAME jmbde.app/Contents/MacOS/

# copy all jmbde plugins into bundle
test -d $PLUGINS || mkdir $PLUGINS
cp plugins/*.dylib $PLUGINS/

# fix libjmbde
install_name_tool -change $LIBRARY_NAME @executable_path/$LIBRARY_NAME jmbde.app/Contents/MacOS/jmbde

# fix plugins
for plugin in $PLUGINS/*.dylib
do
 install_name_tool -change $LIBRARY_NAME @executable_path/$LIBRARY_NAME $plugin
done

# run macdeployqt
$MACDEPLOYQT jmbde.app -qmldir=$PWD/../src/lib/data/data

# create final dmg image
cd ../mac
./create_dmg.sh
