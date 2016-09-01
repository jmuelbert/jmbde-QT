/*
 * PhoneDataModel.h
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


#ifndef PHONEDATAMODEL_H
#define PHONEDATAMODEL_H



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


class PhoneDataModel : public DataModell
{
public:
    /**
     * @brief PhoneDataModel
     * @param parent
     */
    PhoneDataModel(QObject *parent = 0);

    /**
     * @brief PhoneDataModel::~PhoneDataModel
     */
      ~PhoneDataModel();


    /**
     * @brief addDataSet
     */
    void addDataSet();


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

    /**
     * @brief generateTableString
     * @param model
     * @param header
     * @return
     */
    QString generateTableString(QAbstractTableModel *model, QString header);

private:
    /**
     * @brief pcnr
     */
    QString *pcnr;

    /**
     * @brief name
     */
    QString *name;

    /**
     * @brief The PosPhoneTable enum
     */
    enum PosPhoneTable {
        POS_PHONE_ID,
        POS_PHONE_NUMBER,
        POS_PHONE_ACTIVE,
        POS_PHONE_EMPLOYEEID,
        POS_PHONE_LASTUPDATE
    };
};


#endif // PHONEDATAMODEL_H
