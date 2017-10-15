/*
// mainwindow.cpp
// part of jmbde
//
// Copyright (c) 2013-2017 Jürgen Mülbert. All rights reserved.
//
// Licensed under the EUPL, Version 1.2 or – as soon they
// will be approved by the European Commission - subsequent
// versions of the EUPL (the "Licence");
// You may not use this work except in compliance with the
// Licence.
// You may obtain a copy of the Licence at:
//
// https://joinup.ec.europa.eu/page/eupl-text-11-12
//
// Unless required by applicable law or agreed to in
// writing, software distributed under the Licence is
// distributed on an "AS IS" basis,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
// express or implied.
// See the Licence for the specific language governing
// permissions and limitations under the Licence.
//
// Lizenziert unter der EUPL, Version 1.2 oder - sobald
// diese von der Europäischen Kommission genehmigt wurden -
// Folgeversionen der EUPL ("Lizenz");
// Sie dürfen dieses Werk ausschließlich gemäß
// dieser Lizenz nutzen.
// Eine Kopie der Lizenz finden Sie hier:
//
// https://joinup.ec.europa.eu/page/eupl-text-11-12
//
// Sofern nicht durch anwendbare Rechtsvorschriften
// gefordert oder in schriftlicher Form vereinbart, wird
// die unter der Lizenz verbreitete Software "so wie sie
// ist", OHNE JEGLICHE GEWÄHRLEISTUNG ODER BEDINGUNGEN -
// ausdrücklich oder stillschweigend - verbreitet.
// Die sprachspezifischen Genehmigungen und Beschränkungen
// unter der Lizenz sind dem Lizenztext zu entnehmen.
//
*/


#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

  ui->setupUi(this);

  readSettings();

  slModel = new QStringListModel(this);

  QStringList stringList;
  stringList.append(tr("Employee"));
  stringList.append(tr("Computer"));
  stringList.append(tr("Printer"));
  stringList.append(tr("Phone"));

  slModel->setStringList(stringList);

  ui->listView->setModel(slModel);
  int width = ui->centralWidget->width() - 20;
  int height = ui->centralWidget->height() - 20;
  ui->splitter->resize(width, height);

  actualView = VIEW_EMPLOYEE;

  dm = new DataModel();
  bool retValue = dm->CreateConnection();
  if (retValue == true) {
      QSize availableSize = qApp->desktop()->availableGeometry().size();
      int width = availableSize.width();
      int height = availableSize.height();
      qDebug() << "Available dimensions " << width << "x" << height;
    EmployeeDataModel *edm = new EmployeeDataModel;
    tableModel = edm->initializeTableModel();
    ui->tableView->setModel(tableModel);
    ui->tableView->hideColumn(0);
    ui->tableView->show();

    tableModel->database().commit();
  }
}

MainWindow::~MainWindow() {
  dm->~DataModel();
  delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    int width = ui->centralWidget->width() - 20;
    int height = ui->centralWidget->height() - 20;
    qDebug() << "Resize...";
    qDebug() << "width= " << width <<" height= " << height;
    ui->splitter->resize(width, height);
}


void MainWindow::focusChanged(QWidget *, QWidget *now) {
  qDebug() << "Help :-)";
}

void MainWindow::closeEvent(QCloseEvent *event) { writeSettings(); }

void MainWindow::on_actionPreferences_triggered() {
  PreferencesDialog *settingsDialog;
  settingsDialog = new PreferencesDialog();
  settingsDialog->show();
}

void MainWindow::on_actionAbout_triggered() {

  QMessageBox::about(
      this, tr("About"),
      tr("\n\n"
         "Copyright (c) 2013, 2014 Jürgen Mülbert. All rights reserved.\n"
         "\n"
         "This program is free software: you can redistribute it and/or "
         "modify\n"
         "it under the terms of the European Union Public Licence (EUPL),\n"
         "version 1.1.\n"
         "\n"
         "This program is distributed in the hope that it will be useful,\n"
         "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
         "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
         "European Union Public Licence for more details.\n"
         "\n"
         "You should have received a copy of the European Union Public "
         "Licence\n"
         "along with this program. If not, see\n"
         "http://www.osor.eu/eupl/european-union-public-licence-eupl-v.1.1\n"));
}

void MainWindow::writeSettings() {
  QSettings settings;
  settings.beginGroup(QLatin1String(Settings::Groups::MAINWINDOW));
  settings.setValue(QLatin1String(Settings::MainWindow::SIZE), size());
  settings.setValue(QLatin1String(Settings::MainWindow::POS), pos());
  settings.setValue(QLatin1String(Settings::MainWindow::SPLITTER), ui->splitter->saveState());
  settings.endGroup();

  // Database settings
  settings.beginGroup(QLatin1String(Settings::Groups::DATABASE));
  settings.setValue(QLatin1String(Settings::Database::TYPE), dbType);
  settings.setValue(QLatin1String(Settings::Database::CONNECTION),
                    dbConnection);
  settings.setValue(QLatin1String(Settings::Database::HOSTNAME), dbHostname);
  settings.setValue(QLatin1String(Settings::Database::USERNAME), dbUsername);
  settings.setValue(QLatin1String(Settings::Database::PASSWORD), dbPassword);
  settings.endGroup();
}

void MainWindow::readSettings() {
  QSettings settings;
  settings.beginGroup(QLatin1String(Settings::Groups::MAINWINDOW));
  resize(
      settings.value(QLatin1String(Settings::MainWindow::SIZE), QSize(400, 400))
          .toSize());
  move(
      settings.value(QLatin1String(Settings::MainWindow::POS), QPoint(200, 200))
          .toPoint());
  ui->splitter->restoreState(settings.value(QLatin1String(Settings::MainWindow::SPLITTER)).toByteArray());
  settings.endGroup();

// Database settings
#if QT_VERSION >= 0x050000
  QString dataBaseDir =
      QStandardPaths::writableLocation(QStandardPaths::DataLocation);
#else
  QString dataBaseDir =
      QDesktopServices::storageLocation(QDesktopServices::DataLocation);
#endif
  settings.beginGroup(QLatin1String(Settings::Groups::DATABASE));
  dbType =
      settings.value(QLatin1String(Settings::Database::TYPE), SQLITE).toInt();
  dbConnection =
      settings.value(QLatin1String(Settings::Database::CONNECTION), dataBaseDir)
          .toString();
  dbHostname = settings
                   .value(QLatin1String(Settings::Database::HOSTNAME),
                          QLatin1String("localhost"))
                   .toString();
  dbUsername = settings
                   .value(QLatin1String(Settings::Database::USERNAME),
                          QLatin1String("jmbde"))
                   .toString();
  dbPassword = settings
                   .value(QLatin1String(Settings::Database::PASSWORD),
                          QLatin1String("jmbde"))
                   .toString();
}

void MainWindow::on_actionNew_triggered() {
  int ret = QMessageBox::warning(
      this,
      qApp->applicationDisplayName(),
      tr("This action create a new database. if you have an database\n"
         "with data you lost this.\n"
         "Proceed for create a new database ?"),
      QMessageBox::Cancel | QMessageBox::Yes);
  if (ret == QMessageBox::Yes) {
    dm->CreateConnection();
    QMessageBox::information(this, qApp->applicationDisplayName(),
                             tr("The new database is created"));
  }
}

void MainWindow::on_actionQuit_triggered() { qApp->quit(); }

void MainWindow::on_actionOpen_triggered() { Not_Available_Message(); }

void MainWindow::on_actionImport_triggered() {
  CsvImportDialog *csvImport = new CsvImportDialog();
  csvImport->show();
}

void MainWindow::on_actionExport_triggered() { Not_Available_Message(); }

void MainWindow::on_actionPrint_triggered() {

  QTextDocument doc;
  switch (actualView) {
  case VIEW_EMPLOYEE: {
    qDebug() << "Print Employee !";
    tableModel->database().commit();
    QString style = edm->setOutTableStyle();
    QString text = edm->generateTableString(tableModel, tr("Employee"));
    doc.setHtml(style + text);
  } break;

  case VIEW_COMPUTER: {
    qDebug() << "Print Computer !";
    tableModel->database().commit();
    QString style = cdm->setOutTableStyle();
    QString text = cdm->generateTableString(tableModel, tr("Computer"));
    doc.setHtml(style + text);
  } break;

  case VIEW_PRINTER: {
    qDebug() << "Print Printer !";
    tableModel->database().commit();
    QString style = pdm->setOutTableStyle();
    QString text = pdm->generateTableString(tableModel, tr("Printer"));
    doc.setHtml(style + text);
  } break;

  case VIEW_PHONE: {
    qDebug() << "Print Printer !";
    tableModel->database().commit();
    QString style = phdm->setOutTableStyle();
    QString text = phdm->generateTableString(tableModel, tr("Phone"));
    doc.setHtml(style + text);
  } break;

  default:
    Not_Available_Message();
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

void MainWindow::on_action_Export_Pdf_triggered() {
  QTextDocument doc;

  switch (actualView) {
  case VIEW_EMPLOYEE: {
    qDebug() << "Print Employee !";
    tableModel->database().commit();
    QString style = edm->setOutTableStyle();
    QString text = edm->generateTableString(tableModel, tr("Employee"));
    doc.setHtml(style + text);
  } break;

  case VIEW_COMPUTER: {
    qDebug() << "Print Computer !";
    tableModel->database().commit();
    QString style = cdm->setOutTableStyle();
    QString text = cdm->generateTableString(tableModel, tr("Computer"));
    doc.setHtml(style + text);
  } break;

  case VIEW_PRINTER: {
    qDebug() << "Print Printer !";
    tableModel->database().commit();
    QString style = pdm->setOutTableStyle();
    QString text = pdm->generateTableString(tableModel, tr("Printer"));
    doc.setHtml(style + text);
  } break;

  case VIEW_PHONE: {
    qDebug() << "Print Printer !";
    tableModel->database().commit();
    QString style = phdm->setOutTableStyle();
    QString text = phdm->generateTableString(tableModel, tr("Phone"));
    doc.setHtml(style + text);
  } break;

  default:
    Not_Available_Message();
  }

#ifndef QT_NO_PRINTER
  //! [0]
  QString fileName = QFileDialog::getSaveFileName(
      this, QLatin1String("Export PDF"), QString(), QLatin1String("*.pdf"));
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

void MainWindow::on_actionPrint_Preview_triggered() {
  QTextDocument doc;

  switch (actualView) {
  case VIEW_EMPLOYEE: {
    qDebug() << "Print Employee !";
    tableModel->database().commit();
    QString style = edm->setOutTableStyle();
    QString text = edm->generateTableString(tableModel, tr("Employee"));
    doc.setHtml(style + text);
  } break;

  case VIEW_COMPUTER: {
    qDebug() << "Print Computer !";
    tableModel->database().commit();
    QString style = cdm->setOutTableStyle();
    QString text = cdm->generateTableString(tableModel, tr("Computer"));
    doc.setHtml(style + text);
  } break;

  case VIEW_PRINTER: {
    qDebug() << "Print Printer !";
    tableModel->database().commit();
    QString style = pdm->setOutTableStyle();
    QString text = pdm->generateTableString(tableModel, tr("Printer"));
    doc.setHtml(style + text);
  } break;

  case VIEW_PHONE: {
    qDebug() << "Print Printer !";
    tableModel->database().commit();
    QString style = phdm->setOutTableStyle();
    QString text = phdm->generateTableString(tableModel, tr("Phone"));
    doc.setHtml(style + text);
  } break;

  default:
    Not_Available_Message();
  }

#if !defined(QT_NO_PRINTER) && !defined(QT_NO_PRINTDIALOG)
  QPrinter printer(QPrinter::HighResolution);
  printer.setOrientation(QPrinter::Landscape);
  QPrintPreviewDialog preview(&printer, ui->tableView);
  connect(&preview, SIGNAL(paintRequested(QPrinter *)),
          SLOT(printPreview(QPrinter *)));
  preview.exec();
#endif
}

void MainWindow::Not_Available_Message() {
  QString message = tr("This action is not implemented\n"
                       "in the version ");

  message.append(qApp->applicationVersion());
  message.append(tr("\nPlease try a newer version, if any available\n"));
  message.append(tr("you can check this on the project site:\n"));
  message.append(qApp->organizationDomain());

  QMessageBox::critical(this, qApp->applicationDisplayName(), message,
                        QMessageBox::Cancel);
}

void MainWindow::on_actionHelp_triggered() {
  helpWindow = new QDockWidget(tr("Help"), this);
  QSplitter *helpPanel = new QSplitter(Qt::Horizontal);

  HelpBrowser *helpBrowser = new HelpBrowser();

  helpPanel->insertWidget(0, helpBrowser->getContentWidget());
  helpPanel->insertWidget(1, helpBrowser->getLinkWidget());
  helpPanel->setStretchFactor(1, 1);
  helpWindow->setWidget(helpPanel);
  addDockWidget(Qt::BottomDockWidgetArea, helpWindow);

  helpBrowser->showHelpForKeyWord(QLatin1String("main"));
}

void MainWindow::on_actionEditAdd_triggered() {
  switch (actualView) {
  case VIEW_EMPLOYEE: {
    EmployeeInputDialog *eid = new EmployeeInputDialog();
    eid->show();
  } break;

  case VIEW_COMPUTER: {
    ComputerInputDialog *cid = new ComputerInputDialog();
    cid->show();

  } break;

  case VIEW_PRINTER: {

  } break;

  case VIEW_PHONE: {

  } break;

  default:
    Not_Available_Message();
  }
}

void MainWindow::on_actionEditEdit_triggered() {
  QItemSelectionModel *select = ui->tableView->selectionModel();
  QModelIndexList selection = select->selectedRows();

  switch (actualView) {
  case VIEW_EMPLOYEE: {
    for (int i = 0; i < selection.count(); i++) {
      QModelIndex index = selection.at(i);
      EmployeeInputDialog *eid = new EmployeeInputDialog(0, index.row());
      eid->show();
    }
  } break;

  case VIEW_COMPUTER: {
    for (int i = 0; i < selection.count(); i++) {
      QModelIndex index = selection.at(i);
      ComputerInputDialog *cid = new ComputerInputDialog(0, index.row());
      cid->show();
    }
  } break;

  case VIEW_PRINTER: {

  } break;

  case VIEW_PHONE: {

  } break;

  default:
    Not_Available_Message();
  }
}

void MainWindow::on_actionEditDelete_triggered() {
  switch (actualView) {
  case VIEW_EMPLOYEE: {
  } break;

  case VIEW_COMPUTER: {

  } break;

  case VIEW_PRINTER: {

  } break;

  case VIEW_PHONE: {

  } break;

  default:
    Not_Available_Message();
  }
}

void MainWindow::on_listView_clicked(const QModelIndex &index) {
  qDebug() << "Item clicked ---" << index.row();

  switch (index.row()) {
  case VIEW_EMPLOYEE: {
    actualView = VIEW_EMPLOYEE;
    EmployeeDataModel *edm = new EmployeeDataModel;
    tableModel = edm->initializeTableModel();

    ui->tableView->setModel(tableModel);
    ui->tableView->hideColumn(0);

    ui->tableView->show();
    tableModel->database().commit();
  } break;

  case VIEW_COMPUTER: {
    actualView = VIEW_COMPUTER;
    cdm = new ComputerDataModel;
    tableModel = cdm->initializeRelationalModel();
    ui->tableView->setModel(tableModel);
    ui->tableView->hideColumn(0);

    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
    ui->tableView->show();

    tableModel->database().commit();
  } break;

  case VIEW_PRINTER: {
    actualView = VIEW_PRINTER;
    pdm = new PrinterDataModel;
    tableModel = pdm->initializeRelationalModel();
    ui->tableView->setModel(tableModel);
    ui->tableView->hideColumn(0);

    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
    ui->tableView->show();

    tableModel->database().commit();
  } break;

  case VIEW_PHONE: {
    actualView = VIEW_PHONE;
    phdm = new PhoneDataModel;
    tableModel = phdm->initializeRelationalModel();
    ui->tableView->setModel(tableModel);
    ui->tableView->hideColumn(0);

    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
    ui->tableView->show();

    tableModel->database().commit();
  } break;

  default:
    Not_Available_Message();
  }
}

