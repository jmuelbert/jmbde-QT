/*
   jmbde a BDE Tool for companies
   Copyright (C) 2020 Jürgen Mülbert

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
*/

#include "views/employeetable.h"
#include "ui_employeetable.h"

Q_LOGGING_CATEGORY(jmbdeWidgetsEmployeeTableLog, "jmuelbert.jmbde.widgets.employeetable", QtWarningMsg)

EmployeeTable::EmployeeTable(const QString &tableName, QSqlTableModel *model, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EmployeeTable)
    , m_model(model)
{
    ui->setupUi(this);

    // Set the Model
    m_model = new QSqlRelationalTableModel(this);
    m_model->setTable(QLatin1String("employee"));
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    m_model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    m_model->setHeaderData(1, Qt::Horizontal, tr("First name"));
    m_model->setHeaderData(2, Qt::Horizontal, tr("Last name"));

    ui->tableView->setModel(m_model);
    ui->tableView->resizeColumnsToContents();

    submitButton = new QPushButton(tr("Submit"));
    submitButton->setDefault(true);
    revertButton = new QPushButton(tr("&Revert"));
    quitButton = new QPushButton(tr("Quit"));

    buttonBox = new QDialogButtonBox(Qt::Vertical);
    buttonBox->addButton(submitButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(revertButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

    ui->verticalLayout->addWidget(buttonBox);

    connect(submitButton, &QPushButton::clicked, this, &EmployeeTable::submit);
    connect(revertButton, &QPushButton::clicked, model, &QSqlTableModel::revertAll);
    // connect(quitButton, &QPushButton::clicked, this, &EmployeeTable::close);
}

EmployeeTable::~EmployeeTable()
{
    delete ui;
}

void EmployeeTable ::submit()
{
    m_model->database().transaction();
    if (m_model->submitAll()) {
        m_model->database().commit();
    } else {
        m_model->database().rollback();
        QMessageBox::warning(this, tr("jmbde"), tr("Die Datenbank meldet den Fehler: %1").arg(m_model->lastError().text()));
    }
}
