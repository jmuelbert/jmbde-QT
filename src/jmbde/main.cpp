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

#include <clocale>

#include "views/mainwindow.h"

#define STRINGIFY(x) #x
#define AS_STRING(x) STRINGIFY(x)

static QSettings *createUserSettings() {
  return new QSettings(QSettings::IniFormat, QSettings::UserScope,
                       QLatin1String("de.juergen-muelbert"),
                       QLatin1String("jmbde"));
}

static inline QSettings *userSettings() {
  QSettings *settings = createUserSettings();
  const QString fromVariant = QLatin1String("jmbde");
  if (fromVariant.isEmpty()) {
    return settings;
  }

  // Make sure to use the copied settings
  delete settings;
  return createUserSettings();
}

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

#if defined(Q_OS_MAC)
  QApplication::setAttribute(Qt::AA_DontShowIconsInMenus);
#endif

  // These settings needs to be set before any QSettings object
#if defined(Q_OS_MAC) || defined(Q_OS_WIN)
  QCoreApplication::setApplicationName(QLatin1String("jmBDE"));
#else
  QCoreApplication::setApplicationName(QLatin1String("jmbde"));
#endif

  QGuiApplication::setApplicationDisplayName(QLatin1String("jmbde"));
  QCoreApplication::setOrganizationName(QLatin1String("jmbde"));
  QCoreApplication::setOrganizationDomain(QLatin1String("de.juergen.muelbert"));

#ifdef GIT_REVISION
  QCoreApplication::setApplicationVersion(
      QSL("%1 (%2)").arg(JMBDE_VERSION, GIT_REVISION));
#else
  QCoreApplication::setApplicationVersion(QSL(AS_STRING(JMBDE_VERSION)));
#endif

#if defined(Q_OS_MAC)
  QFileInfo appInfo(QString::fromUtf8(argv[0]));
  QDir appDir(appInfo.absolutePath());
  appDir.cdUp();
  QCoreApplication::addLibraryPath(
      appDir.absoluteFilePath(QLatin1Literal("plugins")));
#elif defined(Q_OS_WIN)
  QFileInfo appInfo(QString::fromUtf8(argv[0]));
  QCoreApplication::addLibraryPath(appInfo.absolutePath());
#endif

  QGuiApplication::setDesktopSettingsAware(false);

#ifndef USE_QUICKVIEW
  QApplication::setStyle(QStyleFactory::create(QLatin1Literal("Fusion")));
  // The QApplication MUST be created before the StelFileMgr is initialized.
  QApplication app(argc, argv);
#else
  QGuiApplication::setDesktopSettingsAware(false);
  QGuiApplication app(argc, argv);
#endif

  QCommandLineParser parser;
  parser.setApplicationDescription(QLatin1String("jmbde - Commandline"));
  parser.addHelpOption();
  parser.addVersionOption();
  // Must be done before any QSettings class is created
  QSettings::setDefaultFormat(QSettings::IniFormat);

  QSettings *settings = userSettings();

  QSettings *globalSettings = new QSettings(
      QSettings::IniFormat, QSettings::SystemScope,
      QLatin1String("de.juergen-muelbert"), QLatin1String("jmbde"));

  QTranslator translator;
  QTranslator qtTranslator;
  QStringList uiLanguages;

  uiLanguages = QLocale::system().uiLanguages();
  QString overideLanguage =
      settings->value(QLatin1Literal("General/OverrideLanguage")).toString();
  if (!overideLanguage.isEmpty()) {
    uiLanguages.prepend(overideLanguage);
  }

  const QString &appDirPath = QCoreApplication::applicationDirPath();
  QString translationFileAndPath;

#ifdef Q_OS_MAC
  QDir trPath(appDirPath);

  trPath.cdUp();
  const QString &creatorTrPath = trPath.path();

  translationFileAndPath = QString(creatorTrPath);

  translationFileAndPath.append(QDir::separator());
  translationFileAndPath.append(QLatin1Literal("Resources"));
#else
  translationFileAndPath = QString(appDirPath);
#endif

  translationFileAndPath.append(QDir::separator());
  translationFileAndPath.append(QLatin1String("translations"));

  for (auto locale : uiLanguages) {
    locale = QLocale(locale).name();
    QString myLangId = QLatin1String("jmbde");
    myLangId.append(QLatin1String("_"));
    myLangId.append(locale);
    if (translator.load(myLangId, translationFileAndPath)) {
      const QString &qtTrPath =
          QLibraryInfo::location(QLibraryInfo::TranslationsPath);
      const QString &qtTrFile = QLatin1String("qt_") + locale;
      // Binary installer puts Qt tr files into creatorTrPath
      if (qtTranslator.load(qtTrFile, qtTrPath) ||
          qtTranslator.load(qtTrFile, translationFileAndPath)) {
        app.installTranslator(&translator);
        app.installTranslator(&qtTranslator);
        app.setProperty("jmbde_locale", locale);
        break;
      }
      translator.load(QString()); // unload()
    } else if (locale ==
               QLatin1Literal("C") /* overrideLanguage == "English" */) {
      // use built-in
      break;
    } else if (locale.startsWith(
                   QLatin1Literal("en")) /* "English is built-in */) {
      // use built-in
      break;
    }
  }

  MainWindow w;
  w.show();

  return app.exec();
}
