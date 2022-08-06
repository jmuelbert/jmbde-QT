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
    \class Software
    \brief The Software class
    \details This Class is for the SoftwareData
    \author Jürgen Mülbert
    \since 0.2
    \version 0.7
    \date 25.12.2021
    \copyright GPL-3.0-or-later
    */
class Software : public CommonData
{
    Q_OBJECT

public:
    /*!
        \fn Software()

        \brief Constructor for the Software
     */
    explicit JMBDEMODELS_EXPORT Software();

    /*!
        \fn  ~Software();

        \brief Destructor for Software
     */
    JMBDEMODELS_EXPORT ~Software()
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
        \fn int SoftwareIdIndex()

        \brief Get the index of the fieldname SoftwareId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getSoftwareIdIndex() const
    {
        return m_SoftwareIdIndex;
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
    const QString m_tableName = QLatin1String("software");

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
       \var int m_SoftwareIdIndex
       \brief The value of the SoftwareId
    */
    int m_SoftwareIdIndex{0};

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
