#include "mediaplayer.h"
#include<setting.h>
MediaPlayer::MediaPlayer(QWidget *parent) : QWidget(parent)
{
    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory,this);
    mediaObject = new Phonon::MediaObject(this);
    Phonon::createPath(mediaObject, audioOutput);//建立连接
    //音量

    //进度条

    //添加播放路径
    QUrl url("qrc:/Music/BgmMarioUpGround.mp3");
    mediaObject->setCurrentSource(url);
    connect(mediaObject, SIGNAL(finished()), SLOT(finished()));//循环播放
    mediaObject->play();
}

void MediaPlayer::finished()
{
    QUrl url("aaa.wav");
    mediaObject->setCurrentSource(url);
    mediaObject->play();
}
