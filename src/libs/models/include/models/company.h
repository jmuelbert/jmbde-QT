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
    \class Company
    \brief The Companyl class
    \details In this is handlet all Companies in the Database
    \author Jürgen Mülbert
    \since 0.4
    \version 0.4.25
    \date 03.08.2019
    \copyright EUPL V1.2
    */

class JMBDEMODELS_EXPORT Company : public CommonData
{


public:
    /*!
        \fn Company(QObject *parent = nullptr)

        \brief Constructor for the Company
     */
    explicit Company(QObject *parent = nullptr);

    /*!
     * \fn   ~Company() override;
     *
     * \brief Destructor for Company()
     */
    ~Company();

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
    virtual auto generateTableString( const QString &header) -> QString;

    /*!
        \fn virtual auto generateFormularString(
                                   const QString &header) -> QString
        \brief generateFormularString

        Returns a QString with the generated Table for Output
     */
    virtual auto generateFormularString(const QString &header) -> QString;

    // Getter

    /*!
        \fn int CompanyIdIndex()

        \brief Get the index of the fieldname CompanyId form the database

        Returns the value of the index
     */
    int CompanyIdIndex() const
    {
        return m_CompanyIdIndex;
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
        \fn int StreetIndex()

        \brief Get the index of the fieldname Street form the database

        Returns the value of the index
     */
    int StreetIndex() const
    {
        return m_StreetIndex;
    }

    /*!
        \fn int CityIndex()

        \brief Get the index of the fieldname City form the database

        Returns the value of the index
    */
    int CityIndex() const
    {
        return m_CityIndex;
    }

    /*!
        \fn int ZipCodeIndex()

        \brief Get the index of the fieldname ZipCode form the database

        Returns the value of the index
    */
    int ZipCodeIndex() const
    {
        return m_ZipCodeIndex;
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
        \fn int FaxNumberIndex()

        \brief Get the index of the fieldname FaxNumber form the database

        Returns the value of the index
    */
    int MobileNumberIndex() const
    {
        return m_MobileNumberIndex;
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
        \fn int ActiveIndex()

        \brief Get the index of the fieldname Active form the database

        Returns the value of the index
    */
    int ActiveIndex() const
    {
        return m_ActiveIndex;
    }

    /*!
        \fn int EmployeeIdIndex()

         \brief Get the index of the fieldname EmployeeId form the database

         Returns the value of the index
    */
    int EmployeeIdIndex() const
    {
        return m_EmployeeIdIndex;
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
    const QString m_tableName = QLatin1String("company"); ///< QString m_tableName
    int m_CompanyIdIndex {0};                             ///< int CompanyIdIndex
    int m_NameIndex {0};                                  ///< int NameIndex
    int m_Name2Index {0};                                 ///< int Name2Index
    int m_StreetIndex {0};                                ///< int m_StreetIndex
    int m_CityIndex {0};                                  ///< int CityIndex
    int m_ZipCodeIndex {0};                               ///< int ZipCodeIndex
    int m_PhoneNumberIndex {0};                           ///< int PhoneNumberIndex
    int m_FaxNumberIndex {0};                             ///< int FaxNumberIndex
    int m_MobileNumberIndex {0};                          ///< int MobileNumberIndex
    int m_MailAddressIndex {0};                           ///< int MailAddressIndex
    int m_ActiveIndex {0};                                ///< int ActiveIndex
    int m_EmployeeIdIndex {0};                            ///< int EmployeeIdIndex
    int m_LastUpdateIndex {0};                            ///< int LastUpdateIndex
};
} // namespace Model
