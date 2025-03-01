#include "dialog.h"
#include "ui_dialog.h"
#include<game.h>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(1700,1000);
    setAttribute(Qt::WA_TranslucentBackground);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_R:{
        Game* regame=new Game;
        regame->show();
        this->close();
        break;
    }
    case Qt::Key_Escape:{
        this->close();
        break;
    }
    }
}
