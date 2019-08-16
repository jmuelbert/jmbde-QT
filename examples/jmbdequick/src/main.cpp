/**************************************************************************
**
** Copyright (c) 2013-2019 Jürgen Mülbert. All rights reserved.
**
** This file is part of jmbde
**
** Licensed under the EUPL, Version 1.2 or – as soon they
** will be approved by the European Commission - subsequent
** versions of the EUPL (the "Licence");
** You may not use this work except in compliance with the
** Licence.
** You may obtain a copy of the Licence at:
**
** https://joinup.ec.europa.eu/page/eupl-text-11-12
**
** Unless required by applicable law or agreed to in
** writing, software distributed under the Licence is
** distributed on an "AS IS" basis,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
** express or implied.
** See the Licence for the specific language governing
** permissions and limitations under the Licence.
**
** Lizenziert unter der EUPL, Version 1.2 oder - sobald
**  diese von der Europäischen Kommission genehmigt wurden -
** Folgeversionen der EUPL ("Lizenz");
** Sie dürfen dieses Werk ausschließlich gemäß
** dieser Lizenz nutzen.
** Eine Kopie der Lizenz finden Sie hier:
**
** https://joinup.ec.europa.eu/page/eupl-text-11-12
**
** Sofern nicht durch anwendbare Rechtsvorschriften
** gefordert oder in schriftlicher Form vereinbart, wird
** die unter der Lizenz verbreitete Software "so wie sie
** ist", OHNE JEGLICHE GEWÄHRLEISTUNG ODER BEDINGUNGEN -
** ausdrücklich oder stillschweigend - verbreitet.
** Die sprachspezifischen Genehmigungen und Beschränkungen
** unter der Lizenz sind dem Lizenztext zu entnehmen.
**
**************************************************************************/

// #include "config.h"
// #include "version.h"

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
#include <QTranslator>

#ifndef Q_OS_WIN
#include <unistd.h>
#endif
#include <iostream>

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
    app.setApplicationName(QStringLiteral("jmbde"));

    /**
     * enable high dpi support
     */
    app.setAttribute(Qt::AA_UseHighDpiPixmaps, true);

    /**
     * set the program icon
     */
    app.setWindowIcon(
        QIcon::fromTheme(QStringLiteral("jmbde"), app.windowIcon()));
    app.setOrganizationDomain(QStringLiteral("jmuelbert.github.io"));

#if defined(Q_OS_MAC) || defined(Q_OS_WIN)
    app.setApplicationName(QStringLiteral("jmbde"));
    app.setAttribute(Qt::AA_DontShowIconsInMenus);
#else
    app.setApplicationName(QStringLiteral("jmbde"));
#endif

    app.setApplicationDisplayName(QStringLiteral("jmbde"));
    app.setOrganizationName(QStringLiteral("jmuelbert.github.io"));
    app.setApplicationVersion(QLatin1String("0.4.25"));

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

    QString qmlDir = QApplication::applicationDirPath();
#ifdef Q_OS_WIN
    qmlDir += QStringLiteral("/qml");
#else
    qmlDir += QStringLiteral("../qml");
#endif

    QQmlApplicationEngine engine;
    engine.addImportPath(qmlDir);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return QApplication::exec();
}
