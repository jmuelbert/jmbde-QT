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
  \class Department
  \brief The Department class
  \details In this is handlet all Departments in the Company
  \author Jürgen Mülbert
  \since 0.4
  \version 0.7
  \date 25.12.2021
  \copyright GPL-3.0-or-later
    */
class Department : public CommonData
{
  Q_OBJECT

public:
  /*!
      \fn explicit Department()
      \brief The Constructor for Department
   */
  explicit JMBDEMODELS_EXPORT Department();

  /*!
      \fn  ~Department() override;

      \brief Destructor for Department
   */
  JMBDEMODELS_EXPORT ~Department() {}

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
  virtual JMBDEMODELS_EXPORT auto initializeRelationalModel() -> QSqlRelationalTableModel * final;

  /*!
      \fn virtual auto initializeInputDataModel() -> QSqlRelationalTableModel*
     fina \brief Initialize the InputDataModel

       \return The QSqlRelationalTableModel
   */
  virtual JMBDEMODELS_EXPORT auto initializeInputDataModel() -> QSqlRelationalTableModel * final;

  /*!
      \fn virtual auto initializeViewModel() -> QSqlTableModel* final
      \brief Initialize the ViewModel

      \return QSqlTableModel
   */
  virtual JMBDEMODELS_EXPORT auto initializeViewModel() -> QSqlTableModel * final;

  /*!
      \fn virtual auto initializeListModel() -> QSqlTableModel* final
      \brief Initiallize the list Model for select one dataset
  */
  virtual JMBDEMODELS_EXPORT auto initializeListModel() -> QSqlTableModel * final;

  /*!
   * \fn virtual auto generateTableString(const QString& header) -> QString
   final \brief generateTableString

      \return a QString with the generated Table for Output
   */
  virtual JMBDEMODELS_EXPORT auto generateTableString(const QString &header) -> QString final;

  /*!
      \fn virtual auto generateFormularString(const QString& header) -> QString
     final \brief generateFormularString

      \return a QString with the generated Table for Output
   */
  virtual JMBDEMODELS_EXPORT auto generateFormularString(const QString &header) -> QString final;

  // Getter
  /*!
   * \brief getTableName
   * \return
   */
  JMBDEMODELS_EXPORT auto getTableName() const -> QString { return this->m_tableName; }
  /*!
      \fn auot getDB() const -> QSqlDatabase
   */
  JMBDEMODELS_EXPORT auto getDB() const -> QSqlDatabase { return this->m_db; }

  /*!
      \fn int getDepartmentIdIndex()

      \brief Get the index of the fieldname DepartmentId form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getDepartmentIdIndex() const { return m_DepartmentIdIndex; }

  /*!
      \fn  int getNameIndex()

      \brief Get the index of the fieldname Name form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getNameIndex() const { return m_NameIndex; }

  /*!
      \fn int getPriorityIndex()

      \brief Get the index of the fieldname Priority form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getPriorityIndex() const { return m_PriorityIndex; }

  /*!
      \fn int getPrinterIdIndex()

      \brief Get the index of the fieldname PrinterId form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getPrinterIdIndex() const { return m_PrinterIdIndex; }

  /*!
      \fn  int getFaxIdIndex()

      \brief Get the index of the fieldname LastUpdate form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getFaxIdIndex() const { return m_FaxIdIndex; }

  /*!
      \fn  int getLastUpdateIndex()

      \brief Get the index of the fieldname LastUpdate form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getLastUpdateIndex() const { return m_LastUpdateIndex; }

private:
  /*!
      \brief The Tablename in the database \e is const
   */
  const QString m_tableName = QLatin1String("department");

  /*!
   * @ brief m_db
   */
  QSqlDatabase m_db = {};

  /*!
   * @brief DataContext
   */
  Model::DataContext *m_dataContext = {};
  /*!
      \var  int m_DepartmentIdIndex
      \brief The value of the DepartmentIdIndex
  */
  int m_DepartmentIdIndex{ 0 };

  /*!
     \var int m_NameIndex
     \brief The value of the NameIndex
 */
  int m_NameIndex{ 0 };

  /*!
     \var  int m_PriorityIndex
     \brief The value of the PriorityIndex
 */
  int m_PriorityIndex{ 0 };

  /*!
     \var int m_PrinterIdIndex
     \brief The value of the PrinterIdIndex
 */
  int m_PrinterIdIndex{ 0 };

  /*!
      \var int m_FaxIdIndex
      \brief The value of the FaxIdIndex
  */
  int m_FaxIdIndex{ 0 };

  /*!
     \var int m_LastUpdateIndex
     \brief The value of the LastUpdateIndex
 */
  int m_LastUpdateIndex{ 0 };
};
}// namespace Model
