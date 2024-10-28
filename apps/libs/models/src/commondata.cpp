/*
 *  SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert
 * <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "jmbdemodels/commondata.h"

auto Model::CommonData::createSheet() -> QTextDocument *
{
  auto *document = new QTextDocument;

  return document;
}

auto Model::CommonData::setOutTableStyle() -> QString
{
  QString css;

  css = QLatin1String("<style type=\"text/css\">");
  css += QLatin1String("H1 { color: #f00;}");
  css += QLatin1String(
    "table.tbl {border-width: 1px;border-style: "
    "solid;border-color: black;margin-top: 0px;margin-bottom: "
    "0px;color: black; font-size: small; }");
  css += QLatin1String("table.tbl td {padding: 3px;}");
  css += QLatin1String("table.tbl th {padding: 3px;}");
  css += QLatin1String("</style>");

  return css;
}

auto Model::CommonData::setOutFormularStyle() -> QString
{
  QString css;

  css = QLatin1String("<style type=\"text/css\">");
  css += QLatin1String("H1 { color: #f00;}");

  return css;
}
