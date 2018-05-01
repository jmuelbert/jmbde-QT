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

#include "datamodel.h"
#include "utils.h"

#include <QUuid>

DataModel::DataModel(QObject* parent) : QObject(parent)
{
    QSettings settings;
    QString dataBaseDir = QString();

    this->name = QUuid::createUuid().toString();
    const int dbType =
        settings.value(QLatin1String(Settings::Database::TYPE), SQLITE).toInt();

    const QString dbConnectionString =
        settings.value(QLatin1String(Settings::Database::CONNECTION), dataBaseDir)
        .toString();

    if (dbType == SQLITE) {
        // Application Directory +
        // Resources on Mac
        // share/appname on Linux
        // + /database/jmbdesqlite.db
        // Destination Directory
        QString targetFileAndPath = QString(dbConnectionString);
        // Create the Directory
        QDir d(targetFileAndPath);
        d.mkpath(targetFileAndPath);

        // Append the Datafile on the Path
        targetFileAndPath.append(QDir::separator());
        targetFileAndPath.append(this->name);
        targetFileAndPath.append(QLatin1String("sqlite.db3"));

        if (!Utils::fileExists(Utils::JmBdeDBPath + Utils::DBName)) {
            this->openDB(this->name);
            qDebug() << "DB doesn't exists, trying to create it" << targetFileAndPath;
            this->prepareDB();
        }
        else {
            this->openDB(this->name);
        }
    }
    else {
        qDebug() << "Now not supported";
        exit(1);
    }
}

DataModel::DataModel(const QString &name, QObject* parent) : QObject(parent)
{
    this->name = name.isEmpty() ? QUuid::createUuid().toString() : name;
    qDebug() << "Creating DB for: " << this->name;

    QString dbDataPath = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
    dbDataPath.append(QDir::separator());
    dbDataPath.append(QLatin1Literal("de.juergen-muelbert"));

    QSettings settings;
    settings.beginGroup(QLatin1String(Settings::Groups::DATABASE));
    const int dbType =
        settings.value(QLatin1Literal(Settings::Database::TYPE), SQLITE).toInt();

    const QString dbConnectionString =
        settings.value(QLatin1Literal(Settings::Database::CONNECTION), dbDataPath)
        .toString();
    settings.endGroup();


    qDebug() << "DbConnection from Settings : " << dbConnectionString;

    if (dbType == SQLITE) {
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
        d.mkpath(targetFileAndPath);

        // Append the Datafile on the Path
        targetFileAndPath.append(QDir::separator());
        targetFileAndPath.append(this->name);
        targetFileAndPath.append(QLatin1Literal("sqlite.db3"));
        QFile f(targetFileAndPath);

        if (!f.exists()) {
            this->openDB(targetFileAndPath);
            qDebug() << "DB doesn't exists, trying to create it" << targetFileAndPath;
            this->prepareDB();
        }
        else {
            this->openDB(targetFileAndPath);
        }
    }
    else {
        qDebug() << "Now not supported";
        exit(1);
    }
}

DataModel::~DataModel()
{
    this->m_db.close();
}

void DataModel::closeConnection()
{
    qDebug() << "Closeing Database";
}

void DataModel::prepareDB() const
{
    QSqlQuery query(this->m_db);

    QFile file(QStringLiteral(":/Data/models/script.sql"));

    if (!file.exists()) {
        QString log = QStringLiteral("Fatal error on build database. The file '");
        log.append(
            file.fileName() +
            QStringLiteral(
                "' for database and tables creation query cannot be not found!"));
        qDebug() << log;
        return;
    }

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << QStringLiteral(
                     "Fatal error on try to create database! The file with sql queries "
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
            if (!cleanedLine.startsWith(QStringLiteral("--")) && !cleanedLine.startsWith(QStringLiteral("DROP")) &&
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

        }
        else {
            qDebug() << "exec wrong" << line << query.lastError();
        }
    }
    file.close();
}

bool DataModel::CreateConnection()
{
    bool retValue = false;
    QSettings settings;


    // Read DB Settings
    // Database settings
    QString dataBaseDir =
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

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
                                this->name)
                         .toString();
    QString dbPassWord = settings
                         .value(QLatin1String(Settings::Database::PASSWORD),
                                this->name)
                         .toString();


    if (dbType == SQLITE) {

        // Application Directory +
        // Resources on Mac
        // share/appname on Linux
        // + /database/jmbdesqlite.db
        // Destination Directory
        QString targetFileAndPath = QString(dbConnectionString);
        // Create the Directory
        QDir d(targetFileAndPath);
        d.mkpath(targetFileAndPath);

        // Append the Datafile on the Path
        targetFileAndPath.append(QDir::separator());
        targetFileAndPath.append(this->name);
        targetFileAndPath.append(this->name);

        qDebug() << "Connection-String : " << dbConnectionString;
        qDebug() << "Destination-File : " << targetFileAndPath;

        // Check if the dbFile Exists
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

        m_db = QSqlDatabase::addDatabase(QLatin1String("QSQLITE"));
        qDebug() << "Database Path: " << targetFileAndPath;
        m_db.setDatabaseName(targetFileAndPath);
        retValue = m_db.open();
        if (retValue == true) {
            bool dbVersion = checkDBVersion();
            if (dbVersion == false) {
                QDate now =  QDate::currentDate();
                QString backupName = targetFileAndPath;
                backupName.append(QLatin1String("-"));
                backupName.append(now.toString(QLatin1String("yyyyMMdd")));
                QFile source(targetFileAndPath);
                source.rename(backupName);
                m_db.open();
                initDb();
            }
        }
    }
    else if (dbType == MYSQL) {
        m_db = QSqlDatabase::addDatabase(QStringLiteral("QMYSQL"));
        m_db.setHostName(dbHostName);
        m_db.setDatabaseName(this->name);
        m_db.setUserName(dbUserName);
        m_db.setPassword(dbPassWord);
        retValue = m_db.open();
    }
    else if (dbType == ODBC) {
        m_db = QSqlDatabase::addDatabase(QStringLiteral("QODBC"));
        m_db.setHostName(dbHostName);
        m_db.setDatabaseName(this->name);
        m_db.setUserName(dbUserName);
        m_db.setPassword(dbPassWord);
        retValue = m_db.open();
    }
    else if (dbType == POSTGRESQL) {
        m_db = QSqlDatabase::addDatabase(QStringLiteral("QPSQL"));
        m_db.setHostName(dbHostName);
        m_db.setDatabaseName(this->name);
        m_db.setUserName(dbUserName);
        m_db.setPassword(dbPassWord);
        retValue = m_db.open();
    }
    else {
        qDebug() << "Unknown DB-Type!";
        retValue = false;
    }

    if (retValue == true) {
        retValue = checkDBVersion();
    }
    else {
        qDebug() << m_db.lastError().databaseText();
        qDebug() << m_db.lastError().driverText();
    }

    return retValue;
}

bool DataModel::checkDBVersion()
{
    QString version;
    QString revision;
    QString patch;
    QDateTime lupdate;
    bool retValue = false;


    QSqlQuery query(
        QLatin1String("SELECT version, revision, patch, last_update FROM database_version"));

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
        qDebug() << "Check Databaseverion: OK - Version: " << version << "." << revision << "." << patch << " from " << lupdate.toString();
        retValue = true;
    }
    else {
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

bool DataModel::check_existence(const QString &tableName, const QString &searchId, const QString &search)
{
    auto queryStr = QString(QStringLiteral("SELECT %1 FROM %2 WHERE %3 = \"%4\"")).arg(searchId, tableName, searchId, search);

    auto query = this->getQuery(queryStr);

    qDebug() << queryStr << " : " << query.lastError();

    if (query.exec()) {
        if (query.next()) return true;
    }
    else {
        qDebug() << query.lastError().text();
    }

    return false;
}

bool DataModel::insert(const QString &tableName, const QVariantMap &insertData)
{
    if (tableName.isEmpty()) {
        qDebug() << QStringLiteral("Fatal error on insert! The table name is empty!");
        return false;
    }
    else if (insertData.isEmpty()) {
        qDebug() << QStringLiteral("Fatal error on insert! The insertData is empty!");
        return false;
    }

    QStringList strValues;
    QStringList fields = insertData.keys();
    QVariantList values = insertData.values();
    int totalFields = fields.size();
    for (int i = 0; i < totalFields; ++i) {
        strValues.append(QStringLiteral("?"));
    }

    QString sqlQueryString = QLatin1Literal("INSERT INTO ") + tableName +
                             QLatin1Literal(" (") + QString(fields.join(QStringLiteral(","))) +
                             QLatin1Literal(") VALUES(") +
                             QString(strValues.join(QStringLiteral(","))) + QLatin1Literal(")");
    QSqlQuery query(this->m_db);
    query.prepare(sqlQueryString);

    int k = 0;
    foreach (const QVariant &value, values)
        query.bindValue(k++, value);

    return query.exec();
}

bool DataModel::update(const QString &table, const QString &column, const QVariant &newValue, const QVariant &op, const QString &id)
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

bool DataModel::execQuery(QSqlQuery &query) const
{
    if (query.exec()) return true;
    qDebug() << "ERROR ON EXEC QUERY";
    qDebug() << query.lastError()  << query.lastQuery();
    return false;
}

bool DataModel::execQuery(const QString &queryTxt)
{
    auto query = this->getQuery(queryTxt);
    return query.exec();
}


void DataModel::openDB(const QString &name)
{
    if (!QSqlDatabase::contains(name)) {
        this->m_db = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"), name);
        this->m_db.setDatabaseName(name);
    }

    if (!this->m_db.isOpen()) {
        if (!this->m_db.open()) {
            qDebug() << "ERROR OPENING DB" << this->m_db.lastError().text() << m_db.connectionName();
        }
    }
}

QSqlQuery DataModel::getQuery(const QString &queryTxt)
{
    QSqlQuery query(queryTxt, this->m_db);
    return query;
}
QSqlDatabase DataModel::getDatabase()
{
    return m_db;
}

QSqlError DataModel::initDb()
{
    return m_db.lastError();
}
