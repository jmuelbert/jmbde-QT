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
    const char LAST_VIEW[] = "last_view";
    const char LAST_DATA[] = "last_data";
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

  namespace Version {
    const char Version[] = "0";
    const char Revision[] = "90";
    const char Patch[] = "0";
  }

  namespace Type {
    const char SQLITE[] = "SqLite";
    const char MYSQL[] = "MySql";
    const char ODBC[] = "ODBC";
    const char POSTGRESQL[] = "PostgreSQL";
    const char DEFAULT[] = "SqLite";

  } // namespace Type

  namespace Table {
    const char COMPANY[] = "company";
    const char COMPANY_CREATE[] = "CREATE TABLE company (" \
                                  "company_id INTEGER PRIMARY KEY, " \
                                  "name VARCHAR, " \
                                  "name2 VARCHAR, " \
                                  "street VARCHAR, " \
                                  "city VARCHAR, " \
                                  "zip_code VARCHAR(10), " \
                                  "phone_number VARCHAR, " \
                                  "fax_number VARCHAR, " \
                                  "mobile_number VARCHAR, " \
                                  "mail_address VARCHAR, " \
                                  "active BOOLEAN, " \
                                  "employee_id INTEGER, " \
                                  "last_update TIMESTAMP);";
    const char ZIPCODE[] = "zip_code";
    const char ZIPCODE_CREATE[] = "CREATE TABLE zip_code (" \
                                  "zip_code_id INTEGER PRIMARY KEY, " \
                                  "code VARCHAR(10), " \
                                  "last_update TIMESTAMP);";
    const char CITYNAME[] = "city_name";
    const char CITYNAME_CREATE[] = "CREATE TABLE city_name (" \
                                   "city_name_id INTEGER PRIMARY KEY, " \
                                   "name VARCHAR, " \
                                   "last_update TIMESTAMP);";
    const char ZIPCITY[] = "zip_city";
    const char ZIPCITY_CREATE[] = "CREATE TABLE zip_city (" \
                                  "zip_city_id INTEGER PRIMARY KEY, " \
                                  "zip_code_id INTEGER, " \
                                  "city_id INTEGER, " \
                                  "last_update TIMESTAMP);";
    const char TITLE[] = "title";
    const char TITLE_CREATE[] = "CREATE TABLE title (" \
                                "title_id INTEGER PRIMARY KEY, " \
                                "name VARCHAR(50), " \
                                "from_date DATE " \
                                "to_date DATE, "  \
                                "last_update TIMESTAMP);";
    const char EMPLOYEE[] = "employee";
    const char EMPLOYEE_CREATE[] = "CREATE TABLE employee (" \
                                   "employee_id INTEGER PRIMARY KEY, " \
                                   "employee_nr INTEGER, " \
                                   "gender INTEGER, " \
                                   "title_id INTEGER, " \
                                   "first_name VARCHAR, " \
                                   "last_name VARCHAR, " \
                                   "birth_day DATE, " \
                                   "address VARCHAR, " \
                                   "zip_city_id INTEGER, " \
                                   "home_phone VARCHAR, " \
                                   "home_mobile VARCHAR, " \
                                   "home_mail_address VARCHAR, " \
                                   "business_mail_address VARCHAR, " \
                                   "data_care BOOLEAN, " \
                                   "active BOOLEAN, " \
                                   "photo BLOB, " \
                                   "notes VARCHAR, " \
                                   "hire_date DATE, " \
                                   "end_date DATE, " \
                                   "department_id INTEGER, " \
                                   "function_id INTEGER, " \
                                   "computer_id INTEGER, " \
                                   "printer_id INTEGER, " \
                                   "phone_id INTEGER, " \
                                   "mobile_id INTEGER, " \
                                   "fax_id INTEGER, " \
                                   "employee_account_id INTEGER, " \
                                   "employee_document_id INTGER, " \
                                   "chip_card_id INTEGER, " \
                                   "last_update TIMESTAMP);";
    const char DEVICETYPE[] = "device_type";
    const char DEVICETYPE_CREATE[] = "CREATE TABLE device_type (" \
                                     "device_type_id INTEGER PRIMARY KEY, " \
                                     "name VARCHAR, " \
                                     "last_update TIMESTAMP);";
    const char DEVICENAME[] = "device_name";
    const char DEVICENAME_CREATE[] = "CREATE TABLE device_name (" \
                                     "device_name_id INTEGER PRIMARY KEY, " \
                                     "name VARCHAR, " \
                                     "last_update TIMESTAMP);";
    const char PLACE[] = "place";
    const char PLACE_CREATE[] = "CREATE TABLE place (" \
                                "place_id INTEGER PRIMARY KEY, " \
                                "name VARCHAR, " \
                                "room VARCHAR, " \
                                "desk VARCHAR, " \
                                "last_update TIMESTAMP);";
    const char INVENTORY[] = "inventory";
    const char INVENTORY_CREATE[] = "CREATE TABLE inventory (" \
                                    "inventory_id INTEGER PRIMARY KEY, " \
                                    "number VARCHAR, " \
                                    "text VARCHAR, " \
                                    "active BOOLEAN, " \
                                    "last_update TIMESTAMP);";
    const char MANUFACTURER[] = "manufacturer";
    const char MANUFACTURER_CREATE[] = "CREATE TABLE manufacturer (" \
                                       "manufacturer_id INTEGER PRIMARY KEY, " \
                                       "name VARCHAR, " \
                                       "name2 VARCHAR, " \
                                       "supporter VARCHAR, " \
                                       "address VARCHAR, " \
                                       "address2 VARCHAR, " \
                                       "zip_city_id INTEGER, " \
                                       "mail_address VARCHAR, " \
                                       "phone_number VARCHAR, " \
                                       "fax_number VARCHAR, " \
                                       "hotline_number VARCHAR, " \
                                       "last_update TIMESTAMP);";
    const char DEPARTMENT[] = "department";
    const char DEPARTMENT_CREATE[] = "CREATE TABLE department (" \
                                     "department_id INTEGER PRIMARY KEY, " \
                                     "name VARCHAR, " \
                                     "priority INTEGER, " \
                                     "printer_id INTEGER, " \
                                     "fax_id INTEGER, " \
                                     "last_update TIMESTAMP);";
    const char FUNCTION[] = "function";
    const char FUNCTION_CREATE[] = "CREATE TABLE function (" \
                                   "function_id INTEGER PRIMARY KEY, " \
                                   "name VARCHAR, " \
                                   "priority INTEGER, " \
                                   "last_update TIMESTAMP);";
    const char EMPLOYEEACCOUNT[] = "employee_account";
    const char EMPLOYEEACCOUNT_CREATE[] = "CREATE TABLE employee_account (" \
                                          "employee_account_id INTEGER PRIMARY KEY, " \
                                          "employe_id INTEGER, " \
                                          "account_id INTEGER, " \
                                          "last_update TIMESTAMP);";
    const char ACCOUNT[] = "account";
    const char ACCOUNT_CREATE[] = "CREATE TABLE account (" \
                                  "account_id INTEGER PRIMARY KEY, " \
                                  "user_name VARCHAR, " \
                                  "password VARCHAR, " \
                                  "system_data_id INTEGER, " \
                                  "last_update TIMESTAMP);";
    const char SYSTEMDATA[] = "system_data";
    const char SYSTEMDATA_CREATE[] = "CREATE TABLE system_data (" \
                                     "system_data_id INTEGER PRIMARY KEY, " \
                                     "name VARCHAR, " \
                                     "local BOOLEAN, " \
                                     "company_id INTEGER, " \
                                     "last_update TIMESTAMP);";
    const char EMPLOYEEDOCUMENT[] = "employee_document";
    const char EMPLOYEEDOCUMENT_CREATE[] = "CREATE TABLE employee_document (" \
                                           "employee_document_id INTEGER PRIMARY KEY, " \
                                           "employe_id INTEGER, " \
                                           "document_id INTEGER, " \
                                           "last_update TIMESTAMP);";
    const char DOCUMENTS[] = "document";
    const char DOCUMENTS_CREATE[] = "CREATE TABLE document (" \
                                    "document_id INTEGER PRIMARY KEY, " \
                                    "name VARCHAR, " \
                                    "document_data BLOB, " \
                                    "last_update TIMESTAMP);";
    const char PROCESSOR[] = "processor";
    const char PROCESSOR_CREATE[] = "CREATE TABLE processor (" \
                                    "processor_id INTEGER PRIMARY KEY, " \
                                    "name VARCHAR, " \
                                    "clock_rate DECIMAL, " \
                                    "cores INTEGER, " \
                                    "last_update TIMESTAMP);";
    const char OS[] = "os";
    const char OS_CREATE[] = "CREATE TABLE os (" \
                             "os_id INTEGER PRIMARY KEY, " \
                             "name VARCHAR, " \
                             "version VARCHAR, " \
                             "revision VARCHAR, " \
                             "fix VARCHAR, " \
                             "last_update TIMESTAMP);";
    const char COMPUTERSOFTWARE[] = "computer_software";
    const char COMPUTERSOFTWARE_CREATE[] = "CREATE TABLE computer_software (" \
                                           "computer_software_id INTEGER PRIMARY KEY, " \
                                           "computer_id INTEGER, " \
                                           "software_id INTEGER, " \
                                           "last_update TIMESTAMP);";
    const char SOFTWARE[] = "software";
    const char SOFTWARE_CREATE[] = "CREATE TABLE software (" \
                                   "software_id INTEGER PRIMARY KEY, " \
                                   "name VARCHAR, " \
                                   "version VARCHAR, " \
                                   "revision VARCHAR, " \
                                   "fix VARCHAR, " \
                                   "last_update TIMESTAMP);";
    const char COMPUTER[] = "computer";
    const char COMPUTER_CREATE[] = "CREATE TABLE computer (" \
                                   "computer_id INTEGER PRIMARY KEY, " \
                                   "device_name_id INTEGER, " \
                                   "serial_number VARCHAR, " \
                                   "service_tag VARCHAR, " \
                                   "service_number VARCHAR, " \
                                   "memory INTEGER, " \
                                   "network VARCHAR, " \
                                   "network_name VARCHAR, " \
                                   "network_ip_address VARCHAR, " \
                                   "active BOOLEAN, " \
                                   "replace BOOLEAN, " \
                                   "device_type_id INTEGER, " \
                                   "employe_id INTEGER, " \
                                   "place_id INTEGER, " \
                                   "department_id INTEGER, " \
                                   "manufacturer_id INTEGER, " \
                                   "inventory_id INTEGER, " \
                                   "processor_id INTEGER, " \
                                   "os_id INTEGER, " \
                                   "computer_software_id INTEGER, " \
                                   "printer_id INTEGER, " \
                                   "last_update TIMESTAMP);";
    const char PRINTER[] = "printer";
    const char PRINTER_CREATE[] = "CREATE TABLE printer (" \
                                  "printer_id INTEGER PRIMARY KEY, " \
                                  "device_name_id INTEGER, " \
                                  "serial_number VARCHAR, " \
                                  "network VARCHAR, " \
                                  "network_name VARCHAR, " \
                                  "network_ip_address VARCHAR, " \
                                  "active BOOLEAN, " \
                                  "replace BOOLEAN, " \
                                  "resources VARCHAR, " \
                                  "paper_size_max VARCHAR, " \
                                  "color BOOLEAN, " \
                                  "device_type_id INTEGER, " \
                                  "employe_id INTEGER, " \
                                  "place_id INTEGER, " \
                                  "department_id INTEGER, " \
                                  "manufacturer_id INTEGER, " \
                                  "inventory_id INTEGER, " \
                                  "computer_id INTEGER, " \
                                  "last_update TIMESTAMP);";
    const char PHONE[] = "phone";
    const char PHONE_CREATE[] = "CREATE TABLE phone (" \
                                "phone_id INTEGER PRIMARY KEY, " \
                                "device_name_id INTEGER, " \
                                "serial_number VARCHAR, " \
                                "Number VARCHAR, " \
                                "pin VARCHAR, " \
                                "active BOOLEAN, " \
                                "replace BOOLEAN, " \
                                "device_type_id INTEGER, " \
                                "employe_id INTEGER, " \
                                "place_id INTEGER, " \
                                "department_id INTEGER, " \
                                "manufacturer_id INTEGER, " \
                                "inventory_id INTEGER, " \
                                "last_update TIMESTAMP);";
    const char FAX[] = "fax";
    const char FAX_CREATE[] = "CREATE TABLE fax (" \
                              "fax_id INTEGER PRIMARY KEY, " \
                              "device_name_id INTEGER, " \
                              "serial_number VARCHAR, " \
                              "number VARCHAR, " \
                              "pin VARCHAR, " \
                              "active BOOLEAN, " \
                              "replace BOOLEAN, " \
                              "device_type_id INTEGER, " \
                              "employe_id INTEGER, " \
                              "place_id INTEGER, " \
                              "department_id INTEGER, " \
                              "manufacturer_id INTEGER, " \
                              "inventory_id INTEGER, " \
                              "last_update TIMESTAMP);";
    const char MOBILE[] = "mobile";
    const char MOBILE_CREATE[] = "CREATE TABLE mobile (" \
                                 "mobile_id INTEGER PRIMARY KEY, " \
                                 "device_name_id INTEGER, " \
                                 "serial_number VARCHAR, " \
                                 "number VARCHAR, " \
                                 "card_number VARCHAR, " \
                                 "active BOOLEAN, " \
                                 "replace BOOLEAN, " \
                                 "device_type_id INTEGER, " \
                                 "employe_id INTEGER, " \
                                 "place_id INTEGER, " \
                                 "department_id INTEGER, " \
                                 "manufacturer_ID INTEGER, " \
                                 "inventoryid INTEGER, " \
                                 "last_update TIMESTAMP);";
    const char CHIPCARD[] = "chip_card";
    const char CHIPCARD_CREATE[] = "CREATE TABLE chip_card (" \
                                   "chip_card_id INTEGER PRIMARY KEY, " \
                                   "number VARCHAR(10), " \
                                   "chip_card_door_id INTEGER, " \
                                   "chip_card_profile_id INTEGER, " \
                                   "employee_id INTEGER, " \
                                   "last_update TIMESTAMP);";
    const char CHIPCARDDOOR[] = "chip_card_door";
    const char CHIPCARDDOOR_CREATE[] = "CREATE TABLE chip_card_door (" \
                                       "chip_card_door_id INTEGER PRIMARY KEY, " \
                                       "number VARCHAR(10), " \
                                       "place_id INTEGER, " \
                                       "department_id INTEGER, " \
                                       "employee_id INTEGER, " \
                                       "last_update TIMESTAMP);";
    const char CHIPCARDPROFILE[] = "chip_card_profile";
    const char CHIPCARDPROFILE_CREATE[] = "CREATE TABLE chip_card_profile (" \
                                          "chip_card_profile_id INTEGER PRIMARY KEY, " \
                                          "number VARCHAR(10), " \
                                          "chip_card_door_id INTEGER, " \
                                          "employee_id INTEGER, " \
                                          "last_update TIMESTAMP);";
    const char CHIPCARDPROFILEDOOR[] = "chip_card_profile_door";
    const char CHIPCARDPROFILEDOOR_CREATE[] = "CREATE TABLE chip_card_profile_door (" \
                                              "chip_card_profile_door_id INTEGER PRIMARY KEY, " \
                                              "chip_card_profile_id INTEGER, " \
                                              "chip_card_doors_id INTEGER, " \
                                              "last_update TIMESTAMP);";
    const char DATABASEVERSION[] = "database_version";
    const char DATABASEVERSION_CREATE[] = "CREATE TABLE database_version ("
                                          "database_version_id INTEGER PRIMARY KEY, " \
                                          "version VARCHAR(10), " \
                                          "revision VARCHAR(10), " \
                                          "patch VARCHAR(10), " \
                                          "last_update TIMESTAMP);";
  }

  namespace EmployeeTable {}
} // namespace Database
#endif // DEFINITIONS_H
