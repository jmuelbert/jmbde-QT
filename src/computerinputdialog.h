/*
 * ComputerInputDialog.h
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

#ifndef COMPUTERINPUTDIALOG_H
#define COMPUTERINPUTDIALOG_H

#include <QDialog>
#include <QSqlRelationalDelegate>
#include <QDataWidgetMapper>

#include "computerdatamodel.h"

namespace Ui {
class ComputerInputDialog;
}


/**
 * @brief The ComputerInputDialog class
 * @details Input for ComputerData
 * @author Jürgen Mülbert
 * @version 0.3
 * @date 18.08.2016
 * @copyright EUPL V1.1
 */
class ComputerInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ComputerInputDialog(QWidget *parent = 0);
    ~ComputerInputDialog();

private slots:


    void on_pushButtonPrevious_clicked();

    void on_pushButtonNext_clicked();

private:
    Ui::ComputerInputDialog *ui;

    QSqlRelationalTableModel *model;
    QItemSelectionModel *selectionModel;
    QDataWidgetMapper *mapper;

};

#endif // COMPUTERINPUTDIALOG_H
