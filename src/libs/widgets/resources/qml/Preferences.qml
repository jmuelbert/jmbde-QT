import Qt.labs.settings 1.1
import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.12

Dialog {
    id: prefWindow

    width: 600
    height: 400
    standardButtons: StandardButton.Ok
    onVisibleChanged: {
        if (visible === false)
            destroy();

    }

    Settings {
        property alias type: cbDatabaseType.currentIndex
        property alias connection: textDBConnection.text
        property alias hostname: textInputHostname.text
        property alias username: textInputUsername.text
        property alias password: textInputPassword.text

        category: "Database"
    }

    ColumnLayout {
        id: col

        spacing: 6
        anchors.fill: parent

        Text {
            text: qsTr("Preferences")
            font.bold: true
            font.pointSize: 24
            elide: Text.ElideRight
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            horizontalAlignment: Text.AlignLeft
        }

        ComboBox {
            id: cbDatabaseType

            width: 200
            model: ["None", "SQLite", "mysql", "pgsql", "odbc"]
            onCurrentIndexChanged: {
                console.debug(cbDatabaseType.currentText);
            }
        }

        Label {
            id: labelDatabaseConnection

            text: qsTr("DB-Connection")

            TextField {
                id: textDBConnection

                x: 100
                y: 0
                width: 350
                height: 20
                font.family: "Tahoma"
                font.pixelSize: 12
            }

            Button {
                id: selectFile

                x: 470
                y: -9
                text: "..."
                onClicked: console.debug("Button clicked")
            }

        }

        Label {
            id: labelHostName

            text: qsTr("Hostname")

            TextField {
                id: textInputHostname

                x: 100
                y: 0
                width: 350
                height: 20
                font.family: "Tahoma"
                font.pixelSize: 12
            }

        }

        Label {
            id: labelUserName

            text: qsTr("Username")

            TextField {
                id: textInputUsername

                x: 100
                y: 0
                width: 350
                height: 20
                font.family: "Tahoma"
                font.pixelSize: 12
            }

        }

        Label {
            id: labelPassword

            width: 62
            text: qsTr("Password")

            TextField {
                id: textInputPassword

                x: 100
                y: 0
                width: 350
                height: 20
                cursorVisible: true
                echoMode: TextInput.PasswordEchoOnEdit
                font.pixelSize: 12
            }

        }

    }

}
