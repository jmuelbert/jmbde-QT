/*
 *  SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
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

#include "jmbdewidgets_export.h"
// Models --------------------------
#include "jmbdemodels/account.h"
#include "jmbdemodels/chipcard.h"
#include "jmbdemodels/chipcarddoor.h"
#include "jmbdemodels/chipcardprofile.h"
#include "jmbdemodels/chipcardprofiledoor.h"
#include "jmbdemodels/cityname.h"
#include "jmbdemodels/company.h"
#include "jmbdemodels/computer.h"
#include "jmbdemodels/computersoftware.h"
#include "jmbdemodels/datacontext.h"
#include "jmbdemodels/department.h"
#include "jmbdemodels/devicename.h"
#include "jmbdemodels/devicetype.h"
#include "jmbdemodels/document.h"
#include "jmbdemodels/employee.h"
#include "jmbdemodels/employeeaccount.h"
#include "jmbdemodels/employeedocument.h"
#include "jmbdemodels/fax.h"
#include "jmbdemodels/function.h"
#include "jmbdemodels/inventory.h"
#include "jmbdemodels/manufacturer.h"
#include "jmbdemodels/mobile.h"
#include "jmbdemodels/os.h"
#include "jmbdemodels/phone.h"
#include "jmbdemodels/place.h"
#include "jmbdemodels/printer.h"
#include "jmbdemodels/processor.h"
#include "jmbdemodels/software.h"
#include "jmbdemodels/systemdata.h"
#include "jmbdemodels/title.h"
#include "jmbdemodels/zipcity.h"
#include "jmbdemodels/zipcode.h"

// Data Widgets --------------------------
#include "jmbdewidgets/accountinputarea.h"
#include "jmbdewidgets/chipcarddoorinputarea.h"
#include "jmbdewidgets/chipcardinputarea.h"
#include "jmbdewidgets/chipcardprofiledoorinputarea.h"
#include "jmbdewidgets/chipcardprofileinputarea.h"
#include "jmbdewidgets/cityinputarea.h"
#include "jmbdewidgets/companyinputarea.h"
#include "jmbdewidgets/computerinputarea.h"
#include "jmbdewidgets/computersoftwareinputarea.h"
#include "jmbdewidgets/definitions.h"
#include "jmbdewidgets/departmentinputarea.h"
#include "jmbdewidgets/devicenameinputarea.h"
#include "jmbdewidgets/devicetypeinputarea.h"
#include "jmbdewidgets/documentinputarea.h"
#include "jmbdewidgets/employeeaccountinputarea.h"
#include "jmbdewidgets/employeedocumentinputarea.h"
#include "jmbdewidgets/employeeinputarea.h"
#include "jmbdewidgets/employeetable.h"
#include "jmbdewidgets/faxinputarea.h"
#include "jmbdewidgets/functioninputarea.h"
#include "jmbdewidgets/inventoryinputarea.h"
#include "jmbdewidgets/manufacturerinputarea.h"
#include "jmbdewidgets/mobileinputarea.h"
#include "jmbdewidgets/osinputarea.h"
#include "jmbdewidgets/phoneinputarea.h"
#include "jmbdewidgets/placeinputarea.h"
#include "jmbdewidgets/printerinputarea.h"
#include "jmbdewidgets/processorinputarea.h"
#include "jmbdewidgets/softwareinputarea.h"
#include "jmbdewidgets/systemdatainputarea.h"
#include "jmbdewidgets/titleinputarea.h"
#include "jmbdewidgets/zipcitiyinputarea.h"
#include "jmbdewidgets/zipcodeinputarea.h"

// Widgets ---------------------------------
#include "jmbdewidgets/aboutdialog.h"
#include "jmbdewidgets/csvimportdialog.h"
#include "jmbdewidgets/preferencesdialog.h"

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

public slots:
    void actualizeAccountListView();
    void actualizeChipCardDoorListView();
    void actualizeChipCardListView();
    void actualizeChipCardProfileDoorListView();
    void actualizeChipCardProfileListView();
    void actualizeCityListView();
    void actualizeCompanyListView();
    void actualizeComputerListView();
    void actualizeComputerSoftwareListView();
    void actualizeDepartmentListView();
    void actualizeDeviceNameListView();
    void actualizeDeviceTypeListView();
    void actualizeDocumentListView();
    void actualizeEmployeeAccountListView();
    void actualizeEmployeeDocumentListView();
    void actualizeEmployeeListView();
    void actualizeFaxListView();
    void actualizeFunctionListView();
    void actualizeInventoryListView();
    void actualizeManufacturerListView();
    void actualizeMobileListView();
    void actualizeOsListView();
    void actualizePhoneListView();
    void actualizePlaceListView();
    void actualizePrinterListView();
    void actualizeProcessorListView();
    void actualizeSoftwareListView();
    void actualizeSystemDataListView();
    void actualizeTitleListView();
    void actualizeZipCityListView();
    void actualizeZipCodeListView();

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
    JMBDEWIDGETS_EXPORT void focusChanged(QWidget *from, QWidget *now);

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
    void JMBDEWIDGETS_EXPORT on_treeView_clicked(const QModelIndex &index);

    /**
     * @brief on_listView_clicked
     * @param index The QModelIndex of the ListViewRow to displayed
     */
    void JMBDEWIDGETS_EXPORT on_listView_clicked(const QModelIndex &index);

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
     * \fn void notAvailableMessage()
     * \brief notAvailableMessage
     *
     */
    void notAvailableMessage(const QString &functionName);

    void actualizeListView(QSqlTableModel *listModel, int idx);

    void preparePrint(QTextDocument &doc);

    /**
     * @brief model
     */
    QSqlRelationalTableModel *model{};

    /**
     * @brief tableModel
     */
    QSqlTableModel *tableModel{};

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
    QSplitter *m_splitter{};

    /**
     * @brief m_treeView
     */
    QTreeView *m_treeView{};

    /**
     * @brief m_listView
     */
    QListView *m_listView{};

    /**
     * @brief m_treeviewModel
     */
    QStandardItemModel *m_treeviewModel{};

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
        VIEW_EMPLOYEE_LIST,
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
        VIEW_SYSTEMDATA,
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
