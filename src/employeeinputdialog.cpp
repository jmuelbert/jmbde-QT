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


    workfunctionIndex = model->fieldIndex(QLatin1String("WorkfunctionId"));
    departmentIndex = model->fieldIndex(QLatin1String("DepartmentId"));
    placeIndex = model->fieldIndex(QLatin1String("PlaceId"));
    companyIndex = model->fieldIndex(QLatin1String("CompanyId"));

    model->select();


    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    ui->setupUi(this);

    mapper->addMapping(ui->doubleSpinBoxPersNR, model->fieldIndex(QLatin1String("EmployeeNO")));
    mapper->addMapping(ui->lineEditFirstname, model->fieldIndex(QLatin1String("Firstname")) );
    mapper->addMapping(ui->lineEditLastname, model->fieldIndex(QLatin1String("Name")));
    mapper->addMapping(ui->checkBoxActive, model->fieldIndex(QLatin1String("Active")));
    mapper->addMapping(ui->checkBoxDatacare, model->fieldIndex(QLatin1String("DataCare")));

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
