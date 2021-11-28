/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <ui_employeedocumentinputarea.h>
#include <views/employeedocumentinputarea.h>

EmployeeDocumentInputArea::EmployeeDocumentInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::EmployeeDocumentInputArea)
{
    ui->setupUi(this);

    qCDebug(jmbdeWidgetsEmployeeDocumentInputAreaLog) << tr("Initialisiere EmployeeDocumentInputArea mit Index :") << index.row();

    this->m_employeeDocumentModel = new Model::EmployeeDocument();
    this->m_db = this->m_employeeDocumentModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_employeeDocumentModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);
    m_mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    setMappings();

    qCDebug(jmbdeWidgetsEmployeeDocumentInputAreaLog) << tr("Aktueller Index: ") << m_mapper->currentIndex();

    if (index.row() < 0) {
        m_mapper->toFirst();
    } else {
        m_mapper->setCurrentIndex(index.row());
    }

    QObject::connect(this->ui->addPushButton, &QPushButton::released, this, &EmployeeDocumentInputArea::addEdit);
    QObject::connect(this->ui->editFinishPushButton, &QPushButton::released, this, &EmployeeDocumentInputArea::editFinish);
}

EmployeeDocumentInputArea::~EmployeeDocumentInputArea()
{
    delete ui;
}

void EmployeeDocumentInputArea::setMappings()
{
    m_mapper->addMapping(ui->employeeIdcomboBox, this->m_employeeDocumentModel->getEmployeeIdIndex());
    m_mapper->addMapping(ui->documentIdcomboBox, this->m_employeeDocumentModel->getDocumentIdIndex());
    m_mapper->addMapping(ui->lastUpdatelineEdit, this->m_employeeDocumentModel->getLastUpdateIndex());
}

void EmployeeDocumentInputArea::setViewOnlyMode(bool mode)
{
    // ui->employeeIdcomboBox->setDisabled(mode);
    // ui->documentIdcomboBox->setDisabled(mode);
}

void EmployeeDocumentInputArea::createDataset()
{
    qCDebug(jmbdeWidgetsEmployeeDocumentInputAreaLog) << tr("Erzeuge einen neuen, leeren Datensatz für EmployeeDocument...");

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

void EmployeeDocumentInputArea::deleteDataset(const QModelIndex &index)
{
    qCDebug(jmbdeWidgetsEmployeeDocumentInputAreaLog) << tr("Lösche Daten von EmployeeDocument");
    m_mapper->setCurrentIndex(index.row());
}

void EmployeeDocumentInputArea::addEdit()
{
    qCDebug(jmbdeWidgetsEmployeeDocumentInputAreaLog) << tr("Füge neue Daten zu EmployeeDocument");
    createDataset();
    editFinish();
}

void EmployeeDocumentInputArea::editFinish()
{
    qCDebug(jmbdeWidgetsEmployeeDocumentInputAreaLog) << tr("Bearbeite oder schließe EmployeeDocument Daten");

    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->editFinishPushButton->setText(tr("Fertig"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(jmbdeWidgetsEmployeeDocumentInputAreaLog) << tr("Die Daten werden gesichert.");

        m_actualMode = Mode::Edit;
        ui->editFinishPushButton->setText(tr("Bearbeiten"));
        setViewOnlyMode(false);

        m_mapper->submit();
        m_model->database().transaction();
        if (m_model->submitAll()) {
            m_model->database().commit();
            qCDebug(jmbdeWidgetsEmployeeDocumentInputAreaLog) << tr("Schreiben der Änderungen für Account in die Datenbank");
            dataChanged();
        } else {
            m_model->database().rollback();
            QMessageBox::warning(this, tr("jmbde"), tr("Die Datenbank meldet den Fehler: %1").arg(m_model->lastError().text()));
        }

    } break;

    default: {
        qCCritical(jmbdeWidgetsEmployeeDocumentInputAreaLog) << tr("Fehler: Unbekannter Modus");
    }
    }
}
