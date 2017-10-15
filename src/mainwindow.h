/*
// mainwindow.h
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSettings>


#include <QString>

#include <QSqlRelationalDelegate>
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>

#include <QMessageBox>

#include <QMainWindow>
#include <QtSql>
#include <QtWidgets>

#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QPrinter>

#include <QtHelp>

#include "definitions.h"
#include "accountdatamodel.h"
#include "commondatamodel.h"
#include "computerdatamodel.h"
#include "datamodel.h"
#include "departmentdatamodel.h"
#include "devicetypedatamodel.h"
#include "employeedatamodel.h"
#include "functiondatamodel.h"
#include "inventorydatamodel.h"
#include "manufacturerdatamodel.h"
#include "pctypedatamodel.h"
#include "placedatamodel.h"
#include "systemdatamodel.h"
#include "phonedatamodel.h"
#include "printerdatamodel.h"

#include "helpbrowser.h"

#include "preferencesdialog.h"
#include "employeeinputdialog.h"
#include "computerinputdialog.h"
#include "csvimportdialog.h"


/**
 * Namespace for the UserInterface
 */
namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  /**
   * @brief MainWindow
   * @param parent
   */
  explicit MainWindow(QWidget *parent = 0);

  /**
   * @brief MainWindow::~MainWindow
   */
  ~MainWindow();

protected:
  /**
   * @brief closeEvent
   * @param event
   */
  void closeEvent(QCloseEvent *event);

  void resizeEvent(QResizeEvent *event);

private slots:
  /**
   * @brief on_actionPreferences_triggered
   */
  void on_actionPreferences_triggered();

  /**
   * @brief on_actionAbout_triggered
   */
  void on_actionAbout_triggered();

  /**
   * @brief on_actionNew_triggered
   */
  void on_actionNew_triggered();

  /**
   * @brief on_actionQuit_triggered
   */
  void on_actionQuit_triggered();

  /**
   * @brief focusChanged
   * @param now
   */
  void focusChanged(QWidget *, QWidget *now);

  /**
   * @brief on_actionOpen_triggered
   */
  void on_actionOpen_triggered();

  /**
   * @brief on_actionImport_triggered
   */
  void on_actionImport_triggered();

  /**
   * @brief on_actionExport_triggered
   */
  void on_actionExport_triggered();

  /**
   * @brief on_actionPrint_triggered
   */
  void on_actionPrint_triggered();

  /**
   * @brief on_action_Export_Pdf_triggered
   */
  void on_action_Export_Pdf_triggered();

  /**
   * @brief on_actionPrint_Preview_triggered
   */
  void on_actionPrint_Preview_triggered();

  void on_actionHelp_triggered();

  void on_actionEditAdd_triggered();

  void on_actionEditEdit_triggered();

  void on_actionEditDelete_triggered();

  void on_listView_clicked(const QModelIndex &index);


private:
  /**
   * @brief ui
   */
  Ui::MainWindow *ui;
  /**
   * @brief readSettings
   */
  void readSettings();
  /**
   * @brief writeSettings
   */
  void writeSettings();

  QHelpEngine *helpEngine;

  QDockWidget *helpWindow;

  /**
   * @brief Not_Available_Message
   */
  void Not_Available_Message();
  /**
   * @brief em
   */
  DataModel *dm;
  EmployeeDataModel *edm;
  ComputerDataModel *cdm;
  PrinterDataModel *pdm;
  PhoneDataModel *phdm;

  QSqlRelationalTableModel *model;
  QSqlTableModel *tableModel;

  qint16 dbType = 0;
  QString dbConnection;
  QString dbHostname;
  QString dbUsername;
  QString dbPassword;

  QStringListModel *slModel;

  enum ViewData {
    VIEW_EMPLOYEE = 0,
    VIEW_COMPUTER = 1,
    VIEW_PRINTER = 2,
    VIEW_PHONE = 3
  };

  int actualView;
};

#endif // MAINWINDOW_H
