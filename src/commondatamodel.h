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
#include <QSql>
#include <QStandardPaths>
#endif

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>


#include "datamodell.h"

class CommonDataModel : public DataModell
{
public:
    CommonDataModel(QObject *parent = 0);
    ~CommonDataModel();

    /**
     * @brief createDataTable
     * @return
     */
    bool createDataTable(QString tableName);

    /**
     * @brief initializeRelationalModel
     * @return
     */
    QSqlRelationalTableModel *initializeRelationalModel(const QString tableName);

    /**
     * @brief initializeTableModel
     * @return
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
