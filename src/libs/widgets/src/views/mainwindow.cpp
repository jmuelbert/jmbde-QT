/*
   jmbde a BDE Tool for companies
   Copyright (C) 2013-2019  Jürgen Mülbert

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

    this->dataBaseName = QString(QStringLiteral("jmbde"));
    this->dataContext = new Model::DataContext(dynamic_cast<QObject *>(this), this->dataBaseName);
    qDebug() << "ActualViewRow : " << m_actualView;

    if (m_actualView.row() > 0) {
        ui->treeView->setCurrentIndex(m_actualView);
        onClickedTreeView(m_actualView);
    } else {
        qDebug() << "Select Employee";
        actualView = VIEW_EMPLOYEE;
        dataContext->openDB(dataBaseName);
        auto *edm = new Model::Employee;
        tableModel = edm->initializeRelationalModel();
        int idx = edm->LastNameIndex();

        ui->listView->setModel(tableModel);
        ui->listView->setModelColumn(idx);

        QModelIndex qmi = QModelIndex();
        auto *eia = new EmployeeInputArea(ui->scrollArea, qmi);
        dataContext->closeConnection();
        QSize AdjustSize = eia->size();
        AdjustSize.width();
        eia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(eia);
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

    qDebug() << "Resize...";
    qDebug() << "width= " << width << " height= " << height;
    ui->splitter->resize(width, height);
}

void MainWindow::focusChanged(QWidget *, QWidget *now)
{
    Q_UNUSED(now)

    qDebug() << "Help :-)";
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
}

void MainWindow::on_actionPreferences_triggered()
{
    auto *view = new QQuickWidget;
    view->setSource(QUrl(QLatin1String("qrc:/Preferences.qml")));
    if (view->status() == QQuickWidget::Error)
        return;
    view->show();
}

void MainWindow::on_actionAbout_triggered()
{
    auto *view = new QQuickWidget;
    view->setSource(QUrl(QLatin1String("qrc:/AboutBox.qml")));
    if (view->status() == QQuickWidget::Error)
        return;
    view->show();
}

void MainWindow::initOutline()
{
    QHash<QString, QList<QString>> outlineData;

    QList<QString> subEntries = {tr("Employee"), tr("Function"), tr("Deparment"), tr("Title")};
    outlineData.insert(tr("Person"), subEntries);

    subEntries = {tr("Computer"), tr("Processor"), tr("Operation System"), tr("Software"), tr("Printer")};
    outlineData.insert(tr("Device"), subEntries);

    subEntries = {tr("Phone"), tr("Mobile")};
    outlineData.insert(tr("Communication"), subEntries);

    subEntries = {tr("Manufacturer"), tr("City"), tr("Chipcard")};
    outlineData.insert(tr("Misc"), subEntries);

    m_treeviewModel = new QStandardItemModel(this);
    QStandardItem *parentItem = m_treeviewModel->invisibleRootItem();

    QStandardItem *item;

    QList<QString> od;
    QHashIterator<QString, QList<QString>> i(outlineData);
    while (i.hasNext()) {
        i.next();
        auto *header = new QStandardItem(i.key());
        parentItem->appendRow(header);
        qDebug() << i.key() << ": " << i.value() << endl;

        od = i.value();
        for (int index = 0; index < od.size(); ++index) {
            item = new QStandardItem(od.value(index));
            header->appendRow(item);
            qDebug() << "Found " << od.value(index) << " at position " << index << endl;
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
                                   tr("This action create a new dataContext. if you have an dataContext\n"
                                      "with data you lost this.\n"
                                      "Proceed for create a new dataContext ?"),
                                   QMessageBox::Cancel | QMessageBox::Yes);

    if (ret == QMessageBox::Yes) {
        // TODO: Implement Create a new DB
        // dataContext->initDb();
        QMessageBox::information(this, qApp->applicationDisplayName(), tr("The new dataContext is created"));
    }
}

void MainWindow::on_actionQuit_triggered()
{
    qApp->quit();
}

void MainWindow::on_actionOpen_triggered()
{
    Not_Available_Message();
}

void MainWindow::on_actionImport_triggered()
{
    auto *csvImport = new CsvImportDialog();

    csvImport->show();
}

void MainWindow::on_actionExport_triggered()
{
    Not_Available_Message();
}

void MainWindow::on_actionPrint_triggered()
{
    QTextDocument doc;

    switch (actualView) {
    case VIEW_EMPLOYEE: {
        qDebug() << "Print Employee !";
        dataContext->openDB(dataBaseName);
        auto *edm = new Model::Employee;
        QString style = edm->setOutTableStyle();
        QString text = edm->generateTableString(tr("Employee"));

        doc.setHtml(style + text);
        dataContext->closeConnection();
    } break;

    case VIEW_COMPUTER: {
        qDebug() << "Print Computer !";
        dataContext->openDB(dataBaseName);
        auto *cdm = new Model::Computer;
        QString style = cdm->setOutTableStyle();
        QString text = cdm->generateTableString(tr("Computer"));

        doc.setHtml(style + text);
        dataContext->closeConnection();
    } break;

    case VIEW_PRINTER: {
        qDebug() << "Print Printer !";
        dataContext->openDB(dataBaseName);
        auto *pdm = new Model::Printer;
        QString style = pdm->setOutTableStyle();
        QString text = pdm->generateTableString(tr("Printer"));

        doc.setHtml(style + text);
        dataContext->closeConnection();
    } break;

    case VIEW_PHONE: {
        qDebug() << "Print Printer !";
        dataContext->openDB(dataBaseName);
        auto *pdm = new Model::Phone;
        QString style = pdm->setOutTableStyle();
        QString text = pdm->generateTableString(tr("Phone"));

        doc.setHtml(style + text);
        dataContext->closeConnection();
    } break;

    default:
        Not_Available_Message();
    }

#if !defined(QT_NO_PRINTER) && !defined(QT_NO_PRINTDIALOG)
    QPrinter printer(QPrinter::HighResolution);

    printer.setOrientation(QPrinter::Landscape);
    QPrintDialog *dlg = new QPrintDialog(&printer, this);

    dlg->setWindowTitle(tr("Print Document"));
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
        qDebug() << "Print Employee !";

        dataContext->openDB(dataBaseName);

        auto *edm = new Model::Employee;
        QString style = edm->setOutTableStyle();
        QString text = edm->generateTableString(tr("Employee"));

        doc.setHtml(style + text);
        dataContext->closeConnection();
    } break;

    case VIEW_COMPUTER: {
        qDebug() << "Print Computer !";

        dataContext->openDB(dataBaseName);

        auto *cdm = new Model::Computer;
        QString style = cdm->setOutTableStyle();
        QString text = cdm->generateTableString(tr("Computer"));

        doc.setHtml(style + text);
        dataContext->closeConnection();
    } break;

    case VIEW_PRINTER: {
        qDebug() << "Print Printer !";
        dataContext->openDB(dataBaseName);

        auto *pdm = new Model::Printer;
        QString style = pdm->setOutTableStyle();
        QString text = pdm->generateTableString(tr("Printer"));

        doc.setHtml(style + text);
        dataContext->closeConnection();
    } break;

    case VIEW_PHONE: {
        qDebug() << "Print Printer !";

        dataContext->openDB(dataBaseName);

        auto *pdm = new Model::Phone;
        QString style = pdm->setOutTableStyle();
        QString text = pdm->generateTableString(tr("Phone"));

        doc.setHtml(style + text);
        dataContext->closeConnection();
    } break;

    default:
        Not_Available_Message();
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
        qDebug() << "Print Employee !";

        dataContext->openDB(dataBaseName);

        auto *edm = new Model::Employee;
        QString style = edm->setOutTableStyle();
        QString text = edm->generateTableString(tr("Employee"));

        doc.setHtml(style + text);
        dataContext->closeConnection();
    } break;

    case VIEW_COMPUTER: {
        qDebug() << "Print Computer !";

        dataContext->openDB(dataBaseName);

        auto *cdm = new Model::Computer;
        QString style = cdm->setOutTableStyle();
        QString text = cdm->generateTableString(tr("Computer"));

        doc.setHtml(style + text);
        dataContext->closeConnection();
    } break;

    case VIEW_PRINTER: {
        qDebug() << "Print Printer !";

        dataContext->openDB(dataBaseName);

        auto *pdm = new Model::Printer;
        QString style = pdm->setOutTableStyle();
        QString text = pdm->generateTableString(tr("Printer"));

        doc.setHtml(style + text);
        dataContext->closeConnection();
    } break;

    case VIEW_PHONE: {
        qDebug() << "Print Printer !";

        dataContext->openDB(dataBaseName);

        auto *pdm = new Model::Phone;
        QString style = pdm->setOutTableStyle();
        QString text = pdm->generateTableString(tr("Phone"));

        doc.setHtml(style + text);
        dataContext->closeConnection();
    } break;

    default:
        Not_Available_Message();
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

void MainWindow::Not_Available_Message()
{
    QString message =
        tr("This action is not implemented\n"
           "in the version ");

    message.append(qApp->applicationVersion());
    message.append(tr("\nPlease try a newer version, if any available\n"));
    message.append(tr("you can check this on the project site:\n"));
    message.append(qApp->organizationDomain());

    QMessageBox::critical(this, qApp->applicationDisplayName(), message, QMessageBox::Cancel);
}

void MainWindow::on_actionHelp_triggered()
{
    Not_Available_Message();
}

void MainWindow::onClickedTreeView(const QModelIndex &index)
{
    const QStandardItem *item = m_treeviewModel->itemFromIndex(index);
    const QString selected = item->text();

    m_actualView = index;
    qDebug() << "ActualViewRow : " << index;
    qDebug() << "Item: " << selected;

    // Headers -> no action
    if ((selected == tr("Person")) || (selected == tr("Device")) || (selected == tr("Communication")) || (selected == tr("Misc"))) {
        return;
    }

    // Tree -> Person
    if (selected == tr("Employee")) {
        qDebug() << "Select Employee";
        actualView = VIEW_EMPLOYEE;

        dataContext->openDB(dataBaseName);
        auto *edm = new Model::Employee;

        tableModel = edm->initializeRelationalModel();
        int idx = edm->LastNameIndex();

        ui->listView->setModel(tableModel);
        ui->listView->setModelColumn(idx);
        QModelIndex qmi = QModelIndex();

        auto *eia = new EmployeeInputArea(ui->scrollArea, qmi);
        QSize AdjustSize = eia->size();
        AdjustSize.width();
        eia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(eia);
        dataContext->closeConnection();
    } else if (selected == tr("Function")) {
        qDebug() << "Select Function";

        actualView = VIEW_FUNCTION;

        dataContext->openDB(dataBaseName);
        auto *fdm = new Model::Function;

        tableModel = fdm->initializeRelationalModel();

        ui->listView->setModel(tableModel);
        int idx = fdm->NameIndex();
        ui->listView->setModelColumn(idx);
        QModelIndex qmi = QModelIndex();
        auto *fia = new FunctionInputArea(ui->scrollArea, qmi);
        ui->scrollArea->setWidget(fia);
        dataContext->closeConnection();
    } else if (selected == tr("Department")) {
        qDebug() << "Select Department";

        actualView = VIEW_DEPARTMENT;

        dataContext->openDB(dataBaseName);
        auto *dpm = new Model::Department;

        tableModel = dpm->initializeRelationalModel();
        int idx = dpm->NameIndex();

        ui->listView->setModel(tableModel);
        ui->listView->setModelColumn(idx);
        QModelIndex qmi = QModelIndex();
        auto *dia = new DepartmentInputArea(ui->scrollArea, qmi);
        ui->scrollArea->setWidget(dia);
        dataContext->closeConnection();
    } else if (selected == tr("Title")) {
        qDebug() << "Select Title";

        actualView = VIEW_TITLE;

        dataContext->openDB(dataBaseName);
        auto *tdm = new Model::Title;

        tableModel = tdm->initializeRelationalModel();
        int idx = tdm->NameIndex();

        ui->listView->setModel(tableModel);
        ui->listView->setModelColumn(idx);

        QModelIndex qmi = QModelIndex();
        auto *tia = new TitleInputArea(ui->scrollArea, qmi);
        ui->scrollArea->setWidget(tia);
        dataContext->closeConnection();
        // Tree -> Device
    } else if (selected == tr("Computer")) {
        qDebug() << "Select Computer";

        actualView = VIEW_COMPUTER;

        dataContext->openDB(dataBaseName);
        auto *cdm = new Model::Computer;

        tableModel = cdm->initializeRelationalModel();
        int idx = cdm->NameIndex();

        ui->listView->setModel(tableModel);
        ui->listView->setModelColumn(idx);

        QModelIndex qmi = QModelIndex();
        auto *cia = new ComputerInputArea(ui->scrollArea, qmi);
        ui->scrollArea->setWidget(cia);
        dataContext->closeConnection();
    } else if (selected == tr("Processor")) {
        qDebug() << "Select Processor";

        actualView = VIEW_PROCESSOR;

        dataContext->openDB(dataBaseName);
        auto *pdm = new Model::Processor;

        tableModel = pdm->initializeRelationalModel();
        int idx = pdm->NameIndex();

        ui->listView->setModel(tableModel);
        ui->listView->setModelColumn(idx);

        QModelIndex qmi = QModelIndex();
        auto *pia = new ProcessorInputArea(ui->scrollArea, qmi);
        ui->scrollArea->setWidget(pia);
        dataContext->closeConnection();
    } else if (selected == tr("Operation System")) {
        qDebug() << "Select Operation System";

        actualView = VIEW_OS;

        dataContext->openDB(dataBaseName);
        auto *odm = new Model::OS;

        tableModel = odm->initializeRelationalModel();
        int idx = odm->NameIndex();

        ui->listView->setModel(tableModel);
        ui->listView->setModelColumn(idx);

        QModelIndex qmi = QModelIndex();
        auto *oia = new OSInputArea(ui->scrollArea, qmi);
        ui->scrollArea->setWidget(oia);
        dataContext->closeConnection();
    } else if (selected == tr("Software")) {
        qDebug() << "Select Software";

        actualView = VIEW_SOFTWARE;

        dataContext->openDB(dataBaseName);
        auto *sdm = new Model::Software;

        tableModel = sdm->initializeRelationalModel();
        int idx = sdm->NameIndex();

        ui->listView->setModel(tableModel);
        ui->listView->setModelColumn(idx);

        QModelIndex qmi = QModelIndex();
        auto *sia = new SoftwareInputArea(ui->scrollArea, qmi);
        ui->scrollArea->setWidget(sia);
        dataContext->closeConnection();
    } else if (selected == tr("Printer")) {
        qDebug() << "Select Printer";

        actualView = VIEW_PRINTER;

        dataContext->openDB(dataBaseName);
        auto *pdm = new Model::Printer;

        tableModel = pdm->initializeRelationalModel();
        int idx = pdm->NetworkNameIndex();

        ui->listView->setModel(tableModel);
        ui->listView->setModelColumn(idx);

        QModelIndex qmi = QModelIndex();
        auto *pia = new PrinterInputArea(ui->scrollArea, qmi);
        ui->scrollArea->setWidget(pia);
        dataContext->closeConnection();
        // Tree -> Communication
    } else if (selected == tr("Phone")) {
        qDebug() << "Select Phone";

        actualView = VIEW_PHONE;

        dataContext->openDB(dataBaseName);
        auto *phdm = new Model::Phone;

        tableModel = phdm->initializeRelationalModel();
        int idx = phdm->NumberIndex();

        ui->listView->setModel(tableModel);
        ui->listView->setModelColumn(idx);

        QModelIndex qmi = QModelIndex();
        auto *pia = new PhoneInputArea(ui->scrollArea, qmi);
        ui->scrollArea->setWidget(pia);
        dataContext->closeConnection();
    } else if (selected == tr("Mobile")) {
        qDebug() << "Select Mobile";

        actualView = VIEW_MOBILE;

        dataContext->openDB(dataBaseName);
        auto *phdm = new Model::Mobile;

        tableModel = phdm->initializeRelationalModel();
        int idx = phdm->NumberIndex();

        ui->listView->setModel(tableModel);
        ui->listView->setModelColumn(idx);

        QModelIndex qmi = QModelIndex();
        auto *mia = new MobileInputArea(ui->scrollArea, qmi);
        ui->scrollArea->setWidget(mia);
        dataContext->closeConnection();
        // Tree -> Misc
    } else if (selected == tr("Manufacturer")) {
        qDebug() << "Select Manufacturer";

        actualView = VIEW_MANUFACTURER;

        dataContext->openDB(dataBaseName);
        auto *mdm = new Model::Manufacturer;

        tableModel = mdm->initializeRelationalModel();
        int idx = mdm->NameIndex();

        ui->listView->setModel(tableModel);
        ui->listView->setModelColumn(idx);

        QModelIndex qmi = QModelIndex();
        auto *mia = new ManufacturerInputArea(ui->scrollArea, qmi);
        ui->scrollArea->setWidget(mia);
        dataContext->closeConnection();
    } else if (selected == tr("City")) {
        qDebug() << "Select Zip City";

        actualView = VIEW_CITY;

        dataContext->openDB(dataBaseName);
        auto *cnm = new Model::CityName;

        tableModel = cnm->initializeRelationalModel();
        int idx = cnm->NameIndex();

        ui->listView->setModel(tableModel);
        ui->listView->setModelColumn(idx);

        QModelIndex qmi = QModelIndex();
        auto *cia = new CityInputArea(ui->scrollArea, qmi);
        ui->scrollArea->setWidget(cia);
        dataContext->closeConnection();
    } else if (selected == tr("Chipcard")) {
        qDebug() << "Select Chipcard";

        actualView = VIEW_CHIPCARD;

        dataContext->openDB(dataBaseName);
        auto *ccdm = new Model::ChipCard;

        tableModel = ccdm->initializeRelationalModel();
        int idx = ccdm->NumberIndex();

        ui->listView->setModel(tableModel);
        ui->listView->setModelColumn(idx);

        QModelIndex qmi = QModelIndex();
        auto *cia = new ChipCardInputArea(ui->scrollArea, qmi);
        ui->scrollArea->setWidget(cia);
        dataContext->closeConnection();
    } else {
        Not_Available_Message();
    }
}

void MainWindow::onClickedListViewRow(const QModelIndex &index)
{
    m_actualData = index;
    qDebug() << "Clicked: ActualDataRow : " << index;

    switch (actualView) {
    case VIEW_EMPLOYEE: {
        qDebug() << "Employee Table Row (" << index.row() << ") clicked";

        dataContext->openDB(dataBaseName);
        auto *eia = new EmployeeInputArea(nullptr, index);

        QSize AdjustSize = eia->size();
        AdjustSize.width();
        eia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(eia);
        dataContext->closeConnection();
    } break;

    case VIEW_FUNCTION: {
        dataContext->openDB(dataBaseName);
        auto *fia = new FunctionInputArea(nullptr, index);

        QSize AdjustSize = fia->size();
        AdjustSize.width();
        fia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(fia);
        dataContext->closeConnection();
    } break;

    case VIEW_DEPARTMENT: {
        dataContext->openDB(dataBaseName);
        auto *dia = new DepartmentInputArea(nullptr, index);

        QSize AdjustSize = dia->size();
        AdjustSize.width();
        dia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(dia);
        dataContext->closeConnection();
    } break;

    case VIEW_TITLE: {
        dataContext->openDB(dataBaseName);
        auto *fia = new FunctionInputArea(nullptr, index);

        QSize AdjustSize = fia->size();
        AdjustSize.width();
        fia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(fia);
        dataContext->closeConnection();
    } break;

    case VIEW_COMPUTER: {
        qDebug() << "Computer Table Row (" << index.row() << ") clicked";

        dataContext->openDB(dataBaseName);
        auto *cia = new ComputerInputArea(nullptr, index);

        QSize AdjustSize = cia->size();
        AdjustSize.width();
        cia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(cia);
        dataContext->closeConnection();
    } break;

    case VIEW_PROCESSOR: {
        dataContext->openDB(dataBaseName);
        auto *pia = new ProcessorInputArea(nullptr, index);

        QSize AdjustSize = pia->size();
        AdjustSize.width();
        pia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(pia);
        dataContext->closeConnection();
    } break;

    case VIEW_OS: {
        dataContext->openDB(dataBaseName);
        auto *oia = new OSInputArea(nullptr, index);

        QSize AdjustSize = oia->size();
        AdjustSize.width();
        oia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(oia);
        dataContext->closeConnection();
    } break;

    case VIEW_SOFTWARE: {
        dataContext->openDB(dataBaseName);
        auto *sia = new SoftwareInputArea(nullptr, index);

        QSize AdjustSize = sia->size();
        AdjustSize.width();
        sia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(sia);
        dataContext->closeConnection();
    } break;

    case VIEW_PRINTER: {
        dataContext->openDB(dataBaseName);
        auto *pia = new PrinterInputArea(nullptr, index);

        QSize AdjustSize = pia->size();
        AdjustSize.width();
        pia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(pia);
        dataContext->closeConnection();
    } break;

    case VIEW_PHONE: {
        dataContext->openDB(dataBaseName);
        auto *pia = new PhoneInputArea(nullptr, index);

        QSize AdjustSize = pia->size();
        AdjustSize.width();
        pia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(pia);
        dataContext->closeConnection();
    } break;

    case VIEW_MOBILE: {
        dataContext->openDB(dataBaseName);
        auto *mia = new MobileInputArea(nullptr, index);

        QSize AdjustSize = mia->size();
        AdjustSize.width();
        mia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(mia);
        dataContext->closeConnection();
    } break;

    case VIEW_MANUFACTURER: {
        dataContext->openDB(dataBaseName);
        auto *mia = new ManufacturerInputArea(nullptr, index);

        QSize AdjustSize = mia->size();
        AdjustSize.width();
        mia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(mia);
        dataContext->closeConnection();
    } break;

    case VIEW_CITY: {
        dataContext->openDB(dataBaseName);
        auto *cia = new CityInputArea(nullptr, index);

        QSize AdjustSize = cia->size();
        AdjustSize.width();
        cia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(cia);
        dataContext->closeConnection();
    }

    break;

    case VIEW_CHIPCARD: {
        dataContext->openDB(dataBaseName);
        auto *ccia = new ChipCardInputArea(nullptr, index);

        QSize AdjustSize = ccia->size();
        AdjustSize.width();
        ccia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(ccia);
        dataContext->closeConnection();
    } break;
    default:
        Not_Available_Message();
        break;
    }
}

void MainWindow::onPressedListViewRow(const QModelIndex &index)
{
    m_actualData = index;
    qDebug() << "Pressed: ActualDataRow for deleteting: " << index;

    switch (actualView) {
    case VIEW_EMPLOYEE: {
        qDebug() << "Employee Table Row (" << index.row() << ") clicked";

        dataContext->openDB(dataBaseName);
        auto *eia = new EmployeeInputArea(nullptr, index);

        QSize AdjustSize = eia->size();
        AdjustSize.width();
        eia->setMinimumSize(AdjustSize);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(eia);
        qDebug() << "Delete index : " << index;
        dataContext->closeConnection();
    } break;
    }
}
