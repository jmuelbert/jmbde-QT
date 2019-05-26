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

#include "csvimportdialog.h"
#include "ui_csvimportdialog.h"

CsvImportDialog::CsvImportDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::CsvImportDialog) {
  ui->setupUi(this);
  model = new QStandardItemModel(this);
  ui->tableView->setModel(model);

#if QT_VERSION >= 0x050000
  QStringList dataDirList =
      QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);

  // Use user space
  QString dataBaseDirAndFile = dataDirList.at(0);
#else
  QString dataBaseDirAndFile = QDir::homePath();
#endif

  QString fileName = QFileDialog::getOpenFileName(
      0, tr("open CSV file"), dataBaseDirAndFile, QLatin1String("CSV (*.csv)"));
  QFile file(fileName);

  if (file.open(QFile::Text | QIODevice::ReadOnly)) {
    QString data = QLatin1String(file.readAll());

    data.remove(QRegExp(QLatin1String("\r")));
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

CsvImportDialog::~CsvImportDialog() { delete ui; }

void CsvImportDialog::checkString(QString &temp, QChar character) {
  if (temp.count(QLatin1String("\"")) % 2 == 0) {
    if (temp.startsWith(QLatin1Char('\"')) &&
        temp.endsWith(QLatin1Char('\"'))) {
      temp.remove(QRegExp(QLatin1String("^\"")));
      temp.remove(QRegExp(QLatin1String("\"$")));
    }

    // FIXME: will possibly fail if there are 4 or more reapeating double
    // quotes
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

void CsvImportDialog::on_buttonBox_accepted() {
  int columnCount = model->columnCount();
  int rowCount = model->rowCount();

  qDebug() << "Columns : " << columnCount << " Rows : " << rowCount;
  QString tempString;

  for (int i = 0; i < rowCount; i++) {
    for (int j = 0; j < columnCount; j++) {
      QModelIndex ind(model->index(i, j));

      tempString.append(ind.data(Qt::DisplayRole).toString() +
                        QLatin1String(", "));
    }

    qDebug() << "SqlState : " << tempString;
    tempString.clear();
  }
}
