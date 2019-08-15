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
    \class ComputerSoftware
    \brief The ComputerSoftware class
    \details In this is handle the installed software. Is a many to many
   relation. \author Jürgen Mülbert \since 0.4 \version 0.4.25 \date 03.08.2019
    \copyright EUPL V1.2
    */

namespace Model {

class JMBDE_COMMON_EXPORT ComputerSoftware : public CommonData {
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
    Q_LOGGING_CATEGORY(computerSoftwareLC, "jmbde.models.computersoftware")

public:
    /*!
        \fn ComputerSoftware(QObject *parent = nullptr)

        \brief Constructor for the ComputerSoftware
     */
    explicit ComputerSoftware(QObject *parent = nullptr);

    /*!
        \fn  ~ComputerSoftware() override;

        \brief Destructor for  ComputerSoftware
     */
    virtual ~ComputerSoftware() = default;

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
                                        QString header);

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
        \fn int ComputerSoftwareIdIndex()

         \brief Get the index of the fieldname ComputerSoftwareId from the
       database

         Returns the value of the index
     */
    int ComputerSoftwareIdIndex() const { return m_ComputerSoftwareIdIndex; }

    /*!
        \fn int ComputerIdIndex()

        \brief Get the index of the fieldname ComputerId form the database

        Returns the value of the index
     */
    int ComputerIdIndex() const { return m_ComputerIdIndex; }

    /*!
        \fn int SoftwareIdIndex()

        \brief Get the index of the fieldname SoftwareId form the database

        Returns the value of the index
     */
    int SoftwareIdIndex() const { return m_SoftwareIdIndex; }

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
    const QString m_tableName = QLatin1String("computer_software");

    /*!
        \var int m_ComputerSoftwareIdIndex
        \brief The value of the ComputerSoftwareIdIndex
    */
    int m_ComputerSoftwareIdIndex;

    /*!
        \var int m_ComputerIdIndex
        \brief The value of the ComputerIdIndex
    */
    int m_ComputerIdIndex;

    /*!
        \var int m_SoftwareIdIndex
        \brief The value of the SoftwareIdIndex
    */
    int m_SoftwareIdIndex;

    /*!
        \var int m_LastUpdateIndex
        \brief The value of the LastUpdateIndex
    */
    int m_LastUpdateIndex;
};
} // namespace Model
