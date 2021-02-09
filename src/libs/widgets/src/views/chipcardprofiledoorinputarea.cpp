/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <ui_chipcardprofiledoorinputarea.h>
#include <views/chipcardprofiledoorinputarea.h>

Q_LOGGING_CATEGORY(jmbdeWidgetsChipCardProfileDoorInputAreaLog, "jmuelbert.jmbde.widgets.ChipCardProfileDoorInputArea", QtWarningMsg)

ChipCardProfileDoorInputArea::ChipCardProfileDoorInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::ChipCardProfileDoorInputArea)
{
    ui->setupUi(this);

    qCDebug(jmbdeWidgetsChipCardProfileDoorInputAreaLog) << "Init ChipCardProfileDoorInputArea for Index :" << index.column();

    this->m_chipCardProfileDoorModel = new Model::ChipCardProfileDoor();
    this->m_db = this->m_chipCardProfileDoorModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_chipCardProfileDoorModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);

    setMappings();

    m_mapper->setCurrentIndex(index.row());
}

ChipCardProfileDoorInputArea::~ChipCardProfileDoorInputArea()
{
    delete ui;
}

// TODO change lineEdit to lineEdit_Number
void ChipCardProfileDoorInputArea::setMappings()
{
    m_mapper->addMapping(ui->doorComboBox, this->m_chipCardProfileDoorModel->getChipCardDoorsIdIndex());
    m_mapper->addMapping(ui->profileComboBox, this->m_chipCardProfileDoorModel->getChipCardProfileIdIndex());
    m_mapper->addMapping(ui->lastUpdateLineEdit, this->m_chipCardProfileDoorModel->getLastUpdateIndex());
}

void ChipCardProfileDoorInputArea::setViewOnlyMode(bool mode)
{
    // ui->doorComboBox->setDisabled(mode);
    // ui->profileComboBox->setDisabled(mode);
}

void ChipCardProfileDoorInputArea::createDataset()
{
    qCDebug(jmbdeWidgetsChipCardProfileDoorInputAreaLog) << "Create a new Dataset for ChipCard...";

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

void ChipCardProfileDoorInputArea::retrieveDataset(const QModelIndex index)
{
}

void ChipCardProfileDoorInputArea::updateDataset(const QModelIndex index)
{
}

void ChipCardProfileDoorInputArea::deleteDataset(const QModelIndex index)
{
}

void ChipCardProfileDoorInputArea::on_pushButton_Add_clicked()
{
    createDataset();
    on_pushButton_EditFinish_clicked();
}

void ChipCardProfileDoorInputArea::on_pushButton_EditFinish_clicked()
{
    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->pushButton_EditFinish->setText(tr("Finish"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(jmbdeWidgetsChipCardProfileDoorInputAreaLog) << "Save Data...";

        m_actualMode = Mode::Edit;
        ui->pushButton_EditFinish->setText(tr("Edit"));
        setViewOnlyMode(false);

        m_mapper->submit();
        m_model->database().transaction();
        if (m_model->submitAll()) {
            m_model->database().commit();
            qCDebug(jmbdeWidgetsChipCardProfileDoorInputAreaLog) << "Commit changes for Chipcard Database Table";
            m_model->database().rollback();
        } else {
            m_model->database().rollback();
            QMessageBox::warning(this, tr("jmbde"), tr("The database reported an error: %1").arg(m_model->lastError().text()));
        }
    } break;

    default: {
        qCCritical(jmbdeWidgetsChipCardProfileDoorInputAreaLog) << "Unknown Mode!";
    }
    }
}
