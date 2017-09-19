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
const char COMPANY[] = "Company";
const char COMPANY_CREATE[] = "CREATE TABLE Company (" \
        "Id INTEGER PRIMARY KEY, " \
        "Name VARCHAR, " \
        "Name2 VARCHAR, " \
        "Street VARCHAR, " \
        "City VARCHAR, " \
        "ZipCode VARCHAR(10), " \
        "PhoneNumber VARCHAR, " \
        "FaxNumber VARCHAR, " \
        "MobileNumber VARCHAR, " \
        "Mail VARCHAR, " \
        "Active BOOLEAN, " \
        "EmployeID INTEGER, " \
        "LastUpdate TIMESTAMP);";

const char ZIPCODE[] = "ZipCode";
const char ZIPCODEC_CREATE[] = "CREATE TABLE ZipCode (" \
        "Id INTEGER PRIMARY KEY, " \
        "Zipcode VARCHAR(10), " \
        "LastUpdate TIMESTAMP);";

const char CITYNAME[] = "CityName";
const char CITYNAME_CREATE[] = "CREATE TABLE CityName (" \
        "Id INTEGER PRIMARY KEY, " \
        "Name VARCHAR, " \
        "LastUpdate TIMESTAMP);";

const char ZIPCITY[] = "ZipCity";
const char ZIPCITY_CREATE[] = "CREATE TABLE ZipCity (" \
        "Id INTEGER PRIMARY KEY, " \
        "ZipCodeID INTEGER, " \
        "CityID INTEGER, " \
        "LastUpdate TIMESTAMP);";

const char TITLE[] = "Title";
const char TITLE_CREATE[] = "CREATE TABLE (" \
        "Id INTEGER PRIMARY KEY, " \
        "Name VARCHAR, " \
        "LastUpdate TIMESTAMP);";

const char EMPLOYEE[] = "Employee";
const char EMPLOYEE_CREATE[] = "CREATE TABLE Employee (" \
        "Id INTEGER PRIMARY KEY, " \
        "NR INTEGER, " \
        "Gender INTEGER, " \
        "TitleID INTEGER, " \
        "FirstName VARCHAR, " \
        "LastName VARCHAR, " \
        "BirthDay DATE, " \
        "Street VARCHAR, " \
        "ZipCityID INTEGER, " \
        "HomePhone VARCHAR, " \
        "HomeMobile VARCHAR, " \
        "HomeMail VARCHAR, " \
        "BusinessMail VARCHAR, " \
        "DataCare BOOLEAN, " \
        "Active BOOLEAN, " \
        "Photo BLOB, " \
        "Notes VARCHAR, " \
        "HireDate DATE, " \
        "EndDate DATE, " \
        "DepartmentID INTEGER, " \
        "FunctionID INTEGER, " \
        "ComputerID INTEGER, " \
        "PrinterID INTEGER, " \
        "PhoneID INTEGER, " \
        "MobileID INTEGER, " \
        "FaxID INTEGER, " \
        "EmployeeAccountID INTEGER, " \
        "EmployeeDocumentID INTGER, " \
        "ChipCardID INTEGER, " \
        "LastUpdate TIMESTAMP);";

const char DEVICETYPE[] = "DeviceType";
const char DEVICETYPE_CREATE[] = "CREATE TABLE DeviceType (" \
        "Id INTEGER PRIMARY KEY, " \
        "Name VARCHAR, " \
        "LastUpdate TIMESTAMP);";

const char DEVICENAME[] = "DeviceName";
const char DEVICENAME_CREATE[] = "CREATE TABLE DeviceName (" \
        "Id INTEGER PRIMARY KEY, " \
        "Name VARCHAR, " \
        "LastUpdate TIMESTAMP);";

const char PLACE[] = "Place";
const char PLACE_CREATE[] = "CREATE TABLE Place (" \
        "Id INTEGER PRIMARY KEY, " \
        "Name VARCHAR, " \
        "Room VARCHAR, " \
        "Desk VARCHAR, " \
        "LastUpdate TIMESTAMP);";

const char INVENTORY[] = "Inventory";
const char INVENTORY_CREATE[] = "CREATE TABLE Inventory (" \
        "Id INTEGER PRIMARY KEY, " \
        "Number VARCHAR, " \
        "Text VARCHAR, " \
        "Active BOOLEAN, " \
        "LastUpdate TIMESTAMP);";


}

namespace EmployeeTable {}
} // namespace Database
#endif // CONSTANTS_H
