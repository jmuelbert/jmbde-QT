/*
 *  SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <jmbdewidgets/companyinputarea.h>
#include <ui_companyinputarea.h>

CompanyInputArea::CompanyInputArea(QWidget *parent, const QModelIndex &index)
  : QGroupBox(parent), ui(new Ui::CompanyInputArea)

{
  ui->setupUi(this);

  qDebug() << "Initialisiere CompanyInputArea mit Index :" << index.row();

  this->m_companyModel = new Model::Company();
  this->m_db = this->m_companyModel->getDB();

  m_actualMode = Mode::Edit;
  setViewOnlyMode(true);

  // Set the Model
  m_model = this->m_companyModel->initializeRelationalModel();

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

  QObject::connect(this->ui->addPushButton, &QPushButton::released, this, &CompanyInputArea::addEdit);
  QObject::connect(this->ui->editFinishPushButton, &QPushButton::released, this, &CompanyInputArea::editFinish);
}

CompanyInputArea::~CompanyInputArea() { delete ui; }

void CompanyInputArea::setMappings()
{
  m_mapper->addMapping(ui->nameLineEdit, this->m_companyModel->getNameIndex());
  m_mapper->addMapping(ui->name2LineEdit, this->m_companyModel->getName2Index());
  m_mapper->addMapping(ui->streetLineEdit, this->m_companyModel->getStreetIndex());
  m_mapper->addMapping(ui->cityLineEdit, this->m_companyModel->getCityIndex());
  m_mapper->addMapping(ui->zipCodeLineEdit, this->m_companyModel->getCityIndex());
  m_mapper->addMapping(ui->phoneNumberLineEdit, this->m_companyModel->getPhoneNumberIndex());
  m_mapper->addMapping(ui->faxNumberLineEdit, this->m_companyModel->getFaxNumberIndex());
  m_mapper->addMapping(ui->mobileNumberLineEdit, this->m_companyModel->getMobileNumberIndex());
  m_mapper->addMapping(ui->mailAddressLineEdit, this->m_companyModel->getMailAddressIndex());
  m_mapper->addMapping(ui->activeCheckBox, this->m_companyModel->getActiveIndex());
  m_mapper->addMapping(ui->employeeIdComboBox, this->m_companyModel->getEmployeeIdIndex());
  m_mapper->addMapping(ui->lastUpdateLineEdit, this->m_companyModel->getLastUpdateIndex());
}

void CompanyInputArea::setViewOnlyMode(bool mode)
{
  ui->nameLineEdit->setDisabled(mode);
  ui->name2LineEdit->setDisabled(mode);
  ui->streetLineEdit->setDisabled(mode);
  ui->cityLineEdit->setDisabled(mode);
  ui->zipCodeLineEdit->setDisabled(mode);
  ui->phoneNumberLineEdit->setDisabled(mode);
  ui->faxNumberLineEdit->setDisabled(mode);
  ui->mobileNumberLineEdit->setDisabled(mode);
  ui->mailAddressLineEdit->setDisabled(mode);
  ui->activeCheckBox->setDisabled(mode);
  // ui->employeeIdComboBox->setDisabled(mode);
}

void CompanyInputArea::createDataset()
{
  qDebug() << tr("Erzeuge einen neuen, leeren Datensatz für Company...");

  // Set all inputfields to blank
  m_mapper->toLast();

  int row = m_mapper->currentIndex();
  if (row < 0) { row = 0; }
  m_mapper->submit();
  m_model->insertRow(row);
  m_mapper->setCurrentIndex(row);
}

void CompanyInputArea::deleteDataset(const QModelIndex &index)
{
  qDebug() << tr("Lösche Daten von Company");
  m_mapper->setCurrentIndex(index.row());
}

void CompanyInputArea::addEdit()
{
  qDebug() << tr("Füge neue Daten zu Company");
  createDataset();
  editFinish();
}

void CompanyInputArea::editFinish()
{
  qDebug() << tr("Bearbeite oder schließe Company Daten");

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
      QString message(tr("Bitte geben sie eine den Namen der Firma an."));

      QMessageBox::information(this, tr("Hinzufügen Firma"), message);
    } else {
      m_mapper->submit();
      m_model->database().transaction();
      if (m_model->submitAll()) {
        m_model->database().commit();
        qDebug() << tr("Schreiben der Änderungen für Company in die Datenbank");
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
