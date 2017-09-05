#ifndef MOBILEDATAMODEL_H
#define MOBILEDATAMODEL_H

#include <QObject>
#if QT_VERSION >= 0x050000
#include <QStandardPaths>
#include <QtSql>
#endif

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>

#include "datamodell.h"

class MobileDataModel : public DataModell {
public:
  /**
   * @brief MobileDataModel
   * @param parent
   */
  MobileDataModel(QObject *parent = 0);

  /**
   * @brief MobileDataModel::~MobileDataModel
   */
  ~MobileDataModel();

  /**
   * @brief addDataSet
   */
  void addDataSet();

  /**
   * @brief initializeRelationalModel
   * @return
   */
  QSqlRelationalTableModel *initializeRelationalModel();

  /**
    * @brief getQueryModel
    *
    * @return QSqlQueryModel
    */
  QSqlQueryModel *getQueryModel();

  /**
   * @brief initializeTableModel
   * @return
   */
  QSqlTableModel *initializeTableModel();

  /**
   * @brief generateTableString
   * @param model
   * @param header
   * @return
   */
  QString generateTableString(QAbstractTableModel *model, QString header);


private:
  /**
   * @brief pcnr
   */
  QString *pcnr;

  /**
   * @brief name
   */
  QString *name;

  /**
   * @brief The PosMobileTable enum
   */
  enum PosPhoneTable {
    POS_MOBILE_ID,
    POS_MOBILE_DEVICENAME_ID,
    POS_MOBILE_SERIALNUMBER,
    POS_MOBILE_NUMBER,
    POS_MOBILE_PIN,
    POS_MOBILE_ACTIVE,
    POS_MOBILE_REPLACE,
    POS_MOBILE_DEVICETYPE_ID,
    POS_MOBILE_EMPLOYEE_ID,
    POS_MOBILE_PLACE_ID,
    POS_MOBILE_DEPARTMENT_ID,
    POS_MOBILE_MANUFACTURER_ID,
    POS_MOBILE_INVENTORY_ID,
    POS_MOBILE_LAST_UPDATE
  };
};

#endif // MOBILEDATAMODEL_H
