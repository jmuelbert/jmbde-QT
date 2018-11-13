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

#include "libdatacontext.h"

#include "../jmbde/definitions.h"

#include <QUuid>

/*
LibDataContext::LibDataContext(QObject* parent) : QObject(parent)
{
    this->name = QUuid::createUuid().toString();

    QSettings settings;
    settings.beginGroup(QLatin1String(Settings::Groups::DATABASE));
    const int dbType =
        settings.value(QLatin1Literal(Settings::Database::TYPE),
SQLITE).toInt();

    const QString dbHostName =
        settings.value(QLatin1Literal(Settings::Database::HOSTNAME),
QLatin1String("localhost")).toString();

    const QString dbUserName =
        settings.value(QLatin1Literal(Settings::Database::USERNAME),
QLatin1String("user")).toString();

    const QString dbPassWord =
        settings.value(QLatin1Literal(Settings::Database::PASSWORD),
QLatin1String("123456")).toString();

    settings.endGroup();

    if (dbType == SQLITE) {
        const auto targetFileAndPath = this->getSqliteName();
        QFile f(targetFileAndPath);
        if (!f.exists()) {
            this->openDB(this->name);
            qDebug("DB doesn't exists, trying to create it %s",
qUtf8Printable(targetFileAndPath)); this->prepareDB();
        }
        else {
            this->openDB(this->name);
        }
    }
    else if (dbType == MYSQL) {
        m_db = QSqlDatabase::addDatabase(QStringLiteral("QMYSQL"));
        m_db.setHostName(dbHostName);
        m_db.setDatabaseName(this->name);
        m_db.setUserName(dbUserName);
        m_db.setPassword(dbPassWord);
    }
    else if (dbType == ODBC) {
        m_db = QSqlDatabase::addDatabase(QStringLiteral("QODBC"));
        m_db.setHostName(dbHostName);
        m_db.setDatabaseName(this->name);
        m_db.setUserName(dbUserName);
        m_db.setPassword(dbPassWord);
    }
    else if (dbType == POSTGRESQL) {
        m_db = QSqlDatabase::addDatabase(QStringLiteral("QPSQL"));
        m_db.setHostName(dbHostName);
        m_db.setDatabaseName(this->name);
        m_db.setUserName(dbUserName);
        m_db.setPassword(dbPassWord);
    }
    else {
        qDebug("Unknown DB-Type!");
        exit(0);
    }
}
*/

LibDataContext::LibDataContext(const QString &name, QObject *parent)
    : QObject(parent) {
  this->name = name.isEmpty() ? QUuid::createUuid().toString() : name;
  qDebug("Ctr:Request Database : %s ", qUtf8Printable(this->name));

  QSettings settings;
  settings.beginGroup(QLatin1String(Settings::Groups::DATABASE));
  const int dbType =
      settings.value(QLatin1Literal(Settings::Database::TYPE), SQLITE).toInt();

  const QString dbHostName =
      settings
          .value(QLatin1Literal(Settings::Database::HOSTNAME),
                 QLatin1String("localhost"))
          .toString();

  const QString dbUserName =
      settings
          .value(QLatin1Literal(Settings::Database::USERNAME),
                 QLatin1String("localhost"))
          .toString();

  const QString dbPassWord =
      settings
          .value(QLatin1Literal(Settings::Database::PASSWORD),
                 QLatin1String("localhost"))
          .toString();

  settings.endGroup();

  if (dbType == SQLITE) {

    const auto targetFileAndPath = this->getSqliteName();
    QFile f(targetFileAndPath);
    if (!f.exists()) {
      qInfo("Create Sqlite Database: %s", qUtf8Printable(name));
      this->openDB(name);
      this->prepareDB();
    } else {
      qInfo("Open Sqlite Database: %s", qUtf8Printable(name));
      this->openDB(name);
    }
  } else if (dbType == MYSQL) {
    qInfo("Connect to MySQL Database: %s", qUtf8Printable(this->name));
    m_db = QSqlDatabase::addDatabase(QStringLiteral("QMYSQL"));
    m_db.setHostName(dbHostName);
    m_db.setDatabaseName(this->name);
    m_db.setUserName(dbUserName);
    m_db.setPassword(dbPassWord);
  } else if (dbType == ODBC) {
    qInfo("Connect to MySQL Database: %s", qUtf8Printable(this->name));
    m_db = QSqlDatabase::addDatabase(QStringLiteral("QODBC"));
    m_db.setHostName(dbHostName);
    m_db.setDatabaseName(this->name);
    m_db.setUserName(dbUserName);
    m_db.setPassword(dbPassWord);
  } else if (dbType == POSTGRESQL) {
    qInfo("Connect to PostGreSQL Database: %s", qUtf8Printable(this->name));
    m_db = QSqlDatabase::addDatabase(QStringLiteral("QPSQL"));
    m_db.setHostName(dbHostName);
    m_db.setDatabaseName(this->name);
    m_db.setUserName(dbUserName);
    m_db.setPassword(dbPassWord);
  } else {
    qFatal("Unknown DB-Type!");
    exit(0);
  }
}

LibDataContext::~LibDataContext() {
  this->m_db.close();
  qDebug("m_db.close()");
}

void LibDataContext::closeConnection() { qDebug("Closing Database"); }

void LibDataContext::prepareDB() const {
  if (!this->m_db.isValid()) {
    QSqlDatabase::database(name);
  }

  QSqlQuery query(this->m_db);

  QFile file(QStringLiteral(":/script.sql"));

  if (!file.exists()) {
    qFatal("Fatal error on build database. The file '%s' for database and "
           "tables creation query cannot be not found!",
           qUtf8Printable(file.fileName()));
    return;
  }

  if (!file.open(QIODevice::ReadOnly)) {
    qFatal("Fatal error on try to create database! The file with sql queries "
           "for database creation cannot be opened!");
    return;
  }

  bool hasText;
  QString line;
  QByteArray readLine;
  QString cleanedLine;
  QStringList strings;

  while (!file.atEnd()) {
    hasText = false;
    line = QLatin1String("");
    readLine = QByteArray();
    cleanedLine = QLatin1String("");
    strings.clear();
    while (!hasText) {
      readLine = file.readLine();
      cleanedLine = QLatin1Literal(readLine.trimmed());
      strings = cleanedLine.split(QStringLiteral("--"));
      cleanedLine = strings.at(0);
      if (!cleanedLine.startsWith(QStringLiteral("--")) &&
          !cleanedLine.startsWith(QStringLiteral("DROP")) &&
          !cleanedLine.isEmpty()) {
        line += cleanedLine;
      }
      if (cleanedLine.endsWith(QStringLiteral(";")))
        break;
      if (cleanedLine.startsWith(QStringLiteral("COMMIT"))) {
        hasText = true;
      }
    }
    if (!line.isEmpty()) {
      if (!query.exec(line)) {
        qDebug() << "exec failed" << line << query.lastQuery()
                 << query.lastError();
      }

    } else {
      qDebug() << "exec wrong" << line << query.lastError();
    }
  }
  file.close();
}

bool LibDataContext::checkDBVersion() {
  QString version;
  QString revision;
  QString patch;
  QDateTime lupdate;
  bool retValue = false;

  QSqlQuery query(QLatin1String(
      "SELECT version, revision, patch, last_update FROM database_version"));

  qDebug() << m_db.lastError().text();
  while (query.next()) {
    version = query.value(0).toString();
    qDebug() << "Version = " << version;
    revision = query.value(1).toString();
    patch = query.value(2).toString();
    lupdate = query.value(3).toDateTime();
  }

  if (version == QLatin1String(Database::Version::Version) &&
      revision == QLatin1String(Database::Version::Revision)) {
    qDebug() << "Check Databaseverion: OK - Version: " << version << "."
             << revision << "." << patch << " from " << lupdate.toString();
    retValue = true;
  } else {
    if (version < QLatin1String(Database::Version::Version)) {
      qDebug() << "Database to old. Updata in progress! Version : " << version
               << " <> dbVersion : " << Database::Version::Version
               << "Revision : " << revision
               << "<> dbRevision : " << Database::Version::Revision;
    }

    if (revision < QLatin1String(Database::Version::Revision)) {
      qDebug() << "Database to old. Updata in progress! Version : " << version
               << " <> dbVersion : " << Database::Version::Version
               << "Revision : " << revision
               << "<> dbRevision : " << Database::Version::Revision;
    }

    qDebug() << m_db.lastError().text();
  }

  return retValue;
}

bool LibDataContext::check_existence(const QString &tableName,
                                  const QString &searchId,
                                  const QString &search) {
  auto queryStr = QString(QStringLiteral("SELECT %1 FROM %2 WHERE %3 = \"%4\""))
                      .arg(searchId, tableName, searchId, search);

  auto query = this->getQuery(queryStr);

  if (query.exec()) {
    if (query.next())
      return true;
  } else {
    qWarning("Warning : %s", qUtf8Printable(query.lastError().text()));
  }

  return false;
}

bool LibDataContext::insert(const QString &tableName,
                         const QVariantMap &insertData) {
  if (tableName.isEmpty()) {
    qFatal("Fatal error on insert! The table name is empty!");
    return false;
  } else if (insertData.isEmpty()) {
    qFatal("Fatal error on insert! The insertData is empty!");
    return false;
  }

  QStringList strValues;
  QStringList fields = insertData.keys();
  QVariantList values = insertData.values();
  int totalFields = fields.size();
  for (int i = 0; i < totalFields; ++i) {
    strValues.append(QStringLiteral("?"));
  }

  QString sqlQueryString =
      QLatin1Literal("INSERT INTO ") + tableName + QLatin1Literal(" (") +
      QString(fields.join(QStringLiteral(","))) + QLatin1Literal(") VALUES(") +
      QString(strValues.join(QStringLiteral(","))) + QLatin1Literal(")");
  QSqlQuery query(this->m_db);
  query.prepare(sqlQueryString);

  int k = 0;
  foreach (const QVariant &value, values)
    query.bindValue(k++, value);

  return query.exec();
}

bool LibDataContext::update(const QString &table, const QString &column,
                         const QVariant &newValue, const QVariant &op,
                         const QString &id) {
  auto searchStr = QStringLiteral("\"");
  auto replaceStr = QStringLiteral("\"\"");
  auto newValString = newValue.toString();
  auto realNewString = newValString.replace(searchStr, replaceStr);
  auto queryString =
      QStringLiteral("UPDATA %1 SET %2 = \"%3\" WHERE %4 = \"%5\"");

  auto queryStr =
      QString(queryString).arg(table, column, realNewString, op.toString(), id);
  auto query = this->getQuery(queryStr);
  return query.exec();
}

bool LibDataContext::execQuery(QSqlQuery &query) const {
  if (query.exec())
    return true;
  return false;
}

bool LibDataContext::execQuery(const QString &queryTxt) {
  auto query = this->getQuery(queryTxt);
  return query.exec();
}

bool LibDataContext::openDB(const QString &name) {
  const auto dbFile = getSqliteName();
  if (!QSqlDatabase::contains(name)) {
    qDebug("openDB:Set default DB : %s", qUtf8Printable(name));
    this->m_db = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"), name);
    this->m_db.setDatabaseName(dbFile);
    return true;
  }

  if (!this->m_db.isValid()) {
    this->m_db = QSqlDatabase::database(name);
  }

  if (!this->m_db.isOpen()) {
    if (!this->m_db.open()) {
    } else {
      qWarning("openDB:DB yet open %s ", qUtf8Printable(m_db.databaseName()));
      return false;
    }
    return true;
  }

  return true;
}

void LibDataContext::renameDB(const QString &oldName, const QString &newName) {
  this->name = newName;
  const QString newDBName = this->getSqliteName();

  if (!this->m_db.isValid()) {
    this->m_db = QSqlDatabase::database(oldName);
    QString oldFileName = this->m_db.databaseName();
    QFile f(oldFileName);
    f.rename(newName);
  }
}

void LibDataContext::deleteDB(const QString &name) {
  if (!this->m_db.isValid()) {
    this->m_db = QSqlDatabase::database(name);
    QString fileName = this->m_db.databaseName();
    QFile f(fileName);
    m_db.removeDatabase(name);
    f.remove();
  }
}

QSqlQuery LibDataContext::getQuery(const QString &queryTxt) {
  QSqlQuery query(queryTxt, this->m_db);
  return query;
}

QSqlDatabase LibDataContext::getDatabase() { return m_db; }

QSqlError LibDataContext::initDb() { return m_db.lastError(); }

QString LibDataContext::getSqliteName() {

  QString dbDataPath =
      QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
  dbDataPath.append(QDir::separator());
  dbDataPath.append(QLatin1Literal("de.juergen-muelbert"));

  QSettings settings;
  settings.beginGroup(QLatin1String(Settings::Groups::DATABASE));

  const QString dbConnectionString =
      settings.value(QLatin1Literal(Settings::Database::CONNECTION), dbDataPath)
          .toString();

  qDebug() << "getSqliteName:DbConnection from Settings : "
           << dbConnectionString;

  // Application Directory +
  // Resources on Mac
  // share/appname on Linux
  // + /database/jmbdesqlite.db
  // Destination Directory
  QString targetFileAndPath = QString();
  if (dbConnectionString.isEmpty()) {
    targetFileAndPath = QString(dbDataPath);
  } else {
    targetFileAndPath = QString(dbConnectionString);
  }

  // Create the Directory
  QDir d(targetFileAndPath);
  if (!d.exists())
    d.mkpath(targetFileAndPath);

  // Append the Datafile on the Path
  targetFileAndPath.append(QDir::separator());
  targetFileAndPath.append(this->name);
  targetFileAndPath.append(QLatin1Literal("sqlite.db3"));

  return targetFileAndPath;
}
