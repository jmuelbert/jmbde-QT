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
  \class Mobile
  \brief The Mobile is the class to handle the mobiles
  \sa CommonDataModel

  \author Jürgen Mülbert
  \since 0.4
  \version 0.7
  \date 25.12.2021
  \copyright GPL-3.0-or-later
  */
class Place : public CommonData {
  Q_OBJECT

public:
  /*!
     \fn explicit Place(QObject *parent = nullptr)
     \brief The Constructor for the Place
 */
  explicit JMBDEMODELS_EXPORT Place();

  /*!
      \fn ~Place()
      \brief The destructor for the Place
   */
  JMBDEMODELS_EXPORT ~Place() {}

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
      \fn int PlaceIdIndex()

      \brief Get the index of the fieldname PlaceId form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getPlaceIdIndex() const { return m_PlaceIdIndex; }

  /*!
      \fn int NameIndex()

      \brief Get the index of the fieldname Name form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getNameIndex() const { return m_NameIndex; }

  /*!
      \fn int RoomIndex()

      \brief Get the index of the fieldname Room form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getRoomIndex() const { return m_RoomIndex; }

  /*!
      \fn int DeskIndex()

      \brief Get the index of the fieldname Desk form the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int getDeskIndex() const { return m_DeskIndex; }

  /*!
      \var int m_LastUpdateIndex
      \brief The value of the LastUpdateIndex
  */
  JMBDEMODELS_EXPORT int getLastUpdateIndex() const {
    return m_LastUpdateIndex;
  }

private:
  /*!
      \brief The Tablename in the database \e is const
   */
  const QString m_tableName = QLatin1String("place");

  /*!
   * @ brief m_db
   */
  QSqlDatabase m_db = {};

  /*!
   * @brief DataContext
   */
  Model::DataContext *m_dataContext = {};

  /*!
     \var int m_PlaceIdIndex
     \brief The value of the PlaceIdIndex
  */
  int m_PlaceIdIndex{0};

  /*!
     \var int m_NameIndex
     \brief The value of the NameIndex
  */
  int m_NameIndex{0};

  /*!
     \var int m_RoomIndex
     \brief The value of the RoomIndex
  */
  int m_RoomIndex{0};

  /*!
    \var int m_DeskIndex
    \brief The value of the DeskIndex
 */
  int m_DeskIndex{0};

  /*!
     \var int m_LastUpdateIndex
     \brief The value of the LastUpdateIndex
  */
  int m_LastUpdateIndex{0};
};
} // namespace Model
