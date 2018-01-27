/**************************************************************************
**
** Copyright (c) 2013-2018 Jürgen Mülbert. All rights reserved.
**
** This file is part of jmbde
**
** Licensed under the EUPL, Version 1.2 or – as soon they
** will be approved by the European Commission - subsequent
** versions of the EUPL (the "Licence");
** You may not use this work except in compliance with the
** Licence.
** You may obtain a copy of the Licence at:
**
** https://joinup.ec.europa.eu/page/eupl-text-11-12
**
** Unless required by applicable law or agreed to in
** writing, software distributed under the Licence is
** distributed on an "AS IS" basis,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
** express or implied.
** See the Licence for the specific language governing
** permissions and limitations under the Licence.
**
** Lizenziert unter der EUPL, Version 1.2 oder - sobald
**  diese von der Europäischen Kommission genehmigt wurden -
** Folgeversionen der EUPL ("Lizenz");
** Sie dürfen dieses Werk ausschließlich gemäß
** dieser Lizenz nutzen.
** Eine Kopie der Lizenz finden Sie hier:
**
** https://joinup.ec.europa.eu/page/eupl-text-11-12
**
** Sofern nicht durch anwendbare Rechtsvorschriften
** gefordert oder in schriftlicher Form vereinbart, wird
** die unter der Lizenz verbreitete Software "so wie sie
** ist", OHNE JEGLICHE GEWÄHRLEISTUNG ODER BEDINGUNGEN -
** ausdrücklich oder stillschweigend - verbreitet.
** Die sprachspezifischen Genehmigungen und Beschränkungen
** unter der Lizenz sind dem Lizenztext zu entnehmen.
**
**************************************************************************/

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QtGlobal>

/**
 * Constants for the jmbde application
 */
namespace Constants {

  /**
   * @brief COMPANY_NAME
   */
  const char COMPANY_NAME[] = "de.jmuelbert";

  /**
   * @brief APPL_NAME
   */
  const char APPL_NAME[] = "jmbde";

  /**
   * @brief APPL_VERSION
   */
  const char APPL_VERSION[] = "0.4.0";
  const char APPL_DISPLAYNAME[] = "jmbde 0.4.0 © 2013-2016 Jürgen Mülbert";

  /**
   * @brief APPL_PROJECT_SITE
   */
  const char APPL_PROJECT_SITE[] = "http://www.juergen-muelbert.de/projects/jmbde/";
}

namespace Settings {
  namespace Groups {
    const char MAINWINDOW[] = "MainWindow";
    const char DATABASE[] = "Database";
  }

  namespace MainWindow {
    const char SIZE[] = "size";
    const char POS[] = "pos";
  }

  namespace Database {
    const char TYPE[] = "type";
    const char CONNECTION[] = "connection";
    const char HOSTNAME[] = "hostname";
    const char USERNAME[] = "username";
    const char PASSWORD[] = "password";

  }

}

enum DbType {
  SQLITE,
  MYSQL,
  ODBC,
  POSTGRESQL
};

namespace Database {

  namespace Type {
    const char SQLITE[] = "SqLite";
    const char MYSQL[] = "MySql";
    const char ODBC[] = "ODBC";
    const char POSTGRESQL[] = "PostgreSQL";
    const char DEFAULT[] = "SqLite";

  }

  namespace Table {
    const int DEFAULT_FOREIGN_VALUE = 1;

  }

  namespace EmployeeTable {}
}
#endif // CONSTANTS_H
