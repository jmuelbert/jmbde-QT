/*
 *  SPDX-FileCopyrightText: 2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include <QDateTime>
#include <QFile>
#include <QLoggingCategory>
#include <QScopedPointer>
#include <QTextStream>
#include <stdio.h>

#include "utils_export.h"

class Logger {
private:
    /// @brief The file object where logs are written to.
    static QFile* logFile;

       /// @brief Whether the logger has being initialized.
    static bool isInit;

       /// @brief The different type of contexts.
    static QHash<QtMsgType, QString> contextNames;

public:
    /// @brief Initializes the logger.
    static void init();

       /// @brief Cleans up the logger.
    static void clean();

       /// @brief The function which handles the logging of text.
    static void messageOutput(QtMsgType type, const QMessageLogContext& context,
                              const QString& msg);
};
