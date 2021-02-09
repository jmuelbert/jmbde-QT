/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "views/cityinputarea.h"

#include "ui_cityinputarea.h"

Q_LOGGING_CATEGORY(jmbdeWidgetsCityInputAreaLog, "jmuelbert.jmbde.widgets.cityinputarea", QtWarningMsg)

CityInputArea::CityInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::CityInputArea)
{
    ui->setupUi(this);

    qCDebug(jmbdeWidgetsCityInputAreaLog) << "Init CityInputArea for Index : " << index;

    this->m_cityNameModel = new Model::CityName();
    this->m_db = this->m_cityNameModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_cityNameModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);
    setMappings();

    m_mapper->setCurrentIndex(index.row());
}

CityInputArea::~CityInputArea()
{
    delete ui;
}

void CityInputArea::setMappings()
{
    m_mapper->addMapping(ui->cityNameLineEdit, this->m_cityNameModel->getNameIndex());
    m_mapper->addMapping(ui->lastUpdateLineEdit, this->m_cityNameModel->getLastUpdateIndex());
}

void CityInputArea::setViewOnlyMode(bool mode)
{
    ui->cityNameLineEdit->setDisabled(mode);
}

void CityInputArea::createDataset()
{
    qCDebug(jmbdeWidgetsCityInputAreaLog) << "Create a new Dataset for City...";

    m_mapper->toLast();

    int row = m_mapper->currentIndex();
    if (row < 0) {
        row = 0;
    }
    m_mapper->submit();
    m_model->insertRow(row);
    m_mapper->setCurrentIndex(row);
}

void CityInputArea::retrieveDataset(const QModelIndex index)
{
}

void CityInputArea::updateDataset(const QModelIndex index)
{
}

void CityInputArea::deleteDataset(const QModelIndex index)
{
}

void CityInputArea::on_pushButton_Add_clicked()
{
    createDataset();
    on_pushButton_EditFinish_clicked();
}

void CityInputArea::on_pushButton_EditFinish_clicked()
{
    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->pushButton_EditFinish->setText(tr("Finish"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(jmbdeWidgetsCityInputAreaLog) << "Save Data...";

        m_actualMode = Mode::Edit;
        ui->pushButton_EditFinish->setText(tr("Edit"));
        setViewOnlyMode(false);

        QString name = ui->cityNameLineEdit->text();

        if (name.isEmpty()) {
            QString message(tr("Please provide the name of the city."));

            QMessageBox::information(this, tr("Add City"), message);
        } else {
            m_mapper->submit();
            m_model->database().transaction();
            if (m_model->submitAll()) {
                m_model->database().commit();
                qCDebug(jmbdeWidgetsCityInputAreaLog) << "Commit changes for Computer Databse Table";
            } else {
                m_model->database().rollback();
                QMessageBox::warning(this, tr("jmbde"), tr("The database reported an error: %1").arg(m_model->lastError().text()));
            }
        }
    } break;

    default: {
        qCCritical(jmbdeWidgetsCityInputAreaLog) << "Error";
    }
    }
}
