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

/**
 * \brief The jmbde program
 * \details this will help manage employees, accounts and it hardware
 *
 * \author Jürgen Mülbert
 * \version 0.4.0
 * \date 03.09.2017
 * \copyright EUPL V1.1
 *
 *
 * \mainpage jmbde
 *
 *
 * This is the introduction.
 *
 */

#include <QDebug>
#include <QObject>

#ifndef USE_QUICKVIEW
#include <QApplication>
#include <QMessageBox>
#else
#include <QGuiApplication>
#endif

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
#include <QTranslator>
#include <QStyleFactory>
#include <QCommandLineParser>


#include "views/mainwindow.h"

#define STRINGIFY(x) #x
#define AS_STRING(x) STRINGIFY(x)

/*! \mainpage jmBDE
 *
 * \section intro_sec Introduction
 * 
 * jmbde is a tool to collect data for a company.
 * 
 * https://jmuelbert.github.io/jmbde-QT/
 * 
 * \section install_sec Installation
 * 
 * \subsection dependencies Dependencies
 * 
 * - jmBDE requieres Qt 5.12 or later
 * - Linguist package is required to compile the translations.
 * - For use of the fallback icons the SVG library is required.
 * 
 * \subsection source From source
 * 
 * On most *nix systems all you need is:
 * 
 * `qmake && make && make install``
 */



/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[]) {

  QLoggingCategory::setFilterRules(
      QLatin1String("jmbde.*.debug=false\njmbde.*.info=false"));

#if QT_VERSION >= 0x050600
  QGuiApplication::setFallbackSessionManagementEnabled(false);
#endif

  // Enable support for highres images (added in Qt 5.1, but off by default)
  QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

#if QT_VERSION >= QT_VERSION_CHECK(5, 10, 0)
  QGuiApplication::setAttribute(Qt::AA_DisableWindowContextHelpButton);
#endif

#ifndef USE_QUICKVIEW
  QApplication::setStyle(QStyleFactory::create(QLatin1Literal("Fusion")));
  // The QApplication MUST be created before the StelFileMgr is initialized.
  QApplication app(argc, argv);
#else
  QGuiApplication::setDesktopSettingsAware(false);
  QGuiApplication app(argc, argv);
#endif

QApplication::setOrganizationDomain(QLatin1String("jmuelbert.github.io"));


#if defined(Q_OS_MAC) || defined(Q_OS_WIN)
  QApplication::setApplicationName(QLatin1String("JMBde"));
#else
  QApplication::setApplicationName(QLatin1String("jmbde"));
#endif

QApplication::setApplicationDisplayName(QLatin1String("JMBde"));
QApplication::setOrganizationName(QLatin1String("jmbde"));
QApplication::setApplicationVersion(QLatin1String(AS_STRING(JMBDE_VERSION)));

#if defined(Q_OS_MAC)
  QApplication::setAttribute(Qt::AA_DontShowIconsInMenus);
#endif

  QCommandLineParser parser;
  parser.setApplicationDescription(QLatin1String("jmbde - Commandline"));
  parser.addHelpOption();
  parser.addVersionOption();

  // Must be done before any QSettings class is created
  QSettings::setDefaultFormat(QSettings::IniFormat);


  // Setup and load translator for localization-
  QString locale = QLocale::system().name();
   QTranslator qtTranslator;
    qtTranslator.load(QLatin1String("qt_") + locale,
            QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    QApplication::installTranslator(&qtTranslator);

    QTranslator jmbdeTranslator;
    jmbdeTranslator.load(QLatin1String("jmbde_") + locale);
    QApplication::installTranslator(&jmbdeTranslator);

  app.setProperty("jmbde_locale", locale);
  QApplication::setLayoutDirection(
    QObject::tr("LTR") == QLatin1String("RTL") ? Qt::RightToLeft : Qt::LeftToRight);

  MainWindow w;
  w.show();

  return QApplication::exec();
}

