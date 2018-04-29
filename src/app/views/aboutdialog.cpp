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


#include "aboutdialog.h"
#include "ui_aboutdialog.h"

#include <QAbstractTextDocumentLayout>
#include <QApplication>
#include <QDesktopServices>

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    const QString aboutInfo = QCoreApplication::translate(
            "AboutDialog",
            "<p align=\"center\"><font size=\"+2\"><b>%1</b></font><br><i>Version %2</i></p>\n"
            "<p align=\"center\">Copyright 2013-2018 Jürgen Mülbert\n"
            "<p align=\"center\">This program is free software: you can redistribute it and/or modify</p>\n"
            "<p align=\"center\">it under the terms of the European Union Public Licence (EUPL) version 1.2. or newer</p>\n"
            "<p align=\"center\">this program is distributed in the hope that it will be useful,</p>\n"
            "<p align=\"center\">but WITHOUT ANY WARRANTY; without even the implied warranty of</p>\n"
            "<p align=\"center\">MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the</p>\n"
            "<p align=\"center\">European Union Public Licence for more details.</p>\n\n"
            "<p align=\"center\">You should have received a copy of the European Union Public Licence</p>\n"
            "<p align=\"center\">along with this program. If not, see</p>\n"
            "<p align=\"center\"><a href=\"https://joinup.ec.europa.eu/page/eupl-text-11-12/\">https://joinup.ec.europa.eu/page/eupl-text-11-12</a></p>\n")

                                  .arg(qApp->applicationDisplayName())
                                  .arg(qApp->applicationVersion());

        ui->textBrowser->setHtml(aboutInfo);

       connect(ui->donateButton, SIGNAL(clicked()), SLOT(donate()));

}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::donate()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("test")));
}
