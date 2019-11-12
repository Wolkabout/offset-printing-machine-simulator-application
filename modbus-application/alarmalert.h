#ifndef ALARMALERT_H
#define ALARMALERT_H

#include "simulator.h"

#include <QWidget>

namespace Ui {
class AlarmAlert;
}

class AlarmAlert : public QWidget
{
    Q_OBJECT

public:
    AlarmAlert(QString message, Simulator& simulator, QWidget *component = nullptr, QWidget *parent = nullptr);
    AlarmAlert(QString title, QString message);
    ~AlarmAlert();
    void windowActivationChange(bool) override;

private slots:
    void on_ok_clicked();

    void on_goto_2_clicked();

private:
    QString message;
    QWidget *component;
    Ui::AlarmAlert *ui;
    Simulator& simulator;
};

#endif // ALARMALERT_H
