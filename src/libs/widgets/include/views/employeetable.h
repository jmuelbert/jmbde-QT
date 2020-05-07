#ifndef EMPLOYEETABLE_H
#define EMPLOYEETABLE_H

#include <QDebug>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QPushButton>
#include <QWidget>
#include <QtSql>

#include "jmbdewidgets-version.h"
#include "jmbdewidgets_export.h"
#include "loggingcategory.h"

namespace Ui
{
class EmployeeTable;
}

class EmployeeTable : public QWidget
{
    Q_OBJECT

public:
    explicit EmployeeTable(const QString &tableName, QSqlTableModel *model, QWidget *parent = nullptr);
    ~EmployeeTable();

private:
    Ui::EmployeeTable *ui;
    QPushButton *submitButton;
    QPushButton *revertButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonBox;
    QSqlTableModel *m_model;

private slots:
    void submit();
};

#endif // EMPLOYEETABLE_H
