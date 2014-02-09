/*
 * EmployeeInputDialog.h
 * jmbde
 *
 * Copyright (c) 2013,2013 Jürgen Mülbert. All rights reserved.
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


#include <QDialog>
#include <QSqlRelationalDelegate>
#include <QDataWidgetMapper>

#include "employeedatamodel.h"

namespace Ui {
class EmployeeInputDialog;
}

/**
 * @brief The EmployeeInputDialog class
 */
class EmployeeInputDialog :  public QDialog

{
    Q_OBJECT

public:
     EmployeeInputDialog(QWidget *parent = 0);
    ~EmployeeInputDialog();

private slots:
    void on_buttonBox_accepted();

    void on_nextButton_clicked();

    void on_previousButton_clicked();

    void on_buttonBox_rejected();

    void on_pushButtonNew_clicked();

private:
    void setupModel();
    void addRow(QAbstractTableModel *model);


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
};

#endif // EMPLOYEEINPUTDIALOG_H
