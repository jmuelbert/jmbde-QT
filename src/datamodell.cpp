/*
 * datamodell.cpp
 * jmbde
 *
 *  Copyright (c) 2013 Jürgen Mülbert. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the European Union Public Licence (EUPL),
 * version 1.1.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * European Union Public Licence for more details.
 *
 * You should have received a copy of the European Union Public Licence
 * along with this program. If not, see
 * http://www.osor.eu/eupl/european-union-public-licence-eupl-v.1.1
 *
 */




#include "constants.h"
#include "datamodell.h"

DataModell::DataModell(QObject *parent) :
    QObject(parent)
{
    /*
    if (db.isOpen()) { return; }
    else {
        CreateConnection();
        return;
    }
    */
}

bool DataModell::CreateConnection()
{
#if QT_VERSION >= 0x050000
        QStringList dataDirList = QStandardPaths::standardLocations(QStandardPaths::DataLocation);
        // Use user space
        QString dataBaseDir = dataDirList.at(0);
        qDebug() << "DataDirList0 = " << dataBaseDir;
#else
#ifdef Q_OS_LINUX
        QString dataBaseDir = QDir::homePath();
#endif
#endif
        QString dataBaseFilewithPath =  QString(dataBaseDir);
        dataBaseFilewithPath.append(QDir::separator());
        dataBaseFilewithPath.append(Constants::APPL_NAME);
        dataBaseFilewithPath.append(".db");


        qDebug() << "dataBaseDirAndFile = " << dataBaseFilewithPath;

        QFile dbFile(dataBaseFilewithPath);

        if (dbFile.exists() == false) {
            int ret = QMessageBox::critical(0, tr("The Database don't exist"),
                                  tr("To create a new database"
                                     "click the open button\n"
                                     "The abort button leave this\n"),
                                  QMessageBox::Abort | QMessageBox::Open );
            if (ret == QMessageBox::Open) {
                QDir dataDir(dataBaseDir);
                if (dataDir.exists() == false) {
                    QString dirName = dataDir.dirName();
                    dataDir.cdUp();
                    dataDir.mkpath(dirName);
                }

                db = QSqlDatabase::addDatabase("QSQLITE");
                db.setDatabaseName(dataBaseFilewithPath);
                if (!db.open()) {
                    QMessageBox::critical(0, tr("Cannot open database"),
                        tr("Unable to establish a database connection.\n"
                                 "This example needs SQLite support. Please read "
                                 "the Qt SQL driver documentation for information how "
                                 "to build it.\n\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
                    return false;
                } else {
                    // Create Tables
                    createRelationalTables();

                }
            } else {
                return false;
            }
        } else {
            db = QSqlDatabase::addDatabase("QSQLITE");
            db.setDatabaseName(dataBaseFilewithPath);
            if (!db.open()) {
                QMessageBox::critical(0, tr("Cannot open database"),
                    tr("Unable to establish a database connection.\n"
                             "This example needs SQLite support. Please read "
                             "the Qt SQL driver documentation for information how "
                             "to build it.\n\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);
                return false;
            }
       }
        if (!db.open()) {
            QMessageBox::critical(0, tr("Cannot open database"),
                tr("Unable to establish a database connection.\n"
                         "This example needs SQLite support. Please read "
                         "the Qt SQL driver documentation for information how "
                         "to build it.\n\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
            return false;
        }
    return true;
}

/**
 * @brief DataModell::createRelationalTables
 */
void DataModell::createRelationalTables() {
#ifdef QT_DEBUG
    if (db.isOpen()) {
        qDebug() << "Database Connection: " << db.connectionName();
        qDebug() << "Database Name      : " << db.databaseName();

    } else {
        qDebug() << "No Database !";
   }
#endif


    QSqlQuery query;

    /**
      the person table of the database
      */
    bool ret = query.exec("create table employee (id INTEGER primary key AUTOINCREMENT, "
                          "persnr INTEGER, "
               "firstname varchar(32), "
               "lastname varchar(32), "
               "function INTEGER, "
               "department INTEGER, "
               "computer INTEGER, "
               "phone INTEGER, "
               "mobile INTEGER, "
               "fax INTEGER, "
               "documents INTEGER, "
               "datenschutz BOOLEAN ,"
               "creationTime TEXT, "
               "updateTime TEXT);");
#ifdef QT_DEBUG
    qDebug() << "Create Employee Table" << db.lastError();
#endif

    ret = query.exec("create table function (id INTEGER primary key AUTOINCREMENT, name varchar(32));");
#ifdef QT_DEBUG
    qDebug() << "Create Function Table" << db.lastError();
#endif

    ret = query.exec("create table department (id INTEGER primary key AUTOINCREMENT, name varchar(32));");
#ifdef QT_DEBUG
    qDebug() << "Create Department Table" << db.lastError();
#endif

    ret = query.exec("create table computer (id INTEGER primary key AUTOINCREMENT, pcnr varchar(32), name varchar(32));");
#ifdef QT_DEBUG
    qDebug() << "Create Computer Table" << db.lastError();
#endif

    ret = query.exec("create table phone (id INTEGER primary key AUTOINCREMENT, name varchar(32), typ varchar(32));");
#ifdef QT_DEBUG
    qDebug() << "Create phone Table" << db.lastError();
#endif

    ret = query.exec("create table mobile (id INTEGER primary key AUTOINCREMENT, name varchar(32));");
#ifdef QT_DEBUG
    qDebug() << "Create Mobile Table" << db.lastError();
#endif

    ret = query.exec("create table fax (id INTEGER primary key AUTOINCREMENT, name varchar(32), place varchar(32));");
#ifdef QT_DEBUG
    qDebug() << "Create Fax Table" << db.lastError();
#endif

    ret = query.exec("create table documents (id INTEGER primary key AUTOINCREMENT, name varchar(32));");
#ifdef QT_DEBUG
    qDebug() << "Create Documents Table" << db.lastError();
#endif

    ret = query.exec("create table version (id INTEGER primary key AUTOINCREMENT, name varchar(32), version INTEGER, revision INTEGER, patchversion INTEGER);");
#ifdef QT_DEBUG
    qDebug() << "Create Version Table" << db.lastError();
#endif



#ifdef QT_DEBUG
    qDebug() << "Create Test Data";
    CreateTestData();
#endif

}

/**
 * @brief DataModell::AddEmployee
 */
void DataModell::AddEmployee() {

    QSqlQuery query;
    QString sqlString = "insert into employee(firstname, lastname) values( ";
    sqlString.append("'");
    sqlString.append(firstname);
    sqlString.append("' , '");
    sqlString.append(lastname);
    sqlString.append("');");
    bool ret = query.exec(sqlString);
    if (ret == false) {
        qDebug() << sqlString.toLatin1();
        qDebug() << db.lastError();
    } else {
        db.commit();
    }
}


/**
 * @brief DataModell::initializeModel
 * @param model
 */
QSqlRelationalTableModel *DataModell::initializeRelationalModel(){

    QSqlRelationalTableModel *model = new QSqlRelationalTableModel(this, this->db);
    model->setTable("employee");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setRelation(POS_FUNCTION, QSqlRelation("function", "id", "name"));
    model->setRelation(POS_DEPARTMENT, QSqlRelation("department", "id", "name"));
    model->setRelation(POS_COMPUTER, QSqlRelation("computer", "id", "name"));
    model->setRelation(POS_PHONE, QSqlRelation("phone", "id", "name"));
    // model->setRelation(POS_MOBILE, QSqlRelation("mobile", "id", "name"));
    // model->setRelation(POS_FAX, QSqlRelation("fax", "id", "name"));
    // model->setRelation(POS_DOCUMENTS, QSqlRelation("documents", "id", "name"));

    model->setHeaderData(POS_ID, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(POS_PERSNR, Qt::Horizontal, QObject::tr("Pers.Number"));
    model->setHeaderData(POS_FIRSTNAME, Qt::Horizontal, QObject::tr("Firstname"));
    model->setHeaderData(POS_LASTNAME, Qt::Horizontal, QObject::tr("Lastname"));
    model->setHeaderData(POS_FUNCTION, Qt::Horizontal, QObject::tr("Function"));
    model->setHeaderData(POS_DEPARTMENT, Qt::Horizontal, QObject::tr("Department"));
    model->setHeaderData(POS_COMPUTER, Qt::Horizontal, QObject::tr("Computer"));
    model->setHeaderData(POS_PHONE, Qt::Horizontal, QObject::tr("Phone"));
    model->setHeaderData(POS_MOBILE, Qt::Horizontal, QObject::tr("Mobile"));
    model->setHeaderData(POS_FAX, Qt::Horizontal, QObject::tr("Fax"));
    model->setHeaderData(POS_DOCUMENTS, Qt::Horizontal, QObject::tr("Documents"));
    model->setHeaderData(POS_DATENSCHUTZ, Qt::Horizontal, QObject::tr("Datenschutz"));
    model->setHeaderData(POS_CREATIONTIME, Qt::Horizontal, QObject::tr("Creationtime"));
    model->setHeaderData(POS_UPDATETIME, Qt::Horizontal, QObject::tr("Updatetime"));

    model->select();

    return model;
}

/**
 * @brief DataModell::initializeQueryModel
 * @return
 */
QSqlTableModel *DataModell::initializeEmployeeModel() {
    QSqlTableModel *model = new QSqlTableModel(this, this->db);
    model->setTable("employee");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);

    model->setHeaderData(POS_ID, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(POS_PERSNR, Qt::Horizontal, QObject::tr("Pers.Number"));
    model->setHeaderData(POS_FIRSTNAME, Qt::Horizontal, QObject::tr("Firstname"));
    model->setHeaderData(POS_LASTNAME, Qt::Horizontal, QObject::tr("Lastname"));
    model->setHeaderData(POS_FUNCTION, Qt::Horizontal, QObject::tr("Function"));
    model->setHeaderData(POS_DEPARTMENT, Qt::Horizontal, QObject::tr("Department"));
    model->setHeaderData(POS_COMPUTER, Qt::Horizontal, QObject::tr("Computer"));
    model->setHeaderData(POS_PHONE, Qt::Horizontal, QObject::tr("Phone"));
    model->setHeaderData(POS_MOBILE, Qt::Horizontal, QObject::tr("Mobile"));
    model->setHeaderData(POS_FAX, Qt::Horizontal, QObject::tr("Fax"));
    model->setHeaderData(POS_DOCUMENTS, Qt::Horizontal, QObject::tr("Documents"));
    model->setHeaderData(POS_DATENSCHUTZ, Qt::Horizontal, QObject::tr("Datenschutz"));
    model->setHeaderData(POS_CREATIONTIME, Qt::Horizontal, QObject::tr("Creationtime"));
    model->setHeaderData(POS_UPDATETIME, Qt::Horizontal, QObject::tr("Updatetime"));

    model->select();

    return model;
}


/**
 * @brief Employee::setFirstname
 * @param _firstname
 */
void DataModell::setFirstname(QString *_firstname) {
    this->firstname = _firstname;
}

/**
 * @brief Employee::setLastname
 * @param _lastname
 */
void DataModell::setLastname(QString *_lastname) {
    this->lastname = _lastname;
}

#ifdef QT_DEBUG
/**
 * @brief Employee::CreateTestData
 */
void DataModell::CreateTestData()
{
    QSqlQuery query;

    query.exec("insert into employee values(1, 1, 'Danny', 'Young', 1, 1,1, 1, 1, 1, 1, 1, '99', '98')");
    query.exec("insert into employee values(2, 1, 'Christine', 'Holand', 1, 1, 2, 2, 2, 2, 2, 0, '98', '97')");
    query.exec("insert into employee values(3, 1, 'Lars', 'Gordon', 1, 1, 3, 3, 3, 3, 3, 3, '97', '96')");
    query.exec("insert into employee values(4, 1, 'Roberto', 'Robitaille', 1, 1 , 4, 4, 4, 4, 4, 4, '95', '94')");
    query.exec("insert into employee values(5, 1, 'Maria', 'Papadopoulos', 1, 1, 5, 0, 5, 5, 0, 1, '93', '92')");
    query.exec("insert into employee values(6, 1, 'Willy', 'Winzig', 1, 1, 6, 0,0,6 ,6 ,0,'91', '90')");
    query.exec("insert into employee values(7, 1, 'Danny', 'Young', 1, 1,1, 1, 1, 1, 1, 1, '99', '98')");
    query.exec("insert into employee values(8, 1, 'Christine', 'Holand', 1, 1, 2, 2, 2, 2, 2, 0, '98', '97')");
    query.exec("insert into employee values(9, 1, 'Lars', 'Gordon', 1, 1, 3, 3, 3, 3, 3, 3, '97', '96')");
    query.exec("insert into employee values(10, 1, 'Roberto', 'Robitaille', 1, 1 , 4, 4, 4, 4, 4, 4, '95', '94')");
    query.exec("insert into employee values(11, 1, 'Maria', 'Papadopoulos', 1, 1, 5, 0, 5, 5, 0, 1, '93', '92')");
    query.exec("insert into employee values(12, 1, 'Willy', 'Winzig', 1, 1, 6, 0,0,6 ,6 ,0,'91', '90')");
    query.exec("insert into employee values(13, 1, 'Danny', 'Young', 1, 1,1, 1, 1, 1, 1, 1, '99', '98')");
    query.exec("insert into employee values(14, 1, 'Christine', 'Holand', 1, 1, 2, 2, 2, 2, 2, 0, '98', '97')");
    query.exec("insert into employee values(15, 1, 'Lars', 'Gordon', 1, 1, 3, 3, 3, 3, 3, 3, '97', '96')");
    query.exec("insert into employee values(16, 1, 'Roberto', 'Robitaille', 1, 1 , 4, 4, 4, 4, 4, 4, '95', '94')");
    query.exec("insert into employee values(17, 1, 'Maria', 'Papadopoulos', 1, 1, 5, 0, 5, 5, 0, 1, '93', '92')");
    query.exec("insert into employee values(18, 1, 'Willy', 'Winzig', 1, 1, 6, 0,0,6 ,6 ,0,'91', '90')");
    query.exec("insert into employee values(19, 1, 'Danny', 'Young', 1, 1,1, 1, 1, 1, 1, 1, '99', '98')");
    query.exec("insert into employee values(20, 1, 'Christine', 'Holand', 1, 1, 2, 2, 2, 2, 2, 0, '98', '97')");
    query.exec("insert into employee values(21, 1, 'Lars', 'Gordon', 1, 1, 3, 3, 3, 3, 3, 3, '97', '96')");
    query.exec("insert into employee values(22, 1, 'Roberto', 'Robitaille', 1, 1 , 4, 4, 4, 4, 4, 4, '95', '94')");
    query.exec("insert into employee values(23, 1, 'Maria', 'Papadopoulos', 1, 1, 5, 0, 5, 5, 0, 1, '93', '92')");
    query.exec("insert into employee values(24, 1, 'Willy', 'Winzig', 1, 1, 6, 0,0,6 ,6 ,0,'91', '90')");
    query.exec("insert into employee values(25, 1, 'Danny', 'Young', 1, 1,1, 1, 1, 1, 1, 1, '99', '98')");
    query.exec("insert into employee values(26, 1, 'Christine', 'Holand', 1, 1, 2, 2, 2, 2, 2, 0, '98', '97')");
    query.exec("insert into employee values(27, 1, 'Lars', 'Gordon', 1, 1, 3, 3, 3, 3, 3, 3, '97', '96')");
    query.exec("insert into employee values(28, 1, 'Roberto', 'Robitaille', 1, 1 , 4, 4, 4, 4, 4, 4, '95', '94')");
    query.exec("insert into employee values(29, 1, 'Maria', 'Papadopoulos', 1, 1, 5, 0, 5, 5, 0, 1, '93', '92')");
    query.exec("insert into employee values(30, 1, 'Willy', 'Winzig', 1, 1, 6, 0,0,6 ,6 ,0,'91', '90')");
    query.exec("insert into employee values(31, 1, 'Danny', 'Young', 1, 1,1, 1, 1, 1, 1, 1, '99', '98')");
    query.exec("insert into employee values(32, 1, 'Christine', 'Holand', 1, 1, 2, 2, 2, 2, 2, 0, '98', '97')");
    query.exec("insert into employee values(33, 1, 'Lars', 'Gordon', 1, 1, 3, 3, 3, 3, 3, 3, '97', '96')");
    query.exec("insert into employee values(34, 1, 'Roberto', 'Robitaille', 1, 1 , 4, 4, 4, 4, 4, 4, '95', '94')");
    query.exec("insert into employee values(35, 1, 'Maria', 'Papadopoulos', 1, 1, 5, 0, 5, 5, 0, 1, '93', '92')");
    query.exec("insert into employee values(36, 1, 'Willy', 'Winzig', 1, 1, 6, 0,0,6 ,6 ,0,'91', '90')");
    query.exec("insert into employee values(37, 1, 'Danny', 'Young', 1, 1,1, 1, 1, 1, 1, 1, '99', '98')");
    query.exec("insert into employee values(38, 1, 'Christine', 'Holand', 1, 1, 2, 2, 2, 2, 2, 0, '98', '97')");
    query.exec("insert into employee values(39, 1, 'Lars', 'Gordon', 1, 1, 3, 3, 3, 3, 3, 3, '97', '96')");
    query.exec("insert into employee values(40, 1, 'Roberto', 'Robitaille', 1, 1 , 4, 4, 4, 4, 4, 4, '95', '94')");
    query.exec("insert into employee values(41, 1, 'Maria', 'Papadopoulos', 1, 1, 5, 0, 5, 5, 0, 1, '93', '92')");
    query.exec("insert into employee values(42, 1, 'Willy', 'Winzig', 1, 1, 6, 0,0,6 ,6 ,0,'91', '90')");
    query.exec("insert into employee values(43, 1, 'Danny', 'Young', 1, 1,1, 1, 1, 1, 1, 1, '99', '98')");
    query.exec("insert into employee values(44, 1, 'Christine', 'Holand', 1, 1, 2, 2, 2, 2, 2, 0, '98', '97')");
    query.exec("insert into employee values(45, 1, 'Lars', 'Gordon', 1, 1, 3, 3, 3, 3, 3, 3, '97', '96')");
    query.exec("insert into employee values(46, 1, 'Roberto', 'Robitaille', 1, 1 , 4, 4, 4, 4, 4, 4, '95', '94')");
    query.exec("insert into employee values(47, 1, 'Maria', 'Papadopoulos', 1, 1, 5, 0, 5, 5, 0, 1, '93', '92')");
    query.exec("insert into employee values(48, 1, 'Willy', 'Winzig', 1, 1, 6, 0,0,6 ,6 ,0,'91', '90')");
    query.exec("insert into employee values(49, 1, 'Danny', 'Young', 1, 1,1, 1, 1, 1, 1, 1, '99', '98')");
    query.exec("insert into employee values(50, 1, 'Christine', 'Holand', 1, 1, 2, 2, 2, 2, 2, 0, '98', '97')");
    query.exec("insert into employee values(51, 1, 'Lars', 'Gordon', 1, 1, 3, 3, 3, 3, 3, 3, '97', '96')");
    query.exec("insert into employee values(52, 1, 'Roberto', 'Robitaille', 1, 1 , 4, 4, 4, 4, 4, 4, '95', '94')");
    query.exec("insert into employee values(53, 1, 'Maria', 'Papadopoulos', 1, 1, 5, 0, 5, 5, 0, 1, '93', '92')");
    query.exec("insert into employee values(54, 1, 'Willy', 'Winzig', 1, 1, 6, 0,0,6 ,6 ,0,'91', '90')");
    query.exec("insert into employee values(55, 1, 'Danny', 'Young', 1, 1,1, 1, 1, 1, 1, 1, '99', '98')");
    query.exec("insert into employee values(56, 1, 'Christine', 'Holand', 1, 1, 2, 2, 2, 2, 2, 0, '98', '97')");
    query.exec("insert into employee values(57, 1, 'Lars', 'Gordon', 1, 1, 3, 3, 3, 3, 3, 3, '97', '96')");
    query.exec("insert into employee values(58, 1, 'Roberto', 'Robitaille', 1, 1 , 4, 4, 4, 4, 4, 4, '95', '94')");
    query.exec("insert into employee values(59, 1, 'Maria', 'Papadopoulos', 1, 1, 5, 0, 5, 5, 0, 1, '93', '92')");
    query.exec("insert into employee values(60, 1, 'Willy', 'Winzig', 1, 1, 6, 0,0,6 ,6 ,0,'91', '90')");
#ifdef QT_DEBUG
    qDebug() << "Create Employee TestData" << db.lastError();
#endif


    query.exec("insert into department values(1, 'Managment')");
    query.exec("insert into department values(2, 'Accounting')");
    query.exec("insert into department values(3, 'Sales')");
    query.exec("insert into department values(4, 'Service')");
    query.exec("insert into department values(5, 'Parts')");
    query.exec("insert into department values(6, 'Facility')");
#ifdef QT_DEBUG
    qDebug() << "Create department TestData" << db.lastError();
#endif

    query.exec("insert into function values(1, 'Manager')");
    query.exec("insert into function values(2, 'Assistant')");
    query.exec("insert into function values(3, 'Sales Manager')");
    query.exec("insert into function values(4, 'Sales People')");
    query.exec("insert into function values(5, 'Service Manager')");
    query.exec("insert into function values(6, 'Service People')");
    query.exec("insert into function values(7, 'Accounting Manager')");
    query.exec("insert into function values(8, 'Accounting People Manager')");
    query.exec("insert into function values(9, 'Part Store Manager')");
    query.exec("insert into function values(10, 'Facility People')");
    query.exec("insert into function values(11, 'Trainee')");
    query.exec("insert into function values(12, 'Technical Trainee')");
#ifdef QT_DEBUG
    qDebug() << "Create function TestData" << db.lastError();
#endif


    query.exec("insert into computer values(1, 'PC0001')");
    query.exec("insert into computer values(2, 'PC0002')");
    query.exec("insert into computer values(3, 'PC0003')");
    query.exec("insert into computer values(4, 'PC0004')");
    query.exec("insert into computer values(5, 'PC0005')");
    query.exec("insert into computer values(6, 'PC0006')");
    query.exec("insert into computer values(7, 'PC0007')");
    query.exec("insert into computer values(8, 'PC0008')");
    query.exec("insert into computer values(9, 'PC0009')");
    query.exec("insert into computer values(10, 'PC0010')");
    query.exec("insert into computer values(11, 'PC0011')");
    query.exec("insert into computer values(12, 'PC0012')");
    query.exec("insert into computer values(13, 'PC0013')");
    query.exec("insert into computer values(15, 'PC0015')");
    query.exec("insert into computer values(99, 'NONE')");
#ifdef QT_DEBUG
    qDebug() << "Create function TestData" << db.lastError();
#endif

    query.exec("insert into phone values(1, '0001')");
    query.exec("insert into phone values(2, '0002')");
    query.exec("insert into phone values(3, '0003')");
    query.exec("insert into phone values(4, '0004')");
    query.exec("insert into phone values(5, '0005')");
    query.exec("insert into phone values(6, '0006')");
    query.exec("insert into phone values(7, '0007')");
    query.exec("insert into phone values(8, '0008')");
    query.exec("insert into phone values(9, '0009')");
    query.exec("insert into phone values(10, '0010')");
    query.exec("insert into phone values(11, '0011')");
    query.exec("insert into phone values(12, '0012')");
    query.exec("insert into phone values(13, '0013')");
    query.exec("insert into phone values(15, '0015')");
    query.exec("insert into phone values(99, 'NONE')");
#ifdef QT_DEBUG
    qDebug() << "Create phone TestData" << db.lastError();
#endif

    query.exec("insert into mobile values(1, '0001')");
    query.exec("insert into mobile values(2, '0002')");
    query.exec("insert into mobile values(3, '0003')");
    query.exec("insert into mobile values(4, '0004')");
    query.exec("insert into mobile values(5, '0005')");
    query.exec("insert into mobile values(6, '0006')");
    query.exec("insert into mobile values(7, '0007')");
    query.exec("insert into mobile values(8, '0008')");
    query.exec("insert into mobile values(9, '0009')");
    query.exec("insert into mobile values(10, '0010')");
    query.exec("insert into mobile values(11, '0011')");
    query.exec("insert into mobile values(12, '0012')");
    query.exec("insert into mobile values(13, '0013')");
    query.exec("insert into mobile values(15, '0015')");
    query.exec("insert into mobile values(99, 'NONE')");
#ifdef QT_DEBUG
    qDebug() << "Create mobile TestData" << db.lastError();
#endif

    query.exec("insert into fax values(1, '0001')");
    query.exec("insert into fax values(2, '0002')");
    query.exec("insert into fax values(3, '0003')");
    query.exec("insert into fax values(4, '0004')");
    query.exec("insert into fax values(5, '0005')");
    query.exec("insert into fax values(6, '0006')");
    query.exec("insert into fax values(7, '0007')");
    query.exec("insert into fax values(8, '0008')");
    query.exec("insert into fax values(9, '0009')");
    query.exec("insert into fax values(10, '0010')");
    query.exec("insert into fax values(11, '0011')");
    query.exec("insert into fax values(12, '0012')");
    query.exec("insert into fax values(13, '0013')");
    query.exec("insert into fax values(15, '0015')");
    query.exec("insert into fax values(99, 'NONE')");
#ifdef QT_DEBUG
    qDebug() << "Create fax TestData" << db.lastError();
#endif

    query.exec("insert into documents values(1, '0001')");
    query.exec("insert into documents values(2, '0002')");
    query.exec("insert into documents values(3, '0003')");
    query.exec("insert into documents values(4, '0004')");
    query.exec("insert into documents values(5, '0005')");
    query.exec("insert into documents values(6, '0006')");
    query.exec("insert into documents values(7, '0007')");
    query.exec("insert into documents values(8, '0008')");
    query.exec("insert into documents values(9, '0009')");
    query.exec("insert into documents values(10, '0010')");
    query.exec("insert into documents values(11, '0011')");
    query.exec("insert into documents values(12, '0012')");
    query.exec("insert into documents values(13, '0013')");
    query.exec("insert into documents values(15, '0015')");
    query.exec("insert into documents values(99, 'NONE')");
#ifdef QT_DEBUG
    qDebug() << "Create documents TestData" << db.lastError();
#endif


}
#endif


