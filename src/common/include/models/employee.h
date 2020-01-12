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

#include <QAbstractTableModel>


#include "definitions.h"
#include "jmbde_common_export.h"
#include "models/idatamodel.h"

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

namespace Model {
class JMBDE_COMMON_EXPORT EmployeeTableModel : public QAbstractTableModel {
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
    Q_LOGGING_CATEGORY(employeeLC, "jmbde.models.employee")

public:
    /*!
        \fn explicit EmployeeTableModel(QAbstractTaableModel *parent = nullptr)
        \brief The Constructor for the Employee
    */
    explicit EmployeeTableModel(QAbstractTableModel *parent = nullptr);

    /*!
        \fn  ~Employee() override;

        \brief Destructor for Employee
     */
    ~EmployeeTableModel();

    // Implement the functions
    int rowCount(const QModelIndex & = QModelIndex()) const override
    {
        return 200;
    }

    int columnCount(const QModelIndex & = QModelIndex()) const override
    {
        return 200;
    }

    QVariant data(const QModelIndex &index, int role) const override
    {
        switch (role) {
        case Qt::DisplayRole:
            return QString("%1, %2").arg(index.column()).arg(index.row());
        default:
            break;
        }
        return QVariant();
    }

    QHash<int, QByteArray> roleNames() const override
    {
        return { {Qt::DisplayRole, "display"} };
    }

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
        \fn int EmployeeIdIndex()

        \brief Get the index of the fieldname EmployeeId form the database

        Returns the value of the index
     */
    int EmployeeIdIndex() const { return m_EmployeeIdIndex; }

    /*!
        \fn  int EmployeeNrIndex()

        \brief Get the index of the fieldname EmployeeNr form the database

        Returns the value of the index
     */
    int EmployeeNrIndex() const { return m_EmployeeNrIndex; }

    /*!
        \fn int GenderIndex()

        \brief Get the index of the fieldname Gender form the database

        Returns the value of the index
     */
    int GenderIndex() const { return m_GenderIndex; }

    /*!
        \fn int TitleIdIndex()

        \brief Get the index of the fieldname TitleId form the database

        Returns the value of the index
     */
    int TitleIdIndex() const { return m_TitleIdIndex; }

    /*!
        \fn int FirstNameIndex()

        \brief Get the index of the fieldname FirstName form the database

        Returns the value of the index
     */
    int FirstNameIndex() const { return m_FirstNameIndex; }

    /*!
        \fn int LastNameIndex()

        \brief Get the index of the fieldname LastName form the database

        Returns the value of the index
     */
    int LastNameIndex() const { return m_LastNameIndex; }

    /*!
        \fn int BirthDayIndex()

        \brief Get the index of the fieldname BirthDay form the database

        Returns the value of the index
     */
    int BirthDayIndex() const { return m_BirthDayIndex; }

    /*!
        \fn  int AddressIndex()

        \brief Get the index of the fieldname Address form the database

        Returns the value of the index
     */
    int AddressIndex() const { return m_AddressIndex; }

    /*!
       \fn int ZipCityIdIndex()

       \brief Get the index of the fieldname ZipCityId form the database

       Returns the value of the index
    */
    int ZipCityIdIndex() const { return m_ZipCityIdIndex; }

    /*!
       \fn int HomePhoneIndex()

       \brief Get the index of the fieldname HomePhone form the database

       Returns the value of the index
    */
    int HomePhoneIndex() const { return m_HomePhoneIndex; }

    /*!
       \fn int HomeMobileIndex()

       \brief Get the index of the fieldname HomeMobile form the database

       Returns the value of the index
    */
    int HomeMobileIndex() const { return m_HomeMobileIndex; }

    /*!
       \fn int HomeMailIndex()

       \brief Get the index of the fieldname HomeMail form the database

       Returns the value of the index
    */
    int HomeMailIndex() const { return m_HomeMailIndex; }

    /*!
        \fn int BusinessMailIndex()

        \brief Get the index of the fieldname BusinessMail form the database

        Returns the value of the index
     */
    int BusinessMailIndex() const { return m_BusinessMailIndex; }

    /*!
        \fn int DataCareIndex()

        \brief Get the index of the fieldname DataCare form the database

        Returns the value of the index
     */
    int DataCareIndex() const { return m_DataCareIndex; }

    /*!
        \fn int ActiveIndex()

        \brief Get the index of the fieldname Active form the database

        Returns the value of the index
     */
    int ActiveIndex() const { return m_ActiveIndex; }

    /*!
        \fn int PhotoIndex()

        \brief Get the index of the fieldname Photo form the database

        Returns the value of the index
     */
    int PhotoIndex() const { return m_PhotoIndex; }

    /*!
        \fn int NotesIndex()

        \brief Get the index of the fieldname Notes form the database

        Returns the value of the index
     */
    int NotesIndex() const { return m_NotesIndex; }

    /*!
        \fn int HireDateIndex()

        \brief Get the index of the fieldname  HireDate form the database

        Returns the value of the index
     */
    int HireDateIndex() const { return m_HireDateIndex; }

    /*!
        \fn int EndDateIndex()

        \brief Get the index of the fieldname  EndDate form the database

        Returns the value of the index
     */
    int EndDateIndex() const { return m_EndDateIndex; }

    /*!
        \fn int DepartmentIdIndex()

        \brief Get the index of the fieldname DepartmentId form the database

        Returns the value of the index
     */
    int DepartmentIdIndex() const { return m_DepartmentIdIndex; }

    /*!
        \fn int FunctionIdIndex()

        \brief Get the index of the fieldname FunctionId form the database

        Returns the value of the index
     */
    int FunctionIdIndex() const { return m_FunctionIdIndex; }

    /*!
        \fn int ComputerIdIndex()

        \brief Get the index of the fieldname ComputerId form the database

        Returns the value of the index
     */
    int ComputerIdIndex() const { return m_ComputerIdIndex; }

    /*!
        \fn int PrinterIdIndex()

        \brief Get the index of the fieldname PrinterId form the database

        Returns the value of the index
     */
    int PrinterIdIndex() const { return m_PrinterIdIndex; }

    /*!
        \fn int PhoneIdIndex()

        \brief Get the index of the fieldname PhoneId form the database

        Returns the value of the index
     */
    int PhoneIdIndex() const { return m_PhoneIdIndex; }

    /*!
        \fn int MobileIdIndex()

        \brief Get the index of the fieldname MobileId form the database

        Returns the value of the index
     */
    int MobileIdIndex() const { return m_MobileIdIndex; }

    /*!
        \fn int FaxIdIndex()

        \brief Get the index of the fieldname FaxId form the database

        Returns the value of the index
     */
    int FaxIdIndex() const { return m_FaxIdIndex; }

    /*!
        \fn int EmployeeAccountIdIndex()

        \brief Get the index of the fieldname EmployeeAccountId form the
       database

        Returns the value of the index
     */
    int EmployeeAccountIdIndex() const { return m_EmployeeAccountIdIndex; }

    /*!
        \fn int EmployeeDocumentIdIndex()

        \brief Get the index of the fieldname EmployeeDocumentId form the
       database

        Returns the value of the index
     */
    int EmployeeDocumentIdIndex() const { return m_EmployeeDocumentIdIndex; }

    /*!
        \fn int ChipCardIdIndex()

        \brief Get the index of the fieldname ChipCardId form the database

        Returns the value of the index
     */
    int ChipCardIdIndex() const { return m_ChipCardIdIndex; }

    /*!
        \fn  int LastUpdateIndex()

        \brief Get the index of the fieldname LastUpdate form the database

        Returns the value of the index
     */
    int LastUpdateIndex() const { return m_LastUpdateIndex; }

    /*!
        \fn QString setOutFormularStyle()
        \brief Initialize a String with the css-style for the output formular
        \details This is now just the Header

        Returns The initialized QString

        \sa QString
     */
     QString setOutFormularStyle();

     /*!
        \fn QString setOutTableStyle()
        \brief Initialize a String with the css-style for the output table

        Returns The initialized QString

        \sa QString
      */
      QString setOutTableStyle();


protected:
private:
    /*!
        \fn  QTextDocument *createSheet()
        \brief Create a TextDocument for the Output to the Printer

    Returns The Pointer to the generated TextDocument

        \sa  QTextDocument
            */
        QTextDocument *createSheet();




    /*!
        \brief The Tablename in the database \e is const
     */
    const QString m_tableName = QLatin1String("employee");

    /*!
       \var int m_EmployeeIdIndex
       \brief The value of the EmployeeIdIndex
    */
    int m_EmployeeIdIndex{0};

    /*!
       \var int m_EmployeeNrIndex
       \brief The value of the EmployeeNrIndex
    */
    int m_EmployeeNrIndex{0};

    /*!
       \var int m_GenderIndex
       \brief The value of the GenderIndex
    */
    int m_GenderIndex{0};

    /*!
       \var int m_TitleIdIndex
       \brief The value of the TitleIdIndex
    */
    int m_TitleIdIndex{0};

    /*!
       \var int m_FirstNameIndex
       \brief The value of the FirstNameIndex
    */
    int m_FirstNameIndex{0};

    /*!
        \var int m_LastNameIndex
        \brief The value of the LastNameIndex
     */
    int m_LastNameIndex{0};

    /*!
        \var int m_BirthDayIndex
        \brief The value of the BirthDayIndex
     */
    int m_BirthDayIndex{0};

    /*!
        \var int m_AddressIndex
        \brief The value of the AddressIndex
     */
    int m_AddressIndex{0};

    /*!
        \var int m_ZipCityIdIndex
        \brief The value of the ZipCityIdIndex
     */
    int m_ZipCityIdIndex{0};

    /*!
        \var int m_HomePhoneIndex
        \brief The value of the HomePhoneIndex
     */
    int m_HomePhoneIndex{0};

    /*!
        \var int m_HomeMobileIndex
        \brief The value of the HomeMobileIndex
     */
    int m_HomeMobileIndex{0};

    /*!
        \var int m_HomeMailIndex
        \brief The value of the HomeMailIndex
     */
    int m_HomeMailIndex{0};

    /*!
        \var int m_BusinessMailIndex
        \brief The value of the BusinessMailIndex
     */
    int m_BusinessMailIndex{0};

    /*!
        \var int m_DataCareIndex
        \brief The value of the DataCareIndex
     */
    int m_DataCareIndex{0};

    /*!
        \var int m_ActiveIndex
        \brief The value of the ActiveIndex
     */
    int m_ActiveIndex{0};

    /*!
        \var int m_PhotoIndex
        \brief The value of the PhotoIndex
     */
    int m_PhotoIndex{0};

    /*!
        \var int m_NotesIndex
        \brief The value of the NotesIndex
     */
    int m_NotesIndex{0};

    /*!
        \var int m_HireDateIndex
        \brief The value of the HireDateIndex
     */
    int m_HireDateIndex{0};

    /*!
        \var int m_EndDateIndex
        \brief The value of the EndDateIndex
     */
    int m_EndDateIndex{0};

    /*!
        \var int m_DepartmentIdIndex
        \brief The value of the DepartmentIdIndex
     */
    int m_DepartmentIdIndex{0};

    /*!
        \var int m_FunctionIdIndex
        \brief The value of the FunctionIdIndex
     */
    int m_FunctionIdIndex{0};

    /*!
        \var int m_ComputerIdIndex
        \brief The value of the ComputerIdIndex
     */
    int m_ComputerIdIndex{0};

    /*!
        \var int m_PrinterIdIndex
        \brief The value of the PrinterIdIndex
     */
    int m_PrinterIdIndex{0};

    /*!
        \var int m_PhoneIdIndex
        \brief The value of the PhoneIdIndex
     */
    int m_PhoneIdIndex{0};

    /*!
        \var int m_MobileIdIndex
        \brief The value of the MobileIdIndex
     */
    int m_MobileIdIndex{0};

    /*!
        \var int m_FaxIdIndex
        \brief The value of the FaxIdIndex
     */
    int m_FaxIdIndex{0};

    /*!
        \var int m_EmployeeAccountIdIndex
        \brief The value of the EmployeeAccountIdIndex
     */
    int m_EmployeeAccountIdIndex{0};

    /*!
        \var int m_EmployeeDocumentIdIndex
        \brief The value of the EmployeeDocumentIdIndex
     */
    int m_EmployeeDocumentIdIndex{0};

    /*!
        \var int m_ChipCardIdIndex
        \brief The value of the ChipCardIdIndex
     */
    int m_ChipCardIdIndex{0};

    /*!
        \var int m_LastUpdateIndex
        \brief The value of the LastUpdateIndex
    */
    int m_LastUpdateIndex{0};

    /*!
        \brief holds an initialised pointer to the Relationmodel
        \sa QSqlRelationalTableModel
     */
    QSqlRelationalTableModel *m_model{nullptr};

    /*!
       \brief holds an initialised pointer to the ItemSelectioModel
       \sa QItemSelectionModel
    */
    QItemSelectionModel *m_selectionModel{nullptr};

};
} // namespace Model
