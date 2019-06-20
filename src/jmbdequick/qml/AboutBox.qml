import QtQuick 2.12
import QtQuick.Controls 1.4
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
(see <a href="https://jmuelbert.github.io/jmbde-python">https://jmuelbert.github.io/jmbde-python</a></p>
Copyright &copy Jürgen Mülbert 2019<br />
<h2>Links</h2>
<ul>
<li>Project Page: <a href="https://github.com/jmuelbert/jmbde-python">https://github.com/jmuelbert/jmbde-python</a></li>
<li>Project Docu: <a href="https://jmuelbert.github.io/jmbde-python">https://jmuelbert.github.io/jmbde-python</a></li>
<li>Project Wiki: <a href="https://github.com/jmuelbert/jmbde-python/wiki">https://github.com/jmuelbert/jmbde-python/wiki</a>/li>
</ul>
<h2>Credits</h2>
<ul>
   <li>Icons by <a href="http://tango.freedesktop.org/">The Tango! Desktop Project</a>
        and <a href="http://www.famfamfam.com/lab/icons/silk/">Mark James</a></li>
</ul>
<h2>License</h2>
<p>
Licensed under the EUPL, Version 1.2 or – as soon they
will be approved by the European Commission - subsequent
versions of the EUPL (the "Licence");
You may not use this work except in compliance with the Licence.
You may obtain a copy of the Licence at: <br />

<a href="https://joinup.ec.europa.eu/page/eupl-text-11-12">https://joinup.ec.europa.eu/page/eupl-text-11-12</a>.</p>
')
        onLinkActivated: Qt.openUrlExternally(link)

        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.NoButton
            cursorShape: parent.hoveredLink ? Qt.PointingHandCursor : Qt.ArrowCursor
        }
    }
    standardButtons: StandardButton.Ok
  onVisibleChanged: if (visible === false) destroy()
    Component.onDestruction: console.log("Tschüüüs.")
}

