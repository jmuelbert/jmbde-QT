#ifndef CHIPCARDOINPUTAREA_H
#define CHIPCARDOINPUTAREA_H

#include <QGroupBox>

namespace Ui {
class ChipCardOInputArea;
}

class ChipCardOInputArea : public QGroupBox
{
    Q_OBJECT

public:
    explicit ChipCardOInputArea(QWidget *parent = 0);
    ~ChipCardOInputArea();

private:
    Ui::ChipCardOInputArea *ui;
};

#endif // CHIPCARDOINPUTAREA_H
