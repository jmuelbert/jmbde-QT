-- ------------------------------------
--
-- Database for JMBDE
-- Version 1.0.1 (c) 2014 Jürgen Mülbert
--
-- V1.0		- 29. December 2013
-- V1.0.1	- 12. Januar 2014
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

PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;

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
-- Table Employee
-- Recreatet for the actual Version
-- This Version is synchron with the ASPNET-EF 7 Version
--
-- ------------------------------
CREATE TABLE "Employee" (
    "Id" INTEGER NOT NULL CONSTRAINT "PK_Employee" PRIMARY KEY AUTOINCREMENT,
	"EmployeeNO" TEXT NOT NULL,
    "Gender" TEXT,	
	"FirstName" TEXT,
    "MiddleName" TEXT,
    "Name" TEXT NOT NULL,   
    "Street" TEXT,
    "City" TEXT,
    "ZipCode" TEXT,
	"Birthday" TEXT,
	"PhoneNumber" TEXT,
    "FaxNumber" TEXT,
    "MobileNumber" TEXT,	
    "Mail" TEXT,
	"BusinessMail" TEXT,
    "ChipCard" TEXT,	
	"DataCare" INTEGER,	
    "Active" INTEGER,
    "Photo" BLOB,
    "Notes" TEXT,
	"StartDate" TEXT,	
    "EndDate" TEXT,
    "DepartmentId" INTEGER,
    "WorkfunctionId" INTEGER,
    "PlaceId" INTEGER,
    "CompanyId" INTEGER,
 	"LastUpdate" TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
);

---------------------------------------
--
-- Table Company
--
--
---------------------------------------
DROP TABLE IF EXISTS "Company";

CREATE TABLE "Company" (
    "Id" INTEGER NOT NULL CONSTRAINT "PK_Company" PRIMARY KEY AUTOINCREMENT,
	"Name" TEXT NOT NULL,
	"Name2" TEXT,
    "Street" TEXT,
    "City" TEXT,
    "ZipCode" TEXT,
	"PhoneNumber" TEXT,
    "FaxNumber" TEXT,
    "MobileNumber" TEXT,
    "Mail" TEXT,	
	"Active" INTEGER,
	"EmployeeId" INTEGER NOT NULL,
    "LastUpdate" TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,	
CONSTRAINT "FK_Company_Employee_EmployeeId" FOREIGN KEY ("EmployeeId") REFERENCES "Employee" ("Id") ON DELETE CASCADE
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
DROP TABLE IF EXISTS "Computer";
CREATE TABLE "Computer" (
    "Id" INTEGER NOT NULL CONSTRAINT "PK_Computer" PRIMARY KEY AUTOINCREMENT,
	"Name" TEXT NOT NULL,
    "Active" INTEGER,
    "EmployeeId" INTEGER NOT NULL,
    "LastUpdate" TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT "FK_Computer_Employee_EmployeeId" FOREIGN KEY ("EmployeeId") REFERENCES "Employee" ("Id") ON DELETE CASCADE
);



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
DROP TABLE IF EXISTS "Mobile";

CREATE TABLE "Mobile" (
    "Id" INTEGER NOT NULL CONSTRAINT "PK_Mobile" PRIMARY KEY AUTOINCREMENT,
	"Number" TEXT NOT NULL,
    "Active" INTEGER,
    "EmployeeId" INTEGER NOT NULL,
    "LastUpdate" TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT "FK_Mobile_Employee_EmployeeId" FOREIGN KEY ("EmployeeId") REFERENCES "Employee" ("Id") ON DELETE CASCADE
);


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
CREATE TABLE "Phone" (
    "Id" INTEGER NOT NULL CONSTRAINT "PK_Phone" PRIMARY KEY AUTOINCREMENT,
	"Number" TEXT NOT NULL,
    "Active" INTEGER,
    "EmployeeId" INTEGER NOT NULL,
    "LastUpdate" TEXT,
    CONSTRAINT "FK_Phone_Employee_EmployeeId" FOREIGN KEY ("EmployeeId") REFERENCES "Employee" ("Id") ON DELETE CASCADE
);
DELETE FROM sqlite_sequence;
INSERT INTO "sqlite_sequence" VALUES('Employee',1);
INSERT INTO "sqlite_sequence" VALUES('Computer',1);
COMMIT;
