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

Q_DECLARE_LOGGING_CATEGORY(jmbdeModelsDepartmentLog)

namespace Model
{
/*!
  \class Department
  \brief The Department class
  \details In this is handlet all Departments in the Company
  \author Jürgen Mülbert
  \since 0.4
  \version 0.6
  \date 10.12.2020
  \copyright GPL-3.0-or-later
    */
class Department : public CommonData
{
    Q_OBJECT

public:
    /*!
        \fn explicit Department()
        \brief The Constructor for Department
     */
    explicit JMBDEMODELS_EXPORT Department();

    /*!
        \fn  ~Department() override;

        \brief Destructor for Department
     */
    JMBDEMODELS_EXPORT ~Department()
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
        Returns The QSqlRelationalTableModel
     */
    virtual JMBDEMODELS_EXPORT QSqlRelationalTableModel *initializeRelationalModel() final;

    /*!
        \fn virtual QSqlRelationalTableModel *initializeInputDataModel() final
        \brief Initialize the InputDataModel

        Returns The QSqlRelationalTableModel
     */
    virtual JMBDEMODELS_EXPORT QSqlRelationalTableModel *initializeInputDataModel() final;

    /*!
        \fn virtual QSqlTableModel *initializeViewModel() final
        \brief Initialize the ViewModel

        Returns QSqlTableModel
     */
    virtual JMBDEMODELS_EXPORT QSqlTableModel *initializeViewModel() final;

    /*!
        \fn QSqlTableModel *initializeListModel();
        \brief Initiallize the list Model for select one dataset
    */
    virtual JMBDEMODELS_EXPORT QSqlTableModel *initializeListModel() final;

    /*!
     * \fn virtual auto generateTableString(
                                const QString &header) -> QString final
        \brief generateTableString

        Returns a QString with the generated Table for Output
     */
    virtual JMBDEMODELS_EXPORT auto generateTableString(const QString &header) -> QString final;

    /*!
        \fn virtual auto generateFormularString(const QAbstractTableModel &model,
                                   const QString &header) -> QString final
        \brief generateFormularString

        Returns a QString with the generated Table for Output
     */
    virtual JMBDEMODELS_EXPORT auto generateFormularString(const QString &header) -> QString final;

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
        \fn int getDepartmentIdIndex()

        \brief Get the index of the fieldname DepartmentId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getDepartmentIdIndex() const
    {
        return m_DepartmentIdIndex;
    }

    /*!
        \fn  int getNameIndex()

        \brief Get the index of the fieldname Name form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getNameIndex() const
    {
        return m_NameIndex;
    }

    /*!
        \fn int getPriorityIndex()

        \brief Get the index of the fieldname Priority form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getPriorityIndex() const
    {
        return m_PriorityIndex;
    }

    /*!
        \fn int getPrinterIdIndex()

        \brief Get the index of the fieldname PrinterId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getPrinterIdIndex() const
    {
        return m_PrinterIdIndex;
    }

    /*!
        \fn  int getFaxIdIndex()

        \brief Get the index of the fieldname LastUpdate form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getFaxIdIndex() const
    {
        return m_FaxIdIndex;
    }

    /*!
        \fn  int getLastUpdateIndex()

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
    const QString m_tableName = QLatin1String("department");

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
        \var  int m_DepartmentIdIndex
        \brief The value of the DepartmentIdIndex
    */
    int m_DepartmentIdIndex{0};

    /*!
       \var int m_NameIndex
       \brief The value of the NameIndex
   */
    int m_NameIndex{0};

    /*!
       \var  int m_PriorityIndex
       \brief The value of the PriorityIndex
   */
    int m_PriorityIndex{0};

    /*!
       \var int m_PrinterIdIndex
       \brief The value of the PrinterIdIndex
   */
    int m_PrinterIdIndex{0};

    /*!
        \var int m_FaxIdIndex
        \brief The value of the FaxIdIndex
    */
    int m_FaxIdIndex{0};

    /*!
       \var int m_LastUpdateIndex
       \brief The value of the LastUpdateIndex
   */
    int m_LastUpdateIndex{0};
};
} // namespace Model
