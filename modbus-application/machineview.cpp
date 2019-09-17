#include "machineview.h"
#include "ui_machineview.h"

#include <QMovie>
#include <QDebug>

MachineView::MachineView(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::MachineView)
{
    ui->setupUi(this);

    QMovie * movie = new QMovie(":/Animations/Resources/ConveyorAnimation1.gif");
    if (!movie->isValid()) {
        qDebug() << "The Movie isn't valid!" << endl;
    }
    ui->imageTest->setMovie(movie);
    movie->start();
}

MachineView::~MachineView()
{
    delete ui;
}
