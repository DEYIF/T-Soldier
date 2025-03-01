#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
#include<QTimer>
#include <Phonon/MediaObject>
#include <Phonon/VideoPlayer>
#include <Phonon/BackendCapabilities>
#include<Phonon/AudioOutput>
#include<QKeyEvent>
namespace Ui {
class Setting;
}

class Setting : public QWidget
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = 0);
    ~Setting();
    QTimer tim;
    int volume;
    Phonon::MediaObject* mediaObject = new Phonon::MediaObject(this);
    Phonon::AudioOutput *audioOutput=new Phonon::AudioOutput(Phonon::MusicCategory,this);
    void keyPressEvent(QKeyEvent *);
signals:
    void sliderMove(int value);
private slots:
    void on_btn_backToLogin_clicked();
    void on_sli_MusicLevel_valueChanged(int value);
private:
    Ui::Setting *ui;
};

#endif // SETTING_H
