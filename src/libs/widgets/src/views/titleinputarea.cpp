/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "views/titleinputarea.h"

#include "models/title.h"
#include "ui_titleinputarea.h"

Q_LOGGING_CATEGORY(jmbdeWidgetsTitleDataInputAreaLog, "jmuelbert.jmbde.widgets.titleinputarea", QtWarningMsg)

TitleInputArea::TitleInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::TitleInputArea)
{
    ui->setupUi(this);

    // Init UI
    qCDebug(jmbdeWidgetsTitleDataInputAreaLog) << "Init TitleInputarea for Index : " << index.row();

    this->m_titleModel = new Model::Title();
    this->m_db = this->m_titleModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_titleModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);

    setMappings();

    m_mapper->setCurrentIndex(index.row());
}

TitleInputArea::~TitleInputArea()
{
    delete ui;
}

void TitleInputArea::setMappings()
{
    m_mapper->addMapping(ui->titleLineEdit, this->m_titleModel->getTitleIdIndex());
    m_mapper->addMapping(ui->fromDateEdit, this->m_titleModel->getFromDateIndex());
    m_mapper->addMapping(ui->toDateEdit, this->m_titleModel->getToDateIndex());
    m_mapper->addMapping(ui->lastUpdateLineEdit, this->m_titleModel->getLastUpdateIndex());
}

void TitleInputArea::setViewOnlyMode(bool mode)
{
    ui->titleLineEdit->setDisabled(mode);
    ui->fromDateEdit->setDisabled(mode);
    ui->toDateEdit->setDisabled(mode);
}

void TitleInputArea::createDataset()
{
    qCDebug(jmbdeWidgetsTitleDataInputAreaLog) << "Create a new Dataset for Title...";

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

void TitleInputArea::retrieveDataset(const QModelIndex index)
{
}

void TitleInputArea::updateDataset(const QModelIndex index)
{
}

void TitleInputArea::deleteDataset(const QModelIndex index)
{
}

void TitleInputArea::on_pushButton_Add_clicked()
{
    createDataset();
    on_pushButton_EditFinish_clicked();
}

void TitleInputArea::on_pushButton_EditFinish_clicked()
{
    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->editFinishPushButton->setText(tr("Fertig"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(jmbdeWidgetsTitleDataInputAreaLog) << tr("Daten speichern...");

        m_actualMode = Mode::Edit;
        ui->editFinishPushButton->setText(tr("Bearbeiten"));
        setViewOnlyMode(false);

        QString name = ui->titleLineEdit->text();

        if (name.isEmpty()) {
            QString message(tr("Bitte geben Sie einen neuen Titel an."));

            QMessageBox::information(this, tr("Titel hinzufügen"), message);
        } else {
            m_mapper->submit();
            m_model->database().transaction();
            if (m_model->submitAll()) {
                m_model->database().commit();
                qCDebug(jmbdeWidgetsTitleDataInputAreaLog) << tr("Änderung an der Tabelle title in der Datenbank");
            } else {
                m_model->database().rollback();
                QMessageBox::warning(this, tr("jmbde"), tr("Die Datenbank meldet einen Fehler: %1").arg(m_model->lastError().text()));
            }
        }
    } break;

    default: {
        qCCritical(jmbdeWidgetsTitleDataInputAreaLog) << "Error";
    }
    }
}
