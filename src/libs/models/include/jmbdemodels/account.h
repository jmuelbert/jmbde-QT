/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert
 * <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include <QDebug>
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
    \class Account
    \brief The Account class
    \details In this is handlet all Accounts from the Employees
    \author Jürgen Mülbert
    \since 0.4
    \version 0.7
    \date 25.12.2021
    \copyright GPL-3.0-or-later
    */

class Account : public CommonData {
  Q_OBJECT

public:
  /*!
      \fn Account()

      \brief Constructor for the Account
   */
  explicit JMBDEMODELS_EXPORT Account();
  /*!
      \fn  ~Account();

      \brief Destructor for  Account
   */
  JMBDEMODELS_EXPORT ~Account() {}

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
      \fn int getAccountIdIndex() const

      \brief Get the index of the fieldname AccountId from the database

      \return the value of the index
   */
  JMBDEMODELS_EXPORT auto getAccountIdIndex() const -> int {
    return m_AccountIdIndex;
  }

  /*!
      \fn int getUserNameIndex() const

      \brief Get the index of the fieldname UserName form the database

      \return the value of the index
   */
  JMBDEMODELS_EXPORT auto getUserNameIndex() const -> int {
    return m_UserNameIndex;
  }

  /*!
      \fn int getPasswordIndex() const

      \brief Get the index of the fieldname Password form the database

      \return the value of the index
   */
  JMBDEMODELS_EXPORT auto getPasswordIndex() const -> int {
    return m_PasswordIndex;
  }

  /*!
      \fn int getSystemDataIndex()

      \brief Get the index of the fieldname SystemData form the database

      \return the value of the index
   */
  JMBDEMODELS_EXPORT auto getSystemDataIndex() const -> int {
    return m_SystemDataIdIndex;
  }

  /*!
      \fn  int getLastUpdateIndex()

      \brief Get the index of the fieldname LastUpdate form the database

      \return the value of the index
   */
  JMBDEMODELS_EXPORT auto getLastUpdateIndex() const -> int {
    return m_LastUpdateIndex;
  }

private:
  /*!
      \brief The Tablename in the database \e is const
   */
  const QString m_tableName = QLatin1String("account");

  /*!
   * @ brief m_db
   */
  QSqlDatabase m_db = {};

  /*!
   * @brief DataContext
   */
  Model::DataContext *m_dataContext = {};

  /*!
      \var int m_AccountIdIndex
      \brief The value of the AccountIdIndex
   */
  int m_AccountIdIndex{0};

  /*!
      \var int m_UserNameIndex
      \brief The value of the UserNameIndex
  */
  int m_UserNameIndex{0};

  /*!
       \var int m_PasswordIndex;
       \brief The value of the PasswordIndex
   */
  int m_PasswordIndex{0};

  /*!
      \var int m_SystemDataIdIndex
      \brief The value of the SystemDataIdIndex
  */
  int m_SystemDataIdIndex{0};

  /*!
      \var int m_LastUpdateIndex
      \brief The value of the LastUpdateIndex
  */
  int m_LastUpdateIndex{0};
};
} // namespace Model
