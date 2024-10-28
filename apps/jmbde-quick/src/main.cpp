/*
 * SPDX-FileCopyrightText: 2013-2022 Project jmbde-QT, Jürgen Mülbert
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <QApplication>
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QDebug>
#include <QGuiApplication>
#include <QIcon>
#include <QLibraryInfo>
#include <QLoggingCategory>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QTranslator>

#include "jmbde_version.h"
#include "jmbdequick/maincontroller.h"

#include "singleapplication.h"

/**
 * @brief main
 * @param argc The count of args
 * @param argv The arg Strings
 * @return 0 is exceuted successful
 */
#if defined Q_OS_ANDROID
int __attribute__((visibility("default"))) main(int argc, char *argv[])
#else
auto main(int argc, char *argv[]) -> int
#endif
{
    QLoggingCategory::setFilterRules(QLatin1String("jmbdequick.*.debug=false\njmbdequick.*.info=false"));

    /**
     * Create application first
     * We always use a single application that allows to start multiple instances.
     * This allows for communication even without DBus and better testing of these code paths.
     */
#ifdef Q_OS_WINDOWS
    SingleApplication app(argc, argv, true);

    if (app.isSecondary()) {
        AllowSetForegroundWindow(DWORD(app.primaryPid()));

        app.sendMessage("RAISE_WIDGET");

        return 0;
    }
#else
    SingleApplication app(argc, argv);
#endif

    /**
     * Enforce application name even if the executable is renamed
     */
    app.setApplicationName(QStringLiteral(PROJECT_NAME));

    /**
     * For Windows and macOS: use Breeze if available
     * Of all tested styles that works the best for us
     */
#if defined(Q_OS_MACOS) || defined(Q_OS_WIN)
    app.setAttribute(Qt::AA_DontShowIconsInMenus);
    app.setStyle(QStringLiteral("breeze"));
#endif

    /**
     * set the program icon
     */
    app.setWindowIcon(QIcon::fromTheme(QLatin1String("jmbde"), QApplication::windowIcon()));

    /**
     * Enforce application name even if the executable is renamed
     */
    app.setApplicationName(QStringLiteral(PROJECT_NAME));

#if defined(Q_OS_MAC) || defined(Q_OS_WIN)
    app.setAttribute(Qt::AA_DontShowIconsInMenus);
#endif

    app.setApplicationName(QStringLiteral(PROJECT_NAME));
    app.setApplicationDisplayName(QStringLiteral(PROJECT_NAME));
    app.setOrganizationDomain(QStringLiteral(AUTHOR_MAINTAINER));
    app.setOrganizationName(QStringLiteral("io.jmuelbert.github"));
    app.setApplicationVersion(QLatin1String(VERSION));

    /**
     * Create command line parser and feed it with known options
     */
    QCommandLineParser parser;

    parser.setApplicationDescription(QLatin1String("jmbde - Commandline"));
    parser.addHelpOption();
    parser.addVersionOption();

    /**
     * do the command line parsing
     */
    parser.process(app);

    // Setup and load translator for localization
    static QString locale = QLocale::system().name();

    QTranslator jmbdeTranslator;
    jmbdeTranslator.load(QLatin1String("jmbde_") + locale);
    QApplication::installTranslator(&jmbdeTranslator);

    QIcon::setFallbackSearchPaths(QIcon::fallbackSearchPaths() << QLatin1String(":tango"));
    QIcon::setThemeName(QLatin1String("tango"));

    app.setProperty("jmbde_locale", locale);
    QApplication::setLayoutDirection(QObject::tr("LTR") == QLatin1String("RTL") ? Qt::RightToLeft : Qt::LeftToRight);

    MainController mainController;

    if (!mainController.initialize()) {
        return -1;
    }

    return QApplication::exec();
}
