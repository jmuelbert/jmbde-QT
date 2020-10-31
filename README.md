# jmbde

jmbde is a program for the management of resources in companies. With
the staff and the equipment they need for their work can be used in this program.
need to be recorded. These are computers, printers and telephones.

---

[![Gitpod Ready Code](https://img.shields.io/badge/Gitpod-Ready--to--Code-blue?logo=gitpod)](https://gitpod.io/#https://github.com/jmuelbert/jmbde-QT)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/e3b3996800a147b68ef5b728668ec4d4)](https://www.codacy.com/manual/jmuelbert/jmbde-QT/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=jmuelbert/jmbde-QT&amp;utm_campaign=Badge_Grade)
[![Code Quality](https://www.code-inspector.com/project/8488/score/svg)](https://frontend.code-inspector.com/public/project/8488/github-action/dashboard)
[![Code Grade](https://www.code-inspector.com/project/8488/status/svg)](https://frontend.code-inspector.com/public/project/8488/github-action/dashboard)
[![GitHub All Releases](https://img.shields.io/github/downloads/jmuelbert/jmbde-QT/total?label=downloads%40all)](https://github.com/jmuelbert/jmbde-QT/releases)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Build status](https://ci.appveyor.com/api/projects/status/mq9qt36e588dk7ui?svg=true)](https://ci.appveyor.com/project/jmuelbert/jmbde-qt)
![Misspell fixer](https://github.com/jmuelbert/jmbde-QT/workflows/Misspell%20fixer/badge.svg)
[![pre-commit](https://img.shields.io/badge/pre--commit-enabled-brightgreen?logo=pre-commit&logoColor=white)](https://github.com/pre-commit/pre-commit)
[![Help wanted issues](https://img.shields.io/github/issues/jmuelbert/jmbde-QT/help%20wanted)](https://github.com/jmuelbert/jmbde-QT/issues?q=is%3Aissue+is%3Aopen+label%3A%22help+wanted%22)

[Features](https://github.com/jmuelbert/jmbde-QT) | [Documentation](https://jmuelbert.github.io/jmbde-QT/) | [Changelog](CHANGELOG.md) | [Contributing](CONTRIBUTING.md) | [FAQ](https://github.com/jmuelbert/jmbde-QT/wiki/FAQ) | [deutPsch](README_de-DE.md)

jmbde uses the cross platform framework [Qt](http://www.qt.io/download-open-source/),
which means that it works with most operating systems.

|  type  |                           branch                            |                                                                                                        build                                                                                                         |                                                                     downloads                                                                      |
| :----: | :---------------------------------------------------------: | :------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------: | :------------------------------------------------------------------------------------------------------------------------------------------------: |
| alpha  | [master](https://github.com/jmuelbert/jmbde-QT/tree/master) | [![GitHub Workflow Status](https://github.com/jmuelbert/jmbde-QT/workflows/CI:%20Build%20Test/badge.svg?branch=master&event=push)](https://github.com/jmuelbert/jmbde-QT/actions?query=event%3Apush+branch%3Amaster) |                                                                         -                                                                          |
|  beta  | [v0.5.2](https://github.com/jmuelbert/jmbde-QT/tree/v0.5.2) | [![GitHub Workflow Status](https://github.com/jmuelbert/jmbde-QT/workflows/CI:%20Build%20Test/badge.svg?branch=v0.5.2&event=push)](https://github.com/jmuelbert/jmbde-QT/actions?query=event%3Apush+branch%3Av0.5.2) | [![Downloads](https://img.shields.io/github/downloads/jmuelbert/jmbde-QT/v0.5.2/total)](https://github.com/jmuelbert/jmbde-QT/releases/tag/v0.5.2) |
| stable | [v0.5.0](https://github.com/jmuelbert/jmbde-QT/tree/v0.5.0) | [![GitHub Workflow Status](https://github.com/jmuelbert/jmbde-QT/workflows/CI:%20Build%20Test/badge.svg?branch=v0.5.0&event=push)](https://github.com/jmuelbert/jmbde-QT/actions?query=event%3Apush+branch%3v0.5.0)  | [![Downloads](https://img.shields.io/github/downloads/jmuelbert/jmbde-QT/v0.5.0/total)](https://github.com/jmuelbert/jmbde-QT/releases/tag/v0.5.0) |

## Setup

The program uses the [QT library](https://www.qt.io). Therefore it can be set to
almost every platform can be used. It runs under MacOS, Linux and
Windows. Basically an installer should be used for the installation of the program
can be used on one computer. This installation program is executed on the
required QT libraries. For the use of the program with
Windows as operating system is absolutely necessary. With Linux and macOS
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

## Database Schema

-   Database source code SQL](docs/database-design.md)

## Code Sources

The master branch contains the latest pre-release code.

-   [Releases](https://github.com/jmuelbert/jmbde-QT/releases)

-   [Milestones](https://github.com/jmuelbert/jmbde-QT/milestones)

## Create program

In the following you will find hints for developers how to use jmbde on your
native system. They are not complete guides, but
contain information on the necessary measures. libraries,
compile flags, etc.

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

-   Alternatively, you can also [download Qt here](https://www.qt.io/download-qt-installer)

Run 'cmake' to create jmbde:

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
        cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Debug .
        cmake --build .
```

### Under Windows

-   Visual Studio 2017 or higher
-   You can download [Qt here](https://www.qt.io/download-qt-installer)
-   You can install many tools with choco. [installation guide](https://chocolatey.org/install#installing-chocolatey)

```cmd
  choco install cmake
  choco install ninja
```

#### For the release version

```cmd
        mkdir build
        cd build
        cmake -G "Ninja" ....
        cmake --build . --target install
        cpack .
```

#### For the debug version

```cmd
        mkdir build
        cd build
        cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Debug .
        cmake --build .
```

### Under Linux

-   On Ubuntu/Debian:
    `sudo apt install qt5-default qttools5-dev-tools zlib1g-dev qtdeclarative5-dev cmake ninja`.
-   On Fedora: `sudo dnf builddep jmbde-QT cmake ninja`.
-   On Arch Linux: `pacman -S qt cmake ninja`

The installed toolchains must match the one with which Qt
was compiled.

-   Next you compile by executing:

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
        cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Debug .
        cmake --build .
```

You can now start 'jmbde' with the command 'bin/jmbde' from the command line.

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

GPL V3 © [Jürgen Mülbert](https:/github.com/jmuelbert/jmbde-QT)

[Return to top](#top)
