import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.12

ToolBar {
    id: overlayHeader

    z: 1
    width: parent.width
    parent: window.overlay

    RowLayout {
        anchors.fill: parent
        ToolButton {
            text: ":::"
            onClicked:  drawer.open()
        }
        ToolButton { action: actions.showSearchAction}
        ToolButton { action: actions.showFilterPanel}
        ToolBarSeparator { }
        ToolButton { action: actions.fileSave }
        Item { Layout.fillWidth: true }
    }
}
