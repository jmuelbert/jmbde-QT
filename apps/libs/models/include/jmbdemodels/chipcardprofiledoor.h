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
  \class ChipCardProfileDoor
  \brief The ChipCardProfileDoor class
  \details In this is handlet all ChipCardProfileDoor Data and create a many
  to many relation
  \author Jürgen Mülbert
  \since 0.4
  \version 0.7
  \date 25.12.2021
  \copyright GPL-3.0-or-later
*/
class ChipCardProfileDoor : public CommonData
{
    Q_OBJECT

public:
    /*!
        \fn ChipCardProfileDoor()

        \brief Constructor for the ChipCardProfileDoor
     */
    explicit JMBDEMODELS_EXPORT ChipCardProfileDoor();

    /*!
     * \fn ~ChipCardProfileDoor() override;
     *
     * \brief Destructor for ChipCardProfileDoor
     */
    JMBDEMODELS_EXPORT ~ChipCardProfileDoor()
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
        \fn int ChipCardProfileDoorIdIndex()

        \brief Get the index of the fieldname ChipCardProfileDoorId form the
       database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getChipCardProfileDoorIdIndex() const
    {
        return m_ChipCardProfileDoorIdIndex;
    }

    /*!
        \fn  int ChipCardProfileIdIndex()

        \brief Get the index of the fieldname ChipCardProfileId form the
       database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getChipCardProfileIdIndex() const
    {
        return m_ChipCardProfileIdIndex;
    }

    /*!
        \fn int ChipCardDoorsIdIndex()

        \brief Get the index of the fieldname ChipCardDoorsId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getChipCardDoorsIdIndex() const
    {
        return m_ChipCardDoorsIdIndex;
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
    const QString m_tableName = QLatin1String("chip_card_profile_door");

    /*!
     * @ brief m_db
     */
    QSqlDatabase m_db = {};

    /*!
     * @brief DataContext
     */
    Model::DataContext *m_dataContext = {};

    /*!
        \brief The value of the ChipCardProfileDoorIdIndex
     */
    int m_ChipCardProfileDoorIdIndex{0};

    /*!
        \brief The value of the ChipCardProfileIdIndex
     */
    int m_ChipCardProfileIdIndex{0};

    /*!
        \brief The value of the ChipCardDoorsIdIndex
     */
    int m_ChipCardDoorsIdIndex{0};

    /*!
         \brief The value of the LastUpdateIndex
     */
    int m_LastUpdateIndex{0};
};
} // namespace Model
