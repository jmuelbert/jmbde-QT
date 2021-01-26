/*
    jmbde a BDE Tool for companies
    Copyright (C) 2013-2019  Jürgen Mülbert

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

#include <ui_chipcarddoorinputarea.h>
#include <views/chipcarddoorinputarea.h>

Q_LOGGING_CATEGORY(jmbdeWidgetsChipCardDoorInputAreaLog, "jmuelbert.jmbde.widgets.chipcarddoorinputarea", QtWarningMsg)

ChipCardDoorInputArea::ChipCardDoorInputArea(QWidget* parent, const QModelIndex& index)
    : QGroupBox(parent)
    , ui(new Ui::ChipCardDoorInputArea)
{
    ui->setupUi(this);

    this->m_chipCardDoorModel = new Model::ChipCardDoor();
    this->m_db = this->m_chipCardDoorModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_chipCardDoorModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper(this);
    m_mapper->setModel(m_model);
    setMappings();

    m_mapper->setCurrentIndex(index.row());
}

ChipCardDoorInputArea::~ChipCardDoorInputArea()
{
    delete ui;
}

// TODO change lineEdit to lineEdit_Number
void ChipCardDoorInputArea::setMappings()
{
}

void ChipCardDoorInputArea::setViewOnlyMode(bool mode)
{
}

void ChipCardDoorInputArea::createDataset()
{
    qCDebug(jmbdeWidgetsChipCardDoorInputAreaLog) << "Create a new Dataset for ChipCard...";

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

void ChipCardDoorInputArea::retrieveDataset(const QModelIndex index)
{
}

void ChipCardDoorInputArea::updateDataset(const QModelIndex index)
{
}

void ChipCardDoorInputArea::deleteDataset(const QModelIndex index)
{
}

void ChipCardDoorInputArea::on_pushButton_Add_clicked()
{
    createDataset();
    on_pushButton_EditFinish_clicked();
}

void ChipCardDoorInputArea::on_pushButton_EditFinish_clicked()
{
    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->pushButton_EditFinish->setText(tr("Finish"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(jmbdeWidgetsChipCardDoorInputAreaLog) << "Save Data...";

        m_actualMode = Mode::Edit;
        ui->pushButton_EditFinish->setText(tr("Edit"));
        setViewOnlyMode(false);

        // QString name = ui->lineEdit_Number->text();

        if (true) {
            QString message(tr("Please provide the chipcard number."));

            QMessageBox::information(this, tr("Add City"), message);
        } else {
            m_mapper->submit();
            m_model->database().transaction();
            if (m_model->submitAll()) {
                m_model->database().commit();
                qCDebug(jmbdeWidgetsChipCardDoorInputAreaLog) << "Commit changes for Chipcard Database Table";
                m_model->database().rollback();
            } else {
                m_model->database().rollback();
                QMessageBox::warning(this, tr("jmbde"), tr("The database reported an error: %1").arg(m_model->lastError().text()));
            }
        }
    } break;

    default: {
        qCCritical(jmbdeWidgetsChipCardDoorInputAreaLog) << "Unknown Mode!";
    }
    }
}
