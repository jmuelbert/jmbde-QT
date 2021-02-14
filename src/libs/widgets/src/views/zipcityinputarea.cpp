/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "ui_zipcityinputarea.h"
#include "views/zipcitiyinputarea.h"

Q_LOGGING_CATEGORY(jmbdeWidgetsZipCityInputAreaLog, "jmuelbert.jmbde.widgets.zipcityinputarea", QtWarningMsg)

ZipCityInputArea::ZipCityInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::ZipCityInputArea)
{
    ui->setupUi(this);

    qCDebug(jmbdeWidgetsZipCityInputAreaLog) << "Init ZipCityInputArea for Index :" << index.column();

    this->m_zipCityModel = new Model::ZipCity();
    this->m_db = this->m_zipCityModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_zipCityModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);

    setMappings();

    m_mapper->setCurrentIndex(index.row());
}

ZipCityInputArea::~ZipCityInputArea()
{
    delete ui;
}

void ZipCityInputArea::setMappings()
{
    m_mapper->addMapping(ui->cityComboBox, this->m_zipCityModel->getCityIdIndex());
    m_mapper->addMapping(ui->lastUpdateLineEdit, this->m_zipCityModel->getLastUpdateIndex());
    m_mapper->addMapping(ui->zipCodeComboBox, this->m_zipCityModel->getZipCityIdIndex());
}

void ZipCityInputArea::setViewOnlyMode(bool mode)
{
    // ui->cityComboBox->setDisabled(mode);
    // ui->zipCodeComboBox->setDisabled(mode);
}

void ZipCityInputArea::createDataset()
{
    qCDebug(jmbdeWidgetsZipCityInputAreaLog) << "Create a new Dataset for ChipCard...";

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

void ZipCityInputArea::retrieveDataset(const QModelIndex index)
{
}

void ZipCityInputArea::updateDataset(const QModelIndex index)
{
}

void ZipCityInputArea::deleteDataset(const QModelIndex index)
{
}

void ZipCityInputArea::on_pushButton_Add_clicked()
{
    createDataset();
    on_pushButton_EditFinish_clicked();
}

void ZipCityInputArea::on_pushButton_EditFinish_clicked()
{
    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->editFinishPushButton->setText(tr("Fertig"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(jmbdeWidgetsZipCityInputAreaLog) << tr("Daten speichern...");

        m_actualMode = Mode::Edit;
        ui->editFinishPushButton->setText(tr("Bearbeiten"));
        setViewOnlyMode(false);

        m_mapper->submit();
        m_model->database().transaction();
        if (m_model->submitAll()) {
            m_model->database().commit();
            qCDebug(jmbdeWidgetsZipCityInputAreaLog) << "Commit changes for Chipcard Database Table";
            m_model->database().rollback();
        } else {
            m_model->database().rollback();
            QMessageBox::warning(this, tr("jmbde"), tr("The database reported an error: %1").arg(m_model->lastError().text()));
        }

    } break;

    default: {
        qCCritical(jmbdeWidgetsZipCityInputAreaLog) << "Unknown Mode!";
    }
    }
}
