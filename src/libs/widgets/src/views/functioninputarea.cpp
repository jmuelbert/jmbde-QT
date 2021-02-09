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

    qCDebug(jmbdeWidgetsFunctionInputAreaLog) << "Init FunctionInputArea for Index :" << index.column();

    this->m_functionModel = new Model::Function();
    this->m_db = this->m_functionModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_functionModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);

    setMappings();

    m_mapper->setCurrentIndex(index.row());

    connect(ui->priorityHorizontalSlider, &QSlider::valueChanged, ui->priorityLCDNumber, &QLCDNumber::intValue);
}

FunctionInputArea::~FunctionInputArea()
{
    delete ui;
}

void FunctionInputArea::setMappings()
{
    m_mapper->addMapping(ui->nameLineEdit, this->m_functionModel->getNameIndex());
    m_mapper->addMapping(ui->priorityHorizontalSlider, this->m_functionModel->getPriorityIndex());
    m_mapper->addMapping(ui->lastUpdateLineEdit, this->m_functionModel->getLastUpdateIndex());
}

void FunctionInputArea::setViewOnlyMode(bool mode)
{
    ui->nameLineEdit->setDisabled(mode);
    ui->priorityHorizontalSlider->setDisabled(mode);
}

void FunctionInputArea::createDataset()
{
    qCDebug(jmbdeWidgetsFunctionInputAreaLog) << "Create a new Dataset for ChipCard...";

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

void FunctionInputArea::retrieveDataset(const QModelIndex index)
{
}

void FunctionInputArea::updateDataset(const QModelIndex index)
{
}

void FunctionInputArea::deleteDataset(const QModelIndex index)
{
}

void FunctionInputArea::on_pushButton_Add_clicked()
{
    createDataset();
    on_pushButton_EditFinish_clicked();
}

void FunctionInputArea::on_pushButton_EditFinish_clicked()
{
    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->editFinishPushButton->setText(tr("Fertig"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(jmbdeWidgetsFunctionInputAreaLog) << "Save Data...";

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
                qCDebug(jmbdeWidgetsFunctionInputAreaLog) << "Commit changes for Chipcard Database Table";
                m_model->database().rollback();
            } else {
                m_model->database().rollback();
                QMessageBox::warning(this, tr("jmbde"), tr("Die Datenbank meldet einen Fehler: %1").arg(m_model->lastError().text()));
            }
        }
    } break;

    default: {
        qCCritical(jmbdeWidgetsFunctionInputAreaLog) << tr("Fehler");
    }
    }
}
