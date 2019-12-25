#ifndef MESSAGEALERT_H
#define MESSAGEALERT_H

#include <QDialog>

namespace Ui
{
    class MessageAlert;
}

class MessageAlert : public QDialog
{
    Q_OBJECT

public:
    MessageAlert(QString title, QString message, QWidget *parent = nullptr);

    ~MessageAlert();

private slots:
    void on_ok_clicked();

private:
    void changeEvent(QEvent *) override;

    Ui::MessageAlert *ui;
};

#endif // MESSAGEALERT_H
