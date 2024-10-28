/*
 *  SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "jmbdewidgets/devicenameinputarea.h"
#include <ui_devicenameinputarea.h>

DeviceNameInputArea::DeviceNameInputArea(QWidget *parent, const QModelIndex &index)
  : QGroupBox(parent), ui(new Ui::DeviceNameInputArea)
{
  ui->setupUi(this);

  qDebug() << "Initialisiere DeviceNameInputArea mit Index :" << index.row();

  this->m_deviceNameModel = new Model::DeviceName();
  this->m_db = this->m_deviceNameModel->getDB();

  m_actualMode = Mode::Edit;
  setViewOnlyMode(true);

  // Set the Model
  m_model = this->m_deviceNameModel->initializeRelationalModel();

  // Set the mapper
  m_mapper = new QDataWidgetMapper();
  m_mapper->setModel(m_model);
  m_mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

  setMappings();

  qDebug() << tr("Aktueller Index: ") << m_mapper->currentIndex();

  if (index.row() < 0) {
    m_mapper->toFirst();
  } else {
    m_mapper->setCurrentIndex(index.row());
  }

  QObject::connect(this->ui->addPushButton, &QPushButton::released, this, &DeviceNameInputArea::addEdit);
  QObject::connect(this->ui->editFinishPushButton, &QPushButton::released, this, &DeviceNameInputArea::editFinish);
}

DeviceNameInputArea::~DeviceNameInputArea() { delete ui; }

void DeviceNameInputArea::setMappings()
{
  m_mapper->addMapping(ui->nameLineEdit, this->m_deviceNameModel->getNameIndex());
  m_mapper->addMapping(ui->lastUpdatelineEdit, this->m_deviceNameModel->getLastUpdateIndex());
}

void DeviceNameInputArea::setViewOnlyMode(bool mode) { ui->nameLineEdit->setDisabled(mode); }

void DeviceNameInputArea ::createDataset()
{
  qDebug() << tr("Erzeuge einen neuen, leeren Datensatz für DeviceName...");

  // Set all inputfields to blank
  m_mapper->toLast();

  int row = m_mapper->currentIndex();
  if (row < 0) { row = 0; }
  m_mapper->submit();
  m_model->insertRow(row);
  m_mapper->setCurrentIndex(row);
}

void DeviceNameInputArea::deleteDataset(const QModelIndex &index)
{
  qDebug() << tr("Lösche Daten von DeviceName");
  m_mapper->setCurrentIndex(index.row());
}

void DeviceNameInputArea::addEdit()
{
  qDebug() << tr("Füge neue Daten zu DeviceName");
  createDataset();
  editFinish();
}

void DeviceNameInputArea::editFinish()
{
  qDebug() << tr("Bearbeite oder schließe DeviceName Daten");

  switch (m_actualMode) {
  case Mode::Edit: {
    m_actualMode = Mode::Finish;
    ui->editFinishPushButton->setText(tr("Fertig"));
    setViewOnlyMode(false);

  } break;

  case Mode::Finish: {
    qDebug() << tr("Die Daten werden gesichert.");

    m_actualMode = Mode::Edit;
    ui->editFinishPushButton->setText(tr("Bearbeiten"));
    setViewOnlyMode(false);

    QString name = ui->nameLineEdit->text();

    if (name.isEmpty()) {
      QString message(tr("Bitte den Gerätenamen eingeben."));

      QMessageBox::information(this, tr("Gerätenamen hinzufügen."), message);
    } else {
      m_mapper->submit();
      m_model->database().transaction();
      if (m_model->submitAll()) {
        m_model->database().commit();
        qDebug() << tr("Schreiben der Änderungen für DeviceName in die Datenbank");
        dataChanged();
      } else {
        m_model->database().rollback();
        QMessageBox::warning(
          this, tr("jmbde"), tr("Die Datenbank meldet den Fehler: %1").arg(m_model->lastError().text()));
      }
    }
  } break;

  default: {
    qCritical() << tr("Fehler: Unbekannter Modus");
  }
  }
}
