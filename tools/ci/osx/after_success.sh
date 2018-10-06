PKG=$TRAVIS_BUILD_DIR/${JMBDE_OUT}-jmbde.dmg
set -ev
cd $JMBDE_OUT
chmod +x *.sh
./sdk_install.sh
mkdir -p bin/jmbde.app/Contents/Resources/qml/jmbde
cp -avf lib_*/*.dylib bin/jmbde.app/Contents/Resources/qml/jmbde
cp -avf $TRAVIS_BUILD_DIR/tools/sdk_osx.sh bin/jmbde.app/
cd bin
macdeployqt jmbde.app -dmg
hdiutil convert -format UDBZ jmbde.dmg -o $PKG
cd -

wget http://sourceforge.net/projects/sshpass/files/sshpass/1.05/sshpass-1.05.tar.gz/download -O sshpass.tar.gz
tar zxf sshpass.tar.gz
cd sshpass-1.05
./configure
make
sudo make install
export PATH=$PWD:$PATH
cd $TRAVIS_BUILD_DIR
type -a sshpass
# ignore known hosts: -o StrictHostKeyChecking=no
sshpass -p $SF_PWD scp -o StrictHostKeyChecking=no $PKG $SF_USER,qtav@frs.sourceforge.net:/home/frs/project/q/qt/qtav/ci/

exit 0