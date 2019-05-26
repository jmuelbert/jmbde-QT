/**************************************************************************
**
** Copyright (c) 2013-2019 Jürgen Mülbert. All rights reserved.
**
** This file is part of jmbde
**
** Licensed under the EUPL, Version 1.2 or – as soon they
** will be approved by the European Commission - subsequent
** versions of the EUPL (the "Licence");
** You may not use this work except in compliance with the
** Licence.
** You may obtain a copy of the Licence at:
**
** https://joinup.ec.europa.eu/page/eupl-text-11-12
**
** Unless required by applicable law or agreed to in
** writing, software distributed under the Licence is
** distributed on an "AS IS" basis,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
** express or implied.
** See the Licence for the specific language governing
** permissions and limitations under the Licence.
**
** Lizenziert unter der EUPL, Version 1.2 oder - sobald
**  diese von der Europäischen Kommission genehmigt wurden -
** Folgeversionen der EUPL ("Lizenz");
** Sie dürfen dieses Werk ausschließlich gemäß
** dieser Lizenz nutzen.
** Eine Kopie der Lizenz finden Sie hier:
**
** https://joinup.ec.europa.eu/page/eupl-text-11-12
**
** Sofern nicht durch anwendbare Rechtsvorschriften
** gefordert oder in schriftlicher Form vereinbart, wird
** die unter der Lizenz verbreitete Software "so wie sie
** ist", OHNE JEGLICHE GEWÄHRLEISTUNG ODER BEDINGUNGEN -
** ausdrücklich oder stillschweigend - verbreitet.
** Die sprachspezifischen Genehmigungen und Beschränkungen
** unter der Lizenz sind dem Lizenztext zu entnehmen.
**
**************************************************************************/

import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.0
import Qt.labs.platform 1.0 as Platform

// For access to locals
import "."

ApplicationWindow {
    id: window
    width: 1024
    height: 720
    minimumWidth: 480
    minimumHeight: 320
    title: qsTr("JMBde Quick")
    visible: true    

    Platform.MessageDialog {
        id: aboutBox
        title: qsTr("About JMBde Quick")
        text: qsTr("This is an experimental Qt Quick version of JMBde")
    }

   Settings {
        id: settings
        property alias windowX: window.x
        property alias windowY: window.y
        property alias windowWidth: window.width
        property alias windowHeight: window.height
        property alias windowVisibility: window.visibility
    }

   Action {
        id: openAction
        text: qsTr("Open...")
        shortcut: StandardKey.Open
        onTriggered: {
   
        }
    }

    Action {
        id: exitAction
        text: qsTr("Exit")
        shortcut: StandardKey.Quit
        onTriggered: Qt.quit()
    }

        menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                action: openAction
                text: qsTr("Open...")
                onTriggered: {

                }
            }
            MenuSeparator {}
            MenuItem {
                text: qsTr("Exit")
                action: exitAction
                onTriggered: Qt.quit()
            }
        }
        Menu {
            title: qsTr("Help")
            MenuItem {
                text: qsTr("About Tiled Quick")
                onTriggered: aboutBox.open()
            }
        }
    }

    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            ToolButton {
                action: openAction

            }
        }
    }

}
