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

#pragma once

#include <jmbdequick-version.h>
#include <jmbdequick_export.h>
#include <loggingcategory.h>

#include <QCoreApplication>
#include <QDebug>
#include <QGuiApplication>
#include <QLoggingCategory>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTranslator>

#include "models/employee.h"

class QQmlApplicationEngine;

class MainController : public QObject
{
    Q_OBJECT

public:
    explicit JMBDEQUICK_EXPORT MainController(/* QObject *parent = nullptr */);

    JMBDEQUICK_EXPORT ~MainController();

    Q_REQUIRED_RESULT JMBDEQUICK_EXPORT bool initialize();

private:
    QQmlApplicationEngine *mEngine = nullptr;
};
