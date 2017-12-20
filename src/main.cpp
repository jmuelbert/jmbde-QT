/*
   // main.cpp
   // part of jmbde
   //
   // Copyright (c) 2013-2017 Jürgen Mülbert. All rights reserved.
   //
   // Licensed under the EUPL, Version 1.2 or – as soon they
   // will be approved by the European Commission - subsequent
   // versions of the EUPL (the "Licence");
   // You may not use this work except in compliance with the
   // Licence.
   // You may obtain a copy of the Licence at:
   //
   // https://joinup.ec.europa.eu/page/eupl-text-11-12
   //
   // Unless required by applicable law or agreed to in
   // writing, software distributed under the Licence is
   // distributed on an "AS IS" basis,
   // WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
   // express or implied.
   // See the Licence for the specific language governing
   // permissions and limitations under the Licence.
   //
   // Lizenziert unter der EUPL, Version 1.2 oder - sobald
   // diese von der Europäischen Kommission genehmigt wurden -
   // Folgeversionen der EUPL ("Lizenz");
   // Sie dürfen dieses Werk ausschließlich gemäß
   // dieser Lizenz nutzen.
   // Eine Kopie der Lizenz finden Sie hier:
   //
   // https://joinup.ec.europa.eu/page/eupl-text-11-12
   //
   // Sofern nicht durch anwendbare Rechtsvorschriften
   // gefordert oder in schriftlicher Form vereinbart, wird
   // die unter der Lizenz verbreitete Software "so wie sie
   // ist", OHNE JEGLICHE GEWÄHRLEISTUNG ODER BEDINGUNGEN -
   // ausdrücklich oder stillschweigend - verbreitet.
   // Die sprachspezifischen Genehmigungen und Beschränkungen
   // unter der Lizenz sind dem Lizenztext zu entnehmen.
   //
 */

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

#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QLibraryInfo>
#include <QSettings>
#include <QTextStream>
#include <QTranslator>

#include "definitions.h"
#include "mainwindow.h"

#ifdef Q_OS_MAC
#define SHARE_PATH "/../Resources"
#else
#define SHARE_PATH "/../share/jmbde"
#endif

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char* argv[]) {
  for (int i = 0; i < argc; i++) {
    const QString str = QString::fromLocal8Bit(argv[i]);

    if (str == "-h") {
      qDebug("Usage: jmbde [OPTIONS\n\n"
             "Option\t\tMeaning\n"
             "-h\t\tDisplays this help.");
      return EXIT_SUCCESS;
    }
  }

  QApplication app(argc, argv);

  qDebug("Instantiated Application class.");

#if defined (Q_OS_MAC)
  QApplication::setAttribute(Qt::AA_DontShowIconsInMenus);
#endif

  // These settings needs to be set before any QSettings object
  QCoreApplication::setApplicationName(APP_NAME);
  QCoreApplication::setApplicationVersion(APP_VERSION);
  QCoreApplication::setOrganizationName(APP_ORG_NAME);
  QCoreApplication::setOrganizationDomain(APP_ORG_NAME);

#if defined (QT_DEBUG)
    #if defined (Q_OS_MAC)
  QSettings settings(QSettings::IniFormat, QSettings::UserScope, APP_ORG_NAME, APP_NAME);
    #else
  QSettings settings(QSettings::IniFormat, QSettings::UserScope, APP_URL, APP_NAME);
    #endif
#endif

#if defined (Q_QS_WIN)
  QApplication::setWindowIcon(QIcon(APP_ICON_PATH));
#endif

#ifdef Q_OS_MAC
  const QString& _creatorTrPath = QCoreApplication::applicationDirPath();
  QDir trPath(_creatorTrPath);

  trPath.cdUp();
  const QString& creatorTrPath = trPath.path();

  qDebug() << "ApplicationDirPath : " << creatorTrPath;

  QString translationFileAndPath = QString(creatorTrPath);

  translationFileAndPath.append(QDir::separator());
  translationFileAndPath.append(QLatin1String("Resources"));
#else
  const QString& creatorTrPath = QCoreApplication::applicationDirPath();
  QString translationFileAndPath = QString(creatorTrPath);
#endif

  translationFileAndPath.append(QDir::separator());
  translationFileAndPath.append(QLatin1String("translations"));

  qDebug() << "TranslationDirPath : " << translationFileAndPath;

  QTranslator translator;

  // look up e.g. translations/jmbde_de.qm
  if (translator.load(QLocale(), QLatin1String(APP_NAME), QLatin1String("_"), QString(translationFileAndPath))) {
    app.installTranslator(&translator);
  }
  else {
    qDebug() << "The Translation can't load at " << translationFileAndPath << " : " << QLocale() << " : " << QLatin1String(APP_NAME);
  }

  MainWindow w;

  w.show();

  return app.exec();
}
