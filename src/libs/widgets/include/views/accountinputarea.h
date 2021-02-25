/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
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

#include "jmbdewidgets-version.h"
#include "jmbdewidgets_export.h"
#include "models/account.h"
#include "models/datacontext.h"

Q_DECLARE_LOGGING_CATEGORY(jmbdeWidgetsAccountInputAreaLog)

namespace Ui
{
class AccountInputArea;
}

/**
 * @brief The AccountInputArea class
 */
class JMBDEWIDGETS_EXPORT AccountInputArea : public QGroupBox

{
    Q_OBJECT

public:
    /*!
        @brief AccountInputArea
        @param tableName The name of the table in the Database
        @param The pointer to the Model
        @param parent The pointer to the parent object

        @todo Init the model from here
        @todo Get the tableName from the model
     */
    explicit AccountInputArea(QWidget *parent = nullptr, const QModelIndex &index = QModelIndex());

    /**
     * @brief ~AccountInputArea
     */
    ~AccountInputArea();

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
    Ui::AccountInputArea *ui;

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
    Model::Account *m_accountModel = {};

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
