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

Q_DECLARE_LOGGING_CATEGORY(jmbdeChipCardDoorLog)

namespace Model {
/*!
    \class ChipCardDoor
    \brief The ChipCardDoor class
    \details In this is handle all Doors with Access Control
    \author Jürgen Mülbert
    \since 0.4
    \version 0.6
    \date 1.12.2020
    \copyright GPL-3.0-or-later
    */
class ChipCardDoor : public CommonData {
    Q_OBJECT

public:
    /*!
        \fn ChipCardDoor()

        \brief Constructor for the ChipCardDoor
        \param parent The pointer to the parent Object
     */
    explicit JMBDEMODELS_EXPORT ChipCardDoor()
        : CommonData()
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
        \fn virtual QSqlRelationalTableModel *initializeRelationalModel()
        \brief set the QSqlRelationalTableModel for the DataModel
        \return The QSqlRelationalTableModel
     */
    virtual JMBDEMODELS_EXPORT QSqlRelationalTableModel* initializeRelationalModel() final;

    /*!
        \fn virtual QSqlRelationalTableModel *initializeInputDataModel()
        \brief Initialize the InputDataModel

        \return  The QSqlRelationalTableModel
     */
    virtual JMBDEMODELS_EXPORT QSqlRelationalTableModel* initializeInputDataModel() final;

    /*!
        \fn virtual QSqlTableModel *initializeViewModel()
        \brief Initialize the ViewModel

        \return  QSqlTableModel
     */
    virtual JMBDEMODELS_EXPORT QSqlTableModel* initializeViewModel() final;

    /*!
        \fn QSqlTableModel *initializeListModel();
        \brief Initiallize the list Model for select one dataset
    */
    virtual JMBDEMODELS_EXPORT QSqlTableModel* initializeListModel() final;

    /*!
     * \fn virtual auto generateTableString(
                                const QString &header) -> QString
        \brief generateTableString

        \return  a QString with the generated Table for Output
     */
    virtual JMBDEMODELS_EXPORT auto generateTableString(const QString& header) -> QString final;

    /*!
        \fn virtual auto generateFormularString(
                                   const QString &header) -> QString
        \brief generateFormularString

        \return  a QString with the generated Table for Output
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
        \fn  int ChipCardDoorIdIndex()

        \brief Get the index of the fieldname ChipCardDoorId from the database

        \return  the value of the index
     */
    JMBDEMODELS_EXPORT int getChipCardDoorIdIndex() const
    {
        return m_ChipCardDoorIdIndex;
    }

    /*!
        \fn int NumberIndex()

        \brief Get the index of the fieldname Number form the database

        \return  the value of the index
     */
    JMBDEMODELS_EXPORT int getNumberIndex() const
    {
        return m_NumberIndex;
    }

    /*!
        \fn int PlaceIdIndex()

        \brief Get the index of the fieldname  PlaceId form the database

        \return  the value of the index
     */
    JMBDEMODELS_EXPORT int getPlaceIdIndex() const
    {
        return m_PlaceIdIndex;
    }

    /*!
        \fn int DepartmetIdIndex()

        \brief Get the index of the fieldname DepartmetId form the database

        \return  the value of the index
     */
    JMBDEMODELS_EXPORT int getDepartmentIdIndex() const
    {
        return m_DepartmetIdIndex;
    }

    /*!
       \fn int EmployeeIdIndex()

       \brief Get the index of the fieldname EmployeeIdform the database

       \return  the value of the index
    */
    JMBDEMODELS_EXPORT int getEmployeeIdIndex() const
    {
        return m_EmployeeIdIndex;
    }

    /*!
        \fn  int LastUpdateIndex()

        \brief Get the index of the fieldname LastUpdate form the database

        \return  the value of the index
     */
    JMBDEMODELS_EXPORT int getLastUpdateIndex() const
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
        \brief The value of the ChipCardDoorIdIndex
    */
    int m_ChipCardDoorIdIndex { 0 };

    /*!
        \brief The value of the NumberIndex
    */
    int m_NumberIndex { 0 };

    /*!
        \brief The value of the PlaceIdIndex
    */
    int m_PlaceIdIndex { 0 };

    /*!
        \brief The value of the DepartmetIdIndex
    */
    int m_DepartmetIdIndex { 0 };

    /*!
      \brief The value of the EmployeeIdIndex
  */
    int m_EmployeeIdIndex { 0 };

    /*!
        \brief The value of the LastUpdateIndex
    */
    int m_LastUpdateIndex { 0 };
};
} // namespace Model
