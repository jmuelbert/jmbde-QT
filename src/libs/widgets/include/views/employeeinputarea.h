/*
   jmbde a BDE Tool for companies
   Copyright (C) 2013-2019  Jürgen Mülbert

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
*/

#pragma once

#include <QDataWidgetMapper>
#include <QGroupBox>
#include <QLoggingCategory>
#include <QMessageBox>
#include <QObject>
#include <QSqlRelationalDelegate>
#include <QtSql>

#include "jmbdewidgets-version.h"
#include "jmbdewidgets_export.h"
#include "loggingcategory.h"
#include "models/datacontext.h"
#include "models/computer.h"
#include "models/employee.h"
#include "models/fax.h"
#include "models/mobile.h"
#include "models/phone.h"
#include "models/place.h"
#include "models/printer.h"

Q_DECLARE_LOGGING_CATEGORY(jmbdeWidgetsEmployeeInputAreaLog)

namespace Ui
{
class EmployeeInputArea;
}

/**
 * @brief The EmployeeInputDialog class
 */
class JMBDEWIDGETS_EXPORT EmployeeInputArea : public QGroupBox

{
    Q_OBJECT

public:
    /*!
        @brief EmployeeInputArea
        @param tableName The name of the table in the Database
        @param The pointer to the Model
        @param parent The pointer to the parent object

        @todo Init the model from here
        @todo Get the tableName from the model
     */
    explicit EmployeeInputArea(QWidget *parent = nullptr, const QModelIndex index = QModelIndex());

    /**
     * @brief ~EmployeeInputArea
     */
    ~EmployeeInputArea();

signals:


public slots:

private slots:
    /**
     * @brief on_pushButton_EditFinish_clicked
     */
    void on_pushButton_EditFinish_clicked();

    /**
     * @brief on_pushButton_Add_clicked
     */
    void on_pushButton_Add_clicked();

private:
    /*!
     * @brief ui
     */
    Ui::EmployeeInputArea *ui;

    /*!
     * @brief The Mode enum
     */
    enum Mode { Edit, Finish };

    /*!
     * @brief m_actualMode
     */
    Mode m_actualMode;

    /*!
     * @brief m_dataContext
     */
    Model::Employee *employeeModel = {};

    /*!
     * @brief m_model
     */
    QSqlTableModel *m_model;

    /*!
     * @brief m_selectionModel
     */
    QItemSelectionModel *m_selectionModel {};

    /*!
     * @brief m_mapper
     */
    QDataWidgetMapper *m_mapper;

    /*!
     * @ brief m_db
     */
    QSqlDatabase m_db = {};

    /**
     * @brief setMappings
     */
    void setMappings();
    /**
     * @brief setViewOnlyMode
     * @param mode Set the ViewMode boolean
     */
    void setViewOnlyMode(bool mode = true);

    /**
     * @brief createDataset
     */
    void createDataset();

    /**
     * @brief retrieveDataset
     * @param index Get the data for the ModelIndex
     */
    void retrieveDataset(const QModelIndex index);

    /**
     * @brief updateDataset
     * @param index Update the Data for the ModelIndex
     */
    void updateDataset(const QModelIndex index);

    /**
     * @brief deleteDataset
     * @param index Delete the data for the ModelIndex
     */
    void deleteDataset(const QModelIndex index);
};
