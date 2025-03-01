#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QWidget>
#include <Phonon/MediaObject>
#include <Phonon/VideoPlayer>
#include <Phonon/AudioOutput>
#include <Phonon/BackendCapabilities>
#include <QUrl>
#include <QTime>
Phonon::AudioOutput* audioOutput;
Phonon::MediaObject* mediaObject;

class MediaPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit MediaPlayer(QWidget *parent = 0);

signals:

public slots:
    void finished();
};

#endif // MEDIAPLAYER_H
