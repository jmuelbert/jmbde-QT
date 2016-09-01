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
 * @version 0.3
 * @date 18.08.2016
 * @author Jürgen Mülbert
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
    QString *firstname;
    QString *middlename;
    QString *lastname;
    QString *street;
    QString *city;
    QString *zipcode;
    QDate birthday;
    QString *phonenumber;
    QString *faxnumber;
    QString *mobilenumber;
    QString *mail;
    QString *businessmail;
    QString *chipcard;
    bool datacare;
    bool active;
    QString *notes;
    QDate startdate;
    QDate enddate;
    qint32 departmentid;
    qint32 workfunctionid;
    qint32 placeid;
    QDate last_update;


private:


    /**
     * @brief The PosIEmployeeTable enum
     */
    enum PosEmployeeTable {
        POS_EMPLOYEE_ID,
        POS_EMPLOYEE_NR,
        POS_EMPLOYEE_GENDER,
        POS_EMPLOYEE_FIRSTNAME,
        POS_EMPLOYEE_MIDDLENAME,
        POS_EMPLOYEE_LASTNAME,
        POS_EMPLOYEE_STREET,
        POS_EMPLOYEE_CITY,
        POS_EMPLOYEE_ZIPCODE,
        POS_EMPLOYEE_BIRTHDAY,
        POS_EMPLOYEE_PHONENUMBER,
        POS_EMPLOYEE_FAXNUMBER,
        POS_EMPLOYEE_MOBILENUMBER,
        POS_EMPLOYEE_MAIL,
        POS_EMPLOYEE_BUSINESSMAIL,
        POS_EMPLOYEE_CHIPCARD,
        POS_EMPLOYEE_DATACARE,
        POS_EMPLOYEE_ACTIVE,
        POS_EMPLOYEE_PHOTO,
        POS_EMPLOYEE_NOTES,
        POS_EMPLOYEE_STARTDATE,
        POS_EMPLOYEE_ENDDATE,
        POS_EMPLOYEE_DEPARTMENTID,
        POS_EMPLOYEE_WORKFUNCTIONID,
        POS_EMPLOYEE_PLACEID,
        POS_EMPLOYEE_LASTUPDATE
    };
};
#endif // EMPLOYEEDATAMODEL_H
