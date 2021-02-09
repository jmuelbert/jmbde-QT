/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "views/printerinputarea.h"

#include "models/printer.h"
#include "ui_printerinputarea.h"

Q_LOGGING_CATEGORY(jmbdeWidgetsPrinterInputAreaLog, "jmuelbert.jmbde.widgets.printerinputarea", QtWarningMsg);

PrinterInputArea::PrinterInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::PrinterInputArea)
{
    ui->setupUi(this);

    // Init UI
    qCDebug(jmbdeWidgetsPrinterInputAreaLog) << "Init PrintInputarea for Index : " << index.row();

    this->m_printerModel = new Model::Printer();
    this->m_db = this->m_printerModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_printerModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);

    setMappings();

    m_mapper->setCurrentIndex(index.row());
}

PrinterInputArea::~PrinterInputArea()
{
    delete ui;
}

void PrinterInputArea::setMappings()
{
    m_mapper->addMapping(ui->deviceNameComboBox, this->m_printerModel->getDeviceNameIdIndex());
    m_mapper->addMapping(ui->serialNumberLineEdit, this->m_printerModel->getSerialNumberIndex());
    m_mapper->addMapping(ui->networkLineEdit, this->m_printerModel->getNetworkIndex());
    m_mapper->addMapping(ui->networkNameLineEdit, this->m_printerModel->getNetworkNameIndex());
    m_mapper->addMapping(ui->ipAddressLineEdit, this->m_printerModel->getNetworkIpAddressIndex());
    m_mapper->addMapping(ui->activeCheckBox, this->m_printerModel->getActiveIndex());
    m_mapper->addMapping(ui->replaceCheckBox, this->m_printerModel->getReplaceIndex());
    m_mapper->addMapping(ui->resourcesTextEdit, this->m_printerModel->getResourcesIndex());
    m_mapper->addMapping(ui->papersizeComboBox, this->m_printerModel->getPaperSizeMaxIndex());
    m_mapper->addMapping(ui->colorCheckBox, this->m_printerModel->getColorIndex());
    m_mapper->addMapping(ui->deviceTypeComboBox, this->m_printerModel->getDeviceTypeIdIndex());
    m_mapper->addMapping(ui->employeeComboBox, this->m_printerModel->getEmployeeIdIndex());
    m_mapper->addMapping(ui->placeComboBox, this->m_printerModel->getPlaceIdIndex());
    m_mapper->addMapping(ui->departmentComboBox, this->m_printerModel->getDepartmentIdIndex());
    m_mapper->addMapping(ui->manufacturerComboBox, this->m_printerModel->getManufacurerIdIndex());
    m_mapper->addMapping(ui->inventoryComboBox, this->m_printerModel->getInventoryIdIndex());
    m_mapper->addMapping(ui->computerComboBox, this->m_printerModel->getComputerIdIndex());
    m_mapper->addMapping(ui->lastUpdateLineEdit, this->m_printerModel->getLastUpdateIndex());
}

void PrinterInputArea::setViewOnlyMode(bool mode)
{
    ui->deviceNameComboBox->setDisabled(mode);
    ui->serialNumberLineEdit->setDisabled(mode);
    ui->networkLineEdit->setDisabled(mode);
    ui->networkNameLineEdit->setDisabled(mode);
    ui->ipAddressLineEdit->setDisabled(mode);
    ui->activeCheckBox->setDisabled(mode);
    ui->replaceCheckBox->setDisabled(mode);
    ui->resourcesTextEdit->setDisabled(mode);
    ui->papersizeComboBox->setDisabled(mode);
    ui->colorCheckBox->setDisabled(mode);
    ui->deviceTypeComboBox->setDisabled(mode);
    ui->employeeComboBox->setDisabled(mode);
    ui->placeComboBox->setDisabled(mode);
    ui->departmentComboBox->setDisabled(mode);
    ui->manufacturerComboBox->setDisabled(mode);
    ui->inventoryComboBox->setDisabled(mode);
    ui->computerComboBox->setDisabled(mode);
}

void PrinterInputArea::createDataset()
{
    qCDebug(jmbdeWidgetsPrinterInputAreaLog) << "Create a new Dataset for Processor...";

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

void PrinterInputArea::retrieveDataset(const QModelIndex index)
{
}

void PrinterInputArea::updateDataset(const QModelIndex index)
{
}

void PrinterInputArea::deleteDataset(const QModelIndex index)
{
}

void PrinterInputArea::on_pushButton_Add_clicked()
{
    createDataset();
    on_pushButton_EditFinish_clicked();
}

void PrinterInputArea::on_pushButton_EditFinish_clicked()
{
    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->editFinishPushButton->setText(tr("Fertig"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(jmbdeWidgetsPrinterInputAreaLog) << tr("Daten speichern...");

        m_actualMode = Mode::Edit;
        ui->editFinishPushButton->setText(tr("Bearbeiten"));
        setViewOnlyMode(false);

        m_mapper->submit();
        m_model->database().transaction();
        if (m_model->submitAll()) {
            m_model->database().commit();
            qCDebug(jmbdeWidgetsPrinterInputAreaLog) << tr("Änderung an der Tabelle printer in der Datenbank");
        } else {
            m_model->database().rollback();
            QMessageBox::warning(this, tr("jmbde"), tr("Die Datenbank meldet einen Fehler: %1").arg(m_model->lastError().text()));
        }

    } break;

    default: {
        qCCritical(jmbdeWidgetsPrinterInputAreaLog) << tr("Fehler");
    }
    }
}
