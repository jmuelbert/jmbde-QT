/**************************************************************************
**
** Copyright (c) 2013-2018 Jürgen Mülbert. All rights reserved.
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
#include "employeeaccountdatamodel.h"
#include "employeedatamodel.h"
#include "employeedocumentdatamodel.h"
#include "faxdatamodel.h"
#include "functiondatamodel.h"
#include "inventorydatamodel.h"
#include "manufacturerdatamodel.h"
#include "mobiledatamodel.h"
#include "osdatamodel.h"
#include "phonedatamodel.h"
#include "placedatamodel.h"
#include "printerdatamodel.h"
#include "processordatamodel.h"
#include "softwaredatamodel.h"
#include "systemdatamodel.h"
#include "titledatamodel.h"
#include "zipcitymodel.h"
#include "zipcodemodel.h"

#include "datamodel.h"
#include "definitions.h"

DataModel::DataModel(QObject *parent) : QObject(parent) {}

DataModel::~DataModel()
{
  db.commit();
  db.close();
}

bool DataModel::CreateConnection()
{
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

  if (dbType == SQLITE)
  {
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

    // When the DB-Directory not create than do this.
    if (dbIsCreated == false)
    {

      QDir destDir(dbConnectionString);

      if (destDir.exists() == false)
      {
        if (destDir.mkpath(dbConnectionString) == false)
        {
          // TODO: Error handling
          qDebug() << "Can not create destination directoy...";
          return false;
        }
      }
    }

    db = QSqlDatabase::addDatabase(QLatin1String("QSQLITE"));
    db.setDatabaseName(targetFileAndPath);
    if (!db.open())
    {
      qDebug() << "SQLite DB Exists                : " << retValue;
      qDebug() << "QSQLITE QSqlDriver::QuerySize   : "
               << db.driver()->hasFeature(QSqlDriver::QuerySize); // FALSE
      qDebug() << "QSQLITE QSqlDriver::Transactions: "
               << db.driver()->hasFeature(QSqlDriver::Transactions); // TRUE
      qDebug() << initDb();
      retValue = false;
    }
  }
  else if (dbType == MYSQL)
  {
    db = QSqlDatabase::addDatabase(QLatin1String("QMYSQL"));
    db.setHostName(dbHostName);
    db.setDatabaseName(dbName);
    db.setUserName(dbUserName);
    db.setPassword(dbPassWord);
    retValue = db.open();
  }
  else if (dbType == ODBC)
  {
    db = QSqlDatabase::addDatabase(QLatin1String("QODBC"));
    db.setHostName(dbHostName);
    db.setDatabaseName(dbName);
    db.setUserName(dbUserName);
    db.setPassword(dbPassWord);
    retValue = db.open();
  }
  else if (dbType == POSTGRESQL)
  {
    db = QSqlDatabase::addDatabase(QLatin1String("QPSQL"));
    db.setHostName(dbHostName);
    db.setDatabaseName(dbName);
    db.setUserName(dbUserName);
    db.setPassword(dbPassWord);
    retValue = db.open();
  }
  else
  {
    qDebug() << "Unknown DB-Type!";
    retValue = false;
  }

  if (retValue == true)
  {
    retValue = checkDBVersion();
  }
  else
  {
    qDebug() << db.lastError().databaseText();
    qDebug() << db.lastError().driverText();
  }

  return retValue;
}

bool DataModel::checkDBVersion()
{
  QString version;
  QString revision;
  QString patch;
  QDateTime lupdate;
  QSqlQuery query(
      QLatin1String("SELECT version, revision, patch, last_update FROM database_version"));

  qDebug() << db.lastError().text();
  while (query.next())
  {
    version = query.value(0).toString();
    qDebug() << "Version = " << version;
    revision = query.value(1).toString();
    patch = query.value(2).toString();
    lupdate = query.value(3).toDateTime();
  }

  if (version == QLatin1String(Database::Version::Version) && 
      revision == QLatin1String(Database::Version::Revision))
  {
    qDebug() << "Check Databaseverion: OK - Version: " << version << "." << revision << "." << patch << " from " << lupdate.toString();
    return true;
  }
  else
  {
    if (version < Database::Version::Version)
    {
      qDebug() << "Database to old. Updata in progress! Version : " << version
               << " <> dbVersion : " << Database::Version::Version
               << "Revision : " << revision
               << "<> dbRevision : " << Database::Version::Revision;
    }

    if (revision < Database::Version::Revision)
    {
      qDebug() << "Database to old. Updata in progress! Version : " << version
               << " <> dbVersion : " << Database::Version::Version
               << "Revision : " << revision
               << "<> dbRevision : " << Database::Version::Revision;
    }

    qDebug() << db.lastError().text();
  }

  return true;
}

QSqlDatabase DataModel::getDatabase()
{
  return db;
}

QSqlError DataModel::initDb()
{
  if (!db.open())
    return db.lastError();

  // Check the DB
  QStringList tables = db.tables();

  if (!tables.contains("employee", Qt::CaseInsensitive))
    return QSqlError();

  QSqlQuery q;
  QString queryString;

  AccountDataModel *acm = new AccountDataModel();
  if (!acm->createDataTable())
    return db.lastError();

  ChipCardDataModel *ccm = new ChipCardDataModel();
  if (!ccm->createDataTable())
    return db.lastError();

  ChipCardDoorsDataModel *ccdm = new ChipCardDoorsDataModel();
  if (!ccdm->createDataTable())
    return db.lastError();

  ChipCardProfileDataModel *ccpm = new ChipCardProfileDataModel();
  if (!ccpm->createDataTable())
    return db.lastError();

  ChipCardProfileDoorDataModel *ccpd = new ChipCardProfileDoorDataModel();
  if (!ccpd->createDataTable())
    return db.lastError();

  CityNameDataModel *cnm = new CityNameDataModel();
  if (!cnm->createDataTable())
    return db.lastError();

  CompanyDataModel *cpm = new CompanyDataModel();
  if (!cpm->createDataTable())
    return db.lastError();

  ComputerDataModel *cdm = new ComputerDataModel();
  if (!cdm->createDataTable())
    return db.lastError();

  ComputerSoftwareDataModel *csd = new ComputerSoftwareDataModel();
  if (!csd->createDataTable())
    return db.lastError();

  DepartmentDataModel *dpm = new DepartmentDataModel();
  if (!dpm->createDataTable()) return db.lastError();


  DeviceNameDataModel *dnm = new DeviceNameDataModel();
    if (!dnm->createDataTable()) return db.lastError();

    DeviceTypeDataModel *dtm = new DeviceTypeDataModel();
    if (!dtm->createDataTable()) return db.lastError();


    DocumentsDataModel *dcm = new DocumentsDataModel();
    if (!dcm->createDataTable()) return db.lastError();

    EmployeeAccountDataModel *ead = new EmployeeAccountDataModel();
    if (!ead->createDataTable()) return db.lastError();

    EmployeeDataModel *epm = new EmployeeDataModel();
    if (!epm->createDataTable()) return db.lastError();

    EmployeeDocumentDataModel *edm = new EmployeeDocumentDataModel();
    if (!edm->createDataTable()) return  db.lastError();


    FaxDataModel *fdm = new FaxDataModel();
    if (!fdm->createDataTable()) return db.lastError();


    FunctionDataModel *fudm = new FunctionDataModel();
    if (!fudm->createDataTable()) return db.lastError();


    InventoryDataModel *idm = new InventoryDataModel();
    if (!idm->createDataTable()) return db.lastError();


    ManufacturerDataModel *mdm = new ManufacturerDataModel();
    if (!mdm->createDataTable()) return db.lastError();

    MobileDataModel *modm = new MobileDataModel();
    if (!modm->createDataTable()) return db.lastError();

    OSDataModel *osd = new OSDataModel();
    if (!osd->createDataTable()) return db.lastError();

    PhoneDataModel *pdm = new PhoneDataModel();
    if (!pdm->createDataTable()) return db.lastError();


    PlaceDataModel *pld = new PlaceDataModel();
    if (!pld->createDataTable()) db.lastError();

    PrinterDataModel *prdm = new PrinterDataModel();
    if (!prdm->createDataTable()) return db.lastError();

    ProcessorDataModel *podm = new ProcessorDataModel();
    if (!podm->createDataTable()) return db.lastError();

    SoftwareDataModel *sod = new SoftwareDataModel();
    if (!sod->createDataTable()) return db.lastError();

    SystemDataModel *syd =new SystemDataModel();
    if (!syd->createDataTable()) return db.lastError();

    TitleDataModel *tdm = new TitleDataModel();
    if (!tdm->createDataTable()) return db.lastError();

    ZipCityModel *zcm = new ZipCityModel();
    if (!zcm->createDataTable()) return db.lastError();

    ZipCodeModel *zcom = new ZipCodeModel();
    if (!zcom->createDataTable()) return db.lastError();



  QSqlQuery query;

  QString sqlString = QLatin1String("CREATE TABLE database_version ("
                      "database_version_id INTEGER PRIMARY KEY, " \
                      "version VARCHAR(10), " \
                      "revision VARCHAR(10), " \
                      "patch VARCHAR(10), " \
                      "last_update TIMESTAMP);");
  query.exec(sqlString);
  query.prepare("INSERT INTO database_version (database_version_id, version, revision, patch, last_update)  "
                "VALUES (:database_version_id, :version, :revision, :patch, :last_update)");
  query.bindValue(QLatin1String(":database_version_id"), 1);
  query.bindValue(QLatin1String(":version"), Database::Version::Version);
  query.bindValue((QLatin1String(":revision"), Database::Version::Revision);
  query.bindValue(QLatin1String(":patch"), Database::Version::Patch);
  query.bindValue(QLatin1String(":last_update"), QDateTime().toString());
  query.exec();
  qDebug() << "Set DB-Version: " << query.lastError();
  return q.lastError();
}
