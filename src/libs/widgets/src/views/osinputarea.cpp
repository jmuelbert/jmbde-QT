/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "views/osinputarea.h"

#include "models/os.h"
#include "ui_osinputarea.h"

Q_LOGGING_CATEGORY(jmbdeWidgetsOsInputAreaLog, "jmuelbert.jmbde.widgets.osinputarea", QtWarningMsg);

OSInputArea::OSInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::OSInputArea)
{
    ui->setupUi(this);

    // Init UI
    qCDebug(jmbdeWidgetsOsInputAreaLog) << "Init OSInputarea for Index : " << index.row();

    this->m_osModel = new Model::OS();
    this->m_db = this->m_osModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_osModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);

    setMappings();

    m_mapper->setCurrentIndex(index.row());
}

OSInputArea::~OSInputArea()
{
    delete ui;
}

void OSInputArea::setMappings()
{
    m_mapper->addMapping(ui->nameLineEdit, this->m_osModel->getNameIndex());
    m_mapper->addMapping(ui->versionLineEdit, this->m_osModel->getVersionIndex());
    m_mapper->addMapping(ui->revisionLineEdit, this->m_osModel->getRevisionIndex());
    m_mapper->addMapping(ui->fixLineEdit, this->m_osModel->getFixIndex());
    m_mapper->addMapping(ui->lastUpdateLineEdit, this->m_osModel->getLastUpdateIndex());
}

void OSInputArea::setViewOnlyMode(bool mode)
{
    ui->nameLineEdit->setDisabled(mode);
    ui->versionLineEdit->setDisabled(mode);
    ui->revisionLineEdit->setDisabled(mode);
    ui->fixLineEdit->setDisabled(mode);
}

void OSInputArea::createDataset()
{
    qCDebug(jmbdeWidgetsOsInputAreaLog) << "Create a new Dataset for Operation System...";

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

void OSInputArea::retrieveDataset(const QModelIndex index)
{
}

void OSInputArea::updateDataset(const QModelIndex index)
{
}

void OSInputArea::deleteDataset(const QModelIndex index)
{
}

void OSInputArea::on_pushButton_Add_clicked()
{
    createDataset();
    on_pushButton_EditFinish_clicked();
}

void OSInputArea::on_pushButton_EditFinish_clicked()
{
    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->editFinishPushButton->setText(tr("Fertig"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(jmbdeWidgetsOsInputAreaLog) << tr("Daten speichern...");

        m_actualMode = Mode::Edit;
        ui->editFinishPushButton->setText(tr("Bearbeiten"));
        setViewOnlyMode(false);

        QString name = ui->nameLineEdit->text();

        if (name.isEmpty()) {
            QString message(tr("Bitte geben Sie den Namen des Betriebssystems an."));

            QMessageBox::information(this, tr("Betriebssystem hinzufügen"), message);
        } else {
            m_mapper->submit();
            m_model->database().transaction();
            if (m_model->submitAll()) {
                m_model->database().commit();
                qCDebug(jmbdeWidgetsOsInputAreaLog) << tr("Änderung an der Tabelle os in der Datenbank");
            } else {
                m_model->database().rollback();
                QMessageBox::warning(this, tr("jmbde"), tr("Die Datenbank meldet einen Fehler: %1").arg(m_model->lastError().text()));
            }
        }
    } break;

    default: {
        qCCritical(jmbdeWidgetsOsInputAreaLog) << tr("Fehler");
    }
    }
}
