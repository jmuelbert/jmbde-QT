/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "views/mainwindow.h"

#include "ui_mainwindow.h"

Q_LOGGING_CATEGORY(jmbdeWidgetsMainWindowLog, "jmuelbert.jmbde.widgets.mainwindow", QtWarningMsg)

MainWindow::MainWindow(QWidget* parent)
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
    this->dataContext = new Model::DataContext(dynamic_cast<QObject*>(this), this->dataBaseName);

    qCDebug(jmbdeWidgetsMainWindowLog) << tr("ActualViewRow : ") << m_actualView;

    if (m_actualView.row() > 0) {
        ui->treeView->setCurrentIndex(m_actualView);
        on_treeView_clicked(m_actualView);
    } else {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Setze aktuelle Ansicht: Mitarbeiter - Tabelle");
        actualView = VIEW_EMPLOYEE;

        actualizeEmployeeListView();

        auto* employeeInputArea = new EmployeeInputArea(ui->scrollArea);
        QObject::connect(employeeInputArea, SIGNAL(dataChanged()), this, SLOT(actualizeEmployeListView()));
        QSize AdjustSize = employeeInputArea->size();
        AdjustSize.width();
        employeeInputArea->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(employeeInputArea);
    }
}

MainWindow::~MainWindow()
{
    dataContext->~DataContext();
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event)

    const int OFFSET = 20;

    int width = ui->centralWidget->width() - OFFSET;
    int height = ui->centralWidget->height() - OFFSET;

    ui->splitter->resize(width, height);
}

void MainWindow::focusChanged(QWidget* from, QWidget* now)
{
    Q_UNUSED(from)
    Q_UNUSED(now)

    qCDebug(jmbdeWidgetsMainWindowLog) << tr("Der Fokus hat sich geändert");
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    Q_UNUSED(event)
    qCDebug(jmbdeWidgetsMainWindowLog) << tr("Der Close Event");
}

void MainWindow::on_actionPreferences_triggered()
{
    PreferencesDialog* settingsDialog;

    settingsDialog = new PreferencesDialog();
    settingsDialog->show();
}

void MainWindow::on_actionAbout_triggered()
{
    auto* view = new AboutDialog;
    view->show();
}

void MainWindow::initOutline()
{
    QHash<QString, QList<QString>> outlineData;

    QList<QString> subEntries = { tr("Mitarbeiter"), tr("Funktion"), tr("Abteilung"), tr("Titel"), tr("Zugang") };
    outlineData.insert(tr("Person"), subEntries);

    subEntries = { tr("Computer"), tr("Prozessor"), tr("Betriebssystem"), tr("Software"), tr("Drucker") };
    outlineData.insert(tr("Gerät"), subEntries);

    subEntries = { tr("Telefon"), tr("Mobiltelefon") };
    outlineData.insert(tr("Kommunikation"), subEntries);

    subEntries = { tr("Hersteller"), tr("Stadt"), tr("Schlüsselchip"), tr("Schlüsselchip Tür") };
    outlineData.insert(tr("Verschiedenes"), subEntries);

    m_treeviewModel = new QStandardItemModel(this);
    QStandardItem* parentItem = m_treeviewModel->invisibleRootItem();

    QStandardItem* item;

    QList<QString> od;
    QHashIterator<QString, QList<QString>> i(outlineData);
    while (i.hasNext()) {
        i.next();
        auto* header = new QStandardItem(i.key());
        parentItem->appendRow(header);
        qCDebug(jmbdeWidgetsMainWindowLog) << "initOutline(): (" << i.key() << ": " << i.value() << " )";

        od = i.value();
        for (int index = 0; index < od.size(); ++index) {
            item = new QStandardItem(od.value(index));
            header->appendRow(item);
            qCDebug(jmbdeWidgetsMainWindowLog) << "initOutline(): (Gefunden :" << od.value(index) << " an der Position)" << index;
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

    QString dataContextDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

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
    auto* csvImport = new CsvImportDialog();

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
        auto* edm = new Model::Employee();
        QString text = edm->generateTableString(tr("Mitarbeiter"));

        doc.setHtml(style + text);
    } break;

    case VIEW_COMPUTER: {
        qDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Computer !");
        QString style = Model::Computer::setOutTableStyle();
        auto* cdm = new Model::Computer;
        QString text = cdm->generateTableString(tr("Computer"));

        doc.setHtml(style + text);
    } break;

    case VIEW_PRINTER: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Drucker !");
        QString style = Model::Printer::setOutTableStyle();
        auto* pdm = new Model::Printer;
        QString text = pdm->generateTableString(tr("Drucker"));

        doc.setHtml(style + text);
    } break;

    case VIEW_PHONE: {
        qCDebug(jmbdeWidgetsMainWindowLog) << "Drucke Telefone !";
        QString style = Model::Phone::setOutTableStyle();
        auto* pdm = new Model::Phone;
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

    printer.setPageOrientation(QPageLayout::Landscape);
    auto* dlg = new QPrintDialog(&printer, this);

    dlg->setWindowTitle(tr("Drucke Dokument"));
    if (dlg->exec() == QDialog::Accepted) {
        doc.print(&printer);
    }
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
        auto* edm = new Model::Employee();
        QString text = edm->generateTableString(tr("Mitarbeiter"));

        doc.setHtml(style + text);
    } break;

    case VIEW_COMPUTER: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Computer !");

        QString style = Model::Computer::setOutTableStyle();
        auto* cdm = new Model::Computer;
        QString text = cdm->generateTableString(tr("Computer"));

        doc.setHtml(style + text);
    } break;

    case VIEW_PRINTER: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Drucker !");

        QString style = Model::Printer::setOutTableStyle();
        auto* pdm = new Model::Printer;
        QString text = pdm->generateTableString(tr("Drucker"));

        doc.setHtml(style + text);
    } break;

    case VIEW_PHONE: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Telefone !");

        QString style = Model::Phone::setOutTableStyle();
        auto* pdm = new Model::Phone;
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
        if (QFileInfo(fileName).suffix().isEmpty()) {
            fileName.append(QLatin1String(".pdf"));
        }
        QPrinter printer(QPrinter::HighResolution);

        printer.setPageOrientation(QPageLayout::Landscape);
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
        auto* edm = new Model::Employee();
        QString text = edm->generateTableString(tr("Mitarbeiter"));

        doc.setHtml(style + text);
    } break;

    case VIEW_COMPUTER: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Computer !");

        QString style = Model::Computer::setOutTableStyle();
        auto* cdm = new Model::Computer;
        QString text = cdm->generateTableString(tr("Computer"));

        doc.setHtml(style + text);
    } break;

    case VIEW_PRINTER: {
        qDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Drucker !");

        QString style = Model::Printer::setOutTableStyle();
        auto* pdm = new Model::Printer;
        QString text = pdm->generateTableString(tr("Drucker"));

        doc.setHtml(style + text);
    } break;

    case VIEW_PHONE: {
        qDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Telefone !");

        QString style = Model::Phone::setOutTableStyle();
        auto* pdm = new Model::Phone;
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

    printer.setPageOrientation(QPageLayout::Landscape);
    QPrintPreviewDialog preview(&printer);

    doc.print(&printer);

    connect(&preview, SIGNAL(paintRequested(QPrinter*)), SLOT(printPreview(QPrinter*)));
    preview.exec();
#endif
}

void MainWindow::notAvailableMessage(const QString& functionName)
{
    QString message = tr("In der Version %s ist die Funktion <%s>\n"
                         "noch nicht implementiert\n"
                         "Wenn eine neuere Version zur Verfügung steht, dann probieren Sie es "
                         "bitte damit\n"
                         "Sie können das auf der Project Webseite:\n %s überprüfen.")
                          .arg(qApp->applicationVersion(), functionName, qApp->organizationDomain());

    QMessageBox::critical(this, qApp->applicationDisplayName(), message, QMessageBox::Cancel);
}

void MainWindow::on_actionHelp_triggered()
{
    QString message = tr("Hilfe");
    notAvailableMessage(message);
}

void MainWindow::on_treeView_clicked(const QModelIndex& index)
{
    const QStandardItem* item = m_treeviewModel->itemFromIndex(index);
    const QString selected = item->text();

    m_actualView = index;
    qCDebug(jmbdeWidgetsMainWindowLog) << "ActualViewRow : " << index << " Item : " << selected;
    // Headers -> no action
    if ((selected == tr("Person")) || (selected == tr("Gerät")) || (selected == tr("Kommunikation")) || (selected == tr("Verschiedenes"))) {
        return;
    }

    if (selected == tr("Zugang")) { // Account
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_ACCOUNT;

        actualizeAccoutListView();

        auto* accountInput = new AccountInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = accountInput->size();
        adjustSize.width();
        accountInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(accountInput);
    } else if (selected == tr("Schlüsselchip Tür")) { // ChipCardDoor
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_CHIPCARDDOOR;

        actualizeChipCardDoorListView();

        auto* chipCardDoorInput = new ChipCardDoorInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = chipCardDoorInput->size();
        adjustSize.width();
        chipCardDoorInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(chipCardDoorInput);
    } else if (selected == tr("Schlüsselchip")) { // ChipCard
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_CHIPCARD;

        actualizeChipCardListView();

        auto* chipCardInput = new ChipCardInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = chipCardInput->size();
        adjustSize.width();
        chipCardInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(chipCardInput);
    } else if (selected == tr("Schlüsselchip Profil Tür")) { // ChipCardProfileDoor
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_CHIPCARDPROFILEDOOR;

        actualizeChipCardProfileDoorListView();

        auto* chipCardProfileDoorInput = new ChipCardProfileDoorInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = chipCardProfileDoorInput->size();
        adjustSize.width();
        chipCardProfileDoorInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(chipCardProfileDoorInput);
    } else if (selected == tr("Schlüsselchip Profile")) { // ChipCardProfile
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_CHIPCARDPROFILE;

        actualizeChipCardProfileListView();

        auto* chipCardProfileInput = new ChipCardProfileInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = chipCardProfileInput->size();
        adjustSize.width();
        chipCardProfileInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(chipCardProfileInput);
    } else if (selected == tr("Stadt")) { // City
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_CITYNAME;

        actualizeCityListView();

        auto* cityInput = new CityInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = cityInput->size();
        adjustSize.width();
        cityInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(cityInput);
    } else if (selected == tr("Firma")) { // Company
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_COMPANY;

        actualizeCompanyListView();

        auto* companyInput = new CompanyInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = companyInput->size();
        adjustSize.width();
        companyInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(companyInput);
    } else if (selected == tr("Computer")) {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_COMPUTER;

        actualizeComputerListView();

        auto* computerInput = new ComputerInputArea(ui->scrollArea, QModelIndex());
        QSize AdjustSize = computerInput->size();
        AdjustSize.width();
        computerInput->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(computerInput);
    } else if (selected == tr("Computer Software")) {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_COMPUTERSOFTWARE;

        actualizeComputerSoftwareListView();

        auto* computerSoftwareInput = new ComputerInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = computerSoftwareInput->size();
        adjustSize.width();
        computerSoftwareInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(computerSoftwareInput);
    } else if (selected == tr("Abteilung")) { // Department
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_DEPARTMENT;

        actualizeDepartmentListView();

        auto* departmentInput = new DepartmentInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = departmentInput->size();
        adjustSize.width();
        departmentInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(departmentInput);
    } else if (selected == tr("Gerätename")) { // Device Name
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_DEVICENAME;

        actualizeDeviceNameListView();

        auto* deviceNameInput = new DeviceNameInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = deviceNameInput->size();
        adjustSize.width();
        deviceNameInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(deviceNameInput);
    } else if (selected == tr("Gerätetyp")) { // Device Type
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_DEVICETYPE;

        actualizeDeviceTypeListView();

        auto* deviceTypeInput = new DeviceTypeInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = deviceTypeInput->size();
        adjustSize.width();
        deviceTypeInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(deviceTypeInput);
    } else if (selected == tr("Dokument")) { // Document
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_DOCUMENT;

        actualizeDocumentListView();

        auto* documentInput = new DocumentInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = documentInput->size();
        adjustSize.width();
        documentInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(documentInput);
    } else if (selected == tr("Mitarbeiter Zugang")) { // Employee Account
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_EMPLOYEEACCOUNT;

        actualizeEmployeeAccountListView();

        auto* employeeAccountInput = new EmployeeAccountInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = employeeAccountInput->size();
        adjustSize.width();
        employeeAccountInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(employeeAccountInput);

    } else if (selected == tr("Mitarbeiter Dokument")) { // Employee Document
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_EMPLOYEEDOCUMENT;

        actualizeEmployeeDocumentListView();

        auto* employeeDocumentInput = new EmployeeDocumentInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = employeeDocumentInput->size();
        adjustSize.width();
        employeeDocumentInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(employeeDocumentInput);

    } else if (selected == tr("Mitarbeiter")) { // Employee
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);
        actualView = VIEW_EMPLOYEE;

        actualizeEmployeeListView();

        auto* employeeInput = new EmployeeInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = employeeInput->size();
        adjustSize.width();
        employeeInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(employeeInput);
    } else if (selected == tr("Fax")) { // Fax
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_FAX;

        actualizeFaxListView();

        auto* faxInput = new FaxInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = faxInput->size();
        adjustSize.width();
        faxInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(faxInput);
    } else if (selected == tr("Funktion")) {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_FUNCTION;

        actualizeFunctionListView();

        auto* functionInput = new FunctionInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = functionInput->size();
        adjustSize.width();
        functionInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(functionInput);
    } else if (selected == tr("Inventar")) {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_INVENTORY;

        actualizeInventoryListView();

        auto* inventoryInput = new InventoryInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = inventoryInput->size();
        adjustSize.width();
        inventoryInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(inventoryInput);
    } else if (selected == tr("Funktion")) { // Function
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_FUNCTION;

        actualizeFunctionListView();

        auto* functionInput = new FunctionInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = functionInput->size();
        adjustSize.width();
        functionInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(functionInput);
    } else if (selected == tr("Hersteller")) { // Manufacturer
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_MANUFACTURER;

        actualizeManufacturerListView();

        auto* manufacturerInput = new ManufacturerInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = manufacturerInput->size();
        adjustSize.width();
        manufacturerInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(manufacturerInput);
    } else if (selected == tr("Mobiltelefon")) { // Mobile
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_MOBILE;

        actualizeMobileListView();

        auto* mobileInput = new MobileInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = mobileInput->size();
        adjustSize.width();
        mobileInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(mobileInput);
    } else if (selected == tr("Betriebssystem")) { // OS
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_OS;

        actualizeOsListView();

        auto* osInput = new OSInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = osInput->size();
        adjustSize.width();
        osInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(osInput);
    } else if (selected == tr("Telefon")) { // Phone
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_PHONE;

        actualizePhoneListView();

        auto* phoneInput = new PhoneInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = phoneInput->size();
        adjustSize.width();
        phoneInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(phoneInput);
    } else if (selected == tr("Platz")) { // Place
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_PLACE;

        actualizePlaceListView();

        auto* placeInput = new PlaceInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = placeInput->size();
        adjustSize.width();
        placeInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(placeInput);
    } else if (selected == tr("Drucker")) { // Printer
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_PRINTER;

        actualizePrinterListView();

        auto* printerInput = new PrinterInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = printerInput->size();
        adjustSize.width();
        printerInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(printerInput);
    } else if (selected == tr("Prozessor")) { // Processor
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_PROCESSOR;

        actualizeProcessorListView();

        auto* processorInput = new ProcessorInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = processorInput->size();
        adjustSize.width();
        processorInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(processorInput);
    } else if (selected == tr("Software")) { // Software
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_SOFTWARE;

        actualizeSoftwareListView();

        auto* softwareInput = new SoftwareInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = softwareInput->size();
        adjustSize.width();
        softwareInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(softwareInput);
    } else if (selected == tr("System Daten")) { // System Data
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_SYSTEM;

        actualizeSystemDataListView();

        auto* systemDataInput = new SystemDataInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = systemDataInput->size();
        adjustSize.width();
        systemDataInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(systemDataInput);
    } else if (selected == tr("Titel")) {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_TITLE;

        actualizeTitleListView();

        auto* titleInput = new TitleInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = titleInput->size();
        adjustSize.width();
        titleInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(titleInput);
    } else if (selected == tr("PLZ Stadt")) { // Zip City
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_ZIPCITY;

        actualizeZipCityListView();

        auto* zipCityInput = new ZipCityInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = zipCityInput->size();
        adjustSize.width();
        zipCityInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(zipCityInput);
    } else if (selected == tr("PLZ Code")) { // Zip Code
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: %s").arg(selected);

        actualView = VIEW_ZIPCODE;

        actualizeZipCodeListView();

        auto* zipCodeInput = new ZipCodeInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = zipCodeInput->size();
        adjustSize.width();
        zipCodeInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(zipCodeInput);
    } else {
        const QString caller = tr("onClickedTreeView(): Unbekannte Funktion");
        notAvailableMessage(caller);
    }
}

void MainWindow::on_listView_clicked(const QModelIndex& index)
{
    m_actualData = index;
    qCDebug(jmbdeWidgetsMainWindowLog) << "onClickedlistViewRow(QModelIndex : " << index;
    switch (actualView) {
    case VIEW_ACCOUNT: {
        auto* accountInput = new AccountInputArea(ui->scrollArea, index);

        QObject::connect(accountInput, SIGNAL(dataChanged()), this, SLOT(actualizeAccountListView()));

        QSize AdjustSize = accountInput->size();
        AdjustSize.width();
        accountInput->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(accountInput);
    } break;
    case VIEW_CHIPCARD: {
        auto* chipCardInput = new ChipCardInputArea(ui->scrollArea, index);

        QObject::connect(chipCardInput, SIGNAL(dataChanged()), this, SLOT(actualizeChipCardListView()));

        QSize AdjustSize = chipCardInput->size();
        AdjustSize.width();
        chipCardInput->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(chipCardInput);
    } break;
    case VIEW_CHIPCARDDOOR: {
        auto* chipCardDoorInput = new ChipCardDoorInputArea(ui->scrollArea, index);

        QObject::connect(chipCardDoorInput, SIGNAL(dataChanged()), this, SLOT(actualizeChipCardDoorListView()));

        QSize AdjustSize = chipCardDoorInput->size();
        AdjustSize.width();
        chipCardDoorInput->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(chipCardDoorInput);
    } break;
    case VIEW_CITYNAME: {
        auto* cia = new CityInputArea(nullptr, index);

        QSize AdjustSize = cia->size();
        AdjustSize.width();
        cia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(cia);
    } break;

    case VIEW_COMPUTER: {
        auto* cia = new ComputerInputArea(ui->scrollArea, index);

        QSize AdjustSize = cia->size();
        AdjustSize.width();
        cia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(cia);
    } break;

    case VIEW_DEPARTMENT: {
        auto* dia = new DepartmentInputArea(nullptr, index);

        QSize AdjustSize = dia->size();
        AdjustSize.width();
        dia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(dia);
    } break;

    case VIEW_EMPLOYEE: {
        auto* eia = new EmployeeInputArea(ui->scrollArea, index);

        QObject::connect(eia, SIGNAL(dataChanged()), this, SLOT(actualizeEmployeListView()));

        QSize AdjustSize = eia->size();
        AdjustSize.width();
        eia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(eia);

    } break;

    case VIEW_FUNCTION: {
        auto* fia = new FunctionInputArea(nullptr, index);

        QSize AdjustSize = fia->size();
        AdjustSize.width();
        fia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(fia);
    } break;

    case VIEW_MANUFACTURER: {
        auto* mia = new ManufacturerInputArea(nullptr, index);

        QSize AdjustSize = mia->size();
        AdjustSize.width();
        mia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(mia);
    } break;

    case VIEW_MOBILE: {
        auto* mia = new MobileInputArea(nullptr, index);

        QSize AdjustSize = mia->size();
        AdjustSize.width();
        mia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(mia);
    } break;

    case VIEW_OS: {
        auto* oia = new OSInputArea(nullptr, index);

        QSize AdjustSize = oia->size();
        AdjustSize.width();
        oia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(oia);
    } break;

    case VIEW_PHONE: {
        auto* pia = new PhoneInputArea(nullptr, index);

        QSize AdjustSize = pia->size();
        AdjustSize.width();
        pia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(pia);
    } break;

    case VIEW_PRINTER: {
        auto* pia = new PrinterInputArea(nullptr, index);

        QSize AdjustSize = pia->size();
        AdjustSize.width();
        pia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(pia);
    } break;

    case VIEW_PROCESSOR: {
        auto* pia = new ProcessorInputArea(nullptr, index);

        QSize AdjustSize = pia->size();
        AdjustSize.width();
        pia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(pia);
    } break;

    case VIEW_SOFTWARE: {
        auto* sia = new SoftwareInputArea(nullptr, index);

        QSize AdjustSize = sia->size();
        AdjustSize.width();
        sia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(sia);
    } break;

    case VIEW_TITLE: {
        auto* fia = new FunctionInputArea(nullptr, index);

        QSize AdjustSize = fia->size();
        AdjustSize.width();
        fia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(fia);
    } break;

    default:
        const QString caller = tr("onClickedlistViewRow(): Unbekannte Funktion");
        notAvailableMessage(caller);
        break;
    }
}

void MainWindow::actualizeAccoutListView()
{
    auto* accountModel = new Model::Account();
    tableModel = accountModel->initializeRelationalModel();

    QSqlTableModel* listModel = accountModel->initializeListModel();
    int modelIndex = accountModel->getUserNameIndex();
    accountModel->sort(modelIndex, Qt::AscendingOrder);
    actualizeListView(listModel, modelIndex);
}

void MainWindow::actualizeChipCardDoorListView()
{
    auto* chipCardDoorModel = new Model::ChipCardDoor();
    tableModel = chipCardDoorModel->initializeRelationalModel();

    QSqlTableModel* listModel = chipCardDoorModel->initializeListModel();
    int modelIndex = chipCardDoorModel->getNumberIndex();
    chipCardDoorModel->sort(modelIndex, Qt::AscendingOrder);
    actualizeListView(listModel, modelIndex);
}

void MainWindow::actualizeChipCardListView()
{
    auto* chipCardModel = new Model::ChipCard();
    tableModel = chipCardModel->initializeRelationalModel();

    QSqlTableModel* listModel = chipCardModel->initializeListModel();
    int modelIndex = chipCardModel->getNumberIndex();
    chipCardModel->sort(modelIndex, Qt::AscendingOrder);
    actualizeListView(listModel, modelIndex);
}

void MainWindow::actualizeChipCardProfileDoorListView()
{
    auto* chipCardProfileDoorModel = new Model ::ChipCardProfileDoor();
    tableModel = chipCardProfileDoorModel->initializeRelationalModel();

    QSqlTableModel* listModel = chipCardProfileDoorModel->initializeListModel();
    int modelIndex = chipCardProfileDoorModel->getChipCardProfileIdIndex();
    chipCardProfileDoorModel->sort(modelIndex, Qt::AscendingOrder);
    actualizeListView(listModel, modelIndex);
}

void MainWindow::actualizeChipCardProfileListView()
{
    auto* chipCardProfileModel = new Model::ChipCardProfile();
    tableModel = chipCardProfileModel->initializeRelationalModel();

    QSqlTableModel* listModel = chipCardProfileModel->initializeListModel();
    int modelIndex = chipCardProfileModel->getChipCardDoorIdIndex();
    chipCardProfileModel->sort(modelIndex, Qt::AscendingOrder);
    actualizeListView(listModel, modelIndex);
}

void MainWindow::actualizeCityListView()
{
    auto* cityNameModel = new Model::CityName();
    tableModel = cityNameModel->initializeRelationalModel();

    QSqlTableModel* listModel = cityNameModel->initializeListModel();
    int modelIndex = cityNameModel->getNameIndex();
    actualizeListView(listModel, modelIndex);
}

void MainWindow::actualizeCompanyListView()
{
    auto* companyModel = new Model::Company();
    tableModel = companyModel->initializeRelationalModel();

    QSqlTableModel* listModel = companyModel->initializeListModel();
    int modelIndex = companyModel->getNameIndex();
    actualizeListView(listModel, modelIndex);
}

void MainWindow::actualizeComputerListView()
{
    auto* computerModel = new Model::Computer();
    tableModel = computerModel->initializeRelationalModel();

    QSqlTableModel* listModel = computerModel->initializeListModel();
    int modelIndex = computerModel->getNetworkNameIndex();
    computerModel->sort(modelIndex, Qt::AscendingOrder);
    actualizeListView(listModel, modelIndex);
}

void MainWindow::actualizeComputerSoftwareListView()
{
    auto* computerSoftwareModel = new Model::ComputerSoftware();
    tableModel = computerSoftwareModel->initializeRelationalModel();

    QSqlTableModel* listModel = computerSoftwareModel->initializeListModel();
    int modelIndex = computerSoftwareModel->getSoftwareIdIndex();
    computerSoftwareModel->sort(modelIndex, Qt::AscendingOrder);
    actualizeListView(listModel, modelIndex);
}

void MainWindow::actualizeDepartmentListView()
{
    auto* departmentModel = new Model::Department();
    tableModel = departmentModel->initializeRelationalModel();

    QSqlTableModel* listModel = departmentModel->initializeListModel();
    int modelIndex = departmentModel->getNameIndex();
    departmentModel->sort(modelIndex, Qt::AscendingOrder);
    actualizeListView(listModel, modelIndex);
}

void MainWindow::actualizeDeviceNameListView()
{
    auto* deviceNameModel = new Model::DeviceName();
    tableModel = deviceNameModel->initializeRelationalModel();

    QSqlTableModel* listModel = deviceNameModel->initializeListModel();
    int modelIndex = deviceNameModel->getNameIndex();
    deviceNameModel->sort(modelIndex, Qt::AscendingOrder);
    actualizeListView(listModel, modelIndex);
}

void MainWindow::actualizeDeviceTypeListView()
{
    auto* deviceTypeModel = new Model::DeviceType();
    tableModel = deviceTypeModel->initializeRelationalModel();

    QSqlTableModel* listModel = deviceTypeModel->initializeListModel();
    int modelIndex = deviceTypeModel->getNameIndex();
    deviceTypeModel->sort(modelIndex, Qt::AscendingOrder);
    actualizeListView(listModel, modelIndex);
}

void MainWindow::actualizeDocumentListView()
{
    auto* documentModel = new Model::Document();
    tableModel = documentModel->initializeRelationalModel();

    QSqlTableModel* listModel = documentModel->initializeListModel();
    int modelIndex = documentModel->getNameIndex();
    documentModel->sort(modelIndex, Qt::AscendingOrder);
    actualizeListView(listModel, modelIndex);
}

void MainWindow::actualizeEmployeeAccountListView()
{
    auto* employeeAccountModel = new Model::EmployeeAccount();
    tableModel = employeeAccountModel->initializeRelationalModel();

    QSqlTableModel* listModel = employeeAccountModel->initializeListModel();
    int modelIndex = employeeAccountModel->getAccountIdIndex();
    employeeAccountModel->sort(modelIndex, Qt::AscendingOrder);
    actualizeListView(listModel, modelIndex);
}

void MainWindow::actualizeEmployeeDocumentListView()
{
    auto* employeeDocumentModel = new Model::EmployeeDocument();
    tableModel = employeeDocumentModel->initializeRelationalModel();

    QSqlTableModel* listModel = employeeDocumentModel->initializeListModel();
    int modelIndex = employeeDocumentModel->getDocumentIdIndex();
    employeeDocumentModel->sort(modelIndex, Qt::AscendingOrder);
    actualizeListView(listModel, modelIndex);
}

void MainWindow::actualizeEmployeeListView()
{
    auto* employeeModel = new Model::Employee();
    tableModel = employeeModel->initializeRelationalModel();

    QSqlTableModel* listModel = employeeModel->initializeListModel();
    int modelIndex = employeeModel->getLastNameIndex();
    employeeModel->sort(modelIndex, Qt::AscendingOrder);
    actualizeListView(listModel, modelIndex);
}

void MainWindow::actualizeFaxListView()
{
    auto* faxModel = new Model::Fax();
    tableModel = faxModel->initializeRelationalModel();

    QSqlTableModel* listModel = faxModel->initializeListModel();
    int modelIndex = faxModel->getNumberIndex();
    faxModel->sort(modelIndex, Qt::AscendingOrder);
    actualizeListView(listModel, modelIndex);
}

void MainWindow::actualizeFunctionListView()
{
    auto* functionModel = new Model::Function();
    tableModel = functionModel->initializeRelationalModel();

    QSqlTableModel* listModel = functionModel->initializeListModel();
    int modelIndex = functionModel->getNameIndex();
    functionModel->sort(modelIndex, Qt::AscendingOrder);
    actualizeListView(listModel, modelIndex);
}

void MainWindow::actualizeInventoryListView()
{
    auto* inventoryModel = new Model::Inventory();
    tableModel = inventoryModel->initializeRelationalModel();

    QSqlTableModel* listModel = inventoryModel->initializeListModel();
    int modelIndex = inventoryModel->getNumberIndex();
    inventoryModel->sort(modelIndex, Qt::AscendingOrder);
    actualizeListView(listModel, modelIndex);
}

void MainWindow::actualizeManufacturerListView()
{
    auto* manufacturerModel = new Model::Manufacturer();
    tableModel = manufacturerModel->initializeRelationalModel();

    QSqlTableModel* listModel = manufacturerModel->initializeListModel();
    int modelIndex = manufacturerModel->getNameIndex();
    manufacturerModel->sort(modelIndex, Qt::AscendingOrder);
    actualizeListView(listModel, modelIndex);
}

void MainWindow::actualizeMobileListView()
{
    auto* mobileModel = new Model::Mobile();
    tableModel = mobileModel->initializeRelationalModel();

    QSqlTableModel* listModel = mobileModel->initializeListModel();
    int modelIndex = mobileModel->getNumberIndex();
    mobileModel->sort(modelIndex, Qt::AscendingOrder);
    actualizeListView(listModel, modelIndex);
}

void MainWindow::actualizeOsListView()
{
    auto* osModel = new Model::OS();
    tableModel = osModel->initializeListModel();

    QSqlTableModel* listModel = osModel->initializeListModel();
    int modelIndex = osModel->getNameIndex();
    osModel->sort(modelIndex, Qt::AscendingOrder);
    actualizeListView(listModel, modelIndex);
}

void MainWindow::actualizePhoneListView()
{
    auto* phoneModel = new Model::Phone();
    tableModel = phoneModel->initializeRelationalModel();

    QSqlTableModel* listModel = phoneModel->initializeListModel();
    int modelIndex = phoneModel->getNumberIndex();
    phoneModel->sort(modelIndex, Qt::AscendingOrder);
    actualizeListView(listModel, modelIndex);
}

void MainWindow::actualizePlaceListView()
{
    auto* placeModel = new Model::Place();
    tableModel = placeModel->initializeRelationalModel();

    QSqlTableModel* listModel = placeModel->initializeListModel();
    int modelIndex = placeModel->getRoomIndex();
    placeModel->sort(modelIndex, Qt::AscendingOrder);
    actualizeListView(listModel, modelIndex);
}

void MainWindow::actualizePrinterListView()
{
    auto* printerModel = new Model::Printer();
    tableModel = printerModel->initializeListModel();

    QSqlTableModel* listModel = printerModel->initializeListModel();
    int modelIndex = printerModel->getNetworkNameIndex();
    printerModel->sort(modelIndex, Qt::AscendingOrder);
    actualizeListView(listModel, modelIndex);
}

void MainWindow::actualizeProcessorListView()
{
    auto* processorModel = new Model::Processor();
    tableModel = processorModel->initializeRelationalModel();

    QSqlTableModel* listModel = processorModel->initializeListModel();
    int modelIndex = processorModel->getNameIndex();
    processorModel->sort(modelIndex, Qt::AscendingOrder);
    actualizeListView(listModel, modelIndex);
}

void MainWindow::actualizeSoftwareListView()
{
    auto* softwareModel = new Model::Software();
    tableModel = softwareModel->initializeRelationalModel();

    QSqlTableModel* listModel = softwareModel->initializeListModel();
    int modelIndex = softwareModel->getNameIndex();
    softwareModel->sort(modelIndex, Qt::AscendingOrder);
    actualizeListView(listModel, modelIndex);
}

void MainWindow::actualizeSystemDataListView()
{
    auto* systemDataModel = new Model::SystemData();
    tableModel = systemDataModel->initializeRelationalModel();

    QSqlTableModel* listModel = systemDataModel->initializeListModel();
    int modelIndex = systemDataModel->getNameIndex();
    systemDataModel->sort(modelIndex, Qt::AscendingOrder);
    actualizeListView(listModel, modelIndex);
}

void MainWindow::actualizeTitleListView()
{
    auto* titleModel = new Model::Title();
    tableModel = titleModel->initializeRelationalModel();

    QSqlTableModel* listModel = titleModel->initializeListModel();
    int modelIndex = titleModel->getNameIndex();
    titleModel->sort(modelIndex, Qt::AscendingOrder);
    actualizeListView(listModel, modelIndex);
}

void MainWindow::actualizeZipCityListView()
{
    auto* zipCityModel = new Model::ZipCity();
    tableModel = zipCityModel->initializeRelationalModel();

    QSqlTableModel* listModel = zipCityModel->initializeListModel();
    int modelIndex = zipCityModel->getCityIdIndex();
    zipCityModel->sort(modelIndex, Qt::AscendingOrder);
    actualizeListView(listModel, modelIndex);
}

void MainWindow::actualizeZipCodeListView()
{
    auto* zipCodeModel = new Model::ZipCity();
    tableModel = zipCodeModel->initializeRelationalModel();

    QSqlTableModel* listModel = zipCodeModel->initializeListModel();
    int modelIndex = zipCodeModel->getCityIdIndex();
    zipCodeModel->sort(modelIndex, Qt::AscendingOrder);
    actualizeListView(listModel, modelIndex);
}

void MainWindow::actualizeListView(QSqlTableModel* listModel, int idx)
{
    ui->listView->setModel(listModel);
    ui->listView->setModelColumn(idx);
    ui->listView->show();
}
