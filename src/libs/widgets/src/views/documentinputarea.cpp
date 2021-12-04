/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <ui_documentinputarea.h>
#include <views/documentinputarea.h>

DocumentInputArea::DocumentInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::DocumentInputArea)
    , m_DocumentInputAreaLog(QLoggingCategory("jmbde.widgets.documentinputarea"))
{
    ui->setupUi(this);

    qCDebug(m_DocumentInputAreaLog) << tr("Initialisiere DocumentInputArea mit Index :") << index.row();

    this->m_documentModel = new Model::Document();
    this->m_db = this->m_documentModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_documentModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);
    m_mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    setMappings();

    qCDebug(m_DocumentInputAreaLog) << tr("Aktueller Index: ") << m_mapper->currentIndex();

    if (index.row() < 0) {
        m_mapper->toFirst();
    } else {
        m_mapper->setCurrentIndex(index.row());
    }

    QObject::connect(this->ui->addPushButton, &QPushButton::released, this, &DocumentInputArea::addEdit);
    QObject::connect(this->ui->editFinishPushButton, &QPushButton::released, this, &DocumentInputArea::editFinish);
}

DocumentInputArea::~DocumentInputArea()
{
    delete ui;
}

void DocumentInputArea::setMappings()
{
    m_mapper->addMapping(ui->nameLineEdit, this->m_documentModel->getNameIndex());
    m_mapper->addMapping(ui->lastUpdateLineEdit, this->m_documentModel->getLastUpdateIndex());
}

void DocumentInputArea::setViewOnlyMode(bool mode)
{
    ui->nameLineEdit->setDisabled(mode);
    ui->documentAddPushButton->setDisabled(mode);
}

void DocumentInputArea::createDataset()
{
    qCDebug(m_DocumentInputAreaLog) << tr("Erzeuge einen neuen, leeren Datensatz für Document...");

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

void DocumentInputArea::deleteDataset(const QModelIndex &index)
{
    qCDebug(m_DocumentInputAreaLog) << tr("Lösche Daten von Document");
    m_mapper->setCurrentIndex(index.row());
}

void DocumentInputArea::addEdit()
{
    qCDebug(m_DocumentInputAreaLog) << tr("Füge neue Daten zu Document");
    createDataset();
    editFinish();
}

void DocumentInputArea::editFinish()
{
    qCDebug(m_DocumentInputAreaLog) << tr("Bearbeite oder schließe Document Daten");

    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->editFinishPushButton->setText(tr("Fertig"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(m_DocumentInputAreaLog) << tr("Die Daten werden gesichert.");

        m_actualMode = Mode::Edit;
        ui->editFinishPushButton->setText(tr("Bearbeiten"));
        setViewOnlyMode(false);

        QString name = ui->nameLineEdit->text();

        if (name.isEmpty()) {
            QString message(tr("Bitte geben sie eine Dokumenten Bezeichnung ein."));

            QMessageBox::information(this, tr("Dokument hinzufügen"), message);
        } else {
            m_mapper->submit();
            m_model->database().transaction();
            if (m_model->submitAll()) {
                m_model->database().commit();
                qCDebug(m_DocumentInputAreaLog) << tr("Schreiben der Änderungen für Document in die Datenbank");
                m_model->database().rollback();
            } else {
                m_model->database().rollback();
                QMessageBox::warning(this, tr("jmbde"), tr("Die Datenbank meldet den Fehler: %1").arg(m_model->lastError().text()));
            }
        }
        break;
    }
    default: {
        qCCritical(m_DocumentInputAreaLog) << tr("Fehler: Unbekannter Modus");
    }
    }
}
