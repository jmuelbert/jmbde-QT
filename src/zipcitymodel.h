/*
// zipcity zipcity.h
// part of <Project>
//
// Copyright (c) 2013-2017 Jürgen Mülbert. All rights reserved.
//
// Licensed under the EUPL, Version 1.2 or – as soon they
// will be approved by the European Commission - subsequent
// versions of the EUPL (the "Licence");
// You may not use this work except in compliance with the
// Licence.
// You may obtain a copy of the Licence at:
//
// https://joinup.ec.europa.eu/page/eupl-text-11-12
//
// Unless required by applicable law or agreed to in
// writing, software distributed under the Licence is
// distributed on an "AS IS" basis,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
// express or implied.
// See the Licence for the specific language governing
// permissions and limitations under the Licence.
//
// Lizenziert unter der EUPL, Version 1.2 oder - sobald
// diese von der Europäischen Kommission genehmigt wurden -
// Folgeversionen der EUPL ("Lizenz");
// Sie dürfen dieses Werk ausschließlich gemäß
// dieser Lizenz nutzen.
// Eine Kopie der Lizenz finden Sie hier:
//
// https://joinup.ec.europa.eu/page/eupl-text-11-12
//
// Sofern nicht durch anwendbare Rechtsvorschriften
// gefordert oder in schriftlicher Form vereinbart, wird
// die unter der Lizenz verbreitete Software "so wie sie
// ist", OHNE JEGLICHE GEWÄHRLEISTUNG ODER BEDINGUNGEN -
// ausdrücklich oder stillschweigend - verbreitet.
// Die sprachspezifischen Genehmigungen und Beschränkungen
// unter der Lizenz sind dem Lizenztext zu entnehmen.
//
// Created: 30.10.2017
*/
#ifndef ZIPCITY_H
#define ZIPCITY_H

#include <QObject>
#include <QtSql>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>

#include "definitions.h"
#include "datamodel.h"

class ZipCityModel : public DataModel
{
public:
    ZipCityModel(QObject* parent = 0);

    virtual ~ZipCityModel();

    /**
     * @brief initializeRelationalModel
     * @return
     */
    QSqlRelationalTableModel* initializeRelationalModel();

    /**
     * @brief initializeTableModel
     * @return
     */
    QSqlTableModel* initializeTableModel();

    enum PosZipcityTable {
        POS_ZIPCITY_ID,
        POS_ZIPCITY_ZIPCODE_ID,
        POS_ZIPCITY_CITY_ID,
        POS_ZIPCITY_LASTUPDATE

    };

private:
    /**
     * @brief tableName - the name of the database table
     * @
     */
    const QString tableName = QLatin1String(Database::Table::ZIPCITY);


};

#endif // ZIPCITY_H
