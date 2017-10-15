/*
// helpbrowser.cpp - HelpBrowser
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


#include "helpbrowser.h"

HelpBrowser::HelpBrowser(QWidget *parent) : QTextBrowser(parent) {
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

  QString collectionFile = helpFileAndPath + QLatin1String("/help/help.qch");

  qDebug() << "HelpPath " << collectionFile;

  m_helpEngine = new QHelpEngine(collectionFile, this);
  if (!m_helpEngine->setupData()) {
    delete m_helpEngine;
    m_helpEngine = 0;
  }
}

void HelpBrowser::showHelpForKeyWord(const QString &id) {
  if (m_helpEngine) {
    QMap<QString, QUrl> links = m_helpEngine->linksForIdentifier(id);
    if (links.count()) {
      setSource(links.constBegin().value());
    }
  }
}

QVariant HelpBrowser::loadResource(int type, const QUrl &name) {
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

QWidget *HelpBrowser::getContentWidget() {
  return (QWidget *)m_helpEngine->contentWidget();
}

QWidget *HelpBrowser::getLinkWidget() {
  return (QWidget *)m_helpEngine->indexWidget();
}
