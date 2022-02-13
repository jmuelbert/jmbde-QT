/*
 *  SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert
 * <juergen.muelbert@gmail.com>
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

#include "jmbdemodels_export.h"

namespace Model {
/*!
    \class CommonData

    \brief The CommonData class
    \details This Class is the root for many common classes
    \author Jürgen Mülbert
    \since 0.4
    \version 0.7
    \date 25.11.2021
    \copyright GPL-3.0-or-later
    */

class CommonData : public QAbstractTableModel {
  Q_OBJECT

public:
  /*!
      \fn  CommonData()
      \brief The Constructor for the CommonData
   */
  explicit JMBDEMODELS_EXPORT CommonData()
      : m_model(nullptr), m_selectionModel(nullptr) {}

  /*!
      \fn ~CommonData()

      \brief the Destructor for the CommonData
   */
  virtual JMBDEMODELS_EXPORT ~CommonData() {}

  /*!
      \fn virtual void setIndexes()
      \brief Set the fieldindexes from the datafieldnames of the db.
   */
  virtual JMBDEMODELS_EXPORT void setIndexes() = 0;

  /*!
      \fn virtual QSqlRelationalTableModel *initializeRelationalModel() final
      \brief set the QSqlRelationalTableModel for the DataModel
      \return The QSqlRelationalTableModel
   */
  virtual JMBDEMODELS_EXPORT auto initializeRelationalModel()
      -> QSqlRelationalTableModel * = 0;

  /*!
      \fn virtual QSqlRelationalTableModel *initializeInputDataModel() final
      \brief Initialize the InputDataModel

       \return The QSqlRelationalTableModel
   */
  virtual JMBDEMODELS_EXPORT auto initializeInputDataModel()
      -> QSqlRelationalTableModel * = 0;

  /*!
      \fn virtual QSqlTableModel *initializeViewModel() final
      \brief Initialize the ViewModel

      \return QSqlTableModel
   */
  virtual JMBDEMODELS_EXPORT auto initializeViewModel() -> QSqlTableModel * = 0;

  /*!
      \fn QSqlTableModel *initializeListModel();
      \brief Initiallize the list Model for select one dataset
  */
  virtual JMBDEMODELS_EXPORT auto initializeListModel() -> QSqlTableModel * = 0;

  /*!
   * \fn virtual auto generateTableString(
                              const QString &header) final
      \brief generateTableString

      \return a QString with the generated Table for Output
   */
  virtual JMBDEMODELS_EXPORT auto generateTableString(const QString &header)
      -> QString = 0;

  /*!
      \fn virtual auto generateFormularString(
                                 const QString &header) final
      \brief generateFormularString

      \return a QString with the generated Table for Output
   */
  virtual JMBDEMODELS_EXPORT auto generateFormularString(const QString &header)
      -> QString = 0;

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

  JMBDEMODELS_EXPORT int
  rowCount(const QModelIndex & = QModelIndex()) const override {
    return 200;
  }

  JMBDEMODELS_EXPORT int
  columnCount(const QModelIndex & = QModelIndex()) const override {
    return 200;
  }

  JMBDEMODELS_EXPORT QVariant data(const QModelIndex &index,
                                   int role) const override {
    switch (role) {
    case Qt::DisplayRole:
      return QString(QLatin1String("%1, %2"))
          .arg(index.column())
          .arg(index.row());
    default:
      break;
    }

    return QVariant();
  }

  JMBDEMODELS_EXPORT QHash<int, QByteArray> roleNames() const override {
    return {{Qt::DisplayRole, "display"}};
  }

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
  int m_LastUpdateIndex{0};
};
} // namespace Model
