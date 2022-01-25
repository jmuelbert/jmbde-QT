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
    \class ChipCardDoor
    \brief The ChipCardDoor class
    \details In this is handle all Doors with Access Control
    \author Jürgen Mülbert
    \since 0.4
    \version 0.7
    \date 25.12.2021
    \copyright GPL-3.0-or-later
    */
class ChipCardDoor : public CommonData
{
    Q_OBJECT

public:
    /*!
        \fn ChipCardDoor()

        \brief Constructor for the ChipCardDoor
        \param parent The pointer to the parent Object
     */
    explicit JMBDEMODELS_EXPORT ChipCardDoor();

    /*!
     * \fn  ~ChipCardDoor() override;
     *
     * \brief Destructor for ChipCardDoor
     */
    JMBDEMODELS_EXPORT ~ChipCardDoor()
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
        \fn  int ChipCardDoorIdIndex()

        \brief Get the index of the fieldname ChipCardDoorId from the database

        \return  the value of the index
     */
    JMBDEMODELS_EXPORT auto getChipCardDoorIdIndex() const -> int
    {
        return m_ChipCardDoorIdIndex;
    }

    /*!
        \fn int NumberIndex()

        \brief Get the index of the fieldname Number form the database

        \return  the value of the index
     */
    JMBDEMODELS_EXPORT auto getNumberIndex() const -> int
    {
        return m_NumberIndex;
    }

    /*!
        \fn int PlaceIdIndex()

        \brief Get the index of the fieldname  PlaceId form the database

        \return  the value of the index
     */
    JMBDEMODELS_EXPORT auto getPlaceIdIndex() const -> int
    {
        return m_PlaceIdIndex;
    }

    /*!
        \fn int DepartmetIdIndex()

        \brief Get the index of the fieldname DepartmetId form the database

        \return  the value of the index
     */
    JMBDEMODELS_EXPORT auto getDepartmentIdIndex() const -> int
    {
        return m_DepartmetIdIndex;
    }

    /*!
       \fn int EmployeeIdIndex()

       \brief Get the index of the fieldname EmployeeIdform the database

       \return  the value of the index
    */
    JMBDEMODELS_EXPORT auto getEmployeeIdIndex() const -> int
    {
        return m_EmployeeIdIndex;
    }

    /*!
        \fn  int LastUpdateIndex()

        \brief Get the index of the fieldname LastUpdate form the database

        \return  the value of the index
     */
    JMBDEMODELS_EXPORT auto getLastUpdateIndex() const -> int
    {
        return m_LastUpdateIndex;
    }

private:
    /*!
        \brief The Tablename in the database \e is const
     */
    const QString m_tableName = QLatin1String("chip_card_door");

    /*!
     * @ brief m_db
     */
    QSqlDatabase m_db = {};

    /*!
     * @brief DataContext
     */
    Model::DataContext *m_dataContext = {};

    /*!
        \brief The value of the ChipCardDoorIdIndex
    */
    int m_ChipCardDoorIdIndex{0};

    /*!
        \brief The value of the NumberIndex
    */
    int m_NumberIndex{0};

    /*!
        \brief The value of the PlaceIdIndex
    */
    int m_PlaceIdIndex{0};

    /*!
        \brief The value of the DepartmetIdIndex
    */
    int m_DepartmetIdIndex{0};

    /*!
      \brief The value of the EmployeeIdIndex
  */
    int m_EmployeeIdIndex{0};

    /*!
        \brief The value of the LastUpdateIndex
    */
    int m_LastUpdateIndex{0};
};
} // namespace Model
