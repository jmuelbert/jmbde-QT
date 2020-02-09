/*
   jmbde a BDE Tool for companies
   Copyright (C) 2013-2019  Jürgen Mülbert

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

/*!
    \class Mobile
    \brief The Mobile is the class to handle the mobiles
    \sa CommonDataModel

    \author Jürgen Mülbert
    \since 0.4
    \version 0.4.25
    \date 03.08.2019
    \copyright EUPL V1.2
 */

namespace Model
{
class JMBDEMODELS_EXPORT Processor : public CommonData
{
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

public:
    /*!
        \fn explicit Processor(QObject *parent = nullptr)
        \brief The Constructor for the Processor
    */
    explicit Processor(QObject *parent = nullptr);

    /*!
        \fn ~Processor
        \brief The destructor for the Processor
     */
    ~Processor();

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
      \fn virtual QSqlTableModel *initializeViewModel()
      \brief Initialize the ViewModel

      Returns QSqlTableModel
     */
    virtual QSqlTableModel *initializeViewModel();

    /*!
        \fn virtual QString generateTableString(QAbstractTableModel *model,
                                const QString &header)
        \brief generateTableString

        Returns a QString with the generated Table for Output
     */
    virtual QString generateTableString(QAbstractTableModel *model, QString header);

    /*!
         \fn virtual QString generateFormularString(QAbstractTableModel *model,
                                    const QString &header)
         \brief generateFormularString

         Returns a QString with the generated Table for Output
      */
    virtual QString generateFormularString(QAbstractTableModel *model, QString header);

    // Getter

    /*!
        \fn int ProcessorIdIndex()

        \brief Get the index of the fieldname ProcessorId form the database

        Returns the value of the index
     */
    int ProcessorIdIndex() const
    {
        return m_ProcessorIdIndex;
    }

    /*!
       \fn int NameIndex()

       \brief Get the index of the fieldname Name form the database

       Returns the value of the index
    */
    int NameIndex() const
    {
        return m_NameIndex;
    }

    /*!
       \fn int ClockRateIndex()

       \brief Get the index of the fieldname ClockRate form the database

       Returns the value of the index
    */
    int ClockRateIndex() const
    {
        return m_ClockRateIndex;
    }

    /*!
       \fn int CoresIndex()

       \brief Get the index of the fieldname Cores form the database

       Returns the value of the index
    */
    int CoresIndex() const
    {
        return m_CoresIndex;
    }

    /*!
        \var int m_LastUpdateIndex
        \brief The value of the LastUpdateIndex
    */
    int LastUpdateIndex() const
    {
        return m_LastUpdateIndex;
    }

private:
    /*!
        \brief The Tablename in the database \e is const
     */
    const QString m_tableName = QLatin1String("processor");

    /*!
       \var int m_ProcessorIdIndex
       \brief The value of the ProcessorIdIndex
    */
    int m_ProcessorIdIndex {0};

    /*!
       \var int m_NameIndex
       \brief The value of the Name
    */
    int m_NameIndex {0};

    /*!
       \var int m_ClockRateIndex
       \brief The value of the ClockRate ndex
    */
    int m_ClockRateIndex {0};

    /*!
       \var int m_CoresIndex
       \brief The value of the CoresIndex
    */
    int m_CoresIndex {0};

    /*!
       \var int m_LastUpdateIndex
       \brief The value of the LastUpdateIndex
    */
    int m_LastUpdateIndex {0};
};
} // namespace Model
