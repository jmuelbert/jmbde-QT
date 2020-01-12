import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.12

ToolBar {
    RowLayout {
        anchors.fill: parent
        ToolButton { action: actions.showSearchAction}
        ToolButton { action: actions.showFilterPanel}
        ToolBarSeparator { }
        ToolButton { action: actions.fileSave }
        Item { Layout.fillWidth: true }
    }
}
