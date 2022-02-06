/*
    Copyright 2020, Jürgen Mülbert

    This file is part of jmbde.

    jmbde is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    jmbde is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with jmbde. If not, see <http://www.gnu.org/licenses/>.
*/
import QtQml 2.15
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.4

MenuBar {
    Menu {
        title: qsTr("&File")

        Action {
            text: qsTr("&New...")
        }
        Action {
            text: qsTr("&Open...")
        }
        Action {
            text: qsTr("&Save")
        }
        Action {
            text: qsTr("Save &As...")
        }
        MenuSeparator {
        }
        Action {
            text: qsTr("&Quit")
        }
    }
    Menu {
        title: qsTr("&Edit")

        Action {
            text: qsTr("Cu&t")
        }
        Action {
            text: qsTr("&Copy")
        }
        Action {
            text: qsTr("&Paste")
        }
    }
    Menu {
        title: qsTr("&Help")

        Action {
            text: qsTr("&About")
        }
    }
}
