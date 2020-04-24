import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.3

Item {
    RowLayout {
        // anchors.centerIn: parent
        width: parent.width
        Button {
            text: 'Page 1'
            Layout.fillWidth: true
            onClicked: {
                load_page(text);
            }
        }
        Button {
            text: 'Page 2'
            Layout.fillWidth: true
            onClicked: {
                load_page(text);
            }
        }
        Button {
            text: 'Page 3'
            Layout.fillWidth: true
            onClicked: {
                load_page(text);
            }
        }
        Button {
            text: 'Page 4'
            Layout.fillWidth: true
            onClicked: {
                load_page(text);
            }
        }
    }
}
