/*
   jmbde a BDE Tool for companies
   Copyright (C) 2013-2020  Jürgen Mülbert

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
*/

#include <QQmlApplicationEngine>
#include <QQuickWidget>

#include "ui_mainwindow.h"
#include "views/mainwindow.h"

Q_LOGGING_CATEGORY(jmbdeWidgetsMainWindowLog, "jmuelbert.jmbde.widgets.mainwindow", QtWarningMsg)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString title;
    title.append(QApplication::applicationDisplayName());
    title.append(QLatin1String(" "));
    title.append(QApplication::applicationVersion());
    setWindowTitle(title);

    ui->scrollArea->setWidgetResizable(true);

    readSettings();

    initOutline();

    this->dataBaseName = QString(QApplication::applicationName());
    this->dataContext = new Model::DataContext(dynamic_cast<QObject *>(this), this->dataBaseName);

    qCDebug(jmbdeWidgetsMainWindowLog) << tr("ActualViewRow : ") << m_actualView;

    if (m_actualView.row() > 0) {
        ui->treeView->setCurrentIndex(m_actualView);
        onClickedTreeView(m_actualView);
    } else {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Setze aktuelle Ansicht: Mitarbeiter - Tabelle");
        actualView = VIEW_EMPLOYEE;
        auto *edm = new Model::Employee;
        tableModel = edm->initializeRelationalModel();
        int idx = edm->LastNameIndex();

        ui->listView->setModel(tableModel);
        ui->listView->setModelColumn(idx);

        auto *employeeTable = new EmployeeTable(QStringLiteral("employee"), tableModel, ui->scrollArea);
        QSize AdjustSize = employeeTable->size();
        AdjustSize.width();
        employeeTable->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(employeeTable);
    }

    connect(ui->treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(onClickedTreeView(QModelIndex)));
    connect(ui->listView, SIGNAL(clicked(QModelIndex)), this, SLOT(onClickedListViewRow(QModelIndex)));
    connect(ui->listView, SIGNAL(pressed(QModelIndex)), this, SLOT(onPressedListViewRow(QModelIndex)));
}

MainWindow::~MainWindow()
{
    dataContext->~DataContext();
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)

    const int OFFSET = 20;

    int width = ui->centralWidget->width() - OFFSET;
    int height = ui->centralWidget->height() - OFFSET;

    ui->splitter->resize(width, height);
}

void MainWindow::focusChanged(QWidget *qWidget, QWidget *now)
{
    Q_UNUSED(qWidget)
    Q_UNUSED(now)

    qCDebug(jmbdeWidgetsMainWindowLog) << tr("Der Fokus hat sich geändert");
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    qCDebug(jmbdeWidgetsMainWindowLog) << tr("Der Close Event");
}

void MainWindow::on_actionPreferences_triggered()
{
    auto *view = new QQuickWidget;
    view->setSource(QUrl(QStringLiteral("qrc:/qml/Preferences.qml")));
    if (view->status() == QQuickWidget::Error)
        return;
    view->show();
}

void MainWindow::on_actionAbout_triggered()
{
    auto *view = new QQuickWidget;
    view->setSource(QUrl(QStringLiteral("qrc:/qml/AboutBox.qml")));
    if (view->status() == QQuickWidget::Error)
        return;
    view->show();
}

void MainWindow::initOutline()
{
    QHash<QString, QList<QString>> outlineData;

    QList<QString> subEntries = {tr("Mitarbeiter"), tr("Funktion"), tr("Abteilung"), tr("Titel")};
    outlineData.insert(tr("Person"), subEntries);

    subEntries = {tr("Computer"), tr("Prozessor"), tr("Betriebssystem"), tr("Software"), tr("Drucker")};
    outlineData.insert(tr("Gerät"), subEntries);

    subEntries = {tr("Telefon"), tr("Mobiltelefon")};
    outlineData.insert(tr("Kommunikation"), subEntries);

    subEntries = {tr("Hersteller"), tr("Stadt"), tr("Schlüsselchip")};
    outlineData.insert(tr("Verschiedenes"), subEntries);

    m_treeviewModel = new QStandardItemModel(this);
    QStandardItem *parentItem = m_treeviewModel->invisibleRootItem();

    QStandardItem *item;

    QList<QString> od;
    QHashIterator<QString, QList<QString>> i(outlineData);
    while (i.hasNext()) {
        i.next();
        auto *header = new QStandardItem(i.key());
        parentItem->appendRow(header);
        qCDebug(jmbdeWidgetsMainWindowLog) << "initOutline(): (" << i.key() << ": " << i.value() << " )" << endl;

        od = i.value();
        for (int index = 0; index < od.size(); ++index) {
            item = new QStandardItem(od.value(index));
            header->appendRow(item);
            qCDebug(jmbdeWidgetsMainWindowLog) << "initOutline(): (Gefunden :" << od.value(index) << " an der Position)" << index << endl;
        }
    }

    ui->treeView->setModel(m_treeviewModel);
    ui->treeView->expandAll();
}

/**
 * @brief MainWindow::writeSettings
 *
 *    category: "WindowState"
 *        property alias window_x:    appWindow.x
 *        property alias window_y:    appWindow.y
 *        property alias window_width: appWindow.width
 *        property alias window_height: appWindow.height
 *
 *    category: "Database"
 *        property alias type: cbDatabaseType.currentIndex
 *        property alias connection: textDBConnection.text
 *        property alias hostname: textInputHostname.text
 *        property alias username: textInputUsername.text
 *        property alias password: textInputPassword.text
 */
void MainWindow::writeSettings()
{
    QSettings settings;

    settings.beginGroup(QLatin1String(Settings::Groups::WINDOWSSTATE));
    settings.setValue(QLatin1String(Settings::WindowState::WINDOW_X), ui->centralWidget->x());
    settings.setValue(QLatin1String(Settings::WindowState::WINDOW_Y), ui->centralWidget->y());
    settings.setValue(QLatin1String(Settings::WindowState::WINDOW_WIDTH), ui->centralWidget->width());
    settings.setValue(QLatin1String(Settings::WindowState::WINDOW_HEIGHT), ui->centralWidget->height());
    settings.endGroup();

    // dataContext settings
    settings.beginGroup(QLatin1String(Settings::Groups::DATABASE));
    settings.setValue(QLatin1String(Settings::Database::TYPE), dbType);
    settings.setValue(QLatin1String(Settings::Database::CONNECTION), dbConnection);
    settings.setValue(QLatin1String(Settings::Database::HOSTNAME), dbHostname);
    settings.setValue(QLatin1String(Settings::Database::USERNAME), dbUsername);
    settings.setValue(QLatin1String(Settings::Database::PASSWORD), dbPassword);
    settings.endGroup();
}

void MainWindow::readSettings()
{
    QSettings settings;

    const int DEFAULT_WINDOW_X = 200;
    const int DEFAULT_WINDOW_Y = 200;
    const int DEFAULT_WINDOW_WIDTH = 800;
    const int DEFAULT_WINDOW_HEIGHT = 600;

    settings.beginGroup(QLatin1String(Settings::Groups::WINDOWSSTATE));
    int window_x = settings.value(QLatin1String(Settings::WindowState::WINDOW_X), DEFAULT_WINDOW_X).toInt();
    int window_y = settings.value(QLatin1String(Settings::WindowState::WINDOW_Y), DEFAULT_WINDOW_Y).toInt();
    int window_width = settings.value(QLatin1String(Settings::WindowState::WINDOW_WIDTH), DEFAULT_WINDOW_WIDTH).toInt();
    int window_height = settings.value(QLatin1String(Settings::WindowState::WINDOW_HEIGHT), DEFAULT_WINDOW_HEIGHT).toInt();

    move(window_x, window_y);
    resize(window_width, window_height);
    settings.endGroup();

    // dataContext settings

    QString dataContextDir = QStandardPaths::writableLocation(QStandardPaths::DataLocation);

    settings.beginGroup(QLatin1String(Settings::Groups::DATABASE));
    dbType = settings.value(QLatin1String(Settings::Database::TYPE), SQLITE).toInt();
    dbConnection = settings.value(QLatin1String(Settings::Database::CONNECTION), dataContextDir).toString();
    dbHostname = settings.value(QLatin1String(Settings::Database::HOSTNAME), QLatin1String("localhost")).toString();
    dbUsername = settings.value(QLatin1String(Settings::Database::USERNAME), QLatin1String("jmbde")).toString();
    dbPassword = settings.value(QLatin1String(Settings::Database::PASSWORD), QLatin1String("jmbde")).toString();
}

void MainWindow::on_actionNew_triggered()
{
    int ret = QMessageBox::warning(this,
                                   QApplication::applicationDisplayName(),
                                   tr("Mit diesem Befehl wird einen neue Datenbank erzeugt\n"
                                      "Wenn Sie hier fortsetzen verlieren Sie möglicherweise Daten\n"
                                      "Möchten Sie die den Vorgang fortsetzen ?"),
                                   QMessageBox::Cancel | QMessageBox::Yes);

    if (ret == QMessageBox::Yes) {
        QString message = tr("Noch nicht vollständig implementiert!");
        notAvailableMessage(message);
        QMessageBox::information(this, qApp->applicationDisplayName(), tr("The new dataContext is created"));
    }
}

void MainWindow::on_actionQuit_triggered()
{
    qApp->quit();
}

void MainWindow::on_actionOpen_triggered()
{
    QString message = tr("Menü: öffnen");
    notAvailableMessage(message);
}

void MainWindow::on_actionImport_triggered()
{
    auto *csvImport = new CsvImportDialog();

    csvImport->show();

    QString message = tr("Menu: Import aus CSV");
    notAvailableMessage(message);
}

void MainWindow::on_actionExport_triggered()
{
    QString message = tr("Menu: Export zu CSV");
    notAvailableMessage(message);
}

void MainWindow::on_actionPrint_triggered()
{
    QTextDocument doc;

    switch (actualView) {
    case VIEW_EMPLOYEE: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Mitarbeiter !");
        QString style = Model::Employee::setOutTableStyle();
        auto *edm = new Model::Employee;
        QString text = edm->generateTableString(tr("Mitarbeiter"));

        doc.setHtml(style + text);
    } break;

    case VIEW_COMPUTER: {
        qDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Computer !");
        QString style = Model::Computer::setOutTableStyle();
        auto *cdm = new Model::Computer;
        QString text = cdm->generateTableString(tr("Computer"));

        doc.setHtml(style + text);
    } break;

    case VIEW_PRINTER: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Drucker !");
        QString style = Model::Printer::setOutTableStyle();
        auto *pdm = new Model::Printer;
        QString text = pdm->generateTableString(tr("Drucker"));

        doc.setHtml(style + text);
    } break;

    case VIEW_PHONE: {
        qCDebug(jmbdeWidgetsMainWindowLog) << "Drucke Telefone !";
        QString style = Model::Phone::setOutTableStyle();
        auto *pdm = new Model::Phone;
        QString text = pdm->generateTableString(tr("Telefon"));

        doc.setHtml(style + text);
    } break;

    default:
        QString message = tr("Drucken unbekanntes Submodul");
        notAvailableMessage(message);
        qCCritical(jmbdeWidgetsMainWindowLog) << tr("on_actionPrint_triggered(): Unbekanntes Sub-Modul");
    }

#if !defined(QT_NO_PRINTER) && !defined(QT_NO_PRINTDIALOG)
    QPrinter printer(QPrinter::HighResolution);

    printer.setOrientation(QPrinter::Landscape);
    QPrintDialog *dlg = new QPrintDialog(&printer, this);

    dlg->setWindowTitle(tr("Drucke Dokument"));
    if (dlg->exec() == QDialog::Accepted)
        doc.print(&printer);
    delete dlg;
#endif
}

void MainWindow::on_action_Export_Pdf_triggered()
{
    QTextDocument doc;

    switch (actualView) {
    case VIEW_EMPLOYEE: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Mitarbeiter !");

        QString style = Model::Employee::setOutTableStyle();
        auto *edm = new Model::Employee;
        QString text = edm->generateTableString(tr("Mitarbeiter"));

        doc.setHtml(style + text);
    } break;

    case VIEW_COMPUTER: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Computer !");

        QString style = Model::Computer::setOutTableStyle();
        auto *cdm = new Model::Computer;
        QString text = cdm->generateTableString(tr("Computer"));

        doc.setHtml(style + text);
    } break;

    case VIEW_PRINTER: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Drucker !");

        QString style = Model::Printer::setOutTableStyle();
        auto *pdm = new Model::Printer;
        QString text = pdm->generateTableString(tr("Drucker"));

        doc.setHtml(style + text);
    } break;

    case VIEW_PHONE: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Telefone !");

        QString style = Model::Phone::setOutTableStyle();
        auto *pdm = new Model::Phone;
        QString text = pdm->generateTableString(tr("Telefon"));

        doc.setHtml(style + text);
    } break;

    default:
        QString message = tr("Drucken unbekanntes Submodul");
        notAvailableMessage(message);
        qCCritical(jmbdeWidgetsMainWindowLog) << tr("on_action_Export_Pdf_triggered(): Unbekanntes Sub-Modul");
    }

#ifndef QT_NO_PRINTER

    // ! [0]
    QString fileName = QFileDialog::getSaveFileName(this, QLatin1String("Export PDF"), QString(), QLatin1String("*.pdf"));

    if (!fileName.isEmpty()) {
        if (QFileInfo(fileName).suffix().isEmpty())
            fileName.append(QLatin1String(".pdf"));

        QPrinter printer(QPrinter::HighResolution);

        printer.setOrientation(QPrinter::Landscape);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
        doc.print(&printer);
    }

// ! [0]
#endif
}

void MainWindow::on_actionPrint_Preview_triggered()
{
    QTextDocument doc;

    switch (actualView) {
    case VIEW_EMPLOYEE: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Mitarbeiter !");

        QString style = Model::Employee::setOutTableStyle();
        auto *edm = new Model::Employee;
        QString text = edm->generateTableString(tr("Mitarbeiter"));

        doc.setHtml(style + text);
    } break;

    case VIEW_COMPUTER: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Computer !");

        QString style = Model::Computer::setOutTableStyle();
        auto *cdm = new Model::Computer;
        QString text = cdm->generateTableString(tr("Computer"));

        doc.setHtml(style + text);
    } break;

    case VIEW_PRINTER: {
        qDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Drucker !");

        QString style = Model::Printer::setOutTableStyle();
        auto *pdm = new Model::Printer;
        QString text = pdm->generateTableString(tr("Drucker"));

        doc.setHtml(style + text);
    } break;

    case VIEW_PHONE: {
        qDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Telefone !");

        QString style = Model::Phone::setOutTableStyle();
        auto *pdm = new Model::Phone;
        QString text = pdm->generateTableString(tr("Telefon"));

        doc.setHtml(style + text);
    } break;

    default:
        QString message = tr("Drucken unbekanntes Submodul");
        notAvailableMessage(message);
        qCCritical(jmbdeWidgetsMainWindowLog) << "on_action_Export_Pdf_triggered(): Unbekanntes Sub-Modul";
    }

#if !defined(QT_NO_PRINTER) && !defined(QT_NO_PRINTDIALOG)
    QPrinter printer(QPrinter::HighResolution);

    printer.setOrientation(QPrinter::Landscape);
    QPrintPreviewDialog preview(&printer);

    doc.print(&printer);

    connect(&preview, SIGNAL(paintRequested(QPrinter *)), SLOT(printPreview(QPrinter *)));
    preview.exec();
#endif
}

void MainWindow::notAvailableMessage(const QString &functionName)
{
    QString message = tr("In der Version %s ist die Funktion <%s>\n"
                         "noch nicht implementiert\n"
                         "Wenn eine neuere Version zur Verfügung steht, dann probieren Sie es bitte damit\n"
                         "Sie können das auf der Project Webseite:\n %s überprüfen.")
                          .arg(qApp->applicationVersion(), functionName, qApp->organizationDomain());

    QMessageBox::critical(this, qApp->applicationDisplayName(), message, QMessageBox::Cancel);
}

void MainWindow::on_actionHelp_triggered()
{
    QString message = tr("Hilfe");
    notAvailableMessage(message);
}

void MainWindow::onClickedTreeView(const QModelIndex &index)
{
    const QStandardItem *item = m_treeviewModel->itemFromIndex(index);
    const QString selected = item->text();

    m_actualView = index;
    qCDebug(jmbdeWidgetsMainWindowLog) << "ActualViewRow : " << index << " Item : " << selected;

    // Headers -> no action
    if ((selected == tr("Person")) || (selected == tr("Gerät")) || (selected == tr("Kommunikation")) || (selected == tr("Verschiedenes"))) {
        return;
    }

    // Tree -> Person
    if (selected == tr("Mitarbeiter")) {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);
        actualView = VIEW_EMPLOYEE;

        auto *edm = new Model::Employee;

        tableModel = edm->initializeRelationalModel();
        int idx = edm->LastNameIndex();

        ui->listView->setModel(tableModel);
        ui->listView->setModelColumn(idx);
        QModelIndex qmi = QModelIndex();

        auto *employeeInput = new EmployeeInputArea(ui->scrollArea, qmi);
        QSize AdjustSize = employeeInput->size();
        AdjustSize.width();
        employeeInput->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(employeeInput);
    } else if (selected == tr("Funktion")) {
        qDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_FUNCTION;

        auto *fdm = new Model::Function;

        tableModel = fdm->initializeRelationalModel();

        ui->listView->setModel(tableModel);
        int idx = fdm->NameIndex();
        ui->listView->setModelColumn(idx);
        QModelIndex qmi = QModelIndex();
        auto *fia = new FunctionInputArea(ui->scrollArea, qmi);
        ui->scrollArea->setWidget(fia);
    } else if (selected == tr("Abteilung")) {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_DEPARTMENT;

        auto *dpm = new Model::Department;

        tableModel = dpm->initializeRelationalModel();
        int idx = dpm->NameIndex();

        ui->listView->setModel(tableModel);
        ui->listView->setModelColumn(idx);
        QModelIndex qmi = QModelIndex();
        auto *dia = new DepartmentInputArea(ui->scrollArea, qmi);
        ui->scrollArea->setWidget(dia);
    } else if (selected == tr("Titel")) {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_TITLE;

        auto *tdm = new Model::Title;

        tableModel = tdm->initializeRelationalModel();
        int idx = tdm->NameIndex();

        ui->listView->setModel(tableModel);
        ui->listView->setModelColumn(idx);

        QModelIndex qmi = QModelIndex();
        auto *tia = new TitleInputArea(ui->scrollArea, qmi);
        ui->scrollArea->setWidget(tia);
        // Tree -> Device
    } else if (selected == tr("Computer")) {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_COMPUTER;

        auto *cdm = new Model::Computer;

        tableModel = cdm->initializeRelationalModel();
        int idx = cdm->NameIndex();

        ui->listView->setModel(tableModel);
        ui->listView->setModelColumn(idx);

        QModelIndex qmi = QModelIndex();
        auto *cia = new ComputerInputArea(ui->scrollArea, qmi);
        ui->scrollArea->setWidget(cia);
    } else if (selected == tr("Prozessor")) {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_PROCESSOR;

        auto *pdm = new Model::Processor;

        tableModel = pdm->initializeRelationalModel();
        int idx = pdm->NameIndex();

        ui->listView->setModel(tableModel);
        ui->listView->setModelColumn(idx);

        QModelIndex qmi = QModelIndex();
        auto *pia = new ProcessorInputArea(ui->scrollArea, qmi);
        ui->scrollArea->setWidget(pia);
    } else if (selected == tr("Betriebssystem")) {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_OS;

        auto *odm = new Model::OS;

        tableModel = odm->initializeRelationalModel();
        int idx = odm->NameIndex();

        ui->listView->setModel(tableModel);
        ui->listView->setModelColumn(idx);

        QModelIndex qmi = QModelIndex();
        auto *oia = new OSInputArea(ui->scrollArea, qmi);
        ui->scrollArea->setWidget(oia);
    } else if (selected == tr("Software")) {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_SOFTWARE;

        auto *sdm = new Model::Software;

        tableModel = sdm->initializeRelationalModel();
        int idx = sdm->NameIndex();

        ui->listView->setModel(tableModel);
        ui->listView->setModelColumn(idx);

        QModelIndex qmi = QModelIndex();
        auto *sia = new SoftwareInputArea(ui->scrollArea, qmi);
        ui->scrollArea->setWidget(sia);
    } else if (selected == tr("Drucker")) {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_PRINTER;

        auto *pdm = new Model::Printer;

        tableModel = pdm->initializeRelationalModel();
        int idx = pdm->NetworkNameIndex();

        ui->listView->setModel(tableModel);
        ui->listView->setModelColumn(idx);

        QModelIndex qmi = QModelIndex();
        auto *pia = new PrinterInputArea(ui->scrollArea, qmi);
        ui->scrollArea->setWidget(pia);
        // Tree -> Communication
    } else if (selected == tr("Telefon")) {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_PHONE;

        auto *phdm = new Model::Phone;

        tableModel = phdm->initializeRelationalModel();
        int idx = phdm->NumberIndex();

        ui->listView->setModel(tableModel);
        ui->listView->setModelColumn(idx);

        QModelIndex qmi = QModelIndex();
        auto *pia = new PhoneInputArea(ui->scrollArea, qmi);
        ui->scrollArea->setWidget(pia);
    } else if (selected == tr("Mobiltelefon")) {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_MOBILE;

        auto *phdm = new Model::Mobile;

        tableModel = phdm->initializeRelationalModel();
        int idx = phdm->NumberIndex();

        ui->listView->setModel(tableModel);
        ui->listView->setModelColumn(idx);

        QModelIndex qmi = QModelIndex();
        auto *mia = new MobileInputArea(ui->scrollArea, qmi);
        ui->scrollArea->setWidget(mia);
        // Tree -> Misc
    } else if (selected == tr("Hersteller")) {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_MANUFACTURER;

        auto *mdm = new Model::Manufacturer;

        tableModel = mdm->initializeRelationalModel();
        int idx = mdm->NameIndex();

        ui->listView->setModel(tableModel);
        ui->listView->setModelColumn(idx);

        QModelIndex qmi = QModelIndex();
        auto *mia = new ManufacturerInputArea(ui->scrollArea, qmi);
        ui->scrollArea->setWidget(mia);
    } else if (selected == tr("Stadt")) {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_CITY;

        auto *cnm = new Model::CityName;

        tableModel = cnm->initializeRelationalModel();
        int idx = cnm->NameIndex();

        ui->listView->setModel(tableModel);
        ui->listView->setModelColumn(idx);

        QModelIndex qmi = QModelIndex();
        auto *cia = new CityInputArea(ui->scrollArea, qmi);
        ui->scrollArea->setWidget(cia);
    } else if (selected == tr("Schlüsselchip")) {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_CHIPCARD;

        auto *ccdm = new Model::ChipCard;

        tableModel = ccdm->initializeRelationalModel();
        int idx = ccdm->NumberIndex();

        ui->listView->setModel(tableModel);
        ui->listView->setModelColumn(idx);

        QModelIndex qmi = QModelIndex();
        auto *cia = new ChipCardInputArea(ui->scrollArea, qmi);
        ui->scrollArea->setWidget(cia);
    } else {
        const QString caller = tr("onClickedTreeView(): Unbekannte Funktion");
        notAvailableMessage(caller);
    }
}

void MainWindow::onClickedListViewRow(const QModelIndex &index)
{
    m_actualData = index;
    qCDebug(jmbdeWidgetsMainWindowLog) << "onClickedListViewRow(QModelIndex : " << index;

    switch (actualView) {
    case VIEW_EMPLOYEE: {
        auto *eia = new EmployeeInputArea(nullptr, index);

        QSize AdjustSize = eia->size();
        AdjustSize.width();
        eia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(eia);
    } break;

    case VIEW_FUNCTION: {
        auto *fia = new FunctionInputArea(nullptr, index);

        QSize AdjustSize = fia->size();
        AdjustSize.width();
        fia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(fia);
    } break;

    case VIEW_DEPARTMENT: {
        auto *dia = new DepartmentInputArea(nullptr, index);

        QSize AdjustSize = dia->size();
        AdjustSize.width();
        dia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(dia);
    } break;

    case VIEW_TITLE: {
        auto *fia = new FunctionInputArea(nullptr, index);

        QSize AdjustSize = fia->size();
        AdjustSize.width();
        fia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(fia);
    } break;

    case VIEW_COMPUTER: {
        auto *cia = new ComputerInputArea(nullptr, index);

        QSize AdjustSize = cia->size();
        AdjustSize.width();
        cia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(cia);
    } break;

    case VIEW_PROCESSOR: {
        auto *pia = new ProcessorInputArea(nullptr, index);

        QSize AdjustSize = pia->size();
        AdjustSize.width();
        pia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(pia);
    } break;

    case VIEW_OS: {
        auto *oia = new OSInputArea(nullptr, index);

        QSize AdjustSize = oia->size();
        AdjustSize.width();
        oia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(oia);
    } break;

    case VIEW_SOFTWARE: {
        auto *sia = new SoftwareInputArea(nullptr, index);

        QSize AdjustSize = sia->size();
        AdjustSize.width();
        sia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(sia);
    } break;

    case VIEW_PRINTER: {
        auto *pia = new PrinterInputArea(nullptr, index);

        QSize AdjustSize = pia->size();
        AdjustSize.width();
        pia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(pia);
    } break;

    case VIEW_PHONE: {
        auto *pia = new PhoneInputArea(nullptr, index);

        QSize AdjustSize = pia->size();
        AdjustSize.width();
        pia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(pia);
    } break;

    case VIEW_MOBILE: {
        auto *mia = new MobileInputArea(nullptr, index);

        QSize AdjustSize = mia->size();
        AdjustSize.width();
        mia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(mia);
    } break;

    case VIEW_MANUFACTURER: {
        auto *mia = new ManufacturerInputArea(nullptr, index);

        QSize AdjustSize = mia->size();
        AdjustSize.width();
        mia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(mia);
    } break;

    case VIEW_CITY: {
        auto *cia = new CityInputArea(nullptr, index);

        QSize AdjustSize = cia->size();
        AdjustSize.width();
        cia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(cia);
    }

    break;

    case VIEW_CHIPCARD: {
        auto *ccia = new ChipCardInputArea(nullptr, index);

        QSize AdjustSize = ccia->size();
        AdjustSize.width();
        ccia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(ccia);
    } break;
    default:
        const QString caller = tr("onClickedListViewRow(): Unbekannte Funktion");
        notAvailableMessage(caller);
        break;
    }
}

void MainWindow::onPressedListViewRow(const QModelIndex &index)
{
    m_actualData = index;
    qCDebug(jmbdeWidgetsMainWindowLog) << "Pressed: ActualDataRow for deleteting: " << index;

    switch (actualView) {
    case VIEW_EMPLOYEE: {
        qCDebug(jmbdeWidgetsMainWindowLog) << "Employee Table Row (" << index.row() << ") clicked";

        auto *eia = new EmployeeInputArea(nullptr, index);

        QSize AdjustSize = eia->size();
        AdjustSize.width();
        eia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(eia);
        qDebug() << "Delete index : " << index;
    } break;
    }
}
