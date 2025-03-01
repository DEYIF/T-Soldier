#include "diamarineboard.h"
#include "ui_diamarineboard.h"

DiaMarineBoard::DiaMarineBoard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DiaMarineBoard)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(1247,586);
    setAttribute(Qt::WA_TranslucentBackground);
}

DiaMarineBoard::~DiaMarineBoard()
{
    delete ui;
}

void DiaMarineBoard::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_Space:
        this->close();
        break;
    }
}
