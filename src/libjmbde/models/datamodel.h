#ifndef _SRC_APP_MODELS_DATAMODEL_H
#define _SRC_APP_MODELS_DATAMODEL_H

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

#include <QObject>

#include <QDebug>

#include <QList>
#include <QString>
#include <QStringList>

#include <QDir>
#include <QFileInfo>
#include <QVariantMap>

#include <QDate>

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

#include <QSettings>

#include <QStandardPaths>

#include "definitions.h"

/**
 * \brief The Main Database class
 * \details Here will handle all db actions...
 * \author Jürgen Mülbert
 * \version 0.4
 * \date 14.12.2017
 * \copyright EUPL V1.2
 *
 * \todo Remove UI fpr Testing
 * \todo Move Code for every Table in his own class
 *
 * \page DataModel Page
 *
 *
 * This is the introduction.
 *
 */

/**
 * @brief The DataModel class
 */
class DataModel : public QObject {
    Q_OBJECT

public:
    /**
     * @brief DataModel
     * @param parent
     */
    explicit DataModel(QObject *parent = nullptr);

    explicit DataModel(const QString &name = QString(),
                       QObject *parent = nullptr);

    /**
     * @brief ~DataModel
     */
    ~DataModel() override;

    /**
     * @brief DataModel::CreateConnection
     * @return
     *
     * \todo init all tables
     * \todo check database version
     * \todo export and import all tables
     */
    bool CreateConnection();

    /**
     * @brief getDatabase
     * @return
     */
    QSqlDatabase getDatabase();

    /**
     * @brief initDb
     *
     * If the Database new then create the tables
     */
    QSqlError initDb();

    bool execQuery(QSqlQuery &query) const;
    bool execQuery(const QString &queryText);

    /* basic public actions */
    void prepareDB() const;
    bool check_existence(const QString &tableNmae, const QString &searchId,
                         const QString &serach);

    /* useful actions */
    QSqlQuery getQuery(const QString &queryText);
    void openDB(const QString &name);

private:
    QString name;

    /**
     * @brief db
     */
    QSqlDatabase m_db;

    /**
     * @brief checkDBVersion
     * @return
     */
    bool checkDBVersion();

    /* basic actions */
    bool insert(const QString &tableName, const QVariantMap &insertData);
    bool update(const QString &table, const QString &column,
                const QVariant &newValue, const QVariant &op,
                const QString &id);
    bool remove();

signals:
    void DBActionFinished();

public slots:
    void closeConnection();
};

#endif // _SRC_APP_MODELS_DATAMODEL_H
