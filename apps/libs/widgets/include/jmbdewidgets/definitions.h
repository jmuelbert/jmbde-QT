/*
 *  SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

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

/**
 * @brief Definitions for Settings
 *
 *    category: "WindowState"
 *        property alias window_x:    appWindow.x
 *        property alias window_y:    appWindow.y
 *        property alias window_width: appWindow.width
 *        property alias window_height: appWindow.height
 *
 *    category: "Database"
 *        property alias type: cbDatabaseType.currentIndex
 *        property alias connection: textDBConnection.text
 *        property alias hostname: textInputHostname.text
 *        property alias username: textInputUsername.text
 *        property alias password: textInputPassword.text
 */
namespace Settings
{
namespace Groups
{
const char WINDOWSSTATE[] = "WindowState";
const char DATABASE[] = "Database";
} // namespace Groups

namespace WindowState
{
const char WINDOW_X[] = "window_x";
const char WINDOW_Y[] = "window_y";
const char WINDOW_WIDTH[] = "window_width";
const char WINDOW_HEIGHT[] = "window_height";
} // namespace WindowState

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
} // namespace Version

namespace Type
{
const char SQLITE[] = "SqLite";
const char MYSQL[] = "MySql";
const char ODBC[] = "ODBC";
const char POSTGRESQL[] = "PostgreSQL";
const char DEFAULT[] = "SqLite";

} // namespace Type
} // namespace Database
