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

#include "views/computerinputarea.h"
#include "ui_computerinputarea.h"

ComputerInputArea::ComputerInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent), ui(new Ui::ComputerInputArea) {
    ui->setupUi(this);

    qDebug() << "Init ComputerInputArea for Index : " << index;

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
    qDebug() << "Create a new Dataset for Computer...";

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
        qDebug() << "Save Data...";

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
        qDebug() << "Error";
    }
    }
}
