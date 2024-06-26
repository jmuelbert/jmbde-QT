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

#include "jmbdeappquick-version.h"
#include "quick/maincontroller.h"

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
int main(int argc, char *argv[])
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
   * enable high dpi support
   */

  /**
   * allow fractional scaling
   * we only activate this on Windows, it seems to creates problems on unices
   * (and there the fractional scaling with the QT_... env vars as set by
   * KScreen works) see bug 416078
   */
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0) && defined(Q_OS_WIN)
  QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
#endif

  /**
   * Create application first
   */
  QApplication app(argc, argv);

  /**
   * set the program icon
   */
  QApplication::setWindowIcon(QIcon::fromTheme(QLatin1String("jmbde"), QApplication::windowIcon()));

  /**
   * For Windows and macOS: use Breeze if available
   * Of all tested styles that works the best for us
   */
#if defined(Q_OS_MACOS) || defined(Q_OS_WIN)
  QApplication::setAttribute(Qt::AA_DontShowIconsInMenus);
  QApplication::setStyle(QStringLiteral("breeze"));
#endif

  QApplication::setApplicationName(QLatin1String("jmbde"));
  QApplication::setApplicationDisplayName(QLatin1String("jmbde"));
  QApplication::setOrganizationName(QStringLiteral("io.jmuelbert.github"));
  QApplication::setOrganizationName(QLatin1String("jmuelbert.github.io"));
  QApplication::setApplicationVersion(QLatin1String(JMBDEAPPQUICK_VERSION_STRING));

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

  MainController mainController;

  if (!mainController.initialize()) { return -1; }

  return QApplication::exec();
}
