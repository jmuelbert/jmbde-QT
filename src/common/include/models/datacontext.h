/**************************************************************************
**
** Copyright (c) 2013-2019 Jürgen Mülbert. All rights reserved.
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

#pragma once

#include <QObject>

#include <QDebug>

#include <QList>
#include <QLoggingCategory>
#include <QString>
#include <QStringList>

#include <QDir>
#include <QFileInfo>
#include <QVariantMap>

#include <QDate>

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

#include <QSettings>
#include <QStandardPaths>
#include <QUuid>

#include "definitions.h"
#include "jmbde_common_export.h"

/**
  \class DataContext
  \brief The Main Database class
  \details Here will handle all db actions...
  \author Jürgen Mülbert
  \version 0.4
  \date 14.12.2017
  \copyright EUPL V1.2

  \todo Remove UI for Testing
  \todo Move Code for every Table in his own class
 */

namespace Model {

class JMBDE_COMMON_EXPORT DataContext : public QObject {
    /*!
      \macro Q_OBJECT
      \relates QObject

      The Q_OBJECT macro must appear in the private section
      of a class definition that declares its own signals and
      slots, or that uses other services provided by Qt's
      meta-object system.

      ...

      \sa {Meta-Object System}, {Signals and Slots}, {QtsProperty System}
  */
    Q_OBJECT

    /*!
        \macro Q_LOGGING_CATEGORY
        \relates QLogging

        Defines the Logging Categorie for the class
     */
    Q_LOGGING_CATEGORY(dataContextLC, "jmbde.models.datacontext")
public:
    // TODO: Add Constructor: DataContext(const QString &name, + init for mySQL etc.)
    // TODO: Remove access of settings
    /*!
        \fn DataContext(QObject *parent = nullptr)

        \brief Constructor for the DataContext
        \details Constructor without a name for the database. This will create a uuid and connect with that the database.
     */
    explicit DataContext(QObject *parent = nullptr);

    /*!
        \fn DataContext( QObject *parent = nullptr,
                        const QString &name = QString() );

        \brief Constructor for the DataContext
        \details Contructur with a name for the database to use.
     */
    explicit DataContext(QObject *parent = nullptr, const QString &name = QString());

    /*!
          \fn  ~DataContext() override;

          \brief Destructor for DataContext()
          \details Close the connection to the database.
       */
      ~DataContext();

    /*!
        \fn void prepareDB()

        \brief Create the database from sql  
     */
    void prepareDB();

    /*!
        \fn  QSqlDatabase getDatabase()

        \brief Get the ref for the opened database

        \Returns the referenz
     */
    QSqlDatabase getDatabase();

    /*!
        \fn QSqlError initDb()
        \brief initDb get the db.lastError()
     
        Returns The last error from the Database
     */
    QSqlError initDb();

    /*!
        \fn bool execQuery(QSqlQuery &query) const
        
        \brief exec the QSqlQuery

        Returns true if the execution succesful
     */
    bool execQuery(QSqlQuery &query) const;

    /*!
        \fn bool execQuery(QString &queryText) const
        
        \brief exec the QString

        Returns true if the execution succesful
     */    
    bool execQuery(const QString &queryText);

    /* basic public actions */

    bool check_existence(const QString &tableNmae, const QString &searchId,
                         const QString &serach);

    /* useful actions */
    
    /*!
        \fn QSqlQuery getQuery(const QString &queryText)

        \brief get the query by the given queryText

        Return QSqlQuery

        \sa QSqlQuery
     */
    QSqlQuery getQuery(const QString &queryText);

    /*!
        \fn bool openDB(const QString &name)

        \brief Open the Database with the given name

        Returns true ist the database succesful opened.
     */
    bool openDB(const QString &name);

    /*!
        \fn   void renameDB(const QString &oldName, const QString &newName)

        \brief Rename the database to newName
     */
    void renameDB(const QString &oldName, const QString &newName);

    /*!
        \fn void deleteDB(const QString &name)

        \brief delete the database with the given name.
     */
    void deleteDB(const QString &name);

private:
    /*!
        \fn void CreateConnection()

        \brief Create the connection to the database

        \details calls from constructor. The CreateConnection
                 will Create for the four OS DB's the Connection.
                 By using sqlite is the system depend user directory
                 used.
     
        \todo init all tables
        \todo check database version
        \todo export and import all tables
     */
    void CreateConnection();

    /*!
        \fn void CloseConnection()

        \brief Close the connection to the database
        \details \edoes nothing

     */
    void CloseConnection();

    /*!
        \var QString m_Name
        \brief The holder for the DB-Name
     */
    QString m_Name;

    /*!
        \var QSqlDatabase m_db
        \brief the holder for the DB-Connection
     */
    QSqlDatabase m_db;

    /*!
        \var int m_dbType
        \brief The holder for the DB-Type
     */
    int m_dbType;

    /*!
        \var  QString m_dbHostName
        \brief The holder for the DB-Hostname
     */
    QString m_dbHostName;

   /*!
        \var  QString m_dbUserName
        \brief The holder for the DB-Username
     */
    QString m_dbUserName;

   /*!
        \var  QString m_dbPassWord
        \brief The holder for the DB-Password
     */
    QString m_dbPassWord;

    /*!
        \fn  void setDataBaseAccount()
        \brief Provide the DB-Connection
        \details Initial the Data for the Connection from
            the Settings
     */
    void setDataBaseAccount();

    /*!
        \fn bool checkDBVersion()
        \brief Check the Version of the DB
        
        Returns False has the DB a wrong version
     */
    bool checkDBVersion();

    /*!
        \fn bool insert(const QString &tableName, const QVariantMap &insertData)
        \brief insert the VariantMap in the table

        Returns true is successfull

        \sa QVariantMap
     */
    bool insert(const QString &tableName, const QVariantMap &insertData);

    /*!
        \fn  bool update(const QString &table, const QString &column,
                const QVariant &newValue, const QVariant &op,
                const QString &id)
        \brief Update the Data in the table

        Returns true is successfull
     */
    bool update(const QString &table, const QString &column,
                const QVariant &newValue, const QVariant &op,
                const QString &id);

    /*!
        \fn QString getSqliteName()
        \brief Generate the Connection-Strig for the sqlite Database.
     */
    QString getSqliteName();

signals:
    /*!
        \fn void DBActionFinished()
        \brief Signal for the DB-ACtion finished
     */
    void DBActionFinished();

public slots:
    /*!
        \fn void closeConnection()
        \brief Slot for close connection.
    */
    void closeConnection();
};
} // namespace Model

// Q_GLOBAL_STATIC(DataContext, db)
