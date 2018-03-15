#include "chipcardinputarea.h"
#include "ui_chipcardinputarea.h"

ChipCardOInputArea::ChipCardOInputArea(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::ChipCardOInputArea)
{
    ui->setupUi(this);
}

ChipCardOInputArea::~ChipCardOInputArea()
{
    delete ui;
}
