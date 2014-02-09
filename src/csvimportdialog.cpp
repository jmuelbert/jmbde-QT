/*
 * csvimportdialog.cpp
 * jmbde
 *
 *  Copyright (c) 2013,2014 Jürgen Mülbert. All rights reserved.
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

#include "csvimportdialog.h"
#include "ui_csvimportdialog.h"

/**
 * @brief CsvImportDialog::CsvImportDialog
 * @param parent
 */
CsvImportDialog::CsvImportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CsvImportDialog)
{
    ui->setupUi(this);
    model = new QStandardItemModel(this);
    ui->tableView->setModel(model);

#if QT_VERSION >= 0x050000
    QStringList dataDirList = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    // Use user space

    QString dataBaseDirAndFile = dataDirList.at(0);
#else
    QString dataBaseDirAndFile =QDir::homePath();
#endif

    QString fileName = QFileDialog::getOpenFileName(0, tr("open CSV file"),
                                                    dataBaseDirAndFile,
                                                    QLatin1String("CSV (*.csv)"));
    QFile file (fileName);
    if (file.open(QFile::Text | QIODevice::ReadOnly)) {
        QString data = QLatin1String(file.readAll());
        data.remove( QRegExp(QLatin1String("\r")));
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

/**
 * @brief CsvImportDialog::~CsvImportDialog
 */
CsvImportDialog::~CsvImportDialog()
{
    delete ui;
}

/**
 * @brief CsvImportDialog::checkString
 * @param temp
 * @param character
 */
void CsvImportDialog::checkString(QString &temp, QChar character)
{
    if (temp.count(QLatin1String("\"")) %2 == 0) {
        if (temp.startsWith( QLatin1Char ('\"')) && temp.endsWith( QLatin1Char ('\"'))) {
            temp.remove( QRegExp(QLatin1String("^\"")));
            temp.remove( QRegExp(QLatin1String("\"$")));
        }
        // FIXME: will possibly fail if there are 4 or more reapeating double quotes
        temp.replace(QLatin1String("\"\""), QLatin1String("\""));
        QStandardItem *item = new QStandardItem(temp);
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

/**
 * @brief CsvImportDialog::on_buttonBox_accepted
 */
void CsvImportDialog::on_buttonBox_accepted()
{
    int columnCount = model->columnCount();
    int rowCount = model->rowCount();
    qDebug() << "Columns : " << columnCount << " Rows : " << rowCount;
    QString tempString;
    for (int i=0; i<rowCount; i++) {
        for (int j=0; j<columnCount; j++) {
            QModelIndex ind(model->index(i, j));
            tempString.append(ind.data(Qt::DisplayRole).toString() + QLatin1String(", "));
        }
        qDebug() << "SqlState : " << tempString;
        tempString.clear();
    }
}
