/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <ui_documentinputarea.h>
#include <views/documentinputarea.h>

Q_LOGGING_CATEGORY(jmbdeWidgetsDocumentInputAreaLog, "jmuelbert.jmbde.widgets.documentinputarea", QtWarningMsg)

DocumentInputArea::DocumentInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::DocumentInputArea)
{
    ui->setupUi(this);

    qCDebug(jmbdeWidgetsDocumentInputAreaLog) << "Init DocumentInputArea for Index :" << index.column();

    this->m_documentModel = new Model::Document();
    this->m_db = this->m_documentModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_documentModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);

    setMappings();

    m_mapper->setCurrentIndex(index.row());
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
    qCDebug(jmbdeWidgetsDocumentInputAreaLog) << "Create a new Dataset for ChipCard...";

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

void DocumentInputArea::retrieveDataset(const QModelIndex index)
{
}

void DocumentInputArea::updateDataset(const QModelIndex index)
{
}

void DocumentInputArea::deleteDataset(const QModelIndex index)
{
}

void DocumentInputArea::on_pushButton_Add_clicked()
{
    createDataset();
    on_pushButton_EditFinish_clicked();
}

void DocumentInputArea::on_pushButton_EditFinish_clicked()
{
    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->pushButton_EditFinish->setText(tr("Finish"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(jmbdeWidgetsDocumentInputAreaLog) << "Save Data...";

        m_actualMode = Mode::Edit;
        ui->pushButton_EditFinish->setText(tr("Edit"));
        setViewOnlyMode(false);

        m_mapper->submit();
        m_model->database().transaction();
        if (m_model->submitAll()) {
            m_model->database().commit();
            qCDebug(jmbdeWidgetsDocumentInputAreaLog) << "Commit changes for Document Database Table";
            m_model->database().rollback();
        } else {
            m_model->database().rollback();
            QMessageBox::warning(this, tr("jmbde"), tr("The database reported an error: %1").arg(m_model->lastError().text()));
        }
    } break;

    default: {
        qCCritical(jmbdeWidgetsDocumentInputAreaLog) << "Unknown Mode!";
    }
    }
}
