/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <ui_softwareinputarea.h>
#include <views/softwareinputarea.h>

SoftwareInputArea::SoftwareInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::SoftwareInputArea)
    , m_SoftwareInputAreaLog(QLoggingCategory("jmbde.widgets.softwareinputarea"))

{
    ui->setupUi(this);

    qCDebug(m_SoftwareInputAreaLog) << tr("Initialisiere SoftwareInputArea mit Index :") << index.row();

    this->m_softwareModel = new Model::Software();
    this->m_db = this->m_softwareModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_softwareModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);
    m_mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    setMappings();

    qCDebug(m_SoftwareInputAreaLog) << tr("Aktueller Index: ") << m_mapper->currentIndex();

    if (index.row() < 0) {
        m_mapper->toFirst();
    } else {
        m_mapper->setCurrentIndex(index.row());
    }

    QObject::connect(this->ui->addPushButton, &QPushButton::released, this, &SoftwareInputArea::addEdit);
    QObject::connect(this->ui->editFinishPushButton, &QPushButton::released, this, &SoftwareInputArea::editFinish);
}

SoftwareInputArea::~SoftwareInputArea()
{
    delete ui;
}

void SoftwareInputArea::setMappings()
{
    m_mapper->addMapping(ui->nameLineEdit, this->m_softwareModel->getNameIndex());
    m_mapper->addMapping(ui->versionLineEdit, this->m_softwareModel->getVersionIndex());
    m_mapper->addMapping(ui->revisionLineEdit, this->m_softwareModel->getRevisionIndex());
    m_mapper->addMapping(ui->fixLineEdit, this->m_softwareModel->getFixIndex());
    m_mapper->addMapping(ui->lastUpdateLineEdit, this->m_softwareModel->getLastUpdateIndex());
}

void SoftwareInputArea::setViewOnlyMode(bool mode)
{
    ui->nameLineEdit->setDisabled(mode);
    ui->versionLineEdit->setDisabled(mode);
    ui->revisionLineEdit->setDisabled(mode);
    ui->fixLineEdit->setDisabled(mode);
}

void SoftwareInputArea::createDataset()
{
    qCDebug(m_SoftwareInputAreaLog) << tr("Erzeuge einen neuen, leeren Datensatz für Software...");

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

void SoftwareInputArea::deleteDataset(const QModelIndex &index)
{
    qCDebug(m_SoftwareInputAreaLog) << tr("Lösche Daten von Software");
    m_mapper->setCurrentIndex(index.row());
}

void SoftwareInputArea::addEdit()
{
    qCDebug(m_SoftwareInputAreaLog) << tr("Füge neue Daten zu Software");
    createDataset();
    editFinish();
}

void SoftwareInputArea::editFinish()
{
    qCDebug(m_SoftwareInputAreaLog) << tr("Bearbeite oder schließe Software Daten");

    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->editFinishPushButton->setText(tr("Fertig"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(m_SoftwareInputAreaLog) << tr("Die Daten werden gesichert.");

        m_actualMode = Mode::Edit;
        ui->editFinishPushButton->setText(tr("Bearbeiten"));
        setViewOnlyMode(false);

        QString name = ui->nameLineEdit->text();

        if (name.isEmpty()) {
            QString message(tr("PBitte Namen eingeben."));

            QMessageBox::information(this, tr("Software hinzufügen."), message);
        } else {
            m_mapper->submit();
            m_model->database().transaction();
            if (m_model->submitAll()) {
                m_model->database().commit();
                qCDebug(m_SoftwareInputAreaLog) << tr("Schreiben der Änderungen für Software in die Datenbank");
                dataChanged();
            } else {
                m_model->database().rollback();
                QMessageBox::warning(this, tr("jmbde"), tr("Die Datenbank meldet den Fehler: %1").arg(m_model->lastError().text()));
            }
        }
    } break;

    default: {
        qCCritical(m_SoftwareInputAreaLog) << tr("Fehler: Unbekannter Modus");
    }
    }
}
