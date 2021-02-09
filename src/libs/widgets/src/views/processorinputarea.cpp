/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "views/processorinputarea.h"

#include "models/processor.h"
#include "ui_processorinputarea.h"

Q_LOGGING_CATEGORY(jmbdeWidgetsProcessorInputAreaLog, "jmuelbert.jmbde.widgets.processorinputarea", QtWarningMsg);

ProcessorInputArea::ProcessorInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::ProcessorInputArea)
{
    ui->setupUi(this);

    // Init UI
    qCDebug(jmbdeWidgetsProcessorInputAreaLog) << "Init ProcessorInputarea for Index : " << index.row();

    this->m_processorModel = new Model::Processor();
    this->m_db = this->m_processorModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_processorModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);

    setMappings();

    m_mapper->setCurrentIndex(index.row());
}

ProcessorInputArea::~ProcessorInputArea()
{
    delete ui;
}

void ProcessorInputArea::setMappings()
{
    m_mapper->addMapping(ui->nameLineEdit, this->m_processorModel->getNameIndex());
    m_mapper->addMapping(ui->clockRateDoubleSpinBox, this->m_processorModel->getClockRateIndex());
    m_mapper->addMapping(ui->coresSpinBox, this->m_processorModel->getCoresIndex());
    m_mapper->addMapping(ui->lastUpdateLineEdit, this->m_processorModel->getLastUpdateIndex());
}

void ProcessorInputArea::setViewOnlyMode(bool mode)
{
    ui->nameLineEdit->setDisabled(mode);
    ui->clockRateDoubleSpinBox->setDisabled(mode);
    ui->coresSpinBox->setDisabled(mode);
}

void ProcessorInputArea::createDataset()
{
    qCDebug(jmbdeWidgetsProcessorInputAreaLog) << "Create a new Dataset for Processor...";

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

void ProcessorInputArea::retrieveDataset(const QModelIndex index)
{
}

void ProcessorInputArea::updateDataset(const QModelIndex index)
{
}

void ProcessorInputArea::deleteDataset(const QModelIndex index)
{
}

void ProcessorInputArea::on_pushButton_Add_clicked()
{
    createDataset();
    on_pushButton_EditFinish_clicked();
}

void ProcessorInputArea::on_pushButton_EditFinish_clicked()
{
    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->editFinishPushButton->setText(tr("Fertig"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(jmbdeWidgetsProcessorInputAreaLog) << tr("Speichere Daten...");

        m_actualMode = Mode::Edit;
        ui->editFinishPushButton->setText(tr("Bearbeiten"));
        setViewOnlyMode(false);

        QString name = ui->nameLineEdit->text();

        if (name.isEmpty()) {
            QString message(tr("Bitte einen Name für den Prozessor angeben"));

            QMessageBox::information(this, tr("Prozessor hinzufügen"), message);
        } else {
            m_mapper->submit();
            m_model->database().transaction();
            if (m_model->submitAll()) {
                m_model->database().commit();
                qCDebug(jmbdeWidgetsProcessorInputAreaLog) << tr("Änderung an der Tabelle Prozessor in der Datenbank");
            } else {
                m_model->database().rollback();
                QMessageBox::warning(this, tr("jmbde"), tr("Die Datenbank meldet einen Fehler: %1").arg(m_model->lastError().text()));
            }
        }
    } break;

    default: {
        qCCritical(jmbdeWidgetsProcessorInputAreaLog) << "Error";
    }
    }
}
