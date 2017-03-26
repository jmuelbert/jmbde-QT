-- ------------------------------------
--
-- Database for JMBDE
-- Version 1.0.1 (c) 2014 Jürgen Mülbert
--
-- V1.0		- 29. December 2013
-- V1.0.1	- 12. Januar 2014
-- V1.1		- 03. March 2017
--
---------------------------------------

---------------------------------------
--
-- Part for a big database system like
-- MySQL or PostgreSQL
--
---------------------------------------
-- DROP SCHEMA IF EXISTS 'jmbde';
-- CREATE SCHEMA IF NOT EXISTS 'jmbde' DEFAULT CHARACTER SET utf8;
-- SHOW WARNINGS;
-- USE 'jmbde';
---------------------------------------
--
-- uncomment above do you use one of
-- of this.
---------------------------------------

BEGIN TRANSACTION;

---------------------------------------
--
-- Create the ZIPCODE Table
-- This Table hold the ZIPCODE in german
-- Postleitzahl of the City
--
---------------------------------------
DROP TABLE IF EXISTS zipcode;

CREATE TABLE IF NOT EXISTS zipcode (
	zipcode_id INTEGER PRIMARY KEY AUTOINCREMENT,
	zipcode VARCHAR(5) NOT NULL,
	last_update TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
);
CREATE UNIQUE INDEX idx_zip ON zipcode (zipcode ASC);

---------------------------------------
--
-- The City Table
--
---------------------------------------
DROP TABLE IF EXISTS cityname;

CREATE TABLE IF NOT EXISTS cityname (
	cityname_id INTEGER PRIMARY KEY AUTOINCREMENT,
	name VARCHAR(50) NOT NULL,
	last_update TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
);
CREATE UNIQUE INDEX idx_cityname ON cityname (name ASC);

---------------------------------------
--
-- The zipcity Table
--
---------------------------------------
DROP TABLE IF EXISTS zipcity;

CREATE TABLE IF NOT EXISTS zipcity (
	cityname_id INTEGER PRIMARY KEY AUTOINCREMENT,
	zipcode_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	city_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	last_update TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
);



---------------------------------------
--
-- The title table
--
---------------------------------------
DROP TABLE IF EXISTS title;

CREATE TABLE IF NOT EXISTS title (
	title_id INTEGER PRIMARY KEY AUTOINCREMENT,
	name VARCHAR(20) NOT NULL,
	last_update TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
);


---------------------------------------
--
-- Create the Table Employee
-- - The title is Dr., Ing. and so on
-- - address is foreign key for the address table
-- - gender (m/w)
-- - birthday of the employee
-- - email address in the company
-- - datacare in german datenschutz (y/n)
--   or TRUE / FALSE
-- - active is the employee real here
-- - startdate  the employee is then here
-- - enddate this is the last day
-- - the foreign key to the department
-- - the foreign key for the function of the employee
-- - the foreign key to the computer
-- - the foreign key to the printer
-- - the foreign key to the inhouse phone
-- - the foreign key to the mobile
-- - the foreign key to the fax
-- - the foreign key to the table of accounts
-- - the foreign key to the table of documents
--
---------------------------------------
DROP TABLE IF EXISTS employee;

CREATE TABLE IF NOT EXISTS employee (
    employee_id INTEGER PRIMARY KEY AUTOINCREMENT,
    employee_nr SMALLINT UNSIGNED NOT NULL,
    gender VARCHAR(1) NOT NULL,
    title_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
    firstname VARCHAR(45),
    lastname VARCHAR(45) NOT NULL,
    birthday DATETIME,
    address VARCHAR(50) NOT NULL,
    zipcity_id SMALLIT UNSIGNED NOT NULL DEFAULT 1,
    homephone VARCHAR(20),
    homemobile VARCHAR(20),
    homeemail VARCHAR(50),
    businessemail VARCHAR(50),
    datacare BOOLEAN NOT NULL DEFAULT FALSE,
    active BOOLEAN NOT NULL DEFAULT TRUE,
    photo BLOB,
    notes VARCHAR(50),
    startdate DATETIME,
    enddate DATETIME,
    department_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
    function_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
    computer_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
    printer_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
    phone_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
    mobile_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
    fax_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
    employee_account_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
    employee_document_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
    chipcard_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
    last_update TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
);

CREATE INDEX idx_employee_employee_nr ON employee (employee_nr ASC);
CREATE INDEX idx_employee_lastname ON employee (lastname ASC);
CREATE INDEX idx_fk_employee_department_id ON employee (department_id ASC);
CREATE INDEX idx_fk_employee_function_id ON employee (function_id ASC);
CREATE INDEX idx_fk_employee_computer_id ON employee (computer_id ASC);
CREATE INDEX idx_fk_employee_printer_id ON employee (printer_id ASC);
CREATE INDEX idx_fk_employee_phone_id ON employee (phone_id ASC);
CREATE INDEX idx_fk_employee_mobile_id ON employee (mobile_id ASC);
CREATE INDEX idx_fk_employee_fax_id ON employee (fax_id ASC);
CREATE INDEX idx_fk_employee_employee_account_id ON employee (employee_account_id ASC);
CREATE INDEX idx_fk_employee_employee_document_id ON employee (employee_document_id ASC);

---------------------------------------
--
-- Table DeviceType
-- :Computer
-- :Network
-- :Pad
-- :Phones
-- :PRINTER
--
---------------------------------------
DROP TABLE IF EXISTS devicetype;

CREATE TABLE IF NOT EXISTS devicetype (
	devicetype_id INTEGER PRIMARY KEY AUTOINCREMENT,
	name VARCHAR(45) NOT NULL,
	last_update TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
);


---------------------------------------
--
-- The Divice Name Table
-- i.e. Gigaset, Optiplex
--
---------------------------------------
DROP TABLE IF EXISTS devicename;

CREATE TABLE IF NOT EXISTS devicename (
	devicename_id INTEGER PRIMARY KEY AUTOINCREMENT,
	name VARCHAR(45) NOT NULL,
	manufacturer_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	last_update TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
);

CREATE INDEX idx_fk_devicename_manufacturer_id ON devicename (manufacturer_id ASC);

---------------------------------------
--
-- Table Place
--  - Place of Employee
--  - Place of Device
--  - The Offices and the Desks in the Office.
--
---------------------------------------
DROP TABLE IF EXISTS place;

CREATE TABLE IF NOT EXISTS place (
	place_id INTEGER PRIMARY KEY AUTOINCREMENT,
	name VARCHAR(45) NOT NULL,
	room VARCHAR(45) NOT NULL,
	desk VARCHAR(45) NOT NULL,
	last_update TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
);

---------------------------------------
--
-- Table Inventory
-- - The Hardware inventory number.
--
---------------------------------------
DROP TABLE IF EXISTS inventory;

CREATE TABLE IF NOT EXISTS inventory (
	inventory_id INTEGER PRIMARY KEY AUTOINCREMENT,
	number VARCHAR(20) NOT NULL,
	text VARCHAR(45) NOT NULL,
	active BOOLEAN DEFAULT TRUE,
	last_update TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
);

---------------------------------------
--
-- Table Manufacturer
-- The Manufacturer of the Hardware
--
-- - The name of the manufacturer (IBM, Dell, Apple, ..)
-- - The name of the support person.
-- - The address for support.
--
---------------------------------------
DROP TABLE IF EXISTS manufacturer;

CREATE TABLE IF NOT EXISTS manufacturer (
	manufacturer_id INTEGER PRIMARY KEY AUTOINCREMENT,
	name VARCHAR(45) NOT NULL,
	name2 VARCHAR(45),
	supporter VARCHAR(45) NOT NULL,
    address VARCHAR(50) NOT NULL,
    address2 VARCHAR(50),
    email VARCHAR(50),
    fax VARCHAR(20),
    hotline VARCHAR(20),
    phone VARCHAR(20),
	zipcity_id SMALLIT UNSIGNED NOT NULL DEFAULT 1,
	last_update TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
);



---------------------------------------
--
-- Table department
-- - like parts store, accounting, service, ...
-- - The name of the department.
-- - the prio for reports
-- - the foreign key for the department printer.
-- - the foreign key for the department fax.
--
---------------------------------------
DROP TABLE IF EXISTS department;

CREATE TABLE IF NOT EXISTS department (
	department_id INTEGER PRIMARY KEY AUTOINCREMENT,
	name VARCHAR(45) NOT NULL,
	prio SMALLINT NULL DEFAULT 1,
	printer_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	fax_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	last_update TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
);

CREATE INDEX idx_fk_department_printer_id ON department (printer_id ASC);
CREATE INDEX idx_fk_department_dax_id ON department (fax_id ASC);

---------------------------------------
--
-- Table function
-- The function of the employee in the company
--
-- - name of the function
-- - prio for reports
---------------------------------------
DROP TABLE IF EXISTS function;

CREATE TABLE IF NOT EXISTS function (
	function_id INTEGER PRIMARY KEY AUTOINCREMENT,
	name VARCHAR(45) NOT NULL,
	prio SMALLINT NULL DEFAULT 1,
	last_update TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
);

---------------------------------------
--
-- Table employeeaccount
-- this is the m:n table for accounts
--
---------------------------------------
DROP TABLE IF EXISTS employeeaccount;

CREATE TABLE IF NOT EXISTS employeeaccount (
	employeeaccount_id INTEGER PRIMARY KEY AUTOINCREMENT,
	employee_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	account_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	last_update TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
);

CREATE INDEX idx_fk_employeeaccount_employee_id ON employeeaccount (employee_id ASC);
CREATE INDEX idx_fk_employeeaccount_account_id ON employeeaccount (account_id ASC);

---------------------------------------
--
-- Table Account
-- - List of accounts for employee's
-- - Systemdata is a list of systems
--   with accounts
--
-- - the foreign key to the system that realize to account
-- - the username for login
-- - the password for login (the start password, the user must change)
---------------------------------------
DROP TABLE IF EXISTS account;

CREATE TABLE IF NOT EXISTS account (
	account_id INTEGER PRIMARY KEY AUTOINCREMENT,
	username VARCHAR(45) NOT NULL,
	password VARCHAR(45) NOT NULL,
	systemdata_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	last_update TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
);

CREATE INDEX idx_fk_account_systemdata ON account (systemdata_id ASC);

---------------------------------------
--
-- Table systemdata
-- - A list of systems with accounts
-- - i.e. Mail, AD-Server ...
--
-- - name of the system
-- - the foreign key to the real place of the system
-- - local if the systen local (TRUE / FALSE)
-- - account_id - back to account. so if posibel to
--   so the accounts from the system.
--
---------------------------------------
DROP TABLE IF EXISTS systemdata;

CREATE TABLE IF NOT EXISTS systemdata (
	systemdata_id INTEGER PRIMARY KEY AUTOINCREMENT,
	name VARCHAR(45) NOT NULL,
	local BOOLEAN DEFAULT TRUE,
	company VARCHAR(45),
	address VARCHAR(45),
	address2 VARCHAR(45),
	account_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	last_update TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
);

CREATE INDEX idx_fk_systemdata_account ON systemdata (account_id ASC);

---------------------------------------
--
-- Table employeedocument
-- this is the m:n table for documents
--
---------------------------------------
DROP TABLE IF EXISTS employeedocument;

CREATE TABLE IF NOT EXISTS employeedocument (
	employeedocument_id INTEGER PRIMARY KEY AUTOINCREMENT,
	employee_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	document_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	last_update TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
);

CREATE INDEX idx_fk_employeedocument_employee ON employeedocument (employee_id ASC);
CREATE INDEX idx_fk_employeedocument_document ON employeedocument (document_id ASC);

---------------------------------------
--
-- Table Documents
-- - hold the documents for the user
-- - account agrees, ...
--
-- - name of the document
-- - documents (scanned)
--
---------------------------------------
DROP TABLE IF EXISTS documents;

CREATE TABLE IF NOT EXISTS documents (
	documents_id INTEGER PRIMARY KEY AUTOINCREMENT,
	name VARCHAR(45) NOT NULL,
	document BLOB NOT NULL,
	last_update TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
);


---------------------------------------
--
-- Table processor
--
-- - name of the processor (I3, I5, XEON, ...)
-- - ghz
-- - cores
---------------------------------------
DROP TABLE IF EXISTS processor;

CREATE TABLE IF NOT EXISTS processor (
	processor_id INTEGER PRIMARY KEY AUTOINCREMENT,
	name VARCHAR(45) NOT NULL,
	ghz DECIMAL NOT NULL,
	cores SMALLINT UNSIGNED DEFAULT 2,
	last_update TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
);

---------------------------------------
--
-- Table os
--
-- - OS is software, there are the same fields
--   but OS is One installed, software many.
--
-- - name of the software (os)
-- - version of the software (os)
-- - revision of the software (os)
-- - fix of the software (os)
-- - i.e. : 1.2.13
---------------------------------------
DROP TABLE IF EXISTS os;

CREATE TABLE IF NOT EXISTS os (
	os_id INTEGER PRIMARY KEY AUTOINCREMENT,
	name VARCHAR(20) NOT NULL,
	version VARCHAR(5) NOT NULL,
	revision VARCHAR(5) NOT NULL,
	fix VARCHAR(10) NULL,
	last_update TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
);

---------------------------------------
--
-- Table computersoftware
-- this is the m:n table for software
--
---------------------------------------
DROP TABLE IF EXISTS computersoftware;

CREATE TABLE IF NOT EXISTS computersoftware (
	computersoftware_id INTEGER PRIMARY KEY AUTOINCREMENT,
	computer_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	software_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	last_update TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
);

CREATE INDEX idx_fk_computersoftware_computer ON computersoftware (computer_id ASC);
CREATE INDEX idx_fk_computersoftware_software ON computersoftware (software_id ASC);

---------------------------------------
--
-- Table software
--
-- - OS is software, there are the same fields
--   but OS is One installed, software many.
--
-- - name of the software (os)
-- - version of the software (os)
-- - revision of the software (os)
-- - fix of the software (os)
-- - i.e. : 1.2.13
---------------------------------------
DROP TABLE IF EXISTS software;

CREATE TABLE IF NOT EXISTS software (
	software_id INTEGER PRIMARY KEY AUTOINCREMENT,
	name VARCHAR(20) NOT NULL,
	version VARCHAR(5) NOT NULL,
	revision VARCHAR(5) NOT NULL,
	fix VARCHAR(10) NULL,
	last_update TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
);

---------------------------------------
--
-- Table Computer
--
-- - name of the computer
-- - serialnumber of the computer
-- - service_tag of the computer
-- - service_number for the quick service
-- - memory size on the computer
-- - network  of the computer
-- - network_name of the computer
-- - network_ipaddress of the computer
-- - active is the computer working
-- - replace should the computer replace
-- - devicetype_id the foreign key to the devicetyp
-- - employee_id the foreign key to the employee - reverse
-- - place_id the foreign key to the place where the computer is
-- - department_id the foreign key the department where the computer is.
-- - manufacturer_id the foreign key to the manufacturer of the computer
-- - inventory_id the foreign key to the inventory
-- - processor_id the foreign key to the processor
-- - os_id the foreign key to the os
-- - computersoftware_id foreign key to the m:n table software
-- - printer_id the foreign key to the printer
--
---------------------------------------
DROP TABLE IF EXISTS computer;

CREATE TABLE IF NOT EXISTS computer (
	computer_id INTEGER PRIMARY KEY NOT NULL,
	devicename_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	serialnumber VARCHAR(20) NOT NULL,
	service_tag VARCHAR(20) NOT NULL,
	service_number VARCHAR(20) DEFAULT NULL,
	memory SMALLINT UNSIGNED DEFAULT 4096,
	network VARCHAR(45) NOT NULL,
	network_name VARCHAR(30) NOT NULL,
	network_ipaddress VARCHAR(30) NOT NULL,
	active BOOLEAN DEFAULT TRUE,
	replace BOOLEAN DEFAULT FALSE,
	devicetype_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	employee_id SMALLINT UNSIGNED DEFAULT NULL DEFAULT 1,
	place_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	department_id SMALLINT UNSIGNET NOT NULL DEFAULT 1,
	manufacturer_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	inventory_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	processor_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	os_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	computersoftware_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	printer_id SMALLINT UNSIGNED DEFAULT NULL DEFAULT 1,
	last_update TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
	CONSTRAINT "FK_Computer_Employee_EmployeeId" FOREIGN KEY ("employee_id") REFERENCES "employee" ("employee_id") ON DELETE CASCADE
);

CREATE INDEX idx_fk_computer_devicename ON computer (devicename_id ASC);
CREATE INDEX idx_fk_computer_devicetype ON computer (devicetype_id ASC);
CREATE INDEX idx_fk_computer_employee ON computer (employee_id ASC);
CREATE INDEX idx_fk_computer_place ON computer (place_id ASC);
CREATE INDEX idx_fk_computer_department ON computer (department_id ASC);
CREATE INDEX idx_fk_computer_manufacturer ON computer (manufacturer_id ASC);
CREATE INDEX idx_fk_computer_inventory ON computer (inventory_id ASC);
CREATE INDEX idx_fk_computer_processor ON computer (processor_id ASC);
CREATE INDEX idx_fk_computer_os ON computer (os_id ASC);
CREATE INDEX idx_fk_computer_computersoftware ON computer (computersoftware_id ASC);
CREATE INDEX idx_fk_computer_printer ON computer (printer_id ASC);

---------------------------------------
--
-- Table Printer
--
-- - name of the printer
-- - serialnumber of the printer
-- - number if the printer a fax
-- - network  of the printer
-- - network_name of the printer
-- - network_ipaddress of the printer
-- - active is the printer is working
-- - replace should the printer replace
-- - resources - Toner and so
-- - papersize_max - A3, A4, ...
-- - devicetype_id the foreign key to the devicetyp
-- - employee_id the foreign key to the employee - reverse
-- - place_id the foreign key to the place where the printer is
-- - department_id the foreign key the department where the printer is.
-- - manufacturer_id the foreign key to the manufacturer of the printer
-- - inventory_id the foreign key to the inventory
-- - computer_id the foreign key to the computer - reverse.
-- - printer_id the foreign key to the printer
--
---------------------------------------
DROP TABLE IF EXISTS printer;

CREATE TABLE IF NOT EXISTS printer (
	printer_id INTEGER PRIMARY KEY AUTOINCREMENT,
	devicename_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	serialnumber VARCHAR(20) NOT NULL,
	network VARCHAR(45) NOT NULL,
	network_name VARCHAR(30) NOT NULL,
	network_ipaddress VARCHAR(30) NOT NULL,
	active BOOLEAN DEFAULT TRUE,
	replace BOOLEAN DEFAULT FALSE,
	resources VARCHAR(45) NOT NULL,
	papersize_max VARCHAR(5) NOT NULL,
	color BOOLEAN DEFAULT FALSE,			
	devicetype_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	employee_id SMALLINT UNSIGNED DEFAULT NULL DEFAULT 1,
	place_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	department_id SMALLINT UNSIGNET NOT NULL DEFAULT 1,
	manufacturer_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	inventory_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	computer_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	last_update TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
);

CREATE INDEX idx_printer_network_name ON printer (network_name ASC);
CREATE INDEX idx_printer_network_ipaddress ON printer (network_ipaddress ASC);
CREATE INDEX idx_fk_printer_devicename ON printer (devicename_id ASC);
CREATE INDEX idx_fk_printer_devicetype ON printer (devicetype_id ASC);
CREATE INDEX idx_fk_printer_employee ON printer (employee_id ASC);
CREATE INDEX idx_fk_printer_place ON printer (place_id ASC);
CREATE INDEX idx_fk_printer_department ON printer (department_id ASC);
CREATE INDEX idx_fk_printer_manufacturer ON printer (manufacturer_id ASC);
CREATE INDEX idx_fk_printer_inventory ON printer (inventory_id ASC);
CREATE INDEX idx_fk_printer_computer ON printer (computer_id ASC);


---------------------------------------
--
-- Table phone
-- phone, handset and mobile
--
-- - name
-- - serialnumber of the phone
-- - number of the phone
-- - pin for the phone
-- - devicetype_id the foreign key to the devicetyp
-- - employee_id the foreign key to the the employee
-- - place_id the foreign key place where the phone is.
-- - department_id the foreign key to department
-- - manufacturer_id the foreign key to the manufacturer
-- - inventory_id the foreign key to the inventory
--
---------------------------------------
DROP TABLE IF EXISTS phone;

CREATE TABLE IF NOT EXISTS phone (
	phone_id INTEGER PRIMARY KEY AUTOINCREMENT,
	devicename_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	serialnumber VARCHAR(20) NOT NULL,
	number VARCHAR(20) NOT NULL,
	pin VARCHAR(20) DEFAULT NULL,
	active BOOLEAN DEFAULT TRUE,
	replace BOOLEAN DEFAULT FALSE,
	devicetype_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	employee_id SMALLINT UNSIGNED DEFAULT NULL DEFAULT 1,
	place_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	department_id SMALLINT UNSIGNET NOT NULL DEFAULT 1,
	manufacturer_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	inventory_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	last_update TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
	CONSTRAINT "FK_Phone_Employee_EmployeeId" FOREIGN KEY ("employee_id") REFERENCES "employee" ("employee_id") ON DELETE CASCADE

);

CREATE INDEX idx_fk_phone_devicename ON phone (devicename_id ASC);
CREATE INDEX idx_fk_phone_devicetype ON phone (devicetype_id ASC);
CREATE INDEX idx_fk_phone_employee ON phone (employee_id ASC);
CREATE INDEX idx_fk_phone_place ON phone (place_id ASC);
CREATE INDEX idx_fk_phone_department ON phone (department_id ASC);
CREATE INDEX idx_fk_phone_manufacturer ON phone (manufacturer_id ASC);
CREATE INDEX idx_fk_phone_inventory ON phone (inventory_id ASC);

---------------------------------------
--
-- Table fax
--
-- - name
-- - serialnumber of the fax
-- - number of the fax
-- - pin for the fax
-- - devicetype_id the foreign key to the devicetyp
-- - employee_id the foreign key to the the employee
-- - place_id the foreign key place where the phone is.
-- - department_id the foreign key to department
-- - manufacturer_id the foreign key to the manufacturer
-- - inventory_id the foreign key to the inventory
-- - printer_id the foreign key for the printer
--
---------------------------------------
DROP TABLE IF EXISTS fax;

CREATE TABLE IF NOT EXISTS fax (
	fax_id INTEGER PRIMARY KEY AUTOINCREMENT,
	devicename_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	serialnumber VARCHAR(20) NOT NULL,
	number VARCHAR(20) NOT NULL,
	pin VARCHAR(20) DEFAULT NULL,
	active BOOLEAN DEFAULT TRUE,
	replace BOOLEAN DEFAULT FALSE,
	devicetype_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	employee_id SMALLINT UNSIGNED DEFAULT NULL DEFAULT 1,
	place_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	department_id SMALLINT UNSIGNET NOT NULL DEFAULT 1,
	manufacturer_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	inventory_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	printer_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	last_update TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
);

CREATE INDEX idx_fk_fax_devicename ON fax (devicename_id ASC);
CREATE INDEX idx_fk_fax_devicetype ON fax (devicetype_id ASC);
CREATE INDEX idx_fk_fax_employee ON fax (employee_id ASC);
CREATE INDEX idx_fk_fax_place ON fax (place_id ASC);
CREATE INDEX idx_fk_fax_department ON fax (department_id ASC);
CREATE INDEX idx_fk_fax_manufacturer ON fax (manufacturer_id ASC);
CREATE INDEX idx_fk_fax_inventory ON fax (inventory_id ASC);
CREATE INDEX idx_fk_fax_printer_id ON fax (printer_id ASC);


---------------------------------------
--
-- Table mobile
--
-- - name
-- - serialnumber of the mobile
-- - number of the mobile
-- - pin for the mobile
-- - devicetype_id the foreign key to the devicetyp
-- - employee_id the foreign key to the the employee
-- - place_id the foreign key place where the phone is.
-- - department_id the foreign key to department
-- - manufacturer_id the foreign key to the manufacturer
-- - inventory_id the foreign key to the inventory
--
---------------------------------------
DROP TABLE IF EXISTS mobile;

CREATE TABLE IF NOT EXISTS mobile (
	mobile_id INTEGER PRIMARY KEY AUTOINCREMENT,
	devicename_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	serialnumber VARCHAR(20) NOT NULL,
	number VARCHAR(20) NOT NULL,
	cardnumber VARCHAR(20),
	activatedate DATE,
	pin VARCHAR(20) DEFAULT NULL,
	active BOOLEAN DEFAULT TRUE,
	replace BOOLEAN DEFAULT FALSE,
	devicetype_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	employee_id SMALLINT UNSIGNED DEFAULT NULL DEFAULT 1,
	place_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	department_id SMALLINT UNSIGNET NOT NULL DEFAULT 1,
	manufacturer_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	inventory_id SMALLINT UNSIGNED NOT NULL DEFAULT 1,
	last_update TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
	CONSTRAINT "FK_Mobile_Employee_EmployeeId" FOREIGN KEY ("employee_id") REFERENCES "employee" ("employee_id") ON DELETE CASCADE

);

CREATE INDEX idx_fk_mobile_devicename ON mobile (devicename_id ASC);
CREATE INDEX idx_fk_mobile_devicetype ON mobile (devicetype_id ASC);
CREATE INDEX idx_fk_mobile_employee ON mobile (employee_id ASC);
CREATE INDEX idx_fk_mobile_place ON mobile (place_id ASC);
CREATE INDEX idx_fk_mobile_department ON mobile (department_id ASC);
CREATE INDEX idx_fk_mobile_manufacturer ON mobile (manufacturer_id ASC);
CREATE INDEX idx_fk_mobile_inventory ON mobile (inventory_id ASC);

---------------------------------------
--
-- Table DB Version
-- This is checked by the programstart.
-- if the version in the program newer must
-- maybe update the database to a newer
-- version.
--
---------------------------------------
DROP TABLE IF EXISTS databaseversion;

CREATE TABLE IF NOT EXISTS databaseversion (
	databaseversion_id INTEGER PRIMARY KEY AUTOINCREMENT,
	version SMALLINT UNSIGNED DEFAULT 1,
	revision SMALLINT UNSIGNED DEFAULT 0,
	patch SMALLINT UNSIGNED DEFAULT 0,
	last_update TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
);

---------------------------------------
--
-- Views
--
---------------------------------------

--
-- SET My Version
--
--------------------------------------
INSERT INTO databaseversion VALUES(1,1,0,0,'2013-12-29');
COMMIT;