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

#include "models/datacontext.h"

Model::DataContext::DataContext(QObject *parent, const QString &name)
    : QObject(parent),
      m_Name(name.isEmpty() ? QUuid::createUuid().toString() : name) {

#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 2)
    qCDebug(dataContextLC, "Request Database : %s ", qUtf8Printable(this->m_Name));
#else
   qDebug("Ctr:Request Database : %s ", qUtf8Printable(this->m_Name));
#endif
        CreateConnection();
      }

Model::DataContext::~DataContext() {
    this->m_db.close();
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 2)
    qCDebug(dataContextLC, "~DataContext()");
#else
    qDebug("~DataContext()");
#endif

}

void Model::DataContext::CreateConnection() {
    this->setDataBaseAccount();

    if (m_dbType == SQLITE) {
        const auto targetFileAndPath = this->getSqliteName();

        QFile f(targetFileAndPath);
        if (!f.exists()) {
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 2)
            qCInfo(dataContextLC, "Create Sqlite Database: %s", qUtf8Printable(m_Name));
#else
            qInfo("Create Sqlite Database: %s", qUtf8Printable(m_Name));
#endif
            m_db = QSqlDatabase::addDatabase(QLatin1String("QSQLITE"));
            m_db.setDatabaseName(targetFileAndPath);
            m_db.open();
            this->prepareDB();
        } else {
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 2)
            qCInfo(dataContextLC, "Open Sqlite Database: %s", qUtf8Printable(m_Name));
#else
            qInfo("Open Sqlite Database: %s", qUtf8Printable(m_Name));
#endif        
            m_db = QSqlDatabase::addDatabase(QLatin1String("QSQLITE"));
            m_db.setDatabaseName(targetFileAndPath);
        }
    } else if (m_dbType == MYSQL) {
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 2)
        qCInfo(dataContextLC, "Open MySQL Database: %s on host %s", qUtf8Printable(this->m_Name), qUtf8Printable(this->m_dbHostName));
#else
        qInfo("Open MySQL Database: %s on host %s", qUtf8Printable(this->m_Name), qUtf8Printable(this->m_dbHostName));        
#endif
        m_db = QSqlDatabase::addDatabase(QStringLiteral("QMYSQL"));
        m_db.setHostName(this->m_dbHostName);
        m_db.setDatabaseName(this->m_Name);
        m_db.setUserName(this->m_dbUserName);
        m_db.setPassword(this->m_dbPassWord);
    } else if (m_dbType == ODBC) {
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 2)
        qCInfo(dataContextLC, "Open ODBC Database: %s on host %s", qUtf8Printable(this->m_Name), qUtf8Printable(this->m_dbHostName));
#else
        qInfo("Open ODBC Database: %s on host %s", qUtf8Printable(this->m_Name), qUtf8Printable(this->m_dbHostName));        
#endif
        m_db = QSqlDatabase::addDatabase(QStringLiteral("QODBC"));
        m_db.setHostName(this->m_dbHostName);
        m_db.setDatabaseName(this->m_Name);
        m_db.setUserName(this->m_dbUserName);
        m_db.setPassword(this->m_dbPassWord);
    } else if (m_dbType == POSTGRESQL) {
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 2)
        qCInfo(dataContextLC, "Open PostgreSQL Database: %s on host %s", qUtf8Printable(this->m_Name), qUtf8Printable(this->m_dbHostName));
#else
        qInfo("Open PostgreSQL Database: %s on host %s", qUtf8Printable(this->m_Name), qUtf8Printable(this->m_dbHostName));        
#endif
        m_db = QSqlDatabase::addDatabase(QStringLiteral("QPSQL"));
        m_db.setHostName(this->m_dbHostName);
        m_db.setDatabaseName(this->m_Name);
        m_db.setUserName(this->m_dbUserName);
        m_db.setPassword(this->m_dbPassWord);
    } else {
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 2)
       qCCritical(dataContextLC, "Unknown DB-Type!");
#else       
       qCritical("Unknown DB-Type!");
#endif
    }
}

void Model::DataContext::closeConnection() { }

void Model::DataContext::prepareDB() {
    if (!this->m_db.isValid()) {
        this->m_db = QSqlDatabase::database(this->m_Name);
    }

    QSqlQuery query(this->m_db);

    QFile file(QStringLiteral(":/script.sql"));

    if (!file.exists()) {
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 2)
       qCCritical(dataContextLC,"Fatal error on build database. The file '%s' for database and "
               "tables creation query cannot be not found!",
               qUtf8Printable(file.fileName()));
#else
       qCritical("Fatal error on build database. The file '%s' for database and "
               "tables creation query cannot be not found!",
               qUtf8Printable(file.fileName()));
#endif   
    }

    if (!file.open(QIODevice::ReadOnly)) {
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 2)
        qCCritical(dataContextLC,
            "Fatal error on try to create database! The file with sql queries "
            "for database creation cannot be opened!");
#else
      qCritical(
            "Fatal error on try to create database! The file with sql queries "
            "for database creation cannot be opened!");
#endif
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
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 2)
                qCCritical(dataContextLC, "exec failed at line <%s>: %s, %s",
                         qUtf8Printable(line),
                         qUtf8Printable(query.lastQuery()),
                          qUtf8Printable(query.lastError().text()));
#else
                qCritical() << "exec failed" << line << query.lastQuery()
                         << query.lastError();

#endif
            }

        } else {
#if QT_VERSION >= QT_VERSION_CHECK(5,12, 2)
            qCCritical(dataContextLC, "exec wrong at line <%s>: %s",
                     qUtf8Printable(line),
                     qUtf8Printable(query.lastError().text()));
#else
            qDebug() << "exec wrong" << line << query.lastError();
#endif 
        }
    }
    file.close();
}

bool Model::DataContext::checkDBVersion() {
    QString version;
    QString revision;
    QString patch;
    QDateTime lupdate;
    bool retValue = false;

    QSqlQuery query(QLatin1String(
        "SELECT version, revision, patch, last_update FROM database_version"));

#if QT_VERSION >= QT_VERSION_CHECK(5,12, 2)
    qCDebug(dataContextLC, "CheckDBVersion, try getversion %s" ,
            qUtf8Printable(m_db.lastError().text()));
#else
    qDebug() << "CheckDBVersion, try getversion : "  << m_db.lastError().text();
#endif

    while (query.next()) {
        version = query.value(0).toString();
        qDebug() << "Version = " << version;
        revision = query.value(1).toString();
        patch = query.value(2).toString();
        lupdate = query.value(3).toDateTime();
    }

    if (version == QLatin1String(Database::Version::Version) &&
        revision == QLatin1String(Database::Version::Revision)) {
 #if QT_VERSION >= QT_VERSION_CHECK(5,12, 2)   
        qCDebug(dataContextLC, "Check DBVersion: OK - Version: %s.%s.%s fron %s", 
                qUtf8Printable(version), 
                qUtf8Printable(revision),
                qUtf8Printable(patch),
               qUtf8Printable(lupdate.toString()));
#else
       qDebug() << "Check DBVersion: OK - Version: " <<
                version << "." << 
                revision << "." << 
                patch << " from " << lupdate.toString();

#endif
        retValue = true;
    } else {
        if (version < QLatin1String(Database::Version::Version)) {
#if QT_VERSION >= QT_VERSION_CHECK(5,12, 2) 
            qCCritical(dataContextLC,
                "Check DBVersion: Database to old. Version : %s  <> dbVersion : %s Revision : %s <> dbRevision : %s",
                qUtf8Printable(version), 
                Database::Version::Version, 
                qUtf8Printable(revision), 
                Database::Version::Revision);
#else
            qCritical() <<
                "Check DBVersion: Database to old. Version : " << 
                " Version : " << version << "  <> dbVersion : " <<  Database::Version::Version << 
                " Revision : " << revision <<  "  <> dbRevision : " << Database::Version::Revision;
#endif
        }

        if (revision < QLatin1String(Database::Version::Revision)) {
#if QT_VERSION >= QT_VERSION_CHECK(5,12, 2) 
            qCCritical(dataContextLC,
                "Check DBVersion: Database to old. Revision : %s  <> dbVersion : %s Revision : %s <> dbRevision : %s",
                qUtf8Printable(version), 
                Database::Version::Version, 
                qUtf8Printable(revision), 
                Database::Version::Revision);
#else
            qCritical() <<
                "Check DBVersion: Database to old. Version : " << 
                " Version : " << version << "  <> dbVersion : " <<  Database::Version::Version << 
                " Revision : " << revision <<  "  <> dbRevision : " << Database::Version::Revision;
#endif
        }
    }

    return retValue;
}

bool Model::DataContext::check_existence(const QString &tableName,
                                         const QString &searchId,
                                         const QString &search) {
    auto queryStr =
        QString(QStringLiteral("SELECT %1 FROM %2 WHERE %3 = \"%4\""))
            .arg(searchId, tableName, searchId, search);

    auto query = this->getQuery(queryStr);

    if (query.exec()) {
        if (query.next())
            return true;
    } else {
#if QT_VERSION >= QT_VERSION_CHECK(5,12, 2) 
        qCWarning(dataContextLC, "CheckExistence(%s, %s, %s) : %s",
            qUtf8Printable(tableName),
            qUtf8Printable(searchId),
            qUtf8Printable(search), 
            qUtf8Printable(query.lastError().text()));
#else
        qWarning() << "CheckExistence( " << 
            tableName <<  " , " <<
            searchId << ", "  <<
            search << " ) :  " << 
            qUtf8Printable(query.lastError().text());
#endif
    }

    return false;
}

bool Model::DataContext::insert(const QString &tableName,
                                const QVariantMap &insertData) {
    if (tableName.isEmpty()) {
#if QT_VERSION >= QT_VERSION_CHECK(5,12, 2)         
       qCCritical(dataContextLC, "Fatal error on insert! The table m_Name is empty!");
#else
       qCritical("Fatal error on insert! The table m_Name is empty!");
#endif
    } else if (insertData.isEmpty()) {
#if QT_VERSION >= QT_VERSION_CHECK(5,12, 2) 
       qCCritical(dataContextLC, "Fatal error on insert! The insertData is empty!");
#else
       qCritical("Fatal error on insert! The insertData is empty!");
#endif
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
        QString(fields.join(QStringLiteral(","))) +
        QLatin1Literal(") VALUES(") +
        QString(strValues.join(QStringLiteral(","))) + QLatin1Literal(")");
    QSqlQuery query(this->m_db);
    query.prepare(sqlQueryString);

    int k = 0;
    for (const QVariant &value : values)
        query.bindValue(k++, value);

    return query.exec();
}

bool Model::DataContext::update(const QString &table, const QString &column,
                                const QVariant &newValue, const QVariant &op,
                                const QString &id) {
    auto searchStr = QStringLiteral("\"");
    auto replaceStr = QStringLiteral("\"\"");
    auto newValString = newValue.toString();
    auto realNewString = newValString.replace(searchStr, replaceStr);
    auto queryString =
        QStringLiteral("UPDATA %1 SET %2 = \"%3\" WHERE %4 = \"%5\"");

    auto queryStr = QString(queryString)
                        .arg(table, column, realNewString, op.toString(), id);
    auto query = this->getQuery(queryStr);
    return query.exec();
}

bool Model::DataContext::execQuery(QSqlQuery &query) const {
    if (query.exec())
        return true;
    return false;
}

bool Model::DataContext::execQuery(const QString &queryTxt) {
    auto query = this->getQuery(queryTxt);
    return query.exec();
}

QSqlQuery Model::DataContext::getQuery(const QString &queryTxt) {
    QSqlQuery query(queryTxt, this->m_db);
    return query;
}

bool Model::DataContext::openDB(const QString &m_Name) {
    const auto dbFile = getSqliteName();
    if (!QSqlDatabase::contains(m_Name)) {

#if QT_VERSION >= QT_VERSION_CHECK(5,12, 2) 
        qCDebug(dataContextLC,"openDB:Set default DB : %s", qUtf8Printable(m_Name));
#else
        qDebug("openDB:Set default DB : %s", qUtf8Printable(m_Name));
#endif
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
#if QT_VERSION >= QT_VERSION_CHECK(5,12, 2) 
            qCWarning(dataContextLC, "openDB:DB yet open %s ",
                     qUtf8Printable(m_db.databaseName()));
#else
            qWarning("openDB:DB yet open %s ",
                     qUtf8Printable(m_db.databaseName()));
#endif
            return false;
        }
        return true;
    }

    return true;
}

void Model::DataContext::renameDB(const QString &oldName,
                                  const QString &newName) {
    this->m_Name = newName;
    const QString newDBName = this->getSqliteName();

    if (!this->m_db.isValid()) {
        this->m_db = QSqlDatabase::database(oldName);
        QString oldFileName = this->m_db.databaseName();
        QFile f(oldFileName);
        f.rename(newName);
    }
}

void Model::DataContext::deleteDB(const QString &m_Name) {
    if (!this->m_db.isValid()) {
        this->m_db = QSqlDatabase::database(m_Name);
        QString fileName = this->m_db.databaseName();
        QFile f(fileName);
        m_db.removeDatabase(m_Name);
        f.remove();
    }
}



QSqlDatabase Model::DataContext::getDatabase() { return m_db; }

QSqlError Model::DataContext::initDb() { return m_db.lastError(); }

void Model::DataContext::setDataBaseAccount() {
    QSettings settings;
    settings.beginGroup(QLatin1String(Settings::Groups::DATABASE));
    m_dbType = settings.value(QLatin1Literal(Settings::Database::TYPE), SQLITE)
                   .toInt();

    m_dbHostName = settings
                       .value(QLatin1Literal(Settings::Database::HOSTNAME),
                              QLatin1String("localhost"))
                       .toString();

    m_dbUserName = settings
                       .value(QLatin1Literal(Settings::Database::USERNAME),
                              QLatin1String("localhost"))
                       .toString();

    m_dbPassWord = settings
                       .value(QLatin1Literal(Settings::Database::PASSWORD),
                              QLatin1String("localhost"))
                       .toString();

    settings.endGroup();
}

QString Model::DataContext::getSqliteName() {

    QString dbDataPath =
        QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
    dbDataPath.append(QDir::separator());
    // TODO: Set this from above
    dbDataPath.append(QLatin1Literal("io.github.jmuelbert.jmbde"));

    QSettings settings;
    settings.beginGroup(QLatin1String(Settings::Groups::DATABASE));

    const QString dbConnectionString =
        settings
            .value(QLatin1Literal(Settings::Database::CONNECTION), dbDataPath)
            .toString();

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
    targetFileAndPath.append(this->m_Name);
    targetFileAndPath.append(QLatin1Literal(".sqlite"));


#if (QT_VERSION >= QT_VERSION_CHECK(5,12, 2)) 
            qCDebug(dataContextLC, "getSqliteName %s ",
                     qUtf8Printable(targetFileAndPath));
#else
            qCDebug() <<  "getSqliteName :" <<
                     qUtf8Printable(targetFileAndPath);
#endif

    return targetFileAndPath;
}
