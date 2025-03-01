#include "music.h"

Q_GLOBAL_STATIC(Music,mus)
Music::Music(QWidget *parent,int vol) : QWidget(parent)
{
    volume=5;
    vol=volume;
    mediaObject->setCurrentSource(Phonon::MediaSource(":/Music/BgmMarioUpGround.mp3"));
    Phonon::createPath(mediaObject, audioOutput);
    audioOutput->setVolume(0.50);
    mediaObject->play();
}

void Music::changeVolume(int value){
    audioOutput->setVolume(double(value)/10.0);
}
