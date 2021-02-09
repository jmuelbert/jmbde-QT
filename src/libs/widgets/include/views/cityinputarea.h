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
#include "models/cityname.h"
#include "models/datacontext.h"

Q_DECLARE_LOGGING_CATEGORY(jmbdeWidgetsCityInputAreaLog)

namespace Ui {
class CityInputArea;
}

/**
 * @brief The CityInputArea class
 */
class JMBDEWIDGETS_EXPORT CityInputArea : public QGroupBox {
    Q_OBJECT

public:
    /**
     * @brief CityInputArea
       @param parent The pointer to the parent object
       @param index The index for view the data
     */
    explicit CityInputArea(QWidget* parent = nullptr, const QModelIndex& index = QModelIndex());

    /**
     * @brief ~CityInputArea
     */
    ~CityInputArea();

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
    Ui::CityInputArea* ui;

    /**
     * @brief The Mode enum
     */
    enum Mode { Edit,
        Finish };

    /**
     * @brief m_actualMode
     */
    Mode m_actualMode;

    /*!
     * @brief m_dataContext
     */
    Model::CityName* m_cityNameModel = {};

    /**
     * @brief m_model
     */
    QSqlRelationalTableModel* m_model;

    /**
     * @brief m_selectionModel
     */
    QItemSelectionModel* m_selectionModel {};

    /**
     * @brief m_mapper
     */
    QDataWidgetMapper* m_mapper;

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
