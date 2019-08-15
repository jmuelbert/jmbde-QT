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
    \class Company
    \brief The Companyl class
    \details In this is handlet all Companies in the Database
    \author Jürgen Mülbert
    \since 0.4
    \version 0.4.25
    \date 03.08.2019
    \copyright EUPL V1.2
    */

namespace Model {

class JMBDE_COMMON_EXPORT Company : public CommonData {
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
    Q_LOGGING_CATEGORY(companyLC, "jmbde.models.company")

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
    virtual ~Company() = default;

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
        \fn int CompanyIdIndex()

        \brief Get the index of the fieldname CompanyId form the database

        Returns the value of the index
     */
    int CompanyIdIndex() const { return m_CompanyIdIndex; }

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
        \fn int StreetIndex()

        \brief Get the index of the fieldname Street form the database

        Returns the value of the index
     */
    int StreetIndex() const { return m_StreetIndex; }

    /*!
        \fn int CityIndex()

        \brief Get the index of the fieldname City form the database

        Returns the value of the index
    */
    int CityIndex() const { return m_CityIndex; }

    /*!
        \fn int ZipCodeIndex()

        \brief Get the index of the fieldname ZipCode form the database

        Returns the value of the index
    */
    int ZipCodeIndex() const { return m_ZipCodeIndex; }

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
        \fn int FaxNumberIndex()

        \brief Get the index of the fieldname FaxNumber form the database

        Returns the value of the index
    */
    int MobileNumberIndex() const { return m_MobileNumberIndex; }

    /*!
        \fn int MailAddressIndex()

        \brief Get the index of the fieldname MailAddress form the database

        Returns the value of the index
    */
    int MailAddressIndex() const { return m_MailAddressIndex; }

    /*!
        \fn int ActiveIndex()

        \brief Get the index of the fieldname Active form the database

        Returns the value of the index
    */
    int ActiveIndex() const { return m_ActiveIndex; }

    /*!
        \fn int EmployeeIdIndex()

         \brief Get the index of the fieldname EmployeeId form the database

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
        \variable  const QString m_tableName
        \brief The Tablename in the database \e is const
     */
    const QString m_tableName = QLatin1String("company");

    /*!
        \brief The value of the CompanyIdIndex
     */
    int m_CompanyIdIndex;

    /*!
        \brief The value of the NameIndex
     */
    int m_NameIndex;

    /*!
        \brief The value of the Name2Index
     */
    int m_Name2Index;

    /*!
        \brief The value of the StreetIndex
     */
    int m_StreetIndex;

    /*!
        \brief The value of the CityIndex
     */
    int m_CityIndex;

    /*!
        \brief The value of the ZipCodeIndex
     */
    int m_ZipCodeIndex;

    /*!
        \brief The value of the PhoneNumberIndex
     */
    int m_PhoneNumberIndex;

    /*!
        \brief The value of the FaxNumberIndex
     */
    int m_FaxNumberIndex;

    /*!
        \brief The value of the MobileNumberIndex
     */
    int m_MobileNumberIndex;

    /*!
        \brief The value of the MailAddressIndex
     */
    int m_MailAddressIndex;

    /*!
        \brief The value of the ActiveIndex
     */
    int m_ActiveIndex;

    /*!
        \brief The value of the EmployeeIdIndex
     */
    int m_EmployeeIdIndex;

    /*!
        \brief The value of the LastUpdateIndex
     */
    int m_LastUpdateIndex;
};
} // namespace Model
