import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQml 2.2

MenuBar {
    Menu {
        title: qsTr("File")
        MenuItem { action: actions.fileNew }
        MenuItem { action: actions.fileOpen}
        MenuItem { action: actions.fileSave }
        MenuSeparator {}
        MenuItem {
            text: qsTr("Preferences")
            iconName: "configure"
            onTriggered: {
                var component = Qt.createComponent("Preferences.qml")
                var dialog = component.createObject(component.prefWindow)
                dialog.open()
            }
        }
        MenuSeparator {}
        MenuItem { action: actions.quitApp}
        //FIXME: if you want you can play around with the style in ./style/dark_blue/MenuStyle.qml
        //style: MyStyle.MenuStyle{}
        }
    Menu {
        title: qsTr("Help")
        MenuItem { action: actions.helpShowAbout }
    }
}
