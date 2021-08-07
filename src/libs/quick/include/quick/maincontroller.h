/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include <jmbdequick-version.h>
#include <jmbdequick_export.h>

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
