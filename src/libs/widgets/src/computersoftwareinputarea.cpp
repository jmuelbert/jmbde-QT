/*
 *  SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "jmbdewidgets/computersoftwareinputarea.h"
#include <ui_computersoftwareinputarea.h>

ComputerSoftwareInputArea::ComputerSoftwareInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::ComputerSoftwareInputArea)
{
    ui->setupUi(this);

    qDebug() << tr("Initialisiere ComputerSoftwareInputArea mit Index :") << index.row();

    this->m_computerSoftwareModel = new Model::ComputerSoftware();
    this->m_db = this->m_computerSoftwareModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_computerSoftwareModel->initializeRelationalModel();

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

    QObject::connect(this->ui->addPushButton, &QPushButton::released, this, &ComputerSoftwareInputArea::addEdit);
    QObject::connect(this->ui->editFinishPushButton, &QPushButton::released, this, &ComputerSoftwareInputArea::editFinish);
}

ComputerSoftwareInputArea::~ComputerSoftwareInputArea()
{
    delete ui;
}

void ComputerSoftwareInputArea::setMappings()
{
    m_mapper->addMapping(ui->computerComboBox, this->m_computerSoftwareModel->getComputerIdIndex());
    m_mapper->addMapping(ui->softwareComboBox, this->m_computerSoftwareModel->getSoftwareIdIndex());
    m_mapper->addMapping(ui->lastUpdateLineEdit, this->m_computerSoftwareModel->getLastUpdateIndex());
}

void ComputerSoftwareInputArea::setViewOnlyMode(bool mode)
{
    // ui->computerComboBox->setDisabled(mode);
    // ui->softwareComboBox->setDisabled(mode);
}

void ComputerSoftwareInputArea::createDataset()
{
    qDebug() << tr("Erzeuge einen neuen, leeren Datensatz für ComputerSoftware...");

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

void ComputerSoftwareInputArea::deleteDataset(const QModelIndex &index)
{
    qDebug() << tr("Lösche Daten von ComputerSoftware");
    m_mapper->setCurrentIndex(index.row());
}
void ComputerSoftwareInputArea::addEdit()
{
    qDebug() << tr("Füge neue Daten zu ComputerSoftware");
    createDataset();
    editFinish();
}

void ComputerSoftwareInputArea::editFinish()
{
    qDebug() << tr("Bearbeite oder schließe ComputerSoftware Daten");
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

        m_mapper->submit();
        m_model->database().transaction();
        if (m_model->submitAll()) {
            m_model->database().commit();
            qDebug() << tr("Schreiben der Änderungen für ComputerSoftware in die Datenbank");
            m_model->database().rollback();
        } else {
            m_model->database().rollback();
            QMessageBox::warning(this, tr("jmbde"), tr("Die Datenbank meldet den Fehler: %1").arg(m_model->lastError().text()));
        }
    } break;

    default: {
        qCritical() << tr("Fehler: Unbekannter Modus");
    }
    }
}
