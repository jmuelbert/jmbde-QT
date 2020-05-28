/*
   jmbde a BDE Tool for companies
   Copyright (C) 2020  Jürgen Mülbert

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

#include <QObject>

#include <QLoggingCategory>

#include <QDialogButtonBox>
#include <QMessageBox>
#include <QPushButton>
#include <QWidget>
#include <QtSql>

#include "jmbdewidgets-version.h"
#include "jmbdewidgets_export.h"

Q_DECLARE_LOGGING_CATEGORY(jmbdeWidgetsEmployeeTableLog)

namespace Ui
{
class EmployeeTable;
}

class EmployeeTable : public QWidget
{
    Q_OBJECT

public:
    explicit EmployeeTable(const QString &tableName, QSqlTableModel *model, QWidget *parent = nullptr);
    ~EmployeeTable();

private:
    Ui::EmployeeTable *ui;
    QPushButton *submitButton;
    QPushButton *revertButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonBox;
    QSqlTableModel *m_model;

private slots:
    void submit();
};
