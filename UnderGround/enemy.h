#ifndef ENEMY_H
#define ENEMY_H

#include <QWidget>

class Enemy : public QWidget
{
    Q_OBJECT

public:
    int EHp;//Enemy生命值
    int EmaxHp;//Enemy最大生命值
    int EEn;//Enemy精力

    //Enemy坐标
    int Ex;
    int Ey;

    //Enemy长宽
    int Ewid;
    int Ehei;
    int goCount;
    //Enemy朝向
    int Edirection;//0下 1上 2左 3右
    QPixmap Epics[6];//不同Enemy的图片
    QPixmap EDeath;//Enemy死亡的图片
    QPixmap Soil;
    //QPixmap Ewalk;//Enemy走路的图片
    bool enemyIsIn(int,int,int,int);//判断Enemy是否在指定区域内 左右上下
    void enemyReduceHp(int);//Enemy血量减少
    void enemyIncreaseHp(int);//Enemy血量增加
    void enemyTurnToSoil();//拖把扫掉
    QPixmap getpic(int,int);
public:
    explicit Enemy(QWidget *parent = 0);

signals:

public slots:
};

#endif // ENEMY_H
