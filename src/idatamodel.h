#ifndef IDATAMODEL_H
#define IDATAMODEL_H

class IDataModel {
  public:

    ~IDataModel() {}

    /**
     * @brief createDataTable
     * @param tableName
     * @deprecated You should not longer use this. The Database will create with a
     * script
     * @return boolean true or false, created ?
     */
    virtual bool createDataTable() = 0;

    /**
     * @brief setIndexes
     */
    virtual void setIndexes() = 0;

    /**
     * @brief initializeRelationalModel
     * @param tableName
     * @return RelationalTableModel
     */
    virtual QSqlRelationalTableModel* initializeRelationalModel() = 0;

    /**
     * @brief initializeInputDataModel
     * @return
     */
    virtual QSqlRelationalTableModel* initializeInputDataModel() = 0;

    /**
     * @brief initializeViewModel
     * @return
     */
    virtual QSqlTableModel* initializeViewModel() = 0;

    /**
     * @brief generateTabletring
     * @param model
     * @param header
     * @return
     */
    virtual QString generateTableString(QAbstractTableModel* model, QString header) = 0;

    /**
     * @brief generateFormularString
     * @param model
     * @param header
     * @return
     */
    virtual QString generateFormularString(QAbstractTableModel* model, QString header) = 0;
};

#endif // IDATAMODEL_H
