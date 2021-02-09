/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <ui_systemdatainputarea.h>
#include <views/systemdatainputarea.h>

Q_LOGGING_CATEGORY(jmbdeWidgetsSystemDataInputAreaLog, "jmuelbert.jmbde.widgets.systemdatainputarea", QtWarningMsg)

SystemDataInputArea ::SystemDataInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::SystemDataInputArea)
{
    ui->setupUi(this);

    qCDebug(jmbdeWidgetsSystemDataInputAreaLog) << "Init SystemDataInputArea for Index :" << index.column();

    this->m_systemDataModel = new Model::SystemData();
    this->m_db = this->m_systemDataModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_systemDataModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);

    setMappings();

    m_mapper->setCurrentIndex(index.row());
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
    qCDebug(jmbdeWidgetsSystemDataInputAreaLog) << "Create a new Dataset for ChipCard...";

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

void SystemDataInputArea::retrieveDataset(const QModelIndex index)
{
}

void SystemDataInputArea::updateDataset(const QModelIndex index)
{
}

void SystemDataInputArea::deleteDataset(const QModelIndex index)
{
}

void SystemDataInputArea::on_pushButton_Add_clicked()
{
    createDataset();
    on_pushButton_EditFinish_clicked();
}

void SystemDataInputArea::on_pushButton_EditFinish_clicked()
{
    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->editFinishPushButton->setText(tr("Fertig"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(jmbdeWidgetsSystemDataInputAreaLog) << tr("Daten speichern...");

        m_actualMode = Mode::Edit;
        ui->editFinishPushButton->setText(tr("Bearbeiten"));
        setViewOnlyMode(false);

        QString name = ui->nameLineEdit->text();

        if (name.isEmpty()) {
            QString message(tr("Bitte geben Sie den Namen fpr die Systemdatem an."));

            QMessageBox::information(this, tr("Füze Systemdaten hinzu"), message);
        } else {
            m_mapper->submit();
            m_model->database().transaction();
            if (m_model->submitAll()) {
                m_model->database().commit();
                qCDebug(jmbdeWidgetsSystemDataInputAreaLog) << tr("Änderung an der Tabelle systemdatem in der Datenbank");
                m_model->database().rollback();
            } else {
                m_model->database().rollback();
                QMessageBox::warning(this, tr("jmbde"), tr("Die Datenbank meldet einen Fehler: %1").arg(m_model->lastError().text()));
            }
        }
    } break;

    default: {
        qCCritical(jmbdeWidgetsSystemDataInputAreaLog) << tr("Fehler");
    }
    }
}
