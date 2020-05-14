#include <QCoreApplication>
#include <QDebug>
#include <QGuiApplication>
#include <QLoggingCategory>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTranslator>

#include <jmbdequick-version.h>
#include <jmbdequick_export.h>
#include <loggingcategory.h>

#include "models/employee.h"


#pragma once

class QQmlApplicationEngine;

class  MainController : public QObject
{
    Q_OBJECT

public:
    explicit JMBDEQUICK_EXPORT MainController(/* QObject *parent = nullptr */);

    JMBDEQUICK_EXPORT ~MainController();

    Q_REQUIRED_RESULT JMBDEQUICK_EXPORT bool initialize();


private:
    QQmlApplicationEngine *mEngine = nullptr;
};
