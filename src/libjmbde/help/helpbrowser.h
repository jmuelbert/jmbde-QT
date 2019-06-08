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

#ifndef HELPBROWSER_H
#define HELPBROWSER_H

#include <QObject>

#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QHelpEngine>
#include <QLibraryInfo>
#include <QLoggingCategory>
#include <QTextBrowser>

class QHelpEngineCore;

//! The jmbde Help System
/*!
  \page Help Help
  The first implenmentation of the help-system
*/
class HelpBrowser : public QTextBrowser {
    Q_OBJECT
    Q_LOGGING_CATEGORY(helpSystem, "jmbde.help")

public:
    //! The HelpBrowser Constructor.
    /*!
     * \brief HelpBrowser
     * \param parent
     */
    explicit HelpBrowser(QWidget *parent = nullptr);

    //! The ContextHelp Fuction
    /*!
     * \brief showHelpForKeyWord
     * \param id
     */
    void showHelpForKeyWord(const QString &id);

signals:

public slots:

private:
    /*!
     * \brief loadResource
     * \param type
     * \param name
     * \return
     */
    QVariant loadResource(int type, const QUrl &name) override;
    /*!
     * \brief m_helpEngine
     */
    QHelpEngine *m_helpEngine;
};

#endif // HELPBROWSER_H
