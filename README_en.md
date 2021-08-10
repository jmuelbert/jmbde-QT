# jmbde

jmbde is a program for the management of resources in companies. With the staff and the
equipment they need for their work can be used in this program. need to be recorded.
These are computers, printers and telephones.

---

---
[![Gitpod Ready Code][gitpod-shield]][gitpod-url]
[![Gitlab Status](https://gitlab.com/jmuelbert/jmbde-QT/badges/master/pipeline.svg)](https://gitlab.com/jmuelbert/jmbde-QT/commits/master)
[![Building(CMake)](https://github.com/jmuelbert/jmbde-QT/actions/workflows/build.yml/badge.svg)](https://github.com/jmuelbert/jmbde-QT/actions/workflows/build.yml)
[![Packaging Linux](https://github.com/jmuelbert/jmbde-QT/actions/workflows/linux-pack.yml/badge.svg)](https://github.com/jmuelbert/jmbde-QT/actions/workflows/linux-pack.yml)
[![Packaging(macOS)](https://github.com/jmuelbert/jmbde-QT/actions/workflows/macos-pack.yml/badge.svg)](https://github.com/jmuelbert/jmbde-QT/actions/workflows/macos-pack.yml)
[![Packaging(Windows)](https://github.com/jmuelbert/jmbde-QT/actions/workflows/windows-pack.yml/badge.svg)](https://github.com/jmuelbert/jmbde-QT/actions/workflows/windows-pack.yml)
[![Codacy Badge][codacy-shield]][codacy-url]
[![Total Alerts][lgtm-alerts-shield]][lgtm-alerts-url]
[![Language grade: C/C++][lgtm-cpp-shield]][lgtm-cpp-url]
[![Language grade: Python][lgtm-python-shield]][lgtm-python-url]
[![Language grade: JavaScript][lgtm-js-shield]][lgtm-js-url]
[![GitHub All Releases][downloads_all-shield]][downloads_all-url]
[![Issues][issues-shield]][issues-url]
[![Help wanted issues][help-issues-shield]][help-issues-url]
[![Pull Requests][pr-shield]][pr-url] 
[![pre-commit][pre-commit-shield]][pre-commit-url]
[![Misspell fixer][misspell_fixer-shield]][misspell_fixer-url]
[![Release](https://img.shields.io/github/release/jmuelbert/jmbde-QT.svg?style=flat-square)](https://github.com/jmuelbert/jmbde-QT/releases)
[![Documentation][documentation-shield]][documentation-url]
[![License][license-shield]][license-url]

[Features](https://github.com/jmuelbert/jmbde-QT) |
[Documentation](https://jmuelbert.github.io/jmbde-QT/) | [Changelog](CHANGELOG.md) |
[Contributing](CONTRIBUTING_de-DE.md) |
[FAQ](https://github.com/jmuelbert/jmbde-QT/wiki/FAQ) | [deutsch](README.md)

## About jmbde

jmbde uses the cross platform framework [Qt](http://www.qt.io/download-open-source/),
which means that it works with most operating systems.

|  type  |                           branch                            |                                                                                                        build                                                                                                         |                                                                     downloads                                                                      |
| :----: | :---------------------------------------------------------: | :------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------: | :------------------------------------------------------------------------------------------------------------------------------------------------: |
| alpha  | [master](https://github.com/jmuelbert/jmbde-QT/tree/master) | [![GitHub Workflow Status](https://github.com/jmuelbert/jmbde-QT/workflows/CI:%20Build%20Test/badge.svg?branch=master&event=push)](https://github.com/jmuelbert/jmbde-QT/actions?query=event%3Apush+branch%3Amaster) |                                                                         -                                                                          |
|  beta  | [v0.5.4](https://github.com/jmuelbert/jmbde-QT/tree/0.5.4)  |  [![GitHub Workflow Status](https://github.com/jmuelbert/jmbde-QT/workflows/CI:%20Build%20Test/badge.svg?branch=0.5.4&event=push)](https://github.com/jmuelbert/jmbde-QT/actions?query=event%3Apush+branch%3A0.5.4)  | [![Downloads](https://img.shields.io/github/downloads/jmuelbert/jmbde-QT/v0.5.4/total)](https://github.com/jmuelbert/jmbde-QT/releases/tag/v0.5.4) |
| stable | [v0.5.4](https://github.com/jmuelbert/jmbde-QT/tree/v0.5.4) |  [![GitHub Workflow Status](https://github.com/jmuelbert/jmbde-QT/workflows/CI:%20Build%20Test/badge.svg?branch=0.5.4&event=push)](https://github.com/jmuelbert/jmbde-QT/actions?query=event%3Apush+branch%3A0.5.4)  | [![Downloads](https://img.shields.io/github/downloads/jmuelbert/jmbde-QT/v0.5.4/total)](https://github.com/jmuelbert/jmbde-QT/releases/tag/v0.5.4) |

| Plattform | Build for Qt6                                                                                       | Build for Qt5                                                                             |
| --------- | --------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------------------------------- |
| Appimage  | ![CD: AppImage Qt6](https://github.com/jmuelbert/jmbde-QT/workflows/CD:%20AppImage%20Qt6/badge.svg) | ![CD: AppImage](https://github.com/jmuelbert/jmbde-QT/workflows/CD:%20AppImage/badge.svg) |
| MacOS     | ![CD: MacOS Qt6](https://github.com/jmuelbert/jmbde-QT/workflows/CD:%20MacOS%20Qt6/badge.svg)       | ![CD: MacOS](https://github.com/jmuelbert/jmbde-QT/workflows/CD:%20MacOS/badge.svg)       |
| Windows   | ![CD: MacOS](https://github.com/jmuelbert/jmbde-QT/workflows/CD:%20MacOS/badge.svg)                 | ![CD: Windows](https://github.com/jmuelbert/jmbde-QT/workflows/CD:%20Windows/badge.svg)   |

## Setup

The program uses the [QT library](https://www.qt.io). Therefore it can be set to almost
every platform can be used. It runs under MacOS, Linux and Windows. Basically an
installer should be used for the installation of the program can be used on one
computer. This installation program is executed on the required QT libraries. For the
use of the program with Windows as operating system is absolutely necessary. With Linux
and macOS can be used on another variant. For these two operating systems QT can be
installed centrally. With these two operating systems only the actual program files are
installed. But also here there are complete installation packages with everything,
including QT.

## Supported platforms

The executable programs and installers are available for the following platforms made
available:

-   macOS from version 10.10
-   Windows as of version 7
-   Linux

## Execute

Below are some helpful hints on how to use jmbde on your native platform.

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

In the following you will find hints for developers how to use jmbde on your native
system. They are not complete guides, but contain information on the necessary measures.
libraries, compile flags, etc.

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

-   Alternatively, you can also
    [download Qt here](https://www.qt.io/download-qt-installer)

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

### on Windows

-   Visual Studio 2017 or higher
-   You can download [Qt here](https://www.qt.io/download-qt-installer)
-   You can install many tools with choco.
    [installation guide](https://chocolatey.org/install#installing-chocolatey)

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

### on Linux

-   On Ubuntu/Debian:
    `sudo apt install qt5-default qttools5-dev-tools zlib1g-dev qtdeclarative5-dev cmake ninja`.
-   On Fedora: `sudo dnf builddep jmbde-QT cmake ninja`.
-   On Arch Linux: `pacman -S qt cmake ninja`

The installed toolchains must match the one with which Qt was compiled.

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

This program is free software: you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation, either
version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this
program. If not, see <https://www.gnu.org/licenses/gpl-3.0.txt>.

Qt is available under several [licenses](https://www.qt.io/licensing/).

GPL V3 © [Jürgen Mülbert](https:/github.com/jmuelbert/jmbde-QT)

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->

[contributors-shield]: https://img.shields.io/github/contributors/jmuelbert/jmbde-QT
[contributors-url]: https://github.com/jmuelbert/jmbde-QT/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/jmuelbert/jmbde-QT
[forks-url]: https://github.com/jmuelbert/jmbde-QT/network/members
[issues-shield]: https://img.shields.io/github/issues-raw/jmuelbert/jmbde-QT
[issues-url]: https://github.com//jmuelbert/jmbde-QT/issues
[license-shield]: https://img.shields.io/github/license/jmuelbert/jmbde-QT
[license-url]: https://github.com//jmuelbert/jmbde-QT/blob/release/LICENSE
[product-screenshot]: images/doc/images/Logo_template.png
[build-shield]:
    https://img.shields.io/github/workflow/status/jmuelbert/jmbde-QT/Build/release
[build-url]: https://github.com/jmuelbert/jmbde-QT/workflows/Build
[gitpod-shield]: https://img.shields.io/badge/Gitpod-Ready--to--Code-blue?logo=gitpod
[gitpod-url]: https://gitpod.io/#https://github.com/jmuelbert/jmbde-QT
[codacy-shield]:
    https://api.codacy.com/project/badge/Grade/caf2526829cb447b9ca6091cccebad27
[codacy-url]:
    https://app.codacy.com/manual/jmuelbert/jmbde-QT?utm_source=github.com&utm_medium=referral&utm_content=jmuelbert/jmbde-QT&utm_campaign=Badge_Grade_Dashboard
[downloads_all-shield]:
    https://img.shields.io/github/downloads/jmuelbert/jmbde-QT/total?label=downloads%40all
[downloads_all-url]: https://github.com/jmuelbert/jmbde-QT/releases
[pre-commit-shield]:
    https://img.shields.io/badge/pre--commit-enabled-brightgreen?logo=pre-commit&logoColor=white
[pre-commit-url]: https://github.com/pre-commit/pre-commit
[misspell_fixer-shield]:
    https://github.com/jmuelbert/jmbde-QT/workflows/Misspell%20fixer/badge.svg
[misspell_fixer-url]: https://github.com/marketplace/actions/misspell-fixer-action
[help-issues-shield]:
    https://img.shields.io/github/issues/jmuelbert/jmbde-QT/help%20wanted
[help-issues-url]:
    https://github.com/jmuelbert/jmbde-QT/issues?q=is%3Aissue+is%3Aopen+label%3A%22help+wanted%22
[documentation-shield]: https://img.shields.io/badge/Documentation-latest-blue.svg
[documentation-url]: https://jmuelbert.github.io/jmbde-QT
[lgtm-alerts-shield]:
    https://img.shields.io/lgtm/alerts/g/jmuelbert/jmbde-QT.svg?logo=lgtm&logoWidth=18
[lgtm-alerts-url]: https://lgtm.com/projects/g/jmuelbert/jmbde-QT/alerts/
[lgtm-cpp-shield]:
    https://img.shields.io/lgtm/grade/cpp/g/jmuelbert/jmbde-QT.svg?logo=lgtm&logoWidth=18
[lgtm-cpp-url]: https://lgtm.com/projects/g/jmuelbert/jmbde-QT/context:cpp
[lgtm-python-shield]:
    https://img.shields.io/lgtm/grade/python/g/jmuelbert/jmbde-QT.svg?logo=lgtm&logoWidth=18
[lgtm-python-url]: https://lgtm.com/projects/g/jmuelbert/jmbde-QT/context:python
[lgtm-js-shield]:
    https://img.shields.io/lgtm/grade/javascript/g/jmuelbert/jmbde-QT.svg?logo=lgtm&logoWidth=18
[lgtm-js-url]: https://lgtm.com/projects/g/jmuelbert/jmbde-QT/context:javascript
[cdash-shield]: https://img.shields.io/badge/CDash-Access-blue.svg
[cdash-url]: http://my.cdash.org/index.php?project=jmbde-QT
[pr-shield]: https://img.shields.io/github/issues-pr-raw/jmuelbert/jmbde-QT.svg
[pr-url]: https://github.com/jmuelbert/jmbde-QT/pulls
