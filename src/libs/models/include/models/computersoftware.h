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

#include "jmbdemodels-version.h"
#include "jmbdemodels_export.h"
#include "loggingcategory.h"
#include "models/commondata.h"
#include "models/idatamodel.h"



namespace Model
{
/*!
    \class ComputerSoftware
    \brief The ComputerSoftware class
    \details In this is handle the installed software. Is a many to many
   relation. \author Jürgen Mülbert \since 0.4 \version 0.4.25 \date 03.08.2019
    \copyright EUPL V1.2
    */
class ComputerSoftware : public CommonData
{
    Q_OBJECT

public:
    /*!
        \fn ComputerSoftware(QObject *parent = nullptr)

        \brief Constructor for the ComputerSoftware
     */
    explicit JMBDEMODELS_EXPORT ComputerSoftware(QObject *parent = nullptr);

    /*!
        \fn  ~ComputerSoftware() override;

        \brief Destructor for  ComputerSoftware
     */
    JMBDEMODELS_EXPORT ~ComputerSoftware();

    // implement the virtuals

    /*!
       \fn virtual void setIndexes()
       \brief Set the fieldindexes from the datafieldnames of the db.
    */
    virtual JMBDEMODELS_EXPORT void setIndexes();

    /*!
        \fn virtual QSqlRelationalTableModel *initializeRelationalModel()
        \brief set the QSqlRelationalTableModel for the DataModel
        Returns The QSqlRelationalTableModel
     */
    virtual JMBDEMODELS_EXPORT QSqlRelationalTableModel *initializeRelationalModel();

    /*!
        \fn virtual QSqlRelationalTableModel *initializeInputDataModel()
        \brief Initialize the InputDataModel

        Returns The QSqlRelationalTableModel
     */
    virtual JMBDEMODELS_EXPORT QSqlRelationalTableModel *initializeInputDataModel();

    /*!
        \fn virtual QSqlTableModel *initializeViewModel()
        \brief Initialize the ViewModel

        Returns QSqlTableModel
      */
    virtual JMBDEMODELS_EXPORT QSqlTableModel *initializeViewModel();

    /*!
     * \fn virtual auto generateTableString(
                                const QString &header) -> QString
        \brief generateTableString

        Returns a QString with the generated Table for Output
     */
    virtual JMBDEMODELS_EXPORT auto generateTableString(const QString &header) -> QString;

    /*!
        \fn virtual auto generateFormularString(
                                   const QString &header) -> QString
        \brief generateFormularString

        Returns a QString with the generated Table for Output
     */
    virtual JMBDEMODELS_EXPORT auto generateFormularString(const QString &header) -> QString;

    // Getter
    /*!
        \fn int ComputerSoftwareIdIndex()

         \brief Get the index of the fieldname ComputerSoftwareId from the
       database

         Returns the value of the index
     */
    JMBDEMODELS_EXPORT int ComputerSoftwareIdIndex() const
    {
        return m_ComputerSoftwareIdIndex;
    }

    /*!
        \fn int ComputerIdIndex()

        \brief Get the index of the fieldname ComputerId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int ComputerIdIndex() const
    {
        return m_ComputerIdIndex;
    }

    /*!
        \fn int SoftwareIdIndex()

        \brief Get the index of the fieldname SoftwareId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int SoftwareIdIndex() const
    {
        return m_SoftwareIdIndex;
    }

    /*!
        \fn  int LastUpdateIndex()

        \brief Get the index of the fieldname LastUpdate form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int LastUpdateIndex() const
    {
        return m_LastUpdateIndex;
    }

private:
    /*!
          \brief The Tablename in the database \e is const
       */
    const QString m_tableName = QLatin1String("computer_software");

    /*!
        \var int m_ComputerSoftwareIdIndex
        \brief The value of the ComputerSoftwareIdIndex
    */
    int m_ComputerSoftwareIdIndex {0};

    /*!
        \var int m_ComputerIdIndex
        \brief The value of the ComputerIdIndex
    */
    int m_ComputerIdIndex {0};

    /*!
        \var int m_SoftwareIdIndex
        \brief The value of the SoftwareIdIndex
    */
    int m_SoftwareIdIndex {0};

    /*!
        \var int m_LastUpdateIndex
        \brief The value of the LastUpdateIndex
    */
    int m_LastUpdateIndex {0};
};
} // namespace Model
