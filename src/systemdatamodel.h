/*
 * systemdatamodel.h - SystemDataModel
 * jmbde
 *
 * Created by Jürgen Mülbert on 23.11.2013
 * Copyright (c) 2013, 2014 Jürgen Mülbert. All rights reserved.
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


#ifndef SYSTEMDATAMODEL_H
#define SYSTEMDATAMODEL_H

#if QT_VERSION >= 0x050000
#include <QtSql>
#include <QStandardPaths>
#endif

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>

#include "commondatamodel.h"

class SystemDataModel : public CommonDataModel
{
public:
    /**
     * @brief SystemDataModel
     * @param parent
     */
    SystemDataModel(QObject *parent = 0);

    /**
      * ~SystemDataModel
      */
    ~SystemDataModel();

    /**
     * @brief createDataTable
     * @return
     */
    bool createDataTable();

    /**
     * @brief initializeRelationalModel
     * @return
     */
    QSqlRelationalTableModel *initializeRelationalModel();

    /**
     * @brief initializeTableModel
     * @return
     */
    QSqlTableModel *initializeTableModel();


private:
    /**
     * @brief tableName
     */
    QString tableName = QLatin1String("system");
};

#endif // SYSTEMDATAMODEL_H
