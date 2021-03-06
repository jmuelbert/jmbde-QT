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

Q_DECLARE_LOGGING_CATEGORY(jmbdeModelsMobileLog)

namespace Model {
/*!
    \class Mobile
    \brief The Mobile is the class to handle the mobiles
    \sa CommonDataModel
    \author Jürgen Mülbert
    \since 0.4
    \version 0.6
    \date 21.01.2020
    \copyright GPL-3.0-or-later
    */
class Mobile : public CommonData {
    Q_OBJECT

public:
    /*!
        \fn explicit Mobile()
        \brief The Constructor for the Mobile
    */
    explicit JMBDEMODELS_EXPORT Mobile();

    /*!
        \fn ~Mobile
        \brief The destructor for the Mobile
     */
    JMBDEMODELS_EXPORT ~Mobile()
    {
    }

    // implement the virtuals

    /*!
        \fn virtual void setIndexes() final
        \brief Set the fieldindexes from the datafieldnames of the db.
     */
    virtual JMBDEMODELS_EXPORT void setIndexes() final;

    /*!
        \fn virtual QSqlRelationalTableModel *initializeRelationalModel() final
        \brief set the QSqlRelationalTableModel for the DataModel
        Returns The QSqlRelationalTableModel
     */
    virtual JMBDEMODELS_EXPORT QSqlRelationalTableModel* initializeRelationalModel() final;

    /*!
            \fn virtual QSqlRelationalTableModel *initializeInputDataModel() final
            \brief Initialize the InputDataModel

            Returns The QSqlRelationalTableModel
        */
    virtual JMBDEMODELS_EXPORT QSqlRelationalTableModel* initializeInputDataModel() final;

    /*!
      \fn virtual QSqlTableModel *initializeViewModel() final
      \brief Initialize the ViewModel

      Returns QSqlTableModel
     */
    virtual JMBDEMODELS_EXPORT QSqlTableModel* initializeViewModel() final;

    /*!
        \fn QSqlTableModel *initializeListModel();
        \brief Initiallize the list Model for select one dataset
    */
    virtual JMBDEMODELS_EXPORT QSqlTableModel* initializeListModel() final;

    /*!
         \fn virtual auto generateTableString(
                                const QString &header) -> QString final
        \brief generateTableString

        Returns a QString with the generated Table for Output
     */
    virtual JMBDEMODELS_EXPORT auto generateTableString(const QString& header) -> QString final;

    /*!
         \fn virtual auto generateFormularString(
                                    const QString &header) -> QString final
         \brief generateFormularString

         Returns a QString with the generated Table for Output
      */
    virtual JMBDEMODELS_EXPORT auto generateFormularString(QString& header) -> QString final;

    // Getter
    JMBDEMODELS_EXPORT QString getTableName() const
    {
        return this->m_tableName;
    }

    JMBDEMODELS_EXPORT QSqlDatabase getDB() const
    {
        return this->m_db;
    }

    /*!
        \fn int MobileIdIndex()

        \brief Get the index of the fieldname MobileId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getMobileIdIndex() const
    {
        return m_MobileIdIndex;
    }

    /*!
        \fn int DeviceNameIdIndex()

        \brief Get the index of the fieldname DeviceNameId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getDeviceNameIdIndex() const
    {
        return m_DeviceNameIdIndex;
    }

    /*!
        \fn int SerialNumberIndex()

        \brief Get the index of the fieldname SerialNumber form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getSerialNumberIndex() const
    {
        return m_SerialNumberIndex;
    }

    /*!
        \fn int NumberIndex()

        \brief Get the index of the fieldname Number form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getNumberIndex() const
    {
        return m_NumberIndex;
    }

    /*!
        \fn int PinIndex()

        \brief Get the index of the fieldname Pin form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getPinIndex() const
    {
        return m_PinIndex;
    }

    /*!
        \fn int CardNumberIndex()

        \brief Get the index of the fieldname CardNumber form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getCardNumberIndex() const
    {
        return m_CardNumberIndex;
    }

    /*!
       \fn int ActiveIndex()

       \brief Get the index of the fieldname Active form the database

       Returns the value of the index
    */
    JMBDEMODELS_EXPORT int getActiveIndex() const
    {
        return m_ActiveIndex;
    }

    /*!
       \fn int ReplaceIndex()

       \brief Get the index of the fieldname Replace form the database

       Returns the value of the index
    */
    JMBDEMODELS_EXPORT int getReplaceIndex() const
    {
        return m_ReplaceIndex;
    }

    /*!
       \fn int DeviceTypeIdIndex()

       \brief Get the index of the fieldname DeviceTypeId form the database

       Returns the value of the index
    */
    JMBDEMODELS_EXPORT int getDeviceTypeIdIndex() const
    {
        return m_DeviceTypeIdIndex;
    }

    /*!
       \fn int EmployeeIdIndex()

       \brief Get the index of the fieldname EmployeeId form the database

       Returns the value of the index
    */
    JMBDEMODELS_EXPORT int getEmployeeIdIndex() const
    {
        return m_EmployeeIdIndex;
    }

    /*!
       \fn int PlaceIdIndex()

       \brief Get the index of the fieldname PlaceId form the database

       Returns the value of the index
    */
    JMBDEMODELS_EXPORT int getPlaceIdIndex() const
    {
        return m_PlaceIdIndex;
    }

    /*!
       \fn int DepartmentIdIndex()

       \brief Get the index of the fieldname DepartmentId form the database

       Returns the value of the index
    */
    JMBDEMODELS_EXPORT int getDepartmentIdIndex() const
    {
        return m_DepartmentIdIndex;
    }

    /*!
       \fn int ManufacturerIdIndex()

       \brief Get the index of the fieldname ManufacturerId form the database

       Returns the value of the index
    */
    JMBDEMODELS_EXPORT int getManufacturerIdIndex() const
    {
        return m_ManufacturerIdIndex;
    }

    /*!
       \fn int InventoryIdIndex()

       \brief Get the index of the fieldname InventoryId form the database

       Returns the value of the index
    */
    JMBDEMODELS_EXPORT int getInventoryIdIndex() const
    {
        return m_InventoryIdIndex;
    }

    /*!
        \var int m_LastUpdateIndex
        \brief The value of the LastUpdateIndex
    */
    JMBDEMODELS_EXPORT int getLastUpdateIndex() const
    {
        return m_LastUpdateIndex;
    }

private:
    /*!
        \brief The Tablename in the database \e is const
     */
    const QString m_tableName = QLatin1String("mobile");

    /*!
     * @ brief m_db
     */
    QSqlDatabase m_db = {};

    /*!
        \brief holds an initialised pointer to the Relationmodel
        \sa QSqlRelationalTableModel
     */
    QSqlRelationalTableModel* m_model { nullptr };

    /*!
       \brief holds an initialised pointer to the ItemSelectioModel
       \sa QItemSelectionModel
    */
    QItemSelectionModel* m_selectionModel { nullptr };

    /*!
     * @brief DataContext
     */
    Model::DataContext* m_dataContext = {};

    /*!
       \var int m_MobileIdIndex
       \brief The value of the MobileIdIndex
    */
    int m_MobileIdIndex { 0 };

    /*!
       \var int m_DeviceNameIdIndex
       \brief The value of the DeviceNameIdIndex
    */
    int m_DeviceNameIdIndex { 0 };

    /*!
         \var int m_SerialNumberIndex
         \brief The value of the SerialNumberIndex
      */
    int m_SerialNumberIndex { 0 };

    /*!
       \var int m_NumberIndex
       \brief The value of the NumberIndex
    */
    int m_NumberIndex { 0 };

    /*!
       \var int m_PinIndex
       \brief The value of the PinIndex
    */
    int m_PinIndex { 0 };

    /*!
       \var int m_CardNumberIndex
       \brief The value of the CardNumberIndex
    */
    int m_CardNumberIndex { 0 };

    /*!
       \var int m_ActiveIndex
       \brief The value of the ActiveIndex
    */
    int m_ActiveIndex { 0 };

    /*!
       \var int m_ReplaceIndex
       \brief The value of the ReplaceIndex
    */
    int m_ReplaceIndex { 0 };

    /*!
       \var int m_DeviceTypeIdIndex
       \brief The value of the DeviceTypeIdIndex
    */
    int m_DeviceTypeIdIndex { 0 };

    /*!
       \var int m_EmployeeIdIndex
       \brief The value of the EmployeeIdIndex
    */
    int m_EmployeeIdIndex { 0 };

    /*!
       \var int m_PlaceIdIndex
       \brief The value of the PlaceIdIndex
    */
    int m_PlaceIdIndex { 0 };

    /*!
       \var int m_DepartmentIdIndex
       \brief The value of the DepartmentIdIndex
    */
    int m_DepartmentIdIndex { 0 };

    /*!
       \var int m_ManufacturerIdIndex
       \brief The value of the ManufacturerIdIndex
    */
    int m_ManufacturerIdIndex { 0 };

    /*!
       \var int m_InventoryIdIndex
       \brief The value of the InventoryIdIndex
    */
    int m_InventoryIdIndex { 0 };

    /*!
       \var int m_LastUpdateIndex
       \brief The value of the LastUpdateIndex
    */
    int m_LastUpdateIndex { 0 };
};
} // namespace Model
