/*
 * helpbrowser.h - HelpBrowser
 *
 * Created by Jürgen Mülbert on 09.03.2014
 * Copyright (c) 2014 Jürgen Mülbert. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the European Union Public Licence (EUPL),
 * version 1.1.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * European Union Public Licence for more details.
 *
 * You should have received a copy of the European Union Public Licence
 * along with this program. If not, see
 * http://www.osor.eu/eupl/european-union-public-licence-eupl-v.1.1
 *
 */


#ifndef HELPBROWSER_H
#define HELPBROWSER_H

#include <QTextBrowser>

class HelpBrowser : public QTextBrowser
{
    Q_OBJECT
public:
    explicit HelpBrowser(QObject *parent = 0);

signals:

public slots:

};

#endif // HELPBROWSER_H
