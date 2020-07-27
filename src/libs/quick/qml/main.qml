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
// TODO:
// - make designer-friendly

import Qt.labs.platform 1.1 as Platform
import Qt.labs.settings 1.1
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import "models" as Models
import "ui" as Ui

ApplicationWindow {
    // Signals ----------------------

    id: applicationWindow

    property int currentEmployee: -1
    property int margin: 10
    property int theme: Material.theme

    objectName: "window"
    title: qsTr("jmbde")
    visible: true
    // Functions --------------------
    onClosing: {
        close.accepted = true;
        console.log("On closing...");
    }

    // Shortcuts ---------------------
    Shortcut {
        sequence: StandardKey.Open
        onActivated: openDialog.open()
    }

    Shortcut {
        sequence: StandardKey.SaveAs
        onActivated: saveDialog.open()
    }

    Shortcut {
        sequence: StandardKey.Quit
        onActivated: applicationWindow.close()
    }

    Ui.About {
        id: windowAbout
    }

    Ui.Message {
        id: dialogMessage

        modal: true

        footer: DialogButtonBox {
            Button {
                id: buttonDialogMessageOK

                text: qsTr("OK")
                onClicked: dialogMessage.close()
            }

        }

    }

    Platform.FileDialog {
        // onAccepted: document.load(file)

        id: openDialog

        fileMode: Platform.FileDialog.OpenFile
        selectedNameFilter.index: 1
        nameFilters: ["Text files (*.txt, *.csv)"]
        folder: Platform.StandardPaths.writableLocation(Platform.StandardPaths.DocumentsLocation)
    }

    Platform.FolderDialog {
        id: saveDialog

        options: Platform.FolderDialog.ShowDirsOnly
        onAccepted: {
            var saveToURI = folderDialogSaveTo.folder.toString();
            switch (Qt.platform.os) {
            case "windows":
                saveToURI = saveToURI.replace(/^(file:\/{3})/, "");
                break;
            default:
                saveToURI = saveToURI.replace(/^(file:\/{2})/, "");
                break;
            }
            textFieldSaveToDir.text = saveToURI;
            applicationWindow.setSaveToDir(saveToURI);
        }
    }

    Models.EmployeeDialog {
        id: employeeDialog

        onFinished: {
            if (currentEmployee === -1)
                employeeView.model.append(lastName, street, zip, city);
            else
                employeeView.model.set(currentEmployee, lastname, street, zip, city);
        }
    }

    Models.EmployeeView {
        id: employeeView

        anchors.fill: parent
        onPressAndHold: {
            currentEmployee = index;
        }
    }

    RoundButton {
        text: qsTr("+")
        highlighted: true
        anchors.margins: 10
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        onClicked: {
            currentEmployee = -1;
            employeeDialog.createEmployee();
        }
    }

    menuBar: Ui.MenuBar {
        id: menuBar
    }

    header: Ui.ToolBar {
        id: toolBar
    }

    footer: Ui.TabBar {
        id: tabBar
    }

}
