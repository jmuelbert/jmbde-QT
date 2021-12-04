/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <ui_systemdatainputarea.h>
#include <views/systemdatainputarea.h>

SystemDataInputArea ::SystemDataInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::SystemDataInputArea)
    , m_SystemDataInputAreaLog(QLoggingCategory("jmbde.widgets.systemdatainputarea"))

{
    ui->setupUi(this);

    qCDebug(m_SystemDataInputAreaLog) << tr("Initialisiere SystemDataInputArea mit Index :") << index.row();

    this->m_systemDataModel = new Model::SystemData();
    this->m_db = this->m_systemDataModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_systemDataModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);
    m_mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    setMappings();

    qCDebug(m_SystemDataInputAreaLog) << tr("Aktueller Index: ") << m_mapper->currentIndex();

    if (index.row() < 0) {
        m_mapper->toFirst();
    } else {
        m_mapper->setCurrentIndex(index.row());
    }

    QObject::connect(this->ui->addPushButton, &QPushButton::released, this, &SystemDataInputArea::addEdit);
    QObject::connect(this->ui->editFinishPushButton, &QPushButton::released, this, &SystemDataInputArea::editFinish);
}
SystemDataInputArea::~SystemDataInputArea()
{
    delete ui;
}

void SystemDataInputArea::setMappings()
{
    m_mapper->addMapping(ui->nameLineEdit, this->m_systemDataModel->getNameIndex());
    m_mapper->addMapping(ui->localCheckBox, this->m_systemDataModel->getLocalIndex());
    m_mapper->addMapping(ui->compamyComboBox, this->m_systemDataModel->getCompanyIdIndex());
    m_mapper->addMapping(ui->lastUpdateLineEdit, this->m_systemDataModel->getLastUpdateIndex());
}

void SystemDataInputArea::setViewOnlyMode(bool mode)
{
    ui->nameLineEdit->setDisabled(mode);
    ui->localCheckBox->setDisabled(mode);
    // ui->compamyComboBox->setDisabled(mode);
}

void SystemDataInputArea::createDataset()
{
    qCDebug(m_SystemDataInputAreaLog) << tr("Erzeuge einen neuen, leeren Datensatz für SystemData...");

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

void SystemDataInputArea::deleteDataset(const QModelIndex &index)
{
    qCDebug(m_SystemDataInputAreaLog) << tr("Lösche Daten von SystemData");
    m_mapper->setCurrentIndex(index.row());
}

void SystemDataInputArea::addEdit()
{
    qCDebug(m_SystemDataInputAreaLog) << tr("Füge neue Daten zu SystemData");
    createDataset();
    editFinish();
}

void SystemDataInputArea::editFinish()
{
    qCDebug(m_SystemDataInputAreaLog) << tr("Bearbeite oder schließe SystemData Daten");

    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->editFinishPushButton->setText(tr("Fertig"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(m_SystemDataInputAreaLog) << tr("Die Daten werden gesichert.");

        m_actualMode = Mode::Edit;
        ui->editFinishPushButton->setText(tr("Bearbeiten"));
        setViewOnlyMode(false);

        QString name = ui->nameLineEdit->text();

        if (name.isEmpty()) {
            QString message(tr("Bitte geben Sie den Namen fpr die Systemdatem an."));

            QMessageBox::information(this, tr("Füge Systemdaten hinzu"), message);
        } else {
            m_mapper->submit();
            m_model->database().transaction();
            if (m_model->submitAll()) {
                m_model->database().commit();
                qCDebug(m_SystemDataInputAreaLog) << tr("Schreiben der Änderungen für Systemdatem in die Datenbank");
                emit dataChanged();
            } else {
                m_model->database().rollback();
                QMessageBox::warning(this, tr("jmbde"), tr("Die Datenbank meldet den Fehler: %1").arg(m_model->lastError().text()));
            }
        }
    } break;

    default: {
        qCCritical(m_SystemDataInputAreaLog) << tr("Fehler: Unbekannter Modus");
    }
    }
}
