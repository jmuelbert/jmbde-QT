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

#include <ui_devicenameinputarea.h>
#include <views/devicenameinputarea.h>

Q_LOGGING_CATEGORY(jmbdeWidgetsDeviceNameInputAreaLog, "jmuelbert.jmbde.widgets.devicenameinputarea", QtWarningMsg)

DeviceNameInputArea::DeviceNameInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::DeviceNameInputArea)
{
    ui->setupUi(this);

    qCDebug(jmbdeWidgetsDeviceNameInputAreaLog) << "Init DeviceNameInputArea for Index :" << index.column();

    this->m_deviceNameModel = new Model::DeviceName();
    this->m_db = this->m_deviceNameModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_deviceNameModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);

    setMappings();

    m_mapper->setCurrentIndex(index.row());
}

DeviceNameInputArea::~DeviceNameInputArea()
{
    delete ui;
}

void DeviceNameInputArea::setMappings()
{
    m_mapper->addMapping(ui->nameLineEdit, this->m_deviceNameModel->getNameIndex());
    m_mapper->addMapping(ui->lastUpdatelineEdit, this->m_deviceNameModel->getLastUpdateIndex());
}

void DeviceNameInputArea::setViewOnlyMode(bool mode)
{
    ui->nameLineEdit->setDisabled(mode);
}

void DeviceNameInputArea ::createDataset()
{
    qCDebug(jmbdeWidgetsDeviceNameInputAreaLog) << "Create a new Dataset for ChipCard...";

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

void DeviceNameInputArea::retrieveDataset(const QModelIndex index)
{
}

void DeviceNameInputArea::updateDataset(const QModelIndex index)
{
}

void DeviceNameInputArea::deleteDataset(const QModelIndex index)
{
}

void DeviceNameInputArea::on_pushButton_Add_clicked()
{
    createDataset();
    on_pushButton_EditFinish_clicked();
}

void DeviceNameInputArea::on_pushButton_EditFinish_clicked()
{
    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->pushButton_EditFinish->setText(tr("Finish"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(jmbdeWidgetsDeviceNameInputAreaLog) << "Save Data...";

        m_actualMode = Mode::Edit;
        ui->pushButton_EditFinish->setText(tr("Edit"));
        setViewOnlyMode(false);

        QString name = ui->nameLineEdit->text();

        if (name.isEmpty()) {
            QString message(tr("Please provide the chipcard number."));

            QMessageBox::information(this, tr("Add Devicename"), message);
        } else {
            m_mapper->submit();
            m_model->database().transaction();
            if (m_model->submitAll()) {
                m_model->database().commit();
                qCDebug(jmbdeWidgetsDeviceNameInputAreaLog) << "Commit changes for Devicename Database Table";
                m_model->database().rollback();
            } else {
                m_model->database().rollback();
                QMessageBox::warning(this, tr("jmbde"), tr("The database reported an error: %1").arg(m_model->lastError().text()));
            }
        }
    } break;

    default: {
        qCCritical(jmbdeWidgetsDeviceNameInputAreaLog) << "Unknown Mode!";
    }
    }
}
