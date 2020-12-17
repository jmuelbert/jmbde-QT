/*
    jmbde a BDE Tool for companies
    Copyright (C) 2013-2019  Jürgen Mülbert

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

#include "views/csvimportdialog.h"

#include "ui_csvimportdialog.h"

Q_LOGGING_CATEGORY(jmbdeWidgetsCsvInputDialogLog, "jmuelbert.jmbde.widgets.csvinputdialog", QtWarningMsg)

CsvImportDialog::CsvImportDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CsvImportDialog)
{
    ui->setupUi(this);
    model = new QStandardItemModel(this);
    ui->tableView->setModel(model);

    QStringList dataDirList = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);

    // Use user space
    const QString &dataBaseDirAndFile = dataDirList.at(0);

    QString fileName = QFileDialog::getOpenFileName(nullptr, tr("open CSV file"), dataBaseDirAndFile, QLatin1String("CSV (*.csv)"));
    QFile file(fileName);

    if (file.open(QFile::Text | QIODevice::ReadOnly)) {
        QString data = QLatin1String(file.readAll());

        data.remove(QRegularExpression(QLatin1String("\r")));
        QString temp;
        QChar character;
        QTextStream textStream(&data);

        while (!textStream.atEnd()) {
            textStream >> character;
            if (character == QLatin1Char(',')) {
                checkString(temp, character);
            } else if (character == QLatin1Char(';')) {
                character = QLatin1Char(',');
                checkString(temp, character);
            } else if (character == QLatin1Char('\n')) {
                checkString(temp, character);
            } else if (textStream.atEnd()) {
                temp.append(character);
                checkString(temp);
            } else {
                temp.append(character);
            }
        }
    }
}

CsvImportDialog::~CsvImportDialog()
{
    delete ui;
}

void CsvImportDialog::checkString(QString &temp, QChar character)
{
    if (temp.count(QLatin1String("\"")) % 2 == 0) {
        if (temp.startsWith(QLatin1Char('\"')) && temp.endsWith(QLatin1Char('\"'))) {
            temp.remove(QRegularExpression(QLatin1String("^\"")));
            temp.remove(QRegularExpression(QLatin1String("\"$")));
        }

        // FIXME: will possibly fail if there are 4 or more reapeating double
        // quotes
        temp.replace(QLatin1String("\"\""), QLatin1String("\""));
        auto *item = new QStandardItem(temp);

        standardItemList.append(item);
        if (character != QLatin1Char(',')) {
            model->appendRow(standardItemList);
            standardItemList.clear();
        }

        temp.clear();
    } else {
        temp.append(character);
    }
}

void CsvImportDialog::on_buttonBox_accepted()
{
    int columnCount = model->columnCount();
    int rowCount = model->rowCount();

    qCDebug(jmbdeWidgetsCsvInputDialogLog) << "Columns : " << columnCount << " Rows : " << rowCount;
    QString tempString;

    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < columnCount; j++) {
            QModelIndex ind(model->index(i, j));

            tempString.append(ind.data(Qt::DisplayRole).toString() + QLatin1String(", "));
        }

        qCDebug(jmbdeWidgetsCsvInputDialogLog) << "SqlState : " << tempString;
        tempString.clear();
    }
}
