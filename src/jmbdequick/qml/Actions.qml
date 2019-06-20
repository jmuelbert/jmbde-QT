import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.1
import Qt.labs.settings 1.0

import Theme 1.0

Item {
  id: actions

  Settings {
    category: "VisibleWidgets"
    property alias toolbar_visible: showToolBarAction.checked
  }

    property Action fileNew: Action{
            iconName: "document-new"
            text: qsTr("New")
            //shortcut: StandardKey.New
            onTriggered: {        }
    }

    property Action fileOpen: Action {
        iconName: "document-open"
        text: qsTr("Open")
        shortcut: StandardKey.Open
        enabled: !taskListView.editing
        onTriggered: {
            fileDialog.selectExisting = true
            fileDialog.open()
        }
    }

   property Action fileSave: Action{
        iconName: "document-save"
        iconSource: Theme.iconSource(iconName)
        text: qsTr("Save")
        shortcut: StandardKey.Save
        enabled: !taskListView.editing
        onTriggered: mainController.save()
    }

   property Action showToolBarAction: Action{
        id: showToolBarAction
        iconName: "configure-toolbars"
        iconSource: Theme.iconSource(iconName)
        text: qsTr("Show ToolBar")
        shortcut: "Ctrl+T"
        checkable: true
        checked: true
    }

  property Action quitApp: Action{
    iconName: "application-exit"
     text: qsTr("Exit")
     shortcut: StandardKey.Quit
     onTriggered: appWindow.close()
  }

    property Action helpShowAbout: Action{
        iconName: "help-about"
        iconSource: Theme.iconSource(iconName)
        text: qsTr("About");
        shortcut: "F1"
        onTriggered: {
            var component = Qt.createComponent("AboutBox.qml")
            var dialog = component.createObject(appWindow)
            dialog.open()
        }
    }

    property Action helpShowShortcuts: Action{
        iconName: "help-about"
        text: qsTr("Shortcuts list");
        shortcut: "Ctrl+F1"
        onTriggered: aboutBox.open()
    }


}
