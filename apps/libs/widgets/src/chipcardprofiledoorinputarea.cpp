/*
 *  SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "jmbdewidgets/chipcardprofiledoorinputarea.h"
#include <ui_chipcardprofiledoorinputarea.h>

ChipCardProfileDoorInputArea::ChipCardProfileDoorInputArea(QWidget *parent, const QModelIndex &index)
  : QGroupBox(parent), ui(new Ui::ChipCardProfileDoorInputArea)
{
  ui->setupUi(this);

  qDebug() << "Initialisiere ChipCardProfileDoor mit Index :" << index.row();

  this->m_chipCardProfileDoorModel = new Model::ChipCardProfileDoor();
  this->m_db = this->m_chipCardProfileDoorModel->getDB();

  m_actualMode = Mode::Edit;
  setViewOnlyMode(true);

  // Set the Model
  m_model = this->m_chipCardProfileDoorModel->initializeRelationalModel();

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

  QObject::connect(this->ui->addPushButton, &QPushButton::released, this, &ChipCardProfileDoorInputArea::addEdit);
  QObject::connect(
    this->ui->editFinishPushButton, &QPushButton::released, this, &ChipCardProfileDoorInputArea::editFinish);
}

ChipCardProfileDoorInputArea::~ChipCardProfileDoorInputArea() { delete ui; }

void ChipCardProfileDoorInputArea::setMappings()
{
  m_mapper->addMapping(ui->doorComboBox, this->m_chipCardProfileDoorModel->getChipCardDoorsIdIndex());
  m_mapper->addMapping(ui->profileComboBox, this->m_chipCardProfileDoorModel->getChipCardProfileIdIndex());
  m_mapper->addMapping(ui->lastUpdateLineEdit, this->m_chipCardProfileDoorModel->getLastUpdateIndex());
}

void ChipCardProfileDoorInputArea::setViewOnlyMode(bool mode)
{
  ui->doorComboBox->setDisabled(mode);
  ui->profileComboBox->setDisabled(mode);
}

void ChipCardProfileDoorInputArea::createDataset()
{
  qDebug() << tr("Erzeuge einen neuen, leeren Datensatz für ChipCardProfileDoor...");

  // Set all inputfields to blank
  m_mapper->toLast();

  int row = m_mapper->currentIndex();
  if (row < 0) { row = 0; }
  m_mapper->submit();
  m_model->insertRow(row);
  m_mapper->setCurrentIndex(row);
}

void ChipCardProfileDoorInputArea::deleteDataset(const QModelIndex &index)
{
  qDebug() << tr("Lösche Daten von ChipCardProfileDoor");
  m_mapper->setCurrentIndex(index.row());
}

void ChipCardProfileDoorInputArea::addEdit()
{
  qDebug() << tr("Füge neue Daten zu ChipCardProfileDoor");
  createDataset();
  editFinish();
}

void ChipCardProfileDoorInputArea::editFinish()
{
  qDebug() << tr("Bearbeite oder schließe ChipCardProfileDoor Daten");

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

    m_mapper->submit();
    m_model->database().transaction();
    if (m_model->submitAll()) {
      m_model->database().commit();
      qDebug() << tr("Schreiben der Änderungen für ChipCardProfileDoor in die Datenbank");
      dataChanged();
    } else {
      m_model->database().rollback();
      QMessageBox::warning(
        this, tr("jmbde"), tr("Die Datenbank meldet den Fehler: %1").arg(m_model->lastError().text()));
    }
  } break;

  default: {
    qCritical() << tr("Fehler: Unbekannter Modus");
  }
  }
}
