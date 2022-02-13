/*
 * SPDX-FileCopyrightText: 2013-2022 Project jmbde-QT, Jürgen Mülbert
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include "jmbde_version.h"
#include "jmbdewidgets/mainwindow.h"

/**
 * @brief main
 * @param argc The count of args
 * @param argv The arg Strings
 * @return 0 is executed successful
 */
auto main(int argc, char *argv[]) -> int
{
    QLoggingCategory::setFilterRules(QLatin1String("jmuelbert.jmbde.*.debug=true\njmuelbert.jmbde.*.info=true"));

    /**
     * Create application first
     */
    QApplication app(argc, argv);

    /**
     * Enforce application name even if the executable is renamed
     */
    QApplication::setApplicationName(QStringLiteral(PROJECT_NAME));

    /**
     * set the program icon
     */

    QApplication::setWindowIcon(QIcon::fromTheme(QStringLiteral(PROJECT_NAME)));

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
    qtTranslator.load(QLatin1String("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    QApplication::installTranslator(&qtTranslator);

    QTranslator jmbdeTranslator;
    jmbdeTranslator.load(QLatin1String("jmbde_") + locale);
    QApplication::installTranslator(&jmbdeTranslator);

    QIcon::setFallbackSearchPaths(QIcon::fallbackSearchPaths() << QLatin1String(":tango"));
    QIcon::setThemeName(QLatin1String("tango"));

    app.setProperty("jmbde_locale", locale);
    QApplication::setLayoutDirection(QObject::tr("LTR") == QLatin1String("RTL") ? Qt::RightToLeft : Qt::LeftToRight);

    MainWindow w;
    w.show();

    return QApplication::exec();
}
