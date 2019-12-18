#ifndef RATELISTENER_H
#define RATELISTENER_H

#include "Machine/conveyorcontrol.h"
#include <regex>
#include <QObject>
#include <QPushButton>
#include <QLineEdit>
#include <Interfaces/ConveyorRateMessageReceiver.h>

class RateListener : public QObject, public ConveyorRateMessageReceiver {
private:
    Q_OBJECT
    Conveyor& m_conveyor;
    QLabel * m_rateLabel;
    QPushButton * m_button;
    QLineEdit * m_lineEdit;
    Q_INVOKABLE void setButtonLabel(QString);
public:
    RateListener(Conveyor&, QLabel *);
    RateListener(Conveyor&, QLineEdit *);
    RateListener(Conveyor&, QPushButton *);
    void ReceiveMessage(std::shared_ptr<ConveyorRateMessage>) override;
signals:
    void setRate(QString);
};

#endif // RATELISTENER_H
