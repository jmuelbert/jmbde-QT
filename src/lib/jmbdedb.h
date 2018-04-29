#ifndef JMBDEDB_H
#define JMBDEDB_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QList>
#include <QSqlDatabase>
#include <typeinfo>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlDriver>
#include <QFileInfo>
#include <QDir>
#include <QVariantMap>

#include "data_global.h"

class DATASHARED_EXPORT JmBdeDB : public QObject
{
    Q_OBJECT
public:
    explicit JmBdeDB(QObject* parent = nullptr);
    explicit JmBdeDB(const QString &name = QString(), QObject* parent = nullptr);
    ~JmBdeDB() override;

    bool execQuery(QSqlQuery &query) const;
    bool execQuery(const QString &queryText);

    /* basic public actions */
    void prepareJmBdeDB() const;
    bool check_existence(const QString &tableName, const QString &searchId, const QString &search);

    /* useful actions */
    QSqlQuery getQuery(const QString &queryTxt);
    void openDB(const QString &name);

private:
    QString name;
    QSqlDatabase m_db;

    /* basic actions */
    bool insert(const QString &tableName, const QVariantMap &insertData);
    bool update(const QString &table, const QString &column, const QVariant &newValue, const QVariant &op, const QString &id);
    bool remove();

signals:
    void DBactionFinished();

public slots:
    void closeConnection();

};

#endif // JMBDEDB_H
