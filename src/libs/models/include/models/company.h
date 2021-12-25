/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include <QLoggingCategory>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>
#include <QTextDocument>
#include <QtSql>

#include "commondata.h"
#include "datacontext.h"
#include "jmbdemodels-version.h"
#include "jmbdemodels_export.h"

namespace Model {
/*!
    \class Company
    \brief The Companyl class
    \details In this is handlet all Companies in the Database
    \author Jürgen Mülbert
    \since 0.4
    \version 0.7
    \date 25.12.2021
    \copyright GPL-3.0-or-later
    */

class Company : public CommonData {
    Q_OBJECT

public:
    /*!
        \fn Company()

        \brief Constructor for the Company
     */
    explicit JMBDEMODELS_EXPORT Company();

    /*!
     * \fn   ~Company() override;
     *
     * \brief Destructor for Company()
     */
    JMBDEMODELS_EXPORT ~Company()
    {
    }

    // implement the virtuals

    /*!
        \fn virtual void setIndexes()
        \brief Set the fieldindexes from the datafieldnames of the db.
     */
    virtual JMBDEMODELS_EXPORT void setIndexes() final;

    /*!
        \fn virtual JMBDEMODELS_EXPORT auto initializeRelationalModel() -> QSqlRelationalTableModel* final
        \brief set the QSqlRelationalTableModel for the DataModel
        \return The QSqlRelationalTableModel
     */
    virtual JMBDEMODELS_EXPORT auto initializeRelationalModel() -> QSqlRelationalTableModel* final;

    /*!
        \fn virtual auto initializeInputDataModel() -> QSqlRelationalTableModel* fina
        \brief Initialize the InputDataModel

         \return The QSqlRelationalTableModel
     */
    virtual JMBDEMODELS_EXPORT auto initializeInputDataModel() -> QSqlRelationalTableModel* final;

    /*!
        \fn virtual auto initializeViewModel() -> QSqlTableModel* final
        \brief Initialize the ViewModel

        \return QSqlTableModel
     */
    virtual JMBDEMODELS_EXPORT auto initializeViewModel() -> QSqlTableModel* final;

    /*!
        \fn virtual auto initializeListModel() -> QSqlTableModel* final
        \brief Initiallize the list Model for select one dataset
    */
    virtual JMBDEMODELS_EXPORT auto initializeListModel() -> QSqlTableModel* final;

    /*!
     * \fn virtual auto generateTableString(const QString& header) -> QString final
        \brief generateTableString

        \return a QString with the generated Table for Output
     */
    virtual JMBDEMODELS_EXPORT auto generateTableString(const QString& header) -> QString final;

    /*!
        \fn virtual auto generateFormularString(const QString& header) -> QString final
        \brief generateFormularString

        \return a QString with the generated Table for Output
     */
    virtual JMBDEMODELS_EXPORT auto generateFormularString(const QString& header) -> QString final;

    // Getter
    /*!
     * \brief getTableName
     * \return
     */
    JMBDEMODELS_EXPORT auto getTableName() const -> QString
    {
        return this->m_tableName;
    }
    /*!
        \fn auot getDB() const -> QSqlDatabase
     */
    JMBDEMODELS_EXPORT auto getDB() const -> QSqlDatabase
    {
        return this->m_db;
    }

    /*!
        \fn int getCompanyIdIndex()

        \brief Get the index of the fieldname CompanyId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getCompanyIdIndex() const
    {
        return m_CompanyIdIndex;
    }

    /*!
        \fn int getNameIndex()

        \brief Get the index of the fieldname Name form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getNameIndex() const
    {
        return m_NameIndex;
    }

    /*!
        \fn int getName2Index()

        \brief Get the index of the fieldname Name2 form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getName2Index() const
    {
        return m_Name2Index;
    }

    /*!
        \fn int getStreetIndex()

        \brief Get the index of the fieldname Street form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getStreetIndex() const
    {
        return m_StreetIndex;
    }

    /*!
        \fn int getCityIndex()

        \brief Get the index of the fieldname City form the database

        Returns the value of the index
    */
    JMBDEMODELS_EXPORT int getCityIndex() const
    {
        return m_CityIndex;
    }

    /*!
        \fn int getZipCodeIndex()

        \brief Get the index of the fieldname ZipCode form the database

        Returns the value of the index
    */
    JMBDEMODELS_EXPORT int getZipCodeIndex() const
    {
        return m_ZipCodeIndex;
    }

    /*!
        \fn int getPhoneNumberIndex()

        \brief Get the index of the fieldname PhoneNumber form the database

        Returns the value of the index
    */
    JMBDEMODELS_EXPORT int getPhoneNumberIndex() const
    {
        return m_PhoneNumberIndex;
    }

    /*!
        \fn int getFaxNumberIndex()

        \brief Get the index of the fieldname FaxNumber form the database

        Returns the value of the index
    */
    JMBDEMODELS_EXPORT int getFaxNumberIndex() const
    {
        return m_FaxNumberIndex;
    }

    /*!
        \fn int getMobileNumberIndex()

        \brief Get the index of the fieldname FaxNumber form the database

        Returns the value of the index
    */
    JMBDEMODELS_EXPORT int getMobileNumberIndex() const
    {
        return m_MobileNumberIndex;
    }

    /*!
        \fn int getMailAddressIndex()

        \brief Get the index of the fieldname MailAddress form the database

        Returns the value of the index
    */
    JMBDEMODELS_EXPORT int getMailAddressIndex() const
    {
        return m_MailAddressIndex;
    }

    /*!
        \fn int getActiveIndex()

        \brief Get the index of the fieldname Active form the database

        Returns the value of the index
    */
    JMBDEMODELS_EXPORT int getActiveIndex() const
    {
        return m_ActiveIndex;
    }

    /*!
        \fn int getEmployeeIdIndex()

         \brief Get the index of the fieldname EmployeeId form the database

         Returns the value of the index
    */
    JMBDEMODELS_EXPORT int getEmployeeIdIndex() const
    {
        return m_EmployeeIdIndex;
    }

    /*!
        \fn  int getLastUpdateIndex()

    \brief Get the index of the fieldname LastUpdate form the database

            Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getLastUpdateIndex() const
    {
        return m_LastUpdateIndex;
    }

private:
    const QString m_tableName = QLatin1String("company"); ///< QString m_tableName

    /*!
     * @ brief m_db
     */
    QSqlDatabase m_db = {};

    /*!
     * @brief DataContext
     */
    Model::DataContext* m_dataContext = {};

    int m_CompanyIdIndex { 0 }; ///< int CompanyIdIndex
    int m_NameIndex { 0 }; ///< int NameIndex
    int m_Name2Index { 0 }; ///< int Name2Index
    int m_StreetIndex { 0 }; ///< int m_StreetIndex
    int m_CityIndex { 0 }; ///< int CityIndex
    int m_ZipCodeIndex { 0 }; ///< int ZipCodeIndex
    int m_PhoneNumberIndex { 0 }; ///< int PhoneNumberIndex
    int m_FaxNumberIndex { 0 }; ///< int FaxNumberIndex
    int m_MobileNumberIndex { 0 }; ///< int MobileNumberIndex
    int m_MailAddressIndex { 0 }; ///< int MailAddressIndex
    int m_ActiveIndex { 0 }; ///< int ActiveIndex
    int m_EmployeeIdIndex { 0 }; ///< int EmployeeIdIndex
    int m_LastUpdateIndex { 0 }; ///< int LastUpdateIndex
};
} // namespace Model
