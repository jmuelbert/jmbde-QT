/**************************************************************************
**
** Copyright (c) 2013-2018 Jürgen Mülbert. All rights reserved.
**
** This file is part of jmbde
**
** Licensed under the EUPL, Version 1.2 or – as soon they
** will be approved by the European Commission - subsequent
** versions of the EUPL (the "Licence");
** You may not use this work except in compliance with the
** Licence.
** You may obtain a copy of the Licence at:
**
** https://joinup.ec.europa.eu/page/eupl-text-11-12
**
** Unless required by applicable law or agreed to in
** writing, software distributed under the Licence is
** distributed on an "AS IS" basis,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
** express or implied.
** See the Licence for the specific language governing
** permissions and limitations under the Licence.
**
** Lizenziert unter der EUPL, Version 1.2 oder - sobald
**  diese von der Europäischen Kommission genehmigt wurden -
** Folgeversionen der EUPL ("Lizenz");
** Sie dürfen dieses Werk ausschließlich gemäß
** dieser Lizenz nutzen.
** Eine Kopie der Lizenz finden Sie hier:
**
** https://joinup.ec.europa.eu/page/eupl-text-11-12
**
** Sofern nicht durch anwendbare Rechtsvorschriften
** gefordert oder in schriftlicher Form vereinbart, wird
** die unter der Lizenz verbreitete Software "so wie sie
** ist", OHNE JEGLICHE GEWÄHRLEISTUNG ODER BEDINGUNGEN -
** ausdrücklich oder stillschweigend - verbreitet.
** Die sprachspezifischen Genehmigungen und Beschränkungen
** unter der Lizenz sind dem Lizenztext zu entnehmen.
**
**************************************************************************/

#include "chipcardinputarea.h"
#include "ui_chipcardinputarea.h"

ChipCardInputArea::ChipCardInputArea(QWidget *parent, const QModelIndex& index)
    :  QGroupBox (parent), ui(new Ui::ChipCardInputArea) {
    ui->setupUi(this);

    qDebug() << "Init ChipCardInputArea for Index : " << index;

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = new QSqlRelationalTableModel(this);
    m_model->setTable(QLatin1String("chip_card"));
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    m_model->select();

    m_mapper = new QDataWidgetMapper(this);
    m_mapper->setModel(m_model);
    setMappings();

    m_mapper->setCurrentIndex(index.row());
  }

ChipCardInputArea::~ChipCardInputArea()
{
    delete ui;
}

// TODO change lineEdit to lineEdit_Number
void ChipCardInputArea::setMappings() {
    m_mapper->addMapping(ui->lineEdit,
                         m_model->fieldIndex(QLatin1String("number")));
    m_mapper->addMapping(ui->comboBox_Door,
                         m_model->fieldIndex((QLatin1String( "chip_card_door_id"))));
    m_mapper->addMapping(ui->comboBox_Profile,
                         m_model->fieldIndex(QLatin1String("chip_card_profile_id")));
    m_mapper->addMapping(ui->comboBox_Employee,
                         m_model->fieldIndex((QLatin1String("employee_id"))));
}

void ChipCardInputArea::setViewOnlyMode(bool mode) {
    ui->lineEdit->setDisabled(mode);
    ui->comboBox_Door->setDisabled(mode);
    ui->comboBox_Profile->setDisabled(mode);
    ui->comboBox_Employee->setDisabled(mode);
}

void ChipCardInputArea::createDataset() {
  qDebug() << "Create a new Dataset for ChipCard...";

  // Set all inputfields to blank
  m_mapper->toLast();

  int row = m_mapper->currentIndex();
  if (row < 0) row = 0;

  m_mapper->submit();
  m_model->insertRow(row);
  m_mapper->setCurrentIndex(row);
}

void ChipCardInputArea::retrieveDataset(const QModelIndex index) {}

void ChipCardInputArea::updateDataset(const QModelIndex index) {}

void ChipCardInputArea::deleteDataset(const QModelIndex index) {}

void ChipCardInputArea::on_pushButton_Add_clicked()
{
  createDataset();
  on_pushButton_EditFinish_clicked();
}

void ChipCardInputArea::on_pushButton_EditFinish_clicked()
{
  switch(m_actualMode) {
    case Mode::Edit:
    {
      m_actualMode = Mode::Finish;
      ui->pushButton_EditFinish->setText(tr("Finish"));
      setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
      qDebug() << "Save Data...";

      m_actualMode = Mode::Edit;
      ui->pushButton_EditFinish->setText(tr("Edit"));
      setViewOnlyMode(false);

      QString name = ui->lineEdit->text();

      if (name.isEmpty()) {
        QString message(tr("Please provide the chipcard number."));

        QMessageBox::information(this, tr("Add City"), message);
      }
      else {

        m_mapper->submit();
        m_model->database().transaction();
        if (m_model->submitAll()) {
          m_model->database().commit();
          qDebug() << "Commit changes for Chipcard Databse Table";
          m_model->database().rollback();
        }
        else {
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


