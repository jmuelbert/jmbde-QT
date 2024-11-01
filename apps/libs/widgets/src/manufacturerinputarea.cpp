/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "jmbdewidgets/manufacturerinputarea.h"
#include <ui_manufacturerinputarea.h>

ManufacturerInputArea::ManufacturerInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::ManufacturerInputArea)
{
    ui->setupUi(this);

    qDebug() << tr("Initialisiere ManufacturerInputArea mit Index :") << index.row();

    this->m_manufacturerModel = new Model::Manufacturer();
    this->m_db = this->m_manufacturerModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_manufacturerModel->initializeRelationalModel();

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

    QObject::connect(this->ui->addPushButton, &QPushButton::released, this, &ManufacturerInputArea::addEdit);
    QObject::connect(this->ui->editFinishPushButton, &QPushButton::released, this, &ManufacturerInputArea::editFinish);
}

ManufacturerInputArea::~ManufacturerInputArea()
{
    delete ui;
}

void ManufacturerInputArea::setMappings()
{
    m_mapper->addMapping(ui->nameLineEdit, this->m_manufacturerModel->getNameIndex());
    m_mapper->addMapping(ui->name2LineEdit, this->m_manufacturerModel->getName2Index());
    m_mapper->addMapping(ui->supporterLineEdit, this->m_manufacturerModel->getSupporterIndex());
    m_mapper->addMapping(ui->addressLineEdit, this->m_manufacturerModel->getAddressIndex());
    m_mapper->addMapping(ui->address2LineEdit, this->m_manufacturerModel->getAddress2Index());
    m_mapper->addMapping(ui->zipCodeComboBox, this->m_manufacturerModel->getZipCityIdIndex());
    m_mapper->addMapping(ui->mailAddressLineEdit, this->m_manufacturerModel->getMailAddressIndex());
    m_mapper->addMapping(ui->phoneNumberLineEdit, this->m_manufacturerModel->getPhoneNumberIndex());
    m_mapper->addMapping(ui->faxNumberLineEdit, this->m_manufacturerModel->getFaxNumberIndex());
    m_mapper->addMapping(ui->hotlineNumberLineEdit, this->m_manufacturerModel->getHotlineNumberIndex());
    m_mapper->addMapping(ui->lastUpdateLineEdit, this->m_manufacturerModel->getLastUpdateIndex());
}

void ManufacturerInputArea::setViewOnlyMode(bool mode)
{
    ui->nameLineEdit->setDisabled(mode);
    ui->name2LineEdit->setDisabled(mode);
    ui->supporterLineEdit->setDisabled(mode);
    ui->addressLineEdit->setDisabled(mode);
    ui->address2LineEdit->setDisabled(mode);
    // ui->zipCodeComboBox->setDisabled(mode);
    ui->mailAddressLineEdit->setDisabled(mode);
    ui->phoneNumberLineEdit->setDisabled(mode);
    ui->faxNumberLineEdit->setDisabled(mode);
    ui->hotlineNumberLineEdit->setDisabled(mode);
}

void ManufacturerInputArea::createDataset()
{
    qDebug() << tr("Erzeuge einen neuen, leeren Datensatz für Manufacturer...");

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

void ManufacturerInputArea::deleteDataset(const QModelIndex &index)
{
    qDebug() << tr("Lösche Daten von Manufacturer");

    m_mapper->setCurrentIndex(index.row());
}

void ManufacturerInputArea::addEdit()
{
    qDebug() << tr("Füge neue Daten zu Manufacturer");

    createDataset();
    editFinish();
}

void ManufacturerInputArea::editFinish()
{
    qDebug() << tr("Bearbeite oder schließe Manufacturer Daten");

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

        QString name = ui->nameLineEdit->text();

        if (name.isEmpty()) {
            QString message(tr("Bitte einen Namen angeben."));

            QMessageBox::information(this, tr("Hersteller hinzufügen"), message);
        } else {
            m_mapper->submit();
            m_model->database().transaction();
            if (m_model->submitAll()) {
                m_model->database().commit();

                qDebug() << tr("Schreiben der Änderungen für Manufacturer in die Datenbank");

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
