/*
 * mainwindow.cpp
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


#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

#if defined(Q_OS_MAC)
    ui->actionAbout->setMenuRole(QAction::AboutRole); // 5.1 fix
    ui->actionPreferences->setMenuRole(QAction::PreferencesRole); // 5.1 fix
#endif

    readSettings();


    dm = new DataModell();
    bool retValue = dm->CreateConnection();
    if (retValue == true) {
        ui->radioButtonEmployee->setChecked(true);
        this->on_radioButtonEmployee_toggled(true);
    }
}


MainWindow::~MainWindow()
{
     dm->~DataModell();
    delete ui;
}

void MainWindow::focusChanged(QWidget *, QWidget *now)
{
    qDebug() << "Help :-)";
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    writeSettings();
}

void MainWindow::on_actionPreferences_triggered()
{
    PreferencesDialog *settingsDialog;
    settingsDialog = new PreferencesDialog();
    settingsDialog->show();
}

void MainWindow::on_actionAbout_triggered()
{

    QMessageBox::about(this,
                       tr("About"),
                       tr(
                       "\n\n"
                          "Copyright (c) 2013, 2014 Jürgen Mülbert. All rights reserved.\n"
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

void MainWindow::writeSettings()
{
    QString CompanyName = QLatin1String(Constants::COMPANY_NAME);
    QString ApplicationName = QLatin1String(Constants::APPL_NAME);
    QSettings settings(CompanyName, ApplicationName);
    settings.beginGroup(QLatin1String(Settings::Groups::MAINWINDOW));
    settings.setValue(QLatin1String(Settings::MainWindow::SIZE), size());
    settings.setValue(QLatin1String(Settings::MainWindow::POS), pos());
    settings.endGroup();

    // Database settings
    settings.beginGroup(QLatin1String(Settings::Groups::DATABASE));
    settings.setValue(QLatin1String(Settings::Database::TYPE),dbType);
    settings.setValue(QLatin1String(Settings::Database::CONNECTION), dbConnection);
    settings.setValue(QLatin1String(Settings::Database::HOSTNAME), dbHostname);
    settings.setValue(QLatin1String(Settings::Database::USERNAME), dbUsername);
    settings.setValue(QLatin1String(Settings::Database::PASSWORD), dbPassword);
    settings.endGroup();

}

void MainWindow::readSettings()
{
    QString CompanyName = QLatin1String(Constants::COMPANY_NAME);
    QString ApplicationName = QLatin1String(Constants::APPL_NAME);
    QSettings settings(CompanyName, ApplicationName);
    settings.beginGroup(QLatin1String(Settings::Groups::MAINWINDOW));
    resize(settings.value(QLatin1String(Settings::MainWindow::SIZE),QSize(400,400)).toSize());
    move(settings.value(QLatin1String(Settings::MainWindow::POS), QPoint(200,200)).toPoint());
    settings.endGroup();

    // Database settings
#if QT_VERSION >= 0x050000
    QString dataBaseDir = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
#else
    QString dataBaseDir = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
#endif
    settings.beginGroup(QLatin1String(Settings::Groups::DATABASE));
    dbType = settings.value(QLatin1String(Settings::Database::TYPE), SQLITE).toInt();
    dbConnection = settings.value(QLatin1String(Settings::Database::CONNECTION), dataBaseDir).toString();
    dbHostname = settings.value(QLatin1String(Settings::Database::HOSTNAME), QLatin1String("localhost")).toString();
    dbUsername = settings.value(QLatin1String(Settings::Database::USERNAME), QLatin1String("jmbde")).toString();
    dbPassword = settings.value(QLatin1String(Settings::Database::PASSWORD), QLatin1String("jmbde")).toString();

}

void MainWindow::on_actionNew_triggered()
{
    int ret = QMessageBox::warning(this,
                         QLatin1String(Constants::APPL_NAME),
                                   tr("This action create a new database. if you have an database\n"
                                      "with data you lost this.\n"
                                      "Proceed for create a new database ?"),
                                   QMessageBox::Cancel | QMessageBox::Yes);
    if ( ret == QMessageBox::Yes) {
        dm->CreateConnection();
        QMessageBox::information(this,
                                 QLatin1String(Constants::APPL_NAME),
                                 tr("The new database is created"));
    }
}

void MainWindow::on_actionQuit_triggered()
{
    qApp->quit();
}

void MainWindow::on_actionOpen_triggered()
{
    Not_Available_Message();
}

void MainWindow::on_actionImport_triggered()
{
    CsvImportDialog *csvImport = new CsvImportDialog();
    csvImport->show();
}

void MainWindow::on_actionExport_triggered()
{
    Not_Available_Message();
}

void MainWindow::on_actionPrint_triggered()
{

    QTextDocument doc;

    if (ui->radioButtonEmployee->isChecked()) {
        qDebug() << "Print Employee !";
        tableModel->database().commit();
        QString style = edm->setOutTableStyle();
        QString text = edm->generateTableString(tableModel, tr("Employee"));
        doc.setHtml(style+text);

    } else if (ui->radioButtonComputer->isChecked()) {
        qDebug() << "Print Computer !";
        tableModel->database().commit();
        QString style = cdm->setOutTableStyle();
        QString text = cdm->generateTableString(tableModel, tr("Computer"));
        doc.setHtml(style+text);

    } else if (ui->radioButtonPrinter->isChecked()) {
       qDebug() << "Print Printer !";
       tableModel->database().commit();
       QString style = pdm->setOutTableStyle();
       QString text = pdm->generateTableString(tableModel, tr("Printer"));
       doc.setHtml(style+text);


    } else if (ui->radioButtonPhone->isChecked()) {
        qDebug() << "Print Printer !";
        tableModel->database().commit();
        QString style = phdm->setOutTableStyle();
        QString text = phdm->generateTableString(tableModel, tr("Phone"));
        doc.setHtml(style+text);
    }


#if !defined(QT_NO_PRINTER) && !defined(QT_NO_PRINTDIALOG)

    QPrinter printer(QPrinter::HighResolution);
    printer.setOrientation(QPrinter::Landscape);
    QPrintDialog *dlg = new QPrintDialog(&printer, this);

    dlg->setWindowTitle(tr("Print Document"));
    if (dlg->exec() == QDialog::Accepted)
        doc.print(&printer);
    delete dlg;
#endif
}

void MainWindow::on_action_Export_Pdf_triggered()
{
    QTextDocument doc;

    if (ui->radioButtonEmployee->isChecked()) {
        qDebug() << "Print Employee !";
        tableModel->database().commit();
        QString style = edm->setOutTableStyle();
        QString text = edm->generateTableString(tableModel, tr("Employee"));
        doc.setHtml(style+text);

    } else if (ui->radioButtonComputer->isChecked()) {
        qDebug() << "Print Computer !";
        tableModel->database().commit();
        QString style = cdm->setOutTableStyle();
        QString text = cdm->generateTableString(tableModel, tr("Computer"));
        doc.setHtml(style+text);

    } else if (ui->radioButtonPrinter->isChecked()) {
       qDebug() << "Print Printer !";
       tableModel->database().commit();
       QString style = pdm->setOutTableStyle();
       QString text = pdm->generateTableString(tableModel, tr("Printer"));
       doc.setHtml(style+text);


    } else if (ui->radioButtonPhone->isChecked()) {
        qDebug() << "Print Printer !";
        tableModel->database().commit();
        QString style = phdm->setOutTableStyle();
        QString text = phdm->generateTableString(tableModel, tr("Phone"));
        doc.setHtml(style+text);
    }

#ifndef QT_NO_PRINTER
//! [0]
    QString fileName = QFileDialog::getSaveFileName(this, QLatin1String("Export PDF"),
                                                    QString(), QLatin1String("*.pdf"));
    if (!fileName.isEmpty()) {
        if (QFileInfo(fileName).suffix().isEmpty())
            fileName.append(QLatin1String(".pdf"));
        QPrinter printer(QPrinter::HighResolution);
        printer.setOrientation(QPrinter::Landscape);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
        doc.print(&printer);
    }
//! [0]
#endif

}

void MainWindow::on_actionPrint_Preview_triggered()
{
    QTextDocument doc;

    if (ui->radioButtonEmployee->isChecked()) {
        qDebug() << "Print Employee !";
        tableModel->database().commit();
        QString style = edm->setOutTableStyle();
        QString text = edm->generateTableString(tableModel, tr("Employee"));
        doc.setHtml(style+text);

    } else if (ui->radioButtonComputer->isChecked()) {
        qDebug() << "Print Computer !";
        tableModel->database().commit();
        QString style = cdm->setOutTableStyle();
        QString text = cdm->generateTableString(tableModel, tr("Computer"));
        doc.setHtml(style+text);

    } else if (ui->radioButtonPrinter->isChecked()) {
       qDebug() << "Print Printer !";
       tableModel->database().commit();
       QString style = pdm->setOutTableStyle();
       QString text = pdm->generateTableString(tableModel, tr("Printer"));
       doc.setHtml(style+text);


    } else if (ui->radioButtonPhone->isChecked()) {
        qDebug() << "Print Printer !";
        tableModel->database().commit();
        QString style = phdm->setOutTableStyle();
        QString text = phdm->generateTableString(tableModel, tr("Phone"));
        doc.setHtml(style+text);
    }


#if !defined(QT_NO_PRINTER) && !defined(QT_NO_PRINTDIALOG)
    QPrinter printer(QPrinter::HighResolution);
    printer.setOrientation(QPrinter::Landscape);
    QPrintPreviewDialog preview(&printer, ui->tableView);
    connect(&preview, SIGNAL(paintRequested(QPrinter*)), SLOT(printPreview(QPrinter*)));
    preview.exec();
#endif

}

void MainWindow::Not_Available_Message()
{
    QString message = tr("This action is not implemented\n"
                         "in the version ");


    message.append(QLatin1String(Constants::APPL_VERSION));
    message.append(tr("\nPlease try a newer version, if any available\n"));
    message.append(tr("you can check this on the project site:\n"));
    message.append(QLatin1String(Constants::APPL_PROJECT_SITE));


   QMessageBox::critical(this,
                      QLatin1String(Constants::APPL_NAME),
                     message,
                      QMessageBox::Cancel );

}


void MainWindow::on_actionEmployee_triggered()
{
    EmployeeDataModel *edm = new EmployeeDataModel;
    tableModel = edm->initializeTableModel();
    ui->tableView->setModel(tableModel);
    ui->tableView->hideColumn(0);
    ui->tableView->show();


    tableModel->database().commit();
}


void MainWindow::on_radioButtonEmployee_toggled(bool checked)
{
    qDebug() << "Employee Button : " << checked;

    edm = new EmployeeDataModel;
    tableModel = edm->initializeRelationalModel();

    ui->tableView->setModel(tableModel);


    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
    ui->tableView->show();

    tableModel->database().commit();
}

void MainWindow::on_radioButtonComputer_toggled(bool checked)
{
      qDebug() << "Computer Button : " << checked;

      cdm = new ComputerDataModel;
      tableModel = cdm->initializeRelationalModel();
      ui->tableView->setModel(tableModel);
      ui->tableView->hideColumn(0);

      ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
      ui->tableView->show();

      tableModel->database().commit();

}

void MainWindow::on_radioButtonPrinter_toggled(bool checked)
{
   qDebug() << "Printer Button : " << checked;

   pdm = new PrinterDataModel;
   tableModel = pdm->initializeRelationalModel();
   ui->tableView->setModel(tableModel);
   ui->tableView->hideColumn(0);

   ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
   ui->tableView->show();

   tableModel->database().commit();


}

void MainWindow::on_radioButtonPhone_toggled(bool checked)
{
  qDebug() << "Phone Button : " << checked;

  phdm = new PhoneDataModel;
  tableModel = phdm->initializeRelationalModel();
  ui->tableView->setModel(tableModel);
  ui->tableView->hideColumn(0);

  ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
  ui->tableView->show();

  tableModel->database().commit();

}


void MainWindow::on_pushButtonAddData_clicked()
{
    if (ui->radioButtonEmployee->isChecked()) {
        qDebug() << "New Employee !";
        tableModel->database().commit();
        edm->addRow(ui->tableView);

    } else if (ui->radioButtonComputer->isChecked()) {
        qDebug() << "New Computer !";
        tableModel->database().commit();
        cdm->addRow(ui->tableView);


    } else if (ui->radioButtonPrinter->isChecked()) {
        qDebug() << "New Printer !";
        tableModel->database().commit();
        pdm->addRow(ui->tableView);

    } else if (ui->radioButtonPhone->isChecked()) {
         qDebug() << "New Phone !";
         tableModel->database().commit();
         phdm->addRow(ui->tableView);

    }

}


void MainWindow::on_QPushButtonSubmit_clicked()
{
    tableModel->submitAll();
    qDebug() << "Submit All ------------";
    qDebug() << "Database : " << tableModel->database().databaseName();
    qDebug() << "DB       : " << tableModel->database().isValid();
    qDebug() << "Last Error : " << tableModel->database().lastError().text();
}

void MainWindow::on_actionHelp_triggered()
{
    helpWindow = new QDockWidget(tr("Help"), this);
    QSplitter *helpPanel = new QSplitter(Qt::Horizontal);

    HelpBrowser *helpBrowser = new HelpBrowser();

    helpPanel->insertWidget(0, helpBrowser->getContentWidget());
    helpPanel->insertWidget(1, helpBrowser->getLinkWidget());
    helpPanel->setStretchFactor(1,1);
    helpWindow->setWidget(helpPanel);
    addDockWidget(Qt::BottomDockWidgetArea, helpWindow);

    helpBrowser->showHelpForKeyWord(QLatin1String("main"));
}

