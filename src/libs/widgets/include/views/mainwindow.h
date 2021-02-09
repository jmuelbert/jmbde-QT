/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include <QLoggingCategory>
#include <QMainWindow>
#include <QMessageBox>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QPrinter>
#include <QSettings>
#include <QSqlRelationalDelegate>
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>
#include <QString>
#include <QtSql>
#include <QtWidgets>

#include "definitions.h"
#include "jmbdewidgets-version.h"
#include "jmbdewidgets_export.h"
#include "models/cityname.h"
#include "models/datacontext.h"
#include "models/department.h"
#include "models/function.h"
#include "models/manufacturer.h"
#include "models/os.h"
#include "models/processor.h"
#include "models/software.h"
#include "models/title.h"
#include "views/aboutdialog.h"
#include "views/accountinputarea.h"
#include "views/chipcarddoorinputarea.h"
#include "views/chipcardinputarea.h"
#include "views/cityinputarea.h"
#include "views/computerinputarea.h"
#include "views/csvimportdialog.h"
#include "views/departmentinputarea.h"
#include "views/employeeinputarea.h"
#include "views/employeetable.h"
#include "views/functioninputarea.h"
#include "views/manufacturerinputarea.h"
#include "views/mobileinputarea.h"
#include "views/osinputarea.h"
#include "views/phoneinputarea.h"
#include "views/preferencesdialog.h"
#include "views/printerinputarea.h"
#include "views/processorinputarea.h"
#include "views/softwareinputarea.h"
#include "views/titleinputarea.h"

Q_DECLARE_LOGGING_CATEGORY(jmbdeWidgetsMainWindowLog)

/**
 * Namespace for the UserInterface
 */
namespace Ui {
class MainWindow;
}

/**
 * \class MainWindow
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief MainWindow
     * @param parent The parent widget
     */
    explicit JMBDEWIDGETS_EXPORT MainWindow(QWidget* parent = nullptr);

    /**
     * @brief MainWindow::~MainWindow
     */
    JMBDEWIDGETS_EXPORT ~MainWindow();

protected:
    /**
     * @brief closeEvent
     * @param event The recived event
     */
    void JMBDEWIDGETS_EXPORT closeEvent(QCloseEvent* event);

    /**
     * @brief resizeEvent
     * @param event Tehe recived event
     */
    void JMBDEWIDGETS_EXPORT resizeEvent(QResizeEvent* event);

private slots:
    /**
     * @brief on_actionPreferences_triggered
     */
    JMBDEWIDGETS_EXPORT void on_actionPreferences_triggered();

    /**
     * @brief on_actionAbout_triggered
     */
    JMBDEWIDGETS_EXPORT void on_actionAbout_triggered();

    /**
     * \fn void on_actionNew_triggered()
     * \brief on_actionNew_triggered
     */
    void JMBDEWIDGETS_EXPORT on_actionNew_triggered();

    /**
     * \fn on_actionQuit_triggered()
     * \brief on_actionQuit_triggered
     */
    JMBDEWIDGETS_EXPORT void on_actionQuit_triggered();

    /**
     * @brief focusChanged
     * @param from The old focus widget
     * @param now The actual focus widget
     */
    JMBDEWIDGETS_EXPORT void focusChanged(QWidget* from, QWidget* now);

    /**
     * \fn on_actionOpen_triggered()
     * \brief on_actionOpen_triggered
     */
    void JMBDEWIDGETS_EXPORT on_actionOpen_triggered();

    /**
     * \fn on_actionImport_triggered()
     * \brief on_actionImport_triggered
     */
    void JMBDEWIDGETS_EXPORT on_actionImport_triggered();

    /**
     * @brief on_actionExport_triggered
     */
    void JMBDEWIDGETS_EXPORT on_actionExport_triggered();

    /**
     * @brief on_actionPrint_triggered
     */
    void JMBDEWIDGETS_EXPORT on_actionPrint_triggered();

    /**
     * \fn void on_action_Export_Pdf_triggered()
     * \brief on_action_Export_Pdf_triggered
     */
    void JMBDEWIDGETS_EXPORT on_action_Export_Pdf_triggered();

    /**
     * \fn void on_actionPrint_Preview_triggered()
     * \brief on_actionPrint_Preview_triggered
     */
    void JMBDEWIDGETS_EXPORT on_actionPrint_Preview_triggered();

    /**
     * @brief on_actionHelp_triggered
     */
    void JMBDEWIDGETS_EXPORT on_actionHelp_triggered();

    /**
     * @brief on_treeView_clicked
     * @param index The QModelIndex of the TreeView to displayed
     *
     * \see QModelIndex::QModelIndex
     */
    void JMBDEWIDGETS_EXPORT on_treeView_clicked(const QModelIndex& index);

    /**
     * @brief on_listView_clicked
     * @param index The QModelIndex of the ListViewRow to displayed
     */
    void JMBDEWIDGETS_EXPORT on_listView_clicked(const QModelIndex& index);

    void actualizeAccoutListView();
    void actualizeChipCardListView();
    void actualizeChipCardDoorListView();
    void actualizeComputerListView();

    void actualizeDepartmentListView();

    /*!
        @brief Actualize the list view for employee after data changes
     */
    void actualizeEmployeeListView();

    void actualizeFunctionListView();

private:
    /**
     * @brief ui
     */
    Ui::MainWindow* ui;

    /**
      @brief initOutline
      */
    void initOutline();

    /**
     * @brief readSettings
     */
    void readSettings();

    /**
     * @brief writeSettings
     */
    void writeSettings();

    /**
     * \fn void notAvailableMessage()
     * \brief notAvailableMessage
     *
     */
    void notAvailableMessage(const QString& functionName);

    void actualizeListView(QSqlTableModel* listModel, int idx);

    /**
     * @brief model
     */
    QSqlRelationalTableModel* model {};

    /**
     * @brief tableModel
     */
    QSqlTableModel* tableModel {};

    /**
     * @brief dataBaseName
     */
    QString dataBaseName;

    /**
     * @brief dataContext
     */
    Model::DataContext* dataContext;

    /**
     * @brief dbType
     */
    int dbType = 0;

    /**
     * @brief dbConnection
     */
    QString dbConnection;

    /**
     * @brief dbHostname
     */
    QString dbHostname;

    /**
     * @brief dbUsername
     */
    QString dbUsername;

    /**
     * @brief dbPassword
     */
    QString dbPassword;

    /**
     * @brief m_splitter
     */
    QSplitter* m_splitter {};

    /**
     * @brief m_treeView
     */
    QTreeView* m_treeView {};

    /**
     * @brief m_listView
     */
    QListView* m_listView {};

    /**
     * @brief m_treeviewModel
     */
    QStandardItemModel* m_treeviewModel {};

    /**
     * @brief The ViewData enum
     */
    enum ViewData {
        VIEW_ACCOUNT,
        VIEW_CHIPCARD,
        VIEW_CHIPCARDDOOR,
        VIEW_CHIPCARDPROFILE,
        VIEW_CHIPCARDPROFILEDOOR,
        VIEW_CITYNAME,
        VIEW_COMPANY,
        VIEW_COMPUTER,
        VIEW_COMPUTERSOFTWARE,
        VIEW_DEPARTMENT,
        VIEW_DEVICENAME,
        VIEW_DEVICETYPE,
        VIEW_DOCUMENT,
        VIEW_EMPLOYEE,
        VIEW_EMPLOYEEACCOUNT,
        VIEW_EMPLOYEEDOCUMENT,
        VIEW_FAX,
        VIEW_FUNCTION,
        VIEW_INVENTORY,
        VIEW_MANUFACTURER,
        VIEW_MOBILE,
        VIEW_OS,
        VIEW_PHONE,
        VIEW_PLACE,
        VIEW_PRINTER,
        VIEW_PROCESSOR,
        VIEW_SOFTWARE,
        VIEW_SYSTEM,
        VIEW_TITLE,
        VIEW_ZIPCITY,
        VIEW_ZIPCODE
    };

    /**
     * @brief actualView
     */
    int actualView;

    /**
     * @brief m_actualView
     */
    QModelIndex m_actualView;

    /**
     * @brief m_actualData
     */
    QModelIndex m_actualData;
};
