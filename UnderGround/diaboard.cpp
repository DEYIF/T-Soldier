#include "diaboard.h"
#include "ui_diaboard.h"

DiaBoard::DiaBoard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DiaBoard)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(1247,586);
    setAttribute(Qt::WA_TranslucentBackground);
}

DiaBoard::~DiaBoard()
{
    delete ui;
}

void DiaBoard::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_Space:
        this->close();
        break;
    }
}
