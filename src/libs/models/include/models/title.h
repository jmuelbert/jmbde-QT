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

namespace Model
{
/*!
    \class Title
    \brief The Title class
    \details In this is handlet all Titles
    \author Jürgen Mülbert
    \since 0.4
    \version 0.7
    \date 25.12.2021
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
        \fn virtual JMBDEMODELS_EXPORT auto initializeRelationalModel() -> QSqlRelationalTableModel* final
        \brief set the QSqlRelationalTableModel for the DataModel
        \return The QSqlRelationalTableModel
     */
    virtual JMBDEMODELS_EXPORT auto initializeRelationalModel() -> QSqlRelationalTableModel * final;

    /*!
        \fn virtual auto initializeInputDataModel() -> QSqlRelationalTableModel* fina
        \brief Initialize the InputDataModel

         \return The QSqlRelationalTableModel
     */
    virtual JMBDEMODELS_EXPORT auto initializeInputDataModel() -> QSqlRelationalTableModel * final;

    /*!
        \fn virtual auto initializeViewModel() -> QSqlTableModel* final
        \brief Initialize the ViewModel

        \return QSqlTableModel
     */
    virtual JMBDEMODELS_EXPORT auto initializeViewModel() -> QSqlTableModel * final;

    /*!
        \fn virtual auto initializeListModel() -> QSqlTableModel* final
        \brief Initiallize the list Model for select one dataset
    */
    virtual JMBDEMODELS_EXPORT auto initializeListModel() -> QSqlTableModel * final;

    /*!
     * \fn virtual auto generateTableString(const QString& header) -> QString final
        \brief generateTableString

        \return a QString with the generated Table for Output
     */
    virtual JMBDEMODELS_EXPORT auto generateTableString(const QString &header) -> QString final;

    /*!
        \fn virtual auto generateFormularString(const QString& header) -> QString final
        \brief generateFormularString

        \return a QString with the generated Table for Output
     */
    virtual JMBDEMODELS_EXPORT auto generateFormularString(const QString &header) -> QString final;

    // Getter
    /*!
     * \brief getTableName
     * \return
     */
    JMBDEMODELS_EXPORT auto getTableName() const -> QString
    {
        return this->m_tableName;
    }
    /*!
        \fn auot getDB() const -> QSqlDatabase
     */
    JMBDEMODELS_EXPORT auto getDB() const -> QSqlDatabase
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
};
} // namespace Model
