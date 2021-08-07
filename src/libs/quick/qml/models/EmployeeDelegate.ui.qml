/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

/*##^##

Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ItemDelegate {
    id: delegate

    checkable: true
    states: [
        State {
            name: "expanded"
            when: delegate.checked

            PropertyChanges {
                target: grid
                visible: true
            }

        }
    ]

    contentItem: ColumnLayout {
        spacing: 10

        Label {
            text: lastName
            font.bold: true
            elide: Text.ElideRight
            Layout.fillWidth: true
        }

        GridLayout {
            id: grid

            visible: false
            columns: 2
            rowSpacing: 10
            columnSpacing: 10

            Label {
                text: qsTr("Address:")
                Layout.leftMargin: 60
            }

            Label {
                text: street
                font.bold: true
                elide: Text.ElideRight
                Layout.fillWidth: true
            }

            Label {
                text: qsTr("zip:")
                Layout.leftMargin: 60
            }

            Label {
                text: zip
                font.bold: true
                elide: Text.ElideRight
                Layout.fillWidth: true
            }

            Label {
                text: qsTr("City:")
                Layout.leftMargin: 60
            }

            Label {
                text: street
                font.bold: true
                elide: Text.ElideRight
                Layout.fillWidth: true
            }

        }

    }

}
