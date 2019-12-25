#ifndef VALUEINPUT_H
#define VALUEINPUT_H

#include <functional>
#include <QDialog>

namespace Ui
{
    class ValueInput;
}

class ValueInput : public QDialog
{
    Q_OBJECT

public:
    ValueInput(QString title, QString message,
               QWidget *parent, std::function<void(std::string)> callback);

    ~ValueInput();

private slots:
    void on_ok_clicked();

    void on_apply_clicked();

    void on_cancel_clicked();

private:
    void changeEvent(QEvent *) override;

    std::function<void(std::string)> m_callback;
    Ui::ValueInput *ui;
};

#endif // VALUEINPUT_H
