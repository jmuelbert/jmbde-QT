/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include <QDataWidgetMapper>
#include <QDebug>
#include <QGroupBox>
#include <QMessageBox>
#include <QSqlRelationalDelegate>
#include <QtSql>

#include "jmbdewidgets-version.h"
#include "jmbdewidgets_export.h"
#include "models/computer.h"
#include "models/datacontext.h"

Q_DECLARE_LOGGING_CATEGORY(jmbdeWidgetsComputerInputAreaLog)

namespace Ui
{
class ComputerInputArea;
}

/**
 * @brief The ComputerInputArea class
 */
class JMBDEWIDGETS_EXPORT ComputerInputArea : public QGroupBox
{
    Q_OBJECT

public:
    /**
       @brief ComputerInputArea
       @param parent The pointer to the parent object
       @param index The index for view the data
     */
    explicit ComputerInputArea(QWidget *parent = nullptr, const QModelIndex &index = QModelIndex());

    /**
     * @brief ~ComputerInputArea();
     */
    ~ComputerInputArea();

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
    /**
     * @brief ui
     */
    Ui::ComputerInputArea *ui;

    /**
     * @brief The Mode enum
     */
    enum Mode { Edit, Finish };

    /**
     * @brief m_actualMode
     */
    Mode m_actualMode;

    /*!
     * @brief m_dataContext
     */
    Model::Computer *m_computerModel = {};

    /**
     * @brief m_model
     */
    QSqlRelationalTableModel *m_model;

    /**
     * @brief m_selectionModel
     */
    QItemSelectionModel *m_selectionModel{};

    /**
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
