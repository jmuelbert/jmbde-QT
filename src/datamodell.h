/*
 * datamodell.h
 * jmbde
 *
 * Copyright (c) 2013,2014 Jürgen Mülbert. All rights reserved.
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
#include <QApplication>

#include <QMessageBox>
#if QT_VERSION >= 0x050000
#include <QSql>
#include <QStandardPaths>
#else
#include <QDesktopServices>
#endif


#include <QDate>
#include <QDir>
#include <QSettings>

#include <QDebug>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>
#include <QSqlDriver>

#include <QTableView>

/**
 * @brief The DataModell class
 */
class DataModell : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief DataModell
     * @param parent
     */
    DataModell(QObject *parent = 0);

    ~DataModell();

    /**
     * @brief CreateConnection
     * @return
     */
    bool CreateConnection();


    /**
     * @brief getDatabase
     * @return
     */
    QSqlDatabase getDatabase();
      void addRow(QTableView *);

      /**
     * @brief setOutTableStyle
     * @return
     */
    QString setOutTableStyle();
protected:
     /**
      * @brief db
      */
     QSqlDatabase db;



private:
     /**
      * @brief checkDBVersion
      * @return
      */
     bool checkDBVersion();

     const static qint16 dbVersion = 1;
     const static qint16 dbRevision = 0;
     const static qint16 dbPatch = 0;
signals:
    
public slots:
    
};

#endif // DATAMODELL_H
