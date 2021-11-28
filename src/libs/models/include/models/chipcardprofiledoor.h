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

Q_DECLARE_LOGGING_CATEGORY(m_ChipcardProfileDoorLog)

namespace Model {
/*!
  \class ChipCardProfileDoor
  \brief The ChipCardProfileDoor class
  \details In this is handlet all ChipCardProfileDoor Data and create a many
  to many relation
  \author Jürgen Mülbert
  \since 0.4
  \version 0.6
  \date 03.12.2020
  \copyright GPL-3.0-or-later
*/
class ChipCardProfileDoor : public CommonData {
    Q_OBJECT

public:
    /*!
        \fn ChipCardProfileDoor()

        \brief Constructor for the ChipCardProfileDoor
     */
    explicit JMBDEMODELS_EXPORT ChipCardProfileDoor()
        : CommonData()
        , m_ChipcardProfileDoorLog(QLoggingCategory("jmbde.jmbdemodels.chipcardprofiledoor"))
    {
        this->m_dataContext = new Model::DataContext();
        this->m_db = m_dataContext->getDatabase();

        // Set the Model
        this->m_model = new QSqlRelationalTableModel(this, this->m_db);
        this->m_model->setTable(this->m_tableName);
        this->m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

        setIndexes();
    }

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
        \fn virtual void setIndexes() final
        \brief Set the fieldindexes from the datafieldnames of the db.
     */
    virtual JMBDEMODELS_EXPORT void setIndexes() final;

    /*!
        \fn virtual QSqlRelationalTableModel *initializeRelationalModel()
        \brief set the QSqlRelationalTableModel for the DataModel
        Returns The QSqlRelationalTableModel
     */
    virtual JMBDEMODELS_EXPORT QSqlRelationalTableModel* initializeRelationalModel() final;

    /*!
        \fn virtual QSqlRelationalTableModel *initializeInputDataModel() final
        \brief Initialize the InputDataModel

        Returns The QSqlRelationalTableModel
     */
    virtual JMBDEMODELS_EXPORT QSqlRelationalTableModel* initializeInputDataModel() final;

    /*!
        \fn virtual QSqlTableModel *initializeViewModel() final
        \brief Initialize the ViewModel

        Returns QSqlTableModel
     */
    virtual JMBDEMODELS_EXPORT QSqlTableModel* initializeViewModel() final;

    /*!
        \fn QSqlTableModel *initializeListModel();
        \brief Initiallize the list Model for select one dataset
    */
    virtual JMBDEMODELS_EXPORT QSqlTableModel* initializeListModel() final;

    /*!
     * \fn virtual auto generateTableString(
                                const QString &header) -> QString final
        \brief generateTableString

        Returns a QString with the generated Table for Output
     */
    virtual JMBDEMODELS_EXPORT auto generateTableString(const QString& header) -> QString final;

    /*!
        \fn virtual auto generateFormularString(
                                   const QString &header) -> QString final
        \brief generateFormularString

        Returns a QString with the generated Table for Output
     */
    virtual JMBDEMODELS_EXPORT auto generateFormularString(const QString& header) -> QString final;

    // Getter

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
        \brief holds an initialised pointer to the Relationmodel
        \sa QSqlRelationalTableModel
     */
    QSqlRelationalTableModel* m_model { nullptr };

    /*!
       \brief holds an initialised pointer to the ItemSelectioModel
       \sa QItemSelectionModel
    */
    QItemSelectionModel* m_selectionModel { nullptr };

    /*!
     * @brief DataContext
     */
    Model::DataContext* m_dataContext = {};

    /*!
        \brief The value of the ChipCardProfileDoorIdIndex
     */
    int m_ChipCardProfileDoorIdIndex { 0 };

    /*!
        \brief The value of the ChipCardProfileIdIndex
     */
    int m_ChipCardProfileIdIndex { 0 };

    /*!
        \brief The value of the ChipCardDoorsIdIndex
     */
    int m_ChipCardDoorsIdIndex { 0 };

    /*!
         \brief The value of the LastUpdateIndex
     */
    int m_LastUpdateIndex { 0 };

    /*!
     * Logging Category
     */
    QLoggingCategory m_ChipcardProfileDoorLog;
};

} // namespace Model
