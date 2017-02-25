/*
 * PhoneDataModel
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


#include "phonedatamodel.h"

PhoneDataModel::PhoneDataModel(QObject *parent) : DataModell(parent)
{
}

PhoneDataModel::~PhoneDataModel() {

}

void PhoneDataModel::addDataSet() {
    QSqlQuery query;

    QString sqlString = QLatin1String("insert into phone(pcnr, name) values( ");

    sqlString.append(QLatin1String("'"));
    sqlString.append(pcnr);
    sqlString.append(QLatin1String("' , '"));
    sqlString.append(name);
    sqlString.append(QLatin1String("');"));
    bool ret = query.exec(sqlString);
    if (ret == false) {
        qDebug() << sqlString.toLatin1();
        qDebug() << db.lastError();
    } else {
        db.commit();
    }
}

QSqlRelationalTableModel *PhoneDataModel::initializeRelationalModel() {
    //TODO: id als locale Konstante

    QSqlRelationalTableModel *model = new QSqlRelationalTableModel(this);
    model->setTable(QLatin1String("phone"));
    model->setEditStrategy(QSqlTableModel::OnFieldChange);


    model->setRelation(POS_PHONE_EMPLOYEEID, QSqlRelation(QLatin1String("Employee"),
                                                  QLatin1String("Id"),
                                                  QLatin1String("Name")));


    model->setHeaderData(POS_PHONE_ID, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(POS_PHONE_NUMBER, Qt::Horizontal, QObject::tr("Number"));
    model->setHeaderData(POS_PHONE_ACTIVE, Qt::Horizontal, QObject::tr("Active"));
    model->setHeaderData(POS_PHONE_EMPLOYEEID, Qt::Horizontal, QObject::tr("Employee"));
    model->setHeaderData(POS_PHONE_LASTUPDATE, Qt::Horizontal, QObject::tr("Last Update"));

    model->select();

    return model;
}

QSqlTableModel *PhoneDataModel::initializeTableModel() {
    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable(QLatin1String("phone"));
    model->setEditStrategy(QSqlTableModel::OnFieldChange);

    model->setHeaderData(POS_PHONE_ID, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(POS_PHONE_NUMBER, Qt::Horizontal, QObject::tr("Number"));
    model->setHeaderData(POS_PHONE_ACTIVE, Qt::Horizontal, QObject::tr("Active"));
    model->setHeaderData(POS_PHONE_EMPLOYEEID, Qt::Horizontal, QObject::tr("Employee"));
    model->setHeaderData(POS_PHONE_LASTUPDATE, Qt::Horizontal, QObject::tr("Last Update"));

    model->select();

    return model;

}


QString PhoneDataModel::generateTableString(QAbstractTableModel *model, QString header) {
    QString outString;
    int columnCount = model->columnCount();
    int rowCount = model->rowCount();
    qDebug() << "Header : " << header << " Columns : " << columnCount << " Rows : " << rowCount;

    QList<int> set;
    set.append(POS_PHONE_NUMBER);
    set.append(POS_PHONE_EMPLOYEEID);

    // Document Title
    outString = QLatin1String("<h1>");
    outString += header;
    outString += QLatin1String("</h1>");
    outString += QLatin1String("<hr />");
    outString += QLatin1String("<table width=\"100%\" cellspacing=\"0\" class=\"tbl\">");
    outString += QLatin1String("<thead> <tr>");


    foreach (const int i, set) {
        qDebug() << "int i = " << i;
        outString += QLatin1String("<th>");
        outString.append(model->headerData(i, Qt::Horizontal).toString());
        outString += QLatin1String("</th>");
    }
    outString += QLatin1String("</tr> </thead>");


    for (int i=0; i<rowCount; i++) {
        outString += QLatin1String("<tr>");
        foreach (const int j, set) {
            outString += QLatin1String("<td>");
            QModelIndex ind(model->index(i, j));
            outString.append(ind.data(Qt::DisplayRole).toString());
            outString += QLatin1String("</td>");
        }
        outString += QLatin1String("</tr>");
    }

    // Close Table
    outString += QLatin1String("</table>");
    return outString;

}


