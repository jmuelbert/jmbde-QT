/**************************************************************************
**
** Copyright (c) 2013-2019 Jürgen Mülbert. All rights reserved.
**
** This file is part of jmbde
**
** Licensed under the EUPL, Version 1.2 or – as soon they
** will be approved by the European Commission - subsequent
** versions of the EUPL (the "Licence");
** You may not use this work except in compliance with the
** Licence.
** You may obtain a copy of the Licence at:
**
** https://joinup.ec.europa.eu/page/eupl-text-11-12
**
** Unless required by applicable law or agreed to in
** writing, software distributed under the Licence is
** distributed on an "AS IS" basis,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
** express or implied.
** See the Licence for the specific language governing
** permissions and limitations under the Licence.
**
** Lizenziert unter der EUPL, Version 1.2 oder - sobald
**  diese von der Europäischen Kommission genehmigt wurden -
** Folgeversionen der EUPL ("Lizenz");
** Sie dürfen dieses Werk ausschließlich gemäß
** dieser Lizenz nutzen.
** Eine Kopie der Lizenz finden Sie hier:
**
** https://joinup.ec.europa.eu/page/eupl-text-11-12
**
** Sofern nicht durch anwendbare Rechtsvorschriften
** gefordert oder in schriftlicher Form vereinbart, wird
** die unter der Lizenz verbreitete Software "so wie sie
** ist", OHNE JEGLICHE GEWÄHRLEISTUNG ODER BEDINGUNGEN -
** ausdrücklich oder stillschweigend - verbreitet.
** Die sprachspezifischen Genehmigungen und Beschränkungen
** unter der Lizenz sind dem Lizenztext zu entnehmen.
**
**************************************************************************/

#include "printerinputarea.h"
#include "ui_printerinputarea.h"

PrinterInputArea::PrinterInputArea(QWidget *parent, const QModelIndex index)
    : QGroupBox(parent), ui(new Ui::PrinterInputArea) {
    ui->setupUi(this);

    // Init UI
    qDebug() << "Init ProcessorInputarea for Index : " << index.row();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = new QSqlRelationalTableModel(this);
    m_model->setTable(QLatin1String("printer"));
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    m_model->select();

    // Set the mapper
    m_mapper = new QDataWidgetMapper(this);
    m_mapper->setModel(m_model);
    m_mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    setMappings();

    m_mapper->setCurrentIndex(index.row());
}

PrinterInputArea::~PrinterInputArea() { delete ui; }

void PrinterInputArea::setMappings() {
    m_mapper->addMapping(ui->checkBox_Active,
                         m_model->fieldIndex(QLatin1String("active")));
    m_mapper->addMapping(ui->checkBox_Color,
                         m_model->fieldIndex(QLatin1String("color")));
    m_mapper->addMapping(ui->checkBox_Replace,
                         m_model->fieldIndex(QLatin1String("replace")));
    m_mapper->addMapping(ui->comboBox_Computer,
                         m_model->fieldIndex(QLatin1String("computer_id")));
    m_mapper->addMapping(ui->comboBox_Department,
                         m_model->fieldIndex(QLatin1String("department_id")));

    m_mapper->addMapping(ui->comboBox_DeviceName,
                         m_model->fieldIndex(QLatin1String("device_name_id")));
    m_mapper->addMapping(ui->comboBox_DeviceType,
                         m_model->fieldIndex(QLatin1String("device_type_id")));
    m_mapper->addMapping(ui->comboBox_Employee,
                         m_model->fieldIndex(QLatin1String("employe_id")));
    m_mapper->addMapping(ui->comboBox_Inventory,
                         m_model->fieldIndex(QLatin1String("inventory_id")));
    m_mapper->addMapping(ui->comboBox_Manufacturer,
                         m_model->fieldIndex(QLatin1String("manufacturer_id")));

    m_mapper->addMapping(ui->comboBox_Papersize,
                         m_model->fieldIndex(QLatin1String("paper_size_max")));
    m_mapper->addMapping(ui->comboBox_Place,
                         m_model->fieldIndex(QLatin1String("place_id")));
    m_mapper->addMapping(ui->lineEdit_PrinterName,
                         m_model->fieldIndex(QLatin1String("network_name")));
    m_mapper->addMapping(
        ui->lineEdit_IPAddress,
        m_model->fieldIndex(QLatin1String("network_ip_address")));
    m_mapper->addMapping(ui->lineEdit_Network,
                         m_model->fieldIndex(QLatin1String("network")));
    m_mapper->addMapping(ui->lineEdit_SerialNumber,
                         m_model->fieldIndex(QLatin1String("serial_number")));
    m_mapper->addMapping(ui->textEdit_Resources,
                         m_model->fieldIndex(QLatin1String("resources")));
}

void PrinterInputArea::setViewOnlyMode(bool mode) {
    ui->checkBox_Active->setDisabled(mode);
    ui->checkBox_Color->setDisabled(mode);
    ui->checkBox_Replace->setDisabled(mode);
    ui->comboBox_Computer->setDisabled(mode);
    ui->comboBox_Department->setDisabled(mode);
    ui->comboBox_DeviceName->setDisabled(mode);
    ui->comboBox_DeviceType->setDisabled(mode);
    ui->comboBox_Employee->setDisabled(mode);
    ui->comboBox_Inventory->setDisabled(mode);
    ui->comboBox_Manufacturer->setDisabled(mode);
    ui->comboBox_Papersize->setDisabled(mode);
    ui->comboBox_Place->setDisabled(mode);
    ui->lineEdit_IPAddress->setDisabled(mode);
    ui->lineEdit_Network->setDisabled(mode);
    ui->lineEdit_PrinterName->setDisabled(mode);
    ui->lineEdit_SerialNumber->setDisabled(mode);
    ui->textEdit_Resources->setDisabled(mode);
}

void PrinterInputArea::createDataset() {
    qDebug() << "Create a new Dataset for Processor...";

    // Set all inputfields to blank
    m_mapper->toLast();

    int row = m_mapper->currentIndex();
    if (row < 0)
        row = 0;

    m_mapper->submit();
    m_model->insertRow(row);
    m_mapper->setCurrentIndex(row);
}

void PrinterInputArea::retrieveDataset(const QModelIndex index) {}

void PrinterInputArea::updateDataset(const QModelIndex index) {}

void PrinterInputArea::deleteDataset(const QModelIndex index) {}

void PrinterInputArea::on_pushButton_Add_clicked() {
    createDataset();
    on_pushButton_EditFinish_clicked();
}

void PrinterInputArea::on_pushButton_EditFinish_clicked() {
    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->pushButton_EditFinish->setText(tr("Finish"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qDebug() << "Save Data...";

        m_actualMode = Mode::Edit;
        ui->pushButton_EditFinish->setText(tr("Edit"));
        setViewOnlyMode(false);

        m_mapper->submit();
        m_model->database().transaction();
        if (m_model->submitAll()) {
            m_model->database().commit();
            qDebug() << "Commit changes for Processor Databse Table";
        } else {
            m_model->database().rollback();
            QMessageBox::warning(this, tr("jmbde"),
                                 tr("The database reported an error: %1")
                                     .arg(m_model->lastError().text()));
        }

    } break;

    default: {
        qDebug() << "Error";
    }
    }
}
