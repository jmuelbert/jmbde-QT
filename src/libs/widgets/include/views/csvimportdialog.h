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

#include <QDebug>
#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QStandardPaths>
#include <QString>
#include <QTextStream>

#include "jmbdewidgets-version.h"
#include "jmbdewidgets_export.h"
#include "loggingcategory.h"

namespace Ui
{
class CsvImportDialog;
}

/**
 * @brief The CsvImportDialog class
 */
class JMBDEWIDGETS_EXPORT CsvImportDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief CsvImportDialog::CsvImportDialog
       @param parent The pointer to the parent object
     */
    explicit CsvImportDialog(QWidget *parent = nullptr);

    /**
     * @brief CsvImportDialog::~CsvImportDialog
     */
    ~CsvImportDialog();

private:
    /**
     * @brief ui
     */
    Ui::CsvImportDialog *ui;

    /**
     * @brief csv
     */
    QList<QStringList> csv;

    /**
     * @brief model
     */
    QStandardItemModel *model;

    /**
     * @brief standardItemList
     */
    QList<QStandardItem *> standardItemList;

private slots:

    /**
     * @brief CsvImportDialog::checkString
     * @param temp Check the String
     * @param character The character to checking
     */
    void checkString(QString &temp, QChar character = 0);

    /**
     * @brief CsvImportDialog::on_buttonBox_accepted
     */
    void on_buttonBox_accepted();
};
