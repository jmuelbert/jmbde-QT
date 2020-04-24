/**************************************************************************
**
** Copyright (c) 2013-2019 Jürgen Mülbert. All rights reserved.
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

#include "views/employeeinputarea.h"
#include "ui_employeeinputarea.h"

// Edit an existing Employee
EmployeeInputArea::EmployeeInputArea(QWidget *parent, const QModelIndex index)
    : QGroupBox(parent), ui(new Ui::EmployeeInputArea) {
  ui->setupUi(this);

  // Init UI
  qDebug() << "Init EmployeeInputarea for Index : " << index.row();

  m_actualMode = Mode::Edit;
  setViewOnlyMode(true);

  // Set the Model
  m_model = new QSqlRelationalTableModel(this);
  m_model->setTable(QLatin1String("employee"));
  m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

  m_model->select();

  // Set the mapper
  m_mapper = new QDataWidgetMapper(this);
  m_mapper->setModel(m_model);
  m_mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

  setMappings();

  m_mapper->setCurrentIndex(index.row());
}

EmployeeInputArea::~EmployeeInputArea() { delete ui; }

void EmployeeInputArea::setMappings() {
  // Set the fields to the mapper
  // Line 1.
  m_mapper->addMapping(ui->comboBox_Title,
                       m_model->fieldIndex(QLatin1String("title_id")));
  m_mapper->addMapping(ui->comboBox_Gender,
                       m_model->fieldIndex(QLatin1String("gender")));

  // Line 2.
  m_mapper->addMapping(ui->lineEdit_Firstname,
                       m_model->fieldIndex(QLatin1String("first_name")));
  m_mapper->addMapping(ui->lineEdit_Lastname,
                       m_model->fieldIndex(QLatin1String("last_name")));
  m_mapper->addMapping(ui->doubleSpinBox_PersNR,
                       m_model->fieldIndex(QLatin1String("employee_nr")));

  // Line 3.
  m_mapper->addMapping(ui->lineEditZipCode,
                       m_model->fieldIndex(QLatin1String("zipcity_id")));

  // TODO: Write City in the City Text Field
  m_mapper->addMapping(ui->lineEdit_Address,
                       m_model->fieldIndex(QLatin1String("address")));

  // Line 4.
  m_mapper->addMapping(ui->dateEdit_Birthday,
                       m_model->fieldIndex(QLatin1String("birth_day")));

  // Line 5.
  m_mapper->addMapping(ui->lineEdit_HomeMail,
                       m_model->fieldIndex(QLatin1String("home_mail_address")));
  m_mapper->addMapping(ui->lineEdit_HomePhone,
                       m_model->fieldIndex(QLatin1String("home_phone")));
  m_mapper->addMapping(ui->lineEdit_HomeMobile,
                       m_model->fieldIndex(QLatin1String("home_mobile")));

  // Line 6.
  m_mapper->addMapping(
      ui->lineEdit_BusinessMail,
      m_model->fieldIndex(QLatin1String("business_mail_addess")));
  m_mapper->addMapping(ui->checkBox_Active,
                       m_model->fieldIndex(QLatin1String("active")));
  m_mapper->addMapping(ui->checkBox_DataCare,
                       m_model->fieldIndex(QLatin1String("data_care")));

  // Line 7.
  m_mapper->addMapping(ui->dateEdit_StartDate,
                       m_model->fieldIndex(QLatin1String("hire_date")));
  m_mapper->addMapping(ui->dateEdit_EndDate,
                       m_model->fieldIndex(QLatin1String("end_date")));

  // Line 8.

  /*
     m_mapper->addMapping(ui->comboBoxPhone,
                     m_model->fieldIndex(QLatin1String("phone_id")));
     m_mapper->addMapping(ui->comboBoxMobile,
                     m_model->fieldIndex(QLatin1String("mobile_id")));
     m_mapper->addMapping(ui->comboBoxFax,
                     m_model->fieldIndex(QLatin1String("fax_id")));


     // Line 9.
     m_mapper->addMapping(ui->comboBoxComputer,
                     m_model->fieldIndex(QLatin1String("computer_id")));

     m_mapper->addMapping(ui->comboBoxPrinter,
                     m_model->fieldIndex(QLatin1String("printer_id")));

     m_mapper->addMapping(ui->comboBoxChipCard,
                     m_model->fieldIndex(QLatin1String("chipcard_id")));
     m_mapper->addMapping(ui->comboBoxDepartment,
                     m_model->fieldIndex(QLatin1String("department_id")));
     m_mapper->addMapping(ui->comboBoxFunction,
                     m_model->fieldIndex(QLatin1String("function_id")));

     // Line 10.
     m_mapper->addMapping(ui->comboBoxEmployeeAccount,
                     m_model->fieldIndex(QLatin1String("employee_account_id")));
     m_mapper->addMapping(ui->comboBoxEmployeeDocument,
                     m_model->fieldIndex(QLatin1String("employee_document_id")));
   */
  m_mapper->addMapping(ui->label_Lastupdate_Date,
                       m_model->fieldIndex(QLatin1String("last_update")));

  // Line 11.
  m_mapper->addMapping(ui->textEdit_Notes,
                       m_model->fieldIndex(QLatin1String("notes")));
}

void EmployeeInputArea::setViewOnlyMode(bool mode) {
  ui->checkBox_Active->setDisabled(mode);
  ui->checkBox_DataCare->setDisabled(mode);
  ui->comboBox_ChipCard->setDisabled(mode);
  ui->comboBox_Computer->setDisabled(mode);
  ui->comboBox_Department->setDisabled(mode);
  ui->comboBox_EmployeeAccount->setDisabled(mode);
  ui->comboBox_EmployeeDocument->setDisabled(mode);
  ui->comboBox_Fax->setDisabled(mode);
  ui->comboBox_Function->setDisabled(mode);
  ui->comboBox_Gender->setDisabled(mode);
  ui->comboBox_Mobile->setDisabled(mode);
  ui->comboBox_Phone->setDisabled(mode);
  ui->comboBox_Printer->setDisabled(mode);
  ui->comboBox_Title->setDisabled(mode);
  ui->dateEdit_Birthday->setDisabled(mode);
  ui->dateEdit_EndDate->setDisabled(mode);
  ui->dateEdit_StartDate->setDisabled(mode);
  ui->doubleSpinBox_PersNR->setDisabled(mode);
  ui->lineEditZipCode->setDisabled(mode);
  ui->lineEdit_Address->setDisabled(mode);
  ui->lineEdit_BusinessMail->setDisabled(mode);
  ui->lineEdit_City->setDisabled(mode);
  ui->lineEdit_Firstname->setDisabled(mode);
  ui->lineEdit_HomeMail->setDisabled(mode);
  ui->lineEdit_HomeMobile->setDisabled(mode);
  ui->lineEdit_HomePhone->setDisabled(mode);
  ui->lineEdit_Lastname->setDisabled(mode);
}

void EmployeeInputArea::createDataset() {
  qDebug() << "Create a new Dataset for Employee...";

  // Set all inputfields to blank
  m_mapper->toLast();

  int row = m_mapper->currentIndex();
  if (row < 0)
    row = 0;

  m_mapper->submit();
  m_model->insertRow(row);
  m_mapper->setCurrentIndex(row);
}

void EmployeeInputArea::retrieveDataset(const QModelIndex index) {}

void EmployeeInputArea::updateDataset(const QModelIndex index) {}

void EmployeeInputArea::deleteDataset(const QModelIndex index) {}

// Save the actual data

void EmployeeInputArea::on_pushButton_Add_clicked() {
  createDataset();
  on_pushButton_EditFinish_clicked();
}

void EmployeeInputArea::on_pushButton_EditFinish_clicked() {
  switch (m_actualMode) {
  case Mode::Edit: {
    m_actualMode = Mode::Finish;
    ui->pushButton_EditFinish->setText(tr("Finish"));
    setViewOnlyMode(false);

  } break;

  case Mode::Finish: {
    qDebug() << "Save Data...";

    m_actualMode = Mode::Edit;
    ui->pushButton_EditFinish->setText(tr("Edit"));
    setViewOnlyMode(false);

    QString lastName = ui->lineEdit_Lastname->text();

    if (lastName.isEmpty()) {
      QString message(tr("Please provide the name of the employee."));

      QMessageBox::information(this, tr("Add Employee"), message);
    } else {
      m_mapper->submit();
      m_model->database().transaction();
      if (m_model->submitAll()) {
        m_model->database().commit();
        qDebug() << "Commit changes for Employee Database Table";
      } else {
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
