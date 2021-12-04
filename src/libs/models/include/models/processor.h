/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
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
#include "jmbdemodels-version.h"
#include "jmbdemodels_export.h"

Q_DECLARE_LOGGING_CATEGORY(m_ProcessorLog)

namespace Model
{
/*!
    \class Processor
    \brief The Processor is the class to handle the processors
    \sa CommonDataModel

  \author Jürgen Mülbert
    \since 0.4
    \version 0.6
    \date 23.01.2021
    \copyright GPL-3.0-or-later
    */
class Processor : public CommonData
{
public:
    /*!
        \fn explicit Processor()
        \brief The Constructor for the Processor
    */
    explicit JMBDEMODELS_EXPORT Processor();

    /*!
        \fn ~Processor
        \brief The destructor for the Processor
     */
    JMBDEMODELS_EXPORT ~Processor()
    {
    }

    // implement the virtuals

    /*!
        \fn virtual void setIndexes() final
        \brief Set the fieldindexes from the datafieldnames of the db.
     */
    virtual JMBDEMODELS_EXPORT void setIndexes() final;

    /*!
        \fn virtual QSqlRelationalTableModel *initializeRelationalModel()
        \brief set the QSqlRelationalTableModel for the DataModel
        Returns The QSqlRelationalTableModel
     */
    virtual JMBDEMODELS_EXPORT QSqlRelationalTableModel *initializeRelationalModel() final;

    /*!
            \fn virtual QSqlRelationalTableModel *initializeInputDataModel()
            \brief Initialize the InputDataModel

            Returns The QSqlRelationalTableModel
        */
    virtual QSqlRelationalTableModel *initializeInputDataModel();

    /*!
      \fn virtual QSqlTableModel *initializeViewModel() final
      \brief Initialize the ViewModel

      Returns QSqlTableModel
     */
    virtual JMBDEMODELS_EXPORT QSqlTableModel *initializeViewModel() final;

    /*!
        \fn QSqlTableModel *initializeListModel();
        \brief Initiallize the list Model for select one dataset
    */
    virtual JMBDEMODELS_EXPORT QSqlTableModel *initializeListModel() final;

    /*!
        \fn virtual auto generateTableString(
                                const QString &header) -> QString
        \brief generateTableString

        Returns a QString with the generated Table for Output
     */
    virtual JMBDEMODELS_EXPORT auto generateTableString(const QString &header) -> QString final;

    /*!
         \fn virtual auto generateFormularString(const QAbstractTableModel &model,
                                    const QString &header) -> QString final
         \brief generateFormularString

         Returns a QString with the generated Table for Output
      */
    virtual JMBDEMODELS_EXPORT auto generateFormularString(const QString &header) -> QString final;

    // Getter
    JMBDEMODELS_EXPORT QString getTableName() const
    {
        return this->m_tableName;
    }

    JMBDEMODELS_EXPORT QSqlDatabase getDB() const
    {
        return this->m_db;
    }

    /*!
        \fn int ProcessorIdIndex()

        \brief Get the index of the fieldname ProcessorId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getProcessorIdIndex() const
    {
        return m_ProcessorIdIndex;
    }

    /*!
       \fn int NameIndex()

       \brief Get the index of the fieldname Name form the database

       Returns the value of the index
    */
    JMBDEMODELS_EXPORT int getNameIndex() const
    {
        return m_NameIndex;
    }

    /*!
       \fn int ClockRateIndex()

       \brief Get the index of the fieldname ClockRate form the database

       Returns the value of the index
    */
    JMBDEMODELS_EXPORT int getClockRateIndex() const
    {
        return m_ClockRateIndex;
    }

    /*!
       \fn int CoresIndex()

       \brief Get the index of the fieldname Cores form the database

       Returns the value of the index
    */
    JMBDEMODELS_EXPORT int getCoresIndex() const
    {
        return m_CoresIndex;
    }

    /*!
        \var int m_LastUpdateIndex
        \brief The value of the LastUpdateIndex
    */
    JMBDEMODELS_EXPORT int getLastUpdateIndex() const
    {
        return m_LastUpdateIndex;
    }

private:
    /*!
        \brief The Tablename in the database \e is const
     */
    const QString m_tableName = QLatin1String("processor");

    /*!
     * @ brief m_db
     */
    QSqlDatabase m_db = {};

    /*!
        \brief holds an initialised pointer to the Relationmodel
        \sa QSqlRelationalTableModel
     */
    QSqlRelationalTableModel *m_model{nullptr};

    /*!
       \brief holds an initialised pointer to the ItemSelectioModel
       \sa QItemSelectionModel
    */
    QItemSelectionModel *m_selectionModel{nullptr};

    /*!
     * @brief DataContext
     */
    Model::DataContext *m_dataContext = {};

    /*!
       \var int m_ProcessorIdIndex
       \brief The value of the ProcessorIdIndex
    */
    int m_ProcessorIdIndex{0};

    /*!
       \var int m_NameIndex
       \brief The value of the Name
    */
    int m_NameIndex{0};

    /*!
       \var int m_ClockRateIndex
       \brief The value of the ClockRate ndex
    */
    int m_ClockRateIndex{0};

    /*!
       \var int m_CoresIndex
       \brief The value of the CoresIndex
    */
    int m_CoresIndex{0};

    /*!
       \var int m_LastUpdateIndex
       \brief The value of the LastUpdateIndex
    */
    int m_LastUpdateIndex{0};

    /*!
     * Logging Category
     */
    QLoggingCategory m_ProcessorLog;
};
} // namespace Model
