/*
 * ComputerDataModel.h
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

#ifndef COMPUTERDATAMODEL_H
#define COMPUTERDATAMODEL_H

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

/**
 * @brief The ComputerDataModel class
 */
class ComputerDataModel : public DataModell
{
public:
    /**
     * @brief ComputerDataModel
     * @param parent
     */
    ComputerDataModel(QObject *parent = 0);

    ~ComputerDataModel();


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
     * @brief The PosCompTable enum
     */
    enum PosCompTable {
        POS_COMPUTER_ID,
        POS_COMPUTER_DEVICENAME_ID,
        POS_COMPUTER_SERIALNUMBER,
        POS_COMPUTER_SERVICE_TAG,
        POS_COMPUTER_SERVICE_NUMBER,
        POS_COMPUTER_MEMORY,
        POS_COMPUTER_NETWORK,
        POS_COMPUTER_NETWORK_NAME,
        POS_COMPUTER_NETWORK_IPADDRESS,
        POS_COMPUTER_ACTIVE,
        POS_COMPUTER_REPLACE,
        POS_COMPUTER_DEVICETYPE_ID,
        POS_COMPUTER_EMPLOYEE_ID,
        POS_COMPUTER_PLACE_ID,
        POS_COMPUTER_DEPARTMENT_ID,
        POS_COMPUTER_MANUFACTURER_ID,
        POS_COMPUTER_INVENTORY_ID,
        POS_COMPUTER_PROCESSOR_ID,
        POS_COMPUTER_OS_ID,
        POS_COMPUTER_COMPUTERSOFTWARE_ID,
        POS_COMPUTER_PRINTER_ID,
        POS_COMPUTER_LAST_UPDATE
    };
};

#endif // COMPUTERDATAMODEL_H
