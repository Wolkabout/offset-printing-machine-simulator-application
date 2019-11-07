#ifndef COUNTLISTENER_H
#define COUNTLISTENER_H

#include <Interfaces/CountMessageReceiver.h>
#include <Components/TempoComponent.h>
#include <QLabel>
#include <QPushButton>

class CountListener : public QObject, public CountMessageReceiver {
private:
    Q_OBJECT
    TempoComponent& tempoComponent;
    QPushButton * button = nullptr;
    QLabel * label;
    QLabel * optionalLabel;
public:
    CountListener(TempoComponent&, QLabel *, QLabel * optionalLabel);
    CountListener(TempoComponent&, QLabel *);
    CountListener(TempoComponent&, QPushButton *);
    void ReceiveMessage(std::shared_ptr<CountMessage>) override;
    Q_INVOKABLE void setLabels(QString, QString);
signals:
    void receiveLabels(QString, QString);
};

#endif // COUNTLISTENER_H
