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

        auto* employeeInputArea = new EmployeeInputArea(ui->scrollArea, QModelIndex());
        QObject::connect(employeeInputArea, SIGNAL(dataChanged()), this, SLOT(actualizeEmployeeListView()));
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
    QList<QString> subEntries = { tr("Zugang"),
        tr("Schlüsselchip Tür"),
        tr("Schlüssel Chip"),
        tr("Schlüssel Chip Profile Tür"),
        tr("Schlüssel Chip Profil"),
        tr("Stadt"),
        tr("Firma"),
        tr("Computer"),
        tr("Computer Software"),
        tr("Abteilung"),
        tr("Geräte Name"),
        tr("Geräte Typ"),
        tr("Dokument"),
        tr("Mitarbeiter*innen Zugang"),
        tr("Mitarbeiter*innen Dokument"),
        tr("Mitarbeiter*innen"),
        tr("Fax"),
        tr("Funktion"),
        tr("Inventar"),
        tr("Hersteller"),
        tr("Mobile Telefon"),
        tr("Betriebssystem"),
        tr("Telefon"),
        tr("Platz"),
        tr("Drucker"),
        tr("Prozessor"),
        tr("Software"),
        tr("System Daten"),
        tr("Titel"),
        tr("PLZ Stadt"),
        tr("PLZ Code")

    };
    outlineData.insert(tr("Alles"), subEntries);
    subEntries = { tr("Mitarbeiter"), tr("Funktion"), tr("Abteilung"), tr("Titel"), tr("Zugang") };
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

void MainWindow::preparePrint(QTextDocument& doc)
{
    switch (actualView) {
    case VIEW_ACCOUNT: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Accounts !");

        auto* accountModel = new Model::Account;
        QString style = Model::Account::setOutTableStyle();

        QString text = accountModel->generateTableString(tr("Account"));
        doc.setHtml(style + text);
    } break;
    case VIEW_CHIPCARD: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Chip Karten !");

        auto* chipCardModel = new Model::ChipCard;
        QString style = Model::ChipCard::setOutTableStyle();

        QString text = chipCardModel->generateTableString(tr("ChipCard"));
        doc.setHtml(style + text);
    } break;
    case VIEW_CHIPCARDDOOR: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Chip Karten Türen !");

        auto* chipCardDoorModel = new Model::ChipCardDoor;
        QString style = Model::ChipCardDoor::setOutTableStyle();

        QString text = chipCardDoorModel->generateTableString(tr("ChipCardDoor"));
        doc.setHtml(style + text);
    } break;

    case VIEW_CHIPCARDPROFILE: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Chip Karten Profile !");

        auto* chipCardProfileModel = new Model::ChipCardProfile;
        QString style = Model::ChipCardProfile::setOutTableStyle();

        QString text = chipCardProfileModel->generateTableString(tr("ChipCardProfile"));
        doc.setHtml(style + text);
    } break;
    case VIEW_CHIPCARDPROFILEDOOR: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Chip Profile Tür !");

        auto* chipCardProfileDoorModel = new Model::ChipCardProfileDoor;
        QString style = Model::ChipCardProfileDoor::setOutTableStyle();

        QString text = chipCardProfileDoorModel->generateTableString(tr("ChipCardProfileDoor"));
        doc.setHtml(style + text);
    } break;
    case VIEW_CITYNAME: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Ortsnamen !");

        auto* cityNameModel = new Model::CityName;
        QString style = Model::CityName::setOutTableStyle();

        QString text = cityNameModel->generateTableString(tr("CityName"));
        doc.setHtml(style + text);
    } break;
    case VIEW_COMPANY: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Firmen !");

        auto* companyModel = new Model::Company;
        QString style = Model::Company::setOutTableStyle();

        QString text = companyModel->generateTableString(tr("Company"));
        doc.setHtml(style + text);
    } break;
    case VIEW_COMPUTER: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Computer !");

        auto* computerModel = new Model::Computer;
        QString style = Model::Computer::setOutTableStyle();

        QString text = computerModel->generateTableString(tr("Computer"));
        doc.setHtml(style + text);
    } break;
    case VIEW_COMPUTERSOFTWARE: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Software!");

        auto* computerSoftwareModel = new Model::ComputerSoftware;
        QString style = Model::ComputerSoftware::setOutTableStyle();

        QString text = computerSoftwareModel->generateTableString(tr("ComputerSoftware"));
        doc.setHtml(style + text);
    } break;
    case VIEW_DEPARTMENT: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Abteilung !");

        auto* departmentModel = new Model::Department;
        QString style = Model::Department::setOutTableStyle();

        QString text = departmentModel->generateTableString(tr("department"));
        doc.setHtml(style + text);
    } break;
    case VIEW_DEVICENAME: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Gerätename !");

        auto* deviceNameModel = new Model::DeviceName;
        QString style = Model::DeviceName::setOutTableStyle();

        QString text = deviceNameModel->generateTableString(tr("devicename"));
        doc.setHtml(style + text);
    } break;
    case VIEW_DEVICETYPE: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Geräte Typ !");

        auto* deviceTypeModel = new Model::DeviceType;
        QString style = Model::DeviceType::setOutTableStyle();

        QString text = deviceTypeModel->generateTableString(tr("devicetype"));
        doc.setHtml(style + text);
    } break;
    case VIEW_DOCUMENT: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Dokumente !");

        auto* documentModel = new Model::Document;
        QString style = Model::Document::setOutTableStyle();

        QString text = documentModel->generateTableString(tr("document"));
        doc.setHtml(style + text);
    } break;

    case VIEW_EMPLOYEE: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Mitarbeiter !");

        auto* employeeModel = new Model::Employee;
        QString style = Model::Employee::setOutTableStyle();

        QString text = employeeModel->generateTableString(tr("Mitarbeiter*innnen"));
        doc.setHtml(style + text);
    } break;
    case VIEW_EMPLOYEEACCOUNT: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Mitarbeiter*innen Zugänge!");

        auto* employeeAccountModel = new Model::EmployeeAccount;
        QString style = Model::EmployeeAccount::setOutTableStyle();

        QString text = employeeAccountModel->generateTableString(tr("Mitarbeiter*innen Zugänge"));
        doc.setHtml(style + text);
    } break;
    case VIEW_EMPLOYEEDOCUMENT: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Mitarbeiter*innen Documente!");

        auto* employeeDocumentModel = new Model::EmployeeDocument;
        QString style = Model::EmployeeDocument::setOutTableStyle();

        QString text = employeeDocumentModel->generateTableString(tr("Mitarbeiter*innen Documente"));
        doc.setHtml(style + text);
    } break;
    case VIEW_EMPLOYEE_LIST: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Mitarbeiter*innen Liste!");

        auto* employeeDocumentModel = new Model::EmployeeDocument;
        QString style = Model::EmployeeDocument::setOutTableStyle();

        QString text = employeeDocumentModel->generateTableString(tr("Mitarbeiter*innen Liste"));
        doc.setHtml(style + text);
    } break;
    case VIEW_FAX: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Fax!");

        auto* faxModel = new Model::Fax;
        QString style = Model::Fax::setOutTableStyle();

        QString text = faxModel->generateTableString(tr("Fax"));
        doc.setHtml(style + text);
    } break;
    case VIEW_FUNCTION: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Funktion!");

        auto* functionModel = new Model::Function;
        QString style = Model::Function::setOutTableStyle();

        QString text = functionModel->generateTableString(tr("Funktion"));
        doc.setHtml(style + text);
    } break;
    case VIEW_INVENTORY: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Inventar!");

        auto* inventoryModel = new Model::Inventory;
        QString style = Model::Inventory::setOutTableStyle();

        QString text = inventoryModel->generateTableString(tr("Inventar"));
        doc.setHtml(style + text);
    } break;

    case VIEW_MANUFACTURER: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Hersteller!");

        auto* manufacturerModel = new Model::Manufacturer;
        QString style = Model::Manufacturer::setOutTableStyle();

        QString text = manufacturerModel->generateTableString(tr("Hersteller"));
        doc.setHtml(style + text);
    } break;
    case VIEW_MOBILE: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Mobiltelefon!");

        auto* mobileModel = new Model::Mobile;
        QString style = Model::Mobile::setOutTableStyle();

        QString text = mobileModel->generateTableString(tr("Mobiletelefon"));
        doc.setHtml(style + text);
    } break;

    case VIEW_OS: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Betriebssystem!");

        auto* osModel = new Model::OS;
        QString style = Model::OS::setOutTableStyle();

        QString text = osModel->generateTableString(tr("Betriebssystem"));
        doc.setHtml(style + text);
    } break;

    case VIEW_PHONE: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Telefon!");

        auto* faxModel = new Model::Fax;
        QString style = Model::Fax::setOutTableStyle();

        QString text = faxModel->generateTableString(tr("Telefon"));
        doc.setHtml(style + text);
    } break;

    case VIEW_PLACE: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Platz!");

        auto* placeModel = new Model::Place;
        QString style = Model::Place::setOutTableStyle();

        QString text = placeModel->generateTableString(tr("Platz"));
        doc.setHtml(style + text);
    } break;
    case VIEW_PRINTER: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Drucker!");

        auto* printerModel = new Model::Printer;
        QString style = Model::Printer::setOutTableStyle();

        QString text = printerModel->generateTableString(tr("Drucker"));
        doc.setHtml(style + text);
    } break;

    case VIEW_PROCESSOR: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Prozessor!");

        auto* processorModel = new Model::Processor;
        QString style = Model::Processor::setOutTableStyle();

        QString text = processorModel->generateTableString(tr("Prozessor"));
        doc.setHtml(style + text);
    } break;
    case VIEW_SOFTWARE: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Software!");

        auto* softwareModel = new Model::Software;
        QString style = Model::Software::setOutTableStyle();

        QString text = softwareModel->generateTableString(tr("Software"));
        doc.setHtml(style + text);
    } break;
    case VIEW_SYSTEMDATA: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Systemdaten!");

        auto* systemDataModel = new Model::SystemData;
        QString style = Model::SystemData::setOutTableStyle();

        QString text = systemDataModel->generateTableString(tr("Systemdaten"));
        doc.setHtml(style + text);
    } break;
    case VIEW_TITLE: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Titel!");

        auto* titleModel = new Model::Title;
        QString style = Model::Title::setOutTableStyle();

        QString text = titleModel->generateTableString(tr("Titel"));
        doc.setHtml(style + text);
    } break;
    case VIEW_ZIPCITY: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Zip City!");

        auto* zipCityModel = new Model::ZipCity;
        QString style = Model::ZipCity::setOutTableStyle();

        QString text = zipCityModel->generateTableString(tr("ZipCity"));
        doc.setHtml(style + text);
    } break;
    case VIEW_ZIPCODE: {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Drucke Zip Code!");

        auto* zipCodeModel = new Model::ZipCode;
        QString style = Model::ZipCode::setOutTableStyle();

        QString text = zipCodeModel->generateTableString(tr("ZipCode"));
        doc.setHtml(style + text);
    } break;
    default:
        QString message = tr("Drucken unbekanntes Submodul");
        notAvailableMessage(message);
        qCCritical(jmbdeWidgetsMainWindowLog) << tr("on_action_Export_Pdf_triggered(): Unbekanntes Sub-Modul");
    }
}

void MainWindow::on_action_Export_Pdf_triggered()
{
    QTextDocument doc;

    preparePrint(doc);

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
}

void MainWindow::on_actionPrint_Preview_triggered()
{
    QTextDocument doc;

    preparePrint(doc);

    QPrinter printer(QPrinter::HighResolution);

    printer.setPageOrientation(QPageLayout::Landscape);
    QPrintPreviewDialog preview(&printer);

    doc.print(&printer);

    connect(&preview, SIGNAL(paintRequested(QPrinter*)), SLOT(printPreview(QPrinter*)));
    preview.exec();
}

void MainWindow::on_actionPrint_triggered()
{
    QTextDocument doc;

    preparePrint(doc);

    QPrinter printer(QPrinter::HighResolution);

    printer.setPageOrientation(QPageLayout::Landscape);
    auto* dlg = new QPrintDialog(&printer, this);

    dlg->setWindowTitle(tr("Drucke Dokument"));
    if (dlg->exec() == QDialog::Accepted) {
        doc.print(&printer);
    }
    delete dlg;
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
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: ") << selected;

        actualView = VIEW_ACCOUNT;

        actualizeAccountListView();

        auto* accountInput = new AccountInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = accountInput->size();
        adjustSize.width();
        accountInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(accountInput);

    } else if (selected == tr("Schlüsselchip Tür")) { // ChipCardDoor
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: ") << selected;

        actualView = VIEW_CHIPCARDDOOR;

        actualizeChipCardDoorListView();

        auto* chipCardDoorInput = new ChipCardDoorInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = chipCardDoorInput->size();
        adjustSize.width();
        chipCardDoorInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(chipCardDoorInput);

    } else if (selected == tr("Schlüssel Chip")) { // ChipCard
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: ") << selected;

        actualView = VIEW_CHIPCARD;

        actualizeChipCardListView();

        auto* chipCardInput = new ChipCardInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = chipCardInput->size();
        adjustSize.width();
        chipCardInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(chipCardInput);

    } else if (selected == tr("Schlüssel Chip Profile Tür")) { // ChipCardProfileDoor
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: ") << selected;

        actualView = VIEW_CHIPCARDPROFILEDOOR;

        actualizeChipCardProfileDoorListView();

        auto* chipCardProfileDoorInput = new ChipCardProfileDoorInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = chipCardProfileDoorInput->size();
        adjustSize.width();
        chipCardProfileDoorInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(chipCardProfileDoorInput);

    } else if (selected == tr("Schlüssel Chip Profil")) { // ChipCardProfile
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: ") << selected;

        actualView = VIEW_CHIPCARDPROFILE;

        actualizeChipCardProfileListView();

        auto* chipCardProfileInput = new ChipCardProfileInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = chipCardProfileInput->size();
        adjustSize.width();
        chipCardProfileInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(chipCardProfileInput);

    } else if (selected == tr("Stadt")) { // City
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: ") << selected;

        actualView = VIEW_CITYNAME;

        actualizeCityListView();

        auto* cityInput = new CityInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = cityInput->size();
        adjustSize.width();
        cityInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(cityInput);

    } else if (selected == tr("Firma")) { // Company
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: ") << selected;

        actualView = VIEW_COMPANY;

        actualizeCompanyListView();

        auto* companyInput = new CompanyInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = companyInput->size();
        adjustSize.width();
        companyInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(companyInput);
    } else if (selected == tr("Computer")) {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: ") << selected;

        actualView = VIEW_COMPUTER;

        actualizeComputerListView();

        auto* computerInput = new ComputerInputArea(ui->scrollArea, QModelIndex());
        QSize AdjustSize = computerInput->size();
        AdjustSize.width();
        computerInput->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(computerInput);
    } else if (selected == tr("Computer Software")) {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: ") << selected;

        actualView = VIEW_COMPUTERSOFTWARE;

        actualizeComputerSoftwareListView();

        auto* computerSoftwareInput = new ComputerSoftwareInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = computerSoftwareInput->size();
        adjustSize.width();
        computerSoftwareInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(computerSoftwareInput);
    } else if (selected == tr("Abteilung")) { // Department
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: ") << selected;

        actualView = VIEW_DEPARTMENT;

        actualizeDepartmentListView();

        auto* departmentInput = new DepartmentInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = departmentInput->size();
        adjustSize.width();
        departmentInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(departmentInput);
    } else if (selected == tr("Geräte Name")) { // Device Name
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: ") << selected;

        actualView = VIEW_DEVICENAME;

        actualizeDeviceNameListView();

        auto* deviceNameInput = new DeviceNameInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = deviceNameInput->size();
        adjustSize.width();
        deviceNameInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(deviceNameInput);
    } else if (selected == tr("Geräte Typ")) { // Device Type
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: ") << selected;

        actualView = VIEW_DEVICETYPE;

        actualizeDeviceTypeListView();

        auto* deviceTypeInput = new DeviceTypeInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = deviceTypeInput->size();
        adjustSize.width();
        deviceTypeInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(deviceTypeInput);

    } else if (selected == tr("Dokument")) { // Document
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: ") << selected;

        actualView = VIEW_DOCUMENT;

        actualizeDocumentListView();

        auto* documentInput = new DocumentInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = documentInput->size();
        adjustSize.width();
        documentInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(documentInput);
    } else if (selected == tr("Mitarbeiter*innen Zugang")) { // Employee Account
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: ") << selected;

        actualView = VIEW_EMPLOYEEACCOUNT;

        actualizeEmployeeAccountListView();

        auto* employeeAccountInput = new EmployeeAccountInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = employeeAccountInput->size();
        adjustSize.width();
        employeeAccountInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(employeeAccountInput);

    } else if (selected == tr("Mitarbeiter*innen Dokument")) { // Employee Document
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: ") << selected;

        actualView = VIEW_EMPLOYEEDOCUMENT;

        actualizeEmployeeDocumentListView();

        auto* employeeDocumentInput = new EmployeeDocumentInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = employeeDocumentInput->size();
        adjustSize.width();
        employeeDocumentInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(employeeDocumentInput);

    } else if (selected == tr("Mitarbeiter*innen")) { // Employee
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: ") << selected;
        actualView = VIEW_EMPLOYEE;

        actualizeEmployeeListView();

        auto* employeeInput = new EmployeeInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = employeeInput->size();
        adjustSize.width();
        employeeInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(employeeInput);
    } else if (selected == tr("Fax")) { // Fax
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: ") << selected;

        actualView = VIEW_FAX;

        actualizeFaxListView();

        auto* faxInput = new FaxInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = faxInput->size();
        adjustSize.width();
        faxInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(faxInput);
    } else if (selected == tr("Funktion")) {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: ") << selected;

        actualView = VIEW_FUNCTION;

        actualizeFunctionListView();

        auto* functionInput = new FunctionInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = functionInput->size();
        adjustSize.width();
        functionInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(functionInput);

    } else if (selected == tr("Inventar")) {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: ") << selected;

        actualView = VIEW_INVENTORY;

        actualizeInventoryListView();

        auto* inventoryInput = new InventoryInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = inventoryInput->size();
        adjustSize.width();
        inventoryInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(inventoryInput);
    } else if (selected == tr("Funktion")) { // Function
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: ") << selected;

        actualView = VIEW_FUNCTION;

        actualizeFunctionListView();

        auto* functionInput = new FunctionInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = functionInput->size();
        adjustSize.width();
        functionInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(functionInput);
    } else if (selected == tr("Hersteller")) { // Manufacturer
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: ") << selected;

        actualView = VIEW_MANUFACTURER;

        actualizeManufacturerListView();

        auto* manufacturerInput = new ManufacturerInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = manufacturerInput->size();
        adjustSize.width();
        manufacturerInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(manufacturerInput);
    } else if (selected == tr("Mobile Telefon")) { // Mobile
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: ") << selected;

        actualView = VIEW_MOBILE;

        actualizeMobileListView();

        auto* mobileInput = new MobileInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = mobileInput->size();
        adjustSize.width();
        mobileInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(mobileInput);

    } else if (selected == tr("Betriebssystem")) { // OS
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: ") << selected;

        actualView = VIEW_OS;

        actualizeOsListView();

        auto* osInput = new OSInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = osInput->size();
        adjustSize.width();
        osInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(osInput);
    } else if (selected == tr("Telefon")) { // Phone
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: ") << selected;

        actualView = VIEW_PHONE;

        actualizePhoneListView();

        auto* phoneInput = new PhoneInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = phoneInput->size();
        adjustSize.width();
        phoneInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(phoneInput);
    } else if (selected == tr("Platz")) { // Place
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: ") << selected;

        actualView = VIEW_PLACE;

        actualizePlaceListView();

        auto* placeInput = new PlaceInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = placeInput->size();
        adjustSize.width();
        placeInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(placeInput);
    } else if (selected == tr("Drucker")) { // Printer
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: ") << selected;

        actualView = VIEW_PRINTER;

        actualizePrinterListView();

        auto* printerInput = new PrinterInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = printerInput->size();
        adjustSize.width();
        printerInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(printerInput);

    } else if (selected == tr("Prozessor")) { // Processor
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: ") << selected;

        actualView = VIEW_PROCESSOR;

        actualizeProcessorListView();

        auto* processorInput = new ProcessorInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = processorInput->size();
        adjustSize.width();
        processorInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(processorInput);
    } else if (selected == tr("Software")) { // Software
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: ") << selected;

        actualView = VIEW_SOFTWARE;

        actualizeSoftwareListView();

        auto* softwareInput = new SoftwareInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = softwareInput->size();
        adjustSize.width();
        softwareInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(softwareInput);
    } else if (selected == tr("System Daten")) { // System Data
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: ") << selected;

        actualView = VIEW_SYSTEMDATA;

        actualizeSystemDataListView();

        auto* systemDataInput = new SystemDataInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = systemDataInput->size();
        adjustSize.width();
        systemDataInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(systemDataInput);
    } else if (selected == tr("Titel")) {
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: ") << selected;

        actualView = VIEW_TITLE;

        actualizeTitleListView();

        auto* titleInput = new TitleInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = titleInput->size();
        adjustSize.width();
        titleInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(titleInput);
    } else if (selected == tr("PLZ Stadt")) { // Zip City
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: ") << selected;

        actualView = VIEW_ZIPCITY;

        actualizeZipCityListView();

        auto* zipCityInput = new ZipCityInputArea(ui->scrollArea, QModelIndex());
        QSize adjustSize = zipCityInput->size();
        adjustSize.width();
        zipCityInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(zipCityInput);
    } else if (selected == tr("PLZ Code")) { // Zip Code
        qCDebug(jmbdeWidgetsMainWindowLog) << tr("Auswahl: ") << selected;

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

        QObject::connect(accountInput, &AccountInputArea::dataChanged, this, &MainWindow::actualizeAccountListView);
        QSize adjustSize = accountInput->size();
        adjustSize.width();
        accountInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(accountInput);
    } break;

    case VIEW_CHIPCARDDOOR: {
        auto* chipCardDoorInput = new ChipCardDoorInputArea(ui->scrollArea, index);

        QObject::connect(chipCardDoorInput, &ChipCardDoorInputArea::dataChanged, this, &MainWindow::actualizeChipCardDoorListView);

        QSize adjustSize = chipCardDoorInput->size();
        adjustSize.width();
        chipCardDoorInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(chipCardDoorInput);
    } break;

    case VIEW_CHIPCARD: {
        auto* chipCardInput = new ChipCardInputArea(ui->scrollArea, index);

        QObject::connect(chipCardInput, &ChipCardInputArea::dataChanged, this, &MainWindow::actualizeChipCardListView);

        QSize adjustSize = chipCardInput->size();
        adjustSize.width();
        chipCardInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(chipCardInput);
    } break;

    case VIEW_CHIPCARDPROFILEDOOR: {
        auto* chipCardProfileDoorInput = new ChipCardProfileDoorInputArea(ui->scrollArea, index);

        QObject::connect(chipCardProfileDoorInput, &ChipCardProfileDoorInputArea::dataChanged, this, &MainWindow::actualizeChipCardProfileDoorListView);

        QSize adjustSize = chipCardProfileDoorInput->size();
        adjustSize.width();
        chipCardProfileDoorInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(chipCardProfileDoorInput);
    } break;

    case VIEW_CHIPCARDPROFILE: {
        auto* chipCardProfileInput = new ChipCardProfileInputArea(ui->scrollArea, index);

        QObject::connect(chipCardProfileInput, &ChipCardProfileInputArea::dataChanged, this, &MainWindow::actualizeChipCardProfileListView);

        QSize adjustSize = chipCardProfileInput->size();
        adjustSize.width();
        chipCardProfileInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(chipCardProfileInput);
    } break;

    case VIEW_CITYNAME: {
        auto* cityNameInput = new CityInputArea(ui->scrollArea, index);

        QObject::connect(cityNameInput, &CityInputArea::dataChanged, this, &MainWindow::actualizeCityListView);

        QSize adjustSize = cityNameInput->size();
        adjustSize.width();
        cityNameInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(cityNameInput);
    } break;

    case VIEW_COMPANY: {
        auto* companyInput = new CompanyInputArea(ui->scrollArea, index);

        QObject::connect(companyInput, &CompanyInputArea::dataChanged, this, &MainWindow::actualizeCompanyListView);

        QSize adjustSize = companyInput->size();
        adjustSize.width();
        companyInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(companyInput);
    } break;

    case VIEW_COMPUTER: {
        auto* computerInput = new ComputerInputArea(ui->scrollArea, index);

        QObject::connect(computerInput, &ComputerInputArea::dataChanged, this, &MainWindow::actualizeComputerListView);

        QSize adjustSize = computerInput->size();
        adjustSize.width();
        computerInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(computerInput);
    } break;

    case VIEW_COMPUTERSOFTWARE: {
        auto* computerSoftwareInput = new ComputerSoftwareInputArea(ui->scrollArea, index);

        QObject::connect(computerSoftwareInput, &ComputerSoftwareInputArea::dataChanged, this, &MainWindow::actualizeComputerSoftwareListView);

        QSize adjustSize = computerSoftwareInput->size();
        adjustSize.width();
        computerSoftwareInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(computerSoftwareInput);
    } break;

    case VIEW_DEPARTMENT: {
        auto* departmentInput = new DepartmentInputArea(ui->scrollArea, index);

        QObject::connect(departmentInput, &DepartmentInputArea::dataChanged, this, &MainWindow::actualizeDepartmentListView);

        QSize adjustSize = departmentInput->size();
        adjustSize.width();
        departmentInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(departmentInput);
    } break;

    case VIEW_DEVICENAME: {
        auto* deviceNameInput = new DeviceNameInputArea(ui->scrollArea, index);

        QObject::connect(deviceNameInput, &DeviceNameInputArea::dataChanged, this, &MainWindow::actualizeDeviceNameListView);

        QSize adjustSize = deviceNameInput->size();
        adjustSize.width();
        deviceNameInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(deviceNameInput);
    } break;

    case VIEW_DEVICETYPE: {
        auto* deviceTypeInput = new DeviceTypeInputArea(ui->scrollArea, index);

        QObject::connect(deviceTypeInput, &DeviceTypeInputArea::dataChanged, this, &MainWindow::actualizeDeviceTypeListView);

        QSize adjustSize = deviceTypeInput->size();
        adjustSize.width();
        deviceTypeInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(deviceTypeInput);
    } break;

    case VIEW_DOCUMENT: {
        auto* documentInput = new DocumentInputArea(ui->scrollArea, index);

        QObject::connect(documentInput, &DocumentInputArea::dataChanged, this, &MainWindow::actualizeDocumentListView);

        QSize adjustSize = documentInput->size();
        adjustSize.width();
        documentInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(documentInput);
    } break;

    case VIEW_EMPLOYEEACCOUNT: {
        auto* employeeAccountInput = new EmployeeAccountInputArea(ui->scrollArea, index);

        QObject::connect(employeeAccountInput, &EmployeeAccountInputArea::dataChanged, this, &MainWindow::actualizeEmployeeAccountListView);

        QSize adjustSize = employeeAccountInput->size();
        adjustSize.width();
        employeeAccountInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(employeeAccountInput);
    } break;

    case VIEW_EMPLOYEEDOCUMENT: {
        auto* employeeDocumentInput = new EmployeeDocumentInputArea(ui->scrollArea, index);

        QObject::connect(employeeDocumentInput, &EmployeeDocumentInputArea::dataChanged, this, &MainWindow::actualizeEmployeeDocumentListView);

        QSize adjustSize = employeeDocumentInput->size();
        adjustSize.width();
        employeeDocumentInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(employeeDocumentInput);
    } break;

    case VIEW_EMPLOYEE: {
        auto* employeeInput = new EmployeeInputArea(ui->scrollArea, index);

        QObject::connect(employeeInput, &EmployeeInputArea::dataChanged, this, &MainWindow::actualizeEmployeeListView);

        QSize adjustSize = employeeInput->size();
        adjustSize.width();
        employeeInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(employeeInput);

    } break;

    case VIEW_EMPLOYEE_LIST: {
        auto* employeeList = new EmployeeTable(ui->scrollArea, index);

        QSize adjustSize = employeeList->size();
        adjustSize.width();
        employeeList->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(employeeList);
    } break;

    case VIEW_FAX: {
        auto* faxInput = new FaxInputArea(ui->scrollArea, index);

        QObject::connect(faxInput, &FaxInputArea::dataChanged, this, &MainWindow::actualizeFaxListView);

        QSize adjustSize = faxInput->size();
        adjustSize.width();
        faxInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(faxInput);
    } break;

    case VIEW_FUNCTION: {
        auto* functionInput = new FunctionInputArea(ui->scrollArea, index);

        QObject::connect(functionInput, &FunctionInputArea::dataChanged, this, &MainWindow::actualizeFunctionListView);

        QSize adjustSize = functionInput->size();
        adjustSize.width();
        functionInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(functionInput);
    } break;

    case VIEW_INVENTORY: {
        auto* inventoryInput = new InventoryInputArea(ui->scrollArea, index);

        QObject::connect(inventoryInput, &InventoryInputArea::dataChanged, this, &MainWindow::actualizeInventoryListView);

        QSize adjustSize = inventoryInput->size();
        adjustSize.width();
        inventoryInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(inventoryInput);
    } break;

    case VIEW_MANUFACTURER: {
        auto* manufacturerInput = new ManufacturerInputArea(ui->scrollArea, index);

        QObject::connect(manufacturerInput, &ManufacturerInputArea::dataChanged, this, &MainWindow::actualizeManufacturerListView);

        QSize adjustSize = manufacturerInput->size();
        adjustSize.width();
        manufacturerInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(manufacturerInput);
    } break;

    case VIEW_MOBILE: {
        auto* mobileInput = new MobileInputArea(ui->scrollArea, index);

        QObject::connect(mobileInput, &MobileInputArea::dataChanged, this, &MainWindow::actualizeMobileListView);

        QSize AdjustSize = mobileInput->size();
        AdjustSize.width();
        mobileInput->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(mobileInput);
    } break;

    case VIEW_OS: {
        auto* osInput = new OSInputArea(ui->scrollArea, index);

        QObject::connect(osInput, &OSInputArea::dataChanged, this, &MainWindow::actualizeOsListView);

        QSize adjustSize = osInput->size();
        adjustSize.width();
        osInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(osInput);
    } break;

    case VIEW_PHONE: {
        auto* phoneInput = new PhoneInputArea(ui->scrollArea, index);

        QObject::connect(phoneInput, SIGNAL(dataChanged()), this, SLOT(actualizePhoneListView()));

        QSize adjustSize = phoneInput->size();
        adjustSize.width();
        phoneInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(phoneInput);
    } break;

    case VIEW_PLACE: {
        auto* placeInput = new PlaceInputArea(ui->scrollArea, index);

        QObject::connect(placeInput, &PlaceInputArea::dataChanged, this, &MainWindow::actualizePlaceListView);

        QSize adjustSize = placeInput->size();
        adjustSize.width();
        placeInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(placeInput);
    } break;

    case VIEW_PRINTER: {
        auto* printerInput = new PrinterInputArea(ui->scrollArea, index);

        QObject::connect(printerInput, &PrinterInputArea::dataChanged, this, &MainWindow::actualizePrinterListView);

        QSize adjustSize = printerInput->size();
        adjustSize.width();
        printerInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(printerInput);
    } break;

    case VIEW_PROCESSOR: {
        auto* processorInput = new ProcessorInputArea(ui->scrollArea, index);

        QObject::connect(processorInput, &ProcessorInputArea::dataChanged, this, &MainWindow::actualizeProcessorListView);

        QSize adjustSize = processorInput->size();
        adjustSize.width();
        processorInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(processorInput);
    } break;

    case VIEW_SOFTWARE: {
        auto* softwareInput = new SoftwareInputArea(ui->scrollArea, index);

        QObject::connect(softwareInput, &SoftwareInputArea::dataChanged, this, &MainWindow::actualizeSoftwareListView);

        QSize adjustSize = softwareInput->size();
        adjustSize.width();
        softwareInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(softwareInput);
    } break;

    case VIEW_SYSTEMDATA: {
        auto* systemDataInput = new SystemDataInputArea(ui->scrollArea, index);

        QObject::connect(systemDataInput, &SystemDataInputArea::dataChanged, this, &MainWindow::actualizeSystemDataListView);

        QSize adjustSize = systemDataInput->size();
        adjustSize.width();
        systemDataInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(systemDataInput);
    } break;

    case VIEW_TITLE: {
        auto* titleInput = new TitleInputArea(ui->scrollArea, index);

        QObject::connect(titleInput, &TitleInputArea::dataChanged, this, &MainWindow::actualizeTitleListView);

        QSize adjustSize = titleInput->size();
        adjustSize.width();
        titleInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(titleInput);
    } break;

    case VIEW_ZIPCITY: {
        auto* zipCityInput = new ZipCityInputArea(ui->scrollArea, index);

        QObject::connect(zipCityInput, &ZipCityInputArea::dataChanged, this, &MainWindow::actualizeZipCityListView);

        QSize adjustSize = zipCityInput->size();
        adjustSize.width();
        zipCityInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(zipCityInput);
    } break;

    case VIEW_ZIPCODE: {
        auto* zipCodeInput = new ZipCodeInputArea(ui->scrollArea, index);

        QObject::connect(zipCodeInput, &ZipCodeInputArea::dataChanged, this, &MainWindow::actualizeZipCodeListView);

        QSize adjustSize = zipCodeInput->size();
        adjustSize.width();
        zipCodeInput->setMinimumSize(adjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(zipCodeInput);
    } break;
    default:
        const QString caller = tr("onClickedlistViewRow(): Unbekannte Funktion");
        notAvailableMessage(caller);
        break;
    }
}

void MainWindow::actualizeAccountListView()
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
    int modelIndex = chipCardProfileModel->getNumberIndex();
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
    qCDebug(jmbdeWidgetsMainWindowLog) << tr("Aufruf von: void MainWindow::actualizeEmployeeListView()");

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
    tableModel = printerModel->initializeRelationalModel();

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
    auto* zipCodeModel = new Model::ZipCode();
    tableModel = zipCodeModel->initializeRelationalModel();

    QSqlTableModel* listModel = zipCodeModel->initializeListModel();
    int modelIndex = zipCodeModel->getCodeIndex();
    zipCodeModel->sort(modelIndex, Qt::AscendingOrder);
    actualizeListView(listModel, modelIndex);
}

void MainWindow::actualizeListView(QSqlTableModel* listModel, int idx)
{
    ui->listView->setModel(listModel);
    ui->listView->setModelColumn(idx);
    ui->listView->repaint();
    ui->listView->show();
}
