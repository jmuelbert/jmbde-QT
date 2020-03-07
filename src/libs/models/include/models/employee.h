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
#include <QSet>
#include <QSetIterator>

#include <QStandardPaths>
#include <QtSql>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlRelation>

#include <QTableView>
#include <QTextDocument>

#include "jmbdemodels-version.h"
#include "jmbdemodels_export.h"
#include "loggingcategory.h"
#include "models/commondata.h"
#include "models/idatamodel.h"



namespace Model
{

/*!
    \class Employee
    \brief The Employee class

    \details
        ## The Datafields ##
        - The title is Dr., Ing. and so on
        - address is foreign key for the address table
         - gender (m/w)
         - birthday of the employee
        - email address in the company
        - datacare in german datenschutz (y/n)
          or TRUE / FALSE
        - active is the employee real here
        - startdate  the employee is then here
        - enddate this is the last day
        - the foreign key to the department
        - the foreign key for the function of the employee
        - the foreign key to the computer
        - the foreign key to the printer
        - the foreign key to the inhouse phone
        - the foreign key to the mobile
        - the foreign key to the fax
        - the foreign key to the table of accounts
        - the foreign key to the table of documents

digraph g {
    graph [
        rankdir = "LR";
    ];
    node [
        fontsize = "16";
        shape = "record";
        ];
    }

    \author Jürgen Mülbert
    \since 0.4
    \version 0.4.25
    \date 03.08.2019
    \copyright EUPL V1.2
 */
class JMBDEMODELS_EXPORT Employee : public CommonData
{


public:
    /*!
        \fn explicit Employee(QObject *parent = nullptr)
        \brief The Constructor for the Employee
    */
    explicit Employee(QObject *parent = nullptr);

    /*!
        \fn  ~Employee() override;

        \brief Destructor for Employee
     */
    ~Employee();

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
        \fn int EmployeeIdIndex()

        \brief Get the index of the fieldname EmployeeId form the database

        Returns the value of the index
     */
    int EmployeeIdIndex() const
    {
        return m_EmployeeIdIndex;
    }

    /*!
        \fn  int EmployeeNrIndex()

        \brief Get the index of the fieldname EmployeeNr form the database

        Returns the value of the index
     */
    int EmployeeNrIndex() const
    {
        return m_EmployeeNrIndex;
    }

    /*!
        \fn int GenderIndex()

        \brief Get the index of the fieldname Gender form the database

        Returns the value of the index
     */
    int GenderIndex() const
    {
        return m_GenderIndex;
    }

    /*!
        \fn int TitleIdIndex()

        \brief Get the index of the fieldname TitleId form the database

        Returns the value of the index
     */
    int TitleIdIndex() const
    {
        return m_TitleIdIndex;
    }

    /*!
        \fn int FirstNameIndex()

        \brief Get the index of the fieldname FirstName form the database

        Returns the value of the index
     */
    int FirstNameIndex() const
    {
        return m_FirstNameIndex;
    }

    /*!
        \fn int LastNameIndex()

        \brief Get the index of the fieldname LastName form the database

        Returns the value of the index
     */
    int LastNameIndex() const
    {
        return m_LastNameIndex;
    }

    /*!
        \fn int BirthDayIndex()

        \brief Get the index of the fieldname BirthDay form the database

        Returns the value of the index
     */
    int BirthDayIndex() const
    {
        return m_BirthDayIndex;
    }

    /*!
        \fn  int AddressIndex()

        \brief Get the index of the fieldname Address form the database

        Returns the value of the index
     */
    int AddressIndex() const
    {
        return m_AddressIndex;
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
       \fn int HomePhoneIndex()

       \brief Get the index of the fieldname HomePhone form the database

       Returns the value of the index
    */
    int HomePhoneIndex() const
    {
        return m_HomePhoneIndex;
    }

    /*!
       \fn int HomeMobileIndex()

       \brief Get the index of the fieldname HomeMobile form the database

       Returns the value of the index
    */
    int HomeMobileIndex() const
    {
        return m_HomeMobileIndex;
    }

    /*!
       \fn int HomeMailIndex()

       \brief Get the index of the fieldname HomeMail form the database

       Returns the value of the index
    */
    int HomeMailIndex() const
    {
        return m_HomeMailIndex;
    }

    /*!
        \fn int BusinessMailIndex()

        \brief Get the index of the fieldname BusinessMail form the database

        Returns the value of the index
     */
    int BusinessMailIndex() const
    {
        return m_BusinessMailIndex;
    }

    /*!
        \fn int DataCareIndex()

        \brief Get the index of the fieldname DataCare form the database

        Returns the value of the index
     */
    int DataCareIndex() const
    {
        return m_DataCareIndex;
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
        \fn int PhotoIndex()

        \brief Get the index of the fieldname Photo form the database

        Returns the value of the index
     */
    int PhotoIndex() const
    {
        return m_PhotoIndex;
    }

    /*!
        \fn int NotesIndex()

        \brief Get the index of the fieldname Notes form the database

        Returns the value of the index
     */
    int NotesIndex() const
    {
        return m_NotesIndex;
    }

    /*!
        \fn int HireDateIndex()

        \brief Get the index of the fieldname  HireDate form the database

        Returns the value of the index
     */
    int HireDateIndex() const
    {
        return m_HireDateIndex;
    }

    /*!
        \fn int EndDateIndex()

        \brief Get the index of the fieldname  EndDate form the database

        Returns the value of the index
     */
    int EndDateIndex() const
    {
        return m_EndDateIndex;
    }

    /*!
        \fn int DepartmentIdIndex()

        \brief Get the index of the fieldname DepartmentId form the database

        Returns the value of the index
     */
    int DepartmentIdIndex() const
    {
        return m_DepartmentIdIndex;
    }

    /*!
        \fn int FunctionIdIndex()

        \brief Get the index of the fieldname FunctionId form the database

        Returns the value of the index
     */
    int FunctionIdIndex() const
    {
        return m_FunctionIdIndex;
    }

    /*!
        \fn int ComputerIdIndex()

        \brief Get the index of the fieldname ComputerId form the database

        Returns the value of the index
     */
    int ComputerIdIndex() const
    {
        return m_ComputerIdIndex;
    }

    /*!
        \fn int PrinterIdIndex()

        \brief Get the index of the fieldname PrinterId form the database

        Returns the value of the index
     */
    int PrinterIdIndex() const
    {
        return m_PrinterIdIndex;
    }

    /*!
        \fn int PhoneIdIndex()

        \brief Get the index of the fieldname PhoneId form the database

        Returns the value of the index
     */
    int PhoneIdIndex() const
    {
        return m_PhoneIdIndex;
    }

    /*!
        \fn int MobileIdIndex()

        \brief Get the index of the fieldname MobileId form the database

        Returns the value of the index
     */
    int MobileIdIndex() const
    {
        return m_MobileIdIndex;
    }

    /*!
        \fn int FaxIdIndex()

        \brief Get the index of the fieldname FaxId form the database

        Returns the value of the index
     */
    int FaxIdIndex() const
    {
        return m_FaxIdIndex;
    }

    /*!
        \fn int EmployeeAccountIdIndex()

        \brief Get the index of the fieldname EmployeeAccountId form the
       database

        Returns the value of the index
     */
    int EmployeeAccountIdIndex() const
    {
        return m_EmployeeAccountIdIndex;
    }

    /*!
        \fn int EmployeeDocumentIdIndex()

        \brief Get the index of the fieldname EmployeeDocumentId form the
       database

        Returns the value of the index
     */
    int EmployeeDocumentIdIndex() const
    {
        return m_EmployeeDocumentIdIndex;
    }

    /*!
        \fn int ChipCardIdIndex()

        \brief Get the index of the fieldname ChipCardId form the database

        Returns the value of the index
     */
    int ChipCardIdIndex() const
    {
        return m_ChipCardIdIndex;
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

protected:
private:
    /*!
        \brief The Tablename in the database \e is const
     */
    const QString m_tableName = QLatin1String("employee");

    /*!
       \var int m_EmployeeIdIndex
       \brief The value of the EmployeeIdIndex
    */
    int m_EmployeeIdIndex {0};

    /*!
       \var int m_EmployeeNrIndex
       \brief The value of the EmployeeNrIndex
    */
    int m_EmployeeNrIndex {0};

    /*!
       \var int m_GenderIndex
       \brief The value of the GenderIndex
    */
    int m_GenderIndex {0};

    /*!
       \var int m_TitleIdIndex
       \brief The value of the TitleIdIndex
    */
    int m_TitleIdIndex {0};

    /*!
       \var int m_FirstNameIndex
       \brief The value of the FirstNameIndex
    */
    int m_FirstNameIndex {0};

    /*!
        \var int m_LastNameIndex
        \brief The value of the LastNameIndex
     */
    int m_LastNameIndex {0};

    /*!
        \var int m_BirthDayIndex
        \brief The value of the BirthDayIndex
     */
    int m_BirthDayIndex {0};

    /*!
        \var int m_AddressIndex
        \brief The value of the AddressIndex
     */
    int m_AddressIndex {0};

    /*!
        \var int m_ZipCityIdIndex
        \brief The value of the ZipCityIdIndex
     */
    int m_ZipCityIdIndex {0};

    /*!
        \var int m_HomePhoneIndex
        \brief The value of the HomePhoneIndex
     */
    int m_HomePhoneIndex {0};

    /*!
        \var int m_HomeMobileIndex
        \brief The value of the HomeMobileIndex
     */
    int m_HomeMobileIndex {0};

    /*!
        \var int m_HomeMailIndex
        \brief The value of the HomeMailIndex
     */
    int m_HomeMailIndex {0};

    /*!
        \var int m_BusinessMailIndex
        \brief The value of the BusinessMailIndex
     */
    int m_BusinessMailIndex {0};

    /*!
        \var int m_DataCareIndex
        \brief The value of the DataCareIndex
     */
    int m_DataCareIndex {0};

    /*!
        \var int m_ActiveIndex
        \brief The value of the ActiveIndex
     */
    int m_ActiveIndex {0};

    /*!
        \var int m_PhotoIndex
        \brief The value of the PhotoIndex
     */
    int m_PhotoIndex {0};

    /*!
        \var int m_NotesIndex
        \brief The value of the NotesIndex
     */
    int m_NotesIndex {0};

    /*!
        \var int m_HireDateIndex
        \brief The value of the HireDateIndex
     */
    int m_HireDateIndex {0};

    /*!
        \var int m_EndDateIndex
        \brief The value of the EndDateIndex
     */
    int m_EndDateIndex {0};

    /*!
        \var int m_DepartmentIdIndex
        \brief The value of the DepartmentIdIndex
     */
    int m_DepartmentIdIndex {0};

    /*!
        \var int m_FunctionIdIndex
        \brief The value of the FunctionIdIndex
     */
    int m_FunctionIdIndex {0};

    /*!
        \var int m_ComputerIdIndex
        \brief The value of the ComputerIdIndex
     */
    int m_ComputerIdIndex {0};

    /*!
        \var int m_PrinterIdIndex
        \brief The value of the PrinterIdIndex
     */
    int m_PrinterIdIndex {0};

    /*!
        \var int m_PhoneIdIndex
        \brief The value of the PhoneIdIndex
     */
    int m_PhoneIdIndex {0};

    /*!
        \var int m_MobileIdIndex
        \brief The value of the MobileIdIndex
     */
    int m_MobileIdIndex {0};

    /*!
        \var int m_FaxIdIndex
        \brief The value of the FaxIdIndex
     */
    int m_FaxIdIndex {0};

    /*!
        \var int m_EmployeeAccountIdIndex
        \brief The value of the EmployeeAccountIdIndex
     */
    int m_EmployeeAccountIdIndex {0};

    /*!
        \var int m_EmployeeDocumentIdIndex
        \brief The value of the EmployeeDocumentIdIndex
     */
    int m_EmployeeDocumentIdIndex {0};

    /*!
        \var int m_ChipCardIdIndex
        \brief The value of the ChipCardIdIndex
     */
    int m_ChipCardIdIndex {0};

    /*!
        \var int m_LastUpdateIndex
        \brief The value of the LastUpdateIndex
    */
    int m_LastUpdateIndex {0};
};
} // namespace Model
