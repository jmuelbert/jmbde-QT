#include "csvimportdialog.h"
#include "ui_csvimportdialog.h"

CsvImportDialog::CsvImportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CsvImportDialog)
{
    ui->setupUi(this);
    model = new QStandardItemModel(this);
    ui->tableView->setModel(model);

#if QT_VERSION >= 0x050000
    QStringList dataDirList = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    // Use user space

    QString dataBaseDirAndFile = dataDirList.at(0);
#else
    QString dataBaseDirAndFile =QDir::homePath();
#endif

    QString fileName = QFileDialog::getOpenFileName(0, tr("open CSV file"),
                                                    dataBaseDirAndFile,
                                                    "CSV (*.csv)");
    QFile file (fileName);
    if (file.open(QFile::Text | QIODevice::ReadOnly)) {
        QString data = file.readAll();
        data.remove( QRegExp("\r"));
        QString temp;
        QChar character;
        QTextStream textStream(&data);
        while (!textStream.atEnd()) {
            textStream >> character;
            if (character == ',') {
                checkString(temp, character);
            } else if (character == ';') {
                character = ',';
                checkString(temp, character);
            } else if (character == '\n') {
                checkString(temp, character);
            } else if (textStream.atEnd()) {
                temp.append(character);
                checkString(temp);
            } else {
                temp.append(character);
            }
        }
    }
}

CsvImportDialog::~CsvImportDialog()
{
    delete ui;
}


void CsvImportDialog::checkString(QString &temp, QChar character)
{
    if (temp.count("\"") %2 == 0) {
        if (temp.startsWith( QChar ('\"')) && temp.endsWith( QChar ('\"'))) {
            temp.remove( QRegExp("^\""));
            temp.remove( QRegExp("\"$"));
        }
        // FIXME: will possibly fail if there are 4 or more reapeating double quotes
        temp.replace("\"\"", "\"");
        QStandardItem *item = new QStandardItem(temp);
        standardItemList.append(item);
        if (character != QChar(',')) {
            model->appendRow(standardItemList);
            standardItemList.clear();
        }
        temp.clear();
    } else {
        temp.append(character);
    }
}

void CsvImportDialog::on_buttonBox_accepted()
{
    int columnCount = model->columnCount();
    int rowCount = model->rowCount();
    qDebug() << "Columns : " << columnCount << " Rows : " << rowCount;
    QString tempString;
    for (int i=0; i<rowCount; i++) {
        for (int j=0; j<columnCount; j++) {
            QModelIndex ind(model->index(i, j));
            tempString.append(ind.data(Qt::DisplayRole).toString() + ", ");
        }
        qDebug() << "SqlState : " << tempString;
        tempString.clear();
    }
}
