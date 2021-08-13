# jmbde

jmbde ist ein Programm für das Management von Ressourcen in Unternehmen. Mit diesem
Programm können die Mitarbeiter und die Ausrüstung, die sie für ihre Arbeit benötigen
erfasst werden. Das sind unter anderem Computer, Drucker und Telefone.

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
[FAQ](https://github.com/jmuelbert/jmbde-QT/wiki/FAQ) | [english](README_en.md)


jmbde verwendet das plattformübergreifende Framework
[Qt](http://www.qt.io/download-open-source/), was bedeutet, dass es mit den meisten
Betriebssystemen funktioniert.

## Setup

Das Programm verwendet die [QT-Bibliothek](https://www.qt.io). Daher kann es auf fast
jeder Plattform verwendet werden . Es läuft unter MacOS, Linux und Windows.
Grundsätzlich sollte ein Installer für die Installation des Programms auf einem Computer
verwendet werden. Dieses Installationsprogramm wird auf die benötigten QT-Bibliotheken
mit installieren. Für die Nutzung des Programms bei Windows als Betriebssystem ist dies
zwingend notwendig. Bei Linux und macOS kann auf eine andere Variante verwendet werden.
Bei diesen beiden Betriebssystemen kann QT zentral installiert werden. Bei diesen beiden
Betriebssystemen werden dann nur noch die eigentlichen Programmdateien installiert. Aber
auch hier gibt es komplette Installationspakete mit allem, auch QT.

## Unterstützte Plattformen

Die ausführbaren Programme und Installer werden für die folgenden Plattformen zur
Verfügung gestellt:

-   macOS ab der Version 10.10
-   Windows ab der Version 7
-   Linux

## Ausführen

Im Folgenden finden Sie einige hilfreiche Hinweise, wie Sie jmbde auf Ihrer nativen
Plattform ausführen können.

### Unix

Entpacken Sie die Dateien in ein Verzeichnis und führen Sie sie aus:

```bash
    bin/jmbde
```

### Windows

Entpacken Sie die Dateien in ein Verzeichnis und führen Sie dann jmbde.exe aus.

## macOS

Ziehen Sie jmbde in Ihren Anwendungsordner und führen Sie jmbde aus.

## Anforderungen und Fehlerberichte

-   [GitHub issues (preferred)](https://github.com/jmuelbert/jmbde-QT/issues)

## Fragen und Kommentare

## Wiki

-   [Main Page](https://github.com/jmuelbert/jmbde-QT/wiki)
-   [User Manual](http://jmuelbert.github.io/jmbde-QT/)

## Datenbank Schema

-   [Datenbank Quellcode SQL](docs/database-design.md)

## Code-Quellen

In dem master branch befindet sich der aktuellste Pre-Release Code.

-   [Releases](https://github.com/jmuelbert/jmbde-QT/releases)

-   [Milestones](https://github.com/jmuelbert/jmbde-QT/milestones)

## Programm erstellen

Im Folgenden finden Sie Hinweise für Entwickler, wie Sie jmbde auf Ihrem nativen System
aufbauen können. Sie sind keine vollständigen Leitfäden, sondern enthalten Hinweise zu
den notwendigen Maßnahmen. Bibliotheken, Kompilierungs-Flags, etc.

### Abhängigkeiten

-   Das Programm benötigt qt5 ab der Version 5.12.9
-   cmake ab der Version 3.13.3
-   ninja
-   c++ Entwicklungssystem

#### Auf macOS

-   Die neueste Xcode Version.
-   Brew [Installationsanleitung](https://brew.sh)

```bash
  brew install cmake
  brew install ninja
  brew install qt5
  brew link qt5 --force
```

-   Alternativ können Sie auch
    [Qt hier herunterladen](https://www.qt.io/download-qt-installer)

Führen Sie `cmake` aus, um jmbde zu erstellen:

#### Für die Release-Version

```bash
        mkdir build
        cd build
        cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Release ..
        cmake --build . --target install
        cpack .
```

#### Für die Debug-Version

```bash
        mkdir build
        cd build
        cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Debug ..
        cmake --build .
```

### Unter Windows

-   Visual Studio 2017 oder höher
-   Sie können [Qt hier herunterladen](https://www.qt.io/download-qt-installer)
-   Sie können viele Werkzeuge mit choco installieren.
    [Installationsanleitung](https://chocolatey.org/install#installing-chocolatey)

```cmd
  choco install cmake
  choco install ninja
```

#### Für die Release-Version

```cmd
        mkdir build
        cd build
        cmake -G "Ninja" ....
        cmake --build . --target install
        cpack .
```

#### Für die Debug-Version

```cmd
        mkdir build
        cd build
        cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Debug ..
        cmake --build .
```

### Unter Linux

-   Auf Ubuntu/Debian:
    `sudo apt install qt5-default qttools5-dev-tools zlib1g-dev qtdeclarative5-dev cmake ninja`.
-   Auf Fedora: `sudo dnf builddep jmbde-QT cmake ninja`
-   Auf Arch Linux: `pacman -S qt cmake ninja`

Die installierten Toolchains müssen mit derjenigen übereinstimmen, mit der Qt kompiliert
wurde.

-   Als nächstes kompilieren Sie durch Ausführen:

#### Für die Release-Version

```bash
        mkdir build
        cd build
        cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Release ..
        cmake --build . --target install
        cpack .
```

#### Für die Debug-Version

```bash
        mkdir build
        cd build
        cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Debug ..
        cmake --build .
```

Sie können nun `jmbde` mit dem Befehl `bin/jmbde` aus der Kommandozeile starten.

## Installation

## Lizenz

This program is free software: you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation, either
version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this
program. If not, see <https://www.gnu.org/licenses/gpl-3.0.txt>.

Qt ist unter mehreren [Lizenzen](https://www.qt.io/licensing/) verfügbar.

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
