/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <ui_chipcarddoorinputarea.h>
#include <views/chipcarddoorinputarea.h>

Q_LOGGING_CATEGORY(jmbdeWidgetsChipCardDoorInputAreaLog, "jmuelbert.jmbde.widgets.chipcarddoorinputarea", QtWarningMsg)

ChipCardDoorInputArea::ChipCardDoorInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::ChipCardDoorInputArea)
{
    ui->setupUi(this);

    qCDebug(jmbdeWidgetsChipCardDoorInputAreaLog) << "Init EmployeeInputArea for Index :" << index.column();

    this->m_chipCardDoorModel = new Model::ChipCardDoor();
    this->m_db = this->m_chipCardDoorModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_chipCardDoorModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);

    setMappings();

    m_mapper->setCurrentIndex(index.row());
}

ChipCardDoorInputArea::~ChipCardDoorInputArea()
{
    delete ui;
}

void ChipCardDoorInputArea::setMappings()
{
    m_mapper->addMapping(ui->numberSpinBox, this->m_chipCardDoorModel->getNumberIndex());
    m_mapper->addMapping(ui->placeComboBox, this->m_chipCardDoorModel->getPlaceIdIndex());
    m_mapper->addMapping(ui->departmentComboBox, this->m_chipCardDoorModel->getDepartmentIdIndex());
    m_mapper->addMapping(ui->employeeComboBox, this->m_chipCardDoorModel->getEmployeeIdIndex());
    m_mapper->addMapping(ui->lastUpdateLineEdit, this->m_chipCardDoorModel->getLastUpdateIndex());
}

void ChipCardDoorInputArea::setViewOnlyMode(bool mode)
{
    ui->numberSpinBox->setDisabled(mode);
    // ui->placeComboBox->setDisabled(mode);
    // ui->deparmentComboBox->setDisabled(mode);
    // ui->employeeComboBox->setDisabled(mode);
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
