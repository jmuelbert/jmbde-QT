
# jmbde

[![GitHub license](https://img.shields.io/badge/license-EUPL-blue.svg)](https://joinup.ec.europa.eu/page/eupl-text-11-12)
[![Build status](https://ci.appveyor.com/api/projects/status/mq9qt36e588dk7ui?svg=true)](https://ci.appveyor.com/project/jmuelbert/jmbde-qt)
[![Build Status](https://travis-ci.org/jmuelbert/jmbde-QT.svg?branch=master)](https://travis-ci.org/jmuelbert/jmbde-QT)

jmbde is a program to collect data for the IT. The database contains employees, departments, functions, phones, mobiles, computers, printers, faxes and accounts.

jmbde use the cross-platform framework [Qt](http://www.qt.io/download-open-source/),
which means it works with the most operating systems.

## Supported Platforms

The standalone binary packages support the following platforms:

* macOS 10.10 or later
* Windows 7 or later
* Linux

## Sources

The master branch represents the latest pre-release code.

* [Releases](https://github.com/jmuelbert/jmbde-QT/releases)

* [Milestones](https://github.com/jmuelbert/jmbde-QT/milestones)

## Requests and Bug reports

* [GitHub issues (preferred)](https://github.com/jmuelbert/jmbde-QT/issues)

## Questions or Comments

## Wiki

* [Main Page](https://github.com/jmuelbert/jmbde-QT/wiki)
* [User Manual](http://jmuelbert.github.io/jmbde-QT/)

## Compiling jmbde

### On macOS
 
    The latest Xcode.

    brew install qt5
    brew link qt5 --force
    brew install qbs
    qbs setup-toolchains --detect
    qbs setup-qt /usr/local/opt/qt/bin/qmake qt-brew
    qbs config profiles.qt-brew.baseProfile xcode-macosx-x86_64
    qbs config defaultProfile qt-brew

Run `qbs` to build jmbde:

    For the release version:

        qbs install --install-root install config:release project.JMBde.version:$JMBDE_VERSION

    For the debug version:

        qbs -d build --all-products config:debug

* Alternatively, you can [download Qt here](https://www.qt.io/download-qt-installer)

### On Windows
 
    you can [download Qt here](https://www.qt.io/download-qt-installer)
    you can install many tools with choco
    choco install qbs
    Visual Studio 2017 or later
    qbs

### On Linux

* On Ubuntu/Debian: `apt-get install qt5-default qttools5-dev-tools zlib1g-dev`
* On Fedora:        `sudo dnf builddep tiled`
* On Arch Linux:    `pacman -S qt`

The installed toolchains have to match the one Qt was compiled with.

Next, compile by running:

    qmake (or qmake-qt5 on some systems)
    make

To perform a shadow build, run qmake from a different directory and refer
it to jmbde.pro. For example:

    mkdir build
    cd build
    qmake ../jmdbde.pro
    make

You can now run jmbde using the executable in `bin/jmbde``

## Installing

To install jmbde, run `make install`from terminal. By default, jmbde will
install itself to `/usr/local`.

The installation prefix fan be changed when running qmake, or by changing thr
install root when running `make install`. For example, to use an installation
prefix of `/usr`instead of `/usr/local`:

    qmake -r PREFIX=/usr

Note: The -r recursive flag is required if you've run qmake before, as this
command will affect nested pro files.

## License

jmbde is free software; you can redistribute ot and/or modify ir under the terms
of the [European Public License Version 1.2](https://joinup.ec.europa.eu/page/eupl-text-11-12).
Please read the [LICENSE](https://github.com/jmuelbert/jmbde-QT/blob/master/LICENSE) for additional information.

EUPL-1.2 © [Jürgen Mülbert](https:/github.com/jmuelbert/jmbde-QT)

[Return to top](#top)
