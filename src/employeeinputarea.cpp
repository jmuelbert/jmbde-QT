//

// EmployeeInputArea
// part of jmbde
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
//

#include "employeeinputarea.h"
#include "ui_employeeinputdialog.h"

// Add an new Employee
EmployeeInputArea::EmployeeInputArea(QWidget* parent)
  : QScrollArea(parent), ui(new Ui::EmployeeInputArea) {
  // Init UI
  ui->setupUi(this);

  preSetFields(true);

  // Set the Model
  model = new QSqlRelationalTableModel(this);
  model->setTable(QLatin1String("employee"));
  model->setEditStrategy(QSqlTableModel::OnManualSubmit);

  // Set the indexes for the relations
  functionIndex = model->fieldIndex(QLatin1String("function_id"));
  departmentIndex = model->fieldIndex(QLatin1String("department_id"));
  computerIndex = model->fieldIndex(QLatin1String("computer_id"));
  printerIndex = model->fieldIndex(QLatin1String("printer_id"));
  chipCardIndex = model->fieldIndex(QLatin1String("chipcard_id"));
  phoneIndex = model->fieldIndex(QLatin1String("phone_id"));
  mobileIndex = model->fieldIndex(QLatin1String("mobile_id"));
  faxIndex = model->fieldIndex(QLatin1String("fax_id"));

  // employeeAccountIdx = model->fieldIndex(QLatin1String("employee_accout_id"));
  // employeeDocumentIdx = model->fieldIndex(QLatin1String("employee_document_id"));

  // Set the relations to the other databases tables
  model->setRelation(phoneIndex, QSqlRelation("phone", "phone_id", "number"));
  model->setRelation(mobileIndex, QSqlRelation("mobile", "mobile_id", "number"));
  model->setRelation(faxIndex, QSqlRelation("fax", "fax_id", "number"));

  model->setRelation(computerIndex, QSqlRelation("computer", "computer_id", "network_name"));
  model->setRelation(printerIndex, QSqlRelation("printer", "printer_id", "network_name"));
  model->setRelation(chipCardIndex, QSqlRelation("chipcard", "chipcard_id", "name"));

  model->setRelation(departmentIndex, QSqlRelation("department", "department_id", "name"));
  model->setRelation(functionIndex, QSqlRelation("function", "function_id", "name"));

  // model->setRelation(employeeAccountIdx, QSqlRelation("employeeaccount", "employee_account_id", "name"));
  // model->setRelation(employeeDocumentIdx, QSqlRelation("employeedocument", "employee_document_id", "name"));

  model->select();

//  ui->comboBoxPhone->setModel(model->relationModel(phoneIndex));
//  ui->comboBoxPhone->setModelColumn(model->relationModel(phoneIndex)->fieldIndex("number"));

//  ui->comboBoxMobile->setModel(model->relationModel(mobileIndex));
//  ui->comboBoxMobile->setModelColumn(model->relationModel(mobileIndex)->fieldIndex("number"));

//  ui->comboBoxFax->setModel(model->relationModel(faxIndex));
//  ui->comboBoxFax->setModelColumn(model->relationModel(faxIndex)->fieldIndex("number"));

//    ui->comboBoxComputer->setModel(model->relationModel(computerIndex));
//    ui->comboBoxComputer->setModelColumn(model->relationModel(computerIndex)->fieldIndex("network_name"));

//    ui->comboBoxPrinter->setModel(model->relationModel(printerIndex));
//    ui->comboBoxPrinter->setModelColumn(model->relationModel(printerIndex)->fieldIndex("network_name"));

//    ui->comboBoxChipCard->setModel(model->relationModel(chipCardIndex));
//    ui->comboBoxChipCard->setModelColumn(model->relationModel(chipCardIndex)->fieldIndex("name"));

//    ui->comboBoxDepartment->setModel(model->relationModel(departmentIndex));
//    ui->comboBoxDepartment->setModelColumn(model->relationModel(departmentIndex)->fieldIndex("name"));

//    ui->comboBoxFunction->setModel(model->relationModel(functionIndex));
//    ui->comboBoxFunction->setModelColumn(model->relationModel(functionIndex)->fieldIndex("name"));

//    ui->comboBoxEmployeeAccount->setModel(model->relationModel(employeeAccountIdx));
//    ui->comboBoxEmployeeAccount->setModelColumn(model->relationModel(employeeAccountIdx)->fieldIndex("name"));

//    ui->comboBoxEmployeeDocument->setModel(model->relationModel(employeeDocumentIdx));
//    ui->comboBoxEmployeeDocument->setModelColumn(model->relationModel(employeeDocumentIdx)->fieldIndex("name"));

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

  ui->doubleSpinBox_PersNR->setValue(++row);
  ui->lineEdit_Firstname->clear();
  ui->lineEdit_Firstname->setFocus();
  ui->lineEdit_Lastname->clear();

}

// Edit an existing Employee
EmployeeInputArea::EmployeeInputArea(QWidget* parent, int index)
  : QScrollArea (parent), ui(new Ui::EmployeeInputArea) {
  // Init UI
  ui->setupUi(this);

  preSetFields(false);

  // Set the Model
  model = new QSqlRelationalTableModel(this);
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
  ui->comboBox_Phone->setModel(model->relationModel(phoneIndex));

  setMappings(model, mapper);

  mapper->setCurrentIndex(index);

  ui->lineEdit_Firstname->setFocus();
}

EmployeeInputArea::~EmployeeInputArea() {
  delete ui;
}

void EmployeeInputArea::preSetFields(bool newEmployee) {

  QStringList qslGender;

  qslGender.append(tr("Not Set"));
  qslGender.append(tr("m"));
  qslGender.append(tr("f"));

  ui->comboBox_Gender->addItems(qslGender);

  QStringList qslTitle;

  qslTitle.append(tr("Not Set"));
  qslTitle.append(tr("Mr."));
  qslTitle.append(tr("Ms."));

  ui->comboBox_Title->addItems(qslTitle);

  /*
     if (newEmployee == true) {
     QString *dateString = new QString(QDate::QDate().currentDate().toString(QLatin1String("dd.MM.yyyy")));
     ui->labelLastupdate_Date->setText(&dateString);
     ui->dateEditStartDate->setDate(QDate::QDate().currentDate());
     }
   */
}

void EmployeeInputArea::setMappings(QSqlTableModel* model,
                                      QDataWidgetMapper* mapper) {
  // Set the fields to the mapper
  // Line 1.
  mapper->addMapping(ui->comboBox_Title,
                     model->fieldIndex(QLatin1String("title_id")));
  mapper->addMapping(ui->comboBox_Gender,
                     model->fieldIndex(QLatin1String("gender")));

  // Line 2.
  mapper->addMapping(ui->lineEdit_Firstname,
                     model->fieldIndex(QLatin1String("first_name")));
  mapper->addMapping(ui->lineEdit_Lastname,
                     model->fieldIndex(QLatin1String("last_name")));
  mapper->addMapping(ui->doubleSpinBox_PersNR,
                     model->fieldIndex(QLatin1String("employee_nr")));

  // Line 3.
  mapper->addMapping(ui->lineEditZipCode,
                     model->fieldIndex(QLatin1String("zipcity_id")));

  // TODO: Write City in the City Text Field
  mapper->addMapping(ui->lineEdit_Address,
                     model->fieldIndex(QLatin1String("address")));

  // Line 4.
  mapper->addMapping(ui->dateEdit_Birthday,
                     model->fieldIndex(QLatin1String("birth_day")));

  // Line 5.
  mapper->addMapping(ui->lineEdit_HomeMail,
                     model->fieldIndex(QLatin1String("home_mail_address")));
  mapper->addMapping(ui->lineEdit_HomePhone,
                     model->fieldIndex(QLatin1String("home_phone")));
  mapper->addMapping(ui->lineEdit_HomeMobile,
                     model->fieldIndex(QLatin1String("home_mobile")));

  // Line 6.
  mapper->addMapping(ui->lineEdit_BusinessMail,
                     model->fieldIndex(QLatin1String("business_mail_addess")));
  mapper->addMapping(ui->checkBox_Active,
                     model->fieldIndex(QLatin1String("active")));
  mapper->addMapping(ui->checkBox_DataCare,
                     model->fieldIndex(QLatin1String("data_care")));

  // Line 7.
  mapper->addMapping(ui->dateEdit_StartDate,
                     model->fieldIndex(QLatin1String("hire_date")));
  mapper->addMapping(ui->dateEdit_EndDate,
                     model->fieldIndex(QLatin1String("end_date")));

  // Line 8.

  /*
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
   */
  mapper->addMapping(ui->label_Lastupdate_Date,
                     model->fieldIndex(QLatin1String("last_update")));

  // Line 11.
  mapper->addMapping(ui->textEdit_Notes,
                     model->fieldIndex(QLatin1String("notes")));
}

void EmployeeInputArea::on_pushButtonAdd_clicked()
{
    qDebug() << "Click Add";

}

void EmployeeInputArea::on_pushButtonEdit_clicked()
{
    qDebug() << "Click Edit";
}

void EmployeeInputArea::onClickedEmployeeTable(const QModelIndex index) {
    qDebug() << "Select row: " << index;
}
