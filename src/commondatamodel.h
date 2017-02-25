/*
 * CommonDataModel.h
 * jmbde
 *
 * Copyright (c) 2013,2014 Jürgen Mülbert. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the European Union Public Licence (EUPL),
 * version 1.1.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * European Union Public Licence for more details.
 *
 * You should have received a copy of the European Union Public Licence
 * along with this program. If not, see
 * http://www.osor.eu/eupl/european-union-public-licence-eupl-v.1.1
 *
 */

#ifndef COMMONDATAMODEL_H
#define COMMONDATAMODEL_H

#include <QObject>

#if QT_VERSION >= 0x050000
#include <QtSql>
#include <QStandardPaths>
#endif

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>


#include "datamodell.h"

/**
 * @brief The CommonDataModel class
 * @details This Class is the root for many common classes
 * @author Jürgen Mülbert
 * @version 0.2
 * @date 09.02.2014
 * @copyright EUPL V1.1
 */
class CommonDataModel : public DataModell
{
public:
    /**
     * @brief CommonDataModel
     * @param parent
     */
    CommonDataModel(QObject *parent = 0);

    /**
      * @brief ~CommonDataModel
      */
    ~CommonDataModel();

    /**
     * @brief createDataTable
     * @param tableName
     * @deprecated You should not longer use this. The Database will create with a script
     * @return boolean true or false, created ?
     */
    bool createDataTable(QString tableName);

    /**
     * @brief initializeRelationalModel
     * @param tableName
     * @return RelationalTableModel
     */
    QSqlRelationalTableModel *initializeRelationalModel(const QString tableName);

    /**
     * @brief initializeTableModel
     * @param tableName
     * @return TableModel
     */
    QSqlTableModel *initializeTableModel(QString tableName);

private:
    /**
     * @brief The PosIFunctionTable enum
     */
    enum PosCommonTable {
        POS_COMMON_ID,
        POS_COMMON_NAME,
        POS_COMMON_CREATIONTIME,
        POS_COMMON_UPDATETIME
    };
};

#endif // COMMONDATAMODEL_H
