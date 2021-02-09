/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <ui_employeeaccountinputarea.h>
#include <views/employeeaccountinputarea.h>

using Model::EmployeeAccount;

Q_LOGGING_CATEGORY(jmbdeWidgetsEmployeeAccountInputAreaLog, "jmuelbert.jmbde.widgets.EmployeeAccountinputarea", QtWarningMsg)

EmployeeAccountInputArea::EmployeeAccountInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::EmployeeAccountInputArea)
{
    ui->setupUi(this);

    qCDebug(jmbdeWidgetsEmployeeAccountInputAreaLog) << "Init EmployeeAccountInputArea for Index :" << index.column();

    this->m_employeeAccountModel = new EmployeeAccount();
    this->m_db = this->m_employeeAccountModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_employeeAccountModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);

    setMappings();

    m_mapper->setCurrentIndex(index.row());
}

EmployeeAccountInputArea::~EmployeeAccountInputArea()
{
    delete ui;
}

void EmployeeAccountInputArea::setMappings()
{
    m_mapper->addMapping(ui->employeeComboBox, this->m_employeeAccountModel->getEmployeeIdIndex());
    m_mapper->addMapping(ui->accountComboBox, this->m_employeeAccountModel->getAccountIdIndex());
    m_mapper->addMapping(ui->lastUpdateLineEdit, this->m_employeeAccountModel->getLastUpdateIndex());
}

void EmployeeAccountInputArea::setViewOnlyMode(bool mode)
{
    // ui->employeeComboBox->setDisabled(mode);
    // ui->accountComboBox->setDisabled(mode);
}

void EmployeeAccountInputArea::createDataset()
{
    qCDebug(jmbdeWidgetsEmployeeAccountInputAreaLog) << "Create a new Dataset for ChipCard...";

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

void EmployeeAccountInputArea::retrieveDataset(const QModelIndex index)
{
}

void EmployeeAccountInputArea::updateDataset(const QModelIndex index)
{
}

void EmployeeAccountInputArea::deleteDataset(const QModelIndex index)
{
}

void EmployeeAccountInputArea::on_pushButton_Add_clicked()
{
    createDataset();
    on_pushButton_EditFinish_clicked();
}

void EmployeeAccountInputArea::on_pushButton_EditFinish_clicked()
{
    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->pushButton_EditFinish->setText(tr("Finish"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(jmbdeWidgetsEmployeeAccountInputAreaLog) << "Save Data...";

        m_actualMode = Mode::Edit;
        ui->pushButton_EditFinish->setText(tr("Edit"));
        setViewOnlyMode(false);

        m_mapper->submit();
        m_model->database().transaction();
        if (m_model->submitAll()) {
            m_model->database().commit();
            qCDebug(jmbdeWidgetsEmployeeAccountInputAreaLog) << "Commit changes for Employee Account Table";
            m_model->database().rollback();
        } else {
            m_model->database().rollback();
            QMessageBox::warning(this, tr("jmbde"), tr("The database reported an error: %1").arg(m_model->lastError().text()));
        }

    } break;

    default: {
        qCCritical(jmbdeWidgetsEmployeeAccountInputAreaLog) << "Unknown Mode!";
    }
    }
}
