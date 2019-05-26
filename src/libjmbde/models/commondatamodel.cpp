/**************************************************************************
**
** Copyright (c) 2013-2019 Jürgen Mülbert. All rights reserved.
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

#include "commondatamodel.h"

CommonDataModel::CommonDataModel(QObject *parent) {}

CommonDataModel::~CommonDataModel() = default;

QTextDocument *CommonDataModel::createSheet() {
  auto *document = new QTextDocument;

  return document;
}

QString CommonDataModel::setOutTableStyle() {
  QString css;

  css = QLatin1String("<style type=\"text/css\">");
  css += QLatin1String("H1 { color: #f00;}");
  css +=
      QLatin1String("table.tbl {border-width: 1px;border-style: "
                    "solid;border-color: black;margin-top: 0px;margin-bottom: "
                    "0px;color: black; font-size: small; }");
  css += QLatin1String("table.tbl td {padding: 3px;}");
  css += QLatin1String("table.tbl th {padding: 3px;}");
  css += QLatin1String("</style>");

  return css;
}

QString CommonDataModel::setOutFormularStyle() {
  QString css;

  css = QLatin1String("<style type=\"text/css\">");
  css += QLatin1String("H1 { color: #f00;}");

  return css;
}
