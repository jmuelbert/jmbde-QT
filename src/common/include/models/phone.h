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
    \class Phone
    \brief The Phone is the class to handle the phones
    \sa CommonDataModel

    \author Jürgen Mülbert
    \since 0.4
    \version 0.4.25
    \date 03.08.2019
    \copyright EUPL V1.2
 */

namespace Model {
class JMBDE_COMMON_EXPORT Phone : public CommonData {
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
    Q_LOGGING_CATEGORY(phoneLC, "jmbde.models.phone")

public:
    /*!
        \fn explicit Phone(QObject *parent = nullptr)
        \brief The Constructor for the Phone
    */
    explicit Phone(QObject *parent = nullptr);

    /*!
        \fn ~Phone()
        \brief The destructor for the Phone
     */
    ~Phone();

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
     * \fn virtual QSqlTableModel *initializeViewModel()
     * \brief Initialize the ViewModel
     *
     * Returns QSqlTableModel
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

    /*!
        \fn int PhoneIdIndex()

        \brief Get the index of the fieldname PhoneId form the database

        Returns the value of the index
     */
    int PhoneIdIndex() const { return m_PhoneIdIndex; }

    /*!
        \fn int DeviceNameIdIndex()

        \brief Get the index of the fieldname DeviceNameId form the database

        Returns the value of the index
     */  
    int DeviceNameIdIndex() const { return m_DeviceNameIdIndex; }

    /*!
        \fn int SerialNumberIndex()

        \brief Get the index of the fieldname SerialNumber form the database

        Returns the value of the index
     */ 
    int SerialNumberIndex() const { return m_SerialNumberIndex; }
   
     /*!
        \fn int NumberIndex()

        \brief Get the index of the fieldname Number form the database

        Returns the value of the index
     */     
    int NumberIndex() const { return m_NumberIndex; }

    /*!
        \fn int PinIndex()

        \brief Get the index of the fieldname Pin form the database

        Returns the value of the index
     */     
    int PinIndex() const { return m_PinIndex; }
    
     /*!
        \fn int ActiveIndex()

        \brief Get the index of the fieldname Active form the database

        Returns the value of the index
     */     
    int ActiveIndex() const { return m_ActiveIndex; }

     /*!
        \fn int ReplaceIndex()

        \brief Get the index of the fieldname Replace form the database

        Returns the value of the index
     */
    int ReplaceIndex() const { return m_ReplaceIndex; }

     /*!
        \fn int DeviceTypeIdIndex()

        \brief Get the index of the fieldname DeviceTypeId form the database

        Returns the value of the index
     */       
    int DeviceTypeIdIndex() const { return m_DeviceTypeIdIndex; }

     /*!
        \fn int EmployeeIdIndex()

        \brief Get the index of the fieldname EmployeeId form the database

        Returns the value of the index
     */
    int EmployeeIdIndex() const { return m_EmployeeIdIndex; }

     /*!
        \fn int PlaceIdIndex()

        \brief Get the index of the fieldname PlaceId form the database

        Returns the value of the index
     */
    int PlaceIdIndex() const { return m_PlaceIdIndex; }

    /*!
        \fn int DepartmentIdIndex()

        \brief Get the index of the fieldname DepartmentId form the database

        Returns the value of the index
     */
    int DepartmentIdIndex() const { return m_DepartmentIdIndex; }

     /*!
        \fn int ManufacturerIdIndex()

        \brief Get the index of the fieldname ManufacturerId form the database

        Returns the value of the index
     */
    int ManufacturerIdIndex() const { return m_ManufacturerIdIndex; }
    
     /*!
        \fn int InventoryIdIndex()

        \brief Get the index of the fieldname InventoryId form the database

        Returns the value of the index
     */    
    int InventoryIdIndex() const { return m_InventoryIdIndex; }

    /*!
        \var int m_LastUpdateIndex
        \brief The value of the LastUpdateIndex
    */
    int LastUpdateIndex() const { return m_LastUpdateIndex; }

private:
    /**
     * @brief tableName - the name of the database table
     * @
     */
    const QString m_tableName = QLatin1String("phone");

     /*!
        \var int m_PhoneIdIndex
        \brief The value of the PhoneIdIndex
     */ 
    int m_PhoneIdIndex{0};

     /*!
        \var int m_DeviceNameIdIndex
        \brief The value of the DeviceNameIdIndex
     */     
    int m_DeviceNameIdIndex{0};

   /*!
        \var int m_SerialNumberIndex
        \brief The value of the SerialNumberIndex
     */  
    int m_SerialNumberIndex{0};

     /*!
        \var int m_NumberIndex
        \brief The value of the NumberIndex
     */  
    int m_NumberIndex{0};
    
     /*!
        \var int m_PinIndex
        \brief The value of the PinIndex
     */       
    int m_PinIndex{0};

     /*!
        \var int m_ActiveIndex
        \brief The value of the ActiveIndex
     */ 
    int m_ActiveIndex{0};

     /*!
        \var int m_ReplaceIndex
        \brief The value of the ReplaceIndex
     */  
    int m_ReplaceIndex{0};

     /*!
        \var int m_DeviceTypeIdIndex
        \brief The value of the DeviceTypeIdIndex
     */
    int m_DeviceTypeIdIndex{0};

     /*!
        \var int m_EmployeeIdIndex
        \brief The value of the EmployeeIdIndex
     */
    int m_EmployeeIdIndex{0};

     /*!
        \var int m_PlaceIdIndex
        \brief The value of the PlaceIdIndex
     */
    int m_PlaceIdIndex{0};
    
     /*!
        \var int m_DepartmentIdIndex
        \brief The value of the DepartmentIdIndex
     */    
    int m_DepartmentIdIndex{0};
    
     /*!
        \var int m_ManufacturerIdIndex
        \brief The value of the ManufacturerIdIndex
     */
    int m_ManufacturerIdIndex{0};

     /*!
        \var int m_InventoryIdIndex
        \brief The value of the InventoryIdIndex
     */    
    int m_InventoryIdIndex{0};

     /*!
        \var int m_LastUpdateIndex
        \brief The value of the LastUpdateIndex
     */
    int m_LastUpdateIndex{0};
};
} // namespace Model
