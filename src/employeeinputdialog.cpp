/*
 * EmployeeInputDialog.cpp
 * jmbde
 *
 *  Copyright (c) 2013,2014 Jürgen Mülbert. All rights reserved.
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


EmployeeInputDialog::EmployeeInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmployeeInputDialog)
{

    model = new QSqlTableModel(this);
    model->setTable(QLatin1String("employee"));
    model->setEditStrategy(QSqlTableModel::OnFieldChange);


    functionIndex = model->fieldIndex(QLatin1String("function_id"));
    departmentIndex = model->fieldIndex(QLatin1String("department_id"));
    computerIndex = model->fieldIndex(QLatin1String("computer_id"));
    printerIndex = model->fieldIndex(QLatin1String("printer_id"));
    phoneIndex = model->fieldIndex(QLatin1String("phone_id"));
    mobileIndex = model->fieldIndex(QLatin1String("mobile_id"));
    faxIndex = model->fieldIndex(QLatin1String("fax_id"));

/*
    model->setRelation(functionIndex, QSqlRelation(QLatin1String("function"),
                                                  QLatin1String("function_id"),
                                                  QLatin1String("name")));
    model->setRelation(departmentIndex, QSqlRelation(QLatin1String("department"),
                                                    QLatin1String("department_id"),
                                                    QLatin1String("name")));
    model->setRelation(computerIndex, QSqlRelation(QLatin1String("computer"),
                                                   QLatin1String("computer_id"),
                                                   QLatin1String("name")));
    model->setRelation(printerIndex, QSqlRelation(QLatin1String("printer"),
                                                  QLatin1String("printer_id"),
                                                  QLatin1String("name")));
    model->setRelation(phoneIndex, QSqlRelation(QLatin1String("phone"),
                                                QLatin1String("phone_id"),
                                                QLatin1String("name")));
    model->setRelation(mobileIndex, QSqlRelation(QLatin1String("mobile"),
                                                 QLatin1String("mobile_id"),
                                                 QLatin1String("name")));
    model->setRelation(faxIndex, QSqlRelation(QLatin1String("fax"),
                                              QLatin1String("fax_id"),
                                              QLatin1String("name")));
*/
    model->select();

/*
    QSqlTableModel *relFunction = model->relationModel(functionIndex);
    QSqlTableModel *relDepartment = model->relationModel(departmentIndex);
    QSqlTableModel *relComputer = model->relationModel(computerIndex);
    QSqlTableModel *relPrinter = model->relationModel(printerIndex);
    QSqlTableModel *relPhone = model->relationModel(phoneIndex);
    QSqlTableModel *relMobile = model->relationModel(mobileIndex);
    QSqlTableModel *relFax = model->relationModel(faxIndex);
*/



    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    // mapper->setItemDelegate(new QSqlRelationalDelegate(this));
    mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    ui->setupUi(this);

    /*
    if (!relDepartment == 0) {
        ui->comboBoxDepartment->setModel(relDepartment);
        ui->comboBoxDepartment->setModelColumn(relDepartment->fieldIndex(QLatin1String("name")));
    }

    if (!relFunction == 0) {
        ui->comboBoxFunction->setModel(relFunction);
        ui->comboBoxFunction->setModelColumn(relFunction->fieldIndex(QLatin1String("name")));
    }

    if (!relComputer == 0) {
        ui->comboBoxComputer->setModel(relComputer);
        ui->comboBoxComputer->setModelColumn(relComputer->fieldIndex(QLatin1String("name")));
    }

    if (!relPrinter == 0) {
        ui->comboBoxPrinter->setModel(relPrinter);
        ui->comboBoxPrinter->setModelColumn(relPrinter->fieldIndex(QLatin1String("name")));
    }

    if (!relPhone == 0) {
        ui->comboBoxPhone->setModel(relPhone);
        ui->comboBoxPhone->setModelColumn(relPhone->fieldIndex(QLatin1String("name")));
    }

    if (!relMobile == 0) {
        ui->comboBoxMobile->setModel(relMobile);
        ui->comboBoxMobile->setModelColumn(relMobile->fieldIndex(QLatin1String("name")));
    }

    if (!relFax == 0) {
        ui->comboBoxFax->setModel(relFax);
        ui->comboBoxFax->setModelColumn(relFax->fieldIndex(QLatin1String("name")));
    }

    */
    mapper->addMapping(ui->doubleSpinBoxPersNR, model->fieldIndex(QLatin1String("employee_nr")));
    mapper->addMapping(ui->lineEditFirstname, model->fieldIndex(QLatin1String("firstname")) );
    mapper->addMapping(ui->lineEditLastname, model->fieldIndex(QLatin1String("lastname")));
    mapper->addMapping(ui->checkBoxActive, model->fieldIndex(QLatin1String("active")));
    mapper->addMapping(ui->checkBoxDatacare, model->fieldIndex(QLatin1String("datacare")));


    /*
    mapper->addMapping(ui->comboBoxDepartment, departmentIndex);
    mapper->addMapping(ui->comboBoxFunction, functionIndex);
    mapper->addMapping(ui->comboBoxComputer, computerIndex);
    mapper->addMapping(ui->comboBoxPhone, phoneIndex);
    mapper->addMapping(ui->comboBoxMobile, mobileIndex);
    mapper->addMapping(ui->comboBoxFax, faxIndex);
*/

    mapper->toFirst();

}

EmployeeInputDialog::~EmployeeInputDialog()
{
    delete ui;
}

void EmployeeInputDialog::on_buttonBox_accepted()
{
    model->database().commit();
    qDebug() << "Last Error : " << model->database().lastError();
    qDebug() << "OK Clicked!, DB->commit.!";

}

void EmployeeInputDialog::on_nextButton_clicked()
{
    mapper->toNext();
}

void EmployeeInputDialog::on_previousButton_clicked()
{
    mapper->toPrevious();
}

void EmployeeInputDialog::on_buttonBox_rejected()
{
    model->database().rollback();
    qDebug() << "Cancel Clicked!, DB-rollback.!";
}

void EmployeeInputDialog::on_pushButtonNew_clicked()
{
   addRow(model);
}


void EmployeeInputDialog::addRow(QAbstractTableModel *model)
{

   model->insertRow(model->rowCount());
}
