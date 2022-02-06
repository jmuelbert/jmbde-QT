/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <ui_chipcardinputarea.h>
#include <views/chipcardinputarea.h>

ChipCardInputArea::ChipCardInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::ChipCardInputArea)
    , m_ChipCardInputAreaLog(QLoggingCategory("jmbde.models.chipcardinputarea"))
{
    ui->setupUi(this);

    qCDebug(m_ChipCardInputAreaLog) << "Initialisiere ChipCardInputArea mit Index :" << index.row();

    this->m_chipCardModel = new Model::ChipCard();
    this->m_db = this->m_chipCardModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_chipCardModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);
    m_mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    setMappings();

    qCDebug(m_ChipCardInputAreaLog) << tr("Aktueller Index: ") << m_mapper->currentIndex();

    if (index.row() < 0) {
        m_mapper->toFirst();
    } else {
        m_mapper->setCurrentIndex(index.row());
    }

    QObject::connect(this->ui->addPushButton, &QPushButton::released, this, &ChipCardInputArea::addEdit);
    QObject::connect(this->ui->editFinishPushButton, &QPushButton::released, this, &ChipCardInputArea::editFinish);
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
    qCDebug(m_ChipCardInputAreaLog) << "Erzeuge einen neuen, leeren Datensatz für ChipCard...";

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

void ChipCardInputArea::deleteDataset(const QModelIndex &index)
{
    qCDebug(m_ChipCardInputAreaLog) << tr("Lösche Daten von ChipCard");
    m_mapper->setCurrentIndex(index.row());
}

void ChipCardInputArea::addEdit()
{
    qCDebug(m_ChipCardInputAreaLog) << tr("Füge neue Daten zu ChipCard");
    createDataset();
    editFinish();
}

void ChipCardInputArea::editFinish()
{
    qCDebug(m_ChipCardInputAreaLog) << tr("Bearbeite oder schließe ChipCard Daten");

    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->editFinishPushButton->setText(tr("Fertig"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(m_ChipCardInputAreaLog) << tr("Die Daten werden gesichert.");

        m_actualMode = Mode::Edit;
        ui->editFinishPushButton->setText(tr("Bearbeiten"));
        setViewOnlyMode(false);

        QString number = ui->numberLineEdit->text();

        if (number.isEmpty()) {
            QString message(tr("Bitte geben sie eine Schlüsselchip Nummer ein."));

            QMessageBox::information(this, tr("Hinzufügen Schlüsselchip"), message);
        } else {
            m_mapper->submit();
            m_model->database().transaction();
            if (m_model->submitAll()) {
                m_model->database().commit();
                qCDebug(m_ChipCardInputAreaLog) << tr("Schreiben der Änderungen für ChipCard in die Datenbank");
                dataChanged();
            } else {
                m_model->database().rollback();
                QMessageBox::warning(this, tr("jmbde"), tr("Die Datenbank meldet den Fehler: %1").arg(m_model->lastError().text()));
            }
        }
    } break;

    default: {
        qCCritical(m_ChipCardInputAreaLog) << tr("Fehler: Unbekannter Modus");
    }
    }
}
