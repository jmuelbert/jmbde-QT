/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

import QtQuick 2.15
import QtQuick.Controls 2.15

Dialog {
    id: dialog

    signal finished(string lastName, string street, string zip, string city)

    function createEmployee() {
        form.lastName.clear();
        form.street.clear();
        form.zip.clear();
        form.city.clear();
        dialog.title = qsTr("Add Employee");
        dialog.open();
    }

    function editEmployee(employee) {
        form.lastName.text = employee.lastName;
        form.street.text = employee.street;
        form.zip.text = employee.zip;
        form.city.text = employee.city;
        dialog.title = qsTr("Edit Employee");
        dialog.open();
    }

    x: parent.width / 2 - width / 2
    y: parent.height / 2 - height / 2
    focus: true
    modal: true
    title: qsTr("Add Employee")
    standardButtons: Dialog.Ok | Dialog.Cancel
    onAccepted: finished(form.lastName.text, form.street.text, form.zip.text, form.city.text)

    contentItem: EmployeeForm {
        id: form
    }

}
