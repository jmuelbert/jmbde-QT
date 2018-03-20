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
#include <QPrinter>
#include <QPrintPreviewDialog>

#include <QtHelp>

#include "app/app_version.h"
#include "accountdatamodel.h"
#include "citynamedatamodel.h"
#include "commondatamodel.h"
#include "computerdatamodel.h"
#include "datamodel.h"
#include "definitions.h"
#include "departmentdatamodel.h"
#include "devicetypedatamodel.h"
#include "employeedatamodel.h"
#include "functiondatamodel.h"
#include "inventorydatamodel.h"
#include "manufacturerdatamodel.h"
#include "osdatamodel.h"
#include "phonedatamodel.h"
#include "placedatamodel.h"
#include "printerdatamodel.h"
#include "processordatamodel.h"
#include "softwaredatamodel.h"
#include "systemdatamodel.h"
#include "titledatamodel.h"
#include "zipcitymodel.h"
#include "zipcodemodel.h"

#include "helpbrowser.h"

#include "csvimportdialog.h"
#include "preferencesdialog.h"

#include "chipcardinputarea.h"
#include "cityinputarea.h"
#include "computerinputarea.h"
#include "departmentinputarea.h"
#include "employeeinputarea.h"
#include "functioninputarea.h"
#include "manufacturerinputarea.h"
#include "mobileinputarea.h"
#include "titleinputarea.h"
#include "osinputarea.h"
#include "phoneinputarea.h"
#include "printerinputarea.h"
#include "processorinputarea.h"
#include "softwareinputarea.h"

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
    explicit MainWindow(QWidget* parent = 0);

    /**
     * @brief MainWindow::~MainWindow
     */
    ~MainWindow();

  protected:

    /**
     * @brief closeEvent
     * @param event
     */
    void closeEvent(QCloseEvent* event);

    void resizeEvent(QResizeEvent* event);

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
    void focusChanged(QWidget*, QWidget* now);

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

    void onClickedTreeView(const QModelIndex& index);

    void onClickedListViewRow(const QModelIndex& index);
    void onPressedListViewRow(const QModelIndex& index);

  private:

    /**
     * @brief ui
     */
    Ui::MainWindow* ui;

    /**
     * @brief readSettings
     */
    void readSettings();

    /**
     * @brief writeSettings
     */
    void writeSettings();

    QHelpEngine* helpEngine;
    QDockWidget* helpWindow;

    /**
     * @brief Not_Available_Message
     */
    void Not_Available_Message();

    /**
     * @brief em
     */
    DataModel* dm;
    QSqlRelationalTableModel* model;
    QSqlTableModel* tableModel;
    int dbType = 0;
    QString dbConnection;
    QString dbHostname;
    QString dbUsername;
    QString dbPassword;
    QSplitter* m_splitter;
    QTreeView* m_treeView;
    QListView* m_listView;
    QStandardItemModel* m_treeviewModel;
    enum ViewData {
      VIEW_EMPLOYEE,
      VIEW_FUNCTION,
      VIEW_DEPARTMENT,
      VIEW_TITLE,
      VIEW_PHONE,
      VIEW_MOBILE,
      VIEW_COMPUTER,
      VIEW_PROCESSOR,
      VIEW_OS,
      VIEW_SOFTWARE,
      VIEW_PRINTER,
      VIEW_MANUFACTURER,
      VIEW_CITY,
      VIEW_CHIPCARD,
    };
    int actualView;
    QModelIndex m_actualView;
    QModelIndex m_actualData;
};

#endif // MAINWINDOW_H
