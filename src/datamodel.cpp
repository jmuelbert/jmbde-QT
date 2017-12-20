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

#include "accountdatamodel.h"
#include "chipcarddatamodel.h"
#include "chipcarddoorsdatamodel.h"
#include "chipcardprofiledatamodel.h"
#include "chipcardprofiledoordatamodel.h"
#include "citynamedatamodel.h"
#include "companydatamodel.h"
#include "computerdatamodel.h"
#include "computersoftwaredatamodel.h"
#include "departmentdatamodel.h"
#include "devicenamedatamodel.h"
#include "devicetypedatamodel.h"
#include "documentsdatamodel.h"
#include "employeedatamodel.h"
#include "faxdatamodel.h"
#include "functiondatamodel.h"
#include "inventorydatamodel.h"
#include "manufacturerdatamodel.h"
#include "mobiledatamodel.h"
#include "osdatamodel.h"
#include "phonedatamodel.h"
#include "placedatamodel.h"
#include "processordatamodel.h"
#include "softwaredatamodel.h"
#include "systemdatamodel.h"
#include "titledatamodel.h"
#include "zipcitymodel.h"
#include "zipcodemodel.h"

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

    // When the DB-Directory not create than do this.
    if (dbIsCreated == false) {

      QDir destDir(dbConnectionString);

      if (destDir.exists() == false) {
        if (destDir.mkpath(dbConnectionString) == false) {
          // TODO: Error handling
          qDebug() << "Can not create destination directoy...";
          return false;
        }
      }
    }

    db = QSqlDatabase::addDatabase(QLatin1String("QSQLITE"));
    db.setDatabaseName(targetFileAndPath);
    if (!db.open()) {
      qDebug() << "SQLite DB Exists                : " << retValue;
      qDebug() << "QSQLITE QSqlDriver::QuerySize   : "
               << db.driver()->hasFeature(QSqlDriver::QuerySize);  // FALSE
      qDebug() << "QSQLITE QSqlDriver::Transactions: "
               << db.driver()->hasFeature(QSqlDriver::Transactions); // TRUE
      qDebug() << initDb();
      retValue = false;
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

  if (!tables.contains("employee", Qt::CaseInsensitive)) return QSqlError();

  QSqlQuery q;
  QString queryString;

  AccountDataModel* acm = new AccountDataModel();
  if (!acm->createDataTable()) return db.lastError();


  ChipCardDataModel* ccm = new ChipCardDataModel();
  if (!ccm->createDataTable()) return db.lastError();

  ChipCardDoorsDataModel* ccdm = new ChipCardDoorsDataModel();
  if (!ccdm->createDataTable()) return db.lastError();

  ChipCardProfileDataModel* ccpm = new ChipCardProfileDataModel();
  if (!ccpm->createDataTable()) return db.lastError();

  ChipCardProfileDoorDataModel* ccpd = new ChipCardProfileDoorDataModel();
  if (!ccpd->createDataTable()) return db.lastError();

  CityNameDataModel* cnm = new CityNameDataModel();
  if (!acm->createDataTable()) return db.lastError();


  CompanyDataModel* cpm = new CompanyDataModel();
  if (!cpm->createDataTable()) return db.lastError();


  ComputerDataModel* cdm = new ComputerDataModel();
  if (!cdm->createDataTable()) return db.lastError();


  ComputerSoftwareDataModel* csd = new ComputerSoftwareDataModel();
  if (!csd->createDataTable()) return db.lastError();


  if (!q.exec(QString(Database::Table::ZIPCODE_CREATE)))
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

  if (!q.exec(QString(Database::Table::MANUFACTURER_CREATE)))
    return q.lastError();

  if (!q.exec(QString(Database::Table::DEPARTMENT_CREATE)))
    return q.lastError();

  if (!q.exec(QString(Database::Table::FUNCTION_CREATE)))
    return q.lastError();

  if (!q.exec(QString(Database::Table::EMPLOYEEACCOUNT_CREATE)))
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


  if (!q.exec(QString(Database::Table::SOFTWARE_CREATE)))
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
