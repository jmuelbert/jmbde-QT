/*
 * EmployeeDataModel.cpp
 * jmbde
 *
 *  Copyright (c) 2013, 2014 Jürgen Mülbert. All rights reserved.
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


#include "employeedatamodel.h"


EmployeeDataModel::EmployeeDataModel(QObject *parent) : DataModell(parent)
{

}

EmployeeDataModel::~EmployeeDataModel() {
}

void EmployeeDataModel::addDataSet() {

   QDate today = QDate::currentDate();
   QString todayDateString = today.toString(Qt::ISODate);

   QSqlQuery query;
   query.prepare(QLatin1String("INSERT INTO EMPLOYEE ("
                              ":Id, :EmployeeNO, :Gender, "
                               ":FirstName, :MiddleName, :Name, "
                               ":Street, :City, :ZipCode, "
                               ":Birthday, "
                               ":PhoneNumber, :FaxNumber, :MobileNumber, "
                               ":Mail, :BusinessMail, :ChipCard, "
                               ":DataCare, :Active, "
                               ":StartDate, :EndDate, "
                               ":DepartmentId, :WorkfunctionId, "
                               ":PlaceId, :CompanyId, "
                               ":LastUpdate)"));

    query.bindValue(QLatin1String(":EmployeeNO"), Database::Table::DEFAULT_FOREIGN_VALUE);
    query.bindValue(QLatin1String(":Gender"), QLatin1String("m"));
    query.bindValue(QLatin1String(":FirstName"),QLatin1String("Test"));
    query.bindValue(QLatin1String(":MiddleName"),QLatin1String("Test"));
    query.bindValue(QLatin1String(":Name"), QLatin1String("Test"));
    query.bindValue(QLatin1String(":Street"), QLatin1String("Test"));
    query.bindValue(QLatin1String(":City"), QLatin1String("Test"));
    query.bindValue(QLatin1String(":ZipCode"), QLatin1String("Test"));
    query.bindValue(QLatin1String(":birthday"), todayDateString);
    query.bindValue(QLatin1String(":Mail"), QLatin1String(" "));
    query.bindValue(QLatin1String(":BusinessMail"), QLatin1String("Test"));
    query.bindValue(QLatin1String(":ChipCard"), QLatin1String("Test"));
    query.bindValue(QLatin1String(":DataCare"), 0);
    query.bindValue(QLatin1String(":Active"), 1);
    query.bindValue(QLatin1String(":StartDate"), todayDateString);
    query.bindValue(QLatin1String(":EndDate"), todayDateString);
    query.bindValue(QLatin1String(":DepartmentId"), Database::Table::DEFAULT_FOREIGN_VALUE);
    query.bindValue(QLatin1String(":WorkfunctionId"), Database::Table::DEFAULT_FOREIGN_VALUE);
    query.bindValue(QLatin1String(":PlaceId"), Database::Table::DEFAULT_FOREIGN_VALUE);
    query.bindValue(QLatin1String(":LastUpdate"), todayDateString);

   bool retValue = query.exec();
   if (retValue == false) {
       qDebug() << db.lastError();
   } else {
       db.commit();
   }
}

QSqlTableModel *EmployeeDataModel::initializeViewModel() {

    //TODO: id als locale Konstante

    QSqlRelationalTableModel *model = new QSqlRelationalTableModel(this);
    model->setTable(QLatin1String("employee_view"));
    model->setEditStrategy(QSqlTableModel::OnFieldChange);

    model->setHeaderData(POS_EMPLOYEE_FIRSTNAME, Qt::Horizontal, QObject::tr("Firstname"));
    model->setHeaderData(POS_EMPLOYEE_LASTNAME, Qt::Horizontal, QObject::tr("Lastname"));

    model->select();

    return model;
}

QSqlRelationalTableModel *EmployeeDataModel::initializeRelationalModel() {

    //TODO: id als locale Konstante

    QSqlRelationalTableModel *model = new QSqlRelationalTableModel(this);
    model->setTable(QLatin1String("employee"));
    model->setEditStrategy(QSqlTableModel::OnFieldChange);

    model->setHeaderData(POS_EMPLOYEE_ID, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(POS_EMPLOYEE_NR, Qt::Horizontal, QObject::tr("Emp.Number"));
    model->setHeaderData(POS_EMPLOYEE_GENDER, Qt::Horizontal, QObject::tr("Gender"));
    model->setHeaderData(POS_EMPLOYEE_FIRSTNAME, Qt::Horizontal, QObject::tr("Firstname"));
    model->setHeaderData(POS_EMPLOYEE_LASTNAME, Qt::Horizontal, QObject::tr("Lastname"));
    model->setHeaderData(POS_EMPLOYEE_STREET, Qt::Horizontal, QObject::tr("Street"));
    model->setHeaderData(POS_EMPLOYEE_CITY, Qt::Horizontal, QObject::tr("City"));
    model->setHeaderData(POS_EMPLOYEE_ZIPCODE, Qt::Horizontal, QObject::tr("Zipcode"));
    model->setHeaderData(POS_EMPLOYEE_BIRTHDAY, Qt::Horizontal, QObject::tr("Birthday"));
    model->setHeaderData(POS_EMPLOYEE_PHONENUMBER, Qt::Horizontal, QObject::tr("Phonenumber"));
    model->setHeaderData(POS_EMPLOYEE_FAXNUMBER, Qt::Horizontal, QObject::tr("Faxnumber"));
    model->setHeaderData(POS_EMPLOYEE_MOBILENUMBER, Qt::Horizontal, QObject::tr("Mobilenumber"));
    model->setHeaderData(POS_EMPLOYEE_MAIL, Qt::Horizontal, QObject::tr("EMail"));
    model->setHeaderData(POS_EMPLOYEE_BUSINESSMAIL, Qt::Horizontal, QObject::tr("BusinessEMail"));
    model->setHeaderData(POS_EMPLOYEE_CHIPCARD, Qt::Horizontal, QObject::tr("Chipcard"));
    model->setHeaderData(POS_EMPLOYEE_DATACARE, Qt::Horizontal, QObject::tr("Datacare"));
    model->setHeaderData(POS_EMPLOYEE_ACTIVE, Qt::Horizontal, QObject::tr("Active"));
    model->setHeaderData(POS_EMPLOYEE_STARTDATE, Qt::Horizontal, QObject::tr("StartDate"));
    model->setHeaderData(POS_EMPLOYEE_ENDDATE, Qt::Horizontal, QObject::tr("EndDate"));
    model->setHeaderData(POS_EMPLOYEE_DEPARTMENTID, Qt::Horizontal, QObject::tr("Department"));
    model->setHeaderData(POS_EMPLOYEE_WORKFUNCTIONID, Qt::Horizontal, QObject::tr("Function"));
    model->setHeaderData(POS_EMPLOYEE_PLACEID, Qt::Horizontal, QObject::tr("Place"));
    model->setHeaderData(POS_EMPLOYEE_LASTUPDATE, Qt::Horizontal, QObject::tr("Last Update"));

    model->select();

    return model;
}

QSqlRelationalTableModel *EmployeeDataModel::initializeInputDataModel() {

    QSqlRelationalTableModel *model = new QSqlRelationalTableModel(this, this->db);
    model->setTable(QLatin1String("employee"));

   return model;
}

QSqlTableModel *EmployeeDataModel::initializeTableModel() {
    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable(QLatin1String("employee"));
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    model->setHeaderData(POS_EMPLOYEE_ID, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(POS_EMPLOYEE_NR, Qt::Horizontal, QObject::tr("Emp.Number"));
    model->setHeaderData(POS_EMPLOYEE_GENDER, Qt::Horizontal, QObject::tr("Gender"));
    model->setHeaderData(POS_EMPLOYEE_FIRSTNAME, Qt::Horizontal, QObject::tr("Firstname"));
    model->setHeaderData(POS_EMPLOYEE_LASTNAME, Qt::Horizontal, QObject::tr("Lastname"));
    model->setHeaderData(POS_EMPLOYEE_STREET, Qt::Horizontal, QObject::tr("Street"));
    model->setHeaderData(POS_EMPLOYEE_CITY, Qt::Horizontal, QObject::tr("City"));
    model->setHeaderData(POS_EMPLOYEE_ZIPCODE, Qt::Horizontal, QObject::tr("Zipcode"));
    model->setHeaderData(POS_EMPLOYEE_BIRTHDAY, Qt::Horizontal, QObject::tr("Birthday"));
    model->setHeaderData(POS_EMPLOYEE_PHONENUMBER, Qt::Horizontal, QObject::tr("Phonenumber"));
    model->setHeaderData(POS_EMPLOYEE_FAXNUMBER, Qt::Horizontal, QObject::tr("Faxnumber"));
    model->setHeaderData(POS_EMPLOYEE_MOBILENUMBER, Qt::Horizontal, QObject::tr("Mobilenumber"));
    model->setHeaderData(POS_EMPLOYEE_MAIL, Qt::Horizontal, QObject::tr("EMail"));
    model->setHeaderData(POS_EMPLOYEE_BUSINESSMAIL, Qt::Horizontal, QObject::tr("BusinessEMail"));
    model->setHeaderData(POS_EMPLOYEE_CHIPCARD, Qt::Horizontal, QObject::tr("Chipcard"));
    model->setHeaderData(POS_EMPLOYEE_DATACARE, Qt::Horizontal, QObject::tr("Datacare"));
    model->setHeaderData(POS_EMPLOYEE_ACTIVE, Qt::Horizontal, QObject::tr("Active"));
    model->setHeaderData(POS_EMPLOYEE_STARTDATE, Qt::Horizontal, QObject::tr("StartDate"));
    model->setHeaderData(POS_EMPLOYEE_ENDDATE, Qt::Horizontal, QObject::tr("EndDate"));
    model->setHeaderData(POS_EMPLOYEE_DEPARTMENTID, Qt::Horizontal, QObject::tr("Department"));
    model->setHeaderData(POS_EMPLOYEE_WORKFUNCTIONID, Qt::Horizontal, QObject::tr("Function"));
    model->setHeaderData(POS_EMPLOYEE_PLACEID, Qt::Horizontal, QObject::tr("Place"));
    model->setHeaderData(POS_EMPLOYEE_PLACEID, Qt::Horizontal, QObject::tr("Company"));
    model->setHeaderData(POS_EMPLOYEE_LASTUPDATE, Qt::Horizontal, QObject::tr("Last Update"));

    model->select();

    return model;
}

void EmployeeDataModel::setFirstname(QString *_firstname) {
    this->firstname = _firstname;
}

void EmployeeDataModel::setLastname(QString *_lastname) {
    this->lastname = _lastname;
}

void EmployeeDataModel::readAllRecords()
{

    QSqlQueryModel model;
    model.setQuery(QLatin1String("SELECT * FROM employee"));

    int colunmCount = model.columnCount();
    int rowCount = model.rowCount();


    QSqlRecord rec = model.record();
    // int recCount = rec.count();


    for (int i=0; i<rowCount; i++) {
        qDebug() << "Record : " << i;
        rec = model.record(i);
        for (int j=0; j<colunmCount; j++) {
            QString value = rec.value(j).toString();
            qDebug() << "ColumnCount : " << j << " - Value  = " << value;
        }
    }
}


QTextDocument *EmployeeDataModel::createSheet() {
    QTextDocument *document = new QTextDocument;

    return document;
}

QString EmployeeDataModel::generateTableString(QAbstractTableModel *model, QString header) {
    QString outString;
    int columnCount = model->columnCount();
    int rowCount = model->rowCount();
    qDebug() << "Header : " << header << " Columns : " << columnCount << " Rows : " << rowCount;

    QList<int> set;
    set.append(POS_EMPLOYEE_FIRSTNAME);
    set.append(POS_EMPLOYEE_LASTNAME);
    set.append(POS_EMPLOYEE_DEPARTMENTID);
    set.append(POS_EMPLOYEE_WORKFUNCTIONID);
    set.append(POS_EMPLOYEE_MAIL);

    // Document Title
    outString = QLatin1String("<h1>");
    outString += header;
    outString += QLatin1String("</h1>");
    outString += QLatin1String("<hr />");
    outString += QLatin1String("<table width=\"100%\" cellspacing=\"0\" class=\"tbl\">");
    outString += QLatin1String("<thead> <tr>");


    foreach (const int i, set) {
        qDebug() << "int i = " << i;
        outString += QLatin1String("<th>");
        outString.append(model->headerData(i, Qt::Horizontal).toString());
        outString += QLatin1String("</th>");
    }
    outString += QLatin1String("</tr> </thead>");


    for (int i=0; i<rowCount; i++) {
        outString += QLatin1String("<tr>");
        foreach (const int j, set) {
            outString += QLatin1String("<td>");
            QModelIndex ind(model->index(i, j));
            outString.append(ind.data(Qt::DisplayRole).toString());
            outString += QLatin1String("</td>");
        }
        outString += QLatin1String("</tr>");
    }

    // Close Table
    outString += QLatin1String("</table>");
    return outString;

}
