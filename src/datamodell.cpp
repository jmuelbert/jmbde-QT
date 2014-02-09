/*
 * datamodell.cpp
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


/**
  * \brief The Main Database class
  * \detail Here will handle all db actions...
  * \author Jürgen Mülbert
  * \version 0.3
  * \date 16.11.2013
  * \copyright EUPL V1.1
  *
  * \todo Remove UI fpr Testing
  * \todo Move Code for every Table in his own class
  *
  * \page DataModel Page
  *
  *
  * This is the introduction.
  *
  */

#include "constants.h"
#include "datamodell.h"
/**
 * @brief DataModell::DataModell
 * @param parent
 */
DataModell::DataModell(QObject *parent) :
    QObject(parent)
{

}

DataModell::~DataModell() {
    db.commit();
    db.close();

}

/**
 * @brief DataModell::CreateConnection
 * @return
 *
 * /todo init all tables
 * /todo check database version
 * /tode export and import all tables
 */
bool DataModell::CreateConnection()
{
    bool retValue = false;
    QString CompanyName = QLatin1String(Constants::COMPANY_NAME);
    QString ApplicationName = QLatin1String(Constants::APPL_NAME);
    QSettings settings(CompanyName, ApplicationName);
    QString dbName = QLatin1String(Constants::APPL_NAME);

    // Read DB Settings
    // Database settings
#if QT_VERSION >= 0x050000
    QString dataBaseDir = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
#else
    QString dataBaseDir = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
#endif
    settings.beginGroup(QLatin1String(Settings::Groups::DATABASE));
    qint16 dbType = settings.value(QLatin1String(Settings::Database::TYPE), SQLITE).toInt();
    QString dbConnectionString = settings.value(QLatin1String(Settings::Database::CONNECTION), dataBaseDir).toString();
    QString dbHostName = settings.value(QLatin1String(Settings::Database::HOSTNAME), QLatin1String("localhost")).toString();
    QString dbUserName = settings.value(QLatin1String(Settings::Database::USERNAME), QLatin1String("jmbde")).toString();
    QString dbPassWord = settings.value(QLatin1String(Settings::Database::PASSWORD), QLatin1String("jmbde")).toString();


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
        databaseFileAndPath.append(QDir::separator());
        databaseFileAndPath.append(QLatin1String("database"));
        databaseFileAndPath.append(QDir::separator());
        databaseFileAndPath.append(dbName);
        databaseFileAndPath.append(QLatin1String("sqlite.db"));
        QFile srcDB(databaseFileAndPath);
        qDebug() << "Source-File : " << databaseFileAndPath;

        // Destination Directory
        QString targetFileAndPath =  QString(dbConnectionString);
        QDir d(targetFileAndPath);
        d.mkpath(targetFileAndPath);
        targetFileAndPath.append(QDir::separator());
        targetFileAndPath.append(dbName);
        targetFileAndPath.append(QLatin1String("sqlite.db"));
        QFile destDB(targetFileAndPath);
        qDebug() << "Destination-File : " << targetFileAndPath;
        qDebug() << "Connection-String : " << dbConnectionString;

        bool dbIsCreated = QFile::exists(targetFileAndPath);
        if (dbIsCreated == true) {
            db = QSqlDatabase::addDatabase(QLatin1String("QSQLITE"));
            db.setDatabaseName(targetFileAndPath);
            retValue = db.open();
            qDebug() << "SQLite DB Exists                : " << retValue;
            qDebug() << "QSQLITE QSqlDriver::QuerySize   : " << db.driver()->hasFeature(QSqlDriver::QuerySize); // FALSE
            qDebug() << "QSQLITE QSqlDriver::Transactions: " << db.driver()->hasFeature(QSqlDriver::Transactions); // TRUE

        } else {
            QDir destDir(dbConnectionString);

            if (destDir.exists() == false) {
                if (destDir.mkpath(dbConnectionString) == false) {
                    // TODO: Error handling
                    qDebug() << "Can not create destination directoy...";
                    return false;
                 }
             }

             bool ret = QFile::copy(databaseFileAndPath, targetFileAndPath);
             if (ret == false) {
                qDebug() << " Can not copy the db-file...";

             } else {
                db = QSqlDatabase::addDatabase(QLatin1String("QSQLITE"));
                db.setDatabaseName(targetFileAndPath);
                retValue = db.open();
            }
        }
    } else if (dbType == MYSQL) {
        db = QSqlDatabase::addDatabase(QLatin1String("QMYSQL"));
        db.setHostName(dbHostName);
        db.setDatabaseName(dbName);
        db.setUserName(dbUserName);
        db.setPassword(dbPassWord);
        retValue = db.open();
    } else if (dbType == ODBC) {
        db = QSqlDatabase::addDatabase(QLatin1String("QODBC"));
        db.setHostName(dbHostName);
        db.setDatabaseName(dbName);
        db.setUserName(dbUserName);
        db.setPassword(dbPassWord);
        retValue = db.open();
    } else if (dbType == POSTGRESQL) {
        db = QSqlDatabase::addDatabase(QLatin1String("QPSQL"));
        db.setHostName(dbHostName);
        db.setDatabaseName(dbName);
        db.setUserName(dbUserName);
        db.setPassword(dbPassWord);
        retValue = db.open();
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

bool DataModell::checkDBVersion() {
    qint16 version;
    qint16 revision;
    qint16 patch;

    QSqlQuery query(QLatin1String("SELECT name, version, revision FROM databaseversion"));
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
            qDebug() << "Database to old. Updata in progress! Version : " << version << " <> dbVersion : " << dbVersion;
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


QSqlDatabase DataModell::getDatabase() {
    return db;
}



/**
 * @brief DataModell::addRow
 * @param tableView
 */
void DataModell::addRow(QTableView *tableView)
{
    QAbstractItemModel *model = tableView->model();

     model->insertRow(model->rowCount());
}

/**
 * @brief DataModell::setOutTableStyle
 * @return
 */
QString DataModell::setOutTableStyle() {
    QString css;

    css = QLatin1String("<style type=\"text/css\">");
    css += QLatin1String("H1 { color: #f00;}");
    css += QLatin1String("table.tbl {border-width: 1px;border-style: solid;border-color: black;margin-top: 0px;margin-bottom: 0px;color: black; font-size: small; }");
    css += QLatin1String("table.tbl td {padding: 3px;}");
    css += QLatin1String("table.tbl th {padding: 3px;}");
    css+=QLatin1String("</style>");

    return css;
}
