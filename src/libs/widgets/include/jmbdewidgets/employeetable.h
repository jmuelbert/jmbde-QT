/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include <QDataWidgetMapper>
#include <QDialogButtonBox>
#include <QLoggingCategory>
#include <QMessageBox>
#include <QObject>
#include <QPushButton>
#include <QSqlRelationalDelegate>
#include <QWidget>
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
class EmployeeTable;
}

/**
 * @brief The EmployeeTable class
 */
class EmployeeTable : public QWidget
{
    Q_OBJECT

public:
    /*!
        @brief EmployeeTable
        @param tableName The name of the table in the Database
        @param The pointer to the Model
        @param parent The pointer to the parent object

        @todo Init the model from here
        @todo Get the tableName from the model
     */
    explicit EmployeeTable(QWidget *parent = nullptr, const QModelIndex &index = QModelIndex());

    /*!
        @brief The destructor
    */
    ~EmployeeTable();

signals:
    /*!
        @brief dataChanged
     */
    void dataChanged();

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

    /*!
     * \brief submit
     */
    void submit();

private:
    /*!
     * @brief ui
     */
    Ui::EmployeeTable *ui;

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

    /*!
     * \brief submitButton
     */
    QPushButton *submitButton;

    /*!
     * \brief revertButton
     */
    QPushButton *revertButton;

    /*!
     * \brief quitButton
     */
    QPushButton *quitButton;

    /*!
     * \brief buttonBox
     */
    QDialogButtonBox *buttonBox;

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
