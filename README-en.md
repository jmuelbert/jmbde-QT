# jmbde

[![Gitpod-Ready-Code](https://img.shields.io/badge/Gitpod-Ready--to--Code-blue?logo=gitpod)](https://gitpod.io/#https://github.com/jmuelbert/jmbde-QT)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/caf2526829cb447b9ca6091cccebad27)](https://app.codacy.com/manual/jmuelbert/jmbde-QT?utm_source=github.com&utm_medium=referral&utm_content=jmuelbert/jmbde-QT&utm_campaign=Badge_Grade_Dashboard)
[![Code Quality](https://www.code-inspector.com/project/8488/score/svg)](https://frontend.code-inspector.com/public/project/8488/github-action/dashboard)
[![Code Grade](https://www.code-inspector.com/project/8488/status/svg)](https://frontend.code-inspector.com/public/project/8488/github-action/dashboard)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
![CI: Build Test](https://github.com/jmuelbert/jmbde-QT/workflows/CI:%20Build%20Test/badge.svg)
[![Build status](https://ci.appveyor.com/api/projects/status/mq9qt36e588dk7ui?svg=true)](https://ci.appveyor.com/project/jmuelbert/jmbde-qt)
[![Build Status](https://travis-ci.org/jmuelbert/jmbde-QT.svg?branch=master)](https://travis-ci.org/jmuelbert/jmbde-QT)
[![pre-commit](https://img.shields.io/badge/pre--commit-enabled-brightgreen?logo=pre-commit&logoColor=white)](https://github.com/pre-commit/pre-commit)

[wechsel zur deutschen version](README.md)

jmbde is a program for the management of resources in companies. With
this program, the employees and the equipment they need for their work
need to be recorded. These are computers, printers and telephones.

jmbde uses the cross-platform framework [Qt](http://www.qt.io/download-open-source/),
which means it works with most operating systems.

## Setup

The program uses the [QT library](https://www.qt.io). Therefore it can be set to
almost every platform can be used. It runs under MacOS, Linux and
Windows. Basically an installer should be used for the installation of the program
can be used on a computer. This installation program is installed on the
required QT libraries. For the use of the program with
Windows as the operating system this is absolutely necessary. With Linux and macOS
can be used on another variant. For these two operating systems
QT can be installed centrally. With these two operating systems
only the actual program files are installed. But also here there are
complete installation packages with everything, including QT.

## Supported platforms

The executable programs and installers are available for the following platforms
made available:

-   macOS from version 10.10
-   Windows as of version 7
-   Linux

## Execute

Below are some helpful hints on how to use jmbde on your native
platform.

### Unix

Unpack the files into a directory and execute them:

```bash
bin/jmbde
```

### Windows

Unpack the files into a directory and then execute jmbde.exe.

## macOS

Drag jmbde into your application folder and run jmbde.

## Requirements and bug reports

-   [GitHub issues (preferred)](https://github.com/jmuelbert/jmbde-QT/issues)

## Questions and comments

## Wiki

-   [Main Page](https://github.com/jmuelbert/jmbde-QT/wiki)
-   [User Manual](http://jmuelbert.github.io/jmbde-QT/)

## Database schema

-   [Database source code SQL](docs/database-design.md)

## Code sources

The master branch contains the latest pre-release code.

-   [Releases](https://github.com/jmuelbert/jmbde-QT/releases)

-   [Milestones](https://github.com/jmuelbert/jmbde-QT/milestones)

## Create program

The following are notes for developers on how to use jmbde on your
native system. They are not complete guides, but
contain information on the necessary measures. libraries,
Compilation flags, etc.

### Dependencies

-   The program requires qt5 from version 5.12.9
-   cmake from version 3.13.3
-   ninja
-   c++ development system

#### On macOS

-   The latest Xcode version.
-   Brew [installation guide](https://brew.sh)

```bash
  brew install cmake
  brew install ninja
  brew install qt5
  brew link qt5 --force
```

-   Alternatively you can also download [Qt here](https://www.qt.io/download-qt-installer)

Run `cmake` to create jmbde:

#### For the release version

```bash
mkdir build
cd build
cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Release ...
cmake --build . --target install
cpack .

```

#### For the debug version

```bash
        mkdir build
        cd build
        cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Debug ..
        cmake --build .
```

### On Windows

-   Visual Studio 2017 or higher
-   You can download [Qt here](https://www.qt.io/download-qt-installer)
-   You can install many tools with choco. [Installation guide](https://chocolatey.org/install#installing-chocolatey)

```cmd
choco install cmake
choco install ninja

```

#### For the release version

```cmd
        mkdir build
        cd build
        cmake -G "Ninja" ...
        cmake --build . --target install
        cpack .
```

#### For the debug version

```cmd
        mkdir build
        cd build
        cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Debug ..
        cmake --build .
```

### Under Linux

-   On Ubuntu/Debian:
    `sudo apt install qt5-default qttools5-dev-tools zlib1g-dev qtdeclarative5-dev cmake ninja`.
-   On Fedora: `sudo dnf builddep jmbde-QT cmake ninja`.
-   On Arch Linux: `pacman -S qt cmake ninja`

The installed toolchains must match the one with which Qt
was compiled.

-   Next, you compile by executing:

#### For the release version

```bash
        mkdir build
        cd build
        cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Release ...
        cmake --build . --target install
        cpack .
```

#### For the debug version

```bash
        mkdir build
        cd build
        cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Debug ..
        cmake --build .
```

You can now start `jmbde` with the command `bin/jmbde` from the remote command line.

## Installation

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

Qt is available under several [licenses](https://www.qt.io/licensing/).

GPL V3 © [Jürgen Mülbert](https:/github.com/jmuelbert/jmbde-QT)

[Return to top](#top)
