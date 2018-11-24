/**************************************************************************
**
** Copyright (c) 2013-2018 Jürgen Mülbert. All rights reserved.
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
/*!
 * \page Data Account
 *
 * The Account Table
 * -----------------
 *
 * - The Account Table
 *     + account_id - the autoincrement number of the account
 *     + username - the login/username in the foreign system
 *     + password - the password for login in the foreign system
 *     + systemdata_id - the foreign table for the extern systems
 *     + last_update - TIMESTAMP of the last modification.
 */

#ifndef ACCOUNTDATAMODEL_H
#define ACCOUNTDATAMODEL_H

#include <QObject>
#include <QtSql>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>

#include "definitions.h"
#include "models/commondatamodel.h"

/*! The Account Data Model
 * \page Data Account
 *
 * \class AccountDataModel
 * \brief The AccountDataModel class
 * \details In this is handlet all Accounts from the Employees
 * \author Jürgen Mülbert
 * \version 0.4
 * \date 07.04.2018
 * \copyright EUPL V1.2
 */
class AccountDataModel : public CommonDataModel {
  Q_OBJECT
  Q_LOGGING_CATEGORY(accountModel, "jmbde.models.account")
public:
    //! Constructor AccountDataModel
    /*!
   * \brief AccountDataModel
   * \param parent
   */
  explicit AccountDataModel(QObject *parent = nullptr);

   //! Destructor AccountDataModel
  ~AccountDataModel() override;

  // implement the virtuals

    //! setIndexes
    /*!
   * \brief setIndexes
   */
  void setIndexes();

  //! initializeRelationalModel
  /*!
   * \brief initializeRelationalModel
   * \return
   */
  QSqlRelationalTableModel *initializeRelationalModel();

  //! initializeInputDataModel
  /*!
   * \brief initializeInputDataModel
   * \return
   */
  QSqlRelationalTableModel *initializeInputDataModel();

  //! initializeViewModel
  /*!
   * \brief initializeViewModel
   * \return
   */
  QSqlTableModel *initializeViewModel();

  //! generateTableString
  /*!
   * \brief generateTableString
   * \param model
   * \param header
   * \return
   */
  QString generateTableString(QAbstractTableModel *model, const QString &header);

  //! generateFormularString
  /*!
   * \brief generateFormularString
   * \param model
   * \param header
   * \return
   */
  QString generateFormularString(QAbstractTableModel *model, const QString &header);

  // Getter
  //! AccountIdIndex
  /*!
   * \brief AccountIdIndex
   * \return
   */
  int AccountIdIndex() const { return m_AccountIdIndex; }

  //! UserNameIndex
  /*!
   * \brief UserNameIndex
   * \return
   */
  int UserNameIndex() const { return m_UserNameIndex; }

  //! PasswordIndex
  /*!
   * \brief PasswordIndex
   * \return
   */
  int PasswordIndex() const { return m_PasswordIndex; }

  //! SystemDataIndex
  /*!
   * \brief SystemDataIndex
   * \return
   */
  int SystemDataIndex() const { return m_SystemDataIdIndex; }

  //! LastUpdateIndex
  /*!
   * \brief LastUpdateIndex
   * \return
   */
  int LastUpdateIndex() const { return m_LastUpdateIndex; }

private:
  /*!
   * \brief m_tableName
   */
  const QString m_tableName = QLatin1String("account");

  //! The value of the AccountIdIndex
  int m_AccountIdIndex{};

  //! The value of the UserNameIndex
  int m_UserNameIndex{};

  //! The value of the PasswordIndex
  int m_PasswordIndex{};

  //! The value of the SystemDataIdIndex
  int m_SystemDataIdIndex{};

  //! The value of the LastUpdateIndex
  int m_LastUpdateIndex{};
};

#endif // ACCOUNTDATAMODEL_H
