<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Database Design](#database-design)
  - [Account Table](#account-table)
  - [ChipCard Table](#chipcard-table)
  - [ChipCardDoor Table](#chipcarddoor-table)
  - [ChipcardProfile Table](#chipcardprofile-table)
  - [ChipCardProfileDoor Table](#chipcardprofiledoor-table)
  - [CityName Table](#cityname-table)
  - [Company Table](#company-table)
  - [Computer Table](#computer-table)
  - [ComputerSoftware Table](#computersoftware-table)
  - [Department Table](#department-table)
  - [DeviceName Table](#devicename-table)
  - [DeviceType Table](#devicetype-table)
  - [Document Table](#document-table)
  - [EmployeeAccount Table](#employeeaccount-table)
  - [Employee Table](#employee-table)
  - [EmployeeDocument Table](#employeedocument-table)
  - [Fax Table](#fax-table)
  - [Function Table](#function-table)
  - [Inventory Table](#inventory-table)
  - [Manufacturer Table](#manufacturer-table)
  - [Mobile Table](#mobile-table)
  - [Os Table](#os-table)
  - [Phone Table](#phone-table)
  - [Place Table](#place-table)
  - [Printer Table](#printer-table)
  - [Processor Table](#processor-table)
  - [Software Table](#software-table)
  - [SystemData Table](#systemdata-table)
  - [Title Table](#title-table)
  - [ZipCity Table](#zipcity-table)
  - [ZipCode Table](#zipcode-table)
  - [DatabaseVersion](#databaseversion)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Database Design #

## Account Table ##

| Fieldname      | Type                | Purpose                          |
| -------------- | ------------------- | -------------------------------- |
| account_id     | INTEGER PRIMARY KEY | The Account index                |
| user_name      | VARCHAR             | The Username/Accessname for the  |
|                |                     | system                           |
| password       | VARCHAR             | The password for the access to   |
|                |                     | the system                       |
| system_data_id | INTEGER             | The System for that is the login |
|                |                     | needed                           |
| last_update    | TIMESTAMP           | Timestamp of last modification   |

## ChipCard Table ##

| Fieldname            | Type                | Purpose                          |
| -------------------- | ------------------- | -------------------------------- |
| chip_chard_id        | INTEGER PRIMARY KEY | The ChipCard index               |
| number               | VARCHAR(10)         | Number of Coin                   |
| chip_card_door_id    | INTEGER             | Related Doors by this Coin       |
| chip_card_profile_id | INTEGER             | Releted ChipCardProfiles by this |
|                      |                     | Coin                             |
| employee_id          | INTEGER             | Related Employee                 |
|                      |                     | (Where has this coin)            |
| last_update          | TIMESTAMP           | Timestamp of last modification   |

## ChipCardDoor Table ##

| Fieldname         | Type                | Purpose                           |
| ----------------- | ------------------- | --------------------------------- |
| chip_card_door_id | INTEGER PRIMARY KEY | The ChipCardDoor index            |
| number            | VARCHAR(10)         | The Number/Name of the Door       |
| place_id          | INTEGER             | Relation the Place where the door |
|                   |                     | is                                |
| employee_id       | INTEGER             | Which employee has access         |
| last_update       | TIMESTAMP           | Timestamp of last modification    |

## ChipcardProfile Table ##

| Fieldname            | Type                | Purpose                          |
| -------------------- | ------------------- | -------------------------------- |
| chip_card_profile_id | INTEGER PRIMARY KEY | The ChipcardProfile index        |
| number               | VARCHAR(10)         | The Number/Name for the profile  |
| chip_card_door_id    | INTEGER             | The doors there included in this |
|                      |                     | profile                          |
| employee_id          | INTEGER             | The employees there use this     |
|                      |                     | profile                          |
| last_update          | TIMESTAMP           | Timestamp of last modification   |

## ChipCardProfileDoor Table ##

| Fieldname                 | Type                | Purpose                         |
| ------------------------- | ------------------- | ------------------------------- |
| chip_card_profile_door_id |
|                           | INTEGER PRIMARY KEY | The ChipCardProfileDoor index   |
| chip_card_profile_id      | VARCHAR             | Relation to the ChipCardProfile |
| chip_card_door_id         | VARCHAR             | Relation to the ChipCardDoor    |
| last_update               | TIMESTAMP           | Timestamp of last modification  |

## CityName Table ##

| Fieldname    | Type                | Purpose                        |
| ------------ | ------------------- | ------------------------------ |
| city_name_id | INTEGER PRIMARY KEY | The CityName index             |
| name         | VARCHAR             | The name of the city           |
| last_update  | TIMESTAMP           | Timestamp of last modification |

## Company Table ##

| Fieldname     | Type                | Purpose                           |
| ------------- | ------------------- | --------------------------------- |
| company_id    | INTEGER PRIMARY KEY | The Company index                 |
| name          | VARCHAR             | Name of the Company               |
| name2         | VARCHAR             | Name2 of the Company              |
| street        | VARCHAR             | The Street of the Company.        |
| city          | VARCHAR             | The City of the Company.          |
| zip_code      | INTEGER             | The Zipcode for the City          |
| phone_number  | VARCHAR             | The Phonenumber from the company  |
| fax_number    | VARCHAR             | The Faxnumber from the company    |
| mobile_number | VARCHAR             | The moblienumber from the company |
| mail_address  | VARCHAR             | The mail address from the company |
| active        | BOOLEAN             | The flag is the entry activ       |
| employee_id   | INTEGER             | Relation to the employees for     |
|               |                     | the company                       |
| last_update   | TIMESTAMP           | Timestamp of last modification    |

## Computer Table ##

| Fieldname            | Type                | Purpose                           |
| -------------------- | ------------------- | --------------------------------- |
| computer_id          | INTEGER PRIMARY KEY | The Computer index                |
| name                 | VARCHAR             | Name for the device (i.e. PC0001) |
| serial_number        | VARCHAR             | The serial number from the device |
| service_tag          | VARCHAR             | The tag for service calls         |
| service_number       | VARCHAR             | The quick service number          |
| memory               | INTEGER             | The memory (i.e. 4GB, 8GB)        |
| drive_size           | INTEGER             | Memory for save data i.e. 1TB     |
| drive_type           | INTEGER             | 1=Harddisk, 2=SSD                 |
| network              | VARCHAR             | The name of the Network           |
| active               | BOOLEAN             | Is active or spare                |
| replace              | BOOLEAN             | Must replace                      |
| device_name_id       | INTEGER             | The relation to the device name   |
| device_type_id       | INTEGER             | The releation to the device type  |
| employee_id          | INTEGER             | The relation to the employee      |
| place_id             | INTEGER             | The relation where this device is |
| department_id        | INTEGER             | The relation to the deparment for |
|                      |                     | this device                       |
| manufacturer_id      | INTEGER             | Which manfacturer                 |
| inventory_id         | INTEGER             | The relation to the inventory     |
| processor_id         | INTEGER             | the Relation to the processor     |
| os_id                | INTEGER             | the relation to the OS            |
| computer_software_id | INTEGER             | The relation to the Software.     |
|                      |                     | This is a many to many relation   |
| printer_id           | INTEGER             | The Printer(s) they are connected |
|                      |                     | with this device. Many to many,   |
| last_update          | TIMESTAMP           | Timestamp of last modification    |

## ComputerSoftware Table ##

| Fieldname            | Type                | Purpose                        |
| -------------------- | ------------------- | ------------------------------ |
| computer_software_id | INTEGER PRIMARY KEY | The ComputerSoftware index     |
| computer_id          | INTEGER             | Relation to Computer           |
|                      |                     | (Many to Many)                 |
| software_id          | INTEGER             | Relation to  Software          |
|                      |                     | (Many to Many)                 |
| last_update          | TIMESTAMP           | Timestamp of last modification |

## Department Table ##

| Fieldname     | Type                | Purpose                                         |
| ------------- | ------------------- | ----------------------------------------------- |
| department_id | INTEGER PRIMARY KEY | The index                                       |
| name          | VARCHAR             | The Name of the department                      |
| priority      | INTEGER             | The priority of the departmet. 1=high - 100=low |
| printer_id    | INTEGER             | The printers for the department. (Many to Many) |
| fax_id        | INTEGER             | The faxes for the department. (Many to Many)    |
| last_update   | TIMESTAMP           | Timestamp of last modification                  |

## DeviceName Table ##

| Fieldname      | Type                | Purpose                        |
| -------------- | ------------------- | ------------------------------ |
| device_name_id | INTEGER PRIMARY KEY | The DeviceName index           |
| name           | VARCHAR             | The Name for the device        |
| last_update    | TIMESTAMP           | Timestamp of last modification |

## DeviceType Table ##

| Fieldname      | Type                | Purpose                             |
| -------------- | ------------------- | ----------------------------------- |
| device_type_id | INTEGER PRIMARY KEY | The DeviceType index                |
| name           | VARCHAR             | The name of the type for the device |
| last_update    | TIMESTAMP           | Timestamp of last modification      |

## Document Table ##

| Fieldname     | Type                | Purpose                        |
| ------------- | ------------------- | ------------------------------ |
| document_id   | INTEGER PRIMARY KEY | The Document index             |
| name          | VARCHAR             | The Name of the Document       |
| document_data | BLOB                | The Content of the Document    |
| last_update   | TIMESTAMP           | Timestamp of last modification |

## EmployeeAccount Table ##

| Fieldname           | Type                | Purpose                        |
| ------------------- | ------------------- | ------------------------------ |
| employee_account_id | INTEGER PRIMARY KEY | The EmployeeAccount index      |
| employe_id          | INTEGER             | The relation to the Employee   |
| account_id          | INTEGER             | The relation to the Account    |
| last_update         | TIMESTAMP           | Timestamp of last modification |

## Employee Table ##

| Fieldname             | Type                | Purpose                                                       |
| --------------------- | ------------------- | ------------------------------------------------------------- |
| employee_id           | INTEGER PRIMARY KEY | The Employee index                                            |
| employee_nr           | INTEGER             | The ID-Number for the Employee                                |
| gender                | INTEGER             | The gender of the Employee                                    |
| title_id              | INTEGER             | The relation of the Title                                     |
| first_name            | VARCHAR             | The Firstname                                                 |
| last_name             | VARCHAR             | The Lastname (Surname)                                        |
| birth_day             | DATE                | The Date of Birth                                             |
| address               | VARCHAR             | The Address (Street and House)                                |
| zip_city_id           | INTEGER             | The releation to the ZipCity                                  |
| home_phone            | VARCHAR             | The Home phone number                                         |
| home_mobile           | VARCHAR             | The Home mobile number                                        |
| home_mail_address     | VARCHAR             | The Home mail address                                         |
| business_mail_address | VARCHAR             | The business mail address                                     |
| data_care             | BOOLEAN             | is true than the employee has allowed the storage of the data |
| active                | BOOLEAN             | is true than is the employee active.                          |
| photo                 | BLOB                | The Foto of the Employee                                      |
| notes                 | VARCHAR             | Notes about the employees                                     |
| hire_date             | DATE                | hiring date                                                   |
| end_date              | DATE                | End of employment                                             |
| department_id         | INTEGER             | relation to Department                                        |
| function_id           | INTEGER             | relation to Function                                          |
| computer_id           | INTEGER             | relation to Computer                                          |
| printer_id            | INTEGER             | relation to Printer                                           |
| phone_id              | INTEGER             | relation to Phone                                             |
| mobile_id             | INTEGER             | relation to Mobile                                            |
| fax_id                | INTEGER             | relation to Fax                                               |
| employee_account_id   | INTEGER             | relation to EmployeeAccount                                   |
| employee_document_id  | INTEGER             | relation to EmployeeDocument                                  |
| chip_card_id          | INTEGER             | relation to ChipCard                                          |
| last_update           | TIMESTAMP           | Timestamp of last modification                                |

## EmployeeDocument Table ##

| Fieldname            | Type                | Purpose                        |
| -------------------- | ------------------- | ------------------------------ |
| employee_document_id | INTEGER PRIMARY KEY | The EmployeeDocument index     |
| employe_id           | INTEGER             | relation to Employee           |
| document_id          | INTEGER             | relation to Document           |
| last_update          | TIMESTAMP           | Timestamp of last modification |

## Fax Table ##

| Fieldname             | Type                | Purpose                                    |
| --------------------- | ------------------- | ------------------------------------------ |
| fax_id                | INTEGER PRIMARY KEY | The Fax index                              |
| device_name_id        | INTEGER             | relation to DeviceName                     |
| serial_number         | VARCHAR             | Serialnumber of this device                |
| number                | VARCHAR             | The Phonenumber for this fax               |
| pin                   | VARCHAR             | The pincode for this device                |
| active                | BOOLEAN             | true is the device active, false for spare |
| replace               | BOOLEAN             | true should replace                        |
| device_type_id        | INTEGER             | relation to DeviceType                     |
| employee_id           | INTEGER             | relation to Employee                       |
| place_id              | INTEGER             | relation to Place                          |
| department_id         | INTEGER             | relation to Department                     |
| manufacturer_id       | INTEGER             | relation to Manufacturer                   |
| inventory_id          | INTEGER             | relation to Inventory                      |
| last_update TIMESTAMP | TIMESTAMP           | Timestamp of last modification             |

## Function Table ##

| Fieldname             | Type                | Purpose                                  |
| --------------------- | ------------------- | ---------------------------------------- |
| function_id           | INTEGER PRIMARY KEY | The Function index                       |
| name                  | VARCHAR             | Name for the Function                    |
| priority              | INTEGER             | priority of the function 1=high, 100=low |
| last_update TIMESTAMP | TIMESTAMP           | Timestamp of last modification           |

## Inventory Table ##

| Fieldname             | Type                | Purpose                           |
| --------------------- | ------------------- | --------------------------------- |
| inventory_id          | INTEGER PRIMARY KEY | The Inventory index               |
| number                | VARCHAR             | The Inventory Number              |
| text                  | VARCHAR             | The description for the inventory |
| active                | BOOLEAN             | is this inventory active          |
| last_update TIMESTAMP | TIMESTAMP           | Timestamp of last modification    |

## Manufacturer Table ##

| Fieldname       | Type                | Purpose                                          |
| --------------- | ------------------- | ------------------------------------------------ |
| manufacturer_id | INTEGER PRIMARY KEY | The Manufacturer index                           |
| name            | VARCHAR             | Name of the Manufacturer Company                 |
| name2           | VARCHAR             | Name2 of the Manufacturer Company                |
| supporter       | VARCHAR             | Name of the Support Person                       |
| address         | VARCHAR             | Address (Street and Number) of the Company       |
| address2        | VARCHAR             | Address2 (Street, Number, PO Box) of the Company |
| zip_city_id     | INTEGER             | relation to to ZipCity                           |
| mail_address    | VARCHAR             | Mailaddress                                      |
| phone_number    | VARCHAR             | Phonenumber                                      |
| fax_number      | VARCHAR             | Faxnumber                                        |
| hotline_number  | VARCHAR             | Number for the Hotline (Support)                 |
| last_update     | TIMESTAMP           | Timestamp of last modification                   |

## Mobile Table ##

| Fieldname       | Type                | Purpose                                    |
| --------------- | ------------------- | ------------------------------------------ |
| mobile_id       | INTEGER PRIMARY KEY | The Mobile index                           |
| device_name_id  | INTEGER             | relation to DeviceName                     |
| serial_number   | VARCHAR             | Serialnumber of this device                |
| number          | VARCHAR             | The Phonenumber for this mobile            |
| pin             | VARCHAR             | The pincode for this device                |
| card_number     | VARCHAR             | The number of the SIM-Card                 |
| active          | BOOLEAN             | true is the device active, false for spare |
| replace         | BOOLEAN             | true is the device active, false for spare |
| device_type_id  | INTEGER             | relation to DeviceType                     |
| employe_id      | INTEGER             | relation to Employee                       |
| place_id        | INTEGER             | relation to Place                          |
| department_id   | INTEGER             | relation to Department                     |
| manufacturer_id | INTEGER             | relation to Manufacturer                   |
| inventory_id    | INTEGER             | relation to Inventory                      |
| last_update     | TIMESTAMP           | Timestamp of last modification             |

## Os Table ##

| Fieldname   | Type                | Purpose                        |
| ----------- | ------------------- | ------------------------------ |
| os_id       | INTEGER PRIMARY KEY | The Os index                   |
| name        | VARCHAR             | Name of the operation system   |
| version     | VARCHAR             | The version                    |
| revision    | VARCHAR             | The revision                   |
| fix         | VARCHAR             | The fix or build number        |
| last_update | TIMESTAMP           | Timestamp of last modification |

## Phone Table ##

| Fieldname       | Type                | Purpose                                    |
| --------------- | ------------------- | ------------------------------------------ |
| phone_id        | INTEGER PRIMARY KEY | The Phone index                            |
| device_name_id  | INTEGER             | relation to DeviceName                     |
| serial_number   | VARCHAR             | Serialnumber of this device                |
| number          | VARCHAR             | The Phonenumber                            |
| pin             | VARCHAR             | The pincode for this device                |
| active          | BOOLEAN             | true is the device active, false for spare |
| replace         | BOOLEAN             | true should replace                        |
| device_type_id  | INTEGER             | relation to DeviceType                     |
| employe_id      | INTEGER             | relation to Employee                       |
| place_id        | INTEGER             | relation to Place                          |
| department_id   | INTEGER             | relation to Department                     |
| manufacturer_id | INTEGER             | relation to Manufacturer                   |
| inventory_id    | INTEGER             | relation to Inventory                      |
| last_update     | TIMESTAMP           | Timestamp of last modification             |

## Place Table ##

| Fieldname   | Type                | Purpose                        |
| ----------- | ------------------- | ------------------------------ |
| place_id    | INTEGER PRIMARY KEY | The Place index                |
| name        | VARCHAR             | Name for this place            |
| room        | VARCHAR             | Number or name for the room    |
| desk        | VARCHAR             | Number or name for the desk    |
| last_update | TIMESTAMP           | Timestamp of last modification |

## Printer Table ##

| Fieldname          | Type                | Purpose                                    |
| ------------------ | ------------------- | ------------------------------------------ |
| printer_id         | INTEGER PRIMARY KEY | The Printer index                          |
| device_name_id     | INTEGER             | relation to DeviceName                     |
| serial_number      | VARCHAR             | Serialnumber of this device                |
| network            | VARCHAR             | Name for the network of this printer       |
| network_name       | VARCHAR             | Name for the network of this printer       |
| network_ip_address | VARCHAR             | IP-Address for this printer                |
| active             | BOOLEAN             | true is the device active, false for spare |
| replace            | BOOLEAN             | true should replace                        |
| resources          | VARCHAR             | Name and type for toner or ink.            |
| paper_size_max     | VARCHAR             | i.e. Legal, Letter, A4, A3                 |
| color              | BOOLEAN             | is true is an color printer                |
| device_type_id     | INTEGER             | relation to DeviceType                     |
| employe_id         | INTEGER             | relation to Employee                       |
| place_id           | INTEGER             | relation to Place                          |
| department_id      | INTEGER             | relation to Department                     |
| manufacturer_id    | INTEGER             | relation to Manufacturer                   |
| inventory_id       | INTEGER             | relation to Inventory                      |
| computer_id        | INTEGER             | relation to the connected Computer         |
| last_update        | TIMESTAMP           | Timestamp of last modification             |

## Processor Table ##

| Fieldname    | Type                | Purpose                        |
| ------------ | ------------------- | ------------------------------ |
| processor_id | INTEGER PRIMARY KEY | The Processor index            |
| name         | VARCHAR             | Name and type of the Processor |
| clock_rate   | DECIMAL             | Clockrate of the Processor     |
| cores        | INTEGER             | Cores                          |
| last_update  | TIMESTAMP           | Timestamp of last modification |

## Software Table ##

| Fieldname   | Type                | Purpose                        |
| ----------- | ------------------- | ------------------------------ |
| software_id | INTEGER PRIMARY KEY | The Software index             |
| name        | VARCHAR             | Name of the Software           |
| version     | VARCHAR             | The version                    |
| revision    | VARCHAR             | The revision                   |
| fix         | VARCHAR             | The fix or the build number    |
| last_update | TIMESTAMP           | Timestamp of last modification |

## SystemData Table ##

| Fieldname      | Type                | Purpose                          |
| -------------- | ------------------- | -------------------------------- |
| system_data_id | INTEGER PRIMARY KEY | The SystemData index             |
| name           | VARCHAR             | Name of the System               |
| local          | BOOLEAN             | True is as a local system        |
| company_id     | INTEGER             | relation to the provider Company |
| last_update    | TIMESTAMP           | Timestamp of last modification   |

## Title Table ##

| Fieldname   | Type                | Purpose                        |
| ----------- | ------------------- | ------------------------------ |
| title_id    | INTEGER PRIMARY KEY | The Title index                |
| name        | VARCHAR(50)         | Name of Title                  |
| from_date   | DATE                | From ...                       |
| last_update | TIMESTAMP           | Timestamp of last modification |

## ZipCity Table ##

| Fieldname   | Type                | Purpose                        |
| ----------- | ------------------- | ------------------------------ |
| zip_city_id | INTEGER PRIMARY KEY | The ZipCity index              |
| zip_code_id | INTEGER             | relation to ZipCode            |
| city_id     | INTEGER             | relation to ZipCity            |
| last_update | TIMESTAMP           | Timestamp of last modification |

## ZipCode Table ##

| Fieldname   | Type                | Purpose                        |
| ----------- | ------------------- | ------------------------------ |
| zip_code_id | INTEGER PRIMARY KEY | The ZipCode index              |
| code        | VARCHAR(10)         | The ZipCode for ZipCity        |
| last_update | TIMESTAMP           | Timestamp of last modification |

## DatabaseVersion ##

| Fieldname           | Type                | Purpose                          |
| ------------------- | ------------------- | -------------------------------- |
| database_version_id | INTEGER PRIMARY KEY | The DatabaseVersion index        |
| version             | VARCHAR(10)         | The Version of the Database      |
| revision            | VARCHAR (10)        | The Revision of the Database     |
| patch               | VARCHAR(10)         | The Patchveriosn of the Database |
