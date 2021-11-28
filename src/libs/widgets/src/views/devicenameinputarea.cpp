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

DeviceNameInputArea::DeviceNameInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::DeviceNameInputArea)
{
    ui->setupUi(this);

    qCDebug(jmbdeWidgetsDeviceNameInputAreaLog) << "Initialisiere DeviceNameInputArea mit Index :" << index.row();

    this->m_deviceNameModel = new Model::DeviceName();
    this->m_db = this->m_deviceNameModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_deviceNameModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);
    m_mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    setMappings();

    qCDebug(jmbdeWidgetsDeviceNameInputAreaLog) << tr("Aktueller Index: ") << m_mapper->currentIndex();

    if (index.row() < 0) {
        m_mapper->toFirst();
    } else {
        m_mapper->setCurrentIndex(index.row());
    }

    QObject::connect(this->ui->addPushButton, &QPushButton::released, this, &DeviceNameInputArea::addEdit);
    QObject::connect(this->ui->editFinishPushButton, &QPushButton::released, this, &DeviceNameInputArea::editFinish);
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
    qCDebug(jmbdeWidgetsDeviceNameInputAreaLog) << tr("Erzeuge einen neuen, leeren Datensatz für DeviceName...");

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

void DeviceNameInputArea::deleteDataset(const QModelIndex &index)
{
    qCDebug(jmbdeWidgetsDeviceNameInputAreaLog) << tr("Lösche Daten von DeviceName");
    m_mapper->setCurrentIndex(index.row());
}

void DeviceNameInputArea::addEdit()
{
    qCDebug(jmbdeWidgetsDeviceNameInputAreaLog) << tr("Füge neue Daten zu DeviceName");
    createDataset();
    editFinish();
}

void DeviceNameInputArea::editFinish()
{
    qCDebug(jmbdeWidgetsDeviceNameInputAreaLog) << tr("Bearbeite oder schließe DeviceName Daten");

    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->editFinishPushButton->setText(tr("Fertig"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(jmbdeWidgetsDeviceNameInputAreaLog) << tr("Die Daten werden gesichert.");

        m_actualMode = Mode::Edit;
        ui->editFinishPushButton->setText(tr("Bearbeiten"));
        setViewOnlyMode(false);

        QString name = ui->nameLineEdit->text();

        if (name.isEmpty()) {
            QString message(tr("Bitte den Gerätenamen eingeben."));

            QMessageBox::information(this, tr("Gerätenamen hinzufügen."), message);
        } else {
            m_mapper->submit();
            m_model->database().transaction();
            if (m_model->submitAll()) {
                m_model->database().commit();
                qCDebug(jmbdeWidgetsDeviceNameInputAreaLog) << tr("Schreiben der Änderungen für DeviceName in die Datenbank");
                dataChanged();
            } else {
                m_model->database().rollback();
                QMessageBox::warning(this, tr("jmbde"), tr("Die Datenbank meldet den Fehler: %1").arg(m_model->lastError().text()));
            }
        }
    } break;

    default: {
        qCCritical(jmbdeWidgetsDeviceNameInputAreaLog) << tr("Fehler: Unbekannter Modus");
    }
    }
}
