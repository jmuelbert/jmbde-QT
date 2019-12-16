 /*
    jmbde a BDE Tool for companies
    Copyright (C) 2013-2019  Jürgen Mülbert

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

#pragma once

#include <QObject>
#include <QtSql>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>

#include "definitions.h"
#include "jmbde_common_export.h"
#include "models/commondata.h"
#include "models/idatamodel.h"

/*!
    \class ChipCard
    \brief The ChipDataModel class
    \details in this class is handled the coins for the room access system.
    \author Jürgen Mülbert
    \since 0.4
    \version 0.4
    \date 23.11.2018
    \copyright GPL V3
 */

namespace Model {

class JMBDE_COMMON_EXPORT ChipCard : public CommonData {
    /*!
        \macro Q_OBJECT
        \relates QObject

        The Q_OBJECT macro must appear in the private section
        of a class definition that declares its own signals and
        slots, or that uses other services provided by Qt's
        meta-object system.

        ...

        \sa {Meta-Object System}, {Signals and Slots}, {QtsProperty System}
    */
    Q_OBJECT
    /*!
         \macro Q_LOGGING_CATEGORY
         \relates QLogging

         Defines the Logging Categorie for the class
      */
    Q_LOGGING_CATEGORY(chipCardLC, "jmbde.models.chipcarddata")

public:
    /*!
        \fn ChipCard(QObject *parent = nullptr)

        \brief Contructor forChipCard
    */
    explicit ChipCard(QObject *parent = nullptr);

    /*!
        \fn ~ChipCard() override

        \brief Destructor for the ChipCard
     */
    ~ChipCard();

    // implement the virtuals

    /*!
        \fn virtual void setIndexes()
        \brief Set the fieldindexes from the datafieldnames of the db.
     */
    virtual void setIndexes();

    /*!
        \fn virtual QSqlRelationalTableModel *initializeRelationalModel()
        \brief set the QSqlRelationalTableModel for the DataModel
        \return The QSqlRelationalTableModel
     */
    virtual QSqlRelationalTableModel *initializeRelationalModel();

    /*!
        \fn virtual QSqlRelationalTableModel *initializeInputDataModel()
        \brief Initialize the InputDataModel

        \return The QSqlRelationalTableModel
     */
    virtual QSqlRelationalTableModel *initializeInputDataModel();

    /*!
        \fn virtual QSqlTableModel *initializeViewModel()
        \brief Initialize the ViewModel

        \return QSqlTableModel
     */
    virtual QSqlTableModel *initializeViewModel();

    /*!
     * \fn virtual QString generateTableString(QAbstractTableModel *model,
                                const QString &header)
        \brief generateTableString

        \return a QString with the generated Table for Output
     */
    virtual QString generateTableString(QAbstractTableModel *model,
                                        const QString header);

    /*!
        \fn virtual QString generateFormularString(QAbstractTableModel *model,
                                   const QString &header)
        \brief generateFormularString

        \return a QString with the generated Table for Output
     */
    virtual QString generateFormularString(QAbstractTableModel *model,
                                           QString header);

    // Getter
    /*!
        \fn int ChipCardIdIndex()

        \brief Get the index of the fieldname ChipCardId from the database

        \return the value of the index
     */
    int ChipCardIdIndex() const { return m_ChipCardIdIndex; }

    /*!
        \fn int NumberIndex()

        \brief Get the index of the fieldname Number from the database

        \return the value of the index
     */
    int NumberIndex() const { return m_NumberIndex; }

    /*!
        \fn  int ChipCardDoorIdIndex()

        \brief Get the index of the fieldname ChipCardDoorId from the database

        \return the value of the index
     */
    int ChipCardDoorIdIndex() const { return m_ChipCardDoorIdIndex; }

    /*!
        \fn  int ChipCardProfileIdIndex()

        \brief Get the index of the fieldname ChipCardProfileId from the
       database

        \return the value of the index
     */
    int ChipCardProfileIdIndex() const { return m_ChipCardProfileIdIndex; }

    /*!
        \fn  int EmployeeIdIndex()

        \brief Get the index of the fieldname EmployeeId from the database

        \return the value of the index
     */
    int EmployeeIdIndex() const { return m_EmployeeIdIndex; }

    /*!
        \fn  int LastUpdateIndex()

        \brief Get the index of the fieldname LastUpdate form the database

        \return the value of the index
     */
    int LastUpdateIndex() const { return m_LastUpdateIndex; }

private:
    /*!
        \brief The Tablename in the database \e is const
     */
    const QString m_tableName = QLatin1String("chip_card");

    /*!
        \brief The value of the ChipCardIdIndex
     */
    int m_ChipCardIdIndex{0};

    /*!
        \brief The value of the NumberIndex
     */
    int m_NumberIndex{0};

    /*!
        \brief The value of the ChipCardDoorIdIndex
     */
    int m_ChipCardDoorIdIndex{0};

    /*!
        \brief The value of the hipCardProfileIdIndex
     */
    int m_ChipCardProfileIdIndex{0};

    /*!
        \brief The value of the EmployeeIdIndex
     */
    int m_EmployeeIdIndex{0};

    /*!
          \brief The value of the LastUpdateIndex
      */
    int m_LastUpdateIndex{0};
};

} // namespace Model
