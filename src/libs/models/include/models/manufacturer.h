/*
   jmbde a BDE Tool for companies
   Copyright (C) 2013-2020  Jürgen Mülbert

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

#include "jmbdemodels-version.h"
#include "jmbdemodels_export.h"
#include "loggingcategory.h"
#include "models/commondata.h"
#include "models/idatamodel.h"



namespace Model
{
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
class JMBDEMODELS_EXPORT Manufacturer : public CommonData
{
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
     * \fn virtual auto generateTableString(
                                const QString &header) -> QString
        \brief generateTableString

        Returns a QString with the generated Table for Output
     */
    virtual auto generateTableString(const QString &header) -> QString;

    /*!
         \fn virtual auto generateFormularString(
                                    const QString &header) -> QString
         \brief generateFormularString

         Returns a QString with the generated Table for Output
      */
    virtual auto generateFormularString(const QString &header) -> QString;

    // Getter

    /*!
        \fn int ManufacturerIdIndex()

        \brief Get the index of the fieldname ManufacturerId form the database

        Returns the value of the index
     */
    int ManufacturerIdIndex() const
    {
        return m_ManufacturerIdIndex;
    }

    /*!
        \fn int NameIndex()

        \brief Get the index of the fieldname Name form the database

        Returns the value of the index
     */
    int NameIndex() const
    {
        return m_NameIndex;
    }

    /*!
        \fn int Name2Index()

        \brief Get the index of the fieldname Name2 form the database

        Returns the value of the index
     */
    int Name2Index() const
    {
        return m_Name2Index;
    }

    /*!
        \fn int SupporterIndex()

        \brief Get the index of the fieldname Supporter form the database

        Returns the value of the index
     */
    int SupporterIndex() const
    {
        return m_SupporterIndex;
    }

    /*!
        \fn int AddressIndex()

        \brief Get the index of the fieldname Address form the database

        Returns the value of the index
     */
    int AddressIndex() const
    {
        return m_AddressIndex;
    }

    /*!
        \fn int Address2Index()

        \brief Get the index of the fieldname Address2 form the database

        Returns the value of the index
     */
    int Address2Index() const
    {
        return m_Address2Index;
    }

    /*!
        \fn int ZipCityIdIndex()

        \brief Get the index of the fieldname ZipCityId form the database

        Returns the value of the index
     */
    int ZipCityIdIndex() const
    {
        return m_ZipCityIdIndex;
    }

    /*!
        \fn int MailAddressIndex()

        \brief Get the index of the fieldname MailAddress form the database

        Returns the value of the index
     */
    int MailAddressIndex() const
    {
        return m_MailAddressIndex;
    }

    /*!
        \fn int PhoneNumberIndex()

        \brief Get the index of the fieldname PhoneNumber form the database

        Returns the value of the index
     */
    int PhoneNumberIndex() const
    {
        return m_PhoneNumberIndex;
    }

    /*!
        \fn int FaxNumberIndex()

        \brief Get the index of the fieldname FaxNumber form the database

        Returns the value of the index
     */
    int FaxNumberIndex() const
    {
        return m_FaxNumberIndex;
    }

    /*!
        \fn int HotlineNumberIndex()

        \brief Get the index of the fieldname HotlineNumber form the database

        Returns the value of the index
     */
    int HotlineNumberIndex() const
    {
        return m_HotlineNumberIndex;
    }

    /*!
        \fn  int LastUpdateIndex()

        \brief Get the index of the fieldname LastUpdate form the database

        Returns the value of the index
     */
    int LastUpdateIndex() const
    {
        return m_LastUpdateIndex;
    }

private:
    /*!
        \brief The Tablename in the database \e is const
     */
    const QString m_tableName = QLatin1String("manufacturer");

    /*!
       \var int m_ManufacturerIdIndex
       \brief The value of the ManufacturerIdIndex
    */
    int m_ManufacturerIdIndex {0};

    /*!
       \var int m_NameIndex
       \brief The value of the NameIndex
    */
    int m_NameIndex {0};

    /*!
       \var int m_Name2Index
       \brief The value of the Name2Index
    */
    int m_Name2Index {0};

    /*!
        \var int m_SupporterIndex
        \brief The value of the SupporterIndex
     */
    int m_SupporterIndex {0};

    /*!
        \var int m_AddressIndex
        \brief The value of the AddressIndex
     */
    int m_AddressIndex {0};

    /*!
        \var int m_Address2Index
        \brief The value of the Address2Index
     */
    int m_Address2Index {0};

    /*!
        \var int m_ZipCityIdIndex
        \brief The value of the ZipCityIdIndex
     */
    int m_ZipCityIdIndex {0};

    /*!
        \var int m_MailAddressIndex
        \brief The value of the MailAddressIndex
     */
    int m_MailAddressIndex {0};

    /*!
        \var int m_PhoneNumberIndex
        \brief The value of the PhoneNumberIndex
     */
    int m_PhoneNumberIndex {0};

    /*!
        \var int m_FaxNumberIndex
        \brief The value of the FaxNumberIndex
     */
    int m_FaxNumberIndex {0};

    /*!
        \var int m_HotlineNumberIndex
        \brief The value of the HotlineNumberIndex
     */
    int m_HotlineNumberIndex {0};

    /*!
        \var int m_LastUpdateIndex
        \brief The value of the LastUpdateIndex
    */
    int m_LastUpdateIndex {0};
};
} // namespace Model
