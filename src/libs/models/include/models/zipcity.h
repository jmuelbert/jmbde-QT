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
    \class ZipCity
    \brief The ZipCity class
    \details In this is handlet all ZipCity
    \author Jürgen Mülbert
    \since 0.4
    \version 0.4.25
    \date 03.08.2019
    \copyright EUPL V1.2
    */
class ZipCity : public CommonData {
public:
  /*!
      \fn ZipCity(QObject *parent = nullptr)

      \brief Constructor for the ZipCity
   */
  explicit JMBDEMODELS_EXPORT ZipCity(QObject *parent = nullptr);

  /*!
      \fn  ~ZipCity();

      \brief Destructor for ZipCity
   */
  JMBDEMODELS_EXPORT ~ZipCity() {}

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
                              const QString &header) -> QString fianl
      \brief generateTableString

      Returns a QString with the generated Table for Output
   */
  virtual JMBDEMODELS_EXPORT auto generateTableString(const QString &header)
      -> QString final;

  /*!
      \fn virtual auto generateFormularString(
                                 const QString &header) -> QString final
      \brief generateFormularString

      Returns a QString with the generated Table for Output
   */
  virtual auto generateFormularString(const QString &header) -> QString final;

  // Getter

  /*!
      \fn  int ZipCityIdIndex()

      \brief Get the index of the fieldname ZipCityId from the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int ZipCityIdIndex() const { return m_ZipCityIdIndex; }

  /*!
      \fn  int ZipCodeIdIndex()

      \brief Get the index of the fieldname ZipCodeId from the database

      Returns the value of the index
   */
  JMBDEMODELS_EXPORT int ZipCodeIdIndex() const { return m_ZipCodeIdIndex; }

  /*!
     \fn  int CityIdIndex()

     \brief Get the index of the fieldname CityId from the database

     Returns the value of the index
  */
  JMBDEMODELS_EXPORT int CityIdIndex() const { return m_CityIdIndex; }

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
  const QString m_tableName = QLatin1String("zip_city");

  /*!
      \var int m_ZipCityIdIndex
      \brief The value of the ZipCityIdIndex
   */
  int m_ZipCityIdIndex{0};

  /*!
      \var int m_ZipCodeIdIndex
      \brief The value of the ZipCodeIdIndex
   */
  int m_ZipCodeIdIndex{0};

  /*!
      \var int m_CityIdIndex
      \brief The value of the CityIdIndex
   */
  int m_CityIdIndex{0};

  /*!
      \var int m_LastUpdateIndex
      \brief The value of the LastUpdateIndex
  */
  int m_LastUpdateIndex{0};
};
} // namespace Model
