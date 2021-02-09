/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "views/mobileinputarea.h"

#include "models/mobile.h"
#include "ui_mobileinputarea.h"

Q_LOGGING_CATEGORY(jmbdeWidgetsMobileInputAreaLog, "jmuelbert.jmbde.widgets.mobileinputarea", QtWarningMsg)

MobileInputArea::MobileInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::MobileInputArea)
{
    ui->setupUi(this);

    // Init UI
    qCDebug(jmbdeWidgetsMobileInputAreaLog) << "Init Mobilenputarea for Index : " << index.row();

    this->m_mobileModel = new Model::Mobile();
    this->m_db = this->m_mobileModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = new QSqlRelationalTableModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);

    setMappings();

    m_mapper->setCurrentIndex(index.row());
}

MobileInputArea::~MobileInputArea()
{
    delete ui;
}

void MobileInputArea::setMappings()
{
    m_mapper->addMapping(ui->deviceNameComboBox, this->m_mobileModel->getDeviceNameIdIndex());
    m_mapper->addMapping(ui->serialNumberLineEdit, this->m_mobileModel->getSerialNumberIndex());
    m_mapper->addMapping(ui->numberLineEdit, this->m_mobileModel->getNumberIndex());
    m_mapper->addMapping(ui->pinLineEdit, this->m_mobileModel->getPinIndex());
    m_mapper->addMapping(ui->cardNumberLineEdit, this->m_mobileModel->getCardNumberIndex());
    m_mapper->addMapping(ui->activeCheckBox, this->m_mobileModel->getActiveIndex());
    m_mapper->addMapping(ui->replaceCheckBox, this->m_mobileModel->getReplaceIndex());
    m_mapper->addMapping(ui->deviceTypeComboBox, this->m_mobileModel->getDeviceTypeIdIndex());
    m_mapper->addMapping(ui->employeeComboBox, this->m_mobileModel->getEmployeeIdIndex());
    m_mapper->addMapping(ui->placeComboBox, this->m_mobileModel->getDepartmentIdIndex());
    m_mapper->addMapping(ui->departmentComboBox, this->m_mobileModel->getDepartmentIdIndex());
    m_mapper->addMapping(ui->manufacturerComboBox, this->m_mobileModel->getManufacturerIdIndex());
    m_mapper->addMapping(ui->inventoryComboBox, this->m_mobileModel->getInventoryIdIndex());
    m_mapper->addMapping(ui->lastUpdateLineEdit, this->m_mobileModel->getLastUpdateIndex());
}

void MobileInputArea::setViewOnlyMode(bool mode)
{
    // ui->deviceNameComboBox->setDisabled(mode);
    ui->serialNumberLineEdit->setDisabled(mode);
    ui->numberLineEdit->setDisabled(mode);
    ui->pinLineEdit->setDisabled(mode);
    ui->cardNumberLineEdit->setDisabled(mode);
    ui->activeCheckBox->setDisabled(mode);
    ui->replaceCheckBox->setDisabled(mode);
    // ui->deviceTypeComboBox->setDisabled(mode);
    // ui->employeeComboBox->setDisabled(mode);
    // ui->placeComboBox->setDisabled(mode);
    // ui->departmentComboBox->setDisabled(mode);
    // ui->manufacturerComboBox->setDisabled(mode);
    // ui->inventoryComboBox->setDisabled(mode);
}

void MobileInputArea::createDataset()
{
    qDebug(jmbdeWidgetsMobileInputAreaLog) << "Create a new Dataset for Mobile...";

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

void MobileInputArea::retrieveDataset(const QModelIndex index)
{
}

void MobileInputArea::updateDataset(const QModelIndex index)
{
}

void MobileInputArea::deleteDataset(const QModelIndex index)
{
}

void MobileInputArea::on_pushButton_Add_clicked()
{
    createDataset();
    on_pushButton_EditFinish_clicked();
}

void MobileInputArea::on_pushButton_EditFinish_clicked()
{
    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->editFinishPushButton->setText(tr("Finish"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(jmbdeWidgetsMobileInputAreaLog) << tr("Sichere Daten...");

        m_actualMode = Mode::Edit;
        ui->editFinishPushButton->setText(tr("Bearbeiten"));
        setViewOnlyMode(false);

        QString number = ui->numberLineEdit->text();

        if (number.isEmpty()) {
            QString message(tr("Bitte eine Nummer angeben."));

            QMessageBox::information(this, tr("Mobiletelefon hinzfügen"), message);
        } else {
            m_mapper->submit();
            m_model->database().transaction();
            if (m_model->submitAll()) {
                m_model->database().commit();
                qCDebug(jmbdeWidgetsMobileInputAreaLog) << "Commit changes for Mobile Database Table";
            } else {
                m_model->database().rollback();
                QMessageBox::warning(this, tr("jmbde"), tr("TDie Datenbank meldet einen Fehler: %1").arg(m_model->lastError().text()));
            }
        }
    } break;

    default: {
        qCCritical(jmbdeWidgetsMobileInputAreaLog) << tr("Fehler");
    }
    }
}
