/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <ui_devicetypeinputarea.h>
#include <views/devicetypeinputarea.h>

Q_LOGGING_CATEGORY(jmbdeWidgetsDeviceTypeInputAreaLog, "jmuelbert.jmbde.widgets.devicetypeinputarea", QtWarningMsg)

DeviceTypeInputArea::DeviceTypeInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::DeviceTypeInputArea)
{
    ui->setupUi(this);

    qCDebug(jmbdeWidgetsDeviceTypeInputAreaLog) << "Init DeviceTypeInputArea for Index :" << index.column();

    this->m_deviceTypeModel = new Model::DeviceType();
    this->m_db = this->m_deviceTypeModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_deviceTypeModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);

    setMappings();

    m_mapper->setCurrentIndex(index.row());
}

DeviceTypeInputArea::~DeviceTypeInputArea()
{
    delete ui;
}

void DeviceTypeInputArea::setMappings()
{
    m_mapper->addMapping(ui->nameLineEdit, this->m_deviceTypeModel->getNameIndex());
    m_mapper->addMapping(ui->lastUpdateLineEdit, this->m_deviceTypeModel->getLastUpdateIndex());
}

void DeviceTypeInputArea::setViewOnlyMode(bool mode)
{
    ui->nameLineEdit->setDisabled(mode);
}

void DeviceTypeInputArea::createDataset()
{
    qCDebug(jmbdeWidgetsDeviceTypeInputAreaLog) << "Create a new Dataset for ChipCard...";

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

void DeviceTypeInputArea::retrieveDataset(const QModelIndex index)
{
}

void DeviceTypeInputArea::updateDataset(const QModelIndex index)
{
}

void DeviceTypeInputArea::deleteDataset(const QModelIndex index)
{
}

void DeviceTypeInputArea::on_pushButton_Add_clicked()
{
    createDataset();
    on_pushButton_EditFinish_clicked();
}

void DeviceTypeInputArea::on_pushButton_EditFinish_clicked()
{
    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->pushButton_EditFinish->setText(tr("Finish"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(jmbdeWidgetsDeviceTypeInputAreaLog) << "Save Data...";

        m_actualMode = Mode::Edit;
        ui->pushButton_EditFinish->setText(tr("Edit"));
        setViewOnlyMode(false);

        QString name = ui->nameLineEdit->text();

        if (name.isEmpty()) {
            QString message(tr("Please provide the chipcard number."));

            QMessageBox::information(this, tr("Add DeviceType"), message);
        } else {
            m_mapper->submit();
            m_model->database().transaction();
            if (m_model->submitAll()) {
                m_model->database().commit();
                qCDebug(jmbdeWidgetsDeviceTypeInputAreaLog) << "Commit changes for Chipcard Database Table";
                m_model->database().rollback();
            } else {
                m_model->database().rollback();
                QMessageBox::warning(this, tr("jmbde"), tr("The database reported an error: %1").arg(m_model->lastError().text()));
            }
        }
    } break;

    default: {
        qCCritical(jmbdeWidgetsDeviceTypeInputAreaLog) << "Unknown Mode!";
    }
    }
}
