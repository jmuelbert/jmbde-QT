/**************************************************************************
**
** Copyright (c) 2013-2018 Jürgen Mülbert. All rights reserved.
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

#include "definitions.h"
#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"

PreferencesDialog::PreferencesDialog(QWidget* parent)
  : QDialog(parent), ui(new Ui::PreferencesDialog) {
  ui->setupUi(this);
  ui->comboBoxDatabaseType->addItem(QLatin1String(Database::Type::SQLITE));
  ui->comboBoxDatabaseType->addItem(QLatin1String(Database::Type::MYSQL));
  ui->comboBoxDatabaseType->addItem(QLatin1String(Database::Type::ODBC));
  ui->comboBoxDatabaseType->addItem(QLatin1String(Database::Type::POSTGRESQL));
  readSettings();
}

PreferencesDialog::~PreferencesDialog() {
  delete ui;
}

void PreferencesDialog::writeSettings() {
  QSettings settings;

  settings.beginGroup(QLatin1String(Settings::Groups::MAINWINDOW));
  settings.setValue(QLatin1String(Settings::MainWindow::SIZE), size());
  settings.setValue(QLatin1String(Settings::MainWindow::POS), pos());
  settings.endGroup();
  settings.beginGroup(QLatin1String(Settings::Groups::DATABASE));
  settings.setValue(QLatin1String(Settings::Database::TYPE),
                    ui->comboBoxDatabaseType->currentIndex());
  QString dbConnectionString = ui->lineEditDatabaseConnection->text();

  if (dbConnectionString.length() < 2) {
    dbConnectionString = this->getUserDataDir();
  }

  settings.setValue(QLatin1String(Settings::Database::CONNECTION),
                    dbConnectionString);
  settings.setValue(QLatin1String(Settings::Database::HOSTNAME),
                    ui->lineEditHostName->text());
  settings.setValue(QLatin1String(Settings::Database::USERNAME),
                    ui->lineEditUserName->text());
  settings.setValue(QLatin1String(Settings::Database::PASSWORD),
                    ui->lineEditPassword->text());
  settings.endGroup();
}

void PreferencesDialog::readSettings() {
  QSettings settings;

  settings.beginGroup(QLatin1String(Settings::Groups::MAINWINDOW));
  resize(
    settings.value(QLatin1String(Settings::MainWindow::SIZE), QSize(400, 400))
    .toSize());
  move(
    settings.value(QLatin1String(Settings::MainWindow::POS), QPoint(200, 200))
    .toPoint());
  settings.endGroup();
  settings.beginGroup(QLatin1String(Settings::Groups::DATABASE));
  ui->comboBoxDatabaseType->setCurrentIndex(
    settings.value(QLatin1String(Settings::Database::TYPE), SQLITE).toInt());
  ui->lineEditDatabaseConnection->setText(
    settings
    .value(QLatin1String(Settings::Database::CONNECTION),
           this->getUserDataDir())
    .toString());
  ui->lineEditHostName->setText(
    settings
    .value(QLatin1String(Settings::Database::HOSTNAME),
           QLatin1String("localhost"))
    .toString());
  ui->lineEditUserName->setText(
    settings
    .value(QLatin1String(Settings::Database::USERNAME),
           QLatin1String("jmbde"))
    .toString());
  ui->lineEditPassword->setText(
    settings
    .value(QLatin1String(Settings::Database::PASSWORD),
           QLatin1String("jmbde"))
    .toString());
}

void PreferencesDialog::on_pushButtonDBForceFileDialog_clicked() {
  QString dbDir = QFileDialog::getExistingDirectory(
    this, tr("Select Directory for Database"), this->getUserDataDir());

  if (dbDir.length() > 2) {
    ui->lineEditDatabaseConnection->setText(dbDir);
  }
}

QString PreferencesDialog::getUserDataDir() {

  QString dataBaseDir =
    QStandardPaths::writableLocation(QStandardPaths::DataLocation);

  return dataBaseDir;
}

void PreferencesDialog::on_buttonBox_accepted() {
  writeSettings();
}
