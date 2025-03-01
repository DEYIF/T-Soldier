#include "diavictory.h"
#include "ui_diavictory.h"
#include<game.h>
DiaVictory::DiaVictory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DiaVictory)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(1247,586);
    setAttribute(Qt::WA_TranslucentBackground);
}

DiaVictory::~DiaVictory()
{
    delete ui;
}

void DiaVictory::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_Escape:{
        this->close();
        break;
    }
    case Qt::Key_R:{
        Game* reg=new Game;
        reg->show();
        this->close();
        break;
    }
    }
}
