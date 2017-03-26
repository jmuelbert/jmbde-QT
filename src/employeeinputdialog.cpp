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
    // Init UI
    ui->setupUi(this);

    preSetFields();

    // Set the Model
    model = new QSqlTableModel(this);
    model->setTable(QLatin1String("employee"));
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    // Set the indexes for the relations
    functionIndex = model->fieldIndex(QLatin1String("function_id"));
    departmentIndex = model->fieldIndex(QLatin1String("department_id"));
    computerIndex = model->fieldIndex(QLatin1String("computer_id"));
    printerIndex = model->fieldIndex(QLatin1String("printer_id"));
    phoneIndex = model->fieldIndex(QLatin1String("phone_id"));
    mobileIndex = model->fieldIndex(QLatin1String("mobile_id"));
    faxIndex = model->fieldIndex(QLatin1String("fax_id"));

    model->select();

    // Set the mapper
    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    // Set the fields to the mapper
    mapper->addMapping(ui->doubleSpinBoxPersNR, model->fieldIndex(QLatin1String("employee_nr")));
    mapper->addMapping(ui->lineEditFirstname, model->fieldIndex(QLatin1String("firstname")) );
    mapper->addMapping(ui->lineEditLastname, model->fieldIndex(QLatin1String("lastname")));
    mapper->addMapping(ui->checkBoxActive, model->fieldIndex(QLatin1String("active")));
    mapper->addMapping(ui->checkBoxDatacare, model->fieldIndex(QLatin1String("datacare")));
    mapper->addMapping(ui->comboBoxGender, model->fieldIndex(QLatin1String("gender")));

    // To the last row to adding a dataset
    mapper->toLast();
    int row = mapper->currentIndex();
    mapper->submit();
    model->insertRow(row);
    mapper->setCurrentIndex(row);

    ui->doubleSpinBoxPersNR->setValue(1);
    ui->lineEditFirstname->clear();
    ui->lineEditFirstname->setFocus();
    ui->lineEditLastname->clear();
}

EmployeeInputDialog::EmployeeInputDialog(QWidget *parent, int index) :
    QDialog (parent),
    ui(new Ui::EmployeeInputDialog)
{
    // Init UI
    ui->setupUi(this);

    // Set the Model
    model = new QSqlTableModel(this);
    model->setTable(QLatin1String("employee"));
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    // Set the indexes for the relations
    functionIndex = model->fieldIndex(QLatin1String("function_id"));
    departmentIndex = model->fieldIndex(QLatin1String("department_id"));
    computerIndex = model->fieldIndex(QLatin1String("computer_id"));
    printerIndex = model->fieldIndex(QLatin1String("printer_id"));
    phoneIndex = model->fieldIndex(QLatin1String("phone_id"));
    mobileIndex = model->fieldIndex(QLatin1String("mobile_id"));
    faxIndex = model->fieldIndex(QLatin1String("fax_id"));

    model->select();

    // Set the mapper
    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    // Set the fields to the mapper
    mapper->addMapping(ui->doubleSpinBoxPersNR, model->fieldIndex(QLatin1String("employee_nr")));
    mapper->addMapping(ui->lineEditFirstname, model->fieldIndex(QLatin1String("firstname")) );
    mapper->addMapping(ui->lineEditLastname, model->fieldIndex(QLatin1String("lastname")));
    mapper->addMapping(ui->checkBoxActive, model->fieldIndex(QLatin1String("active")));
    mapper->addMapping(ui->checkBoxDatacare, model->fieldIndex(QLatin1String("datacare")));
    mapper->addMapping(ui->comboBoxGender, model->fieldIndex(QLatin1String("gender")));
    mapper->setCurrentIndex(index);

    mapper->setCurrentIndex(index);
    ui->lineEditFirstname->setFocus();
}

EmployeeInputDialog::~EmployeeInputDialog()
{
    delete ui;
}

void EmployeeInputDialog::on_buttonBox_accepted()
{
    qDebug() << "Name : " << ui->lineEditLastname->text();
    mapper->submit();
    model->database().transaction();
    if (model->submitAll()) {
         model->database().commit();
    } else {
         model->database().rollback();
         QMessageBox::warning(this, tr("Cached Table"),
                              tr("The database reported an error: %1")
                              .arg(model->lastError().text()));
     }
}

void EmployeeInputDialog::on_buttonBox_rejected()
{
    model->database().rollback();
    qDebug() << "Cancel Clicked!, DB-rollback.!";
}

void EmployeeInputDialog::preSetFields()
{
    QStringList qslGender;
    qslGender.append("Not Set");
    qslGender.append("m");
    qslGender.append("w");

    ui->comboBoxGender->addItems(qslGender);
}
