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
    \class ComputerSoftware
    \brief The ComputerSoftware class
    \details In this is handle the installed software. Is a many to many
   relation.
    \author Jürgen Mülbert
    \since 0.4
    \version 0.7
    \date 25.12.2021
    \copyright GPL-3.0-or-later
    */
class ComputerSoftware : public CommonData
{
    Q_OBJECT

public:
    /*!
        \fn ComputerSoftware()

        \brief Constructor for the ComputerSoftware
     */
    explicit JMBDEMODELS_EXPORT ComputerSoftware();

    /*!
        \fn  ~ComputerSoftware() override;

        \brief Destructor for  ComputerSoftware
     */
    JMBDEMODELS_EXPORT ~ComputerSoftware()
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
        \fn int getComputerSoftwareIdIndex()

         \brief Get the index of the fieldname ComputerSoftwareId from the
       database

         Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getComputerSoftwareIdIndex() const
    {
        return m_ComputerSoftwareIdIndex;
    }

    /*!
        \fn int getComputerIdIndex()

        \brief Get the index of the fieldname ComputerId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getComputerIdIndex() const
    {
        return m_ComputerIdIndex;
    }

    /*!
        \fn int getSoftwareIdIndex()

        \brief Get the index of the fieldname SoftwareId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getSoftwareIdIndex() const
    {
        return m_SoftwareIdIndex;
    }

    /*!
        \fn  int getLastUpdateIndex()

        \brief Get the index of the fieldname getLastUpdate form the database

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
    const QString m_tableName = QLatin1String("computer_software");

    /*!
     * @ brief m_db
     */
    QSqlDatabase m_db = {};

    /*!
     * @brief DataContext
     */
    Model::DataContext *m_dataContext = {};

    /*!
        \var int m_ComputerSoftwareIdIndex
        \brief The value of the ComputerSoftwareIdIndex
    */
    int m_ComputerSoftwareIdIndex{0};

    /*!
        \var int m_ComputerIdIndex
        \brief The value of the ComputerIdIndex
    */
    int m_ComputerIdIndex{0};

    /*!
        \var int m_SoftwareIdIndex
        \brief The value of the SoftwareIdIndex
    */
    int m_SoftwareIdIndex{0};

    /*!
        \var int m_LastUpdateIndex
        \brief The value of the LastUpdateIndex
    */
    int m_LastUpdateIndex{0};
};
} // namespace Model
