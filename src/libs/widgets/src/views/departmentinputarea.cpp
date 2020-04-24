/*
    jmbde a BDE Tool for companies
    Copyright (C) 2013-2019  Jürgen Mülbert

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

#include "views/departmentinputarea.h"
#include "ui_departmentinputarea.h"

DepartmentInputArea::DepartmentInputArea(QWidget *parent,
                                         const QModelIndex index)
    : QGroupBox(parent), ui(new Ui::DepartmentInputArea) {
  ui->setupUi(this);

  // Init UI
  qDebug() << "Init DepartmentInputArea for Index : " << index.row();

  m_actualMode = Mode::Edit;
  setViewOnlyMode(true);

  // Set the Model
  m_model = new QSqlRelationalTableModel(this);
  m_model->setTable(QLatin1String("department"));
  m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

  m_model->select();

  // Set the mapper
  m_mapper = new QDataWidgetMapper(this);
  m_mapper->setModel(m_model);
  m_mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

  setMappings();

  m_mapper->setCurrentIndex(index.row());
}

DepartmentInputArea::~DepartmentInputArea() { delete ui; }

void DepartmentInputArea::setMappings() {
  m_mapper->addMapping(ui->comboBox_Fax,
                       m_model->fieldIndex(QLatin1String("fax_id")));
  m_mapper->addMapping(ui->comboBox_Printer,
                       m_model->fieldIndex(QLatin1String("printer_id")));
  m_mapper->addMapping(ui->spinBox_Priority,
                       m_model->fieldIndex(QLatin1String("priority")));
  m_mapper->addMapping(ui->lineEdit_Name,
                       m_model->fieldIndex(QLatin1String("name")));
}

void DepartmentInputArea::setViewOnlyMode(bool mode) {
  ui->comboBox_Fax->setDisabled(mode);
  ui->comboBox_Printer->setDisabled(mode);
  ui->dial_Priority->setDisabled(mode);
  ui->lcdNumber_Priority->setDisabled(mode);
  ui->lineEdit_Name->setDisabled(mode);
}

void DepartmentInputArea::createDataset() {
  qDebug() << "Create a new Dataset for Employee...";

  // Set all inputfields to blank
  m_mapper->toLast();

  int row = m_mapper->currentIndex();
  if (row < 0)
    row = 0;

  m_mapper->submit();
  m_model->insertRow(row);
  m_mapper->setCurrentIndex(row);
}

void DepartmentInputArea::retrieveDataset(const QModelIndex index) {}

void DepartmentInputArea::updateDataset(const QModelIndex index) {}

void DepartmentInputArea::deleteDataset(const QModelIndex index) {}

void DepartmentInputArea::on_pushButton_Add_clicked() {
  createDataset();
  on_pushButton_EditFinish_clicked();
}

void DepartmentInputArea::on_pushButton_EditFinish_clicked() {
  switch (m_actualMode) {
  case Mode::Edit: {
    m_actualMode = Mode::Finish;
    ui->pushButton_EditFinish->setText(tr("Finish"));
    setViewOnlyMode(false);

  } break;

  case Mode::Finish: {
    qDebug() << "Save Data...";

    m_actualMode = Mode::Edit;
    ui->pushButton_EditFinish->setText(tr("Edit"));
    setViewOnlyMode(false);

    QString lastName = ui->lineEdit_Name->text();

    if (lastName.isEmpty()) {
      QString message(tr("Please provide the name of the department."));

      QMessageBox::information(this, tr("Add Department"), message);
    } else {
      m_mapper->submit();
      m_model->database().transaction();
      if (m_model->submitAll()) {
        m_model->database().commit();
        qDebug() << "Commit changes for Computer Databse Table";
      } else {
        m_model->database().rollback();
        QMessageBox::warning(this, tr("jmbde"),
                             tr("The database reported an error: %1")
                                 .arg(m_model->lastError().text()));
      }
    }
  } break;

  default: {
    qDebug() << "Error";
  }
  }
}
