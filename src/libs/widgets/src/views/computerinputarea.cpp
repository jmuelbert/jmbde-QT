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

ComputerInputArea::ComputerInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent), ui(new Ui::ComputerInputArea) {
    ui->setupUi(this);

    qCDebug(jmbdewidgetsLog, "Init ComputerInputArea for Index : %s", index);

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = new QSqlRelationalTableModel(this);
    m_model->setTable(QLatin1String("computer"));
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    m_model->select();

    m_mapper = new QDataWidgetMapper(this);
    m_mapper->setModel(m_model);
    setMappings();

    m_mapper->setCurrentIndex(index.row());
}

ComputerInputArea::~ComputerInputArea() { delete ui; }

void ComputerInputArea::setMappings() {
    m_mapper->addMapping(ui->checkBox_Active,
                         m_model->fieldIndex(QLatin1String("active")));
    m_mapper->addMapping(ui->checkBox_Replace,
                         m_model->fieldIndex(QLatin1String("replace")));
    m_mapper->addMapping(ui->comboBox_Department,
                         m_model->fieldIndex(QLatin1String("department_id")));
    m_mapper->addMapping(ui->comboBox_DeviceName,
                         m_model->fieldIndex(QLatin1String("device_name_id")));
    m_mapper->addMapping(ui->comboBox_DeviceType,
                         m_model->fieldIndex(QLatin1String("device_type_id")));
    m_mapper->addMapping(ui->comboBox_Employee,
                         m_model->fieldIndex(QLatin1String("employee_id")));
    m_mapper->addMapping(ui->comboBox_Inventory,
                         m_model->fieldIndex(QLatin1String("inventory_id")));
    m_mapper->addMapping(ui->comboBox_Manufacturer,
                         m_model->fieldIndex(QLatin1String("manufacturer_id")));
    m_mapper->addMapping(ui->comboBox_OperationSystem,
                         m_model->fieldIndex(QLatin1String("os_id")));
    m_mapper->addMapping(ui->comboBox_Place,
                         m_model->fieldIndex(QLatin1String("place_id")));
    m_mapper->addMapping(ui->comboBox_Printer,
                         m_model->fieldIndex(QLatin1String("printer_id")));
    m_mapper->addMapping(ui->comboBox_Processor,
                         m_model->fieldIndex(QLatin1String("processor_id")));
    m_mapper->addMapping(
        ui->comboBox_Software,
        m_model->fieldIndex(QLatin1String("computer_software_id")));
    m_mapper->addMapping(ui->lineEdit_ComputerName,
                         m_model->fieldIndex(QLatin1String("network_name")));
    m_mapper->addMapping(
        ui->lineEdit_IPAddress,
        m_model->fieldIndex(QLatin1String("network_ip_address")));
    m_mapper->addMapping(ui->lineEdit_Network,
                         m_model->fieldIndex(QLatin1String("network_name")));
    m_mapper->addMapping(ui->lineEdit_SerialNumber,
                         m_model->fieldIndex(QLatin1String("serial_number")));
    m_mapper->addMapping(ui->lineEdit_ServiceNumber,
                         m_model->fieldIndex(QLatin1String("service_number")));
    m_mapper->addMapping(ui->lineEdit_ServiceTag,
                         m_model->fieldIndex(QLatin1String("service_tag")));
}

void ComputerInputArea::setViewOnlyMode(bool mode) {
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

void ComputerInputArea::createDataset() {
   qCDebug(jmbdewidgetsLog, "Create a new Dataset for Computer...");

    // Set all inputfields to blank
    m_mapper->toLast();

    int row = m_mapper->currentIndex();
    if (row < 0)
        row = 0;

    m_mapper->submit();
    m_model->insertRow(row);
    m_mapper->setCurrentIndex(row);
}

void ComputerInputArea::retrieveDataset(const QModelIndex index) {}

void ComputerInputArea::updateDataset(const QModelIndex index) {}

void ComputerInputArea::deleteDataset(const QModelIndex index) {}

void ComputerInputArea::on_pushButton_Add_clicked() {
    createDataset();
    on_pushButton_EditFinish_clicked();
}

void ComputerInputArea::on_pushButton_EditFinish_clicked() {
    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->pushButton_EditFinish->setText(tr("Finish"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(jmbdewidgetsLog, "Save Data...");

        m_actualMode = Mode::Edit;
        ui->pushButton_EditFinish->setText(tr("Edit"));
        setViewOnlyMode(false);

        QString lastName = ui->lineEdit_ComputerName->text();

        if (lastName.isEmpty()) {
            QString message(tr("Please provide the name of the computer."));

            QMessageBox::information(this, tr("Add Computer"), message);
        } else {
            m_mapper->submit();
            m_model->database().transaction();
            if (m_model->submitAll()) {
                m_model->database().commit();
                qDebug() << "Commit changes for Computer Databse Table";
            } else {
                m_model->database().rollback();
                QMessageBox::warning(this, tr("jmbde"),
                                     tr("The database reported an error: %1")
                                         .arg(m_model->lastError().text()));
            }
        }
    } break;

    default: {
        qCDebug(jmbdewidgetsLog, "Error");
    }
    }
}
