
/*
   jmbde a BDE Tool for companies
   Copyright (C) 2013-2020  Jürgen Mülbert

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
*/

#include "quick/maincontroller.h"
#include "models/employeemodel.h"

MainController::MainController(/* QObject *parent */) = default;

MainController::~MainController()
{
    delete mEngine;
}

auto MainController::initialize() -> bool
{
    mEngine = new QQmlApplicationEngine;

    QQmlContext *ctxt = mEngine->rootContext();

#if !defined(Q_OS_ANDROID) && !defined(Q_OS_IOS)
//    qmlRegisterType<Notification>(URI, 1, 0, "Notification");
//    ctxt->setContextProperty(QLatin1String("systrayIcon"),
//    App::self()->notofication());
#endif

    // ctxt->setContextObject(new KLocalizedContext(mEngine));

    mEngine->addImportPath(QLatin1String("qrc:/"));
    mEngine->addImportPath(QLatin1String("qrc:/qml"));

    qmlRegisterType<EmployeeModel>("Backend", 1, 0, "EmployeeModel");

    mEngine->load(QUrl(QLatin1String("qrc:/qml/main.qml")));

    if (mEngine->rootObjects().isEmpty()) {
        qCCritical(jmbdequickLog) << "Impossible to load object from main.qml";
        return false;
    }
    return true;
}
