#include "diamop.h"
#include "ui_diamop.h"
DiaMop::DiaMop(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DiaMop)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(1247,586);
    setAttribute(Qt::WA_TranslucentBackground);
}

DiaMop::~DiaMop()
{
    delete ui;
}

void DiaMop::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_Space:
        this->close();
        break;
    }
}
