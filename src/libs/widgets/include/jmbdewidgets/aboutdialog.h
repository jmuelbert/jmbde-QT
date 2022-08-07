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
#include <QObject>
#include <QStandardItemModel>
#include <QStandardPaths>
#include <QString>
#include <QTextStream>

#include "jmbdewidgets_export.h"

namespace Ui {
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
};
