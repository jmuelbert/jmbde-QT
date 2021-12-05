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
import QtQuick 2.14
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15

Dialog {
    x: (parent.width - width) / 2
    y: (parent.height - height) / 2
    modal: true

    ColumnLayout {
        id: columnLayoutAbout
        anchors.fill: parent

        RowLayout {
            id: rowLayoutAboutText
            spacing: 20

            Image {
                id: imageAboutLogo
                Layout.alignment: Qt.AlignTop
                source: "qrc:/images/baseline-category-24px.svg"

                sourceSize {
                    height: 86
                    width: 86
                }
            }
        }
        Label {
            id: labelAboutText
            text: "<style>< { color: " + Material.accent + "; }</style>" + "<p><b>jmbde V0.6.0</b></p>" + "<p>" + qsTr("jmbde is a BDE Application") + "<p>" + qsTr("Author: ") + "<a href=”https://github.com/jmuelbert/jmbde-QT\"" + " Jürgen Mülbert" + "</a><br/>" + qsTr("License: ") + "<a href=\"https://github.com/jmuelbert/jmbde-QT\">GPL-V3 License</a>" + "/p>"
            Layout.preferredWidth: 300
            Layout.maximumWidth: 300
            onLinkActivated: Qt.openUrlExternally(link)
            textFormat: Text.RichText
            wrapMode: Text.WordWrap
        }
    }
}
