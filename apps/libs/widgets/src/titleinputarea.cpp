/*
 *  SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "jmbdewidgets/titleinputarea.h"

#include "ui_titleinputarea.h"

TitleInputArea::TitleInputArea(QWidget *parent, const QModelIndex &index)
  : QGroupBox(parent), ui(new Ui::TitleInputArea)
{
  ui->setupUi(this);

  // Init UI
  qDebug() << tr("Initialisiere TitleInputarea mit Index : ") << index.row();

  this->m_titleModel = new Model::Title();
  this->m_db = this->m_titleModel->getDB();

  m_actualMode = Mode::Edit;
  setViewOnlyMode(true);

  // Set the Model
  m_model = this->m_titleModel->initializeRelationalModel();

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

  QObject::connect(this->ui->addPushButton, &QPushButton::released, this, &TitleInputArea::addEdit);
  QObject::connect(this->ui->editFinishPushButton, &QPushButton::released, this, &TitleInputArea::editFinish);
}

TitleInputArea::~TitleInputArea() { delete ui; }

void TitleInputArea::setMappings()
{
  m_mapper->addMapping(ui->titleLineEdit, this->m_titleModel->getNameIndex());
  m_mapper->addMapping(ui->fromDateEdit, this->m_titleModel->getFromDateIndex());
  m_mapper->addMapping(ui->lastUpdateLineEdit, this->m_titleModel->getLastUpdateIndex());
}

void TitleInputArea::setViewOnlyMode(bool mode)
{
  ui->titleLineEdit->setDisabled(mode);
  ui->fromDateEdit->setDisabled(mode);
}

void TitleInputArea::createDataset()
{
  qDebug() << tr("Erzeuge einen neuen, leeren Datensatz für Title...");

  // Set all inputfields to blank
  m_mapper->toLast();

  int row = m_mapper->currentIndex();
  if (row < 0) { row = 0; }
  m_mapper->submit();
  m_model->insertRow(row);
  m_mapper->setCurrentIndex(row);
}

void TitleInputArea::deleteDataset(const QModelIndex &index)
{
  qDebug() << tr("Lösche Daten von Title");
  m_mapper->setCurrentIndex(index.row());
}

void TitleInputArea ::addEdit()
{
  qDebug() << tr("Füge neue Daten zu Title");
  createDataset();
  editFinish();
}

void TitleInputArea ::editFinish()
{
  qDebug() << tr("Bearbeite oder schließe Title Daten");

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

    QString name = ui->titleLineEdit->text();

    if (name.isEmpty()) {
      QString message(tr("Bitte geben Sie einen neuen Titel an."));

      QMessageBox::information(this, tr("Titel hinzufügen"), message);
    } else {
      m_mapper->submit();
      m_model->database().transaction();
      if (m_model->submitAll()) {
        m_model->database().commit();
        qDebug() << tr("Schreiben der Änderungen für Account in die Datenbank");
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
