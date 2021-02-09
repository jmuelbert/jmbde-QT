/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "views/employeeinputarea.h"

#include "ui_employeeinputarea.h"

Q_LOGGING_CATEGORY(jmbdeWidgetsEmployeeInputAreaLog, "jmuelbert.jmbde.widgets.employeeinputarea", QtWarningMsg)

// Edit an existing Employee
EmployeeInputArea::EmployeeInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::EmployeeInputArea)
{
    ui->setupUi(this);

    qCDebug(jmbdeWidgetsEmployeeInputAreaLog) << "Init EmployeeInputArea for Index :" << index.column();

    this->m_employeeModel = new Model::Employee();
    this->m_db = this->m_employeeModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_employeeModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);

    setMappings();

    m_mapper->setCurrentIndex(index.row());
}

EmployeeInputArea::~EmployeeInputArea()
{
    delete ui;
}

void EmployeeInputArea::setMappings()
{
    m_mapper->addMapping(ui->employeeNumberDoubleSpinBox, this->m_employeeModel->getEmployeeNrIndex());
    m_mapper->addMapping(ui->genderComboBox, this->m_employeeModel->getGenderIndex());
    m_mapper->addMapping(ui->titleComboBox, this->m_employeeModel->getTitleIdIndex());
    m_mapper->addMapping(ui->firstNameLineEdit, this->m_employeeModel->getFirstNameIndex());
    m_mapper->addMapping(ui->lastNameLineEdit, this->m_employeeModel->getLastNameIndex());
    m_mapper->addMapping(ui->birthdayDateEdit, this->m_employeeModel->getBirthDayIndex());
    m_mapper->addMapping(ui->addressLineEdit, this->m_employeeModel->getAddressIndex());
    m_mapper->addMapping(ui->zipCityIdComboBox, this->m_employeeModel->getZipCityIdIndex());
    m_mapper->addMapping(ui->homePhoneLineEdit, this->m_employeeModel->getHomePhoneIndex());
    m_mapper->addMapping(ui->homeMobileLineEdit, this->m_employeeModel->getHomeMobileIndex());
    m_mapper->addMapping(ui->homeMailLineEdit, this->m_employeeModel->getHomeMailIndex());
    m_mapper->addMapping(ui->businessMailLineEdit, this->m_employeeModel->getBusinessMailIndex());
    m_mapper->addMapping(ui->dataCareCheckBox, this->m_employeeModel->getDataCareIndex());
    m_mapper->addMapping(ui->activeCheckBox, this->m_employeeModel->getActiveIndex());
    m_mapper->addMapping(ui->photoGraphicsView, this->m_employeeModel->getPhotoIndex());
    m_mapper->addMapping(ui->notesTextEdit, this->m_employeeModel->getNotesIndex());
    m_mapper->addMapping(ui->hireDateDateEdit, this->m_employeeModel->getHireDateIndex());
    m_mapper->addMapping(ui->endDateDateEdit, this->m_employeeModel->getEndDateIndex());
    m_mapper->addMapping(ui->departmentComboBox, this->m_employeeModel->getDepartmentIdIndex());
    m_mapper->addMapping(ui->functionComboBox, this->m_employeeModel->getFunctionIdIndex());
    m_mapper->addMapping(ui->computerComboBox, this->m_employeeModel->getComputerIdIndex());
    m_mapper->addMapping(ui->printerComboBox, this->m_employeeModel->getPrinterIdIndex());
    m_mapper->addMapping(ui->phoneComboBox, this->m_employeeModel->getPhoneIdIndex());
    m_mapper->addMapping(ui->mobileComboBox, this->m_employeeModel->getMobileIdIndex());
    m_mapper->addMapping(ui->faxComboBox, this->m_employeeModel->getFaxIdIndex());
    m_mapper->addMapping(ui->employeeAccountComboBox, this->m_employeeModel->getEmployeeAccountIdIndex());
    m_mapper->addMapping(ui->employeeDocumentComboBox, this->m_employeeModel->getEmployeeDocumentIdIndex());
    m_mapper->addMapping(ui->chipCardComboBox, this->m_employeeModel->getChipCardIdIndex());
    m_mapper->addMapping(ui->lastUpdateLineEdit, this->m_employeeModel->getLastUpdateIndex());
}

void EmployeeInputArea::setViewOnlyMode(bool mode)
{
    ui->employeeNumberDoubleSpinBox->setDisabled(mode);
    // ui->genderComboBox->setDisabled(mode);
    // ui->titleComboBox->setDisabled(mode);
    ui->firstNameLineEdit->setDisabled(mode);
    ui->lastNameLineEdit->setDisabled(mode);
    ui->birthdayDateEdit->setDisabled(mode);
    ui->addressLineEdit->setDisabled(mode);
    // ui->zipCityIdComboBox->setDisabled(mode);
    ui->homePhoneLineEdit->setDisabled(mode);
    ui->homeMobileLineEdit->setDisabled(mode);
    ui->homeMailLineEdit->setDisabled(mode);
    ui->businessMailLineEdit->setDisabled(mode);
    ui->dataCareCheckBox->setDisabled(mode);
    ui->activeCheckBox->setDisabled(mode);
    // ui->photoGraphicsView->setDisabled(mode);
    ui->notesTextEdit->setDisabled(mode);
    ui->hireDateDateEdit->setDisabled(mode);
    ui->endDateDateEdit->setDisabled(mode);
    // ui->departmentComboBox->setDisabled(mode);
    // ui->functionComboBox->setDisabled(mode);
    // ui->computerComboBox->setDisabled(mode);
    // ui->printerComboBox->setDisabled(mode);
    // ui->phoneComboBox->setDisabled(mode);
    // ui->mobileComboBox->setDisabled(mode);
    // ui->faxComboBox->setDisabled(mode);
    // ui->employeeAccountComboBox->setDisabled(mode);
    // ui->employeeDocumentComboBox->setDisabled(mode);
    // ui->chipCardComboBox->setDisabled(mode);
    ui->lastUpdateLineEdit->setDisabled(mode);
}

void EmployeeInputArea::createDataset()
{
    // Set all inputfields to blank
    m_mapper->toLast();

    int row = m_mapper->currentIndex();
    if (row < 0) {
        row = 0;
    }
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

        QString lastName = ui->lastNameLineEdit->text();

        if (lastName.isEmpty()) {
            QString message(tr("Bitte geben Sie den Mitarbeiternamen ein"));

            QMessageBox::information(this, tr("Mitarbeiter hinzufügen"), message);
        } else {
            qCDebug(jmbdeWidgetsEmployeeInputAreaLog) << tr("Mitarbeiter : ") << ui->lastNameLineEdit->text();
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
