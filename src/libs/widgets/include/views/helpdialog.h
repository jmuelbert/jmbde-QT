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

#pragma once

#include <QDialog>
#include <QTextBrowser>

namespace Ui
{
class HelpDialog;
}

class QHelpEngine;

class HelpBrowser : public QTextBrowser
{
public:
    HelpBrowser(QWidget *parent = 0)
        : QTextBrowser(parent)
        , mHelpEngine(nullptr)
    {
    }
    void setHelpEngine(QHelpEngine *helpEngine);
    QVariant loadResource(int type, const QUrl &name);

private:
    QHelpEngine *mHelpEngine;
};

class HelpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HelpDialog(QWidget *parent = nullptr);
    ~HelpDialog();

private:
    Ui::HelpDialog *mUi;
    QHelpEngine *mHelpEngine;
};

#endif // HELPDIALOG_H
