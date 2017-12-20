/*
   // EmployeeDataModel.h
   // part of jmbde
   //
   // Copyright (c) 2013-2017 Jürgen Mülbert. All rights reserved.
   //
   // Licensed under the EUPL, Version 1.2 or – as soon they
   // will be approved by the European Commission - subsequent
   // versions of the EUPL (the "Licence");
   // You may not use this work except in compliance with the
   // Licence.
   // You may obtain a copy of the Licence at:
   //
   // https://joinup.ec.europa.eu/page/eupl-text-11-12
   //
   // Unless required by applicable law or agreed to in
   // writing, software distributed under the Licence is
   // distributed on an "AS IS" basis,
   // WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
   // express or implied.
   // See the Licence for the specific language governing
   // permissions and limitations under the Licence.
   //
   // Lizenziert unter der EUPL, Version 1.2 oder - sobald
   // diese von der Europäischen Kommission genehmigt wurden -
   // Folgeversionen der EUPL ("Lizenz");
   // Sie dürfen dieses Werk ausschließlich gemäß
   // dieser Lizenz nutzen.
   // Eine Kopie der Lizenz finden Sie hier:
   //
   // https://joinup.ec.europa.eu/page/eupl-text-11-12
   //
   // Sofern nicht durch anwendbare Rechtsvorschriften
   // gefordert oder in schriftlicher Form vereinbart, wird
   // die unter der Lizenz verbreitete Software "so wie sie
   // ist", OHNE JEGLICHE GEWÄHRLEISTUNG ODER BEDINGUNGEN -
   // ausdrücklich oder stillschweigend - verbreitet.
   // Die sprachspezifischen Genehmigungen und Beschränkungen
   // unter der Lizenz sind dem Lizenztext zu entnehmen.
   //
 */

#ifndef EMPLOYEEDATAMODEL_H
#define EMPLOYEEDATAMODEL_H

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

#include "commondatamodel.h"
#include "definitions.h"
#include "idatamodel.h"

/**
 * @brief EmployeeDataModel::EmployeeDataModel
 * @param parent
 *
 * The Datafields:
   -- - The title is Dr., Ing. and so on
   -- - address is foreign key for the address table
   -- - gender (m/w)
   -- - birthday of the employee
   -- - email address in the company
   -- - datacare in german datenschutz (y/n)
   --   or TRUE / FALSE
   -- - active is the employee real here
   -- - startdate  the employee is then here
   -- - enddate this is the last day
   -- - the foreign key to the department
   -- - the foreign key for the function of the employee
   -- - the foreign key to the computer
   -- - the foreign key to the printer
   -- - the foreign key to the inhouse phone
   -- - the foreign key to the mobile
   -- - the foreign key to the fax
   -- - the foreign key to the table of accounts
   -- - the foreign key to the table of documents
 *
 * digraph g {
 *  graph [
        rankdir = "LR";
    ];
    node [
        fontsize = "16";
        shape = "record";
        ];
    }
 */

class EmployeeDataModel : public CommonDataModel, public IDataModel {
  Q_OBJECT

  public:

    /**
     * @brief EmployeeDataModel
     * @details The Datamodel for the Accounts from the Employees
     * @param parent
     */
    EmployeeDataModel(QObject* parent = 0);

    /**
     * @brief ~EmployeeDataModel
     */
    ~EmployeeDataModel();

    // implement the virtuals

    /**
     * @brief createDataTable
     * @return bool - true if creation of the table successfull
     */
    virtual bool createDataTable();

    /**
     * @brief setIndexes
     */
    virtual void setIndexes();

    /**
     * @brief initializeRelationalModel
     * @return
     */
    virtual QSqlRelationalTableModel* initializeRelationalModel();

    /**
     * @brief initializeInputDataModel
     * @return
     */
    virtual QSqlRelationalTableModel* initializeInputDataModel();

    /**
     * @brief initializeViewModel
     * @return
     */
    virtual QSqlTableModel* initializeViewModel();

    /**
     * @brief generateTableString
     * @param model
     * @param header
     * @return
     */
    virtual QString generateTableString(QAbstractTableModel* model, QString header);

    /**
     * @brief generateFormularString
     * @param model
     * @param header
     * @return
     */
    virtual QString generateFormularString(QAbstractTableModel* model, QString header);

    // Getter
    /**
     * @brief EmployeeIdIndex
     * @return
     */
    int EmployeeIdIndex() const {
        return m_EmployeeIdIndex;
    }

    /**
     * @brief EmployeeNrIndex
     * @return
     */
    int EmployeeNrIndex() const
    {
      return m_EmployeeNrIndex;
    }

    /**
     * @brief GenderIndex
     * @return
     */
    int GenderIndex() const
    {
      return m_GenderIndex;
    }

    /**
     * @brief TitleIdIndex
     * @return
     */
    int TitleIdIndex() const
    {
      return m_TitleIdIndex;
    }

    /**
     * @brief FirstNameIndex
     * @return
     */
    int FirstNameIndex() const
    {
      return m_FirstNameIndex;
    }

    /**
     * @brief LastNameIndex
     * @return
     */
    int LastNameIndex() const
    {
      return m_LastNameIndex;
    }

    /**
     * @brief BirthDayIndex
     * @return
     */
    int BirthDayIndex() const
    {
      return m_BirthDayIndex;
    }

    /**
     * @brief AddressIndex
     * @return
     */
    int AddressIndex() const
    {
      return m_AddressIndex;
    }

    /**
     * @brief ZipCityIdIndex
     * @return
     */
    int ZipCityIdIndex() const
    {
      return m_ZipCityIdIndex;
    }

    /**
     * @brief HomePhoneIndex
     * @return
     */
    int HomePhoneIndex() const
    {
      return m_HomePhoneIndex;
    }

    /**
     * @brief HomeMobileIndex
     * @return
     */
    int HomeMobileIndex() const
    {
      return m_HomeMobileIndex;
    }

    /**
     * @brief HomeMailIndex
     * @return
     */
    int HomeMailIndex() const
    {
      return m_HomeMailIndex;
    }

    /**
     * @brief BusinessMailIndex
     * @return
     */
    int BusinessMailIndex() const
    {
      return m_BusinessMailIndex;
    }

    /**
     * @brief DataCareIndex
     * @return
     */
    int DataCareIndex() const
    {
      return m_DataCareIndex;
    }

    /**
     * @brief ActiveIndex
     * @return
     */
    int ActiveIndex() const
    {
      return m_ActiveIndex;
    }

    /**
     * @brief PhotoIndex
     * @return
     */
    int PhotoIndex() const
    {
      return m_PhotoIndex;
    }

    /**
     * @brief NotesIndex
     * @return
     */
    int NotesIndex() const
    {
      return m_NotesIndex;
    }

    /**
     * @brief HireDateIndex
     * @return
     */
    int HireDateIndex() const
    {
      return m_HireDateIndex;
    }

    /**
     * @brief EndDateIndex
     * @return
     */
    int EndDateIndex() const
    {
      return m_EndDateIndex;
    }

    /**
     * @brief DepartmentIdIndex
     * @return
     */
    int DepartmentIdIndex() const
    {
      return m_DepartmentIdIndex;
    }

    /**
     * @brief FunctionIdIndex
     * @return
     */
    int FunctionIdIndex() const
    {
      return m_FunctionIdIndex;
    }

    /**
     * @brief ComputerIdIndex
     * @return
     */
    int ComputerIdIndex() const
    {
      return m_ComputerIdIndex;
    }

    /**
     * @brief PrinterIdIndex
     * @return
     */
    int PrinterIdIndex() const
    {
      return m_PrinterIdIndex;
    }

    /**
     * @brief PhoneIdIndex
     * @return
     */
    int PhoneIdIndex() const
    {
      return m_PhoneIdIndex;
    }

    /**
     * @brief MobileIdIndex
     * @return
     */
    int MobileIdIndex() const
    {
      return m_MobileIdIndex;
    }

    /**
     * @brief FaxIdIndex
     * @return
     */
    int FaxIdIndex() const
    {
      return m_FaxIdIndex;
    }

    /**
     * @brief EmployeeAccountIdIndex
     * @return
     */
    int EmployeeAccountIdIndex() const
    {
      return m_EmployeeAccountIdIndex;
    }

    /**
     * @brief EmployeeDocumentIdIndex
     * @return
     */
    int EmployeeDocumentIdIndex() const
    {
      return m_EmployeeDocumentIdIndex;
    }

    /**
     * @brief ChipCardIdIndex
     * @return
     */
    int ChipCardIdIndex() const
    {
      return m_ChipCardIdIndex;
    }

    /**
     * @brief LastUpdateIndex
     * @return
     */
    int LastUpdateIndex() const { return m_LastUpdateIndex; }

  protected:

  private:

    /**
     * @brief tableName - the name of the database table
     * @
     */
    const QString m_tableName = QLatin1String("employee");

    int m_EmployeeIdIndex;
    int m_EmployeeNrIndex;
    int m_GenderIndex;
    int m_TitleIdIndex;
    int m_FirstNameIndex;
    int m_LastNameIndex;
    int m_BirthDayIndex;
    int m_AddressIndex;
    int m_ZipCityIdIndex;
    int m_HomePhoneIndex;
    int m_HomeMobileIndex;
    int m_HomeMailIndex;
    int m_BusinessMailIndex;
    int m_DataCareIndex;
    int m_ActiveIndex;
    int m_PhotoIndex;
    int m_NotesIndex;
    int m_HireDateIndex;
    int m_EndDateIndex;
    int m_DepartmentIdIndex;
    int m_FunctionIdIndex;
    int m_ComputerIdIndex;
    int m_PrinterIdIndex;
    int m_PhoneIdIndex;
    int m_MobileIdIndex;
    int m_FaxIdIndex;
    int m_EmployeeAccountIdIndex;
    int m_EmployeeDocumentIdIndex;
    int m_ChipCardIdIndex;
    int m_LastUpdateIndex;
};

#endif // EMPLOYEEDATAMODEL_H
