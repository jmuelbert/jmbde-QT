/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <ui_chipcardprofileinputarea.h>
#include <views/chipcardprofileinputarea.h>

ChipCardProfileInputArea::ChipCardProfileInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::ChipCardProfileInputArea)
{
    ui->setupUi(this);

    qCDebug(jmbdeWidgetsChipCardProfileInputAreaLog) << "Initialisiere ChipCardProfileInputArea mit Index :" << index.row();

    this->m_chipCardProfileModel = new Model::ChipCardProfile();
    this->m_db = this->m_chipCardProfileModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_chipCardProfileModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);
    m_mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    setMappings();

    qCDebug(jmbdeWidgetsChipCardProfileInputAreaLog) << tr("Aktueller Index: ") << m_mapper->currentIndex();

    if (index.row() < 0) {
        m_mapper->toFirst();
    } else {
        m_mapper->setCurrentIndex(index.row());
    }

    QObject::connect(this->ui->addPushButton, &QPushButton::released, this, &ChipCardProfileInputArea::addEdit);
    QObject::connect(this->ui->editFinishPushButton, &QPushButton::released, this, &ChipCardProfileInputArea::editFinish);
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
    qCDebug(jmbdeWidgetsChipCardProfileInputAreaLog) << tr("Erzeuge einen neuen, leeren Datensatz für ChipCardProfile...");

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

void ChipCardProfileInputArea::deleteDataset(const QModelIndex &index)
{
    qCDebug(jmbdeWidgetsChipCardProfileInputAreaLog) << tr("Lösche Daten von ChipCardProfile");
    m_mapper->setCurrentIndex(index.row());
}

void ChipCardProfileInputArea::addEdit()
{
    qCDebug(jmbdeWidgetsChipCardProfileInputAreaLog) << tr("Füge neue Daten zu ChipCardProfile");
    createDataset();
    editFinish();
}

void ChipCardProfileInputArea::editFinish()
{
    qCDebug(jmbdeWidgetsChipCardProfileInputAreaLog) << tr("Bearbeite oder schließe ChipCardProfile Daten");

    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->editFinishPushButton->setText(tr("Fertig"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(jmbdeWidgetsChipCardProfileInputAreaLog) << tr("Die Daten werden gesichert.");

        m_actualMode = Mode::Edit;
        ui->editFinishPushButton->setText(tr("Bearbeiten"));
        setViewOnlyMode(false);

        QString number = ui->numberLineEdit->text();

        if (number.isEmpty()) {
            QString message(tr("Bitte geben sie eine Schlüsselchip Profil Nummer ein."));

            QMessageBox::information(this, tr("Hinzufügen Schlüsselchip Profil"), message);
        } else {
            m_mapper->submit();
            m_model->database().transaction();
            if (m_model->submitAll()) {
                m_model->database().commit();
                qCDebug(jmbdeWidgetsChipCardProfileInputAreaLog) << tr("Schreiben der Änderungen für Account in die Datenbank");
                dataChanged();
            } else {
                m_model->database().rollback();
                QMessageBox::warning(this, tr("jmbde"), tr("Die Datenbank meldet den Fehler: %1").arg(m_model->lastError().text()));
            }
        }
    } break;

    default: {
        qCCritical(jmbdeWidgetsChipCardProfileInputAreaLog) << tr("Fehler: Unbekannter Modus");
    }
    }
}
