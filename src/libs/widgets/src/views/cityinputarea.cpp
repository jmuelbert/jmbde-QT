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

#include "views/cityinputarea.h"
#include "ui_cityinputarea.h"

CityInputArea::CityInputArea(QWidget *parent, const QModelIndex index)
    : QGroupBox(parent), ui(new Ui::CityInputArea) {
  ui->setupUi(this);

  qCDebug(jmbdewidgetsLog) << "Init CityInputArea for Index : " << index;

  m_actualMode = Mode::Edit;
  setViewOnlyMode(true);

  // Set the Model
  m_model = new QSqlRelationalTableModel(this);
  m_model->setTable(QLatin1String("city_name"));
  m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

  m_model->select();

  // Set the mapper
  m_mapper = new QDataWidgetMapper(this);
  m_mapper->setModel(m_model);
  m_mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

  setMappings();

  m_mapper->setCurrentIndex(index.row());
}

CityInputArea::~CityInputArea() { delete ui; }

void CityInputArea::setMappings() {
  m_mapper->addMapping(ui->lineEdit_CityName,
                       m_model->fieldIndex(QLatin1String("name")));
}

void CityInputArea::setViewOnlyMode(bool mode) {
  ui->comboBox_ZipCode->setDisabled(mode);
  ui->lineEdit_CityName->setDisabled(mode);
}

void CityInputArea::createDataset() {
  qCDebug(jmbdewidgetsLog) << "Create a new Dataset for City...";

  m_mapper->toLast();

  int row = m_mapper->currentIndex();
  if (row < 0)
    row = 0;

  m_mapper->submit();
  m_model->insertRow(row);
  m_mapper->setCurrentIndex(row);
}

void CityInputArea::retrieveDataset(const QModelIndex index) {}

void CityInputArea::updateDataset(const QModelIndex index) {}

void CityInputArea::deleteDataset(const QModelIndex index) {}

void CityInputArea::on_pushButton_Add_clicked() {
  createDataset();
  on_pushButton_EditFinish_clicked();
}

void CityInputArea::on_pushButton_EditFinish_clicked() {
  switch (m_actualMode) {
  case Mode::Edit: {
    m_actualMode = Mode::Finish;
    ui->pushButton_EditFinish->setText(tr("Finish"));
    setViewOnlyMode(false);

  } break;

  case Mode::Finish: {
    qCDebug(jmbdewidgetsLog) << "Save Data...";

    m_actualMode = Mode::Edit;
    ui->pushButton_EditFinish->setText(tr("Edit"));
    setViewOnlyMode(false);

    QString name = ui->lineEdit_CityName->text();

    if (name.isEmpty()) {
      QString message(tr("Please provide the name of the city."));

      QMessageBox::information(this, tr("Add City"), message);
    } else {
      m_mapper->submit();
      m_model->database().transaction();
      if (m_model->submitAll()) {
        m_model->database().commit();
        qCDebug(jmbdewidgetsLog) << "Commit changes for Computer Databse Table";
      } else {
        m_model->database().rollback();
        QMessageBox::warning(this, tr("jmbde"),
                             tr("The database reported an error: %1")
                                 .arg(m_model->lastError().text()));
      }
    }
  } break;

  default: {
    qCCritical(jmbdewidgetsLog) << "Error";
  }
  }
}
