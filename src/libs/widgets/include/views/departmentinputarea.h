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
#include <QDebug>
#include <QGroupBox>
#include <QMessageBox>
#include <QScrollArea>
#include <QSqlRelationalDelegate>
#include <QtSql>

#include "jmbdewidgets-version.h"
#include "jmbdewidgets_export.h"
#include "loggingcategory.h"

namespace Ui
{
class DepartmentInputArea;
}

/**
 * @brief The DepartmentInputArea class
 */
class JMBDEWIDGETS_EXPORT DepartmentInputArea : public QGroupBox
{
    Q_OBJECT

public:
    /**
       @brief DepartmentInputArea
       @param parent The pointer to the parent object
       @param index The index for view the data
     */
    explicit DepartmentInputArea(QWidget *parent = nullptr, const QModelIndex index = QModelIndex());

    /**
     * @brief ~DepartmentInputArea();
     */
    ~DepartmentInputArea();

private slots:
    /**
     * @brief on_pushButton_Add_clicked
     */
    void on_pushButton_Add_clicked();

    /**
     * @brief on_pushButton_EditFinish_clicked
     */
    void on_pushButton_EditFinish_clicked();

private:
    /**
     * @brief ui
     */
    Ui::DepartmentInputArea *ui;

    /**
     * @brief The Mode enum
     */
    enum Mode { Edit, Finish };

    /**
     * @brief m_actualMode
     */
    Mode m_actualMode;

    /**
     * @brief m_model
     */
    QSqlRelationalTableModel *m_model;

    /**
     * @brief m_selectionModel
     */
    QItemSelectionModel *m_selectionModel {};

    /**
     * @brief m_mapper
     */
    QDataWidgetMapper *m_mapper;

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
