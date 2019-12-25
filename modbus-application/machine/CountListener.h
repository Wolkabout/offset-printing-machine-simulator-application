#ifndef COUNTLISTENER_H
#define COUNTLISTENER_H

#include "interfaces/CountMessageReceiver.h"
#include "components/TempoComponent.h"

#include <QLabel>
#include <QPushButton>

class CountListener : public QObject, public simulator::CountMessageReceiver
{
    Q_OBJECT
public:
    CountListener(const simulator::TempoComponent&, QLabel *, QLabel *optionalLabel);

    CountListener(const simulator::TempoComponent&, QLabel *);

    CountListener(const simulator::TempoComponent&, QPushButton *);

    void ReceiveMessage(std::shared_ptr<simulator::CountMessage>) override;

    Q_INVOKABLE void setLabels(QString, QString);

signals:
    void receiveLabels(QString, QString);

private:
    const simulator::TempoComponent& m_tempoComponent;
    QPushButton *m_button = nullptr;
    QLabel *m_label;
    QLabel *m_optionalLabel;
};

#endif // COUNTLISTENER_H
