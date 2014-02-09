#ifndef EMPLOYEEDATA_H
#define EMPLOYEEDATA_H

#include "datamodell.h"

/**
 * @brief The employeedata class
 */

 /**
 * @brief EmployeeDataModel::EmployeeDataModel
 * @param parent
 *
 * ! \Database Page
 *
 * The Datafields:
 *  persnr - The Personalnumber as Integer
 *  title  - The Title if necessary (Dr. Prof. Ing. and so on)
 *  firstname - The Firstname of the Person
 *  lastname - The Family Name of the Person
 *  street - The Home Street
 *  zip_idzip - Foreign Key to Table of Zip Codes
 *  city_idcity - Foreign Key of Table of Cities
 *  gender - Gender of the Person (M)an oder (W)oman
 *  birthday - Day of Birth
 *  email - the email address
 *  datacare - Has Employee Datacare Informations
 *  active - Is the Employee active
 *  startdate - The Date of Start in this Company for the Employee
 *  enddate - The End Date in this Company for the Employee
 *  lastupdate - The newest change on the Data
 *  department_iddepartment - Foreign Key to Table Department
 *  function_idfunction - Foreign Key to the Function Table
 *  computer_idcomputer - Foreign Key to to Computerr Table.
 *  printer_idprinter - Foreign Key to the Printer Table
 *  phone_idphone - Foreign Key to the Phone Table
 *  mobile_idmoblie - Foreign Key to the Mobile Table
 *  fax_idfax - Foreign Key to the Fax Table
 *  acount_idaccount - Foreign Key to the Account Table
 *  documents_iddocuments - Foreign Key to the documents table
 *
* \dot
 * digraph g {
 *	graph [	rankdir = "LR"; ];
 	node [
 		fontsize = "16";
 		shape = "record";
 		];
 	EMPLOYEE [label="emploee"; URL="\ref B"];
 	EMPLOYEE [label="persnr"];
 	}
 	\enddot
 */
class employeedata : public datamodel
{
public:
    employeedata();
};

#endif // EMPLOYEEDATA_H
