/*
// ManufacturerInputArea manufacturerinputarea.h
// part of <Project>
//
// Copyright (c) 2013-2017 Jürgen Mülbert. All rights reserved.
//
// Licensed under the EUPL, Version 1.2 or – as soon they
// will be approved by the European Commission - subsequent
// versions of the EUPL (the "Licence");
// You may not use this work except in compliance with the
// Licence.
// You may obtain a copy of the Licence at:
//
// https://joinup.ec.europa.eu/page/eupl-text-11-12
//
// Unless required by applicable law or agreed to in
// writing, software distributed under the Licence is
// distributed on an "AS IS" basis,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
// express or implied.
// See the Licence for the specific language governing
// permissions and limitations under the Licence.
//
// Lizenziert unter der EUPL, Version 1.2 oder - sobald
// diese von der Europäischen Kommission genehmigt wurden -
// Folgeversionen der EUPL ("Lizenz");
// Sie dürfen dieses Werk ausschließlich gemäß
// dieser Lizenz nutzen.
// Eine Kopie der Lizenz finden Sie hier:
//
// https://joinup.ec.europa.eu/page/eupl-text-11-12
//
// Sofern nicht durch anwendbare Rechtsvorschriften
// gefordert oder in schriftlicher Form vereinbart, wird
// die unter der Lizenz verbreitete Software "so wie sie
// ist", OHNE JEGLICHE GEWÄHRLEISTUNG ODER BEDINGUNGEN -
// ausdrücklich oder stillschweigend - verbreitet.
// Die sprachspezifischen Genehmigungen und Beschränkungen
// unter der Lizenz sind dem Lizenztext zu entnehmen.
//
// Created: 5.11.2017
*/
#ifndef MANUFACTURERINPUTAREA_H
#define MANUFACTURERINPUTAREA_H

#include <QDebug>

#include <QtSql>
#include <QDataWidgetMapper>
#include <QScrollArea>
#include <QSqlRelationalDelegate>

#include <QMessageBox>

namespace Ui {
class ManufacturerInputArea;
}

/**
 * @brief The ManufacturerInputArea class
 */
class ManufacturerInputArea : public QScrollArea
{
    Q_OBJECT

public:
    /**
     * @brief ManufacturerInputArea
     * @param parent
     */
    explicit ManufacturerInputArea(QWidget *parent = 0, const QModelIndex index =  QModelIndex());

    /**
      * @brief ~ManufacturerInputArea
      */
    ~ManufacturerInputArea();

private slots:
    void on_pushButton_Add_clicked();

    void on_pushButton_EditFinish_clicked();

private:
    Ui::ManufacturerInputArea *ui;

    enum Mode {
      Edit,
      Finish
    };
    Mode m_actualMode;

    QSqlRelationalTableModel* m_model;
    QItemSelectionModel* m_selectionModel;
    QDataWidgetMapper* m_mapper;

    void setMappings();
    void setViewOnlyMode(bool mode = true);
    void createDataset();
    void retrieveDataset(const QModelIndex index);
    void updateDataset(const QModelIndex index);
    void deleteDataset(const QModelIndex index);
};

#endif // MANUFACTURERINPUTAREA_H
