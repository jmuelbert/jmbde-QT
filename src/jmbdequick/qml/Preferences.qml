import QtQuick 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.4
import Qt.labs.settings 1.0

Dialog {
    id: prefWindow

  Settings {
        category: "Preferences"
        property alias databaseType: cbDatabaseType.currentText
        property alias databaseConnection: textDBConnection.text
        property alias databaseHostName: textInputHostname.text
        property alias databaseUserName: textInputUsername.text
        property alias databasePassword: textInputPassword.text

    }

   ColumnLayout {
        id: col
        width: 200
        height: 400
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
            currentIndex: 2
            model: ["None", "SQLite", "mysql", "pgsql", "odbc"]

            onCurrentIndexChanged: {
                console.debug(cbDatabaseType.currentText)
            }

        }

        Label {
            id: labelDatabaseConnection
            text: qsTr("DB-Connection")

            TextInput {
                id: textDBConnection
                x: 100
                y: 0
                width: 80
                height: 20
                text: qsTr("DB Connection")
                font.family: "Tahoma"
                font.pixelSize: 12
            }

            Button {
                id: selectFile
                x: 201
                y: 0
                text: "..."
                onClicked:
                    console.debug("Button clicked")
            }
        }

        Label {
            id: labelHostName
            text: qsTr("Hostname")

            TextInput {
                id: textInputHostname
                x: 100
                y: 0
                width: 80
                height: 20
                text: qsTr("Hostname")
                font.family: "Tahoma"
                font.pixelSize: 12
            }
        }

        Label {
            id: labelUserName
            text: qsTr("Username")

            TextInput {
                id: textInputUsername
                x: 100
                y: 0
                width: 80
                height: 20
                text: qsTr("Username")
                font.family: "Tahoma"
                font.pixelSize: 12
            }
        }

        Label {
            id: labelPassword
            width: 62
            text: qsTr("Password")

            TextInput {
                id: textInputPassword
                x: 100
                y: 0
                width: 80
                height: 20
                text: qsTr("Password")
                cursorVisible: true
                renderType: Text.NativeRendering
                echoMode: TextInput.PasswordEchoOnEdit
                font.pixelSize: 12
            }
        }
    }


    standardButtons: StandardButton.Ok
    onVisibleChanged: if (visible == false) destroy()
}
