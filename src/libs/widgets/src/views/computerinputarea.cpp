/*
    jmbde a BDE Tool for companies
    Copyright (C) 2013-2019  Jürgen Mülbert

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

#include "views/computerinputarea.h"

#include "ui_computerinputarea.h"

Q_LOGGING_CATEGORY(jmbdeWidgetsComputerInputAreaLog, "jmuelbert.jmbde.widgets.employeeinputarea", QtWarningMsg)

ComputerInputArea::ComputerInputArea(QWidget *parent, const QModelIndex index)
    : QGroupBox(parent)
    , ui(new Ui::ComputerInputArea)
{
    ui->setupUi(this);

    qCDebug(jmbdeWidgetsComputerInputAreaLog) << "Init ComputerInputArea for Index :" << index.column();

    this->m_computerModel = new Model::Computer();
    this->m_db = this->m_computerModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_computerModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);
    m_mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    setMappings();

    m_mapper->setCurrentIndex(index.row());
}

ComputerInputArea::~ComputerInputArea()
{
    delete ui;
}

void ComputerInputArea::setMappings()
{
    m_mapper->addMapping(ui->checkBox_Active, this->m_computerModel->getActiveIndex());
    m_mapper->addMapping(ui->checkBox_Replace, this->m_computerModel->getReplaceIndex());
    m_mapper->addMapping(ui->comboBox_Department, this->m_computerModel->getDepartmentIdIndex());
    m_mapper->addMapping(ui->comboBox_DeviceName, this->m_computerModel->getDeviceNameIdIndex());
    m_mapper->addMapping(ui->comboBox_DeviceType, this->m_computerModel->getDeviceTypeIdIndex());
    m_mapper->addMapping(ui->comboBox_Employee, this->m_computerModel->getEmployeeIdIndex());
    m_mapper->addMapping(ui->comboBox_Inventory, this->m_computerModel->getInventoryIdIndex());
    m_mapper->addMapping(ui->comboBox_Manufacturer, this->m_computerModel->getManufacturerIdIndex());
    m_mapper->addMapping(ui->comboBox_OperationSystem, this->m_computerModel->getOSIdIndex());
    m_mapper->addMapping(ui->comboBox_Place, this->m_computerModel->getPlaceIdIndex());
    m_mapper->addMapping(ui->comboBox_Printer, this->m_computerModel->getPrinterIdIndex());
    m_mapper->addMapping(ui->comboBox_Processor, this->m_computerModel->getProcessorIdIndex());
    m_mapper->addMapping(ui->comboBox_Software, this->m_computerModel->getComputerSoftwareIdIndex());
    m_mapper->addMapping(ui->lineEdit_ComputerName, this->m_computerModel->getNetworkNameIndex());
    m_mapper->addMapping(ui->lineEdit_IPAddress, this->m_computerModel->getNetworkIndex());
    m_mapper->addMapping(ui->lineEdit_SerialNumber, this->m_computerModel->getSerialNumberIndex());
    m_mapper->addMapping(ui->lineEdit_ServiceNumber, this->m_computerModel->getServiceNumberIndex());
    m_mapper->addMapping(ui->lineEdit_ServiceTag, this->m_computerModel->getServiceTagIndex());
}

void ComputerInputArea::setViewOnlyMode(bool mode)
{
    ui->checkBox_Active->setDisabled(mode);
    ui->checkBox_Replace->setDisabled(mode);
    ui->comboBox_Department->setDisabled(mode);
    ui->comboBox_DeviceName->setDisabled(mode);
    ui->comboBox_DeviceType->setDisabled(mode);
    ui->comboBox_Employee->setDisabled(mode);
    ui->comboBox_Inventory->setDisabled(mode);
    ui->comboBox_Manufacturer->setDisabled(mode);
    ui->comboBox_OperationSystem->setDisabled(mode);
    ui->comboBox_Place->setDisabled(mode);
    ui->comboBox_Printer->setDisabled(mode);
    ui->comboBox_Processor->setDisabled(mode);
    ui->comboBox_Software->setDisabled(mode);
    ui->lineEdit_ComputerName->setDisabled(mode);
    ui->lineEdit_IPAddress->setDisabled(mode);
    ui->lineEdit_Network->setDisabled(mode);
    ui->lineEdit_SerialNumber->setDisabled(mode);
    ui->lineEdit_ServiceNumber->setDisabled(mode);
    ui->lineEdit_ServiceTag->setDisabled(mode);
}

void ComputerInputArea::createDataset()
{
    qCDebug(jmbdeWidgetsComputerInputAreaLog) << "Create a new Dataset for Computer...";

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

void ComputerInputArea::retrieveDataset(const QModelIndex index)
{
}

void ComputerInputArea::updateDataset(const QModelIndex index)
{
}

void ComputerInputArea::deleteDataset(const QModelIndex index)
{
}

void ComputerInputArea::on_pushButton_Add_clicked()
{
    createDataset();
    on_pushButton_EditFinish_clicked();
}

void ComputerInputArea::on_pushButton_EditFinish_clicked()
{
    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->pushButton_EditFinish->setText(tr("Finish"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(jmbdeWidgetsComputerInputAreaLog) << tr("Die Daten werden gesichert.");

        m_actualMode = Mode::Edit;
        ui->pushButton_EditFinish->setText(tr("Edit"));
        setViewOnlyMode(false);

        QString computerName = ui->lineEdit_ComputerName->text();

        if (computerName.isEmpty()) {
            QString message(tr("Bitte geben Sie einen Computernamen an."));

            QMessageBox::information(this, tr("Computer hinzufügen"), message);
        } else {
            m_mapper->submit();
            m_model->database().transaction();
            if (m_model->submitAll()) {
                m_model->database().commit();
                qCDebug(jmbdeWidgetsComputerInputAreaLog) << tr("Schreiben der Änderungen in die Datenbank");
                emit dataChanged();
            } else {
                m_model->database().rollback();
                QMessageBox::warning(this, tr("jmbde"), tr("Die Datenbank meldet den Fehler: %1").arg(m_model->lastError().text()));
            }
        }
    } break;

    default: {
        qCDebug(jmbdeWidgetsComputerInputAreaLog) << tr("Fehler");
    }
    }
}
