
# jmbde

[![GitHub license](https://img.shields.io/badge/license-EUPL-blue.svg)](https://joinup.ec.europa.eu/page/eupl-text-11-12)
[![Build status](https://ci.appveyor.com/api/projects/status/mq9qt36e588dk7ui?svg=true)](https://ci.appveyor.com/project/jmuelbert/jmbde-qt)
[![Build Status](https://travis-ci.org/jmuelbert/jmbde-QT.svg?branch=develop)](https://travis-ci.org/jmuelbert/jmbde-QT)

--
jmbde is a program to collect data for the IT. The database contains employees, departments, functions, phones, mobiles, computers, printers, faxes and accounts.

jmbde uese the cross-platform framework [Qt](http://www.qt.io/download-open-source/),
which means it works with the most operating systems.

## Supported Platforms

The standalone binary packages support the following platforms:

* Windows 7 or later
* macOS 10.10 or later

##  Sources

The master branch represents the latest pre-release code.

- [Releases](https://github.com/jmuelbert/jmbde-QT/releases)

- [Milestones](https://github.com/jmuelbert/jmbde-QT/milestones)

## Requests and Bug reports

- [GitHub issues (preferred)](https://github.com/jmuelbert/jmbde-QT/issues)

## Questions or Comments

## Wiki

- [Main Page](https://github.com/jmuelbert/jmbde-QT/wiki)
- [User Manual](http://jmuelbert.github.io/jmbde-QT/)

## Compiling jmbde

Prerequisites:

* Qt 5.10 or later
* On Windows:
    * MinGW with g++ 4.9 or Visual Studio 2015 or later
    * jom
* On macOS: latest Xcode
* on Linux: g++ 4.9 or later
* Qbs 1.10.x (optional, sources also contain Qbs itself)

The installed toolchains have to match the one Qt was compiled with.

You can build jmbde with

    cd $SOURCE_DIRECTORY
    qmake -r
    make (mingw32-make or nmake or jom, depending on your platform)

Installation ("make install") is not needed. It is however possible, using

    make install INSTALL_ROOT=$INSTALL_DIRECTORY

## License

jmbde is free software; you can redistribute ot and/or modify ir under the terms
of the [European Public License Version 1.2](https://joinup.ec.europa.eu/page/eupl-text-11-12).
Please read the [LICENSE](https://github.com/jmuelbert/jmbde-QT/blob/master/LICENSE) for additional information.

EUPL-1.2 © [Jürgen Mülbert](https:/github.com/jmuelbert/jmbde-QT)

[Return to top](#top)
