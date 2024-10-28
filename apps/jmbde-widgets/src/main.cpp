/*
 * SPDX-FileCopyrightText: 2013-2022 Project jmbde-QT, Jürgen Mülbert
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include "jmbde_version.h"
#include "jmbdewidgets/mainwindow.h"

/*************  ✨ Codeium Command 🌟  *************/
/**
 * @brief main
 * @param argc The count of args
 * @param argv The arg Strings
 * @return 0 is executed successful
 *
 * This function creates a QApplication instance and sets up the necessary
 * options for it. It also creates a instance of the main window and shows it.
 */
auto main(int argc, char *argv[]) -> int
{
    /**
     * Set logging category rules
     *
     * This will enable the logging of debug and info messages for the given
     * categories.
     */
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
     * For Windows and macOS: use Breeze if available
     * Of all tested styles that works the best for us
     */
#if defined(Q_OS_MACOS) || defined(Q_OS_WIN)
    QApplication::setAttribute(Qt::AA_DontShowIconsInMenus);
    QApplication::setStyle(QStringLiteral("breeze"));
#endif

    /**
     * set the program icon
     *
     * This icon is used in the window title and in the taskbar. On macOS it is
     * also used in the dock.
     */

    QApplication::setWindowIcon(QIcon::fromTheme(QStringLiteral(PROJECT_NAME)));

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

    parser.setApplicationDescription(QStringLiteral("jmbde - Commandline"));
    parser.addHelpOption();
    parser.addVersionOption();

    /**
     * do the command line parsing
     */
    parser.process(app);

    qDebug() << "Set Locale to: " << QLocale::system().name();

    QTranslator translator;

#if defined(ENABLED_EMBEDDED_TRANSLATION)
    /**
     * Use embedded translations
     */
    qDebug() << "Use embedded translation";

    if (translator.load(QLocale(), QLatin1String("jmbde"), QLatin1String("_"), QLatin1String(":/i18n")))
        QCoreApplication::installTranslator(&translator);
#else
    /**
     * Use file based translations from translations directory
     */
    qDebug() << "Use file based translations from: " << "Translation Directory";
    qDebug() << "Use file based translations from: "
             << "Translation Directory";
    if (translator.load(QLocale(), QLatin1String("jmbde"), QLatin1String("_"), QLatin1String("translations"))) {
        QCoreApplication::installTranslator(&translator);
    }
#endif
    QApplication::installTranslator(&translator);

    /**
     * Set default icons for the application
     */
    QIcon::setFallbackSearchPaths(QIcon::fallbackSearchPaths() << QLatin1String(":tango"));
    QIcon::setThemeName(QLatin1String("tango"));

    /**
     * Set the layout direction of the application
     */
    QApplication::setLayoutDirection(QObject::tr("LTR") == QLatin1String("RTL") ? Qt::RightToLeft : Qt::LeftToRight);

    /**
     * Create the main window
     */
    MainWindow w;
    w.show();

    /**
     * Enter the main event loop
     */
    return QApplication::exec();
}
/******  85bb567a-2ca7-412a-bae3-e681d3672e8f  *******/
