/*
 *  SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "jmbdewidgets/phoneinputarea.h"

#include "ui_phoneinputarea.h"

PhoneInputArea::PhoneInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::PhoneInputArea)
{
    ui->setupUi(this);

    // Init UI
    qDebug() << tr("Initialisiere PhoneInputarea mit Index : ") << index.row();

    this->m_phoneModel = new Model::Phone();
    this->m_db = this->m_phoneModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_phoneModel->initializeRelationalModel();

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

    QObject::connect(this->ui->addPushButton, &QPushButton::released, this, &PhoneInputArea::addEdit);
    QObject::connect(this->ui->editFinishPushButton, &QPushButton::released, this, &PhoneInputArea::editFinish);
}

PhoneInputArea::~PhoneInputArea()
{
    delete ui;
}

void PhoneInputArea::setMappings()
{
    m_mapper->addMapping(ui->deviceNameComboBox, this->m_phoneModel->getDeviceNameIdIndex());
    m_mapper->addMapping(ui->serialNumberLineEdit, this->m_phoneModel->getSerialNumberIndex());
    m_mapper->addMapping(ui->numberLineEdit, this->m_phoneModel->getNumberIndex());
    m_mapper->addMapping(ui->pinLineEdit, this->m_phoneModel->getPinIndex());
    m_mapper->addMapping(ui->activeCheckBox, this->m_phoneModel->getActiveIndex());
    m_mapper->addMapping(ui->replaceCheckBox, this->m_phoneModel->getReplaceIndex());
    m_mapper->addMapping(ui->deviceTypeComboBox, this->m_phoneModel->getDeviceTypeIdIndex());
    m_mapper->addMapping(ui->employeeComboBox, this->m_phoneModel->getEmployeeIdIndex());
    m_mapper->addMapping(ui->placeComboBox, this->m_phoneModel->getPlaceIdIndex());
    m_mapper->addMapping(ui->departmentComboBox, this->m_phoneModel->getDepartmentIdIndex());
    m_mapper->addMapping(ui->manufacturerComboBox, this->m_phoneModel->getManufacturerIdIndex());
    m_mapper->addMapping(ui->inventoryComboBox, this->m_phoneModel->getInventoryIdIndex());
    m_mapper->addMapping(ui->lastUpdateLineEdit, this->m_phoneModel->getLastUpdateIndex());
}

void PhoneInputArea::setViewOnlyMode(bool mode)
{
    // ui->deviceNameComboBox->setDisabled(mode);
    ui->serialNumberLineEdit->setDisabled(mode);
    ui->numberLineEdit->setDisabled(mode);
    ui->pinLineEdit->setDisabled(mode);
    ui->activeCheckBox->setDisabled(mode);
    ui->replaceCheckBox->setDisabled(mode);
    // ui->deviceTypeComboBox->setDisabled(mode);
    // ui->employeeComboBox->setDisabled(mode);
    // ui->placeComboBox->setDisabled(mode);
    // ui->departmentComboBox->setDisabled(mode);
    // ui->manufacturerComboBox->setDisabled(mode);
    // ui->inventoryComboBox->setDisabled(mode);
}

void PhoneInputArea::createDataset()
{
    qDebug() << tr("Erzeuge einen neuen, leeren Datensatz für Phone...");

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

void PhoneInputArea::deleteDataset(const QModelIndex &index)
{
    qDebug() << tr("Lösche Daten von Phone");
    m_mapper->setCurrentIndex(index.row());
}

void PhoneInputArea::addEdit()
{
    qDebug() << tr("Füge neue Daten zu Phone");
    createDataset();
    editFinish();
}

void PhoneInputArea::editFinish()
{
    qDebug() << tr("Bearbeite oder schließe Phone Daten");

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

        QString number = ui->numberLineEdit->text();
        qDebug() << tr("Number : ") << number;

        if (number.isEmpty()) {
            QString message(tr("Bitte eine Telefonnummer angeben."));

            QMessageBox::information(this, tr("Telefon hinzufügen"), message);
        } else {
            m_mapper->submit();
            m_model->database().transaction();
            if (m_model->submitAll()) {
                m_model->database().commit();
                qDebug() << tr("Schreiben der Änderungen für Phone in die Datenbank");
                dataChanged();
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
