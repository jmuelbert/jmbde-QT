/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "ui_zipcityinputarea.h"
#include "views/zipcitiyinputarea.h"

ZipCityInputArea::ZipCityInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::ZipCityInputArea)
{
    ui->setupUi(this);

    qCDebug(jmbdeWidgetsZipCityInputAreaLog) << tr("Initialisiere ZipCityInputArea mit Index :") << index.row();

    this->m_zipCityModel = new Model::ZipCity();
    this->m_db = this->m_zipCityModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_zipCityModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);
    m_mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    setMappings();

    qCDebug(jmbdeWidgetsZipCityInputAreaLog) << tr("Aktueller Index: ") << m_mapper->currentIndex();

    if (index.row() < 0) {
        m_mapper->toFirst();
    } else {
        m_mapper->setCurrentIndex(index.row());
    }

    QObject::connect(this->ui->addPushButton, &QPushButton::released, this, &ZipCityInputArea::addEdit);
    QObject::connect(this->ui->editFinishPushButton, &QPushButton::released, this, &ZipCityInputArea::editFinish);
}

ZipCityInputArea::~ZipCityInputArea()
{
    delete ui;
}

void ZipCityInputArea::setMappings()
{
    m_mapper->addMapping(ui->cityComboBox, this->m_zipCityModel->getCityIdIndex());
    m_mapper->addMapping(ui->lastUpdateLineEdit, this->m_zipCityModel->getLastUpdateIndex());
    m_mapper->addMapping(ui->zipCodeComboBox, this->m_zipCityModel->getZipCityIdIndex());
}

void ZipCityInputArea::setViewOnlyMode(bool mode)
{
    // ui->cityComboBox->setDisabled(mode);
    // ui->zipCodeComboBox->setDisabled(mode);
}

void ZipCityInputArea::createDataset()
{
    qCDebug(jmbdeWidgetsZipCityInputAreaLog) << tr("Erzeuge einen neuen, leeren Datensatz für ZipCityInputArea...");

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

void ZipCityInputArea::deleteDataset(const QModelIndex &index)
{
    qCDebug(jmbdeWidgetsZipCityInputAreaLog) << tr("Lösche Daten von ZipCityInputArea");
    m_mapper->setCurrentIndex(index.row());
}

void ZipCityInputArea::addEdit()
{
    qCDebug(jmbdeWidgetsZipCityInputAreaLog) << tr("Füge neue Daten zu ZipCityInputArea");
    createDataset();
    editFinish();
}

void ZipCityInputArea::editFinish()
{
    qCDebug(jmbdeWidgetsZipCityInputAreaLog) << tr("Bearbeite oder schließe ZipCityInputArea Daten");

    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->editFinishPushButton->setText(tr("Fertig"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(jmbdeWidgetsZipCityInputAreaLog) << tr("Die Daten werden gesichert.");

        m_actualMode = Mode::Edit;
        ui->editFinishPushButton->setText(tr("Bearbeiten"));
        setViewOnlyMode(false);

        m_mapper->submit();
        m_model->database().transaction();
        if (m_model->submitAll()) {
            m_model->database().commit();
            qCDebug(jmbdeWidgetsZipCityInputAreaLog) << tr("Schreiben der Änderungen für Account in die Datenbank");
            dataChanged();
        } else {
            m_model->database().rollback();
            QMessageBox::warning(this, tr("jmbde"), tr("Die Datenbank meldet den Fehler: %1").arg(m_model->lastError().text()));
        }

    } break;

    default: {
        qCCritical(jmbdeWidgetsZipCityInputAreaLog) << tr("Fehler: Unbekannter Modus");
    }
    }
}
