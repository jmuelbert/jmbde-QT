/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <ui_inventoryinputarea.h>
#include <views/inventoryinputarea.h>

Q_LOGGING_CATEGORY(jmbdeWidgetsInventoryInputAreaLog, "jmuelbert.jmbde.widgets.inventoryinputarea", QtWarningMsg)

InventoryInputArea::InventoryInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::InventoryInputArea)
{
    ui->setupUi(this);

    qCDebug(jmbdeWidgetsInventoryInputAreaLog) << "Init InventoryInputArea for Index :" << index.column();

    this->m_inventoryModel = new Model::Inventory();
    this->m_db = this->m_inventoryModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_inventoryModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);

    setMappings();

    m_mapper->setCurrentIndex(index.row());
}

InventoryInputArea::~InventoryInputArea()
{
    delete ui;
}

void InventoryInputArea::setMappings()
{
    m_mapper->addMapping(ui->numberLineEdit, this->m_inventoryModel->getNumberIndex());
    m_mapper->addMapping(ui->descriptionTextEdit, this->m_inventoryModel->getDescriptionIndex());
    m_mapper->addMapping(ui->activCheckBox, this->m_inventoryModel->getActiveIndex());
    m_mapper->addMapping(ui->lastUpdateLineEdit, this->m_inventoryModel->getLastUpateIndex());
}

void InventoryInputArea::setViewOnlyMode(bool mode)
{
    ui->numberLineEdit->setDisabled(mode);
    ui->descriptionTextEdit->setDisabled(mode);
    ui->activCheckBox->setDisabled(mode);
}

void InventoryInputArea::createDataset()
{
    qCDebug(jmbdeWidgetsInventoryInputAreaLog) << "Create a new Dataset for ChipCard...";

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

void InventoryInputArea::retrieveDataset(const QModelIndex index)
{
}

void InventoryInputArea::updateDataset(const QModelIndex index)
{
}

void InventoryInputArea::deleteDataset(const QModelIndex index)
{
}

void InventoryInputArea::on_pushButton_Add_clicked()
{
    createDataset();
    on_pushButton_EditFinish_clicked();
}

void InventoryInputArea::on_pushButton_EditFinish_clicked()
{
    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->editFinishPushButton->setText(tr("Fertig"));

        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(jmbdeWidgetsInventoryInputAreaLog) << tr("Dten sichern...");

        m_actualMode = Mode::Edit;
        ui->editFinishPushButton->setText(tr("Bearbeiten"));
        setViewOnlyMode(false);

        QString name = ui->numberLineEdit->text();

        if (name.isEmpty()) {
            QString message(tr("Bitte eine Inventar-Nummer angeben."));

            QMessageBox::information(this, tr("Inventar hinzufügen"), message);
        } else {
            m_mapper->submit();
            m_model->database().transaction();
            if (m_model->submitAll()) {
                m_model->database().commit();
                qCDebug(jmbdeWidgetsInventoryInputAreaLog) << "Commit changes for Inventar Database Table";
                m_model->database().rollback();
            } else {
                m_model->database().rollback();
                QMessageBox::warning(this, tr("jmbde"), tr("Die Datenbank meldet einen Fehler: %1").arg(m_model->lastError().text()));
            }
        }
    } break;

    default: {
        qCCritical(jmbdeWidgetsInventoryInputAreaLog) << tr("Fehler");
    }
    }
}
