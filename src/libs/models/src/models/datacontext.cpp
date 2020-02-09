/*
   jmbde a BDE Tool for companies
   Copyright (C) 2013-2019  Jürgen Mülbert

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
*/

#include "models/datacontext.h"

Model::DataContext::DataContext(QObject *parent, const QString &name, const QString &appId)
    : QObject(parent)
    , m_Name(name.isEmpty() ? QUuid::createUuid().toString() : name)
    , m_dbType(DBTypes::SQLITE)
    , m_AppID(appId.isEmpty() ? QUuid::createUuid().toString() : appId)
{
    qCDebug(jmbdemodelsLog, "Request Database : %s ", qUtf8Printable(this->m_Name));

    CreateConnection();
}

Model::DataContext::~DataContext()
{
    this->m_db.close();

    qCDebug(jmbdemodelsLog, "~DataContext()");
}

void Model::DataContext::CreateConnection()
{
    if (m_dbType == DBTypes::SQLITE) {
        const auto targetFileAndPath = this->getSqliteName();

        QFile f(targetFileAndPath);
        if (!f.exists()) {
            qCInfo(jmbdemodelsLog, "Create Sqlite Database: %s", qUtf8Printable(m_Name));

            m_db = QSqlDatabase::addDatabase(QLatin1String("QSQLITE"));
            m_db.setDatabaseName(targetFileAndPath);
            m_db.open();
            this->prepareDB();
        } else {
            qCInfo(jmbdemodelsLog, "Open Sqlite Database: %s", qUtf8Printable(m_Name));

            m_db = QSqlDatabase::addDatabase(QLatin1String("QSQLITE"));
            m_db.setDatabaseName(targetFileAndPath);
        }
    } else if (m_dbType == DBTypes::ODBC) {
        qCInfo(jmbdemodelsLog, "Open ODBC Database: %s on host %s", qUtf8Printable(this->m_Name), qUtf8Printable(this->m_dbHostName));

        m_db = QSqlDatabase::addDatabase(QStringLiteral("QODBC"));
        m_db.setHostName(this->m_dbHostName);
        m_db.setDatabaseName(this->m_Name);
        m_db.setUserName(this->m_dbUserName);
        m_db.setPassword(this->m_dbPassWord);
    } else if (m_dbType == DBTypes::PGSQL) {
        qCInfo(jmbdemodelsLog, "Open PostgreSQL Database: %s on host %s", qUtf8Printable(this->m_Name), qUtf8Printable(this->m_dbHostName));

        m_db = QSqlDatabase::addDatabase(QStringLiteral("QPSQL"));
        m_db.setHostName(this->m_dbHostName);
        m_db.setDatabaseName(this->m_Name);
        m_db.setUserName(this->m_dbUserName);
        m_db.setPassword(this->m_dbPassWord);
    } else {
        qCCritical(jmbdemodelsLog, "Unknown DB-Type!");
    }
}

void Model::DataContext::closeConnection()
{
}

void Model::DataContext::prepareDB()
{
    if (!this->m_db.isValid()) {
        this->m_db = QSqlDatabase::database(this->m_Name);
    }

    QSqlQuery query(this->m_db);

    QFile file(QStringLiteral(":/data/script.sql"));

    if (!file.exists()) {
        qCCritical(jmbdemodelsLog,
                   "Fatal error on build database. The file '%s' for database and "
                   "tables creation query cannot be not found!",
                   qUtf8Printable(file.fileName()));
    }

    if (!file.open(QIODevice::ReadOnly)) {
        qCCritical(jmbdemodelsLog,
                   "Fatal error on try to create database! The file with sql queries "
                   "for database creation cannot be opened!");
    }

    QString line;
    QByteArray readLine;
    QString cleanedLine;
    QStringList strings;

    while (!file.atEnd()) {
        bool hasText = false;
        line = QLatin1String("");
        readLine = QByteArray();
        cleanedLine = QLatin1String("");
        strings.clear();
        while (!hasText) {
            readLine = file.readLine();
            cleanedLine = QLatin1String(readLine.trimmed());
            strings = cleanedLine.split(QStringLiteral("--"));
            cleanedLine = strings.at(0);
            if (!cleanedLine.startsWith(QStringLiteral("--")) && !cleanedLine.startsWith(QStringLiteral("DROP")) && !cleanedLine.isEmpty()) {
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
                qCCritical(jmbdemodelsLog, "exec failed at line <%s>: %s, %s", qUtf8Printable(line), qUtf8Printable(query.lastQuery()), qUtf8Printable(query.lastError().text()));
            }

        } else {
            qCCritical(jmbdemodelsLog, "exec wrong at line <%s>: %s", qUtf8Printable(line), qUtf8Printable(query.lastError().text()));
        }
    }
    file.close();
}

auto Model::DataContext::checkDBVersion(const QString &actualVersion, const QString &actualRevision, const QString & /*actualBuild*/) -> bool
{
    QString version;
    QString revision;
    QString build;
    QDateTime lupdate;
    bool retValue = false;

    QSqlQuery query(QLatin1String("SELECT version, revision, patch, last_update FROM database_version"));

    qCDebug(jmbdemodelsLog, "CheckDBVersion, try getversion %s", qUtf8Printable(m_db.lastError().text()));

    while (query.next()) {
        version = query.value(0).toString();
        qDebug() << "Version = " << version;
        revision = query.value(1).toString();
        build = query.value(2).toString();
        lupdate = query.value(3).toDateTime();
    }

    if ((version == actualVersion) && (revision == actualRevision)) {
        qCDebug(jmbdemodelsLog, "Check DBVersion: OK - Version: %s.%s.%s from %s", qUtf8Printable(version), qUtf8Printable(revision), qUtf8Printable(build), qUtf8Printable(lupdate.toString()));

        retValue = true;
    } else {
        if (version < actualVersion) {
            qCCritical(jmbdemodelsLog,
                       "Check DBVersion: Database to old. Version : %s  <> "
                       "dbVersion : %s Revision : %s <> dbRevision : %s",
                       qUtf8Printable(version),
                       &actualVersion,
                       qUtf8Printable(revision),
                       &actualRevision);
        }

        if (revision < actualRevision) {
            qCCritical(jmbdemodelsLog,
                       "Check DBVersion: Database to old. Revision : %s  <> "
                       "dbVersion : %s Revision : %s <> dbRevision : %s",
                       qUtf8Printable(version),
                       &actualVersion,
                       qUtf8Printable(revision),
                       &actualRevision);
        }
    }

    return retValue;
}

auto Model::DataContext::check_existence(const QString &tableName, const QString &searchId, const QString &search) -> bool
{
    auto queryStr = QString(QStringLiteral("SELECT %1 FROM %2 WHERE %3 = \"%4\"")).arg(searchId, tableName, searchId, search);

    auto query = this->getQuery(queryStr);

    if (query.exec()) {
        if (query.next())
            return true;
    } else {
        qCWarning(jmbdemodelsLog, "CheckExistence(%s, %s, %s) : %s", qUtf8Printable(tableName), qUtf8Printable(searchId), qUtf8Printable(search), qUtf8Printable(query.lastError().text()));
    }

    return false;
}

auto Model::DataContext::insert(const QString &tableName, const QVariantMap &insertData) -> bool
{
    if (tableName.isEmpty()) {
        qCCritical(jmbdemodelsLog, "Fatal error on insert! The table m_Name is empty!");

    } else if (insertData.isEmpty()) {
        qCCritical(jmbdemodelsLog, "Fatal error on insert! The insertData is empty!");
    }

    QStringList strValues;
    QStringList fields = insertData.keys();
    QVariantList values = insertData.values();
    int totalFields = fields.size();
    for (int i = 0; i < totalFields; ++i) {
        strValues.append(QStringLiteral("?"));
    }

    QString sqlQueryString = QLatin1String("INSERT INTO ") + tableName + QLatin1String(" (") + QString(fields.join(QStringLiteral(","))) + QLatin1String(") VALUES(") + QString(strValues.join(QStringLiteral(","))) + QLatin1String(")");
    QSqlQuery query(this->m_db);
    query.prepare(sqlQueryString);

    int k = 0;
    for (const QVariant &value : values)
        query.bindValue(k++, value);

    return query.exec();
}

auto Model::DataContext::update(const QString &table, const QString &column, const QVariant &newValue, const QVariant &op, const QString &id) -> bool
{
    auto searchStr = QStringLiteral("\"");
    auto replaceStr = QStringLiteral("\"\"");
    auto newValString = newValue.toString();
    auto realNewString = newValString.replace(searchStr, replaceStr);
    auto queryString = QStringLiteral("UPDATA %1 SET %2 = \"%3\" WHERE %4 = \"%5\"");

    auto queryStr = QString(queryString).arg(table, column, realNewString, op.toString(), id);
    auto query = this->getQuery(queryStr);
    return query.exec();
}

auto Model::DataContext::execQuery(QSqlQuery &query) -> bool
{
    return query.exec();
}

auto Model::DataContext::execQuery(const QString &queryText) -> bool
{
    auto query = this->getQuery(queryText);
    return query.exec();
}

auto Model::DataContext::getQuery(const QString &queryText) -> QSqlQuery
{
    QSqlQuery query(queryText, this->m_db);
    return query;
}

auto Model::DataContext::openDB(const QString &m_Name) -> bool
{
    const auto dbFile = getSqliteName();
    if (!QSqlDatabase::contains(m_Name)) {
        qCDebug(jmbdemodelsLog, "openDB:Set default DB : %s", qUtf8Printable(m_Name));

        this->m_db = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"), m_Name);
        this->m_db.setDatabaseName(dbFile);
        return true;
    }

    if (!this->m_db.isValid()) {
        this->m_db = QSqlDatabase::database(m_Name);
    }

    if (!this->m_db.isOpen()) {
        if (!this->m_db.open()) {
        } else {
            qCWarning(jmbdemodelsLog, "openDB:DB yet open %s ", qUtf8Printable(m_db.databaseName()));

            return false;
        }
        return true;
    }

    return true;
}

void Model::DataContext::renameDB(const QString &oldName, const QString &newName)
{
    this->m_Name = newName;
    const QString newDBName = this->getSqliteName();

    if (!this->m_db.isValid()) {
        this->m_db = QSqlDatabase::database(oldName);
        QString oldFileName = this->m_db.databaseName();
        QFile f(oldFileName);
        f.rename(newName);
    }
}

void Model::DataContext::deleteDB(const QString &m_Name)
{
    if (!this->m_db.isValid()) {
        this->m_db = QSqlDatabase::database(m_Name);
        QString fileName = this->m_db.databaseName();
        QFile f(fileName);
        QSqlDatabase::removeDatabase(m_Name);
        f.remove();
    }
}

auto Model::DataContext::getDatabase() -> QSqlDatabase
{
    return m_db;
}

auto Model::DataContext::initDb() -> QSqlError
{
    return m_db.lastError();
}

void Model::DataContext::setDataBaseAccount(const QString &DBType, const QString &HostName, const QString &UserName, const QString &PassWord)
{
    auto dbType = QString(DBType);

    // Default is SQLITE
    m_dbType = DBTypes::SQLITE;
    if (dbType == QString::fromLatin1("PGSQL"))
        m_dbType = DBTypes::PGSQL;
    else if (dbType == QString::fromLatin1("ODBC"))
        m_dbType = DBTypes::ODBC;

    m_dbHostName = HostName;
    m_dbUserName = UserName;
    m_dbPassWord = PassWord;
}

auto Model::DataContext::getSqliteName() -> QString
{
    QString dbDataPath = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
    dbDataPath.append(QDir::separator());
    // TODO: Set this from above
    dbDataPath.append(m_AppID);

    // Application Directory +
    // Resources on Mac
    // share/appname on Linux
    // + /database/jmbdesqlite.db
    // Destination Directory
    QString targetFileAndPath = QString(m_connectionString);
    if (m_connectionString.isEmpty()) {
        targetFileAndPath = QString(dbDataPath);
    }
    // Create the Directory
    QDir d(targetFileAndPath);
    if (!d.exists())
        d.mkpath(targetFileAndPath);

    // Append the Datafile on the Path
    targetFileAndPath.append(QDir::separator());
    targetFileAndPath.append(this->m_Name);
    targetFileAndPath.append(QLatin1String(".sqlite"));

    qCDebug(jmbdemodelsLog, "getSqliteName %s ", qUtf8Printable(targetFileAndPath));

    return targetFileAndPath;
}
