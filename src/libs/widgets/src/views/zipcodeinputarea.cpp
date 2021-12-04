/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <ui_zipcodeinputarea.h>
#include <views/zipcodeinputarea.h>

ZipCodeInputArea::ZipCodeInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::ZipCodeInputArea)
    , m_ZipCodeInputAreaLog(QLoggingCategory("jmbde.widgets.zipcodeinputarea"))

{
    ui->setupUi(this);

    qCDebug(m_ZipCodeInputAreaLog) << tr("Initialisiere ZipCodeInputArea mit Index :") << index.row();

    this->m_zipCodeModel = new Model::ZipCode();
    this->m_db = this->m_zipCodeModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_zipCodeModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);
    m_mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    setMappings();

    qCDebug(m_ZipCodeInputAreaLog) << tr("Aktueller Index: ") << m_mapper->currentIndex();

    if (index.row() < 0) {
        m_mapper->toFirst();
    } else {
        m_mapper->setCurrentIndex(index.row());
    }

    QObject::connect(this->ui->addPushButton, &QPushButton::released, this, &ZipCodeInputArea::addEdit);
    QObject::connect(this->ui->editFinishPushButton, &QPushButton::released, this, &ZipCodeInputArea::editFinish);
}

ZipCodeInputArea::~ZipCodeInputArea()
{
    delete ui;
}

void ZipCodeInputArea::setMappings()
{
    m_mapper->addMapping(ui->codeLineEdit, this->m_zipCodeModel->getCodeIndex());
    m_mapper->addMapping(ui->lastUpdateLineEdit, this->m_zipCodeModel->getLastUpdateIndex());
}

void ZipCodeInputArea::setViewOnlyMode(bool mode)
{
    ui->codeLineEdit->setDisabled(mode);
}

void ZipCodeInputArea::createDataset()
{
    qCDebug(m_ZipCodeInputAreaLog) << tr("Erzeuge einen neuen, leeren Datensatz für ZipCodeInput...");

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

void ZipCodeInputArea::deleteDataset(const QModelIndex &index)
{
    qCDebug(m_ZipCodeInputAreaLog) << tr("Lösche Daten von ZipCodeInput");
    m_mapper->setCurrentIndex(index.row());
}

void ZipCodeInputArea::addEdit()
{
    qCDebug(m_ZipCodeInputAreaLog) << tr("Füge neue Daten zu ZipCodeInput");
    createDataset();
    editFinish();
}

void ZipCodeInputArea::editFinish()
{
    qCDebug(m_ZipCodeInputAreaLog) << tr("Bearbeite oder schließe ZipCodeInput Daten");

    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->editFinishPushButton->setText(tr("Fertig"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(m_ZipCodeInputAreaLog) << tr("Die Daten werden gesichert.");

        m_actualMode = Mode::Edit;
        ui->editFinishPushButton->setText(tr("Bearbeiten"));
        setViewOnlyMode(false);

        QString name = ui->codeLineEdit->text();

        if (name.isEmpty()) {
            QString message(tr("Bitte geben Sie den Namen des Betriebssystems an."));

            QMessageBox::information(this, tr("Füge PLZ hinzu"), message);
        } else {
            m_mapper->submit();
            m_model->database().transaction();
            if (m_model->submitAll()) {
                m_model->database().commit();
                qCDebug(m_ZipCodeInputAreaLog) << tr("Schreiben der Änderungen für Account in die Datenbank");
                dataChanged();
            } else {
                m_model->database().rollback();
                QMessageBox::warning(this, tr("jmbde"), tr("Die Datenbank meldet den Fehler: %1").arg(m_model->lastError().text()));
            }
        }
    } break;

    default: {
        qCCritical(m_ZipCodeInputAreaLog) << tr("Fehler: Unbekannter Modus");
    }
    }
}
