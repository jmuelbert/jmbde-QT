if [ "$CXX" == "" ]
then
    CXX=g++
fi

# - Not using Qbs 1.12.0, 1.12.1 or 1.12.2 because of a false "Duplicate source file" error (QBS-1416)
# - Make sure not to build against Qt 5.12 to avoid build issues on macOS (QBS-1417)

git clone --depth 1 https://github.com/probonopd/linuxdeployqt.git linuxdeployqt
pushd linuxdeployqt
# Then build in Qt Creator, or use
export PATH=$(readlink -f /tmp/.mount_QtCreator-*-x86_64/*/gcc_64/bin/):$PATH \
qmake -r linuxdeployqt.pro QMAKE_CXX=$CXX QMAKE_LINK=$CXX
                 && make
export PATH=$PATH:$PWD/bin
popd