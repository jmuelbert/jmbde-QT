import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.14
import TableModel 0.1

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("jmbde")

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            Action {
                text: qsTr("&New...")
            }
            Action {
                text: qsTr("&Open...")
            }
            Action {
                text: qsTr("&Save")
            }
            Action {
                text: qsTr("Save &As...")
            }
            MenuSeparator {}
            Action {
                text: qsTr("&Quit")
            }
        }
        Menu {
            title: qsTr("&Edit")
            Action {
                text: qsTr("Cu&t")
            }
            Action {
                text: qsTr("&Copy")
            }
            Action {
                text: qsTr("&Paste")
            }
        }
        Menu {
            title: qsTr("&Help")
            Action {
                text: qsTr("&About")
            }
        }
    }

    header: ToolBar {
        RowLayout {
            anchors.fill: parent

            ToolButton {
                text: qsTr("<")
                onClicked: stack.pop()
            }

            Label {
                text: qsTr("Title")
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }

            ToolButton {
                text: qsTr("⋮")
                onClicked: menu.open()
            }
        }
    }

    footer: TabBar {// ...
    }

    StackView {
        id: stack
        anchors.fill: parent
        RowLayout {

            id: layout
            anchors.fill: parent
            spacing: 6

            Rectangle {
                color: 'teal'
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.minimumWidth: 20
                Layout.preferredWidth: 50
                Layout.maximumWidth: 100
                Layout.minimumHeight: 150

                ListModel {
                    id: outlineViewSelectItem

                    ListElement {
                        name: qsTr("Employee")
                    }

                    ListElement {
                        name: qsTr("Computer")
                    }

                    ListElement {
                        name: qsTr("Printer")
                    }
                }

                Component {
                    id: outlineViewDelegate
                    ToolButton {
                        width: 75
                        height: 50
                        // anchors.fill: parent
                        text: name
                        onClicked: {

                            // send(name) to the main Controller
                        }
                    }
                }

                ListView {
                    id: listView
                    anchors.fill: parent

                    contentWidth: headerItem.width
                    flickableDirection: Flickable.HorizontalAndVerticalFlick

                    header: Row {
                        spacing: 1
                        function itemAt(index) {
                            return repeater.itemAt(index)
                        }
                        Repeater {
                            id: repeater
                            model: [qsTr("Select")]
                            Label {
                                text: modelData
                                font.bold: true
                                font.pixelSize: 20
                                padding: 10
                                background: Rectangle {
                                    color: "silver"
                                }
                            }
                        }
                    }

                    model: outlineViewSelectItem
                    delegate: outlineViewDelegate
                    ScrollIndicator.horizontal: ScrollIndicator {}
                    ScrollIndicator.vertical: ScrollIndicator {}
                }
            }

            Rectangle {
                color: 'plum'
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.minimumWidth: 100
                Layout.preferredWidth: 200
                Layout.preferredHeight: 100

                TableView {
                    anchors.fill: parent
                    columnSpacing: 1
                    rowSpacing: 1
                    clip: true

                    id: tableView

                    topMargin: header.implicitHeight

                    Text {
                        id: header
                        text: "A table header"
                    }

                    model: TableModel { }

                    delegate: Rectangle {
                        implicitWidth: 100
                        implicitHeight: 50
                        border.width: 1

                        Text {
                            text: display
                            anchors.centerIn: parent
                        }
                    }
                }
            }
        }
    }
}
