set -ev
sudo apt-get update -qq

wget http://sourceforge.net/projects/buildqt/files/lite/Qt${QT}-Linux64.tar.xz/download -O Qt${QT}-Linux64.tar.xz
tar -I xz -xf Qt${QT}-Linux64.tar.xz

export PATH=$PWD/Qt${QT}-Linux64/bin:$PATH
export JMBDE_OUT=JMBDE-Qt${QT}-ubuntu1204-${TRAVIS_COMMIT:0:7}
mkdir -p $JMBDE_OUT

#if [ "$TRAVIS_BRANCH" == "prelease" ]; then
#linux