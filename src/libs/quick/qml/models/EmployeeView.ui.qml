/*
    Copyright 2020, Jürgen Mülbert

    This file is part of jmbde.

    jmbde is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    jmbde is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with jmbde. If not, see <http://www.gnu.org/licenses/>.
*/
/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

import Backend 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15

ListView {
    // onPressAndHold: listView.pressAndHold(index)

    id: listView

    signal pressAndHold(int index)

    width: 320
    height: 480
    focus: true
    boundsBehavior: Flickable.StopAtBounds
    section.property: "lastName"
    section.criteria: ViewSection.FirstCharacter

    section.delegate: SectionDelegate {
        width: listView.width
    }

    delegate: EmployeeDelegate {
        id: delegate

        width: listView.width
    }

    model: EmployeeModel {
        id: employeeModel
    }

    ScrollBar.vertical: ScrollBar {
    }

}
