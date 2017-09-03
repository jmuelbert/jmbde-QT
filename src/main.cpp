/*
 * main.cpp
 * jmbde
 *
 *  Copyright (c) 2013-2017 Jürgen Mülbert. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the European Union Public Licence (EUPL),
 * version 1.1.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * European Union Public Licence for more details.
 *
 * You should have received a copy of the European Union Public Licence
 * along with this program. If not, see
 * http://www.osor.eu/eupl/european-union-public-licence-eupl-v.1.1
 *
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

#include "constants.h"
#include "mainwindow.h"

/**
 * @brief fixedOptionsC
 */
static const char fixedOptionsC[] =
    "[OPTION]... [FILE]...\n"
    "Options:\n"
    "   -help                     Display this help\n"
    "   -version                 Display program version\n";

/**
 * @brief HELP_OPTION1
 */
static const char HELP_OPTION1[] = "-h";
/**
 * @brief HELP_OPTION2
 */
static const char HELP_OPTION2[] = "-help";
/**
 * @brief HELP_OPTION3
 */
static const char HELP_OPTION3[] = "/h";
/**
 * @brief HELP_OPTION4
 */
static const char HELP_OPTION4[] = "--help";
/**
 * @brief VERSION_OPTION
 */
static const char VERSION_OPTION[] = "-version";

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
int main(int argc, char *argv[]) {
  Application app(argc, argv);

  app.setApplicationName(QLatin1String(Constants::APPL_NAME));
  app.setApplicationVersion(QLatin1String(Constants::APPL_VERSION));
#if QT_VERSION >= 0x050000
  app.setApplicationDisplayName(QLatin1String(Constants::APPL_DISPLAYNAME));
#endif
  app.setOrganizationName(QLatin1String(Constants::COMPANY_NAME));

#ifdef Q_OS_MAC
  const QString &_creatorTrPath = QCoreApplication::applicationDirPath();
  QDir trPath(_creatorTrPath);
  trPath.cdUp();
  const QString &creatorTrPath = trPath.path();

  QString translationFileAndPath = QString(creatorTrPath);
  translationFileAndPath.append(QDir::separator());
  translationFileAndPath.append(QLatin1String("Resources"));
#else
  const QString &creatorTrPath = QCoreApplication::applicationDirPath();
  QString translationFileAndPath = QString(creatorTrPath);
#endif

  qDebug() << "Path " << creatorTrPath;

  QString locale = QLocale::system().name();

  QTranslator translator;

  translationFileAndPath.append(QDir::separator());
  translationFileAndPath.append(QLatin1String("translations"));
  translationFileAndPath.append(QDir::separator());
  translationFileAndPath.append(QLatin1String(Constants::APPL_NAME));
  translationFileAndPath.append(QLatin1Char('_'));
  translationFileAndPath.append(locale);

  qDebug() << "Translationfile = " << translationFileAndPath;

  translator.load(translationFileAndPath);
  app.installTranslator(&translator);

  MainWindow w;
  w.show();

  return app.exec();
}
