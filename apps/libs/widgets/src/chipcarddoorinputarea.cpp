/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "jmbdewidgets//chipcarddoorinputarea.h"
#include <ui_chipcarddoorinputarea.h>

ChipCardDoorInputArea::ChipCardDoorInputArea(QWidget *parent, const QModelIndex &index)
  : QGroupBox(parent), ui(new Ui::ChipCardDoorInputArea)
{
  ui->setupUi(this);

  qDebug() << tr("Initialisiere ChipCardDoorInputArea mit Index :") << index.row();

  this->m_chipCardDoorModel = new Model::ChipCardDoor();
  this->m_db = this->m_chipCardDoorModel->getDB();

  m_actualMode = Mode::Edit;
  setViewOnlyMode(true);

  // Set the Model
  m_model = this->m_chipCardDoorModel->initializeRelationalModel();

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

  QObject::connect(this->ui->addPushButton, &QPushButton::released, this, &ChipCardDoorInputArea::addEdit);
  QObject::connect(this->ui->editFinishPushButton, &QPushButton::released, this, &ChipCardDoorInputArea::editFinish);
}

ChipCardDoorInputArea::~ChipCardDoorInputArea() { delete ui; }

void ChipCardDoorInputArea::setMappings()
{
  m_mapper->addMapping(ui->numberSpinBox, this->m_chipCardDoorModel->getNumberIndex());
  m_mapper->addMapping(ui->placeComboBox, this->m_chipCardDoorModel->getPlaceIdIndex());
  m_mapper->addMapping(ui->departmentComboBox, this->m_chipCardDoorModel->getDepartmentIdIndex());
  m_mapper->addMapping(ui->employeeComboBox, this->m_chipCardDoorModel->getEmployeeIdIndex());
  m_mapper->addMapping(ui->lastUpdateLineEdit, this->m_chipCardDoorModel->getLastUpdateIndex());
}

void ChipCardDoorInputArea::setViewOnlyMode(bool mode)
{
  ui->numberSpinBox->setDisabled(mode);
  // ui->placeComboBox->setDisabled(mode);
  // ui->deparmentComboBox->setDisabled(mode);
  // ui->employeeComboBox->setDisabled(mode);
}

void ChipCardDoorInputArea::createDataset()
{
  qDebug() << "Create a new Dataset for ChipCardDoor...";

  // Set all inputfields to blank
  m_mapper->toLast();

  int row = m_mapper->currentIndex();
  if (row < 0) { row = 0; }
  m_mapper->submit();
  m_model->insertRow(row);
  m_mapper->setCurrentIndex(row);
}

void ChipCardDoorInputArea::deleteDataset(const QModelIndex &index)
{
  qDebug() << tr("Lösche Daten von ChipCardDoor");
  m_mapper->setCurrentIndex(index.row());
}

void ChipCardDoorInputArea::addEdit()
{
  qDebug() << tr("Füge neue Daten zu ChipCardDoor");
  createDataset();
  editFinish();
}

void ChipCardDoorInputArea::editFinish()
{
  qDebug() << tr("Bearbeite oder schließe ChipCardDoor Daten");
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

    QString number = ui->numberSpinBox->text();

    if (number.isEmpty()) {
      QString message(tr("Bitte geben sie eine Schlüsselchip Nummer ein."));

      QMessageBox::information(this, tr("Hinzufügen Schlüsselchip Tür"), message);
    } else {
      m_mapper->submit();
      m_model->database().transaction();
      if (m_model->submitAll()) {
        m_model->database().commit();
        qDebug() << tr("Schreiben der Änderungen für ChipCardDoor in die Datenbank");
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
