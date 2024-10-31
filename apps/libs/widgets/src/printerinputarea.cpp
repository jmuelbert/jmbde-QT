/*
 *  SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "jmbdewidgets/printerinputarea.h"
#include "ui_printerinputarea.h"

PrinterInputArea::PrinterInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::PrinterInputArea)
{
    ui->setupUi(this);

    // Init UI
    qDebug() << tr("Initialisiere PrintInputarea mit Index : ") << index.row();

    this->m_printerModel = new Model::Printer();
    this->m_db = this->m_printerModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_printerModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);
    m_mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    setMappings();

    qDebug() << tr("Aktueller Index: ") << m_mapper->currentIndex();

    if (index.row() < 0) {
        m_mapper->toFirst();
    } else {
        m_mapper->setCurrentIndex(index.row());
    }

    QObject::connect(this->ui->addPushButton, &QPushButton::released, this, &PrinterInputArea::addEdit);
    QObject::connect(this->ui->editFinishPushButton, &QPushButton::released, this, &PrinterInputArea::editFinish);
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
    // ui->deviceNameComboBox->setDisabled(mode);
    ui->serialNumberLineEdit->setDisabled(mode);
    ui->networkLineEdit->setDisabled(mode);
    ui->networkNameLineEdit->setDisabled(mode);
    ui->ipAddressLineEdit->setDisabled(mode);
    ui->activeCheckBox->setDisabled(mode);
    ui->replaceCheckBox->setDisabled(mode);
    ui->resourcesTextEdit->setDisabled(mode);
    // ui->papersizeComboBox->setDisabled(mode);
    ui->colorCheckBox->setDisabled(mode);
    //  ui->deviceTypeComboBox->setDisabled(mode);
    // ui->employeeComboBox->setDisabled(mode);
    // ui->placeComboBox->setDisabled(mode);
    // ui->departmentComboBox->setDisabled(mode);
    // ui->manufacturerComboBox->setDisabled(mode);
    // ui->inventoryComboBox->setDisabled(mode);
    // ui->computerComboBox->setDisabled(mode);
}

void PrinterInputArea::createDataset()
{
    qDebug() << tr("Erzeuge einen neuen, leeren Datensatz für Printer...");

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

void PrinterInputArea::deleteDataset(const QModelIndex &index)
{
    qDebug() << tr("Lösche Daten von Printer");
    m_mapper->setCurrentIndex(index.row());
}

void PrinterInputArea::addEdit()
{
    qDebug() << tr("Füge neue Daten zu Printer");
    createDataset();
    editFinish();
}

void PrinterInputArea::editFinish()
{
    qDebug() << tr("Bearbeite oder schließe Printer Daten");

    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->editFinishPushButton->setText(tr("Fertig"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qDebug() << tr("Die Daten werden gesichert.");

        m_actualMode = Mode::Edit;
        ui->editFinishPushButton->setText(tr("Bearbeiten"));
        setViewOnlyMode(false);

        QString name = ui->networkNameLineEdit->text();

        if (name.isEmpty()) {
            QString message(tr("Bitte einen Name für den Druckernamen angeben"));

            QMessageBox::information(this, tr("Drucker hinzufügen"), message);
        } else {
            m_mapper->submit();
            m_model->database().transaction();
            if (m_model->submitAll()) {
                m_model->database().commit();
                qDebug() << tr("Schreiben der Änderungen für Printer in die Datenbank");
                emit dataChanged();
            } else {
                m_model->database().rollback();
                QMessageBox::warning(this, tr("jmbde"), tr("Die Datenbank meldet den Fehler: %1").arg(m_model->lastError().text()));
            }
        }
    } break;

    default: {
        qCritical() << tr("Fehler: Unbekannter Modus");
    }
    }
}
