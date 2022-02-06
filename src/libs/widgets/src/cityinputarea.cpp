/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "views/cityinputarea.h"

#include "ui_cityinputarea.h"

CityInputArea::CityInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::CityInputArea)
    , m_CityInputAreaLog(QLoggingCategory("jmbde.widgts.cityinputarea"))

{
    ui->setupUi(this);

    qCDebug(m_CityInputAreaLog) << "Initiaisiere CityInputArea mit Index : " << index.row();

    this->m_cityNameModel = new Model::CityName();
    this->m_db = this->m_cityNameModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_cityNameModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);
    m_mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    setMappings();

    qCDebug(m_CityInputAreaLog) << tr("Aktueller Index: ") << m_mapper->currentIndex();

    if (index.row() < 0) {
        m_mapper->toFirst();
    } else {
        m_mapper->setCurrentIndex(index.row());
    }

    QObject::connect(this->ui->addPushButton, &QPushButton::released, this, &CityInputArea::addEdit);
    QObject::connect(this->ui->editFinishPushButton, &QPushButton::released, this, &CityInputArea::editFinish);
}

CityInputArea::~CityInputArea()
{
    delete ui;
}

void CityInputArea::setMappings()
{
    m_mapper->addMapping(ui->cityNameLineEdit, this->m_cityNameModel->getNameIndex());
    m_mapper->addMapping(ui->lastUpdateLineEdit, this->m_cityNameModel->getLastUpdateIndex());
}

void CityInputArea::setViewOnlyMode(bool mode)
{
    ui->cityNameLineEdit->setDisabled(mode);
}

void CityInputArea::createDataset()
{
    qCDebug(m_CityInputAreaLog) << tr("Erzeuge einen neuen, leeren Datensatz für City...");

    m_mapper->toLast();

    int row = m_mapper->currentIndex();
    if (row < 0) {
        row = 0;
    }
    m_mapper->submit();
    m_model->insertRow(row);
    m_mapper->setCurrentIndex(row);
}

void CityInputArea::deleteDataset(const QModelIndex &index)
{
    qCDebug(m_CityInputAreaLog) << tr("Lösche Daten von City");
    m_mapper->setCurrentIndex(index.row());
}

void CityInputArea::addEdit()
{
    qCDebug(m_CityInputAreaLog) << tr("Füge neue Daten zu City");
    createDataset();
    editFinish();
}

void CityInputArea::editFinish()
{
    qCDebug(m_CityInputAreaLog) << tr("Bearbeite oder schließe City Daten");

    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->editFinishPushButton->setText(tr("Fertig"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(m_CityInputAreaLog) << tr("Die Daten werden gesichert.");

        m_actualMode = Mode::Edit;
        ui->editFinishPushButton->setText(tr("Bearbeiten"));
        setViewOnlyMode(false);

        QString name = ui->cityNameLineEdit->text();

        if (name.isEmpty()) {
            QString message(tr("Bitte geben sie einen Namen für die Stadt/den Ort an."));

            QMessageBox::information(this, tr("Stadt/Ort hinzufügen"), message);
        } else {
            m_mapper->submit();
            m_model->database().transaction();
            if (m_model->submitAll()) {
                m_model->database().commit();
                qCDebug(m_CityInputAreaLog) << tr("Schreiben der Änderungen für City in die Datenbank");
                dataChanged();
            } else {
                m_model->database().rollback();
                QMessageBox::warning(this, tr("jmbde"), tr("Die Datenbank meldet den Fehler: %1").arg(m_model->lastError().text()));
            }
        }
    } break;

    default: {
        qCCritical(m_CityInputAreaLog) << tr("Fehler: Unbekannter Modus");
    }
    }
}
