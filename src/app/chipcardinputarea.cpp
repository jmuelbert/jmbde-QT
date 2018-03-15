#include "chipcardoinputarea.h"
#include "ui_chipcardoinputarea.h"

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
