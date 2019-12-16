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
    \class Manufacturer
    \brief The Manufacturer class
    \details In this is handle all Manufacturer
    \author Jürgen Mülbert
    \since 0.4
    \version 0.4.25
    \date 03.08.2019
    \copyright EUPL V1.2
    */

namespace Model {
class JMBDE_COMMON_EXPORT Manufacturer : public CommonData {
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
    Q_LOGGING_CATEGORY(manufacturerLC, "jmbde.models.manufacturer")

public:
    /*!
        \fn explicit Manufacturer(QObject *parent = nullptr)
        \brief The Constructor for the Manufacturer
    */
    explicit Manufacturer(QObject *parent = nullptr);

    /*!
        \fn  ~Manufacturer();

        \brief Destructor for Manufacturer
     */
    ~Manufacturer();

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
        \fn int ManufacturerIdIndex()

        \brief Get the index of the fieldname ManufacturerId form the database

        Returns the value of the index
     */
    int ManufacturerIdIndex() const { return m_ManufacturerIdIndex; }

    /*!
        \fn int NameIndex()

        \brief Get the index of the fieldname Name form the database

        Returns the value of the index
     */
    int NameIndex() const { return m_NameIndex; }

    /*!
        \fn int Name2Index()

        \brief Get the index of the fieldname Name2 form the database

        Returns the value of the index
     */
    int Name2Index() const { return m_Name2Index; }

    /*!
        \fn int SupporterIndex()

        \brief Get the index of the fieldname Supporter form the database

        Returns the value of the index
     */
    int SupporterIndex() const { return m_SupporterIndex; }

    /*!
        \fn int AddressIndex()

        \brief Get the index of the fieldname Address form the database

        Returns the value of the index
     */
    int AddressIndex() const { return m_AddressIndex; }

    /*!
        \fn int Address2Index()

        \brief Get the index of the fieldname Address2 form the database

        Returns the value of the index
     */
    int Address2Index() const { return m_Address2Index; }

    /*!
        \fn int ZipCityIdIndex()

        \brief Get the index of the fieldname ZipCityId form the database

        Returns the value of the index
     */
    int ZipCityIdIndex() const { return m_ZipCityIdIndex; }

    /*!
        \fn int MailAddressIndex()

        \brief Get the index of the fieldname MailAddress form the database

        Returns the value of the index
     */
    int MailAddressIndex() const { return m_MailAddressIndex; }

    /*!
        \fn int PhoneNumberIndex()

        \brief Get the index of the fieldname PhoneNumber form the database

        Returns the value of the index
     */
    int PhoneNumberIndex() const { return m_PhoneNumberIndex; }

    /*!
        \fn int FaxNumberIndex()

        \brief Get the index of the fieldname FaxNumber form the database

        Returns the value of the index
     */
    int FaxNumberIndex() const { return m_FaxNumberIndex; }

    /*!
        \fn int HotlineNumberIndex()

        \brief Get the index of the fieldname HotlineNumber form the database

        Returns the value of the index
     */
    int HotlineNumberIndex() const { return m_HotlineNumberIndex; }

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
    const QString m_tableName = QLatin1String("manufacturer");

    /*!
       \var int m_ManufacturerIdIndex
       \brief The value of the ManufacturerIdIndex
    */
    int m_ManufacturerIdIndex{0};

    /*!
       \var int m_NameIndex
       \brief The value of the NameIndex
    */
    int m_NameIndex{0};

    /*!
       \var int m_Name2Index
       \brief The value of the Name2Index
    */
    int m_Name2Index{0};

    /*!
        \var int m_SupporterIndex
        \brief The value of the SupporterIndex
     */
    int m_SupporterIndex{0};

    /*!
        \var int m_AddressIndex
        \brief The value of the AddressIndex
     */
    int m_AddressIndex{0};

    /*!
        \var int m_Address2Index
        \brief The value of the Address2Index
     */
    int m_Address2Index{0};

    /*!
        \var int m_ZipCityIdIndex
        \brief The value of the ZipCityIdIndex
     */
    int m_ZipCityIdIndex{0};

    /*!
        \var int m_MailAddressIndex
        \brief The value of the MailAddressIndex
     */
    int m_MailAddressIndex{0};

    /*!
        \var int m_PhoneNumberIndex
        \brief The value of the PhoneNumberIndex
     */
    int m_PhoneNumberIndex{0};

    /*!
        \var int m_FaxNumberIndex
        \brief The value of the FaxNumberIndex
     */
    int m_FaxNumberIndex{0};

    /*!
        \var int m_HotlineNumberIndex
        \brief The value of the HotlineNumberIndex
     */
    int m_HotlineNumberIndex{0};

    /*!
        \var int m_LastUpdateIndex
        \brief The value of the LastUpdateIndex
    */
    int m_LastUpdateIndex{0};
};
} // namespace Model
