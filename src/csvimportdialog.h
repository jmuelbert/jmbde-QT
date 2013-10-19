#ifndef CSVIMPORTDIALOG_H
#define CSVIMPORTDIALOG_H



#include <QDebug>
#include <QFile>
#if QT_VERSION >= 0x050000
#include <QStandardPaths>
#endif
#include <QString>
#include <QTextStream>
#include <QStandardItemModel>

#include <QDialog>
#include <QFileDialog>

namespace Ui {
class CsvImportDialog;
}

class CsvImportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CsvImportDialog(QWidget *parent = 0);
    ~CsvImportDialog();

private:
    Ui::CsvImportDialog *ui;
    QList<QStringList> csv;
    QStandardItemModel *model;
    QList<QStandardItem*> standardItemList;

private slots:
    void checkString(QString &temp, QChar character = 0);

    void on_buttonBox_accepted();
};

#endif // CSVIMPORTDIALOG_H
