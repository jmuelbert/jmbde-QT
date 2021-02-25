/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <ui_functioninputarea.h>
#include <views/functioninputarea.h>

Q_LOGGING_CATEGORY(jmbdeWidgetsFunctionInputAreaLog, "jmuelbert.jmbde.widgets.functioninputarea", QtWarningMsg)

FunctionInputArea::FunctionInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::FunctionInputArea)
{
    ui->setupUi(this);

    qCDebug(jmbdeWidgetsFunctionInputAreaLog) << tr("Initialisiere FunctionInputArea mit Index :") << index.row();

    this->m_functionModel = new Model::Function();
    this->m_db = this->m_functionModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_functionModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);
    m_mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    setMappings();

    qCDebug(jmbdeWidgetsFunctionInputAreaLog) << tr("Aktueller Index: ") << m_mapper->currentIndex();

    if (index.row() < 0) {
        m_mapper->toFirst();
    } else {
        m_mapper->setCurrentIndex(index.row());
    }

    connect(ui->priorityHorizontalSlider, &QSlider::valueChanged, ui->prioritySpinBox, &QSpinBox::setValue);
    connect(ui->prioritySpinBox, &QSpinBox::valueChanged, ui->priorityHorizontalSlider, &QSlider::setValue);
    QObject::connect(this->ui->addPushButton, &QPushButton::released, this, &FunctionInputArea::addEdit);
    QObject::connect(this->ui->editFinishPushButton, &QPushButton::released, this, &FunctionInputArea::editFinish);
}

FunctionInputArea::~FunctionInputArea()
{
    delete ui;
}

void FunctionInputArea::setMappings()
{
    m_mapper->addMapping(ui->nameLineEdit, this->m_functionModel->getNameIndex());
    m_mapper->addMapping(ui->prioritySpinBox, this->m_functionModel->getPriorityIndex());
    ui->priorityHorizontalSlider->setValue(ui->prioritySpinBox->value());
    m_mapper->addMapping(ui->lastUpdateLineEdit, this->m_functionModel->getLastUpdateIndex());
}

void FunctionInputArea::setViewOnlyMode(bool mode)
{
    ui->nameLineEdit->setDisabled(mode);
    ui->priorityHorizontalSlider->setDisabled(mode);
    ui->priorityHorizontalSlider->setDisabled(mode);
    ui->prioritySpinBox->setDisabled(mode);
    ui->priorityHorizontalSlider->setValue(ui->prioritySpinBox->value());
}

void FunctionInputArea::createDataset()
{
    qCDebug(jmbdeWidgetsFunctionInputAreaLog) << tr("Erzeuge einen neuen, leeren Datensatz für Function...");

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

void FunctionInputArea::deleteDataset(const QModelIndex &index)
{
    qCDebug(jmbdeWidgetsFunctionInputAreaLog) << tr("Lösche Daten von Function");
    m_mapper->setCurrentIndex(index.row());
}

void FunctionInputArea::addEdit()
{
    qCDebug(jmbdeWidgetsFunctionInputAreaLog) << tr("Füge neue Daten zu Function");
    createDataset();
    editFinish();
}

void FunctionInputArea::editFinish()
{
    qCDebug(jmbdeWidgetsFunctionInputAreaLog) << tr("Bearbeite oder schließe Function Daten");

    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->editFinishPushButton->setText(tr("Fertig"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(jmbdeWidgetsFunctionInputAreaLog) << tr("Die Daten werden gesichert.");

        m_actualMode = Mode::Edit;
        ui->editFinishPushButton->setText(tr("Bearbeiten"));
        setViewOnlyMode(false);

        QString name = ui->nameLineEdit->text();

        if (name.isEmpty()) {
            QString message(tr("Bitte Name für fuktion eingeben."));

            QMessageBox::information(this, tr("Funktion hinzufügen"), message);
        } else {
            m_mapper->submit();
            m_model->database().transaction();
            if (m_model->submitAll()) {
                m_model->database().commit();
                qCDebug(jmbdeWidgetsFunctionInputAreaLog) << tr("Schreiben der Änderungen für Function in die Datenbank");
                dataChanged();
            } else {
                m_model->database().rollback();
                QMessageBox::warning(this, tr("jmbde"), tr("Die Datenbank meldet den Fehler: %1").arg(m_model->lastError().text()));
            }
        }
    } break;

    default: {
        qCCritical(jmbdeWidgetsFunctionInputAreaLog) << tr("Fehler: Unbekannter Modus");
    }
    }
}
