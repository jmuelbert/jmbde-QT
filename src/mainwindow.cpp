/*
* Copyright 2013 Jürgen Mülbert
*
* Licensed under the EUPL, Version 1.1 or – as soon they
  will be approved by the European Commission - subsequent
  versions of the EUPL (the "Licence");
* You may not use this work except in compliance with the
  Licence.
* You may obtain a copy of the Licence at:
*
* http://ec.europa.eu/idabc/eupl5
*
* Unless required by applicable law or agreed to in
  writing, software distributed under the Licence is
  distributed on an "AS IS" basis,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
  express or implied.
* See the Licence for the specific language governing
  permissions and limitations under the Licence.
*/


#include "mainwindow.h"
#include "employeeinputdialog.h"
#include "csvimportdialog.h"
#include "ui_mainwindow.h"

/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

#if defined(Q_OS_MAC)
    ui->actionAbout->setMenuRole(QAction::AboutRole); // 5.1 fix
    ui->actionPreferences->setMenuRole(QAction::PreferencesRole); // 5.1 fix
#endif

    dm = new DataModell;
    dm->CreateConnection();


    model = dm->initializeRelationalModel();
    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
    model->database().commit();
}

/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::focusChanged
 * @param now
 */
void MainWindow::focusChanged(QWidget *, QWidget *now)
{
    qDebug() << "Help :-)";
}

/**
 * @brief MainWindow::closeEvent
 * @param event
 */
void MainWindow::closeEvent(QCloseEvent *event)
{
    writeSettings();
}

/**
 * @brief MainWindow::on_actionPreferences_triggered
 */
void MainWindow::on_actionPreferences_triggered()
{
    PreferencesDialog *settingsDialog;
    settingsDialog = new PreferencesDialog();
    settingsDialog->show();
}

/**
 * @brief MainWindow::on_actionAbout_triggered
 */
void MainWindow::on_actionAbout_triggered()
{

    QMessageBox::about(this,
                       tr("About"),
                       tr("About JMBDE Version 0.2\n\n"
                          "Copyright (c) 2013 Jürgen Mülbert. All rights reserved.\n"
                          "\n"
                          "This program is free software: you can redistribute it and/or modify\n"
                          "it under the terms of the European Union Public Licence (EUPL),\n"
                          "version 1.1.\n"
                          "\n"
                          "This program is distributed in the hope that it will be useful,\n"
                          "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
                          "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
                          "European Union Public Licence for more details.\n"
                          "\n"
                          "You should have received a copy of the European Union Public Licence\n"
                          "along with this program. If not, see\n"
                          "http://www.osor.eu/eupl/european-union-public-licence-eupl-v.1.1\n"
                          ));

}

/**
 * @brief MainWindow::writeSettings
 */
void MainWindow::writeSettings()
{
    QSettings settings(Constants::COMPANY_NAME, Constants::APPL_NAME);
    settings.beginGroup("MainWindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();
}

/**
 * @brief MainWindow::readSettings
 */
void MainWindow::readSettings()
{
    QSettings settings(Constants::COMPANY_NAME, Constants::APPL_NAME);
    settings.beginGroup("MainWindow");
    resize(settings.value("size",QSize(400,400)).toSize());
    move(settings.value("pos", QPoint(200,200)).toPoint());
    settings.endGroup();
}

/**
 * @brief MainWindow::on_pushButtonNewPerson_clicked
 */
void MainWindow::on_pushButtonNewPerson_clicked()
{
    EmployeeInputDialog *eip = new EmployeeInputDialog();
    eip->show();
    ui->tableView->repaint();

}


/**
 * @brief MainWindow::on_actionNew_triggered
 */
void MainWindow::on_actionNew_triggered()
{
    int ret = QMessageBox::warning(this,
                         Constants::APPL_NAME,
                                   tr("This action create a new database. if you have an database\n"
                                      "with data you lost this.\n"
                                      "Proceed for create a new database ?"),
                                   QMessageBox::Cancel | QMessageBox::Yes);
    if ( ret == QMessageBox::Yes) {
        dm->CreateConnection();
        QMessageBox::information(this,
                                 Constants::APPL_NAME,
                                 tr("The new database is created"));
    }
}

/**
 * @brief MainWindow::on_actionQuit_triggered
 */
void MainWindow::on_actionQuit_triggered()
{
    qApp->quit();
}

/**
 * @brief MainWindow::on_actionOpen_triggered
 */
void MainWindow::on_actionOpen_triggered()
{
    Not_Available_Message();
}

/**
 * @brief MainWindow::on_actionImport_triggered
 */
void MainWindow::on_actionImport_triggered()
{
    CsvImportDialog *csvImport = new CsvImportDialog();
    csvImport->show();
}

/**
 * @brief MainWindow::on_actionExport_triggered
 */
void MainWindow::on_actionExport_triggered()
{
    Not_Available_Message();
}

/**
 * @brief MainWindow::on_actionPrint_triggered
 */
void MainWindow::on_actionPrint_triggered()
{
    Not_Available_Message();
}

/**
 * @brief MainWindow::Not_Available_Message
 */
void MainWindow::Not_Available_Message()
{
    QString message = tr("This action is not implemented\n"
                         "in the version ");


    message.append(Constants::APPL_VERSION);
    message.append(tr("\nPlease try a newer version, if any available\n"));
    message.append(tr("you can check this on the project site:\n"));
    message.append(Constants::APPL_PROJECT_SITE);


   QMessageBox::critical(this,
                      Constants::APPL_NAME,
                     message,
                      QMessageBox::Cancel );

}

/**
 * @brief MainWindow::on_pushButton_clicked
 */
void MainWindow::on_pushButton_clicked()
{
    if (model->submitAll()) {
        model->database().commit();
    } else {
        model->database().rollback();
        QMessageBox::warning(this, tr("Cached Table"),
                             tr("The database reported an error: %1")
                             .arg(model->lastError().text()));
    }
}

/**
 * @brief MainWindow::on_pushButton_2_clicked
 */
void MainWindow::on_pushButton_2_clicked()
{
    model = dm->initializeRelationalModel();
    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
    model->database().commit();
}

/**
 * @brief MainWindow::on_pushButton_3_clicked
 */
void MainWindow::on_pushButton_3_clicked()
{
    tableModel = dm->initializeEmployeeModel();
    ui->tableView->setModel(tableModel);

    tableModel->database().commit();
}
