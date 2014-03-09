/*
 * helpbrowser.cpp - HelpBrowser
 *
 * Created by Jürgen Mülbert on 09.03.2014
 * Copyright (c) 2014 Jürgen Mülbert. All rights reserved.
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


#include "helpbrowser.h"

HelpBrowser::HelpBrowser(QWidget *parent) :
    QTextBrowser(parent)
{
#ifdef Q_OS_MAC
        const QString &_creatorTrPath = QCoreApplication::applicationDirPath();
        QDir trPath(_creatorTrPath);
        trPath.cdUp();
        const QString &creatorTrPath = trPath.path();

        QString helpFileAndPath = QString(creatorTrPath);
        helpFileAndPath.append(QDir::separator());
        helpFileAndPath.append(QLatin1String("Resources"));
#else
        const QString &creatorTrPath = QCoreApplication::applicationDirPath();
         QString helpFileAndPath = QString(creatorTrPath);
#endif

        QString collectionFile = helpFileAndPath
                + QLatin1String("/help/help.qch");

        qDebug() << "HelpPath " << collectionFile;

        m_helpEngine = new QHelpEngine(collectionFile, this);
        if (!m_helpEngine->setupData()) {
            delete m_helpEngine;
            m_helpEngine = 0;
        }
}

void HelpBrowser::showHelpForKeyWord(const QString &id)
{
    if (m_helpEngine) {
        QMap<QString, QUrl> links = m_helpEngine->linksForIdentifier(id);
        if (links.count()) {
            setSource(links.constBegin().value());
        }
    }
}

QVariant HelpBrowser::loadResource(int type, const QUrl &name)
{
    QByteArray ba;

    if (type < 4 && m_helpEngine) {
        QUrl url(name);
        if (name.isRelative()) {
            url = source().resolved(url);
        }
        ba = m_helpEngine->fileData(url);
    }
    return ba;
}


QWidget *HelpBrowser::getContentWidget()
{
    return (QWidget *) m_helpEngine->contentWidget();
}

QWidget *HelpBrowser::getLinkWidget()
{
    return (QWidget *) m_helpEngine->indexWidget();
}
