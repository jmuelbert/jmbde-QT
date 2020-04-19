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

#include <QObject>

#include <QtSql>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>
#include <QTextDocument>

#include <jmbdemodels-version.h>
#include <jmbdemodels_export.h>

namespace Model
{
/*!
    \class CommonData

    \brief The CommonData class
    \details This Class is the root for many common classes
    \author Jürgen Mülbert
    \since 0.4
    \version 0.4.25
    \date 03.08.2019
    \copyright EUPL V1.2
    */

class CommonData : public QObject
{
public:
    /*!
        \fn  CommonData(QObject *parent = nullptr)
        \brief The Constructor for the CommonData
     */
    explicit JMBDEMODELS_EXPORT CommonData(QObject *parent = nullptr);

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
