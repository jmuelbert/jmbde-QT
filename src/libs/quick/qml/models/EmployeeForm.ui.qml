/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

GridLayout {
    id: grid

    property alias firstName: firstName
    property alias lastName: lastName
    property alias street: street
    property alias zip: zip
    property alias city: city
    property int minimumInputSize: 120
    property string placeholderText: qsTr("<enter>")

    rows: 4
    columns: 2

    Label {
        text: qsTr("First Name")
        Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
    }

    TextField {
        id: firstName

        Layout.fillWidth: true
        Layout.minimumWidth: grid.minimumInputSize
        Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
        placeholderText: grid.placeholderText
    }

    Label {
        text: qsTr("Last Name")
        Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
    }

    TextField {
        id: lastName

        focus: true
        Layout.fillWidth: true
        Layout.minimumWidth: grid.minimumInputSize
        Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
        placeholderText: grid.placeholderText
    }

    Label {
        text: qsTr("Street")
        Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
    }

    TextField {
        id: street

        Layout.fillWidth: true
        Layout.minimumWidth: grid.minimumInputSize
        Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
        placeholderText: grid.placeholderText
    }

    Label {
        text: qsTr("Zip")
        Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
    }

    TextField {
        id: zip

        Layout.fillWidth: true
        Layout.minimumWidth: grid.minimumInputSize
        Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
        placeholderText: grid.placeholderText
    }

    Label {
        text: qsTr("City")
        Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
    }

    TextField {
        id: city

        Layout.fillWidth: true
        Layout.minimumWidth: grid.minimumInputSize
        Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
        placeholderText: grid.placeholderText
    }

}
