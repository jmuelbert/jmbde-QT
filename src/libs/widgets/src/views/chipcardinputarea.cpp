/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <ui_chipcardinputarea.h>
#include <views/chipcardinputarea.h>

Q_LOGGING_CATEGORY(jmbdeWidgetsChipCardInputAreaLog, "jmuelbert.jmbde.widgets.chipcardinputarea", QtWarningMsg)

ChipCardInputArea::ChipCardInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::ChipCardInputArea)
{
    ui->setupUi(this);

    qCDebug(jmbdeWidgetsChipCardInputAreaLog) << "Init ChipCardInputArea for Index :" << index.column();

    this->m_chipCardModel = new Model::ChipCard();
    this->m_db = this->m_chipCardModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_chipCardModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);
    setMappings();

    m_mapper->setCurrentIndex(index.row());
}

ChipCardInputArea::~ChipCardInputArea()
{
    delete ui;
}

// TODO change lineEdit to lineEdit_Number
void ChipCardInputArea::setMappings()
{
    m_mapper->addMapping(ui->numberLineEdit, this->m_chipCardModel->getNumberIndex());
    m_mapper->addMapping(ui->doorComboBox, this->m_chipCardModel->getChipCardDoorIdIndex());
    m_mapper->addMapping(ui->profileComboBox, this->m_chipCardModel->getChipCardProfileIdIndex());
    m_mapper->addMapping(ui->employeeComboBox, this->m_chipCardModel->getEmployeeIdIndex());
    m_mapper->addMapping(ui->lastUpdateLineEdit, this->m_chipCardModel->getLastUpdateIndex());
}

void ChipCardInputArea::setViewOnlyMode(bool mode)
{
    ui->numberLineEdit->setDisabled(mode);
    // ui->doorComboBox->setDisabled(mode);
    // ui->profileComboBox->setDisabled(mode);
    // ui->employeeComboBox->setDisabled(mode);
}

void ChipCardInputArea::createDataset()
{
    qCDebug(jmbdeWidgetsChipCardInputAreaLog) << "Create a new Dataset for ChipCard...";

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

void ChipCardInputArea::retrieveDataset(const QModelIndex index)
{
}

void ChipCardInputArea::updateDataset(const QModelIndex index)
{
}

void ChipCardInputArea::deleteDataset(const QModelIndex index)
{
}

void ChipCardInputArea::on_pushButton_Add_clicked()
{
    createDataset();
    on_pushButton_EditFinish_clicked();
}

void ChipCardInputArea::on_pushButton_EditFinish_clicked()
{
    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->pushButton_EditFinish->setText(tr("Finish"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(jmbdeWidgetsChipCardInputAreaLog) << "Save Data...";

        m_actualMode = Mode::Edit;
        ui->pushButton_EditFinish->setText(tr("Edit"));
        setViewOnlyMode(false);

        QString name = ui->numberLineEdit->text();

        if (name.isEmpty()) {
            QString message(tr("Please provide the chipcard number."));

            QMessageBox::information(this, tr("Add City"), message);
        } else {
            m_mapper->submit();
            m_model->database().transaction();
            if (m_model->submitAll()) {
                m_model->database().commit();
                qCDebug(jmbdeWidgetsChipCardInputAreaLog) << "Commit changes for Chipcard Database Table";
                m_model->database().rollback();
            } else {
                m_model->database().rollback();
                QMessageBox::warning(this, tr("jmbde"), tr("The database reported an error: %1").arg(m_model->lastError().text()));
            }
        }
    } break;

    default: {
        qCCritical(jmbdeWidgetsChipCardInputAreaLog) << "Unknown Mode!";
    }
    }
}
