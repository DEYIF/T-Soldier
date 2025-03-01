#include "setting.h"
#include "ui_setting.h"
#include<login.h>
#include<music.h>
Setting::Setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    volume=5;
    mediaObject->setCurrentSource(Phonon::MediaSource(":/Music/BgmMarioUpGround.mp3"));
    Phonon::createPath(mediaObject, audioOutput);
    audioOutput->setVolume(0.20);
    mediaObject->play();
    //this->grabKeyboard();
}


Setting::~Setting(){
    delete ui;
}

void Setting::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_Escape:
        this->show();
        qDebug()<<"SetEsc";
    }
}

void Setting::on_btn_backToLogin_clicked()
{
    this->hide();
}

void Setting::on_sli_MusicLevel_valueChanged(int value)
{
    audioOutput->setVolume(double(value)/100.00);
}
