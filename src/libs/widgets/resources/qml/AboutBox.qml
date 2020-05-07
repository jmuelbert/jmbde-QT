import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Dialogs 1.2


Dialog {
  width: 640
  title: qsTr('About jmbde')
  id: aboutdialog

  Text {
      wrapMode: Text.WordWrap
      width: aboutdialog.width
      text: qsTr('<h1>About jmbde</h1>

<p>jmbde is a cross-platform tool to collect the data of a company.
(see <a href="https://jmuelbert.github.io/jmbde-QT">https://jmuelbert.github.io/jmbde-QT</a></p>
Copyright &copy Jürgen Mülbert 2019<br />
<h2>Links</h2>
<ul>
<li>Project Page: <a href="https://github.com/jmuelbert/jmbde-QT">https://github.com/jmuelbert/jmbde-QT</a></li>
<li>Project Docu: <a href="https://jmuelbert.github.io/jmbde-QT">https://jmuelbert.github.io/jmbde-QT</a></li>
<li>Project Wiki: <a href="https://github.com/jmuelbert/jmbde-QT/wiki">https://github.com/jmuelbert/jmbde-QT/wiki</a>/li>
</ul>
<h2>Credits</h2>
<ul>
<li>Icons by <a href="http://tango.freedesktop.org/">The Tango! Desktop Project</a>
and <a href="http://www.famfamfam.com/lab/icons/silk/">Mark James</a></li>
</ul>
<h2>License</h2>
<p>This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.</p>
<p>This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.</p>
<p>You should have received a copy of the GNU General Public License
along with this program.  If not, see
<a href="http://www.gnu.org/licenses/">http://www.gnu.org/licenses/</a>.</p>
')
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
    standardButtons: StandardButton.Ok
    onVisibleChanged: if (visible === false) destroy()
    Component.onDestruction: console.log("Tschüüüs.")
}
