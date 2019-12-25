#ifndef RATELISTENER_H
#define RATELISTENER_H

#include "components/Conveyor.h"
#include "interfaces/ConveyorRateMessageReceiver.h"
#include "machine/ConveyorControl.h"

#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QPushButton>

class RateListener : public QObject, public simulator::ConveyorRateMessageReceiver
{
    Q_OBJECT

public:
    RateListener(const simulator::Conveyor&, QLabel *);

    RateListener(const simulator::Conveyor&, QLineEdit *);

    RateListener(const simulator::Conveyor&, QPushButton *);

    void ReceiveMessage(std::shared_ptr<simulator::ConveyorRateMessage>) override;

signals:
    void setRate(QString);

private:
    Q_INVOKABLE void setButtonLabel(QString);

    const simulator::Conveyor& m_conveyor;
    QLabel *m_rateLabel;
    QPushButton *m_button;
    QLineEdit *m_lineEdit;
};

#endif // RATELISTENER_H
