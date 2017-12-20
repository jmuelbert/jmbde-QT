/*
   // ManufacturerInputArea manufacturerinputarea.cpp
   // part of <Project>
   //
   // Copyright (c) 2013-2017 Jürgen Mülbert. All rights reserved.
   //
   // Licensed under the EUPL, Version 1.2 or – as soon they
   // will be approved by the European Commission - subsequent
   // versions of the EUPL (the "Licence");
   // You may not use this work except in compliance with the
   // Licence.
   // You may obtain a copy of the Licence at:
   //
   // https://joinup.ec.europa.eu/page/eupl-text-11-12
   //
   // Unless required by applicable law or agreed to in
   // writing, software distributed under the Licence is
   // distributed on an "AS IS" basis,
   // WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
   // express or implied.
   // See the Licence for the specific language governing
   // permissions and limitations under the Licence.
   //
   // Lizenziert unter der EUPL, Version 1.2 oder - sobald
   // diese von der Europäischen Kommission genehmigt wurden -
   // Folgeversionen der EUPL ("Lizenz");
   // Sie dürfen dieses Werk ausschließlich gemäß
   // dieser Lizenz nutzen.
   // Eine Kopie der Lizenz finden Sie hier:
   //
   // https://joinup.ec.europa.eu/page/eupl-text-11-12
   //
   // Sofern nicht durch anwendbare Rechtsvorschriften
   // gefordert oder in schriftlicher Form vereinbart, wird
   // die unter der Lizenz verbreitete Software "so wie sie
   // ist", OHNE JEGLICHE GEWÄHRLEISTUNG ODER BEDINGUNGEN -
   // ausdrücklich oder stillschweigend - verbreitet.
   // Die sprachspezifischen Genehmigungen und Beschränkungen
   // unter der Lizenz sind dem Lizenztext zu entnehmen.
   //
   // Created: 5.11.2017
 */
#include "manufacturerinputarea.h"
#include "ui_manufacturerinputarea.h"

ManufacturerInputArea::ManufacturerInputArea(QWidget* parent, const QModelIndex index) :
  QScrollArea(parent),
  ui(new Ui::ManufacturerInputArea)
{
  ui->setupUi(this);

  // Init UI
  qDebug() << "Init ManufacturerInputarea for Index : " << index.row();

  m_actualMode = Mode::Edit;
  setViewOnlyMode(true);

  // Set the Model
  m_model = new QSqlRelationalTableModel(this);
  m_model->setTable(QLatin1String("manufacturer"));
  m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

  m_model->select();

  // Set the mapper
  m_mapper = new QDataWidgetMapper(this);
  m_mapper->setModel(m_model);
  m_mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

  setMappings();

  m_mapper->setCurrentIndex(index.row());
}

ManufacturerInputArea::~ManufacturerInputArea()
{
  delete ui;
}

void ManufacturerInputArea::setMappings() {
  m_mapper->addMapping(ui->comboBox_ZipCode,
                       m_model->fieldIndex(QLatin1String("zip_city_id")));
  m_mapper->addMapping(ui->lineEdit_Address,
                       m_model->fieldIndex(QLatin1String("address")));
  m_mapper->addMapping(ui->lineEdit_Address2,
                       m_model->fieldIndex(QLatin1String("address2")));
  m_mapper->addMapping(ui->lineEdit_Fax,
                       m_model->fieldIndex(QLatin1String("fax_number")));
  m_mapper->addMapping(ui->lineEdit_Hotline,
                       m_model->fieldIndex(QLatin1String("hotline_numbert")));
  m_mapper->addMapping(ui->lineEdit_MailAddress,
                       m_model->fieldIndex(QLatin1String("mail_address")));
  m_mapper->addMapping(ui->lineEdit_Name,
                       m_model->fieldIndex(QLatin1String("name")));
  m_mapper->addMapping(ui->lineEdit_Name2,
                       m_model->fieldIndex(QLatin1String("name2")));
  m_mapper->addMapping(ui->lineEdit_Phone,
                       m_model->fieldIndex(QLatin1String("phone_number")));
  m_mapper->addMapping(ui->lineEdit_Supporter,
                       m_model->fieldIndex(QLatin1String("supporter")));
}

void ManufacturerInputArea::setViewOnlyMode(bool mode) {
  ui->comboBox_ZipCode->setDisabled(mode);
  ui->lineEdit_Address->setDisabled(mode);
  ui->lineEdit_Address2->setDisabled(mode);
  ui->lineEdit_Fax->setDisabled(mode);
  ui->lineEdit_Hotline->setDisabled(mode);
  ui->lineEdit_MailAddress->setDisabled(mode);
  ui->lineEdit_Name->setDisabled(mode);
  ui->lineEdit_Name2->setDisabled(mode);
  ui->lineEdit_Phone->setDisabled(mode);
  ui->lineEdit_Supporter->setDisabled(mode);
}

void ManufacturerInputArea::createDataset() {
  qDebug() << "Create a new Dataset for Manufacturer...";

  // Set all inputfields to blank
  m_mapper->toLast();
  int row = m_mapper->currentIndex();

  m_mapper->submit();
  m_model->insertRow(row);
  m_mapper->setCurrentIndex(row);
}

void ManufacturerInputArea::retrieveDataset(const QModelIndex index) {}

void ManufacturerInputArea::updateDataset(const QModelIndex index) {}

void ManufacturerInputArea::deleteDataset(const QModelIndex index) {}

void ManufacturerInputArea::on_pushButton_Add_clicked()
{
  createDataset();
}

void ManufacturerInputArea::on_pushButton_EditFinish_clicked()
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
        QString message(tr("Please provide the name of the manufacturer."));

        QMessageBox::information(this, tr("Add Manufacturer"), message);
      }
      else {
        m_mapper->submit();
        m_model->database().transaction();
        if (m_model->submitAll()) {
          m_model->database().commit();
          qDebug() << "Commit changes for Computer Databse Table";
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
