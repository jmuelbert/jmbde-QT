/*
 *  SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "jmbdewidgets/faxinputarea.h"

#include "ui_faxinputarea.h"

FaxInputArea::FaxInputArea(QWidget *parent, const QModelIndex &index) : QGroupBox(parent), ui(new Ui::FaxInputArea)
{
  ui->setupUi(this);

  // Init UI
  qDebug() << tr("Initialisiere FaxInputarea mit Index : ") << index.row();

  this->m_faxModel = new Model::Fax();
  this->m_db = this->m_faxModel->getDB();

  m_actualMode = Mode::Edit;
  setViewOnlyMode(true);

  // Set the Model
  m_model = this->m_faxModel->initializeRelationalModel();

  // Set the mapper
  m_mapper = new QDataWidgetMapper(this);
  m_mapper->setModel(m_model);
  m_mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

  setMappings();

  qDebug() << tr("Aktueller Index: ") << m_mapper->currentIndex();

  if (index.row() < 0) {
    m_mapper->toFirst();
  } else {
    m_mapper->setCurrentIndex(index.row());
  }

  QObject::connect(this->ui->addPushButton, &QPushButton::released, this, &FaxInputArea::addEdit);
  QObject::connect(this->ui->editFinishPushButton, &QPushButton::released, this, &FaxInputArea::editFinish);
}

FaxInputArea::~FaxInputArea() { delete ui; }

void FaxInputArea::setMappings()
{
  m_mapper->addMapping(ui->deviceNameComboBox, this->m_faxModel->getDeviceNameIdIndex());
  m_mapper->addMapping(ui->serialNumberLineEdit, this->m_faxModel->getSerialNumberIndex());
  m_mapper->addMapping(ui->numberLineEdit, this->m_faxModel->getNumberIndex());
  m_mapper->addMapping(ui->pinLineEdit, this->m_faxModel->getPinIndex());
  m_mapper->addMapping(ui->activeCheckBox, this->m_faxModel->getActiveIndex());
  m_mapper->addMapping(ui->replaceCheckBox, this->m_faxModel->getReplaceIndex());
  m_mapper->addMapping(ui->deviceTypeComboBox, this->m_faxModel->getDeviceTypeIdIndex());
  m_mapper->addMapping(ui->employeeComboBox, this->m_faxModel->getEmployeeIdIndex());
  m_mapper->addMapping(ui->placeComboBox, this->m_faxModel->getPlaceIdIndex());
  m_mapper->addMapping(ui->departmentComboBox, this->m_faxModel->getDepartmentIdIndex());
  m_mapper->addMapping(ui->manufacturerComboBox, this->m_faxModel->getManufacturerIdIndex());
  m_mapper->addMapping(ui->inventoryComboBox, this->m_faxModel->getInventoryIdIndex());
  m_mapper->addMapping(ui->lastUpdateLineEdit, this->m_faxModel->getLastUpdateIndex());
}

void FaxInputArea::setViewOnlyMode(bool mode)
{
  // ui->deviceNameComboBox->setDisabled(mode);
  ui->serialNumberLineEdit->setDisabled(mode);
  ui->numberLineEdit->setDisabled(mode);
  ui->pinLineEdit->setDisabled(mode);
  ui->activeCheckBox->setDisabled(mode);
  ui->replaceCheckBox->setDisabled(mode);
  // ui->deviceTypeComboBox->setDisabled(mode);
  // ui->employeeComboBox->setDisabled(mode);
  // ui->placeComboBox->setDisabled(mode);
  // ui->departmentComboBox->setDisabled(mode);
  // ui->manufacturerComboBox->setDisabled(mode);
  // ui->inventoryComboBox->setDisabled(mode);
}

void FaxInputArea::createDataset()
{
  qDebug() << tr("Erzeuge einen neuen, leeren Datensatz für Fax...");

  // Set all inputfields to blank
  m_mapper->toLast();

  int row = m_mapper->currentIndex();
  if (row < 0) { row = 0; }
  m_mapper->submit();
  m_model->insertRow(row);
  m_mapper->setCurrentIndex(row);
}

void FaxInputArea::deleteDataset(const QModelIndex &index)
{
  qDebug() << tr("Lösche Daten von Fax");
  m_mapper->setCurrentIndex(index.row());
}
void FaxInputArea::addEdit()
{
  qDebug() << tr("Füge neue Daten zu Fax");
  createDataset();
  editFinish();
}

void FaxInputArea::editFinish()
{
  qDebug() << tr("Bearbeite oder schließe Fax Daten");

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

    QString number = ui->numberLineEdit->text();

    if (number.isEmpty()) {
      QString message(tr("Bitte eine Fax-Nummer angeben."));

      QMessageBox::information(this, tr("Fax hinzufügen"), message);
    } else {
      m_mapper->submit();
      m_model->database().transaction();
      if (m_model->submitAll()) {
        m_model->database().commit();
        qDebug() << tr("Schreiben der Änderungen für Fax in die Datenbank");
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
