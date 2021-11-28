/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "views/computerinputarea.h"

#include "ui_computerinputarea.h"

ComputerInputArea::ComputerInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::ComputerInputArea)
{
    ui->setupUi(this);

    qCDebug(jmbdeWidgetsComputerInputAreaLog) << "Initialisiere ComputerInputArea für Index :" << index.row();

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

    qCDebug(jmbdeWidgetsComputerInputAreaLog) << tr("Aktueller Index: ") << m_mapper->currentIndex();

    if (index.row() < 0) {
        m_mapper->toFirst();
    } else {
        m_mapper->setCurrentIndex(index.row());
    }

    QObject::connect(this->ui->addPushButton, &QPushButton::released, this, &ComputerInputArea::addEdit);
    QObject::connect(this->ui->editFinishPushButton, &QPushButton::released, this, &ComputerInputArea::editFinish);
}

ComputerInputArea::~ComputerInputArea()
{
    delete ui;
}

void ComputerInputArea::setMappings()
{
    m_mapper->addMapping(ui->deviceNameComboBox, this->m_computerModel->getDeviceNameIdIndex());
    m_mapper->addMapping(ui->serialNumberLineEdit, this->m_computerModel->getSerialNumberIndex());
    m_mapper->addMapping(ui->serviceTagLineEdit, this->m_computerModel->getServiceTagIndex());
    m_mapper->addMapping(ui->serviceNumberLineEdit, this->m_computerModel->getServiceNumberIndex());
    m_mapper->addMapping(ui->memorySpinBox, this->m_computerModel->getMemoryIndex());
    m_mapper->addMapping(ui->networkLineEdit, this->m_computerModel->getNetworkIndex());
    m_mapper->addMapping(ui->netWorkNameLineEdit, this->m_computerModel->getNetworkNameIndex());
    m_mapper->addMapping(ui->ipAddressLineEdit, this->m_computerModel->getNetworkIndex());
    m_mapper->addMapping(ui->activeCheckBox, this->m_computerModel->getActiveIndex());
    m_mapper->addMapping(ui->replaceCheckBox, this->m_computerModel->getReplaceIndex());
    m_mapper->addMapping(ui->deviceTypeComboBox, this->m_computerModel->getDeviceTypeIdIndex());
    m_mapper->addMapping(ui->employeeComboBox, this->m_computerModel->getEmployeeIdIndex());
    m_mapper->addMapping(ui->placeComboBox, this->m_computerModel->getPlaceIdIndex());
    m_mapper->addMapping(ui->departmentComboBox, this->m_computerModel->getDepartmentIdIndex());
    m_mapper->addMapping(ui->manufacturerComboBox, this->m_computerModel->getManufacturerIdIndex());
    m_mapper->addMapping(ui->inventoryComboBox, this->m_computerModel->getInventoryIdIndex());
    m_mapper->addMapping(ui->processorComboBox, this->m_computerModel->getProcessorIdIndex());
    m_mapper->addMapping(ui->operationSystemComboBox, this->m_computerModel->getOSIdIndex());
    m_mapper->addMapping(ui->softwareComboBox, this->m_computerModel->getComputerSoftwareIdIndex());
    m_mapper->addMapping(ui->printerComboBox, this->m_computerModel->getPrinterIdIndex());
    m_mapper->addMapping(ui->lastUpdateLineEdit, this->m_computerModel->getLastUpdateIndex());
}

void ComputerInputArea::setViewOnlyMode(bool mode)
{
    // ui->deviceNameComboBox->setDisabled(mode);
    ui->serialNumberLineEdit->setDisabled(mode);
    ui->serviceTagLineEdit->setDisabled(mode);
    ui->serviceNumberLineEdit->setDisabled(mode);
    ui->memorySpinBox->setDisabled(mode);
    ui->networkLineEdit->setDisabled(mode);
    ui->netWorkNameLineEdit->setDisabled(mode);
    ui->ipAddressLineEdit->setDisabled(mode);
    ui->activeCheckBox->setDisabled(mode);
    ui->replaceCheckBox->setDisabled(mode);
    // ui->deviceTypeComboBox->setDisabled(mode);
    // ui->employeeComboBox->setDisabled(mode);
    // ui->placeComboBox->setDisabled(mode);
    // ui->departmentComboBox->setDisabled(mode);
    // ui->manufacturerComboBox->setDisabled(mode);
    // ui->inventoryComboBox->setDisabled(mode);
    // ui->processorComboBox->setDisabled(mode);
    // ui->operationSystemComboBox->setDisabled(mode);
    // ui->softwareComboBox->setDisabled(mode);
    // ui->printerComboBox->setDisabled(mode);
}

void ComputerInputArea::createDataset()
{
    qCDebug(jmbdeWidgetsComputerInputAreaLog) << tr("Erzeuge einen neuen, leeren Datensatz für Computer...");

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

void ComputerInputArea::deleteDataset(const QModelIndex &index)
{
    qCDebug(jmbdeWidgetsComputerInputAreaLog) << tr("Lösche Daten von Computer");
    m_mapper->setCurrentIndex(index.row());
}

void ComputerInputArea::addEdit()
{
    qCDebug(jmbdeWidgetsComputerInputAreaLog) << tr("Füge neue Daten zu Computer");
    createDataset();
    editFinish();
}

void ComputerInputArea::editFinish()
{
    qCDebug(jmbdeWidgetsComputerInputAreaLog) << tr("Bearbeite oder schließe Computer Daten");

    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->editFinishPushButton->setText(tr("Fertig"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(jmbdeWidgetsComputerInputAreaLog) << tr("Die Daten werden gesichert.");

        m_actualMode = Mode::Edit;
        ui->editFinishPushButton->setText(tr("Bearbeiten"));
        setViewOnlyMode(false);

        QString computerName = ui->netWorkNameLineEdit->text();

        if (computerName.isEmpty()) {
            QString message(tr("Bitte geben Sie einen Computernamen an."));

            QMessageBox::information(this, tr("Computer hinzufügen"), message);
        } else {
            m_mapper->submit();
            m_model->database().transaction();
            if (m_model->submitAll()) {
                m_model->database().commit();
                qCDebug(jmbdeWidgetsComputerInputAreaLog) << tr("Schreiben der Änderungen für Account in die Datenbank");
                dataChanged();
            } else {
                m_model->database().rollback();
                QMessageBox::warning(this, tr("jmbde"), tr("Die Datenbank meldet den Fehler: %1").arg(m_model->lastError().text()));
            }
        }
    } break;

    default: {
        qCDebug(jmbdeWidgetsComputerInputAreaLog) << tr("Fehler: Unbekannter Modus");
    }
    }
}
