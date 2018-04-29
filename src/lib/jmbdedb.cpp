#include "jmbdedb.h"
#include "utils.h"

#include <QUuid>

JmBdeDB::JmBdeDB(QObject* parent) : QObject(parent)
{
    this->name = QUuid::createUuid().toString();
    if (!Utils::fileExists(Utils::JmBdeDBPath + Utils::DBName)) {
        this->openDB(this->name);
        qDebug() << "DB doesn't exists, trying to create it"
                 << Utils::JmBdeDBPath + Utils::DBName;
        this->prepareJmBdeDB();
    }
    else {
        this->openDB(this->name);
    }
}

JmBdeDB::JmBdeDB(const QString &name, QObject* parent) : QObject(parent)
{
    this->name = name.isEmpty() ? QUuid::createUuid().toString() : name;
    qDebug() << "Creating DB for: " << this->name;

    if (!Utils::fileExists(Utils::JmBdeDBPath + Utils::DBName)) {
        this->openDB(this->name);
        qDebug() << "DB doesn't exists, trying to create it"
                 << Utils::JmBdeDBPath + Utils::DBName;
        this->prepareJmBdeDB();
    }
}

JmBdeDB::~JmBdeDB()
{
    this->m_db.close();
}

void JmBdeDB::closeConnection()
{
    qDebug() << "CLOSING JmBdeDB";
}

void JmBdeDB::prepareJmBdeDB() const
{
    QSqlQuery query(this->m_db);

    QFile file(QLatin1Literal(":/Data/db/script.sql"));

    if (!file.exists()) {
        QString log = QStringLiteral("Fatal error on build database. The file '");
        log.append(file.fileName() + QStringLiteral("' for database and tables creation query cannot be not found!"));
        qDebug() << log;
        return;
    }

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << QStringLiteral("Fatal error on try to create database! The file with sql queries for database creation cannot be opened!");
        return;
    }

    bool hasText;
    QString line;
    QByteArray readLine;
    QString cleanedLine;
    QStringList strings;

    while (!file.atEnd()) {
        hasText     = false;
        line        = QLatin1String("");
        readLine    = QByteArray();
        cleanedLine = QLatin1String("");
        strings.clear();
        while (!hasText) {
            readLine    = file.readLine();
            cleanedLine = QLatin1String(readLine.trimmed());
            strings     = cleanedLine.split(QStringLiteral("--"));
            cleanedLine = strings.at(0);
            if (!cleanedLine.startsWith(QStringLiteral("--")) && !cleanedLine.startsWith(QStringLiteral("DROP")) && !cleanedLine.isEmpty()) {
                line += cleanedLine;
            }
            if (cleanedLine.endsWith(QStringLiteral(";"))) break;
            if (cleanedLine.startsWith(QStringLiteral("COMMIT"))) {
                hasText = true;
            }
        }
        if (!line.isEmpty()) {
            if (!query.exec(line)) {
                qDebug() << "exec failed" << line << query.lastQuery() << query.lastError();
            }

        }
        else {
            qDebug() << "exec wrong" << line << query.lastError();
        }
    }
    file.close();
}

bool JmBdeDB::check_existence(const QString &tableName, const QString &searchId, const QString &search)
{
    auto queryStr = QString(QLatin1String("SELECT %1 FROM %2 WHERE %3 = \"%4\"")).arg(searchId, tableName, searchId, search);

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

bool JmBdeDB::insert(const QString &tableName, const QVariantMap &insertData)
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
        strValues.append(QLatin1Literal("?"));
    }

    QString sqlQueryString = QLatin1String("INSERT INTO ") +
                             tableName +
                             QLatin1Literal(" (") +
                             QString(fields.join(QLatin1Literal(","))) +
                             QLatin1Literal(") VALUES(") +
                             QString(strValues.join(QLatin1Literal(","))) +
                             QLatin1Literal(")");
    QSqlQuery query(this->m_db);
    query.prepare(sqlQueryString);

    int k = 0;
    foreach (const QVariant &value, values)
        query.bindValue(k++, value);

    return query.exec();
}

bool JmBdeDB::update(const QString &table, const QString &column, const QVariant &newValue, const QVariant &op, const QString &id)
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

bool JmBdeDB::execQuery(QSqlQuery &query) const
{
    if (query.exec()) return true;
    qDebug() << "ERROR ON EXEC QUERY";
    qDebug() << query.lastError()  << query.lastQuery();
    return false;
}

bool JmBdeDB::execQuery(const QString &queryTxt)
{
    auto query = this->getQuery(queryTxt);
    return query.exec();
}


void JmBdeDB::openDB(const QString &name)
{
    if (!QSqlDatabase::contains(name)) {
        this->m_db = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"), name);
        this->m_db.setDatabaseName(Utils::JmBdeDBPath + Utils::DBName);
    }

    if (!this->m_db.isOpen()) {
        if (!this->m_db.open()) {
            qDebug() << "ERROR OPENING DB" << this->m_db.lastError().text() << m_db.connectionName();
        }
    }
}

QSqlQuery JmBdeDB::getQuery(const QString &queryTxt)
{
    QSqlQuery query(queryTxt, this->m_db);
    return query;
}
