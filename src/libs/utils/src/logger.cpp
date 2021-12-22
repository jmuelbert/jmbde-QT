/*
 *  SPDX-FileCopyrightText: 2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "utils/logger.h"

void Logger::messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // Open stream file writes
    QTextStream out(m_logFile.data());
    // Write the date of recording
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");
    // By type determine to what level belongs message
    switch (type) {
    case QtInfoMsg:
        out << "INF";
        break;
    case QtDebugMsg:
        out << "DGB";
        break;
    case QtWarningMsg:
        out << "WRN";
        break;
    case QtCriticalMsg:
        out << "CRT";
        break;
    case QtFatalMsg:
        out << "FTL";
        break;
    }
    // Write to the output category of the message and the message itself
    out << context.category << ": " << msg << Qt::endl;
    out.flush();
}
