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

#include "processorinputarea.h"
#include "ui_processorinputarea.h"

ProcessorInputArea::ProcessorInputArea(QWidget* parent, const QModelIndex index) :
  QGroupBox(parent),
  ui(new Ui::ProcessorInputArea)
{
  ui->setupUi(this);

  // Init UI
  qDebug() << "Init ProcessorInputarea for Index : " << index.row();

  m_actualMode = Mode::Edit;
  setViewOnlyMode(true);

  // Set the Model
  m_model = new QSqlRelationalTableModel(this);
  m_model->setTable(QLatin1String("processor"));
  m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

  m_model->select();

  // Set the mapper
  m_mapper = new QDataWidgetMapper(this);
  m_mapper->setModel(m_model);
  m_mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

  setMappings();

  m_mapper->setCurrentIndex(index.row());
}

ProcessorInputArea::~ProcessorInputArea()
{
  delete ui;
}

void ProcessorInputArea::setMappings() {
  m_mapper->addMapping(ui->doubleSpinBox_ClockRate,
                       m_model->fieldIndex(QLatin1String("clock_rate")));
  m_mapper->addMapping(ui->lineEdit_Name,
                       m_model->fieldIndex(QLatin1String("name")));
  m_mapper->addMapping(ui->spinBox_Cores,
                       m_model->fieldIndex(QLatin1String("cores")));
}

void ProcessorInputArea::setViewOnlyMode(bool mode) {
  ui->doubleSpinBox_ClockRate->setDisabled(mode);
  ui->lineEdit_Name->setDisabled(mode);
  ui->spinBox_Cores->setDisabled(mode);
}

void ProcessorInputArea::createDataset() {
  qDebug() << "Create a new Dataset for Processor...";

  // Set all inputfields to blank
  m_mapper->toLast();

  int row = m_mapper->currentIndex();
  if (row < 0) row = 0;

  m_mapper->submit();
  m_model->insertRow(row);
  m_mapper->setCurrentIndex(row);
}

void ProcessorInputArea::retrieveDataset(const QModelIndex index) {}

void ProcessorInputArea::updateDataset(const QModelIndex index) {}

void ProcessorInputArea::deleteDataset(const QModelIndex index) {}

void ProcessorInputArea::on_pushButton_Add_clicked()
{
  createDataset();
}

void ProcessorInputArea::on_pushButton_EditFinish_clicked()
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

      QString name = ui->lineEdit_Name->text();

      if (name.isEmpty()) {
        QString message(tr("Please provide the name of the processor."));

        QMessageBox::information(this, tr("Add Processor"), message);
      }
      else {
        m_mapper->submit();
        m_model->database().transaction();
        if (m_model->submitAll()) {
          m_model->database().commit();
          qDebug() << "Commit changes for Processor Databse Table";
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
