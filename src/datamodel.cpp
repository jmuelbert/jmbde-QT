/*
   // DataModel
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

#include "datamodel.h"
#include "definitions.h"

DataModel::DataModel(QObject* parent) : QObject(parent) {}

DataModel::~DataModel() {
  db.commit();
  db.close();
}

bool DataModel::CreateConnection() {
  bool retValue = false;
  QSettings settings;
  QString dbName = qApp->applicationName();

// Read DB Settings
// Database settings
  QString dataBaseDir =
    QStandardPaths::writableLocation(QStandardPaths::DataLocation);

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
    const QString& _creatorTrPath = QCoreApplication::applicationDirPath();
    QDir trPath(_creatorTrPath);

    trPath.cdUp();
    const QString& creatorTrPath = trPath.path();
    QString databaseFileAndPath = QString(creatorTrPath);

    databaseFileAndPath.append(QDir::separator());
    databaseFileAndPath.append(QLatin1String("Resources"));
#else
    const QString& creatorTrPath = QCoreApplication::applicationDirPath();
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

    }
    else {
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
  }
  else if (dbType == MYSQL) {
    db = QSqlDatabase::addDatabase(QLatin1String("QMYSQL"));
    db.setHostName(dbHostName);
    db.setDatabaseName(dbName);
    db.setUserName(dbUserName);
    db.setPassword(dbPassWord);
    retValue = db.open();
  }
  else if (dbType == ODBC) {
    db = QSqlDatabase::addDatabase(QLatin1String("QODBC"));
    db.setHostName(dbHostName);
    db.setDatabaseName(dbName);
    db.setUserName(dbUserName);
    db.setPassword(dbPassWord);
    retValue = db.open();
  }
  else if (dbType == POSTGRESQL) {
    db = QSqlDatabase::addDatabase(QLatin1String("QPSQL"));
    db.setHostName(dbHostName);
    db.setDatabaseName(dbName);
    db.setUserName(dbUserName);
    db.setPassword(dbPassWord);
    retValue = db.open();
  }
  else {
    qDebug() << "Unknown DB-Type!";
    retValue = false;
  }

  if (retValue == true) {
    retValue = checkDBVersion();
  }
  else {
    qDebug() << db.lastError().databaseText();
    qDebug() << db.lastError().driverText();
  }

  return retValue;
}

bool DataModel::checkDBVersion() {
  QString version;
  QString revision;
  QString patch;
  QDateTime lupdate;
  QSqlQuery query(
    QLatin1String("SELECT version, revision, patch, last_update FROM database_version"));

  qDebug() << db.lastError().text();
  while (query.next()) {
    version = query.value(0).toString();
    qDebug() << "Version = " << version;
    revision = query.value(1).toString();
    patch = query.value(2).toString();
    lupdate = query.value(3).toDateTime();
  }

  if (version == Database::Version::Version && revision == Database::Version::Revision) {
    qDebug() << "Check Databaseverion: OK - Version: " << version << "." << revision << "." << patch << " from " << lupdate.toString();
    return true;
  }
  else {
    if (version < Database::Version::Version) {
      qDebug() << "Database to old. Updata in progress! Version : " << version
               << " <> dbVersion : " << Database::Version::Version
               << "Revision : " << revision
               << "<> dbRevision : " << Database::Version::Revision;
    }

    if (revision < Database::Version::Revision) {
      qDebug() << "Database to old. Updata in progress! Version : " << version
               << " <> dbVersion : " << Database::Version::Version
               << "Revision : " << revision
               << "<> dbRevision : " << Database::Version::Revision;
    }

    qDebug() << db.lastError().text();
  }

  return true;
}

QSqlDatabase DataModel::getDatabase() {
  return db;
}

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

  if (!q.exec(QString(Database::Table::CHIPCARD_CREATE)))
    return q.lastError();

  if (!q.exec(QString(Database::Table::CHIPCARDPROFILEDOOR_CREATE)))
    return q.lastError();

  if (!q.exec(QString(Database::Table::CHIPCARDPROFILE_CREATE)))
    return q.lastError();

  if (!q.exec(QString(Database::Table::DATABASEVERSION_CREATE)))
    return q.lastError();

  QSqlQuery query;

  query.prepare("INSERT INTO database_version (database_version_id, version, revision, patch, last_update)  " \
                "VALUES (:database_version_id, :version, :revision, :patch, :last_update)");
  query.bindValue(":database_version_id", 1);
  query.bindValue(":version", Database::Version::Version);
  query.bindValue(":revision", Database::Version::Revision);
  query.bindValue(":patch", Database::Version::Patch);
  query.bindValue(":last_update", QDateTime().toString());
  query.exec();
  qDebug() << "Set DB-Version: " << query.lastError();
  return q.lastError();
}

void DataModel::addRow(QTableView* tableView) {
  QAbstractItemModel* model = tableView->model();

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
