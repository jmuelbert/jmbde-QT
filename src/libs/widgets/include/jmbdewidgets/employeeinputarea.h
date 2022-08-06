/*
 *  SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include <QDataWidgetMapper>
#include <QGroupBox>
#include <QLoggingCategory>
#include <QMessageBox>
#include <QObject>
#include <QSqlRelationalDelegate>
#include <QtSql>

#include "jmbdemodels/computer.h"
#include "jmbdemodels/datacontext.h"
#include "jmbdemodels/employee.h"
#include "jmbdemodels/fax.h"
#include "jmbdemodels/mobile.h"
#include "jmbdemodels/phone.h"
#include "jmbdemodels/place.h"
#include "jmbdemodels/printer.h"
#include "jmbdewidgets_export.h"

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
    explicit EmployeeInputArea(QWidget *parent = nullptr, const QModelIndex &index = QModelIndex());

    /**
     * @brief ~EmployeeInputArea
     */
    ~EmployeeInputArea();

signals:
    /*!
        @brief dataChanged
     */
    void dataChanged();

public slots:

private slots:
    /**
     * @brief editFinish
     */
    void editFinish();

    /**
     * @brief addEdit
     */
    void addEdit();

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
    Model::Employee *m_employeeModel = {};

    /*!
     * @brief m_model
     */
    QSqlTableModel *m_model;

    /*!
     * @brief m_selectionModel
     */
    QItemSelectionModel *m_selectionModel{};

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
     * @brief deleteDataset
     * @param index Delete the data for the ModelIndex
     */
    void deleteDataset(const QModelIndex &index);
};
