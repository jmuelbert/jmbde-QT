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

import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.12
import QtQml 2.12
import QtQml.Models 2.12
import Qt.labs.settings 1.1
import Qt.labs.platform 1.0 as Platform

// For access to locals
// import "./MainMenu.qml"
// import "./MainToolBar.qml"
// import "./Actions.qml"
import "./Theme" as Theme

ApplicationWindow {
    id: appWindow
    width: 1024
    height: 720
    minimumWidth: 480
    minimumHeight: 320
    title: qsTr("jmbde Quick")
    visible: true

    // Connections {
    //  target: mainController
    //      onError: {
    //          errorDialog.text = msg
    //          errorDialog.open()
    //      }
    //  }

    Settings {
        category: "WindowState"
        property alias window_x:    appWindow.x
        property alias window_y:    appWindow.y
        property alias window_width: appWindow.width
        property alias window_height: appWindow.height
    }

    onClosing: { }

    Actions {
        id: actions
    }

    menuBar: MainMenu { }

    header: MainToolBar {
         visible: actions.showToolBarAction.checked
       }

    MessageDialog {
           id: errorDialog
           title: "QTodotTxt Error"
           text: "Error message should be here!"
       }

    Platform.MessageDialog {
        id: aboutBox
        title: qsTr("About JMBde Quick")
        text: qsTr("This is an experimental Qt Quick version of JMBde")
    }
}
