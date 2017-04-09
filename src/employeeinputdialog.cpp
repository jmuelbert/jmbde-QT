/*
 * EmployeeInputDialog.cpp
 * jmbde
 *
 *  Copyright (c) 2013-2017 Jürgen Mülbert. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the European Union Public Licence (EUPL),
 * version 1.1.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * European Union Public Licence for more details.
 *
 * You should have received a copy of the European Union Public Licence
 * along with this program. If not, see
 * http://www.osor.eu/eupl/european-union-public-licence-eupl-v.1.1
 *
 */

#include "employeeinputdialog.h"
#include "ui_employeeinputdialog.h"

// Add an new Employee
EmployeeInputDialog::EmployeeInputDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::EmployeeInputDialog) {
  // Init UI
  ui->setupUi(this);

  preSetFields(true);

  // Set the Model
  model = new QSqlTableModel(this);
  model->setTable(QLatin1String("employee"));
  model->setEditStrategy(QSqlTableModel::OnManualSubmit);

  // Set the indexes for the relations
  functionIndex = model->fieldIndex(QLatin1String("function_id"));
  departmentIndex = model->fieldIndex(QLatin1String("department_id"));
  computerIndex = model->fieldIndex(QLatin1String("computer_id"));
  printerIndex = model->fieldIndex(QLatin1String("printer_id"));
  phoneIndex = model->fieldIndex(QLatin1String("phone_id"));
  mobileIndex = model->fieldIndex(QLatin1String("mobile_id"));
  faxIndex = model->fieldIndex(QLatin1String("fax_id"));

  model->select();

  // Set the mapper
  mapper = new QDataWidgetMapper(this);
  mapper->setModel(model);
  mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

  setMappings(model, mapper);

  // To the last row to adding a dataset
  mapper->toLast();
  int row = mapper->currentIndex();
  mapper->submit();
  model->insertRow(row);
  mapper->setCurrentIndex(row);

  ui->doubleSpinBoxPersNR->setValue(++row);
  ui->lineEditFirstname->clear();
  ui->lineEditFirstname->setFocus();
  ui->lineEditLastname->clear();
  PhoneDataModel *phd = new PhoneDataModel();
  QSqlQueryModel *phoneQuery = phd->getQueryModel();
  ui->comboBoxPhone->setModel(phoneQuery);
}

// Edit an existing Employee
EmployeeInputDialog::EmployeeInputDialog(QWidget *parent, int index)
    : QDialog(parent), ui(new Ui::EmployeeInputDialog) {
  // Init UI
  ui->setupUi(this);

  preSetFields(false);

  // Set the Model
  model = new QSqlTableModel(this);
  model->setTable(QLatin1String("employee"));
  model->setEditStrategy(QSqlTableModel::OnManualSubmit);

  // Set the indexes for the relations
  functionIndex = model->fieldIndex(QLatin1String("function_id"));
  departmentIndex = model->fieldIndex(QLatin1String("department_id"));
  computerIndex = model->fieldIndex(QLatin1String("computer_id"));
  printerIndex = model->fieldIndex(QLatin1String("printer_id"));
  phoneIndex = model->fieldIndex(QLatin1String("phone_id"));
  mobileIndex = model->fieldIndex(QLatin1String("mobile_id"));
  faxIndex = model->fieldIndex(QLatin1String("fax_id"));

  model->select();

  // Set the mapper
  mapper = new QDataWidgetMapper(this);
  mapper->setModel(model);
  mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

  setMappings(model, mapper);

  mapper->setCurrentIndex(index);

  ui->lineEditFirstname->setFocus();
}

EmployeeInputDialog::~EmployeeInputDialog() { delete ui; }

void EmployeeInputDialog::on_buttonBox_accepted() {
  qDebug() << "Name : " << ui->lineEditLastname->text();
  mapper->submit();
  model->database().transaction();
  if (model->submitAll()) {
    model->database().commit();
  } else {
    model->database().rollback();
    QMessageBox::warning(this, tr("Cached Table"),
                         tr("The database reported an error: %1")
                             .arg(model->lastError().text()));
  }
}

void EmployeeInputDialog::on_buttonBox_rejected() {
  model->database().rollback();
  qDebug() << "Cancel Clicked!, DB-rollback.!";
}

void EmployeeInputDialog::preSetFields(bool newEmployee) {
  QStringList qslGender;
  qslGender.append("Not Set");
  qslGender.append("m");
  qslGender.append("f");

  ui->comboBoxGender->addItems(qslGender);

  QStringList qslTitle;
  qslTitle.append("Not Set");
  qslTitle.append("Mr.");
  qslTitle.append("Ms.");

  ui->comboBoxTitle->addItems(qslTitle);

  if (newEmployee == true) {
    QString dateString = QDate::QDate().currentDate().toString("dd.MM.yyyy");
    ui->labelLastupdate_Date->setText(dateString);
    ui->dateEditStartDate->setDate(QDate::QDate().currentDate());
  }
}

void EmployeeInputDialog::setMappings(QSqlTableModel *model,
                                      QDataWidgetMapper *mapper) {
  // Set the fields to the mapper
  // Line 1.
  mapper->addMapping(ui->comboBoxTitle,
                     model->fieldIndex(QLatin1String("title_id")));
  mapper->addMapping(ui->comboBoxGender,
                     model->fieldIndex(QLatin1String("gender")));
  // Line 2.
  mapper->addMapping(ui->lineEditFirstname,
                     model->fieldIndex(QLatin1String("firstname")));
  mapper->addMapping(ui->lineEditLastname,
                     model->fieldIndex(QLatin1String("lastname")));
  mapper->addMapping(ui->doubleSpinBoxPersNR,
                     model->fieldIndex(QLatin1String("employee_nr")));

  // Line 3.
  mapper->addMapping(ui->lineEditZipCode,
                     model->fieldIndex(QLatin1String("zipcity_id")));
  // TODO: Write City in the City Text Field
  mapper->addMapping(ui->lineEditAddress,
                     model->fieldIndex(QLatin1String("address")));

  // Line 4.
  mapper->addMapping(ui->dateEditBirthday,
                     model->fieldIndex(QLatin1String("birthday")));

  // Line 5.
  mapper->addMapping(ui->lineEditHomeMail,
                     model->fieldIndex(QLatin1String("homeemail")));
  mapper->addMapping(ui->lineEditHomePhone,
                     model->fieldIndex(QLatin1String("homephone")));
  mapper->addMapping(ui->lineEditHomeMobile,
                     model->fieldIndex(QLatin1String("homemobile")));

  // Line 6.
  mapper->addMapping(ui->lineEditBusinessMail,
                     model->fieldIndex(QLatin1String("businessemail")));
  mapper->addMapping(ui->checkBoxActive,
                     model->fieldIndex(QLatin1String("active")));
  mapper->addMapping(ui->checkBoxDatacare,
                     model->fieldIndex(QLatin1String("datacare")));

  // Line 7.
  mapper->addMapping(ui->dateEditStartDate,
                     model->fieldIndex(QLatin1String("startdate")));
  mapper->addMapping(ui->dateEditEndDate,
                     model->fieldIndex(QLatin1String("enddate")));

  // Line 8.
  mapper->addMapping(ui->comboBoxPhone,
                     model->fieldIndex(QLatin1String("phone_id")));
  mapper->addMapping(ui->comboBoxMobile,
                     model->fieldIndex(QLatin1String("mobile_id")));
  mapper->addMapping(ui->comboBoxFax,
                     model->fieldIndex(QLatin1String("fax_id")));

  // Line 9.
  mapper->addMapping(ui->comboBoxComputer,
                     model->fieldIndex(QLatin1String("computer_id")));
  mapper->addMapping(ui->comboBoxPrinter,
                     model->fieldIndex(QLatin1String("printer_id")));
  mapper->addMapping(ui->comboBoxChipCard,
                     model->fieldIndex(QLatin1String("chipcard_id")));
  mapper->addMapping(ui->comboBoxDepartment,
                     model->fieldIndex(QLatin1String("department_id")));
  mapper->addMapping(ui->comboBoxFunction,
                     model->fieldIndex(QLatin1String("function_id")));

  // Line 10.
  mapper->addMapping(ui->comboBoxEmployeeAccount,
                     model->fieldIndex(QLatin1String("employee_account_id")));
  mapper->addMapping(ui->comboBoxEmployeeDocument,
                     model->fieldIndex(QLatin1String("employee_document_id")));
  mapper->addMapping(ui->labelLastupdate_Date,
                     model->fieldIndex(QLatin1String("last_update")));

  // Line 11.
  mapper->addMapping(ui->textEditNotes,
                     model->fieldIndex(QLatin1String("notes")));
}
