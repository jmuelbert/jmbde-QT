/*
 *  SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "jmbdewidgets/preferencesdialog.h"
#include "ui_preferencesdialog.h"

PreferencesDialog::PreferencesDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PreferencesDialog)
{
    ui->setupUi(this);

    qDebug() << "Init the Preferences Dialog";

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
    QSettings settings;

    settings.beginGroup(QLatin1String(Settings::Groups::WINDOWSSTATE));
    // settings.setValue(QLatin1String(Settings::WindowState::WINDOW_X), ui->centralWidget->x());
    // settings.setValue(QLatin1String(Settings::WindowState::WINDOW_Y), ui->centralWidget->y());
    // settings.setValue(QLatin1String(Settings::WindowState::WINDOW_WIDTH), ui->centralWidget->width());
    // settings.setValue(QLatin1String(Settings::WindowState::WINDOW_HEIGHT), ui->centralWidget->height());
    settings.endGroup();

    settings.beginGroup(QLatin1String(Settings::Groups::DATABASE));
    settings.setValue(QLatin1String(Settings::Database::TYPE), ui->comboBoxDatabaseType->currentIndex());
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
    QSettings settings;

    settings.beginGroup(QLatin1String(Settings::Groups::WINDOWSSTATE));
    // resize(settings.value(QLatin1String(Settings::MainWindow::SIZE), QSize(400, 400)).toSize());
    // move(settings.value(QLatin1String(Settings::MainWindow::POS), QPoint(200, 200)).toPoint());
    settings.endGroup();
    settings.beginGroup(QLatin1String(Settings::Groups::DATABASE));
    ui->comboBoxDatabaseType->setCurrentIndex(settings.value(QLatin1String(Settings::Database::TYPE), SQLITE).toInt());
    ui->lineEditDatabaseConnection->setText(settings.value(QLatin1String(Settings::Database::CONNECTION), this->getUserDataDir()).toString());
    ui->lineEditHostName->setText(settings.value(QLatin1String(Settings::Database::HOSTNAME), QLatin1String("localhost")).toString());
    ui->lineEditUserName->setText(settings.value(QLatin1String(Settings::Database::USERNAME), QLatin1String("jmbde")).toString());
    ui->lineEditPassword->setText(settings.value(QLatin1String(Settings::Database::PASSWORD), QLatin1String("jmbde")).toString());
}

void PreferencesDialog::on_pushButtonDBForceFileDialog_clicked()
{
    QString dbDir = QFileDialog::getExistingDirectory(this, tr("Select Directory for Database"), this->getUserDataDir());

    if (dbDir.length() > 2) {
        ui->lineEditDatabaseConnection->setText(dbDir);
    }
}

QString PreferencesDialog::getUserDataDir()
{
    QString dataBaseDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    return dataBaseDir;
}

void PreferencesDialog::on_buttonBox_accepted()
{
    writeSettings();
}
