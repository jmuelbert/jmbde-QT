/*
    jmbde a BDE Tool for companies
    Copyright (C) 2020  Jürgen Mülbert

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

#include "views/aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    const char *htmlraw = R"html(
<p align="center"><font size="+2"><b>jmbde</b></font><br><i>Version %1</i></p>
<p align="center">Copyright 2013-2020 Jürgen Mülbert</a><br>(see the <a href="https://github.com/jmuelbert/jmbde-QT/blob/master/AUTHORS">AUTHORS</a> file for a full list of contributors)</p>
<p align="center">You may modify and redistribute this program under the terms of the <a href="https://spdx.org/licenses/GPL-3.0-or-later.html">GPL-3.0-or-later.<a/>
<p align="center"><a href="http://github.com/jmuelbert/jmbde-QT/">http://github.com/jmuelbert/jmbde-QT</a></p>
)html";

    const QString html = QCoreApplication::translate("AboutDialog", htmlraw).arg(QApplication::applicationVersion());

    ui->textBrowser->setHtml(html);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
