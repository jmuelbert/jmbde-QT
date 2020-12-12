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
};
