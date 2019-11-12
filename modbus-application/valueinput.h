#ifndef VALUEINPUT_H
#define VALUEINPUT_H

#include <QWidget>
#include <functional>

namespace Ui {
class ValueInput;
}

class ValueInput : public QWidget
{
    Q_OBJECT

public:
    ValueInput(QString title, QString message, QWidget *parent, std::function<void(std::string)> callback);
    ~ValueInput();

private slots:
    void on_ok_clicked();

    void on_apply_clicked();

    void on_cancel_clicked();

private:
    Ui::ValueInput *ui;
    std::function<void(std::string)> callback;
};

#endif // VALUEINPUT_H
