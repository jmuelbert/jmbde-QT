/*
 * EmployeeInputDialog.cpp
 * jmbde
 *
 *  Copyright (c) 2013 Jürgen Mülbert. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the European Union Public Licence (EUPL),
 * version 1.1.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * European Union Public Licence for more details.
 *
 * You should have received a copy of the European Union Public Licence
 * along with this program. If not, see
 * http://www.osor.eu/eupl/european-union-public-licence-eupl-v.1.1
 *
 */


#include "employeeinputdialog.h"
#include "ui_employeeinputdialog.h"

/**
 * @brief EmployeeInputDialog::EmployeeInputDialog
 * @param parent
 */
EmployeeInputDialog::EmployeeInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmployeeInputDialog)
{
    QStringList departmentList = (QStringList()
                                 << QApplication::translate("EMPLOYEEINPUTDIALOG", "DM", 0)
                                 << QApplication::translate("EMPLOYEEINPUTDIALOG", "Accounting", 0)
                                 << QApplication::translate("EMPLOYEEINPUTDIALOG", "Marketing", 0)
                                 << QApplication::translate("EMPLOYEEINPUTDIALOG", "Sales", 0)
                                 << QApplication::translate("EMPLOYEEINPUTDIALOG", "CRM", 0)
                                 << QApplication::translate("EMPLOYEEINPUTDIALOG", "Service", 0)
                                 << QApplication::translate("EMPLOYEEINPUTDIALOG", "Parts", 0)
                                 << QApplication::translate("EMPLOYEEINPUTDIALOG", "IT", 0));
    QStringList functionList = (QStringList()
                                 << QApplication::translate("EMPLOYEEINPUTDIALOG", "GM", 0)
                                 << QApplication::translate("EMPLOYEEINPUTDIALOG", "Accounting Leader", 0)
                                 << QApplication::translate("EMPLOYEEINPUTDIALOG", "Accounting Person", 0)
                                 << QApplication::translate("EMPLOYEEINPUTDIALOG", "Marketing Leader", 0)
                                 << QApplication::translate("EMPLOYEEINPUTDIALOG", "Marketing Person", 0)
                                 << QApplication::translate("EMPLOYEEINPUTDIALOG", "Sales Manager", 0)
                                 << QApplication::translate("EMPLOYEEINPUTDIALOG", "Sales Person", 0)
                                 << QApplication::translate("EMPLOYEEINPUTDIALOG", "CRM Person", 0)
                                 << QApplication::translate("EMPLOYEEINPUTDIALOG", "Service Manager", 0)
                                 << QApplication::translate("EMPLOYEEINPUTDIALOG", "Service Person", 0)
                                 << QApplication::translate("EMPLOYEEINPUTDIALOG", "Parts Manager", 0)
                                 << QApplication::translate("EMPLOYEEINPUTDIALOG", "Parts Person", 0)
                                 << QApplication::translate("EMPLOYEEINPUTDIALOG", "IT", 0));

    ui->setupUi(this);
    ui->comboBoxDepartment->insertItems(0, departmentList);
    ui->comboBoxFunction->insertItems(0, functionList);
}

/**
 * @brief EmployeeInputDialog::~EmployeeInputDialog
 */
EmployeeInputDialog::~EmployeeInputDialog()
{
    delete ui;
}

/**
 * @brief EmployeeInputDialog::on_buttonBox_accepted
 */
void EmployeeInputDialog::on_buttonBox_accepted()
{
    dm = new DataModell;

    dm->setFirstname(new QString(ui->lineEditFirstname->text()));
    dm->setLastname(new QString(ui->lineEditLastname->text()));
    dm->AddEmployee();

}
