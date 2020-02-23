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

#include "jmbde-version.h"
// #include "jmbde-settings.h"
// #include "jmbdemodels_export.h"
#include "jmbdewidgets_export.h"
#include "views/mainwindow.h"

#include <QDebug>
#include <QObject>

#include <QApplication>
#include <QMessageBox>
#include <QGuiApplication>


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

#include <QStandardPaths>
#include <QQmlApplicationEngine>
#include <QQmlFileSelector>
#include <QQmlContext>


#ifndef Q_OS_WIN
#include <unistd.h>
#endif
#include <iostream>

#if defined Qt5AndroidExtras_FOUND && Qt5AndroidExtras_FOUND
#include <QAndroidService>
#endif

#include <memory>

#if defined Qt5AndroidExtras_FOUND && Qt5AndroidExtras_FOUND
#include <QAndroidJniObject>
#include <QtAndroid>
#endif


/**
 * @brief main
 * @param argc The count of args
 * @param argv The arg Strings
 * @return 0 is exceuted sucessfull
 */
#if defined Q_OS_ANDROID
int __attribute__((visibility("default"))) main(int argc, char *argv[])
#else
int main(int argc, char *argv[])
#endif
{
#if defined Q_OS_ANDROID
    if(argc > 1 && strcmp(argv[1], "-service") == 0){
        QAndroidService app(argc, argv);
        qInfo() << "Service starting...";

        // My service stuff

        return app.exec();
    }

    qInfo() << "Application starting...";
#endif


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
     * enable high dpi support
     */
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    /**
     * Create application first
     */
    QApplication app(argc, argv);

    /**
     * Enforce application name even if the executable is renamed
     */
    QApplication::setApplicationName(QStringLiteral("jmbde"));

    /**
     * set the program icon
     */
    QApplication::setWindowIcon(
        QIcon::fromTheme(QStringLiteral("jmbde")));
    QApplication::setOrganizationDomain(QStringLiteral("jmuelbert.github.io"));

#if defined(Q_OS_MAC) || defined(Q_OS_WIN)
    QApplication::setApplicationName(QStringLiteral("jmbde"));
    QApplication::setAttribute(Qt::AA_DontShowIconsInMenus);
#else
    QApplication::setApplicationName(QStringLiteral("jmbde"));
#endif

    QApplication::setApplicationDisplayName(QStringLiteral("jmbde"));
    QApplication::setOrganizationName(QStringLiteral("jmuelbert.github.io"));
    QApplication::setApplicationVersion(QLatin1String(JMBDE_VERSION_STRING));

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

    // Quick Settings
    QQmlApplicationEngine engine;
    engine.addImportPath(QStringLiteral("qrc:/imports"));
    // engine.rootContext()->setContextObject(new jmbdeLocalizedContext(&engine));

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

    MainWindow w;
    w.show();

    return QApplication::exec();
}
