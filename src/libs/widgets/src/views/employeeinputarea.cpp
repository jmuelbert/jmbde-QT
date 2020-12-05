/*
   jmbde a BDE Tool for companies
   Copyright (C) 2013-2020 Jürgen Mülbert

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
*/

#include "views/employeeinputarea.h"

#include "ui_employeeinputarea.h"

Q_LOGGING_CATEGORY(jmbdeWidgetsEmployeeInputAreaLog, "jmuelbert.jmbde.widgets.employeeinputarea", QtWarningMsg)

// Edit an existing Employee
EmployeeInputArea::EmployeeInputArea(QWidget *parent, const QModelIndex index)
    : QGroupBox(parent)
    , ui(new Ui::EmployeeInputArea)
{
    ui->setupUi(this);

    qCDebug(jmbdeWidgetsEmployeeInputAreaLog) << "Init ComputerInputArea for Index :" << index.column();

    this->m_employeeModel = new Model::Employee();
    this->m_db = this->m_employeeModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_employeeModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);
    m_mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    setMappings();

    m_mapper->setCurrentIndex(index.row());
}

EmployeeInputArea::~EmployeeInputArea()
{
    delete ui;
}

void EmployeeInputArea::setMappings()
{
    // Set the fields to the mapper
    // Line 1.
    m_mapper->addMapping(ui->comboBox_Title, this->m_employeeModel->getTitleIdIndex());
    m_mapper->addMapping(ui->comboBox_Gender, this->m_employeeModel->getGenderIndex());

    // Line 2.
    m_mapper->addMapping(ui->lineEdit_Firstname, this->m_employeeModel->getFirstNameIndex());
    m_mapper->addMapping(ui->lineEdit_Lastname, this->m_employeeModel->getLastNameIndex());
    m_mapper->addMapping(ui->doubleSpinBox_PersNR, this->m_employeeModel->getEmployeeNrIndex());

    // Line 3.
    m_mapper->addMapping(ui->lineEditZipCode, this->m_employeeModel->getZipCityIdIndex());

    // TODO: Write City in the City Text Field
    m_mapper->addMapping(ui->lineEdit_Address, this->m_employeeModel->getAddressIndex());

    // Line 4.
    m_mapper->addMapping(ui->dateEdit_Birthday, this->m_employeeModel->getBirthDayIndex());

    // Line 5.
    m_mapper->addMapping(ui->lineEdit_HomeMail, this->m_employeeModel->getHomeMailIndex());
    m_mapper->addMapping(ui->lineEdit_HomePhone, this->m_employeeModel->getHomePhoneIndex());
    m_mapper->addMapping(ui->lineEdit_HomeMobile, this->m_employeeModel->getHomeMobileIndex());

    // Line 6.
    m_mapper->addMapping(ui->lineEdit_BusinessMail, this->m_employeeModel->getBusinessMailIndex());
    m_mapper->addMapping(ui->checkBox_Active, this->m_employeeModel->getActiveIndex());
    m_mapper->addMapping(ui->checkBox_DataCare, this->m_employeeModel->getDataCareIndex());

    // Line 7.
    m_mapper->addMapping(ui->dateEdit_StartDate, this->m_employeeModel->getHireDateIndex());
    m_mapper->addMapping(ui->dateEdit_EndDate, this->m_employeeModel->getEndDateIndex());

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
    m_mapper->addMapping(ui->label_Lastupdate_Date, this->m_employeeModel->getLastUpdateIndex());

    // Line 11.
    m_mapper->addMapping(ui->textEdit_Notes, this->m_employeeModel->getNotesIndex());
}

void EmployeeInputArea::setViewOnlyMode(bool mode)
{
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

void EmployeeInputArea::createDataset()
{
    // Set all inputfields to blank
    m_mapper->toLast();

    int row = m_mapper->currentIndex();
    if (row < 0)
        row = 0;

    m_mapper->submit();
    m_model->insertRow(row);
    m_mapper->setCurrentIndex(row);
}

void EmployeeInputArea::retrieveDataset(const QModelIndex index)
{
}

void EmployeeInputArea::updateDataset(const QModelIndex index)
{
}

void EmployeeInputArea::deleteDataset(const QModelIndex index)
{
}

// Save the actual data

void EmployeeInputArea::on_pushButton_Add_clicked()
{
    createDataset();
    on_pushButton_EditFinish_clicked();
}

void EmployeeInputArea::on_pushButton_EditFinish_clicked()
{
    // Set all inputfields to blank

    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->pushButton_EditFinish->setText(tr("Fertig"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(jmbdeWidgetsEmployeeInputAreaLog) << tr("Die Daten werden gesichert.");

        m_actualMode = Mode::Edit;
        ui->pushButton_EditFinish->setText(tr("Bearbeiten"));
        setViewOnlyMode(false);

        QString lastName = ui->lineEdit_Lastname->text();

        if (lastName.isEmpty()) {
            QString message(tr("Bitte geben Sie den Mitarbeiternamen ein"));

            QMessageBox::information(this, tr("Mitarbeiter hinzufügen"), message);
        } else {
            qCDebug(jmbdeWidgetsEmployeeInputAreaLog) << tr("Mitarbeiter : ") << ui->lineEdit_Lastname->text();
            m_mapper->submit();
            m_model->database().transaction();
            if (m_model->submitAll()) {
                m_model->database().commit();
                qCDebug(jmbdeWidgetsEmployeeInputAreaLog) << tr("Schreiben der Änderungen in die Datenbank");
                emit dataChanged();
            } else {
                m_model->database().rollback();
                QMessageBox::warning(this, tr("jmbde"), tr("Die Datenbank meldet den Fehler: %1").arg(m_model->lastError().text()));
            }
        }
    } break;

    default: {
        qCDebug(jmbdeWidgetsEmployeeInputAreaLog) << tr("Fehler");
    }
    }
}
