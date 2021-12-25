/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "models/datacontext.h"

Model::DataContext::DataContext(QObject* parent)
    : QObject(parent)
    , m_Name(QApplication::applicationName())
    , m_dbType(DBTypes::SQLITE)
{
    qDebug() << tr("Öffne SQLite Datenbank");
    this->init();
}

Model::DataContext::DataContext(QObject* parent, const QString& name)
    : QObject(parent)
    , m_Name(name.isEmpty() ? QApplication::applicationName() : name)
    , m_dbType(DBTypes::SQLITE)
{
    qDebug() << tr("Öffne SQLite Datenbank") << this->m_Name;
    this->init();
}

Model::DataContext::DataContext(QObject* parent,
    const QString& name,
    const QString& dbType,
    const QString& userName,
    const QString& passWord,
    const QString& hostName,
    const int port)
    : QObject(parent)
    , m_Name(name.isEmpty() ? QApplication::applicationName() : name)
    , m_dbType(DBTypes::SQLITE)
    , m_dbHostName(hostName)
    , m_dbUserName(userName)
    , m_dbPassWord(passWord)
    , m_dbPort(port)
{
    qDebug() << tr("Öffne Datenbank") << this->m_Name << tr(" Type ") << dbType << tr(" Benutzername ") << userName
             << tr(" Password :-)  *********") << tr(" vom Server ") << hostName << tr(" mit dem Port ") << port;

    auto databaseType = QString(dbType);

    // Default is SQLITE
    if (databaseType == QString::fromLatin1("PGSQL")) {
        m_dbType = DBTypes::PGSQL;
    } else if (databaseType == QString::fromLatin1("ODBC")) {
        m_dbType = DBTypes::ODBC;
    } else if (databaseType == QString::fromLatin1("SQLITE")) {
        m_dbType = DBTypes::SQLITE;
    } else {
        m_dbType = DBTypes::SQLITE;
        qWarning() << "DataContext wurde mit dem Datenbank Typ " << databaseType << " aufgerufen."
                   << " Dieser Typ wird nicht unterstützt. Es geht weiter mit SQLITE";
    }

    this->init();
}

Model::DataContext::~DataContext()
{
    // this->m_db.close();

    qDebug() << tr("Datenbank geschlossen.");
}

void Model::DataContext::init()
{
    if (m_dbType == DBTypes::SQLITE) {
        this->setDatabaseConnection();

        QFile f(this->m_connectionString);
        if (!f.exists()) {
            qInfo() << tr("Erzeuge Sqlite Datenbank: ") << this->m_Name << " Datei " << this->m_connectionString;
            this->open(this->m_Name);
            this->prepareDB();
        } else {
            qInfo() << tr("Öffne Sqlite Datenbank:") << this->m_Name;
            this->open(this->m_Name);
        }
    } else if (m_dbType == DBTypes::ODBC) {
        qInfo() << tr("Öffne ODBC Datenbank: ") << this->m_Name << tr(" auf dem Server: ") << this->m_dbHostName;

        m_db = QSqlDatabase::addDatabase(QLatin1String("QODBC"));
        m_db.setHostName(this->m_dbHostName);
        m_db.setDatabaseName(this->m_Name);
        m_db.setUserName(this->m_dbUserName);
        m_db.setPassword(this->m_dbPassWord);
    } else if (m_dbType == DBTypes::PGSQL) {
        qInfo() << tr("Öffne PostgreSQL Datenbank: ") << this->m_Name << tr(" auf dem Server ") << this->m_dbHostName;

        m_db = QSqlDatabase::addDatabase(QLatin1String("QPSQL"));
        m_db.setHostName(this->m_dbHostName);
    }
}

void Model::DataContext::prepareDB() const
{
    QSqlQuery query(this->m_db);

    QFile file(QLatin1String(":/data/script.sql"));

    if (!file.exists()) {
        qCritical() << tr("Kritischer Fehler bei der Initialisierung der Datenbank.") << tr("Die Datei '") << file.fileName()
                    << tr("' zum initialisieren der Datenbank ") << tr(" und zum erzeugen der Tabellen konnten nicht gefunden werden.");
        return;
    }

    if (!file.open(QIODevice::ReadOnly)) {
        qCritical() << tr("Kritischer Fehler bei der Initialisierung der Datenbank.") << tr("Die Datei '") << file.fileName()
                    << tr(" zum initialisieren der Datenbank ") << tr("kann nicht geöffnet werden.");
    }

    QString line;
    QByteArray readLine;
    QString cleanedLine;
    QStringList strings;

    while (!file.atEnd()) {
        bool hasText = false;
        line = QLatin1String("");
        strings.clear();

        while (!hasText) {
            readLine = file.readLine();
            cleanedLine = QLatin1String(readLine.trimmed());
            strings = cleanedLine.split(QLatin1String("--"));
            cleanedLine = strings.at(0);
            if (!cleanedLine.startsWith(QLatin1String("--")) && !cleanedLine.startsWith(QLatin1String("DROP")) && !cleanedLine.isEmpty()) {
                line += cleanedLine;
            }
            if (cleanedLine.endsWith(QLatin1String(";"))) {
                break;
            }
            if (cleanedLine.startsWith(QLatin1String("COMMIT"))) {
                hasText = true;
            }
        }
        if (!line.isEmpty()) {
            if (!query.exec(line)) {
                qCritical() << tr("Fehler beim Lesen der Datei zur Datenbank Erzeugung: ") << tr("Fehler in der Zeile <") << line
                            << "> : " << tr("Fehlermeldung: ") << query.lastQuery() << " : " << query.lastError().text();
            }
        } else {
            qCritical() << tr("Fehler beim Lesen der Datei zur Datenbank Erzeugung:") << tr("Fehler in der Zeile <") << line
                        << "> : " << tr("Fehlermeldung: ") << query.lastQuery() << " : " << query.lastError().text();
        }
    }
    file.close();

    qDebug() << tr("Datenbank erfolgreich erzeugt");
}

auto Model::DataContext::checkDBVersion(const QString& actualVersion, const QString& actualRevision
    /* const QString &actualBuild */) const -> bool
{
    QString version;
    QString revision;
    QString build;
    QDateTime lastUpdate;
    bool retValue = false;

    QString queryString(QLatin1String("SELECT version, revision, patch, last_update FROM database_version"));
    QSqlQuery query(this->m_db);

    qDebug() << tr("Prüfe Datenbank Version ");

    query.exec(queryString);

    qDebug() << tr("Datenbankabfrage ( %1 ) Rückgabe : %2").arg(queryString, query.lastError().text());

    while (query.next()) {
        version = query.value(0).toString();
        qDebug() << "Version = " << version;
        revision = query.value(1).toString();
        build = query.value(2).toString();
        lastUpdate = query.value(3).toDateTime();
    }

    if ((version == actualVersion) && (revision == actualRevision)) {
        qDebug() << tr("Prüfe Datenbank Version : ") << version << "." << revision << "." << build << tr(" von ") << lastUpdate.toString();

        retValue = true;
    } else {
        if (version < actualVersion) {
            qCritical() << tr("Prüfe Datenbank Version : ") << tr("Datenbank zu alt. Version : ") << version << "  <> " << actualVersion
                        << "dbVersion : " << revision << " <> dbRevision : " << actualRevision;
        }

        if (revision < actualRevision) {
            qCritical() << tr("Prüfe Datenbank Version : ") << tr("Datenbank zu alt. Version : ") << version << "  <> " << actualVersion
                        << "dbVersion : " << revision << " <> dbRevision : " << actualRevision;
        }
    }

    return retValue;
}

auto Model::DataContext::checkExistence(const QString& tableName, const QString& searchId, const QString& search) -> bool
{
    auto queryStr = QString(QLatin1String("SELECT %1 FROM %2 WHERE %3 = \"%4\"")).arg(searchId, tableName, searchId, search);

    auto query = this->getQuery(queryStr);

    if (query.exec()) {
        if (query.next()) {
            return true;
        }
    } else {
        qWarning() << tr("Prüfe Datenbank Tabelle <") << tableName << "> auf " << searchId << " == " << search
                   << ") : " << query.lastError().text();
    }

    return false;
}

auto Model::DataContext::insert(const QString& tableName, const QVariantMap& insertData) const -> bool
{
    if (tableName.isEmpty()) {
        qCritical() << tr("Schwerer Fehler: ") << tr("Der Tabellename <m_Name> ist leer!");
        return false;

    } else if (insertData.isEmpty()) {
        qCritical() << tr("Schwerer Fehler: ") << tr("Es sind keine Daten für den Import vorhanden.");
        return false;
    }

    QStringList strValues;
    QStringList fields = insertData.keys();
    QVariantList values = insertData.values();
    int totalFields = fields.size();
    for (int i = 0; i < totalFields; ++i) {
        strValues.append(QLatin1String("?"));
    }

    QString sqlQueryString = QLatin1String("INSERT INTO ") + tableName + QLatin1String(" (") + QString(fields.join(QLatin1String(",")))
        + QLatin1String(") VALUES(") + QString(strValues.join(QLatin1String(","))) + QLatin1String(")");
    QSqlQuery query(this->m_db);
    query.prepare(sqlQueryString);

    int k = 0;
    for (const QVariant& value : values) {
        query.bindValue(k++, value);
    }
    return query.exec();
}

auto Model::DataContext::update(const QString& table, const QString& column, const QVariant& newValue, const QVariant& op, const QString& id) const -> bool
{
    auto searchStr = QLatin1String("\"");
    auto replaceStr = QLatin1String("\"\"");
    auto newValString = newValue.toString();
    auto realNewString = newValString.replace(searchStr, replaceStr);
    auto queryString = QLatin1String("UPDATA %1 SET %2 = \"%3\" WHERE %4 = \"%5\"");

    auto queryStr = QString(queryString).arg(table, column, realNewString, op.toString(), id);
    auto query = this->getQuery(queryStr);
    return query.exec();
}

auto Model::DataContext::getQuery(const QString& queryText) -> QSqlQuery
{
    QSqlQuery query(queryText);
    return query;
}

void Model::DataContext::open()
{
    auto name = this->m_Name;
    this->open(name);
}

void Model::DataContext::open(const QString& name)
{
    if (!QSqlDatabase::contains(name)) {
        qDebug() << tr("Öffne Datenbank : ") << name;

        this->m_db = QSqlDatabase::addDatabase(QLatin1String("QSQLITE"), name);
        this->m_db.setDatabaseName(this->m_connectionString);
    }

    if (!this->m_db.isOpen()) {
        if (!this->m_db.isValid()) {
            this->m_db = QSqlDatabase::database(name);
        }
        if (!this->m_db.open()) {
            qCritical() << tr("Fehler beim öffnen der Datenbank : ") << this->m_db.lastError().text() << name;
        } else {
            qDebug() << tr("Öffne Datenbank : ") << name;
            if (m_dbType == DBTypes::SQLITE) {
                auto query = QSqlQuery(this->m_db);
                if (!query.exec(QStringLiteral("PRAGMA synchronous=OFF"))) {
                    qCritical() << tr("Fehler beim setzen des Pragma: ") << tr("Fehlermeldung: ") << query.lastQuery() << " : "
                                << query.lastError().text();
                }
            }
        }
    }
}

void Model::DataContext::renameDB(const QString& newName)
{
    if (m_dbType == DBTypes::SQLITE) {
        QString oldConnection = this->m_connectionString;
        this->m_Name = newName;
        this->setDatabaseConnection();

        qDebug() << tr("Ändere den Namen der Datenbank : ") << oldConnection << tr(" Neuer Name: ") << this->m_connectionString;

        this->m_db.close();
        QFile f(oldConnection);
        f.rename(this->m_connectionString);
        this->open(newName);
    }
}

void Model::DataContext::deleteDB(const QString& dbName)
{
    qDebug() << tr("Lösche Datenbank") << dbName;

    this->m_db.close();

    // Delete File only by SQLITE Database
    if (m_dbType == DBTypes::SQLITE) {
        QFile f(this->m_connectionString);
        QSqlDatabase::removeDatabase(dbName);
        if (!f.remove()) {
            qCritical() << tr("Datenbankdatei ") << this->m_connectionString << tr(" konnte nicht gelöscht werden !");
        }
    }
}

void Model::DataContext::setDatabaseConnection()
{
    // QString dbDataPath = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    QString dbDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    // AppDataLocation
    // Create the Directory
    QDir writeDir(dbDataPath);
    if (!writeDir.exists()) {
        writeDir.mkpath(dbDataPath);
    }
    // Append the Datafile on the Path
    dbDataPath.append(QDir::separator());
    dbDataPath.append(this->m_Name);
    dbDataPath.append(QLatin1String(".sqlite3"));

    qDebug() << tr("Pfad und Name der Datenbank für SQLite: ") << dbDataPath;

    this->m_connectionString = dbDataPath;
}
