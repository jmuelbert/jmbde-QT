/*
   jmbde a BDE Tool for companies
   Copyright (C) 2013-2019  Jürgen Mülbert

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
*/

#pragma once

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

#include "definitions.h"

#include "jmbdewidgets-version.h"
#include "jmbdewidgets_export.h"
#include "loggingcategory.h"

#include "views/chipcardinputarea.h"
#include "views/cityinputarea.h"
#include "views/computerinputarea.h"
#include "views/csvimportdialog.h"
#include "views/departmentinputarea.h"
#include "views/employeeinputarea.h"
#include "views/functioninputarea.h"
#include "views/manufacturerinputarea.h"
#include "views/mobileinputarea.h"
#include "views/osinputarea.h"
#include "views/phoneinputarea.h"
#include "views/printerinputarea.h"
#include "views/processorinputarea.h"
#include "views/softwareinputarea.h"
#include "views/titleinputarea.h"

#include "models/cityname.h"
#include "models/datacontext.h"
#include "models/department.h"
#include "models/function.h"
#include "models/manufacturer.h"
#include "models/os.h"
#include "models/processor.h"
#include "models/software.h"
#include "models/title.h"

/**
 * Namespace for the UserInterface
 */
namespace Ui
{
class MainWindow;
}

/**
 * \class MainWindow
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow
     * @param parent The parent widget
     */
    explicit JMBDEWIDGETS_EXPORT MainWindow(QWidget *parent = nullptr);

    /**
     * @brief MainWindow::~MainWindow
     */
    JMBDEWIDGETS_EXPORT ~MainWindow();

protected:
    /**
     * @brief closeEvent
     * @param event The recived event
     */
    void JMBDEWIDGETS_EXPORT closeEvent(QCloseEvent *event);

    /**
     * @brief resizeEvent
     * @param event Tehe recived event
     */
    void JMBDEWIDGETS_EXPORT resizeEvent(QResizeEvent *event);

private slots:

    /**
     * @brief on_actionPreferences_triggered
     */
    void JMBDEWIDGETS_EXPORT on_actionPreferences_triggered();

    /**
     * @brief on_actionAbout_triggered
     */
    void JMBDEWIDGETS_EXPORT on_actionAbout_triggered();

    /**
     * \fn void on_actionNew_triggered()
     * \brief on_actionNew_triggered
     */
    void JMBDEWIDGETS_EXPORT on_actionNew_triggered();

    /**
     * \fn on_actionQuit_triggered()
     * \brief on_actionQuit_triggered
     */
    void JMBDEWIDGETS_EXPORT on_actionQuit_triggered();

    /**
     * @brief focusChanged
     * @param from The old focus widget
     * @param now The actual focus widget
     */
    void JMBDEWIDGETS_EXPORT focusChanged(QWidget *from, QWidget *now);

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
     * @brief onClickedTreeView
     * @param index The QModelIndex of the TreeView to displayed
     *
     * \see QModelIndex::QModelIndex
     */
    void JMBDEWIDGETS_EXPORT onClickedTreeView(const QModelIndex &index);

    /**
     * @brief onClickedListViewRow
     * @param index The QModelIndex of the ListViewRow to displayed
     */
    void JMBDEWIDGETS_EXPORT onClickedListViewRow(const QModelIndex &index);

    /**
     * @brief onPressedListViewRow
     * @param index The QModelIndex of the ListViewRow to displayed
     */
    void JMBDEWIDGETS_EXPORT onPressedListViewRow(const QModelIndex &index);

private:
    /**
     * @brief ui
     */
    Ui::MainWindow *ui;

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
     * \fn void Not_Available_Message()
     * \brief Not_Available_Message
     */
    void Not_Available_Message();

    /**
     * @brief model
     */
    QSqlRelationalTableModel *model;

    /**
     * @brief tableModel
     */
    QSqlTableModel *tableModel;

    /**
     * @brief dataBaseName
     */
    QString dataBaseName;

    /**
     * @brief dataContext
     */
    Model::DataContext *dataContext;

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
    QSplitter *m_splitter;

    /**
     * @brief m_treeView
     */
    QTreeView *m_treeView;

    /**
     * @brief m_listView
     */
    QListView *m_listView;

    /**
     * @brief m_treeviewModel
     */
    QStandardItemModel *m_treeviewModel;

    /**
     * @brief The ViewData enum
     */
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
