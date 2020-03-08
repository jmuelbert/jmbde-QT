import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

ToolBar {
  RowLayout {
    anchors.fill: parent
    ToolButton { action: actions.fileSave }
    ToolBarSeparator { }
    Item { Layout.fillWidth: true }
  }
}
