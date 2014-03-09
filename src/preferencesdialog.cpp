/*
 * preferencesdialog.cpp
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

#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"
#include "constants.h"


PreferencesDialog::PreferencesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferencesDialog)
{
    ui->setupUi(this);
    ui->comboBoxDatabaseType->addItem(QLatin1String(Database::Type::SQLITE));
    ui->comboBoxDatabaseType->addItem(QLatin1String(Database::Type::MYSQL));
    ui->comboBoxDatabaseType->addItem(QLatin1String(Database::Type::ODBC));
    ui->comboBoxDatabaseType->addItem(QLatin1String(Database::Type::POSTGRESQL));
    readSettings();
}


PreferencesDialog::~PreferencesDialog()
{
    delete ui;
}

void PreferencesDialog::writeSettings()
{
    QString CompanyName = QLatin1String(Constants::COMPANY_NAME);
    QString ApplicationName = QLatin1String(Constants::APPL_NAME);
    QSettings settings(CompanyName, ApplicationName);
    settings.beginGroup(QLatin1String(Settings::Groups::MAINWINDOW));
    settings.setValue(QLatin1String(Settings::MainWindow::SIZE), size());
    settings.setValue(QLatin1String(Settings::MainWindow::POS), pos());
    settings.endGroup();
    settings.beginGroup(QLatin1String(Settings::Groups::DATABASE));
    settings.setValue(QLatin1String(Settings::Database::TYPE),ui->comboBoxDatabaseType->currentIndex());
    QString dbConnectionString = ui->lineEditDatabaseConnection->text();
    if (dbConnectionString.length() < 2) {
        dbConnectionString = this->getUserDataDir();
    }
    settings.setValue(QLatin1String(Settings::Database::CONNECTION), dbConnectionString);
    settings.setValue(QLatin1String(Settings::Database::HOSTNAME), ui->lineEditHostName->text());
    settings.setValue(QLatin1String(Settings::Database::USERNAME), ui->lineEditUserName->text());
    settings.setValue(QLatin1String(Settings::Database::PASSWORD), ui->lineEditPassword->text());
    settings.endGroup();
}

void PreferencesDialog::readSettings()
{
    QString CompanyName = QLatin1String(Constants::COMPANY_NAME);
    QString ApplicationName = QLatin1String(Constants::APPL_NAME);
    QSettings settings(CompanyName, ApplicationName);
    settings.beginGroup(QLatin1String(Settings::Groups::MAINWINDOW));
    resize(settings.value(QLatin1String(Settings::MainWindow::SIZE),QSize(400,400)).toSize());
    move(settings.value(QLatin1String(Settings::MainWindow::POS), QPoint(200,200)).toPoint());
    settings.endGroup();
    settings.beginGroup(QLatin1String(Settings::Groups::DATABASE));
    ui->comboBoxDatabaseType->setCurrentIndex(settings.value(QLatin1String(Settings::Database::TYPE), SQLITE).toInt());
    ui->lineEditDatabaseConnection->setText(settings.value(QLatin1String(Settings::Database::CONNECTION), this->getUserDataDir() ).toString());
    ui->lineEditHostName->setText(settings.value(QLatin1String(Settings::Database::HOSTNAME), QLatin1String("localhost")).toString());
    ui->lineEditUserName->setText(settings.value(QLatin1String(Settings::Database::USERNAME), QLatin1String("jmbde")).toString());
    ui->lineEditPassword->setText(settings.value(QLatin1String(Settings::Database::PASSWORD),QLatin1String("jmbde")).toString());

}

void PreferencesDialog::on_pushButtonDBForceFileDialog_clicked()
{
    QString dbDir = QFileDialog::getExistingDirectory ( this, tr("Select Directory for Database"), this->getUserDataDir());

    if (dbDir.length() >2) {
        ui->lineEditDatabaseConnection->setText(dbDir);
    }
}

QString PreferencesDialog::getUserDataDir() {
#if QT_VERSION >= 0x050000
            QString dataBaseDir = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
#else
            QString dataBaseDir = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
#endif
        return dataBaseDir;
}

void PreferencesDialog::on_buttonBox_accepted()
{
    writeSettings();
}
