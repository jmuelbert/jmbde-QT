/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
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

    // QQmlContext *ctxt = mEngine->rootContext();
    // ctxt->setContextObject(new KLocalizedContext(mEngine));

    mEngine->addImportPath(QLatin1String("qrc:/"));
    mEngine->addImportPath(QLatin1String("qrc:/qml"));

    qmlRegisterType<EmployeeModel>("Backend", 1, 0, "EmployeeModel");

    mEngine->load(QUrl(QLatin1String("qrc:/qml/main.qml")));

    if (mEngine->rootObjects().isEmpty()) {
        // qCCritical(jmbdequickLog) << "Impossible to load object from main.qml";
        return false;
    }
    return true;
}
