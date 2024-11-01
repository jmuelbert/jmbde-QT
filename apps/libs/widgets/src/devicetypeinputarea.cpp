/*
 *  SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "jmbdewidgets/devicetypeinputarea.h"
#include <ui_devicetypeinputarea.h>

DeviceTypeInputArea::DeviceTypeInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::DeviceTypeInputArea)
{
    ui->setupUi(this);

    qDebug() << tr("Initialisiere DeviceTypeInputArea mit Index :") << index.row();

    this->m_deviceTypeModel = new Model::DeviceType();
    this->m_db = this->m_deviceTypeModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_deviceTypeModel->initializeRelationalModel();

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

    QObject::connect(this->ui->addPushButton, &QPushButton::released, this, &DeviceTypeInputArea::addEdit);
    QObject::connect(this->ui->editFinishPushButton, &QPushButton::released, this, &DeviceTypeInputArea::editFinish);
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
    qDebug() << tr("Erzeuge einen neuen, leeren Datensatz für DeviceType...");

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

void DeviceTypeInputArea::deleteDataset(const QModelIndex &index)
{
    qDebug() << tr("Lösche Daten von DeviceType");
    m_mapper->setCurrentIndex(index.row());
}

void DeviceTypeInputArea::addEdit()
{
    qDebug() << tr("Füge neue Daten zu DeviceType");
    createDataset();
    editFinish();
}

void DeviceTypeInputArea::editFinish()
{
    qDebug() << tr("Bearbeite oder schließe DeviceType Daten");

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
            QString message(tr("Bitte geben sie einen Geräte Type ein."));

            QMessageBox::information(this, tr("Gerätetyp hinzufügen"), message);
        } else {
            m_mapper->submit();
            m_model->database().transaction();
            if (m_model->submitAll()) {
                m_model->database().commit();
                qDebug() << tr("Schreiben der Änderungen für Account in die Datenbank");
                m_model->database().rollback();
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
