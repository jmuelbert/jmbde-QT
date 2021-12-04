/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include <QDataWidgetMapper>
#include <QDialog>
#include <QFileDialog>
#include <QGroupBox>
#include <QLoggingCategory>
#include <QMessageBox>
#include <QObject>
#include <QSqlRelationalDelegate>
#include <QtSql>

#include "jmbdewidgets-version.h"
#include "jmbdewidgets_export.h"

#include <QLoggingCategory>

#include <QSettings>

#include "definitions.h"
#include <QStandardPaths>

Q_DECLARE_LOGGING_CATEGORY(m_PreferencesDialogLog)

namespace Ui
{
class PreferencesDialog;
}

/**
 * @brief The PreferencesDialog class
 */
class PreferencesDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief PreferencesDialog::PreferencesDialog
     * @param parent
     */
    explicit PreferencesDialog(QWidget *paret = nullptr);

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
    static auto getUserDataDir() -> QString;

    /*!
     * Logging Category
     */
    QLoggingCategory m_PreferencesDialogLog;
};
