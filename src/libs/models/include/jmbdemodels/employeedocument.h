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
    \class EmployeeDocument
    \brief The EmployeeDocument class
    \details In this is handle all EmployeeDocument
    \author Jürgen Mülbert
    \since 0.4
    \version 0.7
    \date 25.12.2021
    \copyright GPL-3.0-or-later
    */
class EmployeeDocument : public CommonData {
  Q_OBJECT

public:
  /*!
      \fn explicit EmployeeDocument()
      \brief The Constructor for the EmployeeDocument
  */
  explicit JMBDEMODELS_EXPORT EmployeeDocument();

  /*!
      \fn  ~EmployeeDocument() override;

      \brief Destructor for EmployeeDocument
   */
  JMBDEMODELS_EXPORT ~EmployeeDocument() {}

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
      \fn int EmployeeDocumentIdIndex()

      \brief Get the index of the fieldname EmployeeDocumentId form the
     database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getEmployeeDocumentIdIndex() const {
    return m_EmployeeDocumentIdIndex;
  }

  /*!
      \fn int EmployeeIdIndex()

      \brief Get the index of the fieldname EmployeeId form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getEmployeeIdIndex() const {
    return m_EmployeeIdIndex;
  }

  /*!
      \fn int DocumentIdIndex()

      \brief Get the index of the fieldname DocumentId form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getDocumentIdIndex() const {
    return m_DocumentIdIndex;
  }

  /*!
      \fn int LastUpdateIndex()

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
  const QString m_tableName = QLatin1String("employee_document");

  /*!
   * @ brief m_db
   */
  QSqlDatabase m_db = {};

  /*!
   * @brief DataContext
   */
  Model::DataContext *m_dataContext = {};

  /*!
     \var int m_EmployeeDocumentIdIndex
     \brief The value of the EmployeeDocumentIdIndex
  */
  int m_EmployeeDocumentIdIndex{0};

  /*!
     \var int m_EmployeeIdIndex
     \brief The value of the EmployeeIdIndex
  */
  int m_EmployeeIdIndex{0};

  /*!
     \var int m_DocumentIdIndex
     \brief The value of the DocumentIdIndex
  */
  int m_DocumentIdIndex{0};

  /*!
      \var int m_LastUpdateIndex
      \brief The value of the LastUpdateIndex
  */
  int m_LastUpdateIndex{0};
};
} // namespace Model
