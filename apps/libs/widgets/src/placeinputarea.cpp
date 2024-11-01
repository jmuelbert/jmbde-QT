/*
 *  SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "jmbdewidgets/placeinputarea.h"
#include <ui_placeinputarea.h>

PlaceInputArea::PlaceInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::PlaceInputArea)
{
    ui->setupUi(this);

    qDebug() << tr("Initialisiere PlaceInputArea mit Index :") << index.row();

    this->m_placeModel = new Model::Place();
    this->m_db = this->m_placeModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_placeModel->initializeRelationalModel();

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

    QObject::connect(this->ui->addPushButton, &QPushButton::released, this, &PlaceInputArea::addEdit);
    QObject::connect(this->ui->editFinishPushButton, &QPushButton::released, this, &PlaceInputArea::editFinish);
}

PlaceInputArea::~PlaceInputArea()
{
    delete ui;
}

void PlaceInputArea::setMappings()
{
    m_mapper->addMapping(ui->nameLineEdit, this->m_placeModel->getNameIndex());
    m_mapper->addMapping(ui->roomLineEdit, this->m_placeModel->getRoomIndex());
    m_mapper->addMapping(ui->deskLineEdit, this->m_placeModel->getDeskIndex());
    m_mapper->addMapping(ui->lastUpdateLineEdit, this->m_placeModel->getLastUpdateIndex());
}

void PlaceInputArea::setViewOnlyMode(bool mode)
{
    ui->nameLineEdit->setDisabled(mode);
    ui->roomLineEdit->setDisabled(mode);
    ui->deskLineEdit->setDisabled(mode);
}

void PlaceInputArea::createDataset()
{
    qDebug() << tr("Erzeuge einen neuen, leeren Datensatz für Place...");

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

void PlaceInputArea::deleteDataset(const QModelIndex &index)
{
    qDebug() << tr("Lösche Daten von Place");
    m_mapper->setCurrentIndex(index.row());
}

void PlaceInputArea::addEdit()
{
    qDebug() << tr("Füge neue Daten zu Place");
    createDataset();
    editFinish();
}

void PlaceInputArea::editFinish()
{
    qDebug() << tr("Bearbeite oder schließe Place Daten");

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

            QMessageBox::information(this, tr("Füge Platz hinzu"), message);
        } else {
            m_mapper->submit();
            m_model->database().transaction();
            if (m_model->submitAll()) {
                m_model->database().commit();
                qDebug() << tr("Schreiben der Änderungen für Account in die Datenbank");
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
