#ifndef MACHINEVIEW_H
#define MACHINEVIEW_H

#include <QFrame>

namespace Ui {
class MachineView;
}

class MachineView : public QFrame
{
    Q_OBJECT

public:
    explicit MachineView(QWidget *parent = nullptr);
    ~MachineView();

private:
    Ui::MachineView *ui;
};

#endif // MACHINEVIEW_H
