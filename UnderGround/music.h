#ifndef MUSIC_H
#define MUSIC_H

#include <QWidget>

#include<QGlobalStatic>
class Music : public QWidget
{
    Q_OBJECT
public:
    explicit Music(QWidget *parent = 0,int vol=0.5);
    int volume;
    Phonon::MediaObject* mediaObject = new Phonon::MediaObject(this);
    Phonon::AudioOutput *audioOutput=new Phonon::AudioOutput(Phonon::MusicCategory,this);
    static Music* mus;
signals:

public slots:
    void changeVolume(int value);
};

#endif // MUSIC_H
