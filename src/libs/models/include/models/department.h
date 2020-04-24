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

#include <QStandardPaths>
#include <QtSql>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>

#include "commondata.h"
#include "jmbdemodels-version.h"
#include "jmbdemodels_export.h"
#include "loggingcategory.h"

namespace Model {
/*!
\class Department
\brief The Department class
\details In this is handlet all Departments in the Company
\author Jürgen Mülbert
\since 0.4
\version 0.4.25
\date 03.08.2019
\copyright EUPL V1.2
*/
class Department : public CommonData {
  Q_OBJECT

public:
  /*!
      \fn explicit Department(QObject *parent = nullptr)
      \brief The Constructor for Department
   */
  explicit JMBDEMODELS_EXPORT Department(QObject *parent = nullptr);

  /*!
      \fn  ~Department() override;

      \brief Destructor for Department
   */
  JMBDEMODELS_EXPORT ~Department() {}

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
  virtual JMBDEMODELS_EXPORT QSqlRelationalTableModel *
  initializeRelationalModel() final;

  /*!
      \fn virtual QSqlRelationalTableModel *initializeInputDataModel() final
      \brief Initialize the InputDataModel

      Returns The QSqlRelationalTableModel
   */
  virtual JMBDEMODELS_EXPORT QSqlRelationalTableModel *
  initializeInputDataModel() final;

  /*!
      \fn virtual QSqlTableModel *initializeViewModel() final
      \brief Initialize the ViewModel

      Returns QSqlTableModel
   */
  virtual JMBDEMODELS_EXPORT QSqlTableModel *initializeViewModel() final;

  /*!
   * \fn virtual auto generateTableString(
                              const QString &header) -> QString final
      \brief generateTableString

      Returns a QString with the generated Table for Output
   */
  virtual JMBDEMODELS_EXPORT auto generateTableString(const QString &header)
      -> QString final;

  /*!
      \fn virtual auto generateFormularString(const QAbstractTableModel &model,
                                 const QString &header) -> QString final
      \brief generateFormularString

      Returns a QString with the generated Table for Output
   */
  virtual JMBDEMODELS_EXPORT auto generateFormularString(const QString &header)
      -> QString final;

  // Getter
  /*!
      \fn int DepartmentIdIndex()

      \brief Get the index of the fieldname DepartmentId form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int DepartmentIdIndex() const {
    return m_DepartmentIdIndex;
  }

  /*!
      \fn  int NameIndex()

      \brief Get the index of the fieldname Name form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int NameIndex() const { return m_NameIndex; }

  /*!
      \fn int PriorityIndex()

      \brief Get the index of the fieldname Priority form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int PriorityIndex() const { return m_PriorityIndex; }

  /*!
      \fn int PrinterIdIndex()

      \brief Get the index of the fieldname PrinterId form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int PrinterIdIndex() const { return m_PrinterIdIndex; }

  /*!
      \fn  int LastUpdateIndex()

      \brief Get the index of the fieldname LastUpdate form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int FaxIdIndex() const { return m_FaxIdIndex; }

  /*!
      \fn  int LastUpdateIndex()

      \brief Get the index of the fieldname LastUpdate form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int LastUpdateIndex() const { return m_LastUpdateIndex; }

private:
  /*!
      \brief The Tablename in the database \e is const
   */
  const QString m_tableName = QLatin1String("department");

  /*!
      \var  int m_DepartmentIdIndex
      \brief The value of the DepartmentIdIndex
  */
  int m_DepartmentIdIndex{0};

  /*!
     \var int m_NameIndex
     \brief The value of the NameIndex
 */
  int m_NameIndex{0};

  /*!
     \var  int m_PriorityIndex
     \brief The value of the PriorityIndex
 */
  int m_PriorityIndex{0};

  /*!
     \var int m_PrinterIdIndex
     \brief The value of the PrinterIdIndex
 */
  int m_PrinterIdIndex{0};

  /*!
      \var int m_FaxIdIndex
      \brief The value of the FaxIdIndex
  */
  int m_FaxIdIndex{0};

  /*!
     \var int m_LastUpdateIndex
     \brief The value of the LastUpdateIndex
 */
  int m_LastUpdateIndex{0};
};
} // namespace Model
