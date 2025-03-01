#include "login.h"
#include "ui_login.h"
#include<choose.h>
#include<help.h>
Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
}

Login::~Login()
{
    delete ui;
}

void Login::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_Return:case Qt::Key_Enter:
        this->on_btn_begin_clicked();
        break;
    }
}

void Login::on_btn_setting_clicked()
{
    settingShow();
}

void Login::on_btn_begin_clicked()
{
    Choose* cho=new Choose;
    cho->show();
    this->close();
}

void Login::settingShow()
{
    set->show();
}


void Login::on_pushButton_clicked()
{
    Help* he=new Help;
    he->show();
}
