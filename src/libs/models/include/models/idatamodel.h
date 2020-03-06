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

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>



namespace Model
{
/*!
    \class IDataModel
    \brief The IDataModel class
    \details In this is the Interface for all Model Classes
    \author Jürgen Mülbert
    \since 0.4
    \version 0.4.25
    \date 03.08.2019
    \copyright GPL V3
    */
class IDataModel
{
public:
    /*!
        \fn explicit IDataModel()
        \brief The Constructor is empty
    */
    explicit IDataModel()
    {
    }

    /*!
        \fn ~IDataModel()
        \brief the Destructor is empty
    */
    virtual ~IDataModel() {};

    // definition of virtuals

    /*!
        \fn virtual void setIndexes()
        \brief Set the fieldindexes from the datafieldnames of the db.
     */
    virtual void setIndexes() = 0;

    /*!
        \fn virtual QSqlRelationalTableModel *initializeRelationalModel()
        \brief set the QSqlRelationalTableModel for the DataModel

        \return The QSqlRelationalTableModel
     */
    virtual QSqlRelationalTableModel *initializeRelationalModel() = 0;

    /*!
          \fn virtual QSqlRelationalTableModel *initializeInputDataModel()
          \brief Initialize the InputDataModel

          \return The QSqlRelationalTableModel
       */
    virtual QSqlRelationalTableModel *initializeInputDataModel() = 0;

    /*!
         \fn virtual QSqlTableModel *initializeViewModel()
         \brief Initialize the ViewModel

         \return QSqlTableModel
      */
    virtual QSqlTableModel *initializeViewModel() = 0;

    /*!
     * \fn virtual auto generateTableString(
                                const QString &header) -> QString
        \brief generateTableString
        \param header The String for the table header

        \return a QString with the generated Table for Output
     */
    virtual auto generateTableString( const QString &header) -> QString = 0;

    /*!
         \fn virtual auto generateFormularString(
                                    const QString &header) -> QString
         \brief generateFormularString
         \param header The String for the table header

         \return a QString with the generated Table for Output
      */
    virtual auto generateFormularString(const QString &header) -> QString = 0;
};
} // namespace Model
