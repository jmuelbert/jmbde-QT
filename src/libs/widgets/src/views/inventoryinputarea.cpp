/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <ui_inventoryinputarea.h>
#include <views/inventoryinputarea.h>

InventoryInputArea::InventoryInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::InventoryInputArea)
    , m_InventoryInputAreaLog(QLoggingCategory("jmbde.widgets.inventoryinputarea"))

{
    ui->setupUi(this);

    qCDebug(m_InventoryInputAreaLog) << tr("Initialisiere InventoryInputArea mit Index :") << index.row();

    this->m_inventoryModel = new Model::Inventory();
    this->m_db = this->m_inventoryModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_inventoryModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);
    m_mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    setMappings();

    qCDebug(m_InventoryInputAreaLog) << tr("Aktueller Index: ") << m_mapper->currentIndex();

    if (index.row() < 0) {
        m_mapper->toFirst();
    } else {
        m_mapper->setCurrentIndex(index.row());
    }

    QObject::connect(this->ui->addPushButton, &QPushButton::released, this, &InventoryInputArea::addEdit);
    QObject::connect(this->ui->editFinishPushButton, &QPushButton::released, this, &InventoryInputArea::editFinish);
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
    qCDebug(m_InventoryInputAreaLog) << tr("Erzeuge einen neuen, leeren Datensatz für Inventory...");

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

void InventoryInputArea::deleteDataset(const QModelIndex &index)
{
    qCDebug(m_InventoryInputAreaLog) << tr("Lösche Daten von Inventory");
    m_mapper->setCurrentIndex(index.row());
}

void InventoryInputArea::addEdit()
{
    qCDebug(m_InventoryInputAreaLog) << tr("Füge neue Daten zu Inventory");
    createDataset();
    editFinish();
}

void InventoryInputArea::editFinish()
{
    qCDebug(m_InventoryInputAreaLog) << tr("Bearbeite oder schließe Inventory Daten");

    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->editFinishPushButton->setText(tr("Fertig"));

        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(m_InventoryInputAreaLog) << tr("Die Daten werden gesichert.");

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
                qCDebug(m_InventoryInputAreaLog) << tr("Schreiben der Änderungen für Inventory in die Datenbank");
                dataChanged();
            } else {
                m_model->database().rollback();
                QMessageBox::warning(this, tr("jmbde"), tr("Die Datenbank meldet den Fehler: %1").arg(m_model->lastError().text()));
            }
        }
    } break;

    default: {
        qCCritical(m_InventoryInputAreaLog) << tr("Fehler: Unbekannter Modus");
    }
    }
}
