/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <ui_chipcardprofileinputarea.h>
#include <views/chipcardprofileinputarea.h>

Q_LOGGING_CATEGORY(jmbdeWidgetsChipCardProfileInputAreaLog, "jmuelbert.jmbde.widgets.chipcardinputarea", QtWarningMsg)

ChipCardProfileInputArea::ChipCardProfileInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::ChipCardProfileInputArea)
{
    ui->setupUi(this);

    qCDebug(jmbdeWidgetsChipCardProfileInputAreaLog) << "Init ChipCardProfileInputArea for Index :" << index.column();

    this->m_chipCardProfileModel = new Model::ChipCardProfile();
    this->m_db = this->m_chipCardProfileModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_chipCardProfileModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);

    setMappings();

    m_mapper->setCurrentIndex(index.row());
}

ChipCardProfileInputArea::~ChipCardProfileInputArea()
{
    delete ui;
}

void ChipCardProfileInputArea::setMappings()
{
    m_mapper->addMapping(ui->numberLineEdit, this->m_chipCardProfileModel->getNumberIndex());
    m_mapper->addMapping(ui->doorComboBox, this->m_chipCardProfileModel->getChipCardDoorIdIndex());
    m_mapper->addMapping(ui->employeeComboBox, this->m_chipCardProfileModel->getEmployeeIdIndex());
    m_mapper->addMapping(ui->lastUpdateLineEdit, this->m_chipCardProfileModel->getLastUpdateIndex());
}

void ChipCardProfileInputArea::setViewOnlyMode(bool mode)
{
    ui->numberLineEdit->setDisabled(mode);
    // ui->doorComboBox->setDisabled(mode);
    // ui->employeeComboBox->setDisabled(mode);
}

void ChipCardProfileInputArea::createDataset()
{
    qCDebug(jmbdeWidgetsChipCardProfileInputAreaLog) << "Create a new Dataset for ChipCard...";

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

void ChipCardProfileInputArea::retrieveDataset(const QModelIndex index)
{
}

void ChipCardProfileInputArea::updateDataset(const QModelIndex index)
{
}

void ChipCardProfileInputArea::deleteDataset(const QModelIndex index)
{
}

void ChipCardProfileInputArea::on_pushButton_Add_clicked()
{
    createDataset();
    on_pushButton_EditFinish_clicked();
}

void ChipCardProfileInputArea::on_pushButton_EditFinish_clicked()
{
    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->pushButton_EditFinish->setText(tr("Finish"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(jmbdeWidgetsChipCardProfileInputAreaLog) << "Save Data...";

        m_actualMode = Mode::Edit;
        ui->pushButton_EditFinish->setText(tr("Edit"));
        setViewOnlyMode(false);

        m_mapper->submit();
        m_model->database().transaction();
        if (m_model->submitAll()) {
            m_model->database().commit();
            qCDebug(jmbdeWidgetsChipCardProfileInputAreaLog) << "Commit changes for Chipcard Database Table";
            m_model->database().rollback();
        } else {
            m_model->database().rollback();
            QMessageBox::warning(this, tr("jmbde"), tr("The database reported an error: %1").arg(m_model->lastError().text()));
        }

    } break;

    default: {
        qCCritical(jmbdeWidgetsChipCardProfileInputAreaLog) << "Unknown Mode!";
    }
    }
}
