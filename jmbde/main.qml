import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.0

import "content"

ApplicationWindow {
    visible: true
    title: "JMBDE (c) 2013-2014 Jürgen Mülbert"

    width: 640
    height: 420
    minimumHeight: 400
    minimumWidth: 600

    FileDialog {
        id: fileDialog
        nameFilters: [ "Image files (*.png *.jpg)" ]
    }

    AboutDialog { id: aboutDialog }

    Action {
        id: openAction
        text: "&Open"
        shortcut: StandardKey.Open
        iconSource: "images/document-open.png"
        onTriggered: fileDialog.open()
        tooltip: "Open a image"
    }

    Action {
        id: aboutAction
        text: "About"
        onTriggered: aboutDialog.open()
    }


    toolBar: ToolBar {
        id: toolbar
        RowLayout {
            id: toolbarLayout
            spacing: 0
            width: parent.width
            ToolButton {
                iconSource: "images/document-new.png"
                // onClicked: <action>
                Accessible.name: "New Window"
                tooltip: "Toggle visibility of the second window"
            }
            ToolButton { action: openAction }
        }
    }

    menuBar: MenuBar {
        Menu {
            title: "&File"
            MenuItem { action: openAction }
            MenuItem {
                text: "Close"
                shortcut: StandardKey.Quit
                onTriggered: Qt.quit()
            }
        }
        Menu {
            title: "&Help"
            MenuItem { action: aboutAction }
        }
    }

    SystemPalette {id: syspal}
    color: syspal.window

    TabView {
        id: frame
        enabled: enabledCheck.checked
        tabPosition: employeePage.item ? employeePage.item.tabPosition : Qt.TopEdge
        anchors.fill:  parent
        anchors.margins: Qt.platform.os == "osx" ? 12 : 2

        Tab {
            id: employeePage
            title:  "Employee"

        }
        Tab {
            id: computerPage
            title: "Computer"

        }
    }
}
