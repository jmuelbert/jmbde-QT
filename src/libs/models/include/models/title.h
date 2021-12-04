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

Q_DECLARE_LOGGING_CATEGORY(m_TitleLog)

namespace Model
{
/*!
    \class Title
    \brief The Title class
    \details In this is handlet all Titles
    \author Jürgen Mülbert
    \since 0.4
    \version 0.6
    \date 23.01.2021
    \copyright GPL-3.0-or-later
    */
class Title : public CommonData
{
    Q_OBJECT

public:
    /*!
        \fn Title()

        \brief Constructor for the Title
     */
    explicit JMBDEMODELS_EXPORT Title();

    /*!
        \fn  ~Title();

        \brief Destructor for Title
     */
    JMBDEMODELS_EXPORT ~Title()
    {
    }

    // implement the virtuals

    /*!
        \fn virtual void setIndexes()
        \brief Set the fieldindexes from the datafieldnames of the db.
     */
    virtual JMBDEMODELS_EXPORT void setIndexes() final;

    /*!
        \fn virtual QSqlRelationalTableModel *initializeRelationalModel() final
        \brief set the QSqlRelationalTableModel for the DataModel
        Returns The QSqlRelationalTableModel
     */
    virtual JMBDEMODELS_EXPORT QSqlRelationalTableModel *initializeRelationalModel() final;

    /*!
        \fn virtual JMBDEMODELS_EXPORT QSqlRelationalTableModel
       *initializeInputDataModel() final \brief Initialize the InputDataModel

        Returns The QSqlRelationalTableModel
     */
    virtual JMBDEMODELS_EXPORT QSqlRelationalTableModel *initializeInputDataModel() final;

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
     * \fn virtual auto generateTableString(
                                const QString &header) -> QString final
        \brief generateTableString

        Returns a QString with the generated Table for Output
     */
    virtual JMBDEMODELS_EXPORT auto generateTableString(const QString &header) -> QString final;

    /*!
        \fn virtual auto generateFormularString(
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
        \fn  int TitleIdIndex()

        \brief Get the index of the fieldname TitleId from the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getTitleIdIndex() const
    {
        return m_TitleIdIndex;
    }

    /*!
      \fn  int NameIndex()

      \brief Get the index of the fieldname Name from the database

      Returns the value of the index
   */
    JMBDEMODELS_EXPORT int getNameIndex() const
    {
        return m_NameIndex;
    }

    /*!
      \fn  int FromDateIndex()

      \brief Get the index of the fieldname FromDate from the database

      Returns the value of the index
   */
    JMBDEMODELS_EXPORT int getFromDateIndex() const
    {
        return m_FromDateIndex;
    }

    /*!
        \fn  int LastUpdateIndex()

        \brief Get the index of the fieldname LastUpdate form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getLastUpdateIndex() const
    {
        return m_LastUpdateIndex;
    }

private:
    /*!
        \brief The Tablename in the database \e is const
     */
    const QString m_tableName = QLatin1String("title");

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
        \var int m_TitleIdIndex
        \brief The value of the TitleIdIndex
     */
    int m_TitleIdIndex{0};

    /*!
        \var int m_NameIndex
        \brief The value of the NameIndex
     */
    int m_NameIndex{0};

    /*!
        \var int m_FromDateIndex
        \brief The value of the FromDateIndex
     */
    int m_FromDateIndex{0};

    int m_LastUpdateIndex{0};

    /*!
     * Logging Category
     */
    QLoggingCategory m_TitleLog;
};
} // namespace Model
