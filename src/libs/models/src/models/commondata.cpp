/*
   jmbde a BDE Tool for companies
   Copyright (C) 2013-2019  Jürgen Mülbert

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
*/

#include "models/commondata.h"

Model::CommonData::CommonData(QObject * /*parent*/)
    : m_model(nullptr)
    , m_selectionModel(nullptr)
{
}

Model::CommonData::~CommonData()
{
}

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
