/*
 * EmployeeInputDialog.h
 * jmbde
 *
 * Copyright (c) 2013-2017 Jürgen Mülbert. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the European Union Public Licence (EUPL),
 * version 1.1.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * European Union Public Licence for more details.
 *
 * You should have received a copy of the European Union Public Licence
 * along with this program. If not, see
 * http://www.osor.eu/eupl/european-union-public-licence-eupl-v.1.1
 *
 */

#ifndef EMPLOYEEINPUTDIALOG_H
#define EMPLOYEEINPUTDIALOG_H

#include <QDataWidgetMapper>
#include <QDialog>
#include <QSqlRelationalDelegate>

#include "employeedatamodel.h"
#include "phonedatamodel.h"

namespace Ui {
class EmployeeInputDialog;
}

/**
 * @brief The EmployeeInputDialog class
 */
class EmployeeInputDialog : public QDialog

{
  Q_OBJECT

public:
  /**
   * @brief EmployeeInputDialog::EmployeeInputDialog
   * @param parent
   */
  EmployeeInputDialog(QWidget *parent = 0);

  EmployeeInputDialog(QWidget *parent, int index = 0);

  /**
   * @brief EmployeeInputDialog::~EmployeeInputDialog
   */
  ~EmployeeInputDialog();

private slots:

  /**
   * @brief EmployeeInputDialog::on_buttonBox_accepted
   */
  void on_buttonBox_accepted();

  /**
   * @brief on_buttonBox_rejected
   */
  void on_buttonBox_rejected();

private:
  int departmentIndex;
  int functionIndex;
  int computerIndex;
  int printerIndex;
  int phoneIndex;
  int mobileIndex;
  int faxIndex;

  // QSqlRelationalTableModel *model;
  QSqlTableModel *model;
  QItemSelectionModel *selectionModel;
  QDataWidgetMapper *mapper;

  Ui::EmployeeInputDialog *ui;

  void preSetFields(bool newEmployee);
  void setMappings(QSqlTableModel *model, QDataWidgetMapper *mapper);
};

#endif // EMPLOYEEINPUTDIALOG_H
