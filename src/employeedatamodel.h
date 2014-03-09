/*
 * EmployeeDataModel.h
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


#ifndef EMPLOYEEDATAMODEL_H
#define EMPLOYEEDATAMODEL_H


#include <QObject>
#include <QSet>
#include <QSetIterator>

#if QT_VERSION >= 0x050000
#include <QSql>
#include <QStandardPaths>
#endif

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>
#include <QSqlRecord>

#include <QTableView>
#include <QTextDocument>


#include "constants.h"
#include "datamodell.h"

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
 *	graph [
        rankdir = "LR";
    ];

    node [
        fontsize = "16";
        shape = "record";
        ];
    }
 */

class EmployeeDataModel : public DataModell
{

public:
    /**
      * @brief EmployeeDataModel
      * @param parent
      */
     EmployeeDataModel(QObject *parent = 0);

     /**
       * @brief ~EmployeeDataModel
       */
     ~EmployeeDataModel();

     /**
      * @brief addDataSet
      */
     void addDataSet();

     /**
     * @brief initializeRelationalModel
     * @return
     */
    QSqlRelationalTableModel *initializeRelationalModel();

    /**
     * @brief initializeInputDataModel
     * @return
     */
    QSqlRelationalTableModel *initializeInputDataModel();

    QSqlTableModel *initializeViewModel();

    /**
     * @brief initializeTableModel
     * @return
     */
    QSqlTableModel *initializeTableModel();

    /**
     * @brief readAllRecords
     */
    void readAllRecords();

    /**
       * @brief createSheet
       * @return
       */
      QTextDocument *createSheet();

      /**
       * @brief generateTabletring
       * @param model
       * @param header
       * @return
       */
      QString generateTableString(QAbstractTableModel *model, QString header);


    /**
     * @brief setFirstname
     * @param _firstname
     */
    void setFirstname(QString *);

    /**
     * @brief setLastname
     * @param _lastname
     */
    void setLastname(QString *);

protected:
    /* The Datafields for Employees */
    qint32 employee_id;
    qint32 employee_nr;
    char gender[1];
    qint32 title_id;
    QString *firstname;
    QString *lastname;
    qint32 address_id;
    QDate birthday;
    QString *email;
    bool datacare;
    bool active;
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
    QDate last_update;


private:


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
        POS_EMPLOYEE_ADDRESS_ID,
        POS_EMPLOYEE_BIRTHDAY,
        POS_EMPLOYEE_EMAIL,
        POS_EMPLOYEE_DATACARE,
        POS_EMPLOYEE_ACTIVE,
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
        POS_EMPLOYEE_LAST_UPDATE
    };
};
#endif // EMPLOYEEDATAMODEL_H
