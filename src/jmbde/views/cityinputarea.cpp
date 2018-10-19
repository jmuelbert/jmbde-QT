/**************************************************************************
**
** Copyright (c) 2013-2018 Jürgen Mülbert. All rights reserved.
**
** This file is part of jmbde
**
** Licensed under the EUPL, Version 1.2 or – as soon they
** will be approved by the European Commission - subsequent
** versions of the EUPL (the "Licence");
** You may not use this work except in compliance with the
** Licence.
** You may obtain a copy of the Licence at:
**
** https://joinup.ec.europa.eu/page/eupl-text-11-12
**
** Unless required by applicable law or agreed to in
** writing, software distributed under the Licence is
** distributed on an "AS IS" basis,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
** express or implied.
** See the Licence for the specific language governing
** permissions and limitations under the Licence.
**
** Lizenziert unter der EUPL, Version 1.2 oder - sobald
**  diese von der Europäischen Kommission genehmigt wurden -
** Folgeversionen der EUPL ("Lizenz");
** Sie dürfen dieses Werk ausschließlich gemäß
** dieser Lizenz nutzen.
** Eine Kopie der Lizenz finden Sie hier:
**
** https://joinup.ec.europa.eu/page/eupl-text-11-12
**
** Sofern nicht durch anwendbare Rechtsvorschriften
** gefordert oder in schriftlicher Form vereinbart, wird
** die unter der Lizenz verbreitete Software "so wie sie
** ist", OHNE JEGLICHE GEWÄHRLEISTUNG ODER BEDINGUNGEN -
** ausdrücklich oder stillschweigend - verbreitet.
** Die sprachspezifischen Genehmigungen und Beschränkungen
** unter der Lizenz sind dem Lizenztext zu entnehmen.
**
**************************************************************************/

#include "cityinputarea.h"
#include "ui_cityinputarea.h"

CityInputArea::CityInputArea(QWidget* parent, const QModelIndex index) :
    QGroupBox(parent), ui(new Ui::CityInputArea)
{
    ui->setupUi(this);

    qDebug() << "Init CityInputArea for Index : " << index;

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = new QSqlRelationalTableModel(this);
    m_model->setTable(QLatin1String("city_name"));
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    m_model->select();

    // Set the mapper
    m_mapper = new QDataWidgetMapper(this);
    m_mapper->setModel(m_model);
    m_mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    setMappings();

    m_mapper->setCurrentIndex(index.row());
}

CityInputArea::~CityInputArea()
{
    delete ui;
}

void CityInputArea::setMappings()
{
    m_mapper->addMapping(ui->lineEdit_CityName, m_model->fieldIndex(QLatin1String("name")));
}

void CityInputArea::setViewOnlyMode(bool mode)
{
    ui->comboBox_ZipCode->setDisabled(mode);
    ui->lineEdit_CityName->setDisabled(mode);
}

void CityInputArea::createDataset()
{
    qDebug() << "Create a new Dataset for City...";

    m_mapper->toLast();

    int row = m_mapper->currentIndex();
    if (row < 0) row = 0;

    m_mapper->submit();
    m_model->insertRow(row);
    m_mapper->setCurrentIndex(row);
}

void CityInputArea::retrieveDataset(const QModelIndex index) {}

void CityInputArea::updateDataset(const QModelIndex index) {}

void CityInputArea::deleteDataset(const QModelIndex index) {}

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

    }
    break;

    case Mode::Finish: {
        qDebug() << "Save Data...";

        m_actualMode = Mode::Edit;
        ui->pushButton_EditFinish->setText(tr("Edit"));
        setViewOnlyMode(false);

        QString name = ui->lineEdit_CityName->text();

        if (name.isEmpty()) {
            QString message(tr("Please provide the name of the city."));

            QMessageBox::information(this, tr("Add City"), message);
        }
        else {
            m_mapper->submit();
            m_model->database().transaction();
            if (m_model->submitAll()) {
                m_model->database().commit();
                qDebug() << "Commit changes for Computer Databse Table";
            }
            else {
                m_model->database().rollback();
                QMessageBox::warning(this, tr("jmbde"),
                                     tr("The database reported an error: %1")
                                     .arg(m_model->lastError().text()));
            }
        }
    }
    break;

    default: {
        qDebug() << "Error";
    }
    }
}


