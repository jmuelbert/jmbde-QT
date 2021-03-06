/*
   jmbde a BDE Tool for companies
   Copyright (C) 2013-2020  Jürgen Mülbert

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
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

Q_DECLARE_LOGGING_CATEGORY(jmbdeModelsCommonDataLog)

namespace Model
{
/*!
    \class CommonData

    \brief The CommonData class
    \details This Class is the root for many common classes
    \author Jürgen Mülbert
    \since 0.4
    \version 0.5
    \date 17.11.2020
    \copyright GPL-3.0-or-later
    */

class CommonData : public QAbstractTableModel
{
    Q_OBJECT

public:
    /*!
        \fn  CommonData()
        \brief The Constructor for the CommonData
     */
    explicit JMBDEMODELS_EXPORT CommonData();

    /*!
        \fn ~CommonData()

        \brief the Destructor for the CommonData
     */
    virtual JMBDEMODELS_EXPORT ~CommonData()
    {
    }

    /*!
        \fn  QTextDocument *createSheet()
        \brief Create a TextDocument for the Output to the Printer

        Returns The Pointer to the generated TextDocument

        \sa  QTextDocument
     */
    static JMBDEMODELS_EXPORT QTextDocument *createSheet();

    /*!
        \fn QString setOutTableStyle()
        \brief Initialize a String with the css-style for the output table

        Returns The initialized QString

        \sa QString
     */
    static JMBDEMODELS_EXPORT QString setOutTableStyle();

    /*!
        \fn QString setOutFormularStyle()
        \brief Initialize a String with the css-style for the output formular
        \details This is now just the Header

        Returns The initialized QString

        \sa QString
     */
    static JMBDEMODELS_EXPORT QString setOutFormularStyle();

    JMBDEMODELS_EXPORT int rowCount(const QModelIndex & = QModelIndex()) const override
    {
        return 200;
    }

    JMBDEMODELS_EXPORT int columnCount(const QModelIndex & = QModelIndex()) const override
    {
        return 200;
    }

    JMBDEMODELS_EXPORT QVariant data(const QModelIndex &index, int role) const override
    {
        switch (role) {
        case Qt::DisplayRole:
            return QString(QLatin1String("%1, %2")).arg(index.column()).arg(index.row());
        default:
            break;
        }

        return QVariant();
    }

    JMBDEMODELS_EXPORT QHash<int, QByteArray> roleNames() const override
    {
        return {{Qt::DisplayRole, "display"}};
    }

protected:
    /*!
        \brief holds an initialised pointer to the Relationmodel
        \sa QSqlRelationalTableModel
     */
    QSqlRelationalTableModel *m_model {nullptr};

    /*!
       \brief holds an initialised pointer to the ItemSelectioModel
       \sa QItemSelectionModel
    */
    QItemSelectionModel *m_selectionModel {nullptr};

private:
};
} // namespace Model
