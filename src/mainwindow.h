/*
 * mainwindow.h
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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QSettings>

#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>

#include <QMessageBox>

#include <QMainWindow>
#if QT_VERSION >= 0x050000
#include <QSql>
#include <QtWidgets>
#endif

#ifndef QT_NO_PRINTER
#include <QPrintDialog>
#include <QPrinter>
#include <QPrintPreviewDialog>
#endif


#include "constants.h"
#include "datamodell.h"
#include "accountdatamodel.h"
#include "commondatamodel.h"
#include "computerdatamodel.h"
#include "departmentdatamodel.h"
#include "devicetypedatamodel.h"
#include "employeedatamodel.h"
#include "employeeinputdialog.h"
#include "employeeinputdialog.h"
#include "functiondatamodel.h"
#include "inventorydatamodel.h"
#include "manufacturerdatamodel.h"
#include "pctypedatamodel.h"
#include "placedatamodel.h"
#include "systemdatamodel.h"
#include "csvimportdialog.h"

#include "printerdatamodel.h"
#include "phonedatamodel.h"

#include "preferencesdialog.h"
#include "computerinputdialog.h"

/**
 * Namespace for the UserInterface
 */
namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    /**
     * @brief MainWindow
     * @param parent
     */
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    /**
     * @brief closeEvent
     * @param event
     */
    void closeEvent(QCloseEvent *event);
    
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

    void on_actionOpen_triggered();

    void on_actionImport_triggered();

    void on_actionExport_triggered();

    void on_actionPrint_triggered();

    void on_action_Export_Pdf_triggered();

    void on_actionPrint_Preview_triggered();


    void on_actionEmployee_triggered();


    void on_radioButtonEmployee_toggled(bool checked);

    void on_radioButtonComputer_toggled(bool checked);

    void on_radioButtonPrinter_toggled(bool checked);

    void on_radioButtonPhone_toggled(bool checked);



    void on_pushButtonAddData_clicked();

    void on_QPushButtonSubmit_clicked();



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


    /**
     * @brief Not_Available_Message
     */
    void Not_Available_Message();
    /**
     * @brief em
     */
    DataModell *dm;
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
};

#endif // MAINWINDOW_H
