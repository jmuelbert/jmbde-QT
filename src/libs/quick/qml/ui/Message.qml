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

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15

Dialog {
    function setIcon(text) {
        labelMessageIcon.text = text;
    }

    function setText(text) {
        labelMessageText.text = text;
    }

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2
    closePolicy: Popup.NoAutoClose

    FontLoader {
        // source: "qrc:/fonts/materialdesignicons-webfont.ttf"

        id: fontMDI
    }

    FontLoader {
        id: fontFontello

        source: "qrc:/fonts/fontello.ttf"
    }

    ColumnLayout {
        id: columnLayoutMessage

        anchors.fill: parent

        RowLayout {
            id: rowLayoutMessageText

            Layout.fillWidth: true
            Layout.alignment: Qt.AlignLeft | Qt.AlignCenter
            spacing: 10

            Label {
                id: labelMessageIcon

                font.family: fontMDI.name
                font.pointSize: labelMessageText.font.pointSize * 3
            }

            Label {
                id: labelMessageText

                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.fillWidth: true
                Layout.minimumWidth: 200
                Layout.maximumWidth: 300
                textFormat: Text.RichText
                wrapMode: Text.WordWrap
            }

        }

    }

}
