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

#ifndef Q_OS_WIN
#include <unistd.h>
#endif
#include <iostream>

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

#ifndef Q_OS_WIN
    // Prohibit using sudo or kdesu (but allow using the root user directly)
    if (getuid() == 0) {
        if (!qEnvironmentVariableIsEmpty("SUDO_USER")) {
            std::cout << "Executing jmbde with sudo is not possible due to "
                         "unfixable security vulnerabilities."
                      << std::endl;
            return EXIT_FAILURE;
        } else if (!qEnvironmentVariableIsEmpty("KDESU_USER")) {
            std::cout << "Executing jmbde with kdesu is not possible due to "
                         "unfixable security vulnerabilities."
                      << std::endl;
            return EXIT_FAILURE;
        }
    }
#endif

    /**
     * Create application first
     */
    QApplication app(argc, argv);

    /**
     * Enforce application name even if the executable is renamed
     */
    QApplication::setApplicationName(QStringLiteral(PROJECT_NAME));

    /**
     * For Windows and macOS: use Breeze if available
     * Of all tested styles that works the best for us
     */
#if defined(Q_OS_MACOS) || defined(Q_OS_WIN)
    QApplication::setAttribute(Qt::AA_DontShowIconsInMenus);
    QApplication::setStyle(QStringLiteral("breeze"));
#endif

    /**
     * set the program icon
     */
    QApplication::setWindowIcon(QIcon::fromTheme(QLatin1String("jmbde"), QApplication::windowIcon()));

    /**
     * Enforce application name even if the executable is renamed
     */
    QApplication::setApplicationName(QStringLiteral(PROJECT_NAME));

#if defined(Q_OS_MAC) || defined(Q_OS_WIN)
    QApplication::setAttribute(Qt::AA_DontShowIconsInMenus);
#endif

    QApplication::setApplicationName(QStringLiteral(PROJECT_NAME));
    QApplication::setApplicationDisplayName(QStringLiteral(PROJECT_NAME));
    QApplication::setOrganizationDomain(QStringLiteral(AUTHOR_MAINTAINER));
    QApplication::setOrganizationName(QStringLiteral("io.jmuelbert.github"));
    QApplication::setApplicationVersion(QLatin1String(VERSION));

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
