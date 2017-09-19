/*
 * Constants.h
 * jmbde
 *
 * Copyright (c) 2013-2017 Jürgen Mülbert. All rights reserved.
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

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QtGlobal>

#define jmbde_VERSION_MAJOR 0
#define jmbde_VERSION_MINOR 4
/**
 * Constants for the jmbde application
 */
namespace Constants {

/**
 * @brief COMPANY_NAME
 */
const char COMPANY_NAME[] = "juergenmuelbert";
/**
 * @brief APPL_NAME
 */
const char APPL_NAME[] = "jmbde";
/**
 * @brief APPL_VERSION
 */
const char APPL_VERSION[] = "0.4.0";

const char APPL_DISPLAYNAME[] = "jmbde 0.4.0 © 2013-2017 Jürgen Mülbert";
/**
 * @brief APPL_PROJECT_SITE
 */
const char APPL_PROJECT_SITE[] =
    "http://www.juergen-muelbert.de/projects/jmbde/";
} // namespace Constants

namespace Settings {
namespace Groups {
const char MAINWINDOW[] = "MainWindow";
const char DATABASE[] = "Database";
} // namespace Groups

namespace MainWindow {
const char SIZE[] = "size";
const char POS[] = "pos";
const char SPLITTER[] = "splitterSizes";
} // namespace MainWindow

namespace Database {
const char TYPE[] = "type";
const char CONNECTION[] = "connection";
const char HOSTNAME[] = "hostname";
const char USERNAME[] = "username";
const char PASSWORD[] = "password";

} // namespace Database

} // namespace Settings

enum DbType { SQLITE, MYSQL, ODBC, POSTGRESQL };

namespace Database {

namespace Type {
const char SQLITE[] = "SqLite";
const char MYSQL[] = "MySql";
const char ODBC[] = "ODBC";
const char POSTGRESQL[] = "PostgreSQL";
const char DEFAULT[] = "SqLite";

} // namespace Type

namespace Table {
const char EMPLOYEE[] = "employee";
const char COMPANY[] = "company";
const char COMPUTER[] = "computer";
const char MOBILE[] = "mobile";
const char PHONE[] = "phone";
const char EMPLOYEE_CREATE[] = "CREATE TABLE employee (" \
        "id integer primary key, " \
        "EmployeeNO varchar, " \
        "Gender varchar, " \
        "FirstName varchar, " \
        "MiddleName varchar, " \
        "Name varchar, " \
        "Street varchar, " \
        "City varchar, " \
        "Zipcode varchar, " \
        "BirthDay varchar, " \
        "PhoneNumber varchar, " \
        "MobileNumber varchar, " \
        "Mail varchar, " \
        "BusinessMail varchar, " \
        "ChipCard varchar, " \
        "DataCare integer, " \
        "Active integer, " \
        "Photo varchar, " \
        "Notes varchar, " \
        "StartDate varchar, " \
        "EndDate varchar, " \
        "DepartmentId integer, " \
        "WorkfunctionId integer, " \
        "PlaceId integer, " \
        "CompanyId integer, " \
        "LastUpdate varchar);";
const char COMPUTER_CREATE[] = "CREATE TABLE computer (id integer primary key, Name varchar, Active integer, EmployeeID integer, LastUpdate varchar);";
const char MOBILE_CREATE[] = "CREATE TABLE phone (id integer primary key, Number varchar, Active integer, EmployeeID integer, Lastupdate varchar);";
const char PHONE_CREATE[] = "CREATE TABLE phone (id integer primary key, Number varchar, Active integer, EmployeeID integer, Lastupdate varchar);";
const char COMPANY_CREATE[] = "CREATE TABLE company ("
        "id integer primary key, " \
        "Name varchar, Name2 varchar, Street varchar, " \
        "City varchar, ZipCode varchar, PhoneNumber varchar, " \
        "FaxNumber varchar, MobileNumber varchar, Mail varchar, " \
        "Active integer, EmployeeID integer, LastUpdate varchar);";
}

namespace Table {
const int DEFAULT_FOREIGN_VALUE = 1;
}

namespace EmployeeTable {}
} // namespace Database
#endif // CONSTANTS_H
