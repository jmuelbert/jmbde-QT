/*
 * ComputerInputDialog.h
 * jmbde
 *
 * Copyright (c) 2013,2014 Jürgen Mülbert. All rights reserved.
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


#include "computerinputdialog.h"
#include "ui_computerinputdialog.h"

ComputerInputDialog::ComputerInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComputerInputDialog)
{

    ui->setupUi(this);

    model = new QSqlRelationalTableModel(this);
    model->setTable(QLatin1String("computer"));
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    mapper->addMapping(ui->lineEditComputerName, model->fieldIndex(QLatin1String("network_name")));
    mapper->toLast();
    int row = mapper->currentIndex();
    mapper->submit();
    model->insertRow(row);
    mapper->setCurrentIndex(row);

    ui->lineEditComputerName->clear();
    ui->lineEditComputerName->setFocus();
 }

ComputerInputDialog::ComputerInputDialog(QWidget *parent, int index) :
    QDialog(parent),
    ui(new Ui::ComputerInputDialog)
{
    ui->setupUi(this);

    model = new QSqlRelationalTableModel(this);
    model->setTable(QLatin1String("computer"));
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    model->select();

    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    mapper->addMapping(ui->lineEditComputerName, model->fieldIndex(QLatin1String("network_name")));
    mapper->setCurrentIndex(index);
    ui->lineEditComputerName->setFocus();

}

ComputerInputDialog::~ComputerInputDialog()
{
    delete ui;
}


void ComputerInputDialog::on_buttonBox_accepted()
{
    qDebug() << "Name : " << ui->lineEditComputerName->text();
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

void ComputerInputDialog::on_buttonBox_rejected()
{
    model->database().rollback();
    qDebug() << "Cancel Clicked!, DB-rollback.!";
}


