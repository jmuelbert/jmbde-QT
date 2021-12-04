/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include <QDebug>
#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QLoggingCategory>
#include <QStandardItemModel>
#include <QStandardPaths>
#include <QString>
#include <QTextStream>

#include "jmbdewidgets-version.h"
#include "jmbdewidgets_export.h"

Q_DECLARE_LOGGING_CATEGORY(m_AboutDialogLog)
namespace Ui
{
class AboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = nullptr);
    ~AboutDialog();

private:
    Ui::AboutDialog *ui;

    /*!
     * Logging Category
     */
    QLoggingCategory m_AboutDialogLog;
};
