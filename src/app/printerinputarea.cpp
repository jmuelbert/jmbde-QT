#include "printerinputarea.h"
#include "ui_printerinputarea.h"

PrinterInputArea::PrinterInputArea(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::PrinterInputArea)
{
    ui->setupUi(this);
}

PrinterInputArea::~PrinterInputArea()
{
    delete ui;
}
