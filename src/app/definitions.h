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

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <QtGlobal>

#define APP_ICON_PATH QStringLiteral(":/graphics/jmbde.png")

#ifndef QSL
#define QSL(x) QStringLiteral(x)
#endif

#ifndef QL1S
#define QL1S(x) QLatin1String(x)
#endif

#ifndef QL1C
#define QL1C(x) QLatin1Char(x)
#endif

namespace Settings
{
namespace Groups
{
const char MAINWINDOW[] = "MainWindow";
const char DATABASE[] = "Database";
} // namespace Groups

namespace MainWindow
{
const char SIZE[] = "size";
const char POS[] = "pos";
const char SPLITTER[] = "splitterSizes";
const char LAST_VIEW[] = "last_view";
const char LAST_DATA[] = "last_data";
} // namespace MainWindow

namespace Database
{
const char TYPE[] = "type";
const char CONNECTION[] = "connection";
const char HOSTNAME[] = "hostname";
const char USERNAME[] = "username";
const char PASSWORD[] = "password";

} // namespace Database

} // namespace Settings

enum DbType { SQLITE, MYSQL, ODBC, POSTGRESQL };

namespace Database
{

namespace Version
{
const char Version[] = "0";
const char Revision[] = "90";
const char Patch[] = "0";
}

namespace Type
{
const char SQLITE[] = "SqLite";
const char MYSQL[] = "MySql";
const char ODBC[] = "ODBC";
const char POSTGRESQL[] = "PostgreSQL";
const char DEFAULT[] = "SqLite";

} // namespace Type
} // namespace Database
#endif // DEFINITIONS_H
