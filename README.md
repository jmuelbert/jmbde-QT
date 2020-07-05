# jmbde

[![Open in Gitpod](https://gitpod.io/button/open-in-gitpod.svg)](https://gitpod.io/#https://github.com/jmuelbert/jmbde-QT)
[![Total alerts](https://img.shields.io/lgtm/alerts/g/jmuelbert/jmbde-QT.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/jmuelbert/jmbde-QT/alerts/)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
![CI: Build Test](https://github.com/jmuelbert/jmbde-QT/workflows/CI:%20Build%20Test/badge.svg)
[![Build status](https://ci.appveyor.com/api/projects/status/mq9qt36e588dk7ui?svg=true)](https://ci.appveyor.com/project/jmuelbert/jmbde-qt)
[![Build Status](https://travis-ci.org/jmuelbert/jmbde-QT.svg?branch=master)](https://travis-ci.org/jmuelbert/jmbde-QT)

[switch to english version](README.md)

jmbde ist ein Programm für das Management von Ressourcen in Unternehmen. Mit
diesem Programm können die Mitarbeiter und die Ausrüstung, die sie für ihre Arbeit
benötigen erfasst werden. Das sind Computer, Drucker und Telefone.

jmbde verwendet das plattformübergreifende Framework [Qt](http://www.qt.io/download-open-source/),
was bedeutet, dass es mit den meisten Betriebssystemen funktioniert.

## Setup

Das Programm verwendet die [QT-Bibliothek](https://www.qt.io). Daher kann es auf
fast jeder Plattform verwendet werden . Es läuft unter MacOS, Linux und
Windows. Grundsätzlich sollte ein Installer für die Installation des Programms
auf einem Computer verwendet werden. Dieses Installationsprogramm wird auf die
benötigten QT-Bibliotheken mit installieren. Für die Nutzung des Programms bei
Windows als Betriebssystem ist dies zwingend notwendig. Bei Linux und macOS kann
auf eine andere Variante verwendet werden. Bei diesen beiden Betriebssystemen
kann QT zentral installiert werden. Bei diesen beiden Betriebssystemen werden dann
nur noch die eigentlichen Programmdateien installiert. Aber auch hier gibt es
komplette Installationspakete mit allem, auch QT.

## Unterstützte Plattformen

Die ausführbaren Programme und Installer werden für die folgenden Plattformen zur
Verfügung gestellt:

- macOS ab der Version 10.10
- Windows ab der Version 7
- Linux

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

- [GitHub issues (preferred)](https://github.com/jmuelbert/jmbde-QT/issues)

## Fragen und Kommentare

## Wiki

- [Main Page](https://github.com/jmuelbert/jmbde-QT/wiki)
- [User Manual](http://jmuelbert.github.io/jmbde-QT/)

## Datenbank Schema

- [Datenbank Quellcode SQL](docs/database-design.md)

## Code-Quellen

In dem master branch befindet sich der aktuellste Pre-Release Code.

- [Releases](https://github.com/jmuelbert/jmbde-QT/releases)

- [Milestones](https://github.com/jmuelbert/jmbde-QT/milestones)

## Programm erstellen

Im Folgenden finden Sie Hinweise für Entwickler, wie Sie jmbde auf Ihrem
nativen System aufbauen können. Sie sind keine vollständigen Leitfäden, sondern
enthalten Hinweise zu den notwendigen Maßnahmen. Bibliotheken,
Kompilierungs-Flags, etc.

### Abhängigkeiten

- Das Programm benötigt qt5 ab der Version 5.12.5
- cmake ab der Version 3.13.3
- ninja
- c++ Entwicklungssystem

#### Auf macOS

- Die neueste Xcode Version.
- Brew [Installationsanleitung](https://brew.sh)

```bash
  brew install cmake
  brew install ninja
  brew install qt5
  brew link qt5 --force
```

- Alternativ können Sie auch [Qt hier herunterladen](https://www.qt.io/download-qt-installer)

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

- Visual Studio 2017 oder höher
- Sie können [Qt hier herunterladen](https://www.qt.io/download-qt-installer)
- Sie können viele Werkzeuge mit choco installieren. [Installationsanleitung](https://chocolatey.org/install#installing-chocolatey)

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

- Auf Ubuntu/Debian:
  `sudo apt install qt5-default qttools5-dev-tools zlib1g-dev qtdeclarative5-dev cmake ninja`.
- Auf Fedora: `sudo dnf builddep jmbde-QT cmake ninja`
- Auf Arch Linux: `pacman -S qt cmake ninja`

Die installierten Toolchains müssen mit derjenigen übereinstimmen, mit der Qt
kompiliert wurde.

- Als nächstes kompilieren Sie durch Ausführen:

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

Sie können nun `jmbde` mit dem Befehl `bin/jmbde`  aus fer Kommandozeile starten.

## Installation

## Lizenz

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

Qt ist unter mehreren [Lizenzen](https://www.qt.io/licensing/) verfügbar.

GPL V3 © [Jürgen Mülbert](https:/github.com/jmuelbert/jmbde-QT)

[Return to top](#top)
