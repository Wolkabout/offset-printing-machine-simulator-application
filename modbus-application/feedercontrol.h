#ifndef FEEDERCONTROL_H
#define FEEDERCONTROL_H

#include <QLabel>
#include <QWidget>

#include <Components/Feeder.h>

namespace Ui {
class FeederControl;
}

class FeederControl : public QWidget
{
    Q_OBJECT

public:
    FeederControl(Feeder &feeder, QWidget *parent = nullptr);
    ~FeederControl();

private slots:
    void on_ok_clicked();

    void on_edit_clicked();

    void on_failure_clicked();

private:
    Ui::FeederControl *ui;
    Feeder &feeder;
    std::shared_ptr<CountMessageReceiver> countListener;

    class ComponentCountListener : public CountMessageReceiver {
    private:
        FeederControl& fc;
        TempoComponent& tempoComponent;
        QLabel * countLabel;
        QLabel * percentageLabel;
    public:
        ComponentCountListener(FeederControl&, TempoComponent&, QLabel *, QLabel *);
        void ReceiveMessage(std::shared_ptr<CountMessage>) override;
    };
};

#endif // FEEDERCONTROL_H
