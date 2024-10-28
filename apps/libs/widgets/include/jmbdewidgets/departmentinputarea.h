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

#include "jmbdemodels/datacontext.h"
#include "jmbdemodels/department.h"
#include "jmbdewidgets_export.h"

namespace Ui {
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
  explicit DepartmentInputArea(QWidget *parent = nullptr, const QModelIndex &index = QModelIndex());

  /**
   * @brief ~DepartmentInputArea();
   */
  ~DepartmentInputArea();

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
  Ui::DepartmentInputArea *ui;

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
  Model::Department *m_departmentModel = {};

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
