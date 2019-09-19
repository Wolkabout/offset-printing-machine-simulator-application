#ifndef ALARMALERT_H
#define ALARMALERT_H

#include <QWidget>

namespace Ui {
class AlarmAlert;
}

class AlarmAlert : public QWidget
{
    Q_OBJECT

public:
    explicit AlarmAlert(QString message, QWidget *component = nullptr, QWidget *parent = nullptr);
    ~AlarmAlert();

private slots:
    void on_ok_clicked();

    void on_goto_2_clicked();

private:
    QString message;
    QWidget *component;
    Ui::AlarmAlert *ui;
};

#endif // ALARMALERT_H
