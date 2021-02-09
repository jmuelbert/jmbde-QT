/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <ui_computersoftwareinputarea.h>
#include <views/computersoftwareinputarea.h>

Q_LOGGING_CATEGORY(jmbdeWidgetsComputerSoftwareInputAreaLog, "jmuelbert.jmbde.widgets.chipcardinputarea", QtWarningMsg)

ComputerSoftwareInputArea::ComputerSoftwareInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::ComputerSoftwareInputArea)
{
    ui->setupUi(this);

    qCDebug(jmbdeWidgetsComputerSoftwareInputAreaLog) << "Init ComputerSoftwareInputArea for Index :" << index.column();

    this->m_computerSoftwareModel = new Model::ComputerSoftware();
    this->m_db = this->m_computerSoftwareModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_computerSoftwareModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);

    setMappings();

    m_mapper->setCurrentIndex(index.row());
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
    qCDebug(jmbdeWidgetsComputerSoftwareInputAreaLog) << "Create a new Dataset for ChipCard...";

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

void ComputerSoftwareInputArea::retrieveDataset(const QModelIndex index)
{
}

void ComputerSoftwareInputArea::updateDataset(const QModelIndex index)
{
}

void ComputerSoftwareInputArea::deleteDataset(const QModelIndex index)
{
}

void ComputerSoftwareInputArea::on_pushButton_Add_clicked()
{
    createDataset();
    on_pushButton_EditFinish_clicked();
}

void ComputerSoftwareInputArea::on_pushButton_EditFinish_clicked()
{
    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->pushButton_EditFinish->setText(tr("Finish"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(jmbdeWidgetsComputerSoftwareInputAreaLog) << "Save Data...";

        m_actualMode = Mode::Edit;
        ui->pushButton_EditFinish->setText(tr("Edit"));
        setViewOnlyMode(false);

        m_mapper->submit();
        m_model->database().transaction();
        if (m_model->submitAll()) {
            m_model->database().commit();
            qCDebug(jmbdeWidgetsComputerSoftwareInputAreaLog) << "Commit changes for Chipcard Database Table";
            m_model->database().rollback();
        } else {
            m_model->database().rollback();
            QMessageBox::warning(this, tr("jmbde"), tr("The database reported an error: %1").arg(m_model->lastError().text()));
        }

    } break;

    default: {
        qCCritical(jmbdeWidgetsComputerSoftwareInputAreaLog) << "Unknown Mode!";
    }
    }
}
