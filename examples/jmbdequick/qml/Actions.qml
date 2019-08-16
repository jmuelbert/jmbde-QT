import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2
import Qt.labs.settings 1.1

import "./Theme" as Theme

Item {
  id: actions

  Settings {
    category: "VisibleWidgets"
    property alias toolbar_visible: showToolBarAction.checked
  }

    property Action fileNew: Action{
            icon.name: "document-new"
            text: qsTr("New")
            //shortcut: StandardKey.New
            onTriggered: {        }
    }

    property Action fileOpen: Action {
        icon.name: "document-open"
        text: qsTr("Open")
        shortcut: StandardKey.Open
        enabled: !taskListView.editing
        onTriggered: {
            fileDialog.selectExisting = true
            fileDialog.open()
        }
    }

   property Action fileSave: Action{
        icon.name: "document-save"
        icon.source: Theme.icon.source(icon.name)
        text: qsTr("Save")
        shortcut: StandardKey.Save
        enabled: !taskListView.editing
        onTriggered: mainController.save()
    }

   property Action showToolBarAction: Action{
        id: showToolBarAction
        icon.name: "configure-toolbars"
        icon.source: Theme.icon.source(icon.name)
        text: qsTr("Show ToolBar")
        shortcut: "Ctrl+T"
        checkable: true
        checked: true
    }

  property Action quitApp: Action{
    icon.name: "application-exit"
     text: qsTr("Exit")
     shortcut: StandardKey.Quit
     onTriggered: appWindow.close()
  }

    property Action helpShowAbout: Action{
        icon.name: "help-about"
        icon.source: Theme.icon.source(icon.name)
        text: qsTr("About");
        shortcut: "F1"
        onTriggered: {
            var component = Qt.createComponent("AboutBox.qml")
            var dialog = component.createObject(appWindow)
            dialog.open()
        }
    }

    property Action helpShowShortcuts: Action{
        icon.name: "help-about"
        text: qsTr("Shortcuts list");
        shortcut: "Ctrl+F1"
        onTriggered: aboutBox.open()
    }
}
