 /*
    jmbde a BDE Tool for companies
    Copyright (C) 2013-2019  Jürgen Mülbert

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

#include <QDebug>
#include <QObject>


#include <QApplication>
#include <QQmlApplicationEngine>


#include <QCommandLineParser>
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QGuiApplication>
#include <QLibraryInfo>
#include <QLoggingCategory>
#include <QSettings>
#include <QString>
#include <QStringList>
#include <QStyleFactory>
#include <QTranslator>
#include <QQmlApplicationEngine>

#ifndef Q_OS_WIN
#include <unistd.h>
#endif
#include <iostream>

#include "views/mainwindow.h"
#include "models/employee.h"

#include "jmbde_common_export.h"

/**
 * @brief main
 * @param argc The count of args
 * @param argv The arg Strings
 * @return 0 is exceuted sucessfull
 */
int main(int argc, char *argv[]) {

    QLoggingCategory::setFilterRules(
        QLatin1String("jmbde.*.debug=false\njmbde.*.info=false"));

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
     * init resources from our static lib
     */
    // Q_INIT_RESOURCE(jmbde);

    /**
     * Create application first
     */
    QApplication app(argc, argv);

    /**
     * Enforce application name even if the executable is renamed
     */
    QApplication::setApplicationName(QStringLiteral("jmbde"));

    /**
     * enable high dpi support
     */
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);

    /**
     * set the program icon
     */
    QApplication::setWindowIcon(
        QIcon::fromTheme(QStringLiteral("jmbde"), app.windowIcon()));
    QApplication::setOrganizationDomain(QStringLiteral("jmuelbert.github.io"));

#if defined(Q_OS_MAC) || defined(Q_OS_WIN)
    QApplication::setApplicationName(QStringLiteral("jmbde"));
    QApplication::setAttribute(Qt::AA_DontShowIconsInMenus);
#else
    QApplication::setApplicationName(QStringLiteral("jmbde"));
#endif

    QApplication::setApplicationDisplayName(QStringLiteral("jmbde"));
    QApplication::setOrganizationName(QStringLiteral("jmuelbert.github.io"));
    QApplication::setApplicationVersion(QLatin1String("0.4.25"));

    /**
     * Create command line parser and feed it with known options
     */
    QCommandLineParser parser;

    parser.setApplicationDescription(QStringLiteral("jmbde - Commandline"));
    parser.addHelpOption();
    parser.addVersionOption();

    /**
     * do the command line parsing
     */
    parser.process(app);

    // Setup and load translator for localization
    QString locale = QLocale::system().name();
    QTranslator qtTranslator;
    qtTranslator.load(QLatin1String("qt_") + locale,
                      QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    QApplication::installTranslator(&qtTranslator);

    QTranslator jmbdeTranslator;
    jmbdeTranslator.load(QLatin1String("app_") + locale);
    QApplication::installTranslator(&jmbdeTranslator);

    QIcon::setFallbackSearchPaths(QIcon::fallbackSearchPaths()
                                  << QLatin1String(":tango"));
    QIcon::setThemeName(QLatin1String("tango"));

    app.setProperty("jmbde_locale", locale);
    QApplication::setLayoutDirection(QObject::tr("LTR") == QLatin1String("RTL")
                                         ? Qt::RightToLeft
                                         : Qt::LeftToRight);

    qmlRegisterType<Model::EmployeeTableModel>("EmployeeTableModel", 0, 1, "EmployeeTableModel");

    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:/");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    return app.exec();

}
