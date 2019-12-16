/**************************************************************************
**
** Copyright (c) 2013-2019 Jürgen Mülbert. All rights reserved.
**
** This file is part of jmbde
**
** Licensed under the EUPL, Version 1.2 or – as soon they
** will be approved by the European Commission - subsequent
** versions of the EUPL (the "Licence");
** You may not use this work except in compliance with the
** Licence.
** You may obtain a copy of the Licence at:
**
** https://joinup.ec.europa.eu/page/eupl-text-11-12
**
** Unless required by applicable law or agreed to in
** writing, software distributed under the Licence is
** distributed on an "AS IS" basis,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
** express or implied.
** See the Licence for the specific language governing
** permissions and limitations under the Licence.
**
** Lizenziert unter der EUPL, Version 1.2 oder - sobald
**  diese von der Europäischen Kommission genehmigt wurden -
** Folgeversionen der EUPL ("Lizenz");
** Sie dürfen dieses Werk ausschließlich gemäß
** dieser Lizenz nutzen.
** Eine Kopie der Lizenz finden Sie hier:
**
** https://joinup.ec.europa.eu/page/eupl-text-11-12
**
** Sofern nicht durch anwendbare Rechtsvorschriften
** gefordert oder in schriftlicher Form vereinbart, wird
** die unter der Lizenz verbreitete Software "so wie sie
** ist", OHNE JEGLICHE GEWÄHRLEISTUNG ODER BEDINGUNGEN -
** ausdrücklich oder stillschweigend - verbreitet.
** Die sprachspezifischen Genehmigungen und Beschränkungen
** unter der Lizenz sind dem Lizenztext zu entnehmen.
**
**************************************************************************/

#pragma once

#include <QObject>

#include <QtSql>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>
#include <QTextDocument>

#include "definitions.h"
#include "jmbde_common_export.h"
#include "models/idatamodel.h"

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

namespace Model {

class JMBDE_COMMON_EXPORT CommonData : public QObject {

public:
    /*!
        \fn  CommonData(QObject *parent = nullptr)
        \brief The Constructor for the CommonData
     */
    explicit CommonData(QObject *parent = nullptr);

    /*!
        \fn ~CommonData()

        \brief the Destructor for the CommonData
     */
    ~CommonData();

    /*!
        \fn  QTextDocument *createSheet()
        \brief Create a TextDocument for the Output to the Printer

        Returns The Pointer to the generated TextDocument

        \sa  QTextDocument
     */
    QTextDocument *createSheet();

    /*!
        \fn QString setOutTableStyle()
        \brief Initialize a String with the css-style for the output table

        Returns The initialized QString

        \sa QString
     */
    QString setOutTableStyle();

    /*!
        \fn QString setOutFormularStyle()
        \brief Initialize a String with the css-style for the output formular
        \details This is now just the Header

        Returns The initialized QString

        \sa QString
     */
    QString setOutFormularStyle();

protected:
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

private:
};
} // namespace Model
