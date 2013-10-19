/*
 * datamodell.h
 * jmbde
 *
 * Copyright (c) 2013 Jürgen Mülbert. All rights reserved.
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

#ifndef DATAMODELL_H
#define DATAMODELL_H

#include <QObject>
#include <QMessageBox>
#if QT_VERSION >= 0x050000
#include <QSql>
#include <QStandardPaths>
#ifdef QT_DEBUG
#include <QtWidgets>
#endif
#endif


#include <QDate>
#include <QDir>

#include <QDebug>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>



class DataModell : public QObject
{
    Q_OBJECT
public:
    explicit DataModell(QObject *parent = 0);
    bool CreateConnection();
    /**
     * @brief initializeModel
     * @param model
     */
    QSqlRelationalTableModel *initializeRelationalModel();
    QSqlTableModel *initializeEmployeeModel();
#ifdef QT_DEBUG
     void viewTableModell();
#endif



    /**
     * @brief createRelationalTables()
     */
     void createRelationalTables();
     /**
      * @brief AddEmployee
      */
     void AddEmployee();
     /**
      * @brief setFirstname
      */
     void setFirstname(QString *);

     /**
      * @brief setLastname
      */
     void setLastname(QString *);

protected:

     qint32 id;
     qint32 persnr;
     QString *firstname;
     QString *lastname;
     const QString *function;
     const QString *department;
     qint32 computer;
     qint32 phone;
     qint32 mobile;
     qint32 fax;
     qint32 documents;
     bool datenschutz;
     QDate creationTime;
     QDate updateTime;

private:

     /**
      * @brief db
      */
     QSqlDatabase db;

     /**
      * @brief The PosInTable enum
      */
     enum PosInTable {
         POS_ID,
         POS_PERSNR,
         POS_FIRSTNAME,
         POS_LASTNAME,
         POS_FUNCTION,
         POS_DEPARTMENT,
         POS_COMPUTER,
         POS_PHONE,
         POS_MOBILE,
         POS_FAX,
         POS_DOCUMENTS,
         POS_DATENSCHUTZ,
         POS_CREATIONTIME,
         POS_UPDATETIME
     };

#ifdef QT_DEBUG
    void CreateTestData();

#endif

signals:
    
public slots:
    
};

#endif // DATAMODELL_H
