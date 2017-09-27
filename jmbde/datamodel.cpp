/*
 * datamodell.cpp
 * jmbde
 *
 *  Copyright (c) 2013-2017 Jürgen Mülbert. All rights reserved.
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

#include "datamodel.h"
#include "constants.h"

DataModel::DataModel(QObject *parent) : QObject(parent) {}

DataModel::~DataModel() {
  db.commit();
  db.close();
}

bool DataModel::CreateConnection() {
  bool retValue = false;
  QString CompanyName = QLatin1String(Constants::COMPANY_NAME);
  QString ApplicationName = QLatin1String(Constants::APPL_NAME);
  QSettings settings(CompanyName, ApplicationName);
  QString dbName = QLatin1String(Constants::APPL_NAME);

// Read DB Settings
// Database settings
#if QT_VERSION >= 0x050000
  QString dataBaseDir =
      QStandardPaths::writableLocation(QStandardPaths::DataLocation);
#else
  QString dataBaseDir =
      QDesktopServices::storageLocation(QDesktopServices::DataLocation);
#endif
  settings.beginGroup(QLatin1String(Settings::Groups::DATABASE));
  int dbType =
      settings.value(QLatin1String(Settings::Database::TYPE), SQLITE).toInt();
  QString dbConnectionString =
      settings.value(QLatin1String(Settings::Database::CONNECTION), dataBaseDir)
          .toString();
  QString dbHostName = settings
                           .value(QLatin1String(Settings::Database::HOSTNAME),
                                  QLatin1String("localhost"))
                           .toString();
  QString dbUserName = settings
                           .value(QLatin1String(Settings::Database::USERNAME),
                                  QLatin1String("jmbde"))
                           .toString();
  QString dbPassWord = settings
                           .value(QLatin1String(Settings::Database::PASSWORD),
                                  QLatin1String("jmbde"))
                           .toString();

  if (dbType == SQLITE) {
#ifdef Q_OS_MAC
    const QString &_creatorTrPath = QCoreApplication::applicationDirPath();
    QDir trPath(_creatorTrPath);
    trPath.cdUp();
    const QString &creatorTrPath = trPath.path();

    QString databaseFileAndPath = QString(creatorTrPath);
    databaseFileAndPath.append(QDir::separator());
    databaseFileAndPath.append(QLatin1String("Resources"));
#else
    const QString &creatorTrPath = QCoreApplication::applicationDirPath();
    QString databaseFileAndPath = QString(creatorTrPath);
#endif

    // Application Directory +
    // Resources on Mac
    // share/appname on Linux
    // + /database/jmbdesqlite.db
    // Destination Directory
    QString targetFileAndPath = QString(dbConnectionString);
    QDir d(targetFileAndPath);
    d.mkpath(targetFileAndPath);
    targetFileAndPath.append(QDir::separator());
    targetFileAndPath.append(dbName);
    targetFileAndPath.append(QLatin1String("sqlite.db3"));
    QFile destDB(targetFileAndPath);
    qDebug() << "Destination-File : " << targetFileAndPath;
    qDebug() << "Connection-String : " << dbConnectionString;

    bool dbIsCreated = QFile::exists(targetFileAndPath);
    if (dbIsCreated == true) {
      db = QSqlDatabase::addDatabase(QLatin1String("QSQLITE"));
      db.setDatabaseName(targetFileAndPath);
      retValue = db.open();
      qDebug() << "SQLite DB Exists                : " << retValue;
      qDebug() << "QSQLITE QSqlDriver::QuerySize   : "
               << db.driver()->hasFeature(QSqlDriver::QuerySize); // FALSE
      qDebug() << "QSQLITE QSqlDriver::Transactions: "
               << db.driver()->hasFeature(QSqlDriver::Transactions); // TRUE
      qDebug() << initDb();

    } else {
      QDir destDir(dbConnectionString);

      if (destDir.exists() == false) {
        if (destDir.mkpath(dbConnectionString) == false) {
          // TODO: Error handling
          qDebug() << "Can not create destination directoy...";
          return false;
        }
      }

        qDebug() << " Create a new DB";
        db = QSqlDatabase::addDatabase(QLatin1String("QSQLITE"));
        db.setDatabaseName(targetFileAndPath);
        qDebug() << db.open();
        qDebug() << initDb();

    }
//  } else if (dbType == MYSQL) {
//    db = QSqlDatabase::addDatabase(QLatin1String("QMYSQL"));
//    db.setHostName(dbHostName);
//    db.setDatabaseName(dbName);
//    db.setUserName(dbUserName);
//    db.setPassword(dbPassWord);
//    retValue = db.open();
//  } else if (dbType == ODBC) {
//    db = QSqlDatabase::addDatabase(QLatin1String("QODBC"));
//    db.setHostName(dbHostName);
//    db.setDatabaseName(dbName);
//    db.setUserName(dbUserName);
//    db.setPassword(dbPassWord);
//    retValue = db.open();
//  } else if (dbType == POSTGRESQL) {
//    db = QSqlDatabase::addDatabase(QLatin1String("QPSQL"));
//    db.setHostName(dbHostName);
//    db.setDatabaseName(dbName);
//    db.setUserName(dbUserName);
//    db.setPassword(dbPassWord);
//    retValue = db.open();
  } else {
    qDebug() << "Unknown DB-Type!";
    retValue = false;
  }
  if (retValue == true) {
    retValue = checkDBVersion();
  } else {
    qDebug() << db.lastError().databaseText();
    qDebug() << db.lastError().driverText();
  }

  return retValue;
}

bool DataModel::checkDBVersion() {
  int version = 0;
  int revision = 0;
  int patch = 0;

  QSqlQuery query(
      QLatin1String("SELECT name, version, revision FROM databaseversion"));
  qDebug() << db.lastError().text();
  while (query.next()) {
    version = query.value(1).toInt();
    qDebug() << "Version = " << version;
    revision = query.value(2).toInt();
    patch = query.value(3).toInt();
  }

  if (version == dbVersion && revision == dbRevision && patch == dbPatch) {
    return true;
  } else {
    if (version < dbVersion) {
      qDebug() << "Database to old. Updata in progress! Version : " << version
               << " <> dbVersion : " << dbVersion;
    }
    if (revision < dbRevision) {
      qDebug() << "a better version of the Database is there. Update :)";
    }
    if (patch < dbPatch) {
      qDebug() << "a patched version of the database are here. Update :)";
    }
    qDebug() << db.lastError().text();
  }
  return true;
}

QSqlDatabase DataModel::getDatabase() { return db; }

QSqlError DataModel::initDb() {
    if (!db.open())
            return db.lastError();

    // Check the DB
    QStringList tables = db.tables();
    // if (!tables.contains("employee", Qt::CaseInsensitive)) return QSqlError();

    QSqlQuery q;
    QString queryString;

    if (!q.exec(QString(Database::Table::COMPANY_CREATE)))
        return q.lastError();

    if (!q.exec(QString(Database::Table::ZIPCODE_CREATE)))
        return q.lastError();

    if (!q.exec(QString(Database::Table::CITYNAME_CREATE)))
        return q.lastError();

    if (!q.exec((QString(Database::Table::ZIPCITY_CREATE))))
        return q.lastError();

    if (!q.exec(QString(Database::Table::TITLE_CREATE)))
        return q.lastError();

    if (!q.exec(QString(Database::Table::EMPLOYEE_CREATE)))
        return q.lastError();

    if (!q.exec(QString(Database::Table::DEVICETYPE_CREATE)))
        return q.lastError();

    if (!q.exec(QString(Database::Table::DEVICENAME_CREATE)))
        return q.lastError();

    if (!q.exec(QString(Database::Table::PLACE_CREATE)))
        return q.lastError();

    if (!q.exec(QString(Database::Table::INVENTORY_CREATE)))
        return q.lastError();

    if (!q.exec(QString(Database::Table::MANIFACTURER_CREATE)))
        return q.lastError();

    if (!q.exec(QString(Database::Table::DEPARTMENT_CREATE)))
        return q.lastError();

    if (!q.exec(QString(Database::Table::FUNCTION_CREATE)))
        return q.lastError();

    if (!q.exec(QString(Database::Table::EMPLOYEEACCOUNT_CREATE)))
        return q.lastError();

    if (!q.exec(QString(Database::Table::ACCOUNT_CREATE)))
        return q.lastError();

    if (!q.exec(QString(Database::Table::SYSTEMDATA_CREATE)))
        return q.lastError();

    if (!q.exec(QString(Database::Table::EMPLOYEEDOCUMENT_CREATE)))
        return q.lastError();

    if (!q.exec(QString(Database::Table::DOCUMENTS_CREATE)))
        return q.lastError();

    if (!q.exec(QString(Database::Table::PROCESSOR_CREATE)))
        return q.lastError();

    if (!q.exec(QString(Database::Table::OS_CREATE)))
        return q.lastError();

    if (!q.exec(QString(Database::Table::COMPUTERSOFTWARE_CREATE)))
        return q.lastError();

    if (!q.exec(QString(Database::Table::SOFTWARE_CREATE)))
        return q.lastError();

    if (!q.exec(QString(Database::Table::COMPUTER_CREATE)))
        return q.lastError();

    if (!q.exec(QString(Database::Table::PRINTER_CREATE)))
        return q.lastError();

    if (!q.exec(QString(Database::Table::PHONE_CREATE)))
        return q.lastError();

    if (!q.exec(QString(Database::Table::FAX_CREATE)))
        return q.lastError();

    if (!q.exec(QString(Database::Table::MOBILE_CREATE)))
        return q.lastError();

    if (!q.exec(QString(Database::Table::DATABASEVERSION_CREATE)))
        return q.lastError();

    return q.lastError();
}

void DataModel::addRow(QTableView *tableView) {
  QAbstractItemModel *model = tableView->model();

  model->insertRow(model->rowCount());
}

QString DataModel::setOutTableStyle() {
  QString css;

  css = QLatin1String("<style type=\"text/css\">");
  css += QLatin1String("H1 { color: #f00;}");
  css +=
      QLatin1String("table.tbl {border-width: 1px;border-style: "
                    "solid;border-color: black;margin-top: 0px;margin-bottom: "
                    "0px;color: black; font-size: small; }");
  css += QLatin1String("table.tbl td {padding: 3px;}");
  css += QLatin1String("table.tbl th {padding: 3px;}");
  css += QLatin1String("</style>");

  return css;
}
