import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Dialogs 1.2

Dialog {
    id: aboutdialog

    width: 640
    title: qsTr("About jmbde")
    standardButtons: StandardButton.Ok
    Component.onDestruction: console.log("Tschüüüs.")
    onVisibleChanged: {
        if (visible === false)
            destroy();

    }

    Text {
        wrapMode: Text.WordWrap
        width: aboutdialog.width
        text: qsTr("<h1>About jmbde</h1>\\n\\n<p>jmbde is a cross-platform tool to collect the data of a company.\\n(see <a href=\"https://jmuelbert.github.io/jmbde-QT\">https://jmuelbert.github.io/jmbde-QT</a></p>\\nCopyright &copy Jürgen Mülbert 2019<br />\\n<h2>Links</h2>\\n<ul>\\n<li>Project Page: <a href=\"https://github.com/jmuelbert/jmbde-QT\">https://github.com/jmuelbert/jmbde-QT</a></li>\\n<li>Project Docu: <a href=\"https://jmuelbert.github.io/jmbde-QT\">https://jmuelbert.github.io/jmbde-QT</a></li>\\n<li>Project Wiki: <a href=\"https://github.com/jmuelbert/jmbde-QT/wiki\">https://github.com/jmuelbert/jmbde-QT/wiki</a>/li>\\n</ul>\\n<h2>Credits</h2>\\n<ul>\\n<li>Icons by <a href=\"http://tango.freedesktop.org/\">The Tango! Desktop Project</a>\\nand <a href=\"http://www.famfamfam.com/lab/icons/silk/\">Mark James</a></li>\\n</ul>\\n<h2>License</h2>\\n<p>This program is free software: you can redistribute it and/or modify\\nit under the terms of the GNU General Public License as published by\\nthe Free Software Foundation, either version 3 of the License, or\\n(at your option) any later version.</p>\\n<p>This program is distributed in the hope that it will be useful,\\nbut WITHOUT ANY WARRANTY; without even the implied warranty of\\nMERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\\nGNU General Public License for more details.</p>\\n<p>You should have received a copy of the GNU General Public License\\nalong with this program.  If not, see\\n<a href=\"http://www.gnu.org/licenses/\">http://www.gnu.org/licenses/</a>.</p>\\n")
        onLinkActivated: Qt.openUrlExternally(link)
        rightPadding: 5
        leftPadding: 5
        bottomPadding: 5
        topPadding: 5

        MouseArea {
            anchors.rightMargin: 5
            anchors.leftMargin: 5
            anchors.bottomMargin: 5
            anchors.topMargin: 5
            anchors.fill: parent
            acceptedButtons: Qt.NoButton
            cursorShape: parent.hoveredLink ? Qt.PointingHandCursor : Qt.ArrowCursor
        }

    }

}
