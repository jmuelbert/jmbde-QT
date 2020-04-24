import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Dialogs 1.2
import Qt.labs.settings 1.1

import "Theme"

Item {
  id: actions

  Settings {
    category: "VisibleWidgets"
    property alias search_field_visible: showSearchAction.checked
    property alias toolbar_visible: showToolBarAction.checked
  }

    property Action fileNew: Action {
            icon.name: "document-new"
            text: qsTr("New")
            shortcut: StandardKey.New
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
        icon.source: Theme.iconSource(icon.name)
        text: qsTr("Save")
        shortcut: StandardKey.Save
        enabled: !taskListView.editing
        onTriggered: mainController.save()
    }

  property Action quitApp: Action{
      icon.name: "application-exit"
      text: qsTr("Exit")
      shortcut: StandardKey.Quit
      onTriggered: appWindow.close()
  }

  property Action showSearchAction: Action {
       id: showSearchAction
       icon.name: "search"
       icon.source: Theme.iconSource(icon.name)
       text: qsTr("Show Search Field")
       shortcut: "Ctrl+F"
       checkable: true
   }

   property Action showFilterPanel: Action {
       id: showFilterPanel
       icon.name: "view-filter"
       icon.source: Theme.iconSource(icon.name)
       text: qsTr("Show Filter Panel")
       checkable: true
       checked: true
   }

   property Action showToolBarAction: Action {
       id: showToolBarAction
       icon.name: "configure-toolbars"
       icon.source: Theme.iconSource(icon.name)
       text: qsTr("Show ToolBar")
       shortcut: "Ctrl+T"
       checkable: true
       checked: true
   }



    property Action helpShowAbout: Action {
        icon.name: "configure-toolbars"
        icon.source: Theme.iconSource(icon.name)
        text: qsTr("About");
        shortcut: "F1"
        onTriggered: {
            var component = Qt.createComponent("AboutBox.qml")
            var dialog = component.createObject(appWindow)
            dialog.open()
        }
    }

    property Action helpShowShortcuts: Action {
        icon.name: "help-about"
        text: qsTr("Shortcuts list");
        shortcut: "Ctrl+F1"
        onTriggered: aboutBox.open()
    }

  FileDialog {
        id: fileDialog
        nameFilters: ["Text files (*.txt)"]
        folder: mainController.docPath
        onAccepted: {
            if (fileDialog.selectExisting) {
                mainController.open(fileUrl)
            } else {
                mainController.save(fileUrl)
            }
        }
    }

    FileDialog {
        id: linkDialog
        selectExisting: true
        onAccepted: {
            taskListView.storeSelection()
            var path = fileUrl.toString()
            path = path.replace(/ /g, "%20")
            taskListView.currentItem.task.text += ' ' + path
            taskListView.restoreSelection()
        }
    }
}
