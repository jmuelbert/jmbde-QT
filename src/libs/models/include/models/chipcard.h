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

Q_DECLARE_LOGGING_CATEGORY(m_ChipcardLog)

namespace Model {
/*!
    \class ChipCard
    \brief The ChipDataModel class
    \details in this class is handled the coins for the room access system.
    \author Jürgen Mülbert
    \since 0.4
    \version 0.5
    \date 1.12.2020
    \copyright GPL-3.0-or-later
 */
class ChipCard : public CommonData {
    Q_OBJECT

public:
    /*!
        \fn ChipCard()

        \brief Constructor forChipCard
    */
    explicit JMBDEMODELS_EXPORT ChipCard()
        : CommonData()
        , m_ChipcardLog(QLoggingCategory("jmbde.jmbdemodels.chipcard"))
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
        \fn ~ChipCard() override

        \brief Destructor for the ChipCard
     */
    JMBDEMODELS_EXPORT ~ChipCard()
    {
    }

    // implement the virtuals

    /*!
        \fn virtual void setIndexes() final
        \brief Set the fieldindexes from the datafieldnames of the db.
     */
    virtual JMBDEMODELS_EXPORT void setIndexes() final;

    /*!
        \fn virtual QSqlRelationalTableModel *initializeRelationalModel() final
        \brief set the QSqlRelationalTableModel for the DataModel
        \return The QSqlRelationalTableModel
     */
    virtual JMBDEMODELS_EXPORT QSqlRelationalTableModel* initializeRelationalModel() final;

    /*!
        \fn virtual QSqlRelationalTableModel *initializeInputDataModel() final
        \brief Initialize the InputDataModel

        \return The QSqlRelationalTableModel
     */
    virtual JMBDEMODELS_EXPORT QSqlRelationalTableModel* initializeInputDataModel() final;

    /*!
        \fn virtual QSqlTableModel *initializeViewModel() final
        \brief Initialize the ViewModel

        \return QSqlTableModel
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

        \return a QString with the generated Table for Output
     */
    virtual JMBDEMODELS_EXPORT auto generateTableString(const QString& header) -> QString final;

    /*!
        \fn virtual auto generateFormularString(
                                   const QString &header) -> QString
        \brief generateFormularString

        \return a QString with the generated Table for Output
     */
    virtual JMBDEMODELS_EXPORT auto generateFormularString(const QString& header) -> QString final;

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
        \fn int ChipCardIdIndex()

        \brief Get the index of the fieldname ChipCardId from the database

        \return the value of the index
     */
    JMBDEMODELS_EXPORT int getChipCardIdIndex() const
    {
        return m_ChipCardIdIndex;
    }

    /*!
        \fn int NumberIndex()

        \brief Get the index of the fieldname Number from the database

        \return the value of the index
     */
    JMBDEMODELS_EXPORT int getNumberIndex() const
    {
        return m_NumberIndex;
    }

    /*!
        \fn  int ChipCardDoorIdIndex()

        \brief Get the index of the fieldname ChipCardDoorId from the database

        \return the value of the index
     */
    JMBDEMODELS_EXPORT int getChipCardDoorIdIndex() const
    {
        return m_ChipCardDoorIdIndex;
    }

    /*!
        \fn  int ChipCardProfileIdIndex()

        \brief Get the index of the fieldname ChipCardProfileId from the
       database

        \return the value of the index
     */
    JMBDEMODELS_EXPORT int getChipCardProfileIdIndex() const
    {
        return m_ChipCardProfileIdIndex;
    }

    /*!
        \fn  int EmployeeIdIndex()

        \brief Get the index of the fieldname EmployeeId from the database

        \return the value of the index
     */
    JMBDEMODELS_EXPORT int getEmployeeIdIndex() const
    {
        return m_EmployeeIdIndex;
    }

    /*!
        \fn  int LastUpdateIndex()

        \brief Get the index of the fieldname LastUpdate form the database

        \return the value of the index
     */
    JMBDEMODELS_EXPORT int getLastUpdateIndex() const
    {
        return m_LastUpdateIndex;
    }

private:
    /*!
        \brief The Tablename in the database \e is const
     */
    const QString m_tableName = QLatin1String("chip_card");

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
        \brief The value of the ChipCardIdIndex
     */
    int m_ChipCardIdIndex { 0 };

    /*!
        \brief The value of the NumberIndex
     */
    int m_NumberIndex { 0 };

    /*!
        \brief The value of the ChipCardDoorIdIndex
     */
    int m_ChipCardDoorIdIndex { 0 };

    /*!
        \brief The value of the hipCardProfileIdIndex
     */
    int m_ChipCardProfileIdIndex { 0 };

    /*!
        \brief The value of the EmployeeIdIndex
     */
    int m_EmployeeIdIndex { 0 };

    /*!
          \brief The value of the LastUpdateIndex
      */
    int m_LastUpdateIndex { 0 };
    /*!
     * Logging Category
     */
    QLoggingCategory m_ChipcardLog;
};

} // namespace Model
