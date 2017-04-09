/*
 * preferencesdialog.h
 * jmbde
 *
 *  Copyright (c) 2013-2017 Jürgen Mülbert. All rights reserved.
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

#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QObject>
#if QT_VERSION >= 0x050000
#include <QStandardPaths>
#else
#include <QDesktopServices>
#endif

#include <QDebug>
#include <QDialog>
#include <QFileDialog>
#include <QSettings>

namespace Ui {
class PreferencesDialog;
}

/**
 * @brief The PreferencesDialog class
 */
class PreferencesDialog : public QDialog {
  Q_OBJECT

public:
  /**
   * @brief PreferencesDialog::PreferencesDialog
   * @param parent
   */
  explicit PreferencesDialog(QWidget *parent = 0);

  /**
   * @brief PreferencesDialog::~PreferencesDialog
   */
  ~PreferencesDialog();

private slots:
  /**
   * @brief on_pushButtonDBForceFileDialog_clicked
   */
  void on_pushButtonDBForceFileDialog_clicked();

  /**
   * @brief on_buttonBox_accepted
   */
  void on_buttonBox_accepted();

private:
  /**
   * @brief ui
   */
  Ui::PreferencesDialog *ui;

  /**
   * @brief readSettings
   */
  void readSettings();

  /**
   * @brief writeSettings
   */
  void writeSettings();

  /**
   * @brief getUserDataDir
   * @return
   */
  QString getUserDataDir();
};

#endif // PREFERENCESDIALOG_H
