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
    \copyright EUPL V1.2
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
        Returns The QSqlRelationalTableModel
     */
    virtual QSqlRelationalTableModel *initializeRelationalModel();

    /*!
        \fn virtual QSqlRelationalTableModel *initializeInputDataModel()
        \brief Initialize the InputDataModel

        Returns The QSqlRelationalTableModel
     */
    virtual QSqlRelationalTableModel *initializeInputDataModel();

    /*!
        \fn virtual QSqlTableModel *initializeViewModel()
        \brief Initialize the ViewModel

        Returns QSqlTableModel
     */
    virtual QSqlTableModel *initializeViewModel();

    /*!
     * \fn virtual QString generateTableString(QAbstractTableModel *model,
                                const QString &header)
        \brief generateTableString

        Returns a QString with the generated Table for Output
     */
    virtual QString generateTableString(QAbstractTableModel *model,
                                        const QString header);

    /*!
        \fn virtual QString generateFormularString(QAbstractTableModel *model,
                                   const QString &header)
        \brief generateFormularString

        Returns a QString with the generated Table for Output
     */
    virtual QString generateFormularString(QAbstractTableModel *model,
                                           QString header);

    // Getter
    /*!
        \fn int ChipCardIdIndex()

        \brief Get the index of the fieldname ChipCardId from the database

        Returns the value of the index
     */
    int ChipCardIdIndex() const { return m_ChipCardIdIndex; }

    /*!
        \fn int NumberIndex()

        \brief Get the index of the fieldname Number from the database

        Returns the value of the index
     */
    int NumberIndex() const { return m_NumberIndex; }

    /*!
        \fn  int ChipCardDoorIdIndex()

        \brief Get the index of the fieldname ChipCardDoorId from the database

        Returns the value of the index
     */
    int ChipCardDoorIdIndex() const { return m_ChipCardDoorIdIndex; }

    /*!
        \fn  int ChipCardProfileIdIndex()

        \brief Get the index of the fieldname ChipCardProfileId from the
       database

        Returns the value of the index
     */
    int ChipCardProfileIdIndex() const { return m_ChipCardProfileIdIndex; }

    /*!
        \fn  int EmployeeIdIndex()

        \brief Get the index of the fieldname EmployeeId from the database

        Returns the value of the index
     */
    int EmployeeIdIndex() const { return m_EmployeeIdIndex; }

    /*!
        \fn  int LastUpdateIndex()

        \brief Get the index of the fieldname LastUpdate form the database

        Returns the value of the index
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
    int m_ChipCardIdIndex {0};

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
