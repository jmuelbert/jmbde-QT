/*
 * PrinterDataModel.h
 * jmbde
 *
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

#ifndef PRINTERDATAMODEL_H
#define PRINTERDATAMODEL_H


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

class PrinterDataModel : public DataModell
{
public:
    /**
     * @brief PrinterDataModel
     * @param parent
     */
    PrinterDataModel(QObject *parent = 0);

    ~PrinterDataModel();

    /**
     * @brief createDataTable
     * @return
     */
    bool createDataTable();

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
    enum PosPrintTable {
        POS_PRINTER_ID,
        POS_PRINTER_DEVICENAME_ID,
        POS_PRINTER_SERIALNUMBER,
        POS_PRINTER_NETWORK,
        POS_PRINTER_NETWORK_NAME,
        POS_PRINTER_NETWORK_IPADDRESS,
        POS_PRINTER_ACTIVE,
        POS_PRINTER_REPLACE,
        POS_PRINTER_RESOURCES,
        POS_PRINTER_PAPERSIZE_MAX,
        POS_PRINTER_DEVICETYPE_ID,
        POS_PRINTER_EMPLOYEE_ID,
        POS_PRINTER_PLACE_ID,
        POS_PRINTER_DEPARTMENT_ID,
        POS_PRINTER_MANUFACTURER_ID,
        POS_PRINTER_INVENTORY_ID,
        POS_PRINTER_COMPUTER_ID,
        POS_PRINTER_LAST_UPDATE
    };
};

#endif // PRINTERDATAMODEL_H
