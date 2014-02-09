/*
 * CsvImportDialog.h
 * jmbde
 *
 * Copyright (c) 2013,2014 Jürgen Mülbert. All rights reserved.
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


#ifndef CSVIMPORTDIALOG_H
#define CSVIMPORTDIALOG_H



#include <QDebug>
#include <QFile>
#if QT_VERSION >= 0x050000
#include <QStandardPaths>
#endif
#include <QString>
#include <QTextStream>
#include <QStandardItemModel>

#include <QDialog>
#include <QFileDialog>

/**
 *
 */
namespace Ui {
class CsvImportDialog;
}

/**
 * @brief The CsvImportDialog class
 */
class CsvImportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CsvImportDialog(QWidget *parent = 0);
    ~CsvImportDialog();

private:
    Ui::CsvImportDialog *ui;
    QList<QStringList> csv;
    QStandardItemModel *model;
    QList<QStandardItem*> standardItemList;

private slots:
    void checkString(QString &temp, QChar character = 0);

    void on_buttonBox_accepted();
};

#endif // CSVIMPORTDIALOG_H
