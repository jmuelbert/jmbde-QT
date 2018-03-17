#ifndef PRINTERINPUTAREA_H
#define PRINTERINPUTAREA_H

#include <QGroupBox>

namespace Ui {
class PrinterInputArea;
}

class PrinterInputArea : public QGroupBox
{
    Q_OBJECT

public:
    explicit PrinterInputArea(QWidget *parent = 0);
    ~PrinterInputArea();

private:
    Ui::PrinterInputArea *ui;
};

#endif // PRINTERINPUTAREA_H
