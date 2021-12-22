/*
 *  SPDX-FileCopyrightText: 2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <QDateTime>
#include <QFile>
#include <QLoggingCategory>
#include <QScopedPointer>
#include <QTextStream>
#include <stdio.h>

#include "utils_export.h"

class Logger
{
    Q_OBJECT

public:
    explicit Logger()
    {
    }

    void UTILS_EXPORT messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

private:
    QScopedPointer<QFile> m_logFile;
};
