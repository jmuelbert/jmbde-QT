/*
   // EmployeeDataModel.h
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

#ifndef EMPLOYEEDATAMODEL_H
#define EMPLOYEEDATAMODEL_H

#include <QObject>
#include <QSet>
#include <QSetIterator>

#include <QStandardPaths>
#include <QtSql>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlRelation>

#include <QTableView>
#include <QTextDocument>

#include "datamodel.h"
#include "definitions.h"

/**
 * @brief EmployeeDataModel::EmployeeDataModel
 * @param parent
 *
 * The Datafields:
   -- - The title is Dr., Ing. and so on
   -- - address is foreign key for the address table
   -- - gender (m/w)
   -- - birthday of the employee
   -- - email address in the company
   -- - datacare in german datenschutz (y/n)
   --   or TRUE / FALSE
   -- - active is the employee real here
   -- - startdate  the employee is then here
   -- - enddate this is the last day
   -- - the foreign key to the department
   -- - the foreign key for the function of the employee
   -- - the foreign key to the computer
   -- - the foreign key to the printer
   -- - the foreign key to the inhouse phone
   -- - the foreign key to the mobile
   -- - the foreign key to the fax
   -- - the foreign key to the table of accounts
   -- - the foreign key to the table of documents
 *
 * digraph g {
 *  graph [
        rankdir = "LR";
    ];

    node [
        fontsize = "16";
        shape = "record";
        ];
    }
 */

class EmployeeDataModel : public DataModel {
  Q_OBJECT

  public:

    /**
     * @brief EmployeeDataModel
     * @param parent
     */
    EmployeeDataModel(QObject* parent = 0);

    /**
     * @brief ~EmployeeDataModel
     */
    ~EmployeeDataModel();

    /**
     * @brief initializeRelationalModel
     * @return
     */
    QSqlRelationalTableModel* initializeRelationalModel();

    /**
     * @brief initializeInputDataModel
     * @return
     */
    QSqlRelationalTableModel* initializeInputDataModel();
    QSqlTableModel* initializeViewModel();

    /**
     * @brief initializeTableModel
     * @return
     */
    QSqlTableModel* initializeTableModel();

    /**
     * @brief readAllRecords
     */
    void readAllRecords();

    /**
     * @brief createSheet
     * @return
     */
    QTextDocument* createSheet();

    /**
     * @brief generateTabletring
     * @param model
     * @param header
     * @return
     */
    QString generateTableString(QAbstractTableModel* model, QString header);

    /**
     * @brief setFirstname
     * @param _firstname
     */
    void setFirstname(QString*);

    /**
     * @brief setLastname
     * @param _lastname
     */
    void setLastname(QString*);

    /**
     * @brief The PosIEmployeeTable enum
     */
    enum PosEmployeeTable {
      POS_EMPLOYEE_ID,
      POS_EMPLOYEE_NR,
      POS_EMPLOYEE_GENDER,
      POS_EMPLOYEE_TITLE_ID,
      POS_EMPLOYEE_FIRSTNAME,
      POS_EMPLOYEE_LASTNAME,
      POS_EMPLOYEE_ADDRESS,
      POS_EMPLOYEE_BIRTHDAY,
      POS_EMPLOYEE_ZIPCITY_ID,
      POS_EMPLOYEE_HOMEPHONE,
      POS_EMPLOYEE_HOMEEMAIL,
      POS_EMPLOYEE_HOMEMOBILE,
      POS_EMPLOYEE_BUSINESSEMAIL,
      POS_EMPLOYEE_DATACARE,
      POS_EMPLOYEE_ACTIVE,
      POS_EMPLOYEE_PHOTO,
      POS_EMPLOYEE_NOTES,
      POS_EMPLOYEE_STARTDATE,
      POS_EMPLOYEE_ENDDATE,
      POS_EMPLOYEE_DEPARTMENT_ID,
      POS_EMPLOYEE_FUNCTION_ID,
      POS_EMPLOYEE_COMPUTER_ID,
      POS_EMPLOYEE_PRINTER_ID,
      POS_EMPLOYEE_PHONE_ID,
      POS_EMPLOYEE_MOBILE_ID,
      POS_EMPLOYEE_FAX_ID,
      POS_EMPLOYEE_EMPLOYEE_ACCOUNT_ID,
      POS_EMPLOYEE_EMPLOYEE_DOCUMENT_ID,
      POS_EMPLOYEE_CHIPCARD_ID,
      POS_EMPLOYEE_LAST_UPDATE
    };

  protected:

    /* The Datafields for Employees */
    qint32 employee_id;
    qint32 employee_nr;
    char gender[1];
    qint32 title_id;
    QString* firstname;
    QString* lastname;
    QDate birthday;
    QString* address;
    qint32 zipcity_id;
    QString* homephone;
    QString* homemobile;
    QString* homeemail;
    QString businessemail;
    bool datacare;
    bool active;
    char photo[8192];
    QString* notes; // Maxchar 50
    QDate startdate;
    QDate enddate;
    qint32 department_id;
    qint32 function_id;
    qint32 computer_id;
    qint32 printer_id;
    qint32 phone_id;
    qint32 mobile_id;
    qint32 fax_id;
    qint32 employee_account_id;
    qint32 employee_document_id;
    qint32 chipcard_id;
    QDate last_update;

  private:

    /**
     * @brief tableName - the name of the database table
     * @
     */
    const QString tableName = QLatin1String(Database::Table::EMPLOYEE);
    int idIdx;
    int GenderIdx;
    int TitleIdx;
    int FirstNameIdx;
    int LastNameIdx;
    int AddressIdx;
    int BirthDayIdx;
    int EmailIdx;
    int DataCareIdx;
    int ActiveIdx;
    int StartDateIdx;
    int EndDateIdx;
    int DepartmentIdx;
    int FunctionIdx;
    int ComputerIdx;
    int PrinterIdx;
    int PhoneIdx;
    int MobileIdx;
    int FaxIdx;
    int EmployeeAccountIdx;
    int EmployeeDocumentIdx;
    int LastUpdateIdx;
};

#endif // EMPLOYEEDATAMODEL_H
