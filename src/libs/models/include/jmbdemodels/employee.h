/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert
 * <juergen.muelbert@gmail.com>
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

#include "jmbdemodels_export.h"

namespace Model {
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
    \version 0.7
    \date 25.12.2021
    \copyright GPL-3.0-or-later
    */
class Employee : public CommonData {
  Q_OBJECT

public:
  /*!
      \fn explicit Employee()
      \brief The Constructor for the Employee
  */
  explicit JMBDEMODELS_EXPORT Employee();

  /*!
      \fn  ~Employee() override;

      \brief Destructor for Employee
   */
  JMBDEMODELS_EXPORT ~Employee() {}

  // implement the virtuals

  /*!
      \fn virtual void setIndexes()
      \brief Set the fieldindexes from the datafieldnames of the db.
   */
  virtual JMBDEMODELS_EXPORT void setIndexes() final;

  /*!
      \fn virtual JMBDEMODELS_EXPORT auto initializeRelationalModel() ->
     QSqlRelationalTableModel* final \brief set the QSqlRelationalTableModel for
     the DataModel \return The QSqlRelationalTableModel
   */
  virtual JMBDEMODELS_EXPORT auto initializeRelationalModel()
      -> QSqlRelationalTableModel * final;

  /*!
      \fn virtual auto initializeInputDataModel() -> QSqlRelationalTableModel*
     fina \brief Initialize the InputDataModel

       \return The QSqlRelationalTableModel
   */
  virtual JMBDEMODELS_EXPORT auto initializeInputDataModel()
      -> QSqlRelationalTableModel * final;

  /*!
      \fn virtual auto initializeViewModel() -> QSqlTableModel* final
      \brief Initialize the ViewModel

      \return QSqlTableModel
   */
  virtual JMBDEMODELS_EXPORT auto initializeViewModel()
      -> QSqlTableModel * final;

  /*!
      \fn virtual auto initializeListModel() -> QSqlTableModel* final
      \brief Initiallize the list Model for select one dataset
  */
  virtual JMBDEMODELS_EXPORT auto initializeListModel()
      -> QSqlTableModel * final;

  /*!
   * \fn virtual auto generateTableString(const QString& header) -> QString
   final \brief generateTableString

      \return a QString with the generated Table for Output
   */
  virtual JMBDEMODELS_EXPORT auto generateTableString(const QString &header)
      -> QString final;

  /*!
      \fn virtual auto generateFormularString(const QString& header) -> QString
     final \brief generateFormularString

      \return a QString with the generated Table for Output
   */
  virtual JMBDEMODELS_EXPORT auto generateFormularString(const QString &header)
      -> QString final;

  // Getter
  /*!
   * \brief getTableName
   * \return
   */
  JMBDEMODELS_EXPORT auto getTableName() const -> QString {
    return this->m_tableName;
  }
  /*!
      \fn auot getDB() const -> QSqlDatabase
   */
  JMBDEMODELS_EXPORT auto getDB() const -> QSqlDatabase { return this->m_db; }

  /*!
      \fn int getEmployeeIdIndex()

      \brief Get the index of the fieldname EmployeeId form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getEmployeeIdIndex() const {
    return m_EmployeeIdIndex;
  }

  /*!
      \fn  int getEmployeeNrIndex()

      \brief Get the index of the fieldname EmployeeNr form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getEmployeeNrIndex() const {
    return m_EmployeeNrIndex;
  }

  /*!
      \fn int getGenderIndex()

      \brief Get the index of the fieldname Gender form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getGenderIndex() const { return m_GenderIndex; }

  /*!
      \fn int getTitleIdIndex()

      \brief Get the index of the fieldname TitleId form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getTitleIdIndex() const { return m_TitleIdIndex; }

  /*!
      \fn int getFirstNameIndex()

      \brief Get the index of the fieldname FirstName form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getFirstNameIndex() const { return m_FirstNameIndex; }

  /*!
      \fn int getLastNameIndex()

      \brief Get the index of the fieldname LastName form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getLastNameIndex() const { return m_LastNameIndex; }

  /*!
      \fn int getBirthDayIndex()

      \brief Get the index of the fieldname BirthDay form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getBirthDayIndex() const { return m_BirthDayIndex; }

  /*!
      \fn  int getAddressIndex()

      \brief Get the index of the fieldname Address form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getAddressIndex() const { return m_AddressIndex; }

  /*!
     \fn int getZipCityIdIndex()

     \brief Get the index of the fieldname ZipCityId form the database

     Returns the value of the index
  */
  JMBDEMODELS_EXPORT int getZipCityIdIndex() const { return m_ZipCityIdIndex; }

  /*!
     \fn int getHomePhoneIndex()

     \brief Get the index of the fieldname HomePhone form the database

     Returns the value of the index
  */
  JMBDEMODELS_EXPORT int getHomePhoneIndex() const { return m_HomePhoneIndex; }

  /*!
     \fn int getHomeMobileIndex()

     \brief Get the index of the fieldname HomeMobile form the database

     Returns the value of the index
  */
  JMBDEMODELS_EXPORT int getHomeMobileIndex() const {
    return m_HomeMobileIndex;
  }

  /*!
     \fn int getHomeMailIndex()

     \brief Get the index of the fieldname HomeMail form the database

     Returns the value of the index
  */
  JMBDEMODELS_EXPORT int getHomeMailIndex() const { return m_HomeMailIndex; }

  /*!
      \fn int getBusinessMailIndex()

      \brief Get the index of the fieldname BusinessMail form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getBusinessMailIndex() const {
    return m_BusinessMailIndex;
  }

  /*!
      \fn int getDataCareIndex()

      \brief Get the index of the fieldname DataCare form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getDataCareIndex() const { return m_DataCareIndex; }

  /*!
      \fn int getActiveIndex()

      \brief Get the index of the fieldname Active form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getActiveIndex() const { return m_ActiveIndex; }

  /*!
      \fn int getPhotoIndex()

      \brief Get the index of the fieldname Photo form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getPhotoIndex() const { return m_PhotoIndex; }

  /*!
      \fn int getNotesIndex()

      \brief Get the index of the fieldname Notes form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getNotesIndex() const { return m_NotesIndex; }

  /*!
      \fn int getHireDateIndex()

      \brief Get the index of the fieldname  HireDate form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getHireDateIndex() const { return m_HireDateIndex; }

  /*!
      \fn int getEndDateIndex()

      \brief Get the index of the fieldname  EndDate form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getEndDateIndex() const { return m_EndDateIndex; }

  /*!
      \fn int getDepartmentIdIndex()

      \brief Get the index of the fieldname DepartmentId form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getDepartmentIdIndex() const {
    return m_DepartmentIdIndex;
  }

  /*!
      \fn int getFunctionIdIndex()

      \brief Get the index of the fieldname FunctionId form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getFunctionIdIndex() const {
    return m_FunctionIdIndex;
  }

  /*!
      \fn int getComputerIdIndex()

      \brief Get the index of the fieldname ComputerId form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getComputerIdIndex() const {
    return m_ComputerIdIndex;
  }

  /*!
      \fn int getPrinterIdIndex()

      \brief Get the index of the fieldname PrinterId form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getPrinterIdIndex() const { return m_PrinterIdIndex; }

  /*!
      \fn int getPhoneIdIndex()

      \brief Get the index of the fieldname PhoneId form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getPhoneIdIndex() const { return m_PhoneIdIndex; }

  /*!
      \fn int getMobileIdIndex()

      \brief Get the index of the fieldname MobileId form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getMobileIdIndex() const { return m_MobileIdIndex; }

  /*!
      \fn int getFaxIdIndex()

      \brief Get the index of the fieldname FaxId form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getFaxIdIndex() const { return m_FaxIdIndex; }

  /*!
      \fn int getEmployeeAccountIdIndex()

      \brief Get the index of the fieldname EmployeeAccountId form the
     database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getEmployeeAccountIdIndex() const {
    return m_EmployeeAccountIdIndex;
  }

  /*!
      \fn int getEmployeeDocumentIdIndex()

      \brief Get the index of the fieldname EmployeeDocumentId form the
     database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getEmployeeDocumentIdIndex() const {
    return m_EmployeeDocumentIdIndex;
  }

  /*!
      \fn int getChipCardIdIndex()

      \brief Get the index of the fieldname ChipCardId form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getChipCardIdIndex() const {
    return m_ChipCardIdIndex;
  }

  /*!
      \fn  int getLastUpdateIndex()

      \brief Get the index of the fieldname LastUpdate form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getLastUpdateIndex() const {
    return m_LastUpdateIndex;
  }

protected:
private:
  /*!
      \brief The Tablename in the database \e is const
   */
  const QString m_tableName = QLatin1String("employee");

  /*!
   * @ brief m_db
   */
  QSqlDatabase m_db = {};

  /*!
   * @brief DataContext
   */
  Model::DataContext *m_dataContext = {};

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
};
} // namespace Model
