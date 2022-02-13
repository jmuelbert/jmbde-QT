/*
 *  SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert
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
    \class Fax
    \brief The Fax class
    \details In this is handle all Fax
    \author Jürgen Mülbert
    \since 0.4
    \version 0.7
    \date 25.12.2021
    \copyright GPL-3.0-or-later
    */
class Fax : public CommonData {
  Q_OBJECT

public:
  /*!
      \fn explicit Fax()
      \brief The Constructor for the Fax
  */
  explicit JMBDEMODELS_EXPORT Fax();

  /*!
      \fn  ~Fax() override;

      \brief Destructor for Fax
   */
  JMBDEMODELS_EXPORT ~Fax() {}

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
      \fn int FaxIdIndex()

      \brief Get the index of the fieldname FaxId form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getFaxIdIndex() const { return m_FaxIdIndex; }

  /*!
      \fn int DeviceNameIdIndex()

      \brief Get the index of the fieldname DeviceNameId form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getDeviceNameIdIndex() const {
    return m_DeviceNameIdIndex;
  }

  /*!
      \fn int SerialNumberIndex()

      \brief Get the index of the fieldname SerialNumberIndex form the
     database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getSerialNumberIndex() const {
    return m_SerialNumberIndex;
  }

  /*!
      \fn int NumberIndex()

      \brief Get the index of the fieldname NumberIndex form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getNumberIndex() const { return m_NumberIndex; }

  /*!
      \fn int PinIndex()

      \brief Get the index of the fieldname PinIndex form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getPinIndex() const { return m_PinIndex; }

  /*!
     \fn int ActiveIndex()

     \brief Get the index of the fieldname ActiveIndex form the database

     Returns the value of the index
  */
  JMBDEMODELS_EXPORT int getActiveIndex() const { return m_ActiveIndex; }

  /*!
     \fn int ReplaceIndex()

     \brief Get the index of the fieldname ReplaceIndex form the database

     Returns the value of the index
  */
  JMBDEMODELS_EXPORT int getReplaceIndex() const { return m_ReplaceIndex; }

  /*!
      \fn int DeviceTypeIdIndex()

      \brief Get the index of the fieldname DeviceTypeIdIndex form the
     database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getDeviceTypeIdIndex() const {
    return m_DeviceTypeIdIndex;
  }

  /*!
      \fn int EmployeeIdIndex()

      \brief Get the index of the fieldname EmployeeIdIndex form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getEmployeeIdIndex() const {
    return m_EmployeeIdIndex;
  }

  /*!
      \fn int PlaceIdIndex()

      \brief Get the index of the fieldname PlaceIdIndex form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getPlaceIdIndex() const { return m_PlaceIdIndex; }

  /*!
      \fn int DepartmentIdIndex()

      \brief Get the index of the fieldname DepartmentIdIndex form the
     database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getDepartmentIdIndex() const {
    return m_DepartmentIdIndex;
  }

  /*!
      \fn int ManufacturerIdIndex()

      \brief Get the index of the fieldname ManufacturerIdIndex form the
     database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getManufacturerIdIndex() const {
    return m_ManufacturerIdIndex;
  }

  /*!
      \fn int InventoryIdIndex()

      \brief Get the index of the fieldname InventoryIdIndex form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getInventoryIdIndex() const {
    return m_InventoryIdIndex;
  }

  /*!
      \fn  int LastUpdateIndex()

      \brief Get the index of the fieldname LastUpdate form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getLastUpdateIndex() const {
    return m_LastUpdateIndex;
  }

private:
  /*!
      \brief The Tablename in the database \e is const
   */
  const QString m_tableName = QLatin1String("fax");

  /*!
   * @ brief m_db
   */
  QSqlDatabase m_db = {};

  /*!
   * @brief DataContext
   */
  Model::DataContext *m_dataContext = {};

  /*!
     \var int m_FaxIdIndex
     \brief The value of the FaxIdIndex
  */
  int m_FaxIdIndex{0};

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
