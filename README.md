# jmbde

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

[![Build status](https://ci.appveyor.com/api/projects/status/mq9qt36e588dk7ui?svg=true)](https://ci.appveyor.com/project/jmuelbert/jmbde-qt)
[![Build Status](https://travis-ci.org/jmuelbert/jmbde-QT.svg?branch=master)](https://travis-ci.org/jmuelbert/jmbde-QT)
[Wechseln zur deutschen Version](README_DE.md)

![Compile on latest Ubuntu](https://github.com/jmuelbert/jmbde-QT/workflows/Compile%20on%20latest%20Ubuntu/badge.svg)

![Compile on latest macOS](https://github.com/jmuelbert/jmbde-QT/workflows/Compile%20on%20latest%20macOS/badge.svg)

jmbde is a program for the management of resources in companies. with this
program, employees and the equipment they need for their work can be
recorded. These are computers, printers and telephones.

jmbde use the cross-platform framework [Qt](http://www.qt.io/download-open-source/),
which means it works with the most operating systems.

## Setup

The program uses the [QT library](https://www.qt.io). Therefore it can be used
on almost any platform. It runs under MacOS, Linux and Windows. Basically, an
installer should be used to install the program on a computer. This installer
will install on the required QT libraries. For the use of the program with
Windows as operating system this is absolutely necessary.
With Linux and macOS you can use a different version. QT can be installed
centrally on these two operating systems. With these two operating systems, only
the actual program files are then installed. But here, too, there are complete
installation packages with everything, including QT.

## Supported Platforms

The standalone binary packages support the following platforms:

- macOS 10.10 or later
- Windows 7 or later
- Linux

## Running

The following are some helpful notes on how to run jmbde on your native platform.

### Unix

Unpack the files into a directory and run:

- `bin/jmbde`

### Windows

Unpack the files into a directory, and then run jmbde.exe

### macOS

Drag jmbde to your applications folder, and then run jmbde.

## Requests and Bug reports

- [GitHub issues (preferred)](https://github.com/jmuelbert/jmbde-QT/issues)

## Questions or Comments

## Wiki

- [Main Page](https://github.com/jmuelbert/jmbde-QT/wiki)
- [User Manual](http://jmuelbert.github.io/jmbde-QT/)

## Database Scheme

- [Database Source SQL](docs/database-design.md)

## Sources

The master branch represents the latest pre-release code.

- [Releases](https://github.com/jmuelbert/jmbde-QT/releases)

- [Milestones](https://github.com/jmuelbert/jmbde-QT/milestones)

## Compiling

The following are instructions for developers on how to use jmbde on your
native system. They are not complete guides, but are contain information
on the necessary measures. Libraries, Compilation flags, etc.

### Dependencies

- The program requires qt5 from version 5.10.0 on.
- cmake version 3.13.3 and higher
- ninja
- c++ development system

### On macOS

- The latest Xcode.
- Brew [installation guide](https://brew.sh)

  brew install cmake
  brew install ninja
  brew install qt5
  brew link qt5 --force

- Alternatively, you can [download Qt here](https://www.qt.io/download-qt-installer)

Run `cmake` to build jmbde:

#### For the release version:

        mkdir build-macos
        cd build-macos
        cmake -G "Ninja" ..
        cmake --build . --target install
        cpack .

#### For the debug version:

        mkdir build-macos
        cd build-macos
        cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Debug ..
        cmake --build .

### On Windows

- Visual Studio 2017 or later
- you can [download Qt here](https://www.qt.io/download-qt-installer)
- you can install many tools with choco.[installation guide](https://chocolatey.org/install#installing-chocolatey)

  choco install cmake
  choco install ninja

#### For the release version:

        mkdir build-win
        cd build-win
        cmake -G "Ninja" ..
        cmake --build . --target install
        cpack .

#### For the debug version:

        mkdir build-win
        cd build-win
        cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Debug ..
        cmake --build .

### On Linux

- On Ubuntu/Debian: `sudo apt install qt5-default qttools5-dev-tools zlib1g-dev qtdeclarative5-dev cmake ninja`
- On Fedora: `sudo dnf builddep jmbde-QT cmake ninja`
- On Arch Linux: `pacman -S qt cmake ninja`

The installed toolchains have to match the one Qt was compiled with.

- Next, compile by running:

#### For the release version:

        mkdir build-linux
        cd build-linux
        cmake -G "Ninja" ..
        cmake --build . --target install
        cpack .

#### For the debug version:

        mkdir build-linux
        cd build-linux
        cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Debug ..
        cmake --build .

You can now run jmbde using the executable in `bin/jmbde`

## Installing

## License

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/gpl-3.0.txt>.

Qt is available under multiple [licenses](https://www.qt.io/licensing/)

GPL V3 © [Jürgen Mülbert](https:/github.com/jmuelbert/jmbde-QT)

[Return to top](#top)
