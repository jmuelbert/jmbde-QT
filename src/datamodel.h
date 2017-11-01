/*
   // datamodell.h
   // part of jmbde
   //
   // Copyright (c) 2013-2017 Jürgen Mülbert. All rights reserved.
   //
   // Licensed under the EUPL, Version 1.2 or – as soon they
   // will be approved by the European Commission - subsequent
   // versions of the EUPL (the "Licence");
   // You may not use this work except in compliance with the
   // Licence.
   // You may obtain a copy of the Licence at:
   //
   // https://joinup.ec.europa.eu/page/eupl-text-11-12
   //
   // Unless required by applicable law or agreed to in
   // writing, software distributed under the Licence is
   // distributed on an "AS IS" basis,
   // WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
   // express or implied.
   // See the Licence for the specific language governing
   // permissions and limitations under the Licence.
   //
   // Lizenziert unter der EUPL, Version 1.2 oder - sobald
   // diese von der Europäischen Kommission genehmigt wurden -
   // Folgeversionen der EUPL ("Lizenz");
   // Sie dürfen dieses Werk ausschließlich gemäß
   // dieser Lizenz nutzen.
   // Eine Kopie der Lizenz finden Sie hier:
   //
   // https://joinup.ec.europa.eu/page/eupl-text-11-12
   //
   // Sofern nicht durch anwendbare Rechtsvorschriften
   // gefordert oder in schriftlicher Form vereinbart, wird
   // die unter der Lizenz verbreitete Software "so wie sie
   // ist", OHNE JEGLICHE GEWÄHRLEISTUNG ODER BEDINGUNGEN -
   // ausdrücklich oder stillschweigend - verbreitet.
   // Die sprachspezifischen Genehmigungen und Beschränkungen
   // unter der Lizenz sind dem Lizenztext zu entnehmen.
   //
 */

#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QApplication>
#include <QObject>

#include <QMessageBox>

#include <QStandardPaths>
#include <QtSql>

#include <QDate>
#include <QDir>
#include <QSettings>

#include <QDebug>

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>

#include <QTableView>

/**
 * \brief The Main Database class
 * \details Here will handle all db actions...
 * \author Jürgen Mülbert
 * \version 0.3
 * \date 16.11.2013
 * \copyright EUPL V1.1
 *
 * \todo Remove UI fpr Testing
 * \todo Move Code for every Table in his own class
 *
 * \page DataModel Page
 *
 *
 * This is the introduction.
 *
 */

/**
 * @brief The DataModel class
 */
class DataModel : public QObject
{
  Q_OBJECT

  public:

    /**
     * @brief DataModel
     * @param parent
     */
    DataModel(QObject* parent = 0);

    /**
     * @brief ~DataModel
     */
    virtual ~DataModel();

    /**
     * @brief DataModel::CreateConnection
     * @return
     *
     * /todo init all tables
     * /todo check database version
     * /tode export and import all tables
     */
    bool CreateConnection();

    /**
     * @brief getDatabase
     * @return
     */
    QSqlDatabase getDatabase();

    /**
     * @brief initDb
     *
     * If the Database new then create the tables
     */
    QSqlError initDb();

    /**
     * @brief DataModell::addRow
     * @param tableView
     */
    void addRow(QTableView*);

    /**
     * @brief setOutTableStyle
     * @return
     */
    QString setOutTableStyle();

  protected:

    /**
     * @brief db
     */
    QSqlDatabase db;

  private:

    /**
     * @brief checkDBVersion
     * @return
     */
    bool checkDBVersion();

  signals:

  public slots:

};

#endif // DATAMODEL_H
