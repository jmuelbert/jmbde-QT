#ifndef EMPLOYEEINPUTDIALOG_H
#define EMPLOYEEINPUTDIALOG_H


#include <QDialog>

#include "datamodell.h"

namespace Ui {
class EmployeeInputDialog;
}

class EmployeeInputDialog : public QDialog

{
    Q_OBJECT

public:
    explicit EmployeeInputDialog(QWidget *parent = 0);
    ~EmployeeInputDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::EmployeeInputDialog *ui;
    DataModell *dm;
};

#endif // EMPLOYEEINPUTDIALOG_H
