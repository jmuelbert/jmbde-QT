/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <ui_employeeaccountinputarea.h>
#include <views/employeeaccountinputarea.h>

using Model::EmployeeAccount;

Q_LOGGING_CATEGORY(jmbdeWidgetsEmployeeAccountInputAreaLog, "jmuelbert.jmbde.widgets.employeeaccountinputarea", QtWarningMsg)

EmployeeAccountInputArea::EmployeeAccountInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::EmployeeAccountInputArea)
{
    ui->setupUi(this);

    qCDebug(jmbdeWidgetsEmployeeAccountInputAreaLog) << tr("Initialisiere EmployeeAccountInputArea mit Index :") << index.row();

    this->m_employeeAccountModel = new EmployeeAccount();
    this->m_db = this->m_employeeAccountModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_employeeAccountModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);
    m_mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    setMappings();

    qCDebug(jmbdeWidgetsEmployeeAccountInputAreaLog) << tr("Aktueller Index: ") << m_mapper->currentIndex();

    if (index.row() < 0) {
        m_mapper->toFirst();
    } else {
        m_mapper->setCurrentIndex(index.row());
    }

    QObject::connect(this->ui->addPushButton, &QPushButton::released, this, &EmployeeAccountInputArea::addEdit);
    QObject::connect(this->ui->editFinishPushButton, &QPushButton::released, this, &EmployeeAccountInputArea::editFinish);
}

EmployeeAccountInputArea::~EmployeeAccountInputArea()
{
    delete ui;
}

void EmployeeAccountInputArea::setMappings()
{
    m_mapper->addMapping(ui->employeeComboBox, this->m_employeeAccountModel->getEmployeeIdIndex());
    m_mapper->addMapping(ui->accountComboBox, this->m_employeeAccountModel->getAccountIdIndex());
    m_mapper->addMapping(ui->lastUpdateLineEdit, this->m_employeeAccountModel->getLastUpdateIndex());
}

void EmployeeAccountInputArea::setViewOnlyMode(bool mode)
{
    // ui->employeeComboBox->setDisabled(mode);
    // ui->accountComboBox->setDisabled(mode);
}

void EmployeeAccountInputArea::createDataset()
{
    qCDebug(jmbdeWidgetsEmployeeAccountInputAreaLog) << tr("Erzeuge einen neuen, leeren Datensatz für EmployeeAccount...");

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

void EmployeeAccountInputArea::deleteDataset(const QModelIndex &index)
{
    qCDebug(jmbdeWidgetsEmployeeAccountInputAreaLog) << tr("Lösche Daten von EmployeeAccount");
    m_mapper->setCurrentIndex(index.row());
}

void EmployeeAccountInputArea::addEdit()
{
    qCDebug(jmbdeWidgetsEmployeeAccountInputAreaLog) << tr("Füge neue Daten zu EmployeeAccount");
    createDataset();
    editFinish();
}
void EmployeeAccountInputArea::editFinish()
{
    qCDebug(jmbdeWidgetsEmployeeAccountInputAreaLog) << tr("Bearbeite oder schließe EmployeeAccount Daten");

    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->editFinishPushButton->setText(tr("Fertig"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(jmbdeWidgetsEmployeeAccountInputAreaLog) << tr("Die Daten werden gesichert.");

        m_actualMode = Mode::Edit;
        ui->editFinishPushButton->setText(tr("Bearbeiten"));
        setViewOnlyMode(false);

        m_mapper->submit();
        m_model->database().transaction();
        if (m_model->submitAll()) {
            m_model->database().commit();
            qCDebug(jmbdeWidgetsEmployeeAccountInputAreaLog) << tr("Schreiben der Änderungen für Account in die Datenbank");
            dataChanged();
        } else {
            m_model->database().rollback();
            QMessageBox::warning(this, tr("jmbde"), tr("Die Datenbank meldet den Fehler: %1").arg(m_model->lastError().text()));
        }

    } break;

    default: {
        qCCritical(jmbdeWidgetsEmployeeAccountInputAreaLog) << tr("Fehler: Unbekannter Modus");
    }
    }
}
