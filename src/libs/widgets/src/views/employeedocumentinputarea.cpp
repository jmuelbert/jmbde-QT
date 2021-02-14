/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <ui_employeedocumentinputarea.h>
#include <views/employeedocumentinputarea.h>

Q_LOGGING_CATEGORY(jmbdeWidgetsEmployeeDocumentInputAreaLog, "jmuelbert.jmbde.widgets.employeedocumentinputarea", QtWarningMsg)

EmployeeDocumentInputArea::EmployeeDocumentInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::EmployeeDocumentInputArea)
{
    ui->setupUi(this);

    qCDebug(jmbdeWidgetsEmployeeDocumentInputAreaLog) << "Init EmployeeDocumentInputArea for Index :" << index.column();

    this->m_employeeDocumentModel = new Model::EmployeeDocument();
    this->m_db = this->m_employeeDocumentModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_employeeDocumentModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);

    setMappings();

    m_mapper->setCurrentIndex(index.row());
}

EmployeeDocumentInputArea::~EmployeeDocumentInputArea()
{
    delete ui;
}

void EmployeeDocumentInputArea::setMappings()
{
    m_mapper->addMapping(ui->employeeIdcomboBox, this->m_employeeDocumentModel->getEmployeeIdIndex());
    m_mapper->addMapping(ui->documentIdcomboBox, this->m_employeeDocumentModel->getDocumentIdIndex());
    m_mapper->addMapping(ui->lastUpdatelineEdit, this->m_employeeDocumentModel->getLastUpdateIndex());
}

void EmployeeDocumentInputArea::setViewOnlyMode(bool mode)
{
    // ui->employeeIdcomboBox->setDisabled(mode);
    // ui->documentIdcomboBox->setDisabled(mode);
}

void EmployeeDocumentInputArea::createDataset()
{
    qCDebug(jmbdeWidgetsEmployeeDocumentInputAreaLog) << "Create a new Dataset for ChipCard...";

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

void EmployeeDocumentInputArea::retrieveDataset(const QModelIndex index)
{
}

void EmployeeDocumentInputArea::updateDataset(const QModelIndex index)
{
}

void EmployeeDocumentInputArea::deleteDataset(const QModelIndex index)
{
}

void EmployeeDocumentInputArea::on_pushButton_Add_clicked()
{
    createDataset();
    on_pushButton_EditFinish_clicked();
}

void EmployeeDocumentInputArea::on_pushButton_EditFinish_clicked()
{
    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->pushButton_EditFinish->setText(tr("Finish"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(jmbdeWidgetsEmployeeDocumentInputAreaLog) << "Save Data...";

        m_actualMode = Mode::Edit;
        ui->pushButton_EditFinish->setText(tr("Edit"));
        setViewOnlyMode(false);

        m_mapper->submit();
        m_model->database().transaction();
        if (m_model->submitAll()) {
            m_model->database().commit();
            qCDebug(jmbdeWidgetsEmployeeDocumentInputAreaLog) << "Commit changes for Employee Document Table";
            m_model->database().rollback();
        } else {
            m_model->database().rollback();
            QMessageBox::warning(this, tr("jmbde"), tr("The database reported an error: %1").arg(m_model->lastError().text()));
        }

    } break;

    default: {
        qCCritical(jmbdeWidgetsEmployeeDocumentInputAreaLog) << "Unknown Mode!";
    }
    }
}
