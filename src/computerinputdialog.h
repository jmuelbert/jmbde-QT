/*
 * ComputerInputDialog.h
 * jmbde
 *
 * Copyright (c) 2013-2017 Jürgen Mülbert. All rights reserved.
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

#include <QDataWidgetMapper>
#include <QDialog>
#include <QSqlRelationalDelegate>

#include "computerdatamodel.h"

namespace Ui {
class ComputerInputDialog;
}

class ComputerInputDialog : public QDialog {
  Q_OBJECT

public:
  explicit ComputerInputDialog(QWidget *parent = 0);
  ComputerInputDialog(QWidget *parent, int index = 0);

  ~ComputerInputDialog();

private slots:

  void on_buttonBox_accepted();

  void on_buttonBox_rejected();

private:
  Ui::ComputerInputDialog *ui;

  QSqlRelationalTableModel *model;
  QItemSelectionModel *selectionModel;
  QDataWidgetMapper *mapper;
};

#endif // COMPUTERINPUTDIALOG_H
