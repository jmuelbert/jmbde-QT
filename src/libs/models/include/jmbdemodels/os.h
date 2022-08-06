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

namespace Model
{
/*!
    \class OS
    \brief The OS class
    \details In this is handle all OS
    \author Jürgen Mülbert
    \since 0.4
    \version 0.7
    \date 25.12.2021
    \copyright GPL-3.0-or-later
    */
class OS : public CommonData
{
    Q_OBJECT

public:
    /*!
        \fn explicit OS()
        \brief The Constructor for the Inventory
    */
    explicit JMBDEMODELS_EXPORT OS();

    /*!
        \fn  ~OS();

        \brief Destructor for OS
     */
    JMBDEMODELS_EXPORT ~OS()
    {
    }

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
    virtual JMBDEMODELS_EXPORT auto initializeRelationalModel() -> QSqlRelationalTableModel * final;

    /*!
        \fn virtual auto initializeInputDataModel() -> QSqlRelationalTableModel*
       fina \brief Initialize the InputDataModel

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
     * \fn virtual auto generateTableString(const QString& header) -> QString
     final \brief generateTableString

        \return a QString with the generated Table for Output
     */
    virtual JMBDEMODELS_EXPORT auto generateTableString(const QString &header) -> QString final;

    /*!
        \fn virtual auto generateFormularString(const QString& header) -> QString
       final \brief generateFormularString

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
        \fn int OSIdIndex()

        \brief Get the index of the fieldname OSId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getOSIdIndex() const
    {
        return m_OSIdIndex;
    }

    /*!
        \fn int NameIndex() const

        \brief Get the index of the fieldname Number form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getNameIndex() const
    {
        return m_NameIndex;
    }

    /*!
       \fn int VersionIndex()

       \brief Get the index of the fieldname Version form the database

       Returns the value of the index
    */
    JMBDEMODELS_EXPORT int getVersionIndex() const
    {
        return m_VersionIndex;
    }

    /*!
       \fn int RevisionIndex()

       \brief Get the index of the fieldname Revision form the database

       Returns the value of the index
    */
    JMBDEMODELS_EXPORT int getRevisionIndex() const
    {
        return m_RevisionIndex;
    }

    /*!
       \fn int FixIndex()

       \brief Get the index of the fieldname Fix form the database

       Returns the value of the index
    */
    JMBDEMODELS_EXPORT int getFixIndex() const
    {
        return m_FixIndex;
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
    const QString m_tableName = QLatin1String("os");

    /*!
     * @ brief m_db
     */
    QSqlDatabase m_db = {};

    /*!
     * @brief DataContext
     */
    Model::DataContext *m_dataContext = {};

    /*!
       \var int m_OSIdIndex
       \brief The value of the OSId
    */
    int m_OSIdIndex{0};

    /*!
       \var int m_NameIndex
       \brief The value of the Name
    */
    int m_NameIndex{0};

    /*!
       \var int m_VersionIndex
       \brief The value of the Version
    */
    int m_VersionIndex{0};

    /*!
       \var int m_RevisionIndex
       \brief The value of the Revision
    */
    int m_RevisionIndex{0};

    /*!
       \var int m_FixIndex
       \brief The value of the Fix
    */
    int m_FixIndex{0};

    /*!
        \var int m_LastUpdateIndex
        \brief The value of the LastUpdateIndex
    */
    int m_LastUpdateIndex{0};
};
} // namespace Model
