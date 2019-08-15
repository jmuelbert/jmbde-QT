/**************************************************************************
**
** Copyright (c) 2013-2019 Jürgen Mülbert. All rights reserved.
**
** This file is part of jmbde
**
** Licensed under the EUPL, Version 1.2 or – as soon they
** will be approved by the European Commission - subsequent
** versions of the EUPL (the "Licence");
** You may not use this work except in compliance with the
** Licence.
** You may obtain a copy of the Licence at:
**
** https://joinup.ec.europa.eu/page/eupl-text-11-12
**
** Unless required by applicable law or agreed to in
** writing, software distributed under the Licence is
** distributed on an "AS IS" basis,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
** express or implied.
** See the Licence for the specific language governing
** permissions and limitations under the Licence.
**
** Lizenziert unter der EUPL, Version 1.2 oder - sobald
**  diese von der Europäischen Kommission genehmigt wurden -
** Folgeversionen der EUPL ("Lizenz");
** Sie dürfen dieses Werk ausschließlich gemäß
** dieser Lizenz nutzen.
** Eine Kopie der Lizenz finden Sie hier:
**
** https://joinup.ec.europa.eu/page/eupl-text-11-12
**
** Sofern nicht durch anwendbare Rechtsvorschriften
** gefordert oder in schriftlicher Form vereinbart, wird
** die unter der Lizenz verbreitete Software "so wie sie
** ist", OHNE JEGLICHE GEWÄHRLEISTUNG ODER BEDINGUNGEN -
** ausdrücklich oder stillschweigend - verbreitet.
** Die sprachspezifischen Genehmigungen und Beschränkungen
** unter der Lizenz sind dem Lizenztext zu entnehmen.
**
**************************************************************************/

#pragma once

#include <QDebug>
#include <QFile>

#include <QStandardPaths>

#include <QStandardItemModel>
#include <QString>
#include <QTextStream>

#include <QDialog>
#include <QFileDialog>

#include "jmbde_common_export.h"

namespace Ui {
class JMBDE_COMMON_EXPORT CsvImportDialog;
}

/**
 * @brief The CsvImportDialog class
 */
class JMBDE_COMMON_EXPORT CsvImportDialog : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief CsvImportDialog::CsvImportDialog
     * @param parent
     */
    explicit CsvImportDialog(QWidget *parent = nullptr);

    /**
     * @brief CsvImportDialog::~CsvImportDialog
     */
    ~CsvImportDialog();

private:
    Ui::CsvImportDialog *ui;
    QList<QStringList> csv;
    QStandardItemModel *model;

    QList<QStandardItem *> standardItemList;

private slots:

    /**
     * @brief CsvImportDialog::checkString
     * @param temp
     * @param character
     */
    void checkString(QString &temp, QChar character = 0);

    /**
     * @brief CsvImportDialog::on_buttonBox_accepted
     */
    void on_buttonBox_accepted();
};
