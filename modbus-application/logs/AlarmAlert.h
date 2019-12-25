#ifndef ALARMALERT_H
#define ALARMALERT_H

#include "Simulator.h"

#include <QWidget>

namespace Ui
{
    class AlarmAlert;
}

class AlarmAlert : public QWidget
{
    Q_OBJECT

public:
    AlarmAlert(const QString& message, const Simulator& simulator, QWidget *component = nullptr, QWidget *parent = nullptr);

    ~AlarmAlert();

    void changeEvent(QEvent *) override;

private slots:
    void on_ok_clicked();

    void on_goto_2_clicked();

private:
    const QString& m_message;
    const Simulator& m_simulator;
    QWidget *m_component;
    Ui::AlarmAlert *ui;
};

#endif // ALARMALERT_H
