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

Q_DECLARE_LOGGING_CATEGORY(m_AccountLog)

namespace Model {
/*!
    \class Account
    \brief The Account class
    \details In this is handlet all Accounts from the Employees
    \author Jürgen Mülbert
    \since 0.4
    \version 0.6
    \date 1.12.2020
    \copyright GPL-3.0-or-later
    */
class Account : public CommonData {
    Q_OBJECT

public:
    /*!
        \fn Account()

        \brief Constructor for the Account
     */
    explicit JMBDEMODELS_EXPORT Account()
        : CommonData()
        , m_AccountLog(QLoggingCategory("jmbde.jmbdemodels.account"))
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
        \fn  ~Account();

        \brief Destructor for  Account
     */
    JMBDEMODELS_EXPORT ~Account()
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
                                const QString &header) final
        \brief generateTableString

        \return a QString with the generated Table for Output
     */
    virtual JMBDEMODELS_EXPORT auto generateTableString(const QString& header) -> QString final;

    /*!
        \fn virtual auto generateFormularString(
                                   const QString &header) final
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
        \fn int getAccountIdIndex() const

        \brief Get the index of the fieldname AccountId from the database

        \return the value of the index
     */
    JMBDEMODELS_EXPORT int getAccountIdIndex() const
    {
        return m_AccountIdIndex;
    }

    /*!
        \fn int getUserNameIndex() const

        \brief Get the index of the fieldname UserName form the database

        \return the value of the index
     */
    JMBDEMODELS_EXPORT int getUserNameIndex() const
    {
        return m_UserNameIndex;
    }

    /*!
        \fn int getPasswordIndex() const

        \brief Get the index of the fieldname Password form the database

        \return the value of the index
     */
    JMBDEMODELS_EXPORT int getPasswordIndex() const
    {
        return m_PasswordIndex;
    }

    /*!
        \fn int getSystemDataIndex()

        \brief Get the index of the fieldname SystemData form the database

        \return the value of the index
     */
    JMBDEMODELS_EXPORT int getSystemDataIndex() const
    {
        return m_SystemDataIdIndex;
    }

    /*!
        \fn  int getLastUpdateIndex()

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
    const QString m_tableName = QLatin1String("account");

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
        \var int m_AccountIdIndex
        \brief The value of the AccountIdIndex
     */
    int m_AccountIdIndex { 0 };

    /*!
        \var int m_UserNameIndex
        \brief The value of the UserNameIndex
    */
    int m_UserNameIndex { 0 };

    /*!
         \var int m_PasswordIndex;
         \brief The value of the PasswordIndex
     */
    int m_PasswordIndex { 0 };

    /*!
        \var int m_SystemDataIdIndex
        \brief The value of the SystemDataIdIndex
    */
    int m_SystemDataIdIndex { 0 };

    /*!
        \var int m_LastUpdateIndex
        \brief The value of the LastUpdateIndex
    */
    int m_LastUpdateIndex { 0 };

    /*!
     * Logging Category
     */
    QLoggingCategory m_AccountLog;
};
} // namespace Model
