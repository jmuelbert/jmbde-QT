/*
 *  SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "jmbdewidgets/departmentinputarea.h"
#include <ui_departmentinputarea.h>

DepartmentInputArea::DepartmentInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::DepartmentInputArea)
{
    ui->setupUi(this);

    qDebug() << tr("Initialisiere DepartmentInputArea mit Index :") << index.row();

    this->m_departmentModel = new Model::Department();
    this->m_db = this->m_departmentModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_departmentModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);
    m_mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    setMappings();

    qDebug() << tr("Aktueller Index: ") << m_mapper->currentIndex();

    if (index.row() < 0) {
        m_mapper->toFirst();
    } else {
        m_mapper->setCurrentIndex(index.row());
    }

    connect(ui->priorityHorizontalSlider, &QSlider::valueChanged, ui->prioritySpinBox, &QSpinBox::setValue);
    connect(ui->prioritySpinBox, &QSpinBox::valueChanged, ui->priorityHorizontalSlider, &QSlider::setValue);
    QObject::connect(this->ui->addPushButton, &QPushButton::released, this, &DepartmentInputArea::addEdit);
    QObject::connect(this->ui->editFinishPushButton, &QPushButton::released, this, &DepartmentInputArea::editFinish);
}

DepartmentInputArea::~DepartmentInputArea()
{
    delete ui;
}

// TODO change lineEdit to lineEdit_Number
void DepartmentInputArea::setMappings()
{
    m_mapper->addMapping(ui->nameLineEdit, this->m_departmentModel->getNameIndex());
    // m_mapper->addMapping(ui->priorityHorizontalSlider, this->m_departmentModel->getPriorityIndex());
    m_mapper->addMapping(ui->prioritySpinBox, this->m_departmentModel->getPriorityIndex());
    ui->priorityHorizontalSlider->setValue(ui->prioritySpinBox->value());
    m_mapper->addMapping(ui->printerComboBox, this->m_departmentModel->getPrinterIdIndex());
    m_mapper->addMapping(ui->faxComboBox, this->m_departmentModel->getFaxIdIndex());
    m_mapper->addMapping(ui->lastUpdateLineEdit, m_departmentModel->getLastUpdateIndex());
}

void DepartmentInputArea::setViewOnlyMode(bool mode)
{
    ui->nameLineEdit->setDisabled(mode);
    ui->priorityHorizontalSlider->setDisabled(mode);
    ui->prioritySpinBox->setDisabled(mode);
    ui->priorityHorizontalSlider->setValue(ui->prioritySpinBox->value());
    // ui->printerComboBox->setDisabled(mode);
    // ui->faxComboBox->setDisabled(mode);
}

void DepartmentInputArea::createDataset()
{
    qDebug() << tr("Erzeuge einen neuen, leeren Datensatz für Department");

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

void DepartmentInputArea::deleteDataset(const QModelIndex &index)
{
    qDebug() << tr("Lösche Daten von Department");
    m_mapper->setCurrentIndex(index.row());
}

void DepartmentInputArea::addEdit()
{
    qDebug() << tr("Füge neue Daten zu Department");
    createDataset();
    editFinish();
}

void DepartmentInputArea::editFinish()
{
    qDebug() << tr("Bearbeite oder schließe Department Daten");

    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->editFinishPushButton->setText(tr("Fertig"));
        setViewOnlyMode(false);
    } break;

    case Mode::Finish: {
        qDebug() << tr("Die Daten werden gesichert.");

        m_actualMode = Mode::Edit;
        ui->editFinishPushButton->setText(tr("Bearbeiten"));
        setViewOnlyMode(false);

        QString name = ui->nameLineEdit->text();

        if (name.isEmpty()) {
            QString message(tr("Bitte geben sie einen Abteilungsnamen an."));

            QMessageBox::information(this, tr("Abteilung hinzufügen"), message);
        } else {
            m_mapper->submit();
            m_model->database().transaction();
            if (m_model->submitAll()) {
                m_model->database().commit();
                qDebug() << tr("Schreiben der Änderungen für Account in die Datenbank");
                m_model->database().rollback();
            } else {
                m_model->database().rollback();
                QMessageBox::warning(this, tr("jmbde"), tr("Die Datenbank meldet den Fehler: %1").arg(m_model->lastError().text()));
            }
        }
    } break;

    default: {
        qCritical() << tr("Fehler: Unbekannter Modus");
    }
    }
}
