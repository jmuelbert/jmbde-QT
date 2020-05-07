/**************************************************************************
**
** Copyright (c) 2013-2019 Jürgen Mülbert. All rights reserved.
**
** This file is part of jmbde
**
** Licensed under the EUPL, Version 1.2 or – as soon they
** will be approved by the European Commission - subsequent
** versions of the EUPL (the "Licence");
** You may not use this work except in compliance with the
** Licence.
** You may obtain a copy of the Licence at:
**
** https://joinup.ec.europa.eu/page/eupl-text-11-12
**
** Unless required by applicable law or agreed to in
** writing, software distributed under the Licence is
** distributed on an "AS IS" basis,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
** express or implied.
** See the Licence for the specific language governing
** permissions and limitations under the Licence.
**
** Lizenziert unter der EUPL, Version 1.2 oder - sobald
**  diese von der Europäischen Kommission genehmigt wurden -
** Folgeversionen der EUPL ("Lizenz");
** Sie dürfen dieses Werk ausschließlich gemäß
** dieser Lizenz nutzen.
** Eine Kopie der Lizenz finden Sie hier:
**
** https://joinup.ec.europa.eu/page/eupl-text-11-12
**
** Sofern nicht durch anwendbare Rechtsvorschriften
** gefordert oder in schriftlicher Form vereinbart, wird
** die unter der Lizenz verbreitete Software "so wie sie
** ist", OHNE JEGLICHE GEWÄHRLEISTUNG ODER BEDINGUNGEN -
** ausdrücklich oder stillschweigend - verbreitet.
** Die sprachspezifischen Genehmigungen und Beschränkungen
** unter der Lizenz sind dem Lizenztext zu entnehmen.
**
**************************************************************************/

import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.14
import QtQml 2.14
import QtQml.Models 2.14
import Qt.labs.settings 1.1
import Qt.labs.platform 1.1 as Platform

import "."
import "tabs"
import "Theme"

ApplicationWindow {
    id: appWindow
    width: 1024
    height: 768
    minimumWidth: 300
    minimumHeight: 320
    title: qsTr("jmbde Quick")
    visible: true

    readonly property bool inPortrait: appWindow.width < appWindow.height

    Connections {
        target: mainController
//        onError: {
//            errorDialog.text = msg
//            errorDialog.open()
//        }
    }

    Settings {
        category: "WindowState"
        property alias window_x:    appWindow.x
        property alias window_y:    appWindow.y
        property alias window_width: appWindow.width
        property alias window_height: appWindow.height
    }

    onClosing: {
        if ( mainController.canExit() ) {
            close.accepted = true
        } else {
            close.accepted = false
            confirmExitDialog.open()
        }
    }

    Actions {
        id: actions
    }

    menuBar: MainMenu { }

    header: MainToolBar {
        visible: actions.showToolBarAction.checked
    }


    MessageDialog {
        id: errorDialog
        title: qsTr("jmbde Error")
        text: qsTr("Error message should be here!")
    }


    SystemPalette {
        id: systemPalette
    }

    Drawer {
        id: drawer

        y: menuBar.height + header.height
        width: appWindow.width / 2
        height: appWindow.height - overlayHeader.height

        modal: inPortrait
        interactive: inPortrait
        position: inPortrait ? 0 : 1
        visible: !inPortrait

        ListView {
            id: listView
            anchors.fill: parent

            headerPositioning: ListView.OverlayHeader
            header: Pane {
                id: header
                z: 2
                width: parent.width

                contentHeight: logo.height

                Image {
                    id: logo
                    width: parent.width
                    source: "images/qt-logo.png"
                    fillMode: implicitWidth > width ? Image.PreserveAspectFit : Image.Pad
                }

                MenuSeparator {
                    parent: header
                    width: parent.width
                    anchors.verticalCenter: parent.bottom
                    visible: !listView.atYBeginning
                }
            }

            footer: ItemDelegate {
                id: footer
                text: qsTr("Footer")
                width: parent.width

                MenuSeparator {
                    parent: footer
                    width: parent.width
                    anchors.verticalCenter: parent.top
                }
            }

            model: 10

            delegate: ItemDelegate {
                text: qsTr("Title %1").arg(index + 1)
                width: parent.width
            }

            ScrollIndicator.vertical: ScrollIndicator { }
        }
    }

    Flickable {
        id: flickable

        anchors.fill: parent
        anchors.topMargin: menuBar.height + header.height
        anchors.leftMargin: !inPortrait ? drawer.width : undefined

        topMargin: 20
        bottomMargin: 20
        contentHeight: column.height

        Column {
            id: column
            spacing: 20
            anchors.margins: 20
            anchors.left: parent.left
            anchors.right: parent.right

            Label {
                font.pixelSize: 22
                width: parent.width
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                text: qsTr("Side Panel Example")
            }

            Label {
                width: parent.width
                wrapMode: Label.WordWrap
                text: qsTr("This example demonstrates how Drawer can be used as a non-closable persistent side panel.\n\n" +
                           "When the application is in portrait mode, the drawer is an interactive side panel that can " +
                           "be swiped open from the left edge. When the application is in landscape mode, the drawer " +
                           "and the content are laid out side by side.\n\nThe application is currently in %1 mode.").arg(inPortrait ? qsTr("portrait") : qsTr("landscape"))
            }
        }

        ScrollIndicator.vertical: ScrollIndicator { }
    }

    StackView {
        id: mystackview

        initialItem: starting_page

    }



    Component {
        id: starting_page
        StartingPage { }
    }

    Component {
        id: second_page
        SecondPage {}
    }
    Component {
        id: third_page
        ThirdPage {}
    }
    Component {
        id: fourth_page
        FourthPage {}
    }

    function load_page(page) {
        switch (page) {
        case 'Page 1':
            mystackview.push(starting_page);
            break;
        case 'Page 2':
            mystackview.push(second_page);
            break;
        case 'Page 3':
            mystackview.push(third_page);
            break;
        case 'Page 4':
            mystackview.push(fourth_page);
            break;
        }
    }

    footer: TabBar {
        id: tabBar
        width: parent.width
        height: 40
        currentIndex: 0

        TabButton {
            text: qsTr("Tab1")
            onClicked: {
                //
            }
        }

        TabButton {
            text: qsTr("Tab2")
            onClicked: {
                //
            }
        }
    }

    Component.onDestruction: {

    }
}
