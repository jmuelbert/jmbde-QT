/*
 *  SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include <QDebug>
#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QLoggingCategory>
#include <QRegularExpression>
#include <QStandardItemModel>
#include <QStandardPaths>
#include <QString>
#include <QTextStream>

#include "jmbdewidgets_export.h"

namespace Ui {
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

private slots:

  /**
   * @brief CsvImportDialog::checkString
   * @param temp Check the String
   * @param character The character to checking
   */
  void checkString(QString &temp, QChar character = QChar(' '));

  /**
   * @brief CsvImportDialog::on_buttonBox_accepted
   */
  void on_buttonBox_accepted();

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
};
