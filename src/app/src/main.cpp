/*
 * SPDX-FileCopyrightText: 2013-2022 Project jmbde-QT, Jürgen Mülbert
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include "jmbde_version.h"
#include "jmbdewidgets/mainwindow.h"

#include <CLI/CLI.hpp>
#include <spdlog/spdlog.h>


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
#if DEBUG
    QString locale = QLocale::system().name();
    qDebug() << "Set Locale to: " << locale;
     spdlog::info("Set Locale to: {}", locale);
#endif

    QTranslator translator;

#if defined (ENABLED_EMBEDED_TRANSLATION)
    qDebug() << "Use embeded translation";

    if (translator.load(QLocale(), QLatin1String("jmbde"), QLatin1String("_"), QLatin1String(":/i18n")))
        QCoreApplication::installTranslator(&translator);
#else
    qDebug() << "Use file based traslations from: " << "Translation Directory";
    if (translator.load(QLocale(), QLatin1String("jmbde"), QLatin1String("_"), QLatin1String("translations")))
    {
           QCoreApplication::installTranslator(&translator);
    }
#endif
    QApplication::installTranslator(&translator);

    QIcon::setFallbackSearchPaths(QIcon::fallbackSearchPaths() << QLatin1String(":tango"));
    QIcon::setThemeName(QLatin1String("tango"));

    QApplication::setLayoutDirection(QObject::tr("LTR") == QLatin1String("RTL") ? Qt::RightToLeft : Qt::LeftToRight);

    MainWindow w;
    w.show();

    return QApplication::exec();
}
