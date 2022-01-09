/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert
 * <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include <QApplication>
#include <QDate>
#include <QDir>
#include <QFileInfo>
#include <QList>
#include <QLoggingCategory>
#include <QObject>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QStandardPaths>
#include <QString>
#include <QStringList>
#include <QUuid>
#include <QVariantMap>

#include "commondata.h"

#include "jmbdemodels_export.h"

namespace Model {
/**
  \class DataContext
  \brief The Main Database class
  \details Here will handle all db actions...
  \author Jürgen Mülbert
  \version 0.6
  \date 25.12.2021
  \copyright GPL-3.0-or-later

  \todo Remove UI for Testing
  \todo Move Code for every Table in his own class
 */
class DataContext : public QObject {
  Q_OBJECT

public:
  // TODO: Add Constructor: DataContext(const QString &name, + init for mySQL
  // etc.)
  // TODO: Remove access of settings

  /*!
      \fn DataContext(QObject *parent = nullptr)

      \brief Constructor for the DataContext
      \details Constructur with a name for the database to use.
   */
  explicit JMBDEMODELS_EXPORT DataContext(QObject *parent = nullptr);

  /*!
      \fn DataContext( QObject *parent = nullptr,
                      const QString &name = QString() );

      \brief Constructor for the DataContext
      \details Constructur with a name for the database to use.
   */
  explicit JMBDEMODELS_EXPORT DataContext(QObject *parent, const QString &name);

  /*!
      \fn DataContext( QObject *parent = nullptr,
                      const QString &dbType = QString(),
                      const QString &name = QString(),
                      const QString &userName = QString(),
                      const QString &passWord = QString(),
                      const QString &hostName = QString(),
                      const int port = 0);


      \brief Constructor for the DataContext
      \details Constructur with a name for the database to use.
      \param parent - QObject
   \param name - Name of the Database
   \param dbType - String for the Database Type {SQLITE, ODBC, PostgreSQL}
      \param userName - Username for login in the Database Server
      \param passWord - Password for login in the Database Server
      \param hostName - Hostname or IP-Address from the Database Server
      \param port - Port for connect to the Database Server
   */

  explicit JMBDEMODELS_EXPORT
  DataContext(QObject *parent, const QString &name, const QString &dbType,
              const QString &userName, const QString &passWord,
              const QString &hostName, const int port);

  /*!
        \fn  ~DataContext() override;

        \brief Destructor for DataContext()
        \details Close the connection to the database.
     */
  JMBDEMODELS_EXPORT ~DataContext();

  /*!
      \fn QSqlDatabase getDatabase()

      \brief get the reference to the QSqlDatabase
  */
  JMBDEMODELS_EXPORT auto getDatabase() -> const QSqlDatabase { return m_db; }

  /*!
      \fn  QSqlQuery getQuery(const QString &queryText);

      \brief get the result of the Query from the text
      \param query - the db quey

      \return true if the execution successful
      \sa QSqlQuery
   */

  JMBDEMODELS_EXPORT static auto getQuery(const QString &query) -> QSqlQuery;

  /* basic public actions */

  JMBDEMODELS_EXPORT auto checkExistence(const QString &tableName,
                                         const QString &searchId,
                                         const QString &search) -> bool;

  /* useful actions */

  /*!
      \fn void open()

      \brief Open the Database with the given name
   */
  JMBDEMODELS_EXPORT void open();

  /*!
      \fn void openDB(const QString &name)

      \brief Open the Database with the given name
   */
  JMBDEMODELS_EXPORT void open(const QString &name);

  /*!
      \fn   void renameDB(const QString &oldName, const QString &newName)

      \brief Rename the database to newName
   */
  JMBDEMODELS_EXPORT void renameDB(const QString &newName);

  /*!
      \fn void deleteDB(const QString &name)

      \brief delete the database with the given name.
   */
  JMBDEMODELS_EXPORT void deleteDB(const QString &name);

protected:
  /*!
      \fn void init()

      \brief Create the connection to the database

      \details calls from constructor. The CreateConnection
               will Create for the four OS DB's the Connection.
               By using sqlite is the system depend user directory
               used.

      \todo init all tables
      \todo check database version
      \todo export and import all tables
   */
  void init();

  /*!
      \fn void prepareDB()

      \brief Create the database from sql
   */
  void prepareDB() const;

  /*!
      \fn bool checkDBVersion()
      \brief Check the Version of the DB

      \return False has the DB a wrong version
   */
  auto checkDBVersion(
      const QString &actualVersion,
      const QString &actualRevision /*, const QString &actualBuild */) const
      -> bool;

  /*!
      \fn bool insert(const QString &tableName, const QVariantMap &insertData)
      \brief insert the VariantMap in the table

      \return true is successful

      \sa QVariantMap
   */
  auto insert(const QString &tableName, const QVariantMap &insertData) const
      -> bool;

  /*!
      \fn  bool update(const QString &table, const QString &column,
              const QVariant &newValue, const QVariant &op,
              const QString &id)
      \brief Update the Data in the table

      \return true is successful
   */
  auto update(const QString &table, const QString &column,
              const QVariant &newValue, const QVariant &op,
              const QString &id) const -> bool;

  /*!
      \fn QString getSqliteName()
      \brief Generate the Connection-Strig for the sqlite Database.
   */
  void setDatabaseConnection();

  enum DBTypes { SQLITE, PGSQL, ODBC };

signals:
  /*!
      \fn void DBActionFinished()
      \brief Signal for the DB-ACtion finished
   */
  JMBDEMODELS_EXPORT void DBActionFinished();

public slots:

private:
  /*!
      \var QString m_Name
      \brief The holder for the DB-Name
   */
  QString m_Name;

  /*!
      \var QString m_connectionString for the SQliteDB
  */
  QString m_connectionString;

  /*!
      \var QSqlDatabase m_db
      \brief the holder for the DB-Connection
   */
  QSqlDatabase m_db;

  /*!
      \var int m_dbType
      \brief The holder for the DB-Type
   */
  int m_dbType{0};

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

  int m_dbPort{0};
};
} // namespace Model

// Q_GLOBAL_STATIC(DataContext, db)
