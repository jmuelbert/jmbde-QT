/*
 * main.cpp
 * jmbde
 *
 *  Copyright (c) 2013 Jürgen Mülbert. All rights reserved.
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


#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QTranslator>
#include <QLibraryInfo>
#include <QApplication>
#include <QTextStream>
#include <QSettings>

#include "constants.h"
#include "mainwindow.h"

/**
 * @brief fixedOptionsC
 */
static const char fixedOptionsC[]=
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
#define SHARE_PATH "/../share/bde"
#endif


/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



 #ifdef Q_OS_MAC
    const QString &_creatorTrPath = QCoreApplication::applicationDirPath();
     QDir trPath(_creatorTrPath);
     trPath.cdUp();
     const QString &creatorTrPath = trPath.path();

     QString translationFileAndPath = QString(creatorTrPath);
     translationFileAndPath.append(QDir::separator());
     translationFileAndPath.append("Resources");
 #else
    const QString &creatorTrPath = QCoreApplication::applicationDirPath();
     QString translationFileAndPath = QString(creatorTrPath);
 #endif
    qDebug() << "Path " << creatorTrPath;


    QString locale = QLocale::system().name();

    QTranslator translator;

    translationFileAndPath.append(QDir::separator());
    translationFileAndPath.append("translations");
    translationFileAndPath.append(QDir::separator());
    translationFileAndPath.append(Constants::APPL_NAME);
    translationFileAndPath.append('_');
    translationFileAndPath.append(locale);

    qDebug() << "Translationfile = " << translationFileAndPath;

    translator.load(translationFileAndPath);
    a.installTranslator(&translator);

    MainWindow w;
    w.show();
    
    return a.exec();
}
