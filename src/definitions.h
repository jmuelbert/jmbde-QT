/*
// definitions.h
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

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <QtGlobal>

#define APP_ICON_PATH QStringLiteral(":/graphics/jmbde.png")

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
const char ZIPCODE_CREATE[] = "CREATE TABLE ZipCode (" \
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
const char TITLE_CREATE[] = "CREATE TABLE Title (" \
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
        "Address VARCHAR, " \
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

const char MANIFACTURER[] = "Manufacturer";
const char MANIFACTURER_CREATE[] = "CREATE TABLE Manufacturer (" \
        "Id INTEGER PRIMARY KEY, " \
        "Name VARCHAR, " \
        "Name2 VARCHAR, " \
        "Supporter VARCHAR, " \
        "Address VARCHAR, " \
        "Address2 VARCHAR, " \
        "ZipCityID INTEGER, " \
        "EMail VARCHAR, " \
        "Phone VARCHAR, " \
        "Fax VARCHAR, " \
        "Hotline VARCHAR, " \
        "LastUpdate TIMESTAMP);";


const char DEPARTMENT[] = "Department";
const char DEPARTMENT_CREATE[] = "CREATE TABLE Department (" \
        "Id INTEGER PRIMARY KEY, " \
        "Name VARCHAR, " \
        "PRIO INTEGER, " \
        "PrinterID INTEGER, " \
        "FaxID INTEGER, " \
        "LastUpdate TIMESTAMP);";

const char FUNCTION[] = "Function";
const char FUNCTION_CREATE[] = "CREATE TABLE Function (" \
        "Id INTEGER PRIMARY KEY, " \
        "Name VARCHAR, " \
        "PRIO INTEGER, " \
        "LastUpdate TIMESTAMP);";

const char EMPLOYEEACCOUNT[] = "EmployeeAccount";
const char EMPLOYEEACCOUNT_CREATE[] = "CREATE TABLE EmployeeAccount (" \
        "Id INTEGER PRIMARY KEY, " \
        "EmployeID INTEGER, " \
        "AccountID INTEGER, " \
        "LastUpdate TIMESTAMP);";

const char ACCOUNT[] = "Account";
const char ACCOUNT_CREATE[] = "CREATE TABLE Account (" \
        "Id INTEGER PRIMARY KEY, " \
        "UserName VARCHAR, " \
        "PassWord VARCHAR, " \
        "SystemDataID INTEGER, " \
        "LastUpdate TIMESTAMP);";

const char SYSTEMDATA[] = "SystemData";
const char SYSTEMDATA_CREATE[] = "CREATE TABLE SystemData (" \
        "Id INTEGER PRIMARY KEY, " \
        "Name VARCHAR, " \
        "Local BOOLEAN, " \
        "Company VARCHAR, " \
        "Address VARCHAR, " \
        "Address2 VARCHAR, " \
        "ZipCityID INTEGER, " \
        "LastUpdate TIMESTAMP);";

const char EMPLOYEEDOCUMENT[] = "EmployeeDocument";
const char EMPLOYEEDOCUMENT_CREATE[] = "CREATE TABLE EmployeeDocument (" \
        "Id INTEGER PRIMARY KEY, " \
        "EmployeID INTEGER, " \
        "DocumentID INTEGER, " \
        "LastUpdate TIMESTAMP);";

const char DOCUMENTS[] = "Documents";
const char DOCUMENTS_CREATE[] = "CREATE TABLE Documents (" \
        "Id INTEGER PRIMARY KEY, " \
        "Name VARCHAR, " \
        "Document BLOB, " \
        "LastUpdate TIMESTAMP);";

const char PROCESSOR[] = "Processor";
const char PROCESSOR_CREATE[] = "CREATE TABLE Processor (" \
        "Id INTEGER PRIMARY KEY, " \
        "Name VARCHAR, " \
        "GHZ DECIMAL, " \
        "CORES INTEGER, " \
        "LastUpdate TIMESTAMP);";

const char OS[] = "OS";
const char OS_CREATE[] = "CREATE TABLE OS (" \
        "Id INTEGER PRIMARY KEY, " \
        "Name VARCHAR, " \
        "Version VARCHAR, " \
        "Revision VARCHAR, " \
        "Fix VARCHAR, " \
        "LastUpdate TIMESTAMP);";

const char COMPUTERSOFTWARE[] = "ComputerSoftware";
const char COMPUTERSOFTWARE_CREATE[] = "CREATE TABLE ComputerSoftware (" \
        "Id INTEGER PRIMARY KEY, " \
        "ComputerID INTEGER, " \
        "SoftwareID INTEGER, " \
        "LastUpdate TIMESTAMP);";

const char SOFTWARE[] = "Software";
const char SOFTWARE_CREATE[] = "CREATE TABLE Software (" \
        "Id INTEGER PRIMARY KEY, " \
        "Name VARCHAR, " \
        "Version VARCHAR, " \
        "Revision VARCHAR, " \
        "Fix VARCHAR, " \
        "LastUpdate TIMESTAMP);";

const char COMPUTER[] = "Computer";
const char COMPUTER_CREATE[] = "CREATE TABLE Computer (" \
        "Id INTEGER PRIMARY KEY, " \
        "DeviceNameID INTEGER, " \
        "SerialNumber VARCHAR, " \
        "ServiceTag VARCHAR, " \
        "ServiceNumber VARCHAR, " \
        "Memory INTEGER, " \
        "Network VARCHAR, " \
        "NetworkName VARCHAR, " \
        "NetworkIPAddress VARCHAR, " \
        "Active BOOLEAN, " \
        "Replace BOOLEAN, " \
        "DeviceTypeID INTEGER, " \
        "EmployeID INTEGER, " \
        "PlaceID INTEGER, " \
        "DepartmentID INTEGER, " \
        "ManufacturerID INTEGER, " \
        "InventoryID INTEGER, " \
        "ProcessorID INTEGER, " \
        "OSID INTEGER, " \
        "ComputerSoftwareID INTEGER, " \
        "PrinterID INTEGER, " \
        "LastUpdate TIMESTAMP);";

const char PRINTER[] = "Printer";
const char PRINTER_CREATE[] = "CREATE TABLE Printer (" \
        "Id INTEGER PRIMARY KEY, " \
        "DeviceNameID INTEGER, " \
        "SerialNumber VARCHAR, " \
        "Network VARCHAR, " \
        "NetworkName VARCHAR, " \
        "NetworkIPAddress VARCHAR, " \
        "Active BOOLEAN, " \
        "Replace BOOLEAN, " \
        "Resources VARCHAR, " \
        "PaperSizeMax VARCHAR, " \
        "Color BOOLEAN, " \
        "DeviceTypeID INTEGER, " \
        "EmployeID INTEGER, " \
        "PlaceID INTEGER, " \
        "DepartmentID INTEGER, " \
        "ManufacturerID INTEGER, " \
        "InventoryID INTEGER, " \
        "ComputerID INTEGER, " \
        "LastUpdate TIMESTAMP);";

const char PHONE[] = "Phone";
const char PHONE_CREATE[] = "CREATE TABLE Phone (" \
        "Id INTEGER PRIMARY KEY, " \
        "DeviceNameID INTEGER, " \
        "SerialNumber VARCHAR, " \
        "Number VARCHAR, " \
        "Pin VARCHAR, " \
        "Active BOOLEAN, " \
        "Replace BOOLEAN, " \
        "DeviceTypeID INTEGER, " \
        "EmployeID INTEGER, " \
        "PlaceID INTEGER, " \
        "DepartmentID INTEGER, " \
        "ManufacturerID INTEGER, " \
        "InventoryID INTEGER, " \
        "LastUpdate TIMESTAMP);";

const char FAX[] = "Fax";
const char FAX_CREATE[] = "CREATE TABLE Fax (" \
        "Id INTEGER PRIMARY KEY, " \
        "DeviceNameID INTEGER, " \
        "SerialNumber VARCHAR, " \
        "Number VARCHAR, " \
        "Pin VARCHAR, " \
        "Active BOOLEAN, " \
        "Replace BOOLEAN, " \
        "DeviceTypeID INTEGER, " \
        "EmployeID INTEGER, " \
        "PlaceID INTEGER, " \
        "DepartmentID INTEGER, " \
        "ManufacturerID INTEGER, " \
        "InventoryID INTEGER, " \
        "LastUpdate TIMESTAMP);";

const char MOBILE[] = "Mobile";
const char MOBILE_CREATE[] = "CREATE TABLE Mobile (" \
        "Id INTEGER PRIMARY KEY, " \
        "DeviceNameID INTEGER, " \
        "SerialNumber VARCHAR, " \
        "Number VARCHAR, " \
        "CardNumber VARCHAR, " \
        "Active BOOLEAN, " \
        "Replace BOOLEAN, " \
        "DeviceTypeID INTEGER, " \
        "EmployeID INTEGER, " \
        "PlaceID INTEGER, " \
        "DepartmentID INTEGER, " \
        "ManufacturerID INTEGER, " \
        "InventoryID INTEGER, " \
        "LastUpdate TIMESTAMP);";

const char DATABASEVERSION[] = "DatabaseVersion";
const char DATABASEVERSION_CREATE[] = "CREATE TABLE DatabaseVersion ("
        "Id INTEGER PRIMARY KEY, " \
        "Version VARCHAR, " \
        "Revision VARCHAR, " \
        "Path VARCHAR, " \
        "LastUpdate TIMESTAMP);";
}

namespace EmployeeTable {}
} // namespace Database
#endif // DEFINITIONS_H
