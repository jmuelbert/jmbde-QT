/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "views/aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AboutDialog)
    , m_AboutDialogLog(QLoggingCategory("jmbde.widget.aboutdialog"))
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
