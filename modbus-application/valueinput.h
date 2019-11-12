#ifndef VALUEINPUT_H
#define VALUEINPUT_H

#include <QWidget>

namespace Ui {
class ValueInput;
}

class ValueInput : public QWidget
{
    Q_OBJECT

public:
    explicit ValueInput(QWidget *parent = nullptr);
    ~ValueInput();

private:
    Ui::ValueInput *ui;
};

#endif // VALUEINPUT_H
